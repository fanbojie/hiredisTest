/*-------------------------------------------------------------------------*/
/*                                                                         */
/*  t120poller.h                                                           */
/*                                                                         */
/*  History                                                                */
/*      08/16/2002     created by Jack Feng                                */
/*                     prototype comes from http://www.kegel.com, which    */
/*                     is recomended by Lei Zhu                            */
/*                                                                         */
/*  Copyright (C) 2002 by WebEx Communications Inc.                        */
/*  All rights reserved                                                    */
/*                                                                         */
/*-------------------------------------------------------------------------*/

#ifndef __T120_POLLER_H__
#define __T120_POLLER_H__

#include "platform.h"

#include "t120thread.h"

#ifdef _ENABLE_EPOLL
#define WBX_POLLIN        EPOLLIN
#define WBX_POLLOUT     EPOLLOUT
#define WBX_POLLHUP     EPOLLHUP
#define WBX_POLLERR      EPOLLERR
#define WBX_POLLET        EPOLLET
#define WBX_NOPOLL		0

#include "t120epoller.h"

#else
#define WBX_POLLIN        POLLIN
#define WBX_POLLOUT     POLLOUT
#define WBX_POLLHUP     POLLHUP
#define WBX_POLLERR      POLLERR
#define WBX_POLLET        0x00
#define WBX_NOPOLL		-1
/////////////////////////////////////////////////////////////////////////////
// class diagram
//
class T120_Poller;

class T120_Signal_Mask;

/////////////////////////////////////////////////////////////////////////////
// T120_Poller_Event
//
typedef struct
{
    int     fd;
    int   revents;
    void*   utoken;
} T120_Poller_Event;

////////////////////////////
// T120_Signal_Mask
class T120_Signal_Mask
{
public:
        T120_Signal_Mask();
        virtual ~T120_Signal_Mask();
};

/////////////////////////////////////////////////////////////////////////////
// T120_Poller
//
class T120_Poller
{
public:
    T120_Poller();
    virtual ~T120_Poller();

    virtual int init();
    virtual void shutdown();
    virtual int set_signum(int signum);

    virtual int add(int fd, void* utoken, int eventmask, uint32 id = 0);
    virtual int remove(int fd);

    virtual int set_mask(int fd, int eventmask);
    virtual int or_mask(int fd, int eventmask);
    virtual int and_mask(int fd, int eventmask);

    virtual int handle_events(int timeout_millisec);

    virtual void *find_utoken ( int fd, uint32 id );

    virtual void replace ( int old_fd, int new_fd );

    
protected:
    int wait_for_events(T120_Poller_Event& evt, int timeout_millisec);
    int poll_wait_for_events(T120_Poller_Event& evt, int timeout_millisec);

    struct sigfd
    {
        void*    utoken;
        int    mask;
        int        pfds_index;
        uint32    id;
    };

protected:
    boolean m_bHighVer;
    int signum;
    sigset_t sigset;

    struct sigfd  *sfds;
    struct pollfd *pfds;
    int num_fds_alloc;
    int num_fds_used;
    int num_poll_revts;
    int cur_pfds_index;

    struct sigaction old_sa;
};

#endif
#endif
