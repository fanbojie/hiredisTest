/*-------------------------------------------------------------------------*/
/*                                                                         */
/*  WebEx utility header file                                              */
/*                                                                         */
/*  T120TRACE.H                                                            */
/*                                                                         */
/*  Copyright (c) 1997-2002 Webex Communications, Inc.                     */
/*  All rights reserved                                                    */
/*                                                                         */
/*                                                                         */
/*                                                                         */
/*-------------------------------------------------------------------------*/

#ifndef __T120TRACE_EXT_H__
#define __T120TRACE_EXT_H__

#include <sys/types.h>
#include <sys/stat.h>
#include <sys/types.h>
#if !defined(WIN32)
#include <unistd.h>
#endif
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <fcntl.h>

#include "t120base.h"
#include "t120trace.h"
#include "wbxconfid.h"
#include "apptokenutil.h"

#ifndef __cplusplus
#error This kind of trace facility can only be used in C++
#endif

T120_Trace::Text_Formator& operator << (T120_Trace::Text_Formator& txtfmt, wbxConfId& confid);

//add for apptoken log function pointer
void apptoken_logger(int level, const char * msg);

#endif  // __T120TRACE_EXT_H__

