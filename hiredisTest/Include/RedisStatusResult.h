#ifndef __REDISSTATUSRESULT_H__
#define __REDISSTATUSRESULT_H__

#include "RedisResult.h"

namespace hiredis_cpp
{
    class CRedisStatusResult :public CRedisResult
    {
    public:
        CRedisStatusResult() {}
        virtual ~CRedisStatusResult() {}

        void setStatus(const std::string& status) { m_retVal = status; }
        std::string& getStatus() { return m_retVal; }
    private:
        std::string m_retVal;
    };
}
#endif