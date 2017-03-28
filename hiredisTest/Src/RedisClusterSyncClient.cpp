#include "RedisClusterSyncClient.h"
#include "t120trace.h"
#include "safe_str_lib.h"
#include "HiredisHeader.h"

using namespace std;

hiredis_cpp::CRedisClusterSyncClient::CRedisClusterSyncClient(const char* addr, int conn_timeout /*= 0*/)
	: CRedisClient()
	, m_redisCtx(NULL)
	, m_timeout(conn_timeout)
{
    strncpy_s(obj_key, sizeof(obj_key), "CRedisClusterSyncClient", sizeof(obj_key) - 1);
	this->m_address = addr;
}

hiredis_cpp::CRedisClusterSyncClient::~CRedisClusterSyncClient()
{
	close();
}

void hiredis_cpp::CRedisClusterSyncClient::setAddress(const char* address)
{
    this->m_address = address;
}

bool hiredis_cpp::CRedisClusterSyncClient::open(CRedisEvent* event /*= NULL*/)
{
	if (m_timeout > 0)
	{
		struct timeval tv;
		tv.tv_sec = m_timeout / 1000;
		tv.tv_usec = (m_timeout % 1000) * 1000;
		m_redisCtx = redisClusterConnectWithTimeout(m_address.c_str(), tv, HIRCLUSTER_FLAG_NULL);
	}
	else
	{
		m_redisCtx = redisClusterConnect(m_address.c_str(), HIRCLUSTER_FLAG_NULL);
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
		redisReply* reply = static_cast<redisReply*>(redisClusterCommand(m_redisCtx, "AUTH %s", m_password.c_str()));
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

void hiredis_cpp::CRedisClusterSyncClient::close()
{
	if (m_redisCtx != NULL)
	{
		redisClusterFree(m_redisCtx);
		m_redisCtx = NULL;
	}
}

redisReply* hiredis_cpp::CRedisClusterSyncClient::execCmd(const char* cmd)
{
	if (m_redisCtx != NULL)
	{
		return static_cast<redisReply*>(redisClusterCommand(m_redisCtx, cmd));
	}

	return NULL;
}
