#ifndef __REDISERRORRESULT_H__
#define __REDISERRORRESULT_H__

#include <string>
#include "RedisResult.h"

namespace hiredis_cpp
{
    class CRedisErrorResult :public CRedisResult
    {
    public:
        CRedisErrorResult() {}
        virtual ~CRedisErrorResult() {}
   
        void setError(const std::string& err) { m_retVal = err; }
        std::string& getError() { return m_retVal; }
    private:
        std::string     m_retVal;
    };
}
#endif
