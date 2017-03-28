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

#ifndef LITEBASE_RWLOCK_H
#define LITEBASE_RWLOCK_H

#include "Noncopyable.h"

#ifdef WIN32
#include <windows.h>
#define	T_RWLOCK				SRWLock
#define RWLOCK_INIT(m, a)	    InitializeSRWLock(m)
#define RWLOCK_UNINIT(m)	    
#define RWLOCK_RDLOCK(m)	    AcquireSRWLockShared(m)
#define RWLOCK_WRLOCK(m)	    AcquireSRWExclusive(m)
#define RWLOCK_UNLOCKRDLOCK(m)	ReleaseSRWLockShared(m)
#define RWLOCK_UNLOCKWRLOCK(m)	ReleaseSRWLockExclusive(m)
#else
#include <pthread.h>
#define	T_RWLOCK			    pthread_rwlock_t		
#define RWLOCK_INIT(m, a)	    pthread_rwlock_init(m, a)
#define RWLOCK_UNINIT(m)	    pthread_rwlock_destroy(m)
#define RWLOCK_RDLOCK(m)	    pthread_rwlock_rdlock(m)
#define RWLOCK_WRLOCK(m)	    pthread_rwlock_wrlock(m)
#define RWLOCK_UNLOCKRDLOCK(m)	pthread_rwlock_unlock(m)
#define RWLOCK_UNLOCKWRLOCK(m)	pthread_rwlock_unlock(m)
#endif

namespace litebase
{
    namespace details
    {
        // 需要支持windows版本
        class LITEBASE_DECL CRWLock: public litebase::details::CNoncopyable
        {
        public:
            CRWLock()
            {
                RWLOCK_INIT(&m_lock, NULL);
            }

            ~CRWLock()
            {
                RWLOCK_UNINIT(&m_lock);
            }

            void rdLock()
            {
                RWLOCK_RDLOCK(&m_lock);
            }

            void wrLock()
            {
                RWLOCK_WRLOCK(&m_lock);
            }

            void rdUnlock()
            {
                RWLOCK_UNLOCKRDLOCK(&m_lock);
            }

            void wrUnlock()
            {
                RWLOCK_UNLOCKWRLOCK(&m_lock);
            }

        private:
            T_RWLOCK        m_lock;
        };

        class LITEBASE_DECL CRScopeLock: public litebase::details::CNoncopyable
        {
        public:
            explicit CRScopeLock(litebase::details::CRWLock& rwlock)
                : m_rwlock(rwlock)
            {
                m_rwlock.rdLock();
            }

            ~CRScopeLock()
            {
                m_rwlock.rdUnlock();
            }

        private:
            litebase::details::CRWLock& m_rwlock;
        };

        class LITEBASE_DECL CWScopeLock: public litebase::details::CNoncopyable
        {
        public:
            explicit CWScopeLock(litebase::details::CRWLock& rwlock)
                : m_rwlock(rwlock)
            {
                m_rwlock.wrLock();
            }

            ~CWScopeLock()
            {
                m_rwlock.wrUnlock();
            }

        private:
            litebase::details::CRWLock& m_rwlock;
        };
    }
}
#endif
