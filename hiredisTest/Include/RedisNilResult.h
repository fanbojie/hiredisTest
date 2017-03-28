#ifndef __REDISNILRESULT_H__
#define __REDISNILRESULT_H__

#include "RedisResult.h"

namespace hiredis_cpp
{
    class CRedisNilResult :public CRedisResult
    {
    public:
        CRedisNilResult() {}
        ~CRedisNilResult() {}
    };
}
#endif
