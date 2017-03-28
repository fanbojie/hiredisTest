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

#ifndef LITEBASE_SCOPELOCK_H
#define LITEBASE_SCOPELOCK_H

#include "Config.h"
#include "Mutex.h"

namespace litebase
{
	namespace details
	{
		class LITEBASE_DECL CScopeLock: public litebase::details::CNoncopyable
		{
		public:
			explicit CScopeLock(litebase::details::CMutex& lock)
				: m_lock(lock)
			{
				m_lock.lock();
			}

			~CScopeLock()
			{
				m_lock.unlock();
			}

		private:
			litebase::details::CMutex&	m_lock;
		};
	}
}

#endif
