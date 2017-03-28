#ifndef __REDISDEFINE_H__
#define __REDISDEFINE_H__

namespace hiredis_cpp
{

    namespace client_type
    {
        enum
        {
            SYNC_CLIENT,
            ASYNC_CLIENT,
            SYNC_CLUSTER,
            ASYNC_CLUSTER,
        };
    }
}
#endif
