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

#ifndef LITEBASE_TIMEMEASURE_H
#define LITEBASE_TIMEMEASURE_H

#include <stdio.h>
#include <stdarg.h>
#include <limits.h>
#include "Config.h"
#include "Noncopyable.h"
#include "Trace.h"

#ifdef WIN32
#include <windows.h>
#else
#include <unistd.h>
#include <sys/times.h>
#endif

namespace litebase
{
    namespace details
    {
        class LITEBASE_DECL CTimeMeasure: public litebase::details::CNoncopyable
        {
        public:
            CTimeMeasure()
                : m_start(getRelativeTime())
                , m_threshold(INT_MAX)
            {
                m_start = getRelativeTime();             
            }

            ~CTimeMeasure() 
            {
                int cost = getCostTime();
                if (cost>=m_threshold)
                {
                    m_desc.append(", cost=%d");
                    TRACE_WARNING(m_desc.c_str(), cost);
                }
            }

            void formatPrint(int threshold, const char *fmt,  ...)
            {
                m_threshold = threshold;
                char buf[300] = {0};
                va_list argp;
                va_start(argp, fmt);
                vsnprintf (buf, sizeof(buf)-1, fmt, argp);
                va_end(argp);
                m_desc = buf;
            }


            static int getRelativeTime()
            {
                #ifdef WIN32
                return (int)GetTickCount();
                #else
                struct tms buf;
                return (int)((long long)times(&buf) * 1000 / sysconf(_SC_CLK_TCK));
                #endif
            }

        private:
            unsigned long getCostTime()
            {
                return getRelativeTime() - m_start;
            }

        private:
            std::string     m_desc;
            unsigned long   m_start;
            int             m_threshold;
        };
    }
}
#endif
