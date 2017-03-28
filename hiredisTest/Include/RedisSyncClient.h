#ifndef __REDISSYNCCLIENT_H__
#define __REDISSYNCCLIENT_H__

#include "RedisClient.h"

class redisContext;
class redisReply;

namespace hiredis_cpp
{
    class CRedisSyncClient: public CRedisClient
    {
    public:
	    CRedisSyncClient(const char* addr, int conn_timeout = 0);
	    virtual ~CRedisSyncClient();
        virtual void setAddress(const char* address);
	    virtual bool open(CRedisEvent* event = NULL);
	    virtual void close();
	    virtual redisReply* execCmd(const char* cmd);
    private:
        char obj_key[128];
	    redisContext* m_redisCtx;
	    int m_timeout;			// millisecond 
    };
}

#endif

