#ifndef __HIREDISHEADER_H__
#define __HIREDISHEADER_H__

#ifdef __cplusplus
extern "C"
{
    #include "redis/ae.h"
    #include "redis/hiredis-vip/read.h"
    #include "redis/hiredis-vip/async.h"
    #include "redis/hiredis-vip/hiredis.h"
    #include "redis/hiredis-vip/hircluster.h"
    #include "redis/hiredis-vip/adapters/ae.h"
}
#else
#include "redis/ae.h"
#include "redis/hiredis-vip/read.h"
#include "redis/hiredis-vip/async.h"
#include "redis/hiredis-vip/hiredis.h"
#include "redis/hiredis-vip/hircluster.h"
#include "redis/hiredis-vip/adapters/ae.h"

#endif // __cplusplus

#endif
