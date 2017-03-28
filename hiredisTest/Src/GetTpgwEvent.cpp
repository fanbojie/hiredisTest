#include "GetTpgwEvent.h"

CGetTpgwEvent::CGetTpgwEvent()
    : m_handle(NULL)
{

}

CGetTpgwEvent::~CGetTpgwEvent()
{

}

void CGetTpgwEvent::setHandle(void* handle)
{
    m_handle = handle;
}

void* CGetTpgwEvent::getHandle()
{
    return m_handle;
}

IRedisProxySink* CGetTpgwEvent::getProxySink()
{
    return m_proxySink;
}

void CGetTpgwEvent::setProxySink(IRedisProxySink* sink)
{
    m_proxySink = sink;
}
