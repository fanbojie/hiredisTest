#ifndef __REDISPROXYSINK_H__
#define __REDISPROXYSINK_H__

#include <string>

class IRedisProxySink
{
public:
    IRedisProxySink() {}
    virtual ~IRedisProxySink() {}

    virtual void onGetTpgw(const std::string& key, const std::string& value, int result, void* handle) = 0;
    virtual void onSetTpgw(const std::string& key, int result, void* handle) = 0;
    virtual void onSetTpgwExpire(const std::string& key, int result) = 0;
    virtual void onDelTpgw(const std::string& key, int result) = 0;
};
#endif
