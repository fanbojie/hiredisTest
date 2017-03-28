#ifndef __REDISUTILS_H__
#define __REDISUTILS_H__

class redisReply;

namespace hiredis_cpp
{
    class CRedisResult;

    class CRedisUtils
    {
    public:
       static CRedisResult* convertRedisReply(redisReply* reply);
    };
}
#endif
