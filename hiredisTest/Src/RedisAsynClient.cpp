#include "RedisAsynClient.h"
#include "stdlib.h"
#include "safe_str_lib.h"
#include "t120trace.h"
#include "RedisEventSink.h"
#include "RedisEvent.h"
#include "RedisResult.h"
#include "ConnectResult.h"
#include "DisconnectResult.h"
#include "HiredisHeader.h"
#include "RedisUtils.h"
#include "RedisConnectEvent.h"

using namespace std;

aeEventLoop* hiredis_cpp::CRedisAsynClient::m_eventLoop = NULL;
map<hiredis_cpp::CRedisEvent*, long long> hiredis_cpp::CRedisAsynClient::m_eventMap;

hiredis_cpp::CRedisAsynClient::CRedisAsynClient(const char* addr, aeEventLoop* loop)
	: CRedisClient()
	, m_redisAsynCtx(NULL)
{
    m_eventLoop = loop;
    strncpy_s(obj_key, sizeof(obj_key), "CRedisAsynClient", sizeof(obj_key) - 1);
	string addrTmp = addr;
	size_t pos = addrTmp.find_first_of(":");
	this->m_address = addrTmp.substr(0, pos);
	this->m_port = atoi(addrTmp.substr(pos + 1).c_str());
}

hiredis_cpp::CRedisAsynClient::~CRedisAsynClient()
{
    close();
}


void hiredis_cpp::CRedisAsynClient::setAddress(const char* address)
{
    string addrTmp = address;
    size_t pos = addrTmp.find_first_of(":");
    this->m_address = addrTmp.substr(0, pos);
    this->m_port = atoi(addrTmp.substr(pos + 1).c_str());
}

void hiredis_cpp::CRedisAsynClient::close()
{
	if (m_redisAsynCtx != NULL)
	{
		redisAsyncDisconnect(m_redisAsynCtx);
		m_redisAsynCtx = NULL;
	}
}


bool hiredis_cpp::CRedisAsynClient::reopen(CRedisEvent* event /*= NULL*/)
{
    return open(event);
}

int hiredis_cpp::CRedisAsynClient::execCmd(CRedisEvent* event)
{
    // 异步操作是否有不回调的情况，是否要为每个cmd设置超时
    int ret = -1;
    
    if (m_redisAsynCtx != NULL)
    {
        long long id = aeCreateTimeEvent(m_eventLoop, 1000, &CRedisAsynClient::aeTimeProc, event, NULL);
        if (id != -1)
        {
            event->setId(id);
            m_eventMap[event] = id;
            ret = redisAsyncCommand(m_redisAsynCtx, CRedisAsynClient::onReply, static_cast<void*>(event), event->getCmd().c_str());
        }
    }

    if (ret != 0)
    {
        CRedisAsynClient::onReply(m_redisAsynCtx, NULL, event);
    }

    return ret;
}

void hiredis_cpp::CRedisAsynClient::onDisconnect(const struct redisAsyncContext* ctx, int status)
{
    INFOTRACE("CRedisAsynClient::onDisconnect" << status);
    if (ctx != NULL && ctx->data != NULL)
    {
        CRedisConnectEvent* event = static_cast<CRedisConnectEvent*>(ctx->data);
        CRedisAsynClient* client = static_cast<CRedisAsynClient*>(event->getClient());
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

void hiredis_cpp::CRedisAsynClient::onConnect(const struct redisAsyncContext* ctx, int status)
{
    INFOTRACE("CRedisAsynClient::onConnect" << status);
    if (ctx != NULL && ctx->data != NULL)
    {
        CRedisConnectEvent* event = static_cast<CRedisConnectEvent*>(ctx->data);
        if (status != REDIS_OK)
        {
            CRedisAsynClient* client = static_cast<CRedisAsynClient*>(event->getClient());
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

void hiredis_cpp::CRedisAsynClient::onReply(struct redisAsyncContext* ctx, void*reply, void*privdata)
{
    INFOTRACE("CRedisAsynClient::onReply");
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

int hiredis_cpp::CRedisAsynClient::aeTimeProc(struct aeEventLoop *eventLoop, long long id, void *clientData)
{
    CRedisEvent* event = static_cast<CRedisEvent*>(clientData);
    m_eventMap.erase(event);
    IRedisEventSink* sink = event->getSink();
    if (sink != NULL)
    {
        INFOTRACE("event " << clientData << " cmd " << event->getCmd().c_str() << " timeout" << " id=" << id);
        CRedisResult* result = CRedisUtils::convertRedisReply(NULL);
        result->setEvent(event);
        sink->callback(result);
    }
    return -1;
}

void hiredis_cpp::CRedisAsynClient::resetCtx()
{
    m_redisAsynCtx = NULL;
}

bool hiredis_cpp::CRedisAsynClient::open(CRedisEvent* event /*= NULL*/)
{
	m_redisAsynCtx = redisAsyncConnect(this->m_address.c_str(), this->m_port);
	if (m_redisAsynCtx == NULL || m_redisAsynCtx->err)
	{
		if (m_redisAsynCtx != NULL)
		{
            INFOXTRACE("Error: " << m_redisAsynCtx->errstr);
		}
		return false;
	}

    m_redisAsynCtx->data = static_cast<void*>(event);
    redisAeAttach(m_eventLoop, m_redisAsynCtx);
	redisAsyncSetConnectCallback(m_redisAsynCtx, &CRedisAsynClient::onConnect);
	redisAsyncSetDisconnectCallback(m_redisAsynCtx, &CRedisAsynClient::onDisconnect);
	return true;
}

