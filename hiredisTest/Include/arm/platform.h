/*--------------------------------------------------------------------------*/
/*                                                                          */
/*  PLATFORM.H                                                              */
/*                                                                          */
/*  Copyright (C) 2001 by WebEx Communications Inc.                         */
/*  All rights reserved                                                     */
/*                                                                          */
/* Introduction:                                                            */
/* This file defined all the platform dependent primitive types.            */
/*                                                                          */
/*--------------------------------------------------------------------------*/

// This file shall not contain any class definitions

#if !defined(__PLATFORM_H__)
#define __PLATFORM_H__

#if defined (WIN32) || defined (WINNT) || defined (WIN95)
	
	#define DLLEXPORT __declspec(dllexport)

#elif defined (WIN31)
    #include "windows.h"
	#define DLLEXPORT WINAPI __export

#elif defined(__MWERKS__) 
// detect macintosh compiler and set flag for
// building mac version
#ifndef MACOS
	#define MACOS
#endif
#endif

#if defined (WIN32) || defined (WINNT) || defined (WIN95)
    #define DLLEXPORT __declspec(dllexport)
#if _MSC_VER > 1200
	#define _WINSOCKAPI_	// Prevent inclusion of winsock.h in windows.h
#endif
    #include <windows.h>
#if _MSC_VER > 1200
	#include <WinSock2.h>
#endif
    #if defined(_DEBUG)
        #include <assert.h>
    #elif !defined(assert)
        #define assert(x)
    #endif

#elif defined (WIN31)
    #include <windows.h>
    #define DLLEXPORT WINAPI __export

#elif defined(LINUX) || defined(UNIX)
	#include <stdio.h>
	#include <stdlib.h>
	#include <string.h>
	#include <unistd.h>
	#include <errno.h>
	#include <limits.h>
	#include <signal.h>
    #include <sys/poll.h>
    #include <sys/types.h>
	#include <sys/stat.h>
	#include <fcntl.h>
    #include <pthread.h>
	#include <netdb.h>
	#include <arpa/inet.h>
    #define _assert(x)

#elif defined(__MWERKS__) 
#ifndef MACOS
    #define MACOS
#endif
#endif

#ifndef WIN32
#include <list>
#include <map>
using namespace std;
#endif

//
// basic primitive data types:
//   int8, uint8, int16, uint16, int32, uint32, float32, float64
//   char, string, boolean, time
//
#if !defined(int8)
#if  defined (AIX)
typedef signed char int8;
#else
typedef char int8;
#endif
#endif

#if !defined(uint8)
typedef unsigned char uint8;
#endif

#if !defined(int16)
typedef short int16;
#endif

#if !defined(uint16)
typedef unsigned short uint16;
#endif

#if !defined(int32)
#if  defined (AIX)
typedef int int32;
#else
#ifdef __64BITS_COMPATIBLE__ 
typedef signed int int32;
#else
typedef long int32;
#endif
#endif
#endif

#if !defined(uint32)
#ifdef __64BITS_COMPATIBLE__ 
typedef unsigned int uint32;
#else
typedef unsigned long uint32;
#endif
#endif

#if !defined(float32)
typedef float float32;
#endif

#if !defined(float64)
typedef double float64;
#endif

//<= Andrew+-, 1/20/2006 11:8:3
// modify for unix team, in their code boolean is defined as int
#ifndef NOT_USE_BOOLEAN 

#if !defined(WMSWC)
#if !defined(boolean)
typedef uint8 boolean;
#endif
#endif // !defined(WMSWC)

#if !defined(TRUE)
#define TRUE ((boolean)1)
#endif

#if !defined(FALSE)
#define FALSE ((boolean)0)
#endif

#endif //NOT_USE_BOOLEAN

#if !defined(NULL)
#define NULL ((int32)0)
#endif

#endif //__PLATFORM_H__
