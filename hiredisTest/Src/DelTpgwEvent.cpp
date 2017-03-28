#include "DelTpgwEvent.h"

CDelTpgwEvent::CDelTpgwEvent()
    : m_proxySink(NULL)
{

}

CDelTpgwEvent::~CDelTpgwEvent()
{

}

IRedisProxySink* CDelTpgwEvent::getProxySink()
{
    return m_proxySink;
}

void CDelTpgwEvent::setProxySink(IRedisProxySink* sink)
{
    m_proxySink = sink;
}
