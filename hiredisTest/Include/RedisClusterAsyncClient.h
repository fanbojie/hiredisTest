#ifndef __REDISCLUSTERASYNCCLIENT_H__
#define __REDISCLUSTERASYNCCLIENT_H__

#include <map>
#include "RedisClient.h"

class aeEventLoop;
class redisClusterAsyncContext;
class redisAsyncContext;

namespace hiredis_cpp
{
    class CRedisClusterAsyncClient :public CRedisClient
    {
    public:
        CRedisClusterAsyncClient(const char* addr, aeEventLoop* loop);
        virtual ~CRedisClusterAsyncClient();
        virtual void setAddress(const char* address);
        virtual bool open(CRedisEvent* event = NULL);
        virtual void close();
        virtual bool reopen(CRedisEvent* event = NULL);
        virtual int execCmd(CRedisEvent* event);
        static void onDisconnect(const struct redisAsyncContext* ctx, int status);
        static void onConnect(const struct redisAsyncContext* ctx, int status);
        static void onReply(struct redisClusterAsyncContext* ctx, void*reply, void*privdata);
        static int aeTimeProc(struct aeEventLoop *eventLoop, long long id, void *clientData);
        void resetCtx();
    private:
        static aeEventLoop*       m_eventLoop;
        static std::map<CRedisEvent*, long long> m_eventMap;
        char obj_key[128];
        redisClusterAsyncContext*   m_redisAsynCtx;
    };
}
#endif
