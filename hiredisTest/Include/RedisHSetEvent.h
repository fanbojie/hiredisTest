#ifndef __REDISHSETEVENT_H__
#define __REDISHSETEVENT_H__

#include "RedisEvent.h"

namespace hiredis_cpp
{
    class CRedisHSetNXEvent :public CRedisEvent
    {
    public:
        CRedisHSetNXEvent();
        virtual ~CRedisHSetNXEvent();
    };
}
#endif
