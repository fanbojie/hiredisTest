#ifndef __REDISNULLREPLYRESULT_H__
#define __REDISNULLREPLYRESULT_H__

#include "RedisResult.h"

namespace hiredis_cpp
{
    class CRedisNullReplyResult :public CRedisResult
    {
    public:
        CRedisNullReplyResult() {}
        virtual ~CRedisNullReplyResult() {}
    };
}
#endif
