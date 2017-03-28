/*-------------------------------------------------------------------------*/
/*                                                                         */
/*  WebEx utility header file                                              */
/*                                                                         */
/*  T120TRACE.H                                                            */
/*                                                                         */
/*  Copyright (c) 1997-2002 Webex Communications, Inc.                     */
/*  All rights reserved                                                    */
/*                                                                         */
/*                                                                         */
/*                                                                         */
/*-------------------------------------------------------------------------*/

/*  
    Trace utility changes for Eureka platform

    1. Trace file can be set to enable or disable a certain type of trace. 
        e.g. disable warning, pdu or function
        The format in webex.cfg is:

        [Trace]       
        XXXX.Error=TRUE;
        XXXX.Warning=FALSE;
        XXXX.Info=FALSE;

        XXXX is the process name to handle. 
        The default value is as in this list: 
            { 0, "Error",      TRUE  },
            { 1, "Server",      TRUE  },
            { 10, "Warning",    TRUE  },
            { 11, "Meeting",    TRUE  },
            { 12, "Session",    TRUE  },
            { 13, "User",    TRUE  },
            { 14, "Statistic",    TRUE  },
            { 20, "Info",       TRUE  },
            { 21, "State",      TRUE  },
            { 22, "PDU",        FALSE },
            { 23, "Func",       FALSE },
            { 24, "Tick",       FALSE },
            { 25, "Detail",     FALSE }

        This setting can be changed at runtime.

    2. Trace file can be set to flush each time a trace is written, or 
        bufferred before written to file in group to reduce overhead. 
        This can be changed at runtime.

        The format in webex.cfg is:

        [Trace]       
        FlushPerLines=1

        or 

        FlushPerLines=200

        Default is 100. This is to reduce the overhead brought by IO operation.

    3. Only 1 file per process. file size can be set in webex.cfg. the 
        default size is 20MB. The file name format is process_name+date.process_id.

        The format in webex.cfg is:

        [Trace]       
        XXXX=100MB

        XXXX is the process name.

    
    4. To allow prcoess realtime refresh trace config through signal, provide 
        an API as follow:
        
        void refersh_trace_config();

        A signal handler should call this function to inform trace module 
        to refresh its config by reading webex.cfg

*/


#ifndef __T120TRACE_H__
#define __T120TRACE_H__

#include <sys/types.h>
#include <sys/stat.h>
#include <sys/types.h>
#if !defined(WIN32)
#include <unistd.h>
#endif
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <fcntl.h>

#include "t120thread.h"

#ifndef __cplusplus
#error This kind of trace facility can only be used in C++
#endif

#include <string>

/////////////////////////////////////////////////////////////////////////////
//
// Macro used in trace module
//

#define EXPORTMODIFIER

#define T120TRACE_MAX_PROCESS                10
#define T120TRACE_MAX_PROCESS_NAME            32
#define T120TRACE_MAX_MODULE                20
#define T120TRACE_MAX_MASK                    32
#define T120TRACE_MAX_TRACE_LEN                8192

#define T120TRACE_MAX_MODULE_NAME            32
#define T120TRACE_MAX_MASK_NAME                32

#define T120TRACE_DEFAULT_FLUSH_FREQ        100
#define T120TRACE_DEFAULT_TRACE_SIZE        20*1024*1024L


#define TRACE_MASK_METRICS    31  //FR29,4/26/2011 log MediaNet trace and other trace
#define TRACE_MASK_RESIP	       32  //T28, 11/24/2011  log resip for tpgw, Elton
  

/////////////////////////////////////////////////////////////////////////////
// base class declare
//
class T120_Critical_Section;

/////////////////////////////////////////////////////////////////////////////
// Trace_File class
//
class LIBUTIL_EXPORT Trace_File
{
public :
    Trace_File(const char* pszFileName, uint32 lMaxSize = 0, boolean bShared = FALSE);
    ~Trace_File();

    boolean is_same_file(const char* pszFileName);
    virtual boolean refresh_settings(uint32 lMaxSize, int nFreq);

    void flush_buffer(boolean bHasEndofTrace=TRUE);

    virtual void write(const char* lpszModule, 
        const char* lpszDescription, 
        const char* lpsz,
        uint32 thread_id,
        struct tm& tmVar,uint32 usec);


    void write_shared(const char* lpszModule, 
        const char* lpszDescription, 
        const char* lpsz,uint32 thread_id,struct tm& tmVar,uint32 usec);
	void set_mask(uint32 mask) { m_dwMask = mask;}
	uint32 get_mask(){ return m_dwMask;}
//    boolean safe_lock();
//    void safe_unlock();
public :
    Trace_File* m_pNext;
    boolean m_bMaxReached;
	
   

protected :
//    T120_Critical_Section m_mutex;
//    boolean m_busy;

    FILE* m_pFile;
    char* m_pFileName;
    uint32 m_lMaxSize;
    int m_nFlushFreq;
    boolean m_bShared;

    int m_nCurrentFileId;
    long m_nCurrentTraceLines;
#if !defined ( WIN32)
    struct flock m_lock;
    struct flock m_unlock;
#endif

    char* m_buffer;
    uint32 m_pos;
    int    m_current_line;
    int m_nMagicNumber;
    int m_pos_limit;
	uint32 m_dwMask;
};

////////////////////////////////////////////////////////////////////////////
// 
// Trace_File_Metrics class
// for metrics log, there is some specific logic differnt to common trace file
// Oliver Zhu, 5/19/2016
//
///////////////////////////////////////////////////////////////////////
class Trace_File_Metrics: public Trace_File
{
public:
	Trace_File_Metrics(const char* pszFileName, uint32 lMaxSize = 0, boolean bShared = FALSE);
	virtual ~Trace_File_Metrics();
	 virtual void write(const char* lpszModule, 
        const char* lpszDescription, 
        const char* lpsz,
        uint32 thread_id,
        struct tm& tmVar,uint32 usec);
	 boolean refresh_settings(uint32 lMaxSize, int nFreq);

};
/////////////////////////////////////////////////////////////////////////////
// Trace_File_Mgr class
//
class LIBUTIL_EXPORT Trace_File_Mgr
{
public :
    Trace_File_Mgr();
    ~Trace_File_Mgr();

public :
    void* open(const char* pszFileName, uint32 lMaxSize = 0, boolean bShared = FALSE,uint32 uMask = 0);
    void close(void* hTrace);
    void write(void* hHandle, const char* lpszModule, 
        const char* lpszDescription, 
        const char* lpsz,uint32 thread_id,struct tm& tmVar,uint32 usec);
    void write_weblog(void* hHandle,const char* lpsz);//oliver,20051208, for web log format trace

    void refresh_settings(uint32 lMaxSize, int nFreq);
    void init_reg_filter();

protected :
    Trace_File* m_pHead;
    int m_cCount;

    T120_Critical_Section m_mutex;
};

/////////////////////////////////////////////////////////////////////////////
// Trace_Map_Entry for macro support
//
//
//  This trace utility supports following trace syntax
//
//  // module trace declaration
//  DECLARE_TRACE_MAP(module)
//  T120TRACE(module, mask, str)
//
//  // module trace definition
//  BEGIN_TRACE_MAP(module)
//      TRACE_MASK(mask, description, enable)
//      TRACE_MASK(mask, description, enable)
//  END_TRACE_MAP(module)
//

struct EXPORTMODIFIER Trace_Map_Entry
{
    uint32   m_dwMask;
    char*  m_lpszMaskDescription;
    boolean    m_bEnable;
};

class LIBUTIL_EXPORT T120_Trace_Helper
{
public:
    static boolean is_trace_enable(uint32 mask);
	static void check_to_enable_metrics_trace();
};

/////////////////////////////////////////////////////////////////////////////
// T120_Trace
// This class is used for supporting the trace macros
//
class LIBUTIL_EXPORT T120_Trace
{
public :
    T120_Trace(char* lpszModule, Trace_Map_Entry mapEntries[],
        char* lpszPrivateInfo = NULL, boolean bShared = FALSE);

    virtual ~T120_Trace();

    boolean load(void * hTrace = NULL);
    void read_config();

    static const char* get_trace_dir();
    const char* get_process_name();

public :
     enum Ordix
    {
        hex     = 0,
        decimal = 1
    };

    // text-based formatting class
    class LIBUTIL_EXPORT Text_Formator
    {
    public :
        Text_Formator(char* lpszBuf, uint32 dwBufSize);
        virtual ~Text_Formator();

    public :
        void reset();
        Text_Formator& operator << (char ch);
        Text_Formator& operator << (uint8 ch);
        Text_Formator& operator << (short s);
        Text_Formator& operator << (uint16 s);
        Text_Formator& operator << (int i);
        Text_Formator& operator << (unsigned int i);
        Text_Formator& operator << (long l);
        Text_Formator& operator << (unsigned long l);
#if (defined(LINUX) || defined(CM_LINUX)) // CM_LINUX is used for MMP library that NBR will used
	Text_Formator& operator << (long long ll);
	Text_Formator& operator << (unsigned long long ll);
#endif
        Text_Formator& operator << (float f);
        Text_Formator& operator << (double d);
        Text_Formator& operator << (char* lpsz);
        Text_Formator& operator << (const char* lpsz);
        Text_Formator& operator << (void* lpv);
        Text_Formator& operator << (Ordix ordix);
        operator char*();

    private :
        void set_hex_flag(boolean bValue);
        boolean get_hex_flag();
        void advance(const char* lpsz);

    private :
        char*  m_lpszBuf;
        uint32  m_dwSize;
        uint32  m_dwPos;

        boolean m_bHex;
    };

public :
    // API methods
    void trace_string(uint32 dwMask, char* lpsz,uint32 thread_id,struct tm& tmVar,uint32 usec);
	void metrics_trace_string( char* lpsz,uint32 thread_id);//FR29,4/26/2011 log MediaNet trace and other trace
	void  resip_trace_string( char * lpsz,uint32 thread_id);    //T28, 11/24/2011  log resip for tpgw, Elton
    void log_string(char* lpsz);
    static T120_Trace* instance();

private :
    static T120_Trace* t120_trace;
    char* m_lpszModule;
    uint32 m_nMapEntries;
    Trace_Map_Entry* m_pMapEntries;

    char* m_lpszPrivateInfo;
    boolean m_bShared;
    boolean m_bEnabled;

    void* m_hTrace;
    void* m_hTraceWarning;
    void* m_hTraceError;
    void* m_hTrace_log;
	void*m_hTrace_metrics_log;//FR29,4/26/2011 log MediaNet trace and other trace
	void * m_hTrace_resip_log;  //T28, 11/24/2011  log resip for tpgw, Elton
    boolean m_bMultiLogs;
    int m_iCurrCount;
    int m_iWarningCount;
    int m_iErrorCount;
	int m_iMetricslogCount;	//FR29,4/26/2011 log MediaNet trace and other trace
	int m_iMetricsLogCountMax;
	int m_iResiplogCount;  //T28, 11/24/2011  log resip for tpgw, Elton
    int m_iCurrInfoDay;
    int m_iCurrInfoMonth;
    int m_processid;
private :
    T120_Critical_Section m_mutex;
    friend class T120_Trace_Helper;
};


class T120_MT_Trace : public T120_Thread
{
    class TraceItem
    {
        public:
            TraceItem(){m_mask = 0;m_thread_id = 0;m_usec = 0; m_len = 0;}
            virtual ~TraceItem(){}
            void WriteTrace();

            std::string m_trace;
            uint32  m_mask;
            uint32 m_thread_id;
			uint32  m_usec;
			struct tm m_tmVar;
			uint32	m_len;
			

    };
public:
    T120_MT_Trace();
    virtual ~T120_MT_Trace();
    void trace_string(uint32 mask,const char* string);
	void metrics_trace_string( char* lpsz);//FR29,4/26/2011 log MediaNet trace and other trace
	void resip_trace_string( char* lpsz);    //T28, 11/24/2011  log resip for tpgw, Elton

    void Start();
    void Stop();
    uint32 thread_run();

    static T120_MT_Trace* instance();

private:
    std::list<TraceItem*> m_traceList[2];
	std::list<TraceItem*>* m_pListIn;
	std::list<TraceItem*>* m_pListThread;
    T120_Critical_Section       m_lock;
};


/////////////////////////////////////////////////////////////////////////////
// Trace macros
//
// This is for use by the following MACROs.



#define T120TRACE(mask, str)                   \
    {                                               \
	if(T120_Trace_Helper::is_trace_enable(mask))	\
	 {\
        char achFormatBuf[T120TRACE_MAX_TRACE_LEN]={0};    \
        T120_Trace::Text_Formator formator(achFormatBuf, T120TRACE_MAX_TRACE_LEN); \
        (T120_MT_Trace::instance())->trace_string(mask, formator << str); \
	}	\
    }

   
#define T120TRACEEX(mask, str)                   \
    {                                               \
        if(T120_Trace_Helper::is_trace_enable(mask))    \
        {    \
            char achFormatBuf[T120TRACE_MAX_TRACE_LEN]={0};    \
            T120_Trace::Text_Formator formator(achFormatBuf, T120TRACE_MAX_TRACE_LEN); \
            (T120_MT_Trace::instance())->trace_string(mask, formator << str); \
        }    \
    }


#define T120_LOG(str)                                 \
    {                                               \
        char achFormatBuf[T120TRACE_MAX_TRACE_LEN]={0};   \
        T120_Trace::Text_Formator formator(achFormatBuf, T120TRACE_MAX_TRACE_LEN); \
        (T120_Trace::instance())->log_string(formator << str);        \
    }


class LIBUTIL_EXPORT func_tracer
{
public :
    func_tracer(char* str)
    {
        buffer = str;
        T120TRACE(23, "Enter " << buffer);
    }

    virtual ~func_tracer()
    {
        T120TRACE(23, "Leave " << buffer);
    }

    char* buffer;
};

class LIBUTIL_EXPORT funcx_tracer
{
public :
    funcx_tracer(char* key, char* str);

    virtual ~funcx_tracer()
    {
        T120TRACE(23, obj_key << ":: "<<"Leave " << obj_key << "::"<<buffer);
    }

    char* buffer;
    char obj_key[64];
};


/////////////////////////////////////////////////////////////////////////////
//
// Public utility function for refreshing trace configuration 
//

void LIBUTIL_EXPORT refresh_trace_config();

/////////////////////////////////////////////////////////////////////////////
//
// Public trace macros for Eureka 
//


#define ERRTRACE(str) T120TRACE(0, str)
#define SERVERTRACE(str) T120TRACE(1, str)
#define WARNINGTRACE(str) T120TRACE(10, str)
#define MEETINGTRACE(str) T120TRACE(11, str)
#define SESSIONTRACE(str) T120TRACE(12, str)
#define USERTRACE(str) T120TRACE(13, str)
#define STATISTICTRACE(str) T120TRACE(14, str)
#define INFOTRACE(str) T120TRACE(20, str)
#define STATETRACE(str) T120TRACE(21, str)
#define PDUTRACE(str) T120TRACE(22, str)
#define FUNCTRACE(str) func_tracer _$FUNCTRACE$(str);
#define TICKTRACE(str) T120TRACE(24, str)
#define DETAILTRACE(str) T120TRACE(25, str)
#define WDMSTRACE(str) T120TRACEEX(26, str)
#define DNYTRACE(mask,str)	T120TRACEEX(mask,str)

#define ERRXTRACE(str) T120TRACE(0, obj_key<<":: "<<str)
#define SERVERXTRACE(str) T120TRACE(1, obj_key<<":: "<<str)
#define WARNINGXTRACE(str) T120TRACE(10, obj_key<<":: "<<str)
#define MEETINGXTRACE(str) T120TRACE(11, obj_key<<":: "<<str)
#define SESSIONXTRACE(str) T120TRACE(12, obj_key<<":: "<<str)
#define USERXTRACE(str) T120TRACE(13, obj_key<<":: "<<str)
#define STATISTICXTRACE(str) T120TRACE(14, obj_key<<":: "<<str)
#define INFOXTRACE(str) T120TRACE(20, obj_key<<":: "<<str)
#define STATEXTRACE(str) T120TRACE(21, obj_key<<":: "<<str)
#define PDUXTRACE(str) T120TRACE(22, obj_key<<":: "<<str)
#define FUNCXTRACE(str) funcx_tracer _$FUNCXTRACE$(obj_key, str);
#define TICKXTRACE(str) T120TRACE(24, obj_key<<":: "<<str)
#define DETAILXTRACE(str) T120TRACE(25, obj_key<<":: "<<str)
#define WDMSXTRACE(str) T120TRACEEX(26, obj_key<<":: "<<str)
#define DNYXTRACE(mask,str) T120TRACEEX(mask, obj_key<<"::"<<str)





//FR29,4/26/2011 log MediaNet trace and other trace
#define ANALYSISTRACE(str)
#define METRICSTRACE(str)                    \
    {                                               \
		if(T120_Trace_Helper::is_trace_enable(TRACE_MASK_METRICS))	\
		{\
			char achFormatBuf[T120TRACE_MAX_TRACE_LEN];    \
			T120_Trace::Text_Formator formator(achFormatBuf, T120TRACE_MAX_TRACE_LEN); \
			(T120_MT_Trace::instance())->metrics_trace_string(formator << str); \
		}\
    }
#define METRICSXTRACE(str)  METRICSTRACE(str);
#define ANALYSISXTRACE(str)	ANALYSISTRACE(obj_key<<":: "<<str);
//end

//T28, 11/24/2011  log resip for tpgw, Elton
#define RESIPTRACE(str)                    \
    {                                               \
		if(T120_Trace_Helper::is_trace_enable(TRACE_MASK_RESIP))	\
		{\
			char achFormatBuf[T120TRACE_MAX_TRACE_LEN];    \
			T120_Trace::Text_Formator formator(achFormatBuf, T120TRACE_MAX_TRACE_LEN); \
			(T120_MT_Trace::instance())->resip_trace_string(formator << str); \
		}\
    }
#define RESIPTRACEXTRACE(str)	RESIPTRACE(obj_key<<":: "<<str);
// resip end


#define ENABLEMETRICS()										\
    {														\
		T120_Trace_Helper::check_to_enable_metrics_trace();	\
    }

extern char g_webex_log_version[200];
extern char g_webex_log_dir[512];


#define T120_ASSERT(x) if(!(x)) T120TRACE(0, "T120 ASSERT " << #x\
    <<" at file " << __FILE__ << ", line " << __LINE__);

#define T120_ASSERTR(x) if(!(x))\
{\
    T120TRACE(0, "T120 ASSERT " << #x\
    <<" at file " << __FILE__ << ", line " << __LINE__);\
    return ;\
}
#define T120_ASSERTR0(x) if(!(x))\
{\
    T120TRACE(0, "T120 ASSERT " << #x\
    <<" at file " << __FILE__ << ", line " << __LINE__);\
    return 0;\
}


#define T120_ASSERTRn(x,n) if(!(x))\
{\
    T120TRACE(0, "T120 ASSERT " << #x\
    <<" at file " << __FILE__ << ", line " << __LINE__);\
    return (n);\
}

#define T120_ASSERTX(x) if(!(x)) \
    { \
        T120TRACE(0, "T120 ASSERTX " << #x\
        <<" at file " << __FILE__ << ", line " << __LINE__);\
        throw 111; \
    }


#define T120_ASSERTXR(x) if(!(x)) \
    { \
        T120TRACE(0, "T120 ASSERTX " << #x\
        <<" at file " << __FILE__ << ", line " << __LINE__);\
        return ; \
    }
#define T120_ASSERTXR0(x) if(!(x)) \
    { \
        T120TRACE(0, "T120 ASSERTX " << #x\
        <<" at file " << __FILE__ << ", line " << __LINE__);\
        return 0; \
    }
#define T120_ASSERTXRn(x,n) if(!(x)) \
    { \
        T120TRACE(0, "T120 ASSERTX " << #x\
        <<" at file " << __FILE__ << ", line " << __LINE__);\
        return (n); \
    }

#endif  // __T120TRACE__


