#ifndef __REDISEVENT_H__
#define __REDISEVENT_H__

#include <string>

namespace hiredis_cpp
{
    class IRedisEventSink;

    class CRedisEvent
    {
    public:
        CRedisEvent();
        virtual ~CRedisEvent() = 0;

        void setCmd(const std::string& cmd);
        std::string& getCmd();
        void setKey(const std::string& key);
        std::string& getKey();
        void setSink(IRedisEventSink* sink);
        IRedisEventSink* getSink();
        void resetTime();
        time_t getTime();
        void setId(long long id);
        long long getId();
    protected:
        time_t m_time;      // event start time
        long long m_id;
        std::string m_cmd;
        std::string m_key;
        IRedisEventSink* m_sink;
    };
}
#endif
