#ifndef __REDISAUTHEVENT_H__
#define __REDISAUTHEVENT_H__

#include "RedisEvent.h"

namespace hiredis_cpp
{
    class CRedisAuthEvent :public CRedisEvent
    {
    public:
        CRedisAuthEvent();
        virtual ~CRedisAuthEvent();
    };
}
#endif
