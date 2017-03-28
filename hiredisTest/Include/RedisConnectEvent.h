#ifndef __REDISCONNECTEVENT_H__
#define __REDISCONNECTEVENT_H__

#include "RedisEvent.h"

namespace hiredis_cpp
{
    class CRedisClient;

    class CRedisConnectEvent : public CRedisEvent
    {
    public:
        CRedisConnectEvent();
        virtual ~CRedisConnectEvent();
        void setClient(CRedisClient* client);
        CRedisClient* getClient();
    private:
        CRedisClient* m_client;
    };
}
#endif