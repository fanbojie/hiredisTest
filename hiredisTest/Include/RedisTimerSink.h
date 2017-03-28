#ifndef __REDISTIMERSINK_H__
#define __REDISTIMERSINK_H__

class CRedisTimer;

namespace hiredis_cpp
{
    class CRedisTimerSink
    {
    public:
        CRedisTimerSink() {};
        virtual ~CRedisTimerSink() {};
        virtual void onTimer(int timeId, CRedisTimer* timer) = 0;
    };
}
#endif
