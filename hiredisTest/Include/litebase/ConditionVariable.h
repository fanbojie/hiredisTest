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

#ifndef LITEBASE_CONDITIONVARIABLE_H
#define LITEBASE_CONDITIONVARIABLE_H

#include "OSAdapter.h"
#include "Macro.h"
#ifdef WIN32
#include <windows.h>
#else
#include <pthread.h>
#include <sys/time.h>
#endif
 
#ifdef WIN32
#define CONVAR_T                    CONDITION_VARIABLE
#define CONATTR_T                   int
#define CONVAR_INIT(c, a)           InitializeConditionVariable(c) 
#define CONVAR_UNINIT(c)
#define CONVAR_WAIT(c, m)           SleepConditionVariableCS(c, m, INFINITE)
#define CONVAR_TIMEWAIT(c, m, t)    SleepConditionVariableCS(c, m, t)
#define CONVAR_WAKE(c)              WakeConditionVariable(c)
#define CONVAR_WAKEALL(c)           WakeAllConditionVariable(c)
#else
#define CONVAR_T            pthread_cond_t
#define CONATTR_T           pthread_condattr_t
#define CONVAR_INIT(c, a)   pthread_condattr_init(a);\
                            pthread_condattr_setclock(a, CLOCK_MONOTONIC);\
                            pthread_cond_init(c, a);
                        
#define CONVAR_UNINIT(c)    pthread_cond_destroy(c)
#define CONVAR_WAIT(c, m)   pthread_cond_wait(c, m)
#define CONVAR_TIMEWAIT(c, m, t)  pthread_cond_timedwait(c, m, t)
#define CONVAR_WAKE(c)  pthread_cond_signal(c)
#define CONVAR_WAKEALL(c) pthread_cond_broadcast(c)
#endif

#include "Config.h"
#include "Noncopyable.h"
#include "Mutex.h"

namespace litebase
{
	namespace details
	{
		class LITEBASE_DECL CConVariable: public litebase::details::CNoncopyable
		{
		public:
			CConVariable()
			{
                CONVAR_INIT(&m_condVar, &m_condAttr);
			}

			~CConVariable()
			{
				CONVAR_UNINIT(&m_condVar);
			}

			int wait(int milliSeconds = -1)
			{
				int ret;
				if (milliSeconds == -1)
				{
					ret = CONVAR_WAIT(&m_condVar, m_mutex.getMutex());
				}
				else
				{
					#ifdef WIN32 
					ret =  CONVAR_TIMEWAIT(&m_condVar, m_mutex.getMutex(), milliSeconds);
					#else
                    uint64_t timeOut = hrTime() + (uint64_t)(milliSeconds*MICROSEC);
                    struct timespec waitTimes;
					waitTimes.tv_sec = timeOut/NANOSEC;
					waitTimes.tv_nsec = timeOut%NANOSEC;
					ret = CONVAR_TIMEWAIT(&m_condVar, m_mutex.getMutex(), &waitTimes);
					#endif
				}

				return ret;
			}

			void notify()
			{
				CONVAR_WAKE(&m_condVar);
			}

			void notifyAll()
			{
				CONVAR_WAKEALL(&m_condVar);
			}

			litebase::details::CMutex& getMutex()
			{
				return m_mutex;
			}

		private:
			CONVAR_T    m_condVar;
            CONATTR_T   m_condAttr;
			litebase::details::CMutex	m_mutex;
		};
	}
}
#endif
