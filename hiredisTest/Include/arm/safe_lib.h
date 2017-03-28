/*------------------------------------------------------------------
 * safe_lib.h -- Use to abstract platform environment 
 *
 * October 2008, Bo Berry
 *
 * Copyright (c) 2008, 2009 Cisco Systems, Inc
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without restriction,
 * including without limitation the rights to use, copy, modify, merge,
 * publish, distribute, sublicense, and/or sell copies of the Software,
 * and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
 * CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
 * TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *------------------------------------------------------------------
 */

#ifndef __SAFE_LIB_H__
#define __SAFE_LIB_H__

/*
 * This is a Safe C Lib internal include file used to abstract the 
 * libraries from the platform environment to ease portability. 
 */
 
/*
 * CONFIGURE: Define a macro for your environment. The library was 
 * initially developed on Mac-OS.
 */ 
/* #define IOS  */

/* #define MAC_OS_X */ 


#if defined(WIN32) || defined(MACOS) || defined(LINUX)||defined(_WIN64) || defined(SOLARIS) || defined(SOLARIS_X86)
#include <stdlib.h>
#include "safe_lib_errno.h"
#include "safe_types.h" 
#elif defined (IOS)
#include "master.h"
#include COMP_INC(posix, inttypes.h)
#include "safe_lib_errno.h"
#include "safe_types.h" 
#else
#error Safe C Library environment not defined.
#endif //defined(WIN32) || defined(MACOS) || defined(LINUX)

#if (defined(WIN32)||defined(_WIN64)) && !defined(__cplusplus)
#define inline __inline
#endif //defined(WIN32) && !defined(__cplusplus)


#endif /* __SAFE_LIB_H__ */
