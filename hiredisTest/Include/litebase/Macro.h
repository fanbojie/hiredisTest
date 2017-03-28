//
//  $Id$
//
//  Copyright (c)1992-2013, ZheJiang Dahua Technology Stock CO.LTD.
//  All Rights Reserved.
//
//    Description:    
//    Revisions:        Year-Month-Day      SVN-Author       Modification
//                        2014-03-27        fan_bojie            Create
//

#ifndef LITEBASE_MACRO_H
#define LITEBASE_MACRO_H

#define NANOSEC     ((uint64_t)1e9)
#define MICROSEC    ((uint64_t)1e6)

#define DELETE_PTR(ptr)\
    delete ptr;\
    ptr = NULL;

#define  SAFE_COPY_PTR(str, ptr)\
    do                          \
    {                           \
        if (ptr != NULL)        \
        {                       \
            str = ptr;          \
        }                       \
    } while (0);
#endif
