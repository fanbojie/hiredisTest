#ifndef __REDISASYNCLIENT_H__
#define __REDISASYNCLIENT_H__

#include <map>
#include "RedisClient.h"

class aeEventLoop;
class redisAsyncContext;

namespace hiredis_cpp
{
    class CRedisAsynClient : public CRedisClient
    {
    public:
        CRedisAsynClient(const char* addr, aeEventLoop* loop);
        virtual ~CRedisAsynClient();
        virtual void setAddress(const char* address);
        virtual bool open(CRedisEvent* event = NULL);
        virtual void close();
        virtual bool reopen(CRedisEvent* event = NULL);
        virtual int execCmd(CRedisEvent* event);

        static void onDisconnect(const struct redisAsyncContext* ctx, int status);
        static void onConnect(const struct redisAsyncContext* ctx, int status);
        static void onReply(struct redisAsyncContext* ctx, void*reply, void*privdata);
        static int aeTimeProc(struct aeEventLoop *eventLoop, long long id, void *clientData);
        void resetCtx();
    private:
        static aeEventLoop*       m_eventLoop;
        static std::map<CRedisEvent*, long long> m_eventMap;
        char obj_key[128];
        redisAsyncContext* m_redisAsynCtx;
    };
}

#endif
