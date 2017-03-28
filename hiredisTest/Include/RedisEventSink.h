#ifndef __REDISCLIENTSINK_H__
#define __REDISCLIENTSINK_H__

namespace hiredis_cpp
{
    class CRedisResult;

    class IRedisEventSink
    {
    public:
	    IRedisEventSink() {}
	    virtual ~IRedisEventSink() {}
        virtual void callback(CRedisResult* result) = 0;
    };
}

#endif
