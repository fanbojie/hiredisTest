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

#ifndef LITEBASE_THREAD_H
#define LITEBASE_THREAD_H

#include "Config.h"
#include "Noncopyable.h"

#ifdef WIN32
#include <process.h>
#define THREADPROC_RET unsigned _stdcall 
#define THREAD_T    unsigned
#else
#include <pthread.h>
#define THREADPROC_RET void *
#define THREAD_T    pthread_t
#endif 

namespace litebase
{
	namespace details
	{
		class LITEBASE_DECL CThread: public litebase::details::CNoncopyable
		{
		public:
			CThread();
			virtual ~CThread();
			void start();
			void stop();
			void resume();
			
			THREAD_T getId() { return m_tid; }
            bool isRunning()
            {
                return m_running;
            }

		private:
            virtual void run() = 0;
			static THREADPROC_RET threadProc(void *);

        protected:
            bool    m_stopFlag;
            bool    m_running;
			THREAD_T m_tid;
		};
	}
}
#endif
