#include "SetTpgwEvent.h"

CSetTpgwEvent::CSetTpgwEvent()
    : m_handle(NULL)
    , m_proxySink(NULL)
{

}

CSetTpgwEvent::~CSetTpgwEvent()
{

}

void CSetTpgwEvent::setHandle(void* handle)
{
    m_handle = handle;
}

void* CSetTpgwEvent::getHandle()
{
    return m_handle;
}

IRedisProxySink* CSetTpgwEvent::getProxySink()
{
    return m_proxySink;
}

void CSetTpgwEvent::setProxySink(IRedisProxySink* sink)
{
    m_proxySink = sink;
}
