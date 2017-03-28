#ifndef __CONNECTRESULT_H__
#define __CONNECTRESULT_H__

#include "RedisResult.h"

namespace hiredis_cpp
{
    class CConnectResult :public CRedisResult
    {
    public:
        CConnectResult():m_retVal(0) {};
        virtual ~CConnectResult() {};

        void setError(const std::string& err) { m_err = err; }
        std::string& getError() { return m_err; }
        void setVal(int ret) { m_retVal = ret; }
        int getVal() { return m_retVal; }
    private:
        std::string m_err;
        int         m_retVal;
    };

}
#endif
