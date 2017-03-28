#ifndef LITEBASE_OSTYPEDEFINE_H
#define LITEBASE_OSTYPEDEFINE_H

#ifdef WIN32
#include <Windows.h>
#include <BaseTsd.h>

typedef UINT64  uint64_t;
typedef INT64   int64_t;
typedef UINT32  uint32_t;

#define snprintf _snprintf

typedef struct{
    DWORD   tls_index;
}tls_key_t;

typedef struct{
    unsigned char ran;
    HANDLE  event;
} base_once_t;

#define BASE_ONCE_INIT  {0, NULL}
#else
#include <stdio.h>
#include <pthread.h>
#include <stdint.h>
#include <dlfcn.h>
typedef pthread_key_t   tls_key_t;
typedef pthread_once_t  base_once_t;

#define LoadLibrary(dllname)    dlopen(dllname, RTLD_LAZY)
#define GetProcAddress          dlsym
#define FreeLibrary             dlclose
typedef void* HMODULE;
#define BASE_ONCE_INIT  PTHREAD_ONCE_INIT

#endif

#endif
