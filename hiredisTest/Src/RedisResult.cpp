#include "RedisResult.h"
#include <time.h>

hiredis_cpp::CRedisResult::CRedisResult()
    : m_event(NULL)
{
    m_time = time(NULL);
}

hiredis_cpp::CRedisResult::~CRedisResult()
{

}

time_t hiredis_cpp::CRedisResult::getTime()
{
    return m_time;
}

void hiredis_cpp::CRedisResult::setEvent(CRedisEvent* event)
{
    m_event = event;
}

hiredis_cpp::CRedisEvent* hiredis_cpp::CRedisResult::getEvent()
{
    return m_event;
}
