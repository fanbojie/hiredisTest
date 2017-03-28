#include "RedisProxyImpl.h"
#include <iostream>
#include <sstream>
#include "t120trace.h"
#include "safe_str_lib.h"
#include "HiredisHeader.h"
#include "RedisTimer.h"
#include "RedisSyncClient.h"
#include "RedisAsynClient.h"
#include "RedisConnectEvent.h"
#include "RedisAuthEvent.h"
#include "ConnectResult.h"
#include "DisconnectResult.h"
#include "RedisStatusResult.h"
#include "RedisStringResult.h"
#include "RedisNilResult.h"
#include "RedisNullReplyResult.h"
#include "RedisIntegerResult.h"
#include "RedisEvent.h"
#include "SetTpgwExpireEvent.h"
#include "GetTpgwEvent.h"
#include "SetTpgwEvent.h"
#include "DelTpgwEvent.h"
#include "RedisTimer.h"
#include "RedisProxySink.h"

using namespace std;
using namespace hiredis_cpp;

CRedisProxyImpl::CRedisProxyImpl()
	: m_redisClient(NULL)
    , m_aeTimerId(0)
{
    strncpy_s(obj_key, sizeof(obj_key), "CRedisProxyImpl", sizeof(obj_key) - 1);
    m_resultTimer = new CRedisTimer(1, this);
    m_resultTimer->add_reference();
    m_resultTimer->schedule(1000);

    m_requestTimer = new CRedisTimer(2, this);
    m_requestTimer->add_reference();
    m_requestTimer->schedule(1000);
    m_loop = aeCreateEventLoop(64);
}

CRedisProxyImpl::~CRedisProxyImpl()
{
    if (m_loop != NULL)
    {
        aeDeleteTimeEvent(m_loop, m_aeTimerId);
        aeDeleteEventLoop(m_loop);
        m_loop = NULL;
    }

    if (m_resultTimer != NULL)
    {
        m_resultTimer->schedule_cancel();
        m_resultTimer->release_reference();
        m_resultTimer = NULL;
    }

    if (m_requestTimer != NULL)
    {
        m_requestTimer->schedule_cancel();
        m_requestTimer->release_reference();
        m_requestTimer = NULL;
    }

    delete m_redisClient;
    m_redisClient = NULL;

    m_resultMutex.lock();
    while (!m_resultQueue.empty())
    {
        CRedisResult* result = m_resultQueue.front();
        delete result;
        m_resultQueue.pop();
    }
    m_resultMutex.unlock();

    m_eventMutex.lock();
    while (!m_eventQueue.empty())
    {
        CRedisEvent* event = m_eventQueue.front();
        delete event;
        m_eventQueue.pop();

    }
    m_eventMutex.unlock();
}

bool CRedisProxyImpl::init(const std::string& address, const std::string& password)
{
    if (m_loop == NULL)
    {
        return false;
    }

    bool ret = T120_Thread::create();
    if (!ret)
    {
        return false;
    }

    m_redisClient = new CRedisAsynClient(address.c_str(), m_loop);
    if (m_redisClient != NULL)
    {
	    m_redisClient->setPassword(password.c_str());
        CRedisConnectEvent* event = new CRedisConnectEvent;
        event->setClient(m_redisClient);
        event->setSink(this);
	    return m_redisClient->open(event);
    }

    return false;
}

bool CRedisProxyImpl::uninit()
{
    if (m_loop != NULL)
    {
        aeStop(m_loop);
    }

    T120_Thread::stop(0);
}

uint32 CRedisProxyImpl::thread_run()
{
    INFOXTRACE("ae loop run...");
    aeCreateTimeEvent(m_loop, 3, &CRedisProxyImpl::aeTimeProc, this, NULL);
    aeMain(m_loop);
    return 0;
}

void CRedisProxyImpl::onTimer(int timerId, CRedisTimer* timer)
{
    //INFOXTRACE("on timer, timerId="<<timerId);
    if (timerId == 1)
    {
        timer->schedule(1000);
        CRedisResult* result = NULL;
        m_resultMutex.lock();
        while (!m_resultQueue.empty())
        {
            result = m_resultQueue.front();
            m_resultQueue.pop();
            dealWithRedisResult(result);
        }
        m_resultMutex.unlock();
    }
    else if (timerId == 2)
    {
        m_requestTimer->schedule(1000);
        setTpgw("fanbojie_123","127.0.0.1:999", NULL, NULL);
        getTpgw("fanbojie_123", NULL, NULL);
        setTpgwExpire("fanbojie_123", 60, NULL);
    }
}

int CRedisProxyImpl::aeTimeProc(struct aeEventLoop *eventLoop, long long id, void *clientData)
{
    //INFOTRACE("aeTimeProc, timerId="<<id);
    CRedisProxyImpl* proxy = static_cast<CRedisProxyImpl*>(clientData);
    if (proxy != NULL)
    {
        proxy->emitCmd();
        proxy->setTimerId(id);
    }
    return 3;
}

void CRedisProxyImpl::callback(CRedisResult* result)
{
    m_resultMutex.lock();
    m_resultQueue.push(result);
    m_resultMutex.unlock();
}

void CRedisProxyImpl::setTpgw(const std::string& key, const std::string& value, void* handle, IRedisProxySink* sink)
{
    stringstream cmd;
    cmd << "SETNX " << key << " " << value;
    CSetTpgwEvent* event = new CSetTpgwEvent;
    event->setKey(key);
    event->setCmd(cmd.str());
    event->setSink(this);
    event->setHandle(handle);
    event->setProxySink(sink);
    m_eventMutex.lock();
    m_eventQueue.push(event);
    m_eventMutex.unlock();
}

void CRedisProxyImpl::getTpgw(const std::string& key, void* handle, IRedisProxySink* sink)
{
    stringstream cmd;
    cmd << "GET " << key;
    CGetTpgwEvent* event = new CGetTpgwEvent;
    event->setKey(key);
    event->setCmd(cmd.str());
    event->setSink(this);
    event->setHandle(handle);
    event->setProxySink(sink);
    m_eventMutex.lock();
    m_eventQueue.push(event);
    m_eventMutex.unlock();
}

void CRedisProxyImpl::setTpgwExpire(const std::string& key, int ttl, IRedisProxySink* sink)
{
    stringstream cmd;
    cmd << "EXPIRE " << key << " " << ttl;
    CSetTpgwExpireEvent* event = new CSetTpgwExpireEvent;
    event->setCmd(cmd.str());
    event->setSink(this);
    event->setProxySink(sink);
    m_eventMutex.lock();
    m_eventQueue.push(event);
    m_eventMutex.unlock();
}

void CRedisProxyImpl::delTpgw(const std::string& key, IRedisProxySink* sink)
{
    stringstream cmd;
    cmd << "DEL " << key;
    CDelTpgwEvent* event = new CDelTpgwEvent;
    event->setCmd(cmd.str());
    event->setSink(this);
    event->setProxySink(sink);
    m_eventMutex.lock();
    m_eventQueue.push(event);
    m_eventMutex.unlock();
}

void CRedisProxyImpl::emitCmd()
{
    m_eventMutex.lock();
    while (!m_eventQueue.empty())
    {
        CRedisEvent* event = m_eventQueue.front();
        CRedisConnectEvent* connEvent = dynamic_cast<CRedisConnectEvent*>(event);
        if (connEvent != NULL)
        {
            m_redisClient->reopen(event);
        }
        else
        {
            m_redisClient->execCmd(event);
        }
        m_eventQueue.pop();
    }
    m_eventMutex.unlock();
}

void CRedisProxyImpl::dealWithRedisResult(hiredis_cpp::CRedisResult* result)
{
    if (result == NULL)
    {
        INFOXTRACE("redis result is null");
        return;
    }
    else
    {
        INFOXTRACE("redis cmd=" << result->getEvent()->getCmd().c_str() << " reply");
    }

    CConnectResult* connectResult = dynamic_cast<CConnectResult*>(result);
    if (connectResult != NULL)
    {
        INFOXTRACE("on connect " << connectResult->getVal() << " " << connectResult->getError().c_str());
        if (connectResult->getVal() == 0)
        {
            if (!m_redisClient->getPassword().empty())
            {
                INFOXTRACE("redis need auth first.");
                CRedisAuthEvent* event = new CRedisAuthEvent;
                event->setCmd("AUTH " + m_redisClient->getPassword());
                event->setSink(this);
                m_eventMutex.lock();
                m_eventQueue.push(event);
                m_eventMutex.unlock();
            }
            else
            {
                INFOXTRACE("redis need not auth");
            }
        }
        else
        {
            result->getEvent()->resetTime();
            m_eventMutex.lock();
            m_eventQueue.push(result->getEvent());
            m_eventMutex.unlock();
        }
        delete result;
        return;
    }

    CDisconnectResult* disconnectResult = dynamic_cast<CDisconnectResult*>(result);
    if (disconnectResult != NULL)
    {
        if (disconnectResult->getVal() != 0)
        {
            INFOXTRACE("redis connection disconnect.");
            result->getEvent()->resetTime();
            m_eventMutex.lock();
            m_eventQueue.push(result->getEvent());
            m_eventMutex.unlock();
        }
        else
        {
            delete result->getEvent();
            INFOXTRACE("user disconnect redis connection.");
        }
        delete result;
        return;
    }

    CRedisAuthEvent* authEvent = dynamic_cast<CRedisAuthEvent*>(result->getEvent());
    if (authEvent != NULL)
    {
        CRedisStatusResult* statusResult = dynamic_cast<CRedisStatusResult*>(result);
        if (statusResult != NULL)
        {
            if (statusResult->getStatus() == "OK")
            {
                delete result->getEvent();
                INFOXTRACE("Auth success");
            }
            else
            {
                INFOXTRACE("Auth failed, status=" << statusResult->getStatus().c_str());
                authEvent->resetTime();
                m_eventMutex.lock();
                m_eventQueue.push(authEvent);
                m_eventMutex.unlock();
            }
        }
        else
        {
            INFOXTRACE("Auth reply not status result");
            authEvent->resetTime();
            m_eventMutex.lock();
            m_eventQueue.push(authEvent);
            m_eventMutex.unlock();
        }

        delete result;
        return;
    }

    CGetTpgwEvent* getTpgwEvent = dynamic_cast<CGetTpgwEvent*>(result->getEvent());
    if (getTpgwEvent != NULL)
    {
        IRedisProxySink* proxySink = getTpgwEvent->getProxySink();
        if (proxySink == NULL)
        {
            delete result->getEvent();
            delete result;
            return;
        }

        CRedisStringResult* stringResult = dynamic_cast<CRedisStringResult*>(result);
        if (stringResult != NULL)
        {
            proxySink->onGetTpgw(getTpgwEvent->getKey(), stringResult->getString(), 0, getTpgwEvent->getHandle());
        }
        else
        {
            CRedisNilResult* nilResult = dynamic_cast<CRedisNilResult*>(result);
            if (nilResult != NULL)
            {
                proxySink->onGetTpgw(getTpgwEvent->getKey(), "", 0, getTpgwEvent->getHandle());
            }
            else
            {
                proxySink->onGetTpgw(getTpgwEvent->getKey(), "", -1, getTpgwEvent->getHandle());
            }
        }
    }

    CSetTpgwEvent* setTpgwEvent = dynamic_cast<CSetTpgwEvent*>(result->getEvent());
    if (setTpgwEvent != NULL)
    {
        IRedisProxySink* proxySink = setTpgwEvent->getProxySink();
        if (proxySink == NULL)
        {
            delete result->getEvent();
            delete result;
            return;
        }

        CRedisIntegerResult* integerResult = dynamic_cast<CRedisIntegerResult*>(result);
        if (integerResult != NULL)
        {
            proxySink->onSetTpgw(setTpgwEvent->getKey(), integerResult->getInteger(), setTpgwEvent->getHandle());
        }
        else
        {
            proxySink->onSetTpgw(setTpgwEvent->getKey(), -1, setTpgwEvent->getHandle());
        }
    }

    CSetTpgwExpireEvent* setTpgwExpireEvent = dynamic_cast<CSetTpgwExpireEvent*>(result->getEvent());
    if (setTpgwExpireEvent != NULL)
    {
        IRedisProxySink* proxySink = setTpgwExpireEvent->getProxySink();
        if (proxySink == NULL)
        {
            delete result->getEvent();
            delete result;
            return;
        }

        CRedisIntegerResult* integerResult = dynamic_cast<CRedisIntegerResult*>(result);
        if (integerResult != NULL)
        {
            proxySink->onSetTpgwExpire(setTpgwExpireEvent->getKey(), integerResult->getInteger());
        }
        else
        {
            proxySink->onSetTpgwExpire(setTpgwExpireEvent->getKey(), -1);
        }
    }

    CDelTpgwEvent* delTpgwEvent = dynamic_cast<CDelTpgwEvent*>(result->getEvent());
    if (delTpgwEvent != NULL)
    {
        IRedisProxySink* proxySink = delTpgwEvent->getProxySink();
        if (proxySink == NULL)
        {
            delete result->getEvent();
            delete result;
            return;
        }

        CRedisIntegerResult* integerResult = dynamic_cast<CRedisIntegerResult*>(result);
        if (integerResult != NULL)
        {
            proxySink->onDelTpgw(delTpgwEvent->getKey(), integerResult->getInteger());
        }
        else
        {
            proxySink->onDelTpgw(delTpgwEvent->getKey(), -1);
        }
    }
    delete result->getEvent();
    delete result;
}
