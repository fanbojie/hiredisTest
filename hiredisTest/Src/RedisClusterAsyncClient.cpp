#include "RedisClusterAsyncClient.h"
#include "stdlib.h"
#include "t120trace.h"
#include "safe_str_lib.h"
#include "HiredisHeader.h"
#include "RedisEventSink.h"
#include "RedisEvent.h"
#include "RedisResult.h"
#include "ConnectResult.h"
#include "DisconnectResult.h"
#include "RedisConnectEvent.h"
#include "RedisUtils.h"

using namespace std;

aeEventLoop* hiredis_cpp::CRedisClusterAsyncClient::m_eventLoop = NULL;
map<hiredis_cpp::CRedisEvent*, long long> hiredis_cpp::CRedisClusterAsyncClient::m_eventMap;

hiredis_cpp::CRedisClusterAsyncClient::CRedisClusterAsyncClient(const char* addr, aeEventLoop* loop)
    : CRedisClient()
    , m_redisAsynCtx(NULL)
{
    m_eventLoop = loop;
    strncpy_s(obj_key, sizeof(obj_key), "CRedisClusterAsyncClient", sizeof(obj_key) - 1);
    this->m_address = addr;
}

hiredis_cpp::CRedisClusterAsyncClient::~CRedisClusterAsyncClient()
{
    close();
}

void hiredis_cpp::CRedisClusterAsyncClient::setAddress(const char* address)
{
    this->m_address = address;
}

bool hiredis_cpp::CRedisClusterAsyncClient::open(CRedisEvent* event /*= NULL*/)
{
    m_redisAsynCtx = redisClusterAsyncConnect(this->m_address.c_str(), HIRCLUSTER_FLAG_NULL);
    if (m_redisAsynCtx == NULL || m_redisAsynCtx->err)
    {
        if (m_redisAsynCtx != NULL)
        {
            INFOXTRACE("Error: " << m_redisAsynCtx->errstr);
        }
        return false;
    }

    m_redisAsynCtx->data = static_cast<void*>(event);
    redisClusterAeAttach(m_eventLoop, m_redisAsynCtx);
    redisClusterAsyncSetConnectCallback(m_redisAsynCtx, &CRedisClusterAsyncClient::onConnect);
    redisClusterAsyncSetDisconnectCallback(m_redisAsynCtx, &CRedisClusterAsyncClient::onDisconnect);
    return true;
}

void hiredis_cpp::CRedisClusterAsyncClient::close()
{
    if (m_redisAsynCtx != NULL)
    {
        redisClusterAsyncDisconnect(m_redisAsynCtx);
        m_redisAsynCtx = NULL;
    }
}


bool hiredis_cpp::CRedisClusterAsyncClient::reopen(CRedisEvent* event /*= NULL*/)
{
    return open(event);
}

int hiredis_cpp::CRedisClusterAsyncClient::execCmd(CRedisEvent* event)
{
    int ret = -1;
    if (m_redisAsynCtx != NULL)
    {
        long long id = aeCreateTimeEvent(m_eventLoop, 1000, &CRedisClusterAsyncClient::aeTimeProc, event, NULL);
        if (id != -1)
        {
            event->setId(id);
            m_eventMap[event] = id;
            ret = redisClusterAsyncCommand(m_redisAsynCtx, CRedisClusterAsyncClient::onReply, static_cast<void*>(event), event->getCmd().c_str());
        }
    }

    if (ret != 0)
    {
        CRedisClusterAsyncClient::onReply(m_redisAsynCtx, NULL, event);
    }

    return ret;
}

void hiredis_cpp::CRedisClusterAsyncClient::onDisconnect(const struct redisAsyncContext* ctx, int status)
{
    INFOTRACE("CRedisClusterAsyncClient::onDisconnect" << status);
    if (ctx != NULL && ctx->data != NULL)
    {
        CRedisConnectEvent* event = static_cast<CRedisConnectEvent*>(ctx->data);
        CRedisClusterAsyncClient* client = static_cast<CRedisClusterAsyncClient*>(event->getClient());
        client->resetCtx();

        IRedisEventSink* sink = event->getSink();
        if (sink != NULL)
        {
            CDisconnectResult* result = new CDisconnectResult;
            result->setVal(status);
            result->setEvent(event);
            sink->callback(result);
        }
    }
}

void hiredis_cpp::CRedisClusterAsyncClient::onConnect(const struct redisAsyncContext* ctx, int status)
{
    INFOTRACE("CRedisClusterAsyncClient::onConnect" << status);
    if (ctx != NULL && ctx->data != NULL)
    {
        CRedisConnectEvent* event = static_cast<CRedisConnectEvent*>(ctx->data);
        if (status != REDIS_OK)
        {
            CRedisClusterAsyncClient* client = static_cast<CRedisClusterAsyncClient*>(event->getClient());
            client->resetCtx();
        }

        IRedisEventSink* sink = event->getSink();
        if (sink != NULL)
        {
            CConnectResult* result = new CConnectResult;
            result->setVal(status);
            result->setError(ctx->errstr);
            result->setEvent(event);
            sink->callback(result);
        }
    }
}

void hiredis_cpp::CRedisClusterAsyncClient::onReply(struct redisClusterAsyncContext* ctx, void*reply, void*privdata)
{
    INFOTRACE("CRedisClusterAsyncClient::onReply");
    if (privdata != NULL)
    {
        CRedisEvent* event = static_cast<CRedisEvent*>(privdata);
        map<CRedisEvent*, long long>::iterator iter = m_eventMap.find(event);
        if (iter != m_eventMap.end() && iter->second == event->getId())
        {
            aeDeleteTimeEvent(m_eventLoop, event->getId());
            m_eventMap.erase(iter);
            IRedisEventSink* sink = event->getSink();
            if (sink != NULL)
            {
                INFOTRACE("event cmd " << event->getCmd().c_str());
                CRedisResult* result = CRedisUtils::convertRedisReply(static_cast<redisReply*>(reply));
                result->setEvent(event);
                sink->callback(result);
            }
        }
        else
        {
            ERRTRACE("can not find event, maybe timeout, event=" << privdata);
        }
    }
}


int hiredis_cpp::CRedisClusterAsyncClient::aeTimeProc(struct aeEventLoop *eventLoop, long long id, void *clientData)
{
    CRedisEvent* event = static_cast<CRedisEvent*>(clientData);
    m_eventMap.erase(event);
    IRedisEventSink* sink = event->getSink();
    if (sink != NULL)
    {
        INFOTRACE("event " << clientData << " cmd " << event->getCmd().c_str() << " timeout"<<" id="<<id);
        CRedisResult* result = CRedisUtils::convertRedisReply(NULL);
        result->setEvent(event);
        sink->callback(result);
    }
    return -1;
}

void hiredis_cpp::CRedisClusterAsyncClient::resetCtx()
{
    m_redisAsynCtx = NULL;
}

