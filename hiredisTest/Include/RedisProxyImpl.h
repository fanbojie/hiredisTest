#ifndef __REDISPROXYIMPL_H__
#define __REDISPROXYIMPL_H__

#include <string>
#include <queue>
#include <map>
#include "t120thread.h"
#include "RedisEventSink.h"
#include "RedisTimer.h"

namespace hiredis_cpp
{
    class CRedisClient;
    class CRedisResult;
    class CRedisEvent;
}

class IRedisProxySink;
class aeEventLoop;

class CRedisProxyImpl:public CRedisTimerSink
                    , public T120_Thread
                    , public hiredis_cpp::IRedisEventSink
{
private:
	CRedisProxyImpl();
	CRedisProxyImpl(const CRedisProxyImpl&);
	CRedisProxyImpl& operator=(const CRedisProxyImpl&);
public:
	~CRedisProxyImpl();
	bool init(const std::string& address, const std::string& password);
    bool uninit();
	static CRedisProxyImpl& getInstance()
	{
		static CRedisProxyImpl instance;
		return instance;
	}

    virtual uint32 thread_run();
    virtual void onTimer(int timerId, CRedisTimer* timer);
    static int aeTimeProc(struct aeEventLoop *eventLoop, long long id, void *clientData);
    virtual void callback(hiredis_cpp::CRedisResult* result);

    void setTimerId(long long timerId) { m_aeTimerId = timerId; }

    // business
    void setTpgw(const std::string& key, const std::string& value, void* handle, IRedisProxySink* sink);
    void getTpgw(const std::string& key, void* handle, IRedisProxySink* sink);
    
    void setTpgwExpire(const std::string& key, int ttl, IRedisProxySink* sink);    // ttl seconds
    void delTpgw(const std::string& key, IRedisProxySink* sink);
private:
    void emitCmd();
    void dealWithRedisResult(hiredis_cpp::CRedisResult* result);
private:
    long long m_aeTimerId;
    char obj_key[128];
	hiredis_cpp::CRedisClient* m_redisClient;
    CRedisTimer* m_resultTimer;
    CRedisTimer* m_requestTimer;
    aeEventLoop* m_loop;
    std::queue<hiredis_cpp::CRedisResult*> m_resultQueue;
    T120_Critical_Section m_resultMutex;
    std::queue<hiredis_cpp::CRedisEvent*> m_eventQueue;
    T120_Critical_Section m_eventMutex;
};
#endif
