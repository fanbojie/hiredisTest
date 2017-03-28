#ifndef __REDISCLIENT_H__
#define __REDISCLIENT_H__

#include <string>

class redisReply;

namespace hiredis_cpp
{
    class CRedisEvent;

    class CRedisClient
    {
    public:
	    CRedisClient();
	    virtual ~CRedisClient();

	    void setPassword(const char* password);
        std::string& getPassword();
        virtual void setAddress(const char* address) = 0;
	    virtual bool open(CRedisEvent* event = NULL) = 0;
	    virtual void close() = 0;
	    virtual bool reopen(CRedisEvent* event = NULL);
	    virtual redisReply* execCmd(const char* cmd);
        //virtual int execCmdAsync(CRedisEvent* event);
        virtual int execCmd(CRedisEvent* event);
    protected:
	    std::string m_address;
	    std::string m_password;
	    int m_port;
    };
}

#endif