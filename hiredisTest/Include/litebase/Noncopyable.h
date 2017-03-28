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

#ifndef LITEBASE_NONCOPYABLE_H
#define LITEBASE_NONCOPYABLE_H

#include "Config.h"

namespace litebase
{
	namespace details
	{
		class LITEBASE_DECL CNoncopyable
		{
		protected:
			CNoncopyable(){}
			~CNoncopyable(){}
		private:
			CNoncopyable(const CNoncopyable&);
			CNoncopyable& operator=(const CNoncopyable&);
		};
	}
}
#endif
