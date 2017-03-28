#ifndef __REDISARRAYRESULT_H__
#define  __REDISARRAYRESULT_H__

#include "RedisResult.h"
#include <vector>
#include <string>

namespace hiredis_cpp
{
    class CRedisArrayResult :public CRedisResult
    {
    public:
        CRedisArrayResult() {}
        virtual ~CRedisArrayResult() {}

        std::vector<std::string>& getArray() { return m_retVal; }
    private:
        std::vector<std::string> m_retVal;
    };
}
#endif