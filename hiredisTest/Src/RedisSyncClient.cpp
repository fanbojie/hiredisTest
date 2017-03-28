#include "RedisSyncClient.h"
#include "stdlib.h"
#include <sys/time.h>
#include "t120trace.h"
#include "safe_str_lib.h"
#include "HiredisHeader.h"

using namespace std;

hiredis_cpp::CRedisSyncClient::CRedisSyncClient(const char* addr, int conn_timeout /*= 0*/)
	: CRedisClient()
	, m_redisCtx(NULL)
	, m_timeout(conn_timeout)
{
    strncpy_s(obj_key, sizeof(obj_key), "CRedisSyncClient", sizeof(obj_key) - 1);
	string addrTmp = addr;
	size_t pos = addrTmp.find_first_of(":");
	this->m_address = addrTmp.substr(0, pos);
	this->m_port = atoi(addrTmp.substr(pos + 1).c_str());
}

hiredis_cpp::CRedisSyncClient::~CRedisSyncClient()
{
	close();
}

void hiredis_cpp::CRedisSyncClient::setAddress(const char* address)
{
    string addrTmp = address;
    size_t pos = addrTmp.find_first_of(":");
    this->m_address = addrTmp.substr(0, pos);
    this->m_port = atoi(addrTmp.substr(pos + 1).c_str());
}

bool hiredis_cpp::CRedisSyncClient::open(CRedisEvent* event /*= NULL*/)
{
	if (m_timeout>0)
	{
		struct timeval tv;
		tv.tv_sec = m_timeout/1000;
		tv.tv_usec = (m_timeout%1000)*1000;
		m_redisCtx = redisConnectWithTimeout(m_address.c_str(), m_port, tv);
	}
	else
	{
		m_redisCtx = redisConnect(m_address.c_str(), m_port);
	}
	
	if (m_redisCtx == NULL || m_redisCtx->err)
	{
		if (m_redisCtx != NULL)
		{
            INFOXTRACE("Error: " << m_redisCtx->errstr);
		}
		else
		{
            INFOXTRACE("Can't allocate redis context");
		}
		return false;
	}

	if (!m_password.empty())
	{
		redisReply* reply = static_cast<redisReply*>(redisCommand(m_redisCtx, "AUTH %s", m_password.c_str()));
		if (reply != NULL && reply->type == REDIS_REPLY_STATUS && string(reply->str, reply->len) == "OK")
		{
            INFOXTRACE("auth success");
			return true;
		}
		else
		{
            INFOXTRACE("auth error ");
			return false;
		}
	}

	return true;
}

void hiredis_cpp::CRedisSyncClient::close()
{
	if (m_redisCtx != NULL)
	{
		redisFree(m_redisCtx);
		m_redisCtx = NULL;
	}
}

redisReply* hiredis_cpp::CRedisSyncClient::execCmd(const char* cmd)
{
	if (m_redisCtx != NULL)
	{
		return static_cast<redisReply*>(redisCommand(m_redisCtx, cmd));
	} 
	
	return NULL;
}
