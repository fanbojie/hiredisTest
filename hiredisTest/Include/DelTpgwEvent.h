#ifndef __DELTPGWEVENT_H__
#define __DELTPGWEVENT_H__

#include "RedisEvent.h"

class IRedisProxySink;

class CDelTpgwEvent :public hiredis_cpp::CRedisEvent
{
public:
    CDelTpgwEvent();
    virtual ~CDelTpgwEvent();

    IRedisProxySink* getProxySink();
    void setProxySink(IRedisProxySink* sink);
private:
    IRedisProxySink* m_proxySink;
};
#endif