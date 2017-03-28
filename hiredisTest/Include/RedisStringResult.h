#ifndef __REDISSTRINGRESULT_H__
#define __REDISSTRINGRESULT_H__

#include "RedisResult.h"
#include <string>

namespace hiredis_cpp
{
    class CRedisStringResult : public CRedisResult
    {
    public:
        CRedisStringResult() {};
        virtual ~CRedisStringResult() {};

        void setString(const std::string& str) { m_retVal = str; }
        std::string& getString() { return m_retVal; }
    private:
        std::string m_retVal;
    };
}
#endif
