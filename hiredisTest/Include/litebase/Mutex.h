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

#ifndef LITEBASE_MUTEX_H
#define LITEBASE_MUTEX_H

#ifdef WIN32
#include <windows.h>
#define T_MUTEX				    CRITICAL_SECTION
#define MUTEX_ATTR              int
#define MUTEX_INIT(m, attr)     InitializeCriticalSection(m) 
#define MUTEX_UNINIT(m, attr)   DeleteCriticalSection(m)
#define MUTEX_LOCK(m)		    EnterCriticalSection(m)
#define MUTEX_UNLOCK(m)		    LeaveCriticalSection(m)
#define MUTEX_TRYLOCK(m)	    TryEnterCriticalSection(m)
#else
#include <pthread.h>
#define T_MUTEX				    pthread_mutex_t
#define MUTEX_ATTR              pthread_mutexattr_t
#define MUTEX_INIT(m, attr)     pthread_mutexattr_init(attr);\
                                pthread_mutexattr_settype(attr, PTHREAD_MUTEX_RECURSIVE);\
                                pthread_mutex_init(m, attr);

#define MUTEX_UNINIT(m, attr)   pthread_mutex_destroy(m);\
                                pthread_mutexattr_destroy(attr);
#define MUTEX_LOCK(m)		    pthread_mutex_lock(m)
#define MUTEX_UNLOCK(m)		    pthread_mutex_unlock(m)
#define MUTEX_TRYLOCK(m)	    pthread_mutex_trylock(m)
#endif

#include "Config.h"
#include "Noncopyable.h"

namespace litebase
{
	namespace details
	{
		class LITEBASE_DECL CMutex: public litebase::details::CNoncopyable
		{
        public:
			CMutex()
			{
                MUTEX_INIT(&m_mutex, &m_attr);
			}

			~CMutex()
			{
                MUTEX_UNINIT(&m_mutex, &m_attr);
			}

			void lock()
			{
				MUTEX_LOCK(&m_mutex);
			}

			void unlock()
			{
				MUTEX_UNLOCK(&m_mutex);
			}

			int trylock()
			{
				int ret = MUTEX_TRYLOCK(&m_mutex);
				#ifdef WIN32
				// windows下 trylock成功返回非0,不成功返回0,与linux下统一
				return (ret == 0 ? -1 : 0);
				#else
				return ret;
				#endif
			}

			T_MUTEX* getMutex()
			{
				return &m_mutex;
			}

		private:
			T_MUTEX	m_mutex;
			MUTEX_ATTR m_attr;
		};
	}
}

#endif
