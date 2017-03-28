#include "RedisClient.h"

using namespace std;

hiredis_cpp::CRedisClient::CRedisClient()
{

}

hiredis_cpp::CRedisClient::~CRedisClient()
{

}

void hiredis_cpp::CRedisClient::setPassword(const char* password)
{
	this->m_password = password;
}

std::string& hiredis_cpp::CRedisClient::getPassword()
{
    return m_password;
}

redisReply* hiredis_cpp::CRedisClient::execCmd(const char* cmd)
{
    return NULL;
}

int hiredis_cpp::CRedisClient::execCmd(CRedisEvent* event)
{
    return 0;
}

bool hiredis_cpp::CRedisClient::reopen(CRedisEvent* event /*= NULL*/)
{
	close();
	return open(event);
}
