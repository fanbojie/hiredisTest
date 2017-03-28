/*-------------------------------------------------------------------------*/
/*                                                                         */
/*  t120thread.h                                                           */
/*                                                                         */
/*  History                                                                */
/*      08/16/2002     created by Jack Feng                                */
/*                                                                         */
/*  Copyright (C) 2002 by WebEx Communications Inc.                        */
/*  All rights reserved                                                    */
/*                                                                         */
/*-------------------------------------------------------------------------*/

#ifndef __T120THREAD_H__
#define __T120THREAD_H__

#include "t120defs.h"

#ifdef UNIX
	#include <pthread.h>
#ifndef INFINITE
#define INFINITE (uint32) -1 
#endif

#endif

/////////////////////////////////////////////////////////////////////////////
// class diagram
//
class T120_Critical_Section;
class T120_Lock;
class T120_Event;
class T120_Thread;

/////////////////////////////////////////////////////////////////////////////
// T120_Critical_Section
//
class LIBUTIL_EXPORT T120_Critical_Section
{
public :
    T120_Critical_Section();
    virtual ~T120_Critical_Section();

    virtual void lock();
    virtual void unlock();
    virtual boolean trylock();

protected :
#if defined(WIN32)
    CRITICAL_SECTION cs;
#endif

#if defined(UNIX)
    pthread_mutex_t mutex;
#endif
};

#define T120_Critical_SectionEx T120_Critical_Section

/////////////////////////////////////////////////////////////////////////////
// T120_Lock
//
class LIBUTIL_EXPORT T120_Lock
{
public :
    T120_Lock(T120_Critical_Section &cs);
    virtual ~T120_Lock();

protected :
    T120_Critical_Section& cs_reference;
};

/////////////////////////////////////////////////////////////////////////////
// T120_Event
//
class LIBUTIL_EXPORT T120_Event
{
public :
    T120_Event();
    virtual ~T120_Event();

public :
    boolean create();
    void set_event();
    void reset_event();

    boolean wait(uint32 time_out = INFINITE);

protected :
#ifdef WIN32
    HANDLE event_handle;
#endif

#ifdef UNIX
    pthread_mutex_t cv_mutex;
    pthread_cond_t  cv;
	int flag;
#endif
};

/////////////////////////////////////////////////////////////////////////////
// T120_Thread
//
#ifdef WIN32
#define THREAD_HANDLE HANDLE
#endif

#ifdef UNIX
#define THREAD_HANDLE pthread_t
#endif

class LIBUTIL_EXPORT T120_Thread
{
public :
    T120_Thread();
    virtual ~T120_Thread();

public :
    boolean create();
    boolean stop(uint32 time_out = INFINITE);
    boolean is_self_thread();

    THREAD_HANDLE get_thread_handle();
	uint32 get_thread_id();

public :
    virtual uint32 thread_run() = 0;

#ifdef WIN32
    static uint32 WINAPI thread_proc(void* param);
#endif

#ifdef UNIX
    static void* thread_proc(void* param);
    static void thread_cleanup_proc(void* param);
#endif

protected :
    THREAD_HANDLE        m_thread_handle;
	boolean              m_stop_flag;
	T120_Event           m_stop_event;

#ifdef WIN32
    uint32               m_thread_id;
#endif
};

#ifdef WIN32
/////////////////////////////////////////////////////////////////////////////
// WIN32 security utility function
//
#define DECLARE_SA(sa)      \
    SECURITY_ATTRIBUTES sa; \
    char pSD_##sa[SECURITY_DESCRIPTOR_MIN_LENGTH];  \
	sa.nLength = sizeof(sa);                        \
	sa.lpSecurityDescriptor = (PSECURITY_DESCRIPTOR)pSD_##sa; \
	sa.bInheritHandle = TRUE

boolean initialize_sa(SECURITY_ATTRIBUTES& sa);
#endif

#endif //__T120THREAD_H__
