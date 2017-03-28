#ifndef __REDISRESULT_H__
#define __REDISRESULT_H__

#include <string>

namespace hiredis_cpp
{
    class CRedisEvent;

    class CRedisResult
    {
    public:
        CRedisResult();
        virtual ~CRedisResult() = 0;

        time_t getTime();
        void setEvent(CRedisEvent* event);
        CRedisEvent* getEvent();
    protected:
        time_t          m_time;	// reply time
        CRedisEvent*    m_event;
    };
}
#endif
