//
//  $Id$
//
//  Copyright (c)1992-2013, ZheJiang Dahua Technology Stock CO.LTD.
//  All Rights Reserved.
//
//    Description:    
//    Revisions:        Year-Month-Day      SVN-Author       Modification
//                        2013-02-14        fan_bojie            Create
//

#ifndef LITEBASE_SINGLETON_H
#define LITEBASE_SINGLETON_H

#include "Config.h"
#include "Noncopyable.h"

namespace litebase
{
    namespace details
    {
        template<typename T>
        class LITEBASE_DECL CSingleton: public litebase::details::CNoncopyable
        {
        protected:
            CSingleton(){}
        public:
            ~CSingleton(){}
            static T& getInstance()
            {
                static T instance;
                return instance;
            }
        };
    }
}

#endif
