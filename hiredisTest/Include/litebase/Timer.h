#ifndef _TIMER_H_
#define _TIMER_H_

#include <map>
#include "OSTypeDefine.h"
#include "Mutex.h"
#include "Thread.h"

namespace litebase
{
    namespace utility
    {
        class CTimerThread: public litebase::details::CThread
        {
        public:
            CTimerThread() {};
            virtual ~CTimerThread() {};
            virtual void run();
        };

        struct InternalTimer
        {
            InternalTimer(): id(0), interval(0), forever(false), callback(NULL), context(NULL), next_time(0) 
            {

            }

            InternalTimer(const InternalTimer& timer)
            {
                this->id = timer.id;
                this->interval = timer.interval;
                this->forever = timer.forever;
                this->callback = timer.callback;
                this->context = timer.context;
                this->next_time = timer.next_time;
            }

            InternalTimer& operator=(const InternalTimer& timer)
            {
                this->id = timer.id;
                this->interval = timer.interval;
                this->forever = timer.forever;
                this->callback = timer.callback;
                this->context = timer.context;
                this->next_time = timer.next_time;
                return *this;
            }

            // 定时器ID，外部维护。
            long id;	
            // 定时间隔（ms），小于0时表示取消定时器。
            int interval;

            // 是否为永久定时器
            bool forever;
            // 到时回调，注意返回值表示下一次定时的间隔，若小于0则取消本定时器。
            // 不能在回调中调用lpi_timer_set；不能在回调中阻塞。
            void (*callback)(long id, int interval, void *context);
            // 回调上下文，外部传入。
            void *context;
            uint64_t next_time;
        };

        class LITEBASE_DECL CTimer
        {
        public:
            CTimer();
            // 注意派生类析构时必须调用cancelTimer取消定时器
            virtual ~CTimer();

            // 初次设置定时器，forever为true表示永久定时器
            int setTimer(long &id, int interval, bool forever=false);
            // 重新设置永久定时器的时间间隔，对非永久定时器无效
            int resetTimer(long id, int interval);
            // 取消定时器
            int cancelTimer(long id);

            // 定时器回调函数，派生类需要重写
            virtual void onTimer(long id) = 0;
        
        };
    }
}

#endif
