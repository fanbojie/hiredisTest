/*------------------------------------------------------------------------*/
/*                                                                        */
/*  T120 implementation                                                   */
/*  T120BASE.H                                                            */
/*                                                                        */
/*  t120 base definitions                                                 */
/*                                                                        */
/*  Copyright (C) 2001 by WebEx Communications Inc.                       */
/*  All rights reserved                                                   */
/*                                                                        */
/*------------------------------------------------------------------------*/

#ifndef __T120BASE_H__
#define __T120BASE_H__

#include "platform.h"
#include "t120defs.h"
#include "t120bs.h"
#include "idatapkt.h"
#include "safe_mem_lib.h"
#include "safe_str_lib.h"

#include "t120utility.h"
#include "t120thread.h"
#include "t120trace_ext.h"
#include "pwd.h"
#include "grp.h"
#ifndef WIN32
#include "t120poller.h"
#include "t120socket.h"
#endif

#include <errno.h>

#ifndef __cplusplus
#error This basic t120 facility can only be used in C++
#endif

#ifdef min
#define __has_defined_min__
#undef min
#endif
#ifdef max
#define __has_defined_max__
#undef max
#endif

#include <string>
#include <vector>
using namespace std;

#ifdef __has_defined_min__ 
#undef __has_defined_min__
#define min(a,b) ((a) > (b)?(b):(a))
#endif
#ifdef __has_defined_max__ 
#undef __has_defined_max__
#define max(a,b) ((a) < (b)?(b):(a))
#endif

#define MAX_STR_LEN 0xffff

/////////////////////////////////////////////////////////////////////////////
// Utility classes diagram
// Classes with _MT_ included in its name means this class' interface is 
// multi thread protecrted.
//
class T120_Object;
class T120_MT_Object;
class T120_Timer_Object;
class T120_MT_Timer_Object;
class T120_Data_Packet;
class T120_MT_Data_Packet;

class T120_Timer_Manager;

//////////////////////////////////////////////////////////////////////////////
// T120_Object
//
class LIBUTIL_EXPORT T120_Object
{
public :
    T120_Object();
    virtual ~T120_Object();

    virtual void add_reference();
    virtual void release_reference();
    virtual void assert_valid();
    virtual bool is_valid();
    void set_obj_key(char* obj_key);
    char* get_obj_key();
    char obj_key[256];

    uint16 magic;
    //weixntmp protected :
    public:    
    //uint16 ref_cnt;
    uint32 ref_cnt;//20060113, oliver, for fix bug#191374, cb crash for ref cnt overflows
};

//////////////////////////////////////////////////////////////////////////////
// T120_MT_Object
//
class LIBUTIL_EXPORT T120_MT_Object : public T120_Object
{
public :
    T120_MT_Object();
    virtual ~T120_MT_Object();

    virtual void add_reference();
    virtual void release_reference();

protected :
    T120_Critical_Section ref_cs;
};

class LIBUTIL_EXPORT T120_REF_Object
{
	public :
	    explicit T120_REF_Object(T120_Object* ptr_obj = NULL);
	    virtual ~T120_REF_Object();

	private:
		T120_REF_Object();
		T120_REF_Object(const T120_REF_Object&);

	protected :
	    T120_Object *m_obj;	
};

//////////////////////////////////////////////////////////////////////////////
// T120_Timer_Object
//
class LIBUTIL_EXPORT T120_Timer_Object : public T120_Object
{
    friend class T120_Timer_Manager;

public :
    T120_Timer_Object();
    virtual ~T120_Timer_Object();

    virtual void on_timer() {}
    virtual boolean schedule(uint32 time_elapse);
    virtual void schedule_cancel();

    bool    is_long_elapse();
protected :
    T120_Timer_Manager* timer_mgr;
    uint32 time_elapse;
    uint32 time_start;
    int32  schedule_index;
    bool   long_elapse;
};


//////////////////////////////////////////////////////////////////////////////
// T120_MT_Timer_Object
//
class LIBUTIL_EXPORT T120_MT_Timer_Object : public T120_Timer_Object
{
public :
    T120_MT_Timer_Object();
    virtual ~T120_MT_Timer_Object();

    virtual void add_reference();
    virtual void release_reference();

protected :
    T120_Critical_Section ref_cs;
};

#define T120_DATA_PACKET_MIN_SIZE 32
/////////////////////////////////////////////////////////////////////////////
// T120_Data_Packet
//
class LIBUTIL_EXPORT T120_Data_Packet : public T120_Object, public ITP_Data_Packet
{
public :
    T120_Data_Packet();
    virtual ~T120_Data_Packet();

    virtual uint8* get_packet_buffer() {return this->raw_data;}
    virtual uint32 get_packet_offset() {return this->offset;}
    virtual void set_packet_offset(uint32 offset) {this->offset = offset;}
    virtual uint32 get_packet_length() {return this->length;}
    virtual void set_packet_length(uint32 length) {this->length = length;}
    virtual uint32 get_raw_length() {return this->raw_length;}
    virtual void set_raw_length(uint32 raw_length) {this->raw_length = raw_length;}

    virtual uint8* alloc_buffer(uint32 raw_length);
    virtual uint8* alloc_buffer();

    virtual void release_buffer();
    virtual void attach_buffer(uint8* raw_data, uint32 raw_length);
    virtual void detach_buffer(uint8* &raw_data, uint32 &raw_length);

    virtual void add_reference();
    virtual void release_reference();

protected :
    T120_Critical_Section ref_cs;

    uint8* raw_data;
    uint32 raw_length;
    uint32 offset;
    uint32 length;

private:
    bool   cache_used;
    uint8  cache[T120_DATA_PACKET_MIN_SIZE + 1];

};

/////////////////////////////////////////////////////////////////////////////
// T120_MT_Data_Packet
//
class LIBUTIL_EXPORT T120_MT_Data_Packet : public T120_Data_Packet
{
public :
    T120_MT_Data_Packet();
    virtual ~T120_MT_Data_Packet();

    virtual void add_reference();
    virtual void release_reference();
};

/////////////////////////////////////////////////////////////////////////////
// T120_Timer_Manager
//
class LIBUTIL_EXPORT T120_Timer_Manager
{
public :
    T120_Timer_Manager();
    virtual ~T120_Timer_Manager();

    static T120_Timer_Manager* instance();
    static void set_max_size(int32 size);
    void cleanup();
    boolean is_corrupted();

    boolean master_timer_is_idle();
    boolean master_timer_obj_set(T120_Timer_Object* timer_obj);
    void master_timer_obj_remove(T120_Timer_Object* timer_obj);
    void master_timer_obj_signal();

    boolean schedule(T120_Timer_Object* schedule_obj, uint32 time_elapse);
    void schedule_cancel(T120_Timer_Object* schedule_obj);
    void grow();

    static void set_exit_flag();
    void on_idle();
    void run();

protected :
    uint32 magic;
    T120_Timer_Object** scheduled_obj_list; 
    T120_Critical_Section cs;
    static T120_Critical_Section cs_time_mgr;
    static T120_Timer_Manager* timer_mgr;
    static int32 max_size;

    static boolean exit_flag;
    int32  cur_index;
    int32  begin_index;
    int32  end_index;

    uint32 last_tick_cnt;
    T120_Event waiting_evt;
    T120_Timer_Object* master_timer_obj; 
    bool   timer_idle;
};

#endif // __T120BASE_H__
