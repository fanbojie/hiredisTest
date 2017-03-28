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

#ifndef __T120_EPOLLER_H__
#define __T120_EPOLLER_H__

#include <sys/epoll.h>
#include "platform.h"
#include "t120thread.h"

/////////////////////////////////////////////////////////////////////////////
// T120_Poller_Event
//
typedef struct
{
    int     fd;
    int   revents;
    void*   utoken;
} T120_Poller_Event;

/////////////////////////////////////////////////////////////////////////////
// class diagram
//
class T120_Poller;


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

    virtual int add(int fd, void* utoken, int eventmask, uint32 id = 0);
    virtual int remove(int fd);

    virtual int set_mask(int fd, int eventmask);
    virtual int or_mask(int fd, int eventmask);
    virtual int and_mask(int fd, int eventmask);

    virtual int handle_events(int timeout_millisec);

    virtual void *find_utoken ( int fd, uint32 id );

    virtual void replace ( int old_fd, int new_fd );

    
protected:

     struct EventHandler
    {
        void*    utoken;
        int    mask;
        uint32    id;
    };

protected:
    int m_nEpollHandle;
    struct EventHandler  *m_pEventRepository;
    struct epoll_event *m_pEpollEvents;
    int m_nMaxHandleNum;
};

#endif
