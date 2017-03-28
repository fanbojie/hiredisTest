#ifndef __REDISINTEGERRESULT_H__
#define __REDISINTEGERRESULT_H__

#include "RedisResult.h"

namespace hiredis_cpp
{
    class CRedisIntegerResult :public CRedisResult
    {
    public:
        CRedisIntegerResult() {}
        virtual ~CRedisIntegerResult() {}

        void setInteger(int integer) { m_retVal = integer; }
        int getInteger() { return m_retVal; }
    private:
        int m_retVal;
    };
}
#endif