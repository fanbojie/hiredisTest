#include "SetTpgwExpireEvent.h"

CSetTpgwExpireEvent::CSetTpgwExpireEvent()
    : m_proxySink(NULL)
{

}

CSetTpgwExpireEvent::~CSetTpgwExpireEvent()
{

}

IRedisProxySink* CSetTpgwExpireEvent::getProxySink()
{
    return m_proxySink;
}

void CSetTpgwExpireEvent::setProxySink(IRedisProxySink* sink)
{
    m_proxySink = sink;
}
