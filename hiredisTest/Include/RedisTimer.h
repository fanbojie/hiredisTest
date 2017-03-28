#ifndef __REDISTIMER_H__
#define __REDISTIMER_H__

#include "t120base.h"

class CRedisTimer;

class CRedisTimerSink
{
public:
    CRedisTimerSink() {};
    virtual ~CRedisTimerSink() {};
    virtual void onTimer(int timerId, CRedisTimer* timer) = 0;
};

class CRedisTimer :public T120_Timer_Object
{
public:
    CRedisTimer(int timerId, CRedisTimerSink* sink);
    virtual ~CRedisTimer();
    virtual void on_timer();

private:
    CRedisTimerSink* m_sink;
    int m_timerId;

};
#endif
