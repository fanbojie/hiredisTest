#ifndef __REDISHGETEVENT_H__
#define __REDISHGETEVENT_H__

#include "RedisEvent.h"

namespace hiredis_cpp
{
    class CRedisHGetEvent :public CRedisEvent
    {
    public:
        CRedisHGetEvent();
        virtual ~CRedisHGetEvent();
    };
}
#endif
