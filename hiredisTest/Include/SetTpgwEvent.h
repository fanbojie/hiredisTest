#ifndef __SETTPGWEVENT_H__
#define __SETTPGWEVENT_H__

#include "RedisEvent.h"

class IRedisProxySink;

class CSetTpgwEvent :public hiredis_cpp::CRedisEvent
{
public:
    CSetTpgwEvent();
    virtual ~CSetTpgwEvent();

    void setHandle(void* handle);
    void* getHandle();
    IRedisProxySink* getProxySink();
    void setProxySink(IRedisProxySink* sink);
private:
    void* m_handle;         // store business data
    IRedisProxySink* m_proxySink;
};
#endif
