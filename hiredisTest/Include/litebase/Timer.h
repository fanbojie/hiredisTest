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

            // ��ʱ��ID���ⲿά����
            long id;	
            // ��ʱ�����ms����С��0ʱ��ʾȡ����ʱ����
            int interval;

            // �Ƿ�Ϊ���ö�ʱ��
            bool forever;
            // ��ʱ�ص���ע�ⷵ��ֵ��ʾ��һ�ζ�ʱ�ļ������С��0��ȡ������ʱ����
            // �����ڻص��е���lpi_timer_set�������ڻص���������
            void (*callback)(long id, int interval, void *context);
            // �ص������ģ��ⲿ���롣
            void *context;
            uint64_t next_time;
        };

        class LITEBASE_DECL CTimer
        {
        public:
            CTimer();
            // ע������������ʱ�������cancelTimerȡ����ʱ��
            virtual ~CTimer();

            // �������ö�ʱ����foreverΪtrue��ʾ���ö�ʱ��
            int setTimer(long &id, int interval, bool forever=false);
            // �����������ö�ʱ����ʱ�������Է����ö�ʱ����Ч
            int resetTimer(long id, int interval);
            // ȡ����ʱ��
            int cancelTimer(long id);

            // ��ʱ���ص���������������Ҫ��д
            virtual void onTimer(long id) = 0;
        
        };
    }
}

#endif
