#include <string>
#include <iostream>
//#include "redis/hiredis/hiredis.h"
#include "RedisClient.h"
#include "RedisSyncClient.h"
#include "RedisProxyImpl.h"
#include "arm/t120base.h"
#include "arm/t120trace.h"

using namespace std;

int main(int argc, char** argv)
{
	string address = "10.224.203.150:6379";
	string key = "fanbojie_123";
    CRedisProxyImpl::getInstance();
    sleep(3);
	CRedisProxyImpl::getInstance().init(address, "123456");
    /*CRedisProxyImpl::getInstance().setFieldAsync(key, "tpgw", "127.0.0.1:9999");
    int value = CRedisProxyImpl::getInstance().getFieldAsync(key, "tpgw");
    INFOTRACE("tpgw " << value);
    CRedisProxyImpl::getInstance().setExpireAsync(key, 60);*/
   
	//sleep(50);
	//CRedisProxyImpl::getInstance().setExpire(key, 60);

    T120_Timer_Manager::instance()->run();
	//CRedisClient* client = new CRedisSyncClient(address.c_str(), 3000);
	//client->setPassword("123456");
	//bool isOpen = client->open();
	//if (isOpen)
	//{
	//	string cmd = "HGET conference_124 tpgw";
	//	redisReply* reply = client->execCmd(cmd.c_str(), cmd.length());
	//	if (reply->type == REDIS_REPLY_ERROR)
	//	{
	//		cout << "reply error" << reply->str<<endl;
	//		freeReplyObject(reply);
	//		isOpen = client->reopen();
	//	}
	//	else
	//	{
	//		cout << "reply type=" << reply->type << endl;
	//	}
	//}

	//if (isOpen)
	//{
	//	string cmd = "HMSET conference_124 tpgw 10.11.111.11 type 1";
	//	redisReply* reply = client->execCmd(cmd.c_str(), cmd.length());
	//	if (reply->type == REDIS_REPLY_ERROR)
	//	{
	//		cout << "reply error" << reply->str << endl;
	//		freeReplyObject(reply);
	//		isOpen = client->reopen();
	//	}
	//	else
	//	{
	//		cout << "reply type=" << reply->type << endl;
	//	}
	//}
}