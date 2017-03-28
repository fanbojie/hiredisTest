#include "RedisTimer.h"

CRedisTimer::CRedisTimer(int timerId, CRedisTimerSink* sink)
    : m_sink(sink)
    , m_timerId(timerId)
{
}

CRedisTimer::~CRedisTimer()
{
    schedule_cancel();
}

void CRedisTimer::on_timer()
{
    if (m_sink != NULL)
    {
        m_sink->onTimer(m_timerId, this);
    }
}
