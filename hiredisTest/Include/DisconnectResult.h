#ifndef __DISCONNECTRESULT_H__
#define __DISCONNECTRESULT_H__

#include "RedisResult.h"

namespace hiredis_cpp
{
    class CDisconnectResult :public CRedisResult
    {
    public:
        CDisconnectResult():m_retVal(0) {};
        virtual ~CDisconnectResult() {};

        void setVal(int ret) { m_retVal = ret; }
        int getVal() { return m_retVal; }
    private:
        int m_retVal;
    };
}
#endif
