#ifndef __GETTPGWEVENT_H__
#define __GETTPGWEVENT_H__

#include "RedisEvent.h"

class IRedisProxySink;

class CGetTpgwEvent:public hiredis_cpp::CRedisEvent
{
public:
    CGetTpgwEvent();
    virtual ~CGetTpgwEvent();

    void setHandle(void* handle);
    void* getHandle();
    IRedisProxySink* getProxySink();
    void setProxySink(IRedisProxySink* sink);
private:
    void* m_handle;     // store business data;
    IRedisProxySink* m_proxySink;
};
#endif
