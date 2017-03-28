#include "RedisUtils.h"
#include <string>
#include "t120trace.h"
#include "HiredisHeader.h"
#include "RedisNullReplyResult.h"
#include "RedisArrayResult.h"
#include "RedisErrorResult.h"
#include "RedisStatusResult.h"
#include "RedisNilResult.h"
#include "RedisIntegerResult.h"
#include "RedisStringResult.h"

using namespace std;

hiredis_cpp::CRedisResult* hiredis_cpp::CRedisUtils::convertRedisReply(redisReply* reply)
{
    if (reply == NULL)
    {
        INFOTRACE("null reply ");
        CRedisNullReplyResult* result = new CRedisNullReplyResult;
        return result;
    }
    
    switch (reply->type)
    {
    case REDIS_REPLY_STATUS:
    {
        CRedisStatusResult* result = new CRedisStatusResult;
        result->setStatus(string(reply->str, reply->len));
        INFOTRACE("status reply, status= " << result->getStatus().c_str());
        return result;
    }
    case REDIS_REPLY_STRING:
    {
        CRedisStringResult* result = new CRedisStringResult;
        result->setString(string(reply->str, reply->len));
        INFOTRACE("string reply, string= " << result->getString().c_str());
        return result;
    }
    case REDIS_REPLY_NIL:
    {
        CRedisNilResult* result = new CRedisNilResult;
        INFOTRACE("nil reply");
        return result;
    }
    case REDIS_REPLY_INTEGER:
    {
        CRedisIntegerResult* result = new CRedisIntegerResult;
        result->setInteger(reply->integer);
        INFOTRACE("integer reply, integer="<<result->getInteger());
        return result;
    }
    case REDIS_REPLY_ERROR:
    {
        CRedisErrorResult* result = new CRedisErrorResult;
        result->setError(string(reply->str, reply->len));
        INFOTRACE("error reply, error=" << result->getError().c_str());
        return result;
    }
    case REDIS_REPLY_ARRAY:
    {
        INFOTRACE("array reply");
        CRedisArrayResult* result = new CRedisArrayResult;
        vector<string>& array = result->getArray();
        for (unsigned i=0; i<reply->elements; i++)
        {
            INFOTRACE("array element="<<reply->element[i]->str);
            array.push_back(reply->element[i]->str);
        }
        return result;
    }
    default:
        INFOTRACE("unsupport reply type " << reply->type);
        break;
    }

    return NULL;
}
