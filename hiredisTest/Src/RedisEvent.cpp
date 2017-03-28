#include "RedisEvent.h"
#include <time.h>

using namespace std;
using namespace hiredis_cpp;

hiredis_cpp::CRedisEvent::CRedisEvent()
    : m_sink(NULL)
    , m_id(-1)
{
    //  maybe use relative times
    //   struct tms buf;
    // m_time =  (int)((long long)times(&buf) * 1000 / sysconf(_SC_CLK_TCK));
    m_time = time(NULL);
}

hiredis_cpp::CRedisEvent::~CRedisEvent()
{

}

void hiredis_cpp::CRedisEvent::setCmd(const std::string& cmd)
{
    m_cmd = cmd;
}

std::string& hiredis_cpp::CRedisEvent::getCmd()
{
    return m_cmd;
}

void hiredis_cpp::CRedisEvent::setKey(const std::string& key)
{
    m_key = key;
}

std::string& hiredis_cpp::CRedisEvent::getKey()
{
    return m_key;
}

void hiredis_cpp::CRedisEvent::setSink(IRedisEventSink* sink)
{
    m_sink = sink;
}

IRedisEventSink* hiredis_cpp::CRedisEvent::getSink()
{
    return m_sink;
}

void hiredis_cpp::CRedisEvent::resetTime()
{
    m_time = time(NULL);
}

time_t hiredis_cpp::CRedisEvent::getTime()
{
    return m_time;
}

void hiredis_cpp::CRedisEvent::setId(long long id)
{
    m_id = id;
}

long long hiredis_cpp::CRedisEvent::getId()
{
    return m_id;
}

