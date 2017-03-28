#ifndef __REDISCLUSTERSYNCCLIENT_H__
#define __REDISCLUSTERSYNCCLIENT_H__

#include "RedisClient.h"

class redisReply;
class redisClusterContext;

namespace hiredis_cpp
{
    class CRedisClusterSyncClient :public CRedisClient
    {
    public:
	    CRedisClusterSyncClient(const char* addr, int conn_timeout = 0);
	    virtual ~CRedisClusterSyncClient();
        virtual void setAddress(const char* address);
	    virtual bool open(CRedisEvent* event = NULL);
	    virtual void close();
	    virtual redisReply* execCmd(const char* cmd);
    private:
        char obj_key[128];
	    redisClusterContext* m_redisCtx;
	    int m_timeout;			// millisecond 
    };
}
#endif
