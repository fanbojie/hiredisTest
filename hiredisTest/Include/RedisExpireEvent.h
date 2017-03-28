#ifndef __REDISEXPIREEVENT_H__
#define __REDISEXPIREEVENT_H__

#include "RedisEvent.h"

namespace hiredis_cpp
{
    class CRedisExpireEvent :public CRedisEvent
    {
    public:
        CRedisExpireEvent();
        virtual ~CRedisExpireEvent();

    };
}
#endif
