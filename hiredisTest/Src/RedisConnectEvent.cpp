#include "RedisConnectEvent.h"
#include "RedisDefine.h"
#include "RedisClient.h"

using namespace hiredis_cpp;

hiredis_cpp::CRedisConnectEvent::CRedisConnectEvent()
    : m_client(NULL)
{
}

hiredis_cpp::CRedisConnectEvent::~CRedisConnectEvent()
{

}

void hiredis_cpp::CRedisConnectEvent::setClient(CRedisClient* client)
{
    m_client = client;
}

CRedisClient* hiredis_cpp::CRedisConnectEvent::getClient()
{
    return m_client;
}
