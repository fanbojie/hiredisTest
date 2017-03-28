#ifndef __SETTPGWEXPIREEVENT_H__
#define __SETTPGWEXPIREEVENT_H__

#include "RedisEvent.h"

class IRedisProxySink;

class CSetTpgwExpireEvent :public hiredis_cpp::CRedisEvent
{
public:
    CSetTpgwExpireEvent();
    virtual ~CSetTpgwExpireEvent();

    IRedisProxySink* getProxySink();
    void setProxySink(IRedisProxySink* sink);
private:

    IRedisProxySink* m_proxySink;

};

#endif
