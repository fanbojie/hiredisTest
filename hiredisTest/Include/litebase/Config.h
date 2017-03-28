//
//  $Id$
//
//  Copyright (c)1992-2013, ZheJiang Dahua Technology Stock CO.LTD.
//  All Rights Reserved.
//
//    Description:    
//    Revisions:        Year-Month-Day      SVN-Author       Modification
//                        2014-02-14        fan_bojie            Create
//

#ifndef LITEBASE_CONFIG_H
#define LITEBASE_CONFIG_H

#ifdef WIN32

#ifdef  LITEBASE_EXPORT
#define LITEBASE_DECL	__declspec(dllexport)
#elif   defined LITEBASE_IMPORT
#define LITEBASE_DECL	__declspec(dllimport)
#else
#define LITEBASE_DECL
#endif

#define LOCALTIME_S(t, s) localtime_s(s, t);
#else
#define LOCALTIME_S(t, s) localtime_r(t, s);
#endif

#ifndef LITEBASE_DECL
#define LITEBASE_DECL
#endif

#endif
