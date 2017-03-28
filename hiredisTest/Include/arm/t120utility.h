/*------------------------------------------------------------------------*/
/*                                                                        */
/*  T120 implementation                                                   */
/*  t120ulitity.h                                                         */
/*                                                                        */
/*  t120 base definitions                                                 */
/*                                                                        */
/*  Copyright (C) 2001 by WebEx Communications Inc.                       */
/*  All rights reserved                                                   */
/*                                                                        */
/*------------------------------------------------------------------------*/

#ifndef __T120UTILITY_H__
#define __T120UTILITY_H__

#include "t120defs.h"
#include "safe_mem_lib.h"
#include "safe_str_lib.h"

#include "t120thread.h"

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
//utility functions
//
extern "C"
{
    LIBUTIL_EXPORT void xbase64_init_decode_table();
    LIBUTIL_EXPORT uint32 xbase64_calc_encode_buf_size(uint8* data, uint32 len);
    LIBUTIL_EXPORT uint32 xbase64_calc_decode_buf_size(uint32 len);
    LIBUTIL_EXPORT uint32 xbase64_encode(uint8* data, uint32 data_len, 
        uint8* buf, uint32 buf_len);
    LIBUTIL_EXPORT uint32 xbase64_decode(uint8* buf, uint32 buf_len, 
        uint8* data, uint32 data_len);
    LIBUTIL_EXPORT uint32 xbase64_n_url_decode(uint8* buf, uint32 buf_len, 
                      uint8* data, uint32);        
    LIBUTIL_EXPORT uint32 calculate_tick_interval(uint32 start, uint32 end);
    LIBUTIL_EXPORT uint32 calculate_tick_delta(uint32 start, uint32 end);
	LIBUTIL_EXPORT int32 URLEncode(char *pOURL,int32 iOLen,char *pURL,int32 iLen);
    #ifdef WIN32
        #define get_tick_count GetTickCount
        #define output_debug_string OutputDebugString
    #else
        uint32 get_tick_count();
	    uint64 GetCurrentGMTime(void);
        void output_debug_string(char* str);
    #endif

    LIBUTIL_EXPORT void init_config(const char* cur_env);
    LIBUTIL_EXPORT boolean get_string_param(char* group, char* item_key, char* item_value, uint32 len);
    LIBUTIL_EXPORT boolean get_string_param_ForDBUserAndPWD(char* group, char* item_key, char* item_value, uint32 len);
	LIBUTIL_EXPORT int get_int_param(char* group, char* item_key);
    LIBUTIL_EXPORT uint16 get_uint16_param(char* group, char* item_key);
    LIBUTIL_EXPORT uint32 get_uint32_param(char* group, char* item_key);
    LIBUTIL_EXPORT boolean get_bool_param(char* group, char* item_key, boolean default_value);
    LIBUTIL_EXPORT void set_webex_home_env(char* home_env);
    LIBUTIL_EXPORT char* get_webex_home_dir();
    LIBUTIL_EXPORT void set_def_webex_home_dir(char* home_dir);//oliver, 10122006
    LIBUTIL_EXPORT const char* get_process_name();
    LIBUTIL_EXPORT const char* get_process_start_cmd();
    LIBUTIL_EXPORT const char* get_process_stop_cmd(const char* process_name);
    LIBUTIL_EXPORT const char* get_exec_name(void);
	LIBUTIL_EXPORT boolean ChangeAppOwner();
	LIBUTIL_EXPORT boolean ChangeFileOwner(const char* path);

    //for eureka 3.6.3, multi-instance, kelvin 2007-7-16
    LIBUTIL_EXPORT int32 get_instance_num();

    LIBUTIL_EXPORT boolean transport_address_parse(char* transport_address, 
        char* protocol_type, int max_protocol_len, 
        char* host_ip, int max_host_ip_len, uint16* port);
    LIBUTIL_EXPORT int32 transport_address_parse_v6(const char* transport_address,
									  char* protocol_type, int32 max_protocol_len, 
									  char* host_ip, int32 max_host_ip_len, uint16* port);
    LIBUTIL_EXPORT boolean transport_address_parse_hostname(
        char* transport_address, char* host_name, int max_host_name_len);
    LIBUTIL_EXPORT char* url_string_encode(char* src, char* dest, int max_len);
    LIBUTIL_EXPORT uint32 xml_get_uint32(char* src, char* tag, uint32 def);
    LIBUTIL_EXPORT int32 xml_get_int32(char* src, char* tag, int32 def);
    LIBUTIL_EXPORT uint16 xml_get_uint16(char* src, char* tag, uint16 def);
    LIBUTIL_EXPORT int16 xml_get_int16(char* src, char* tag, int16 def);
    LIBUTIL_EXPORT char* xml_get_string(char* src, char* tag, int32 max_length, 
        char* dest, char* def);
	LIBUTIL_EXPORT char* xml_get_string_nocase(char* src, char* tag, int32 max_length, 
        char* dest, char* def);
    LIBUTIL_EXPORT char* get_local_ip();
    LIBUTIL_EXPORT char* get_local_ip_address();
    LIBUTIL_EXPORT boolean is_ip_address(char* sz);
    LIBUTIL_EXPORT void resolve_2_ip(char* host_name, char* ip_address);
    LIBUTIL_EXPORT uint32 ip_2_id(char* ip_address);
    LIBUTIL_EXPORT char* id_2_ip(uint32 ip_address);
#if defined(UNIX) || defined(LINUX)
    LIBUTIL_EXPORT void get_vector_from_string(const char* istring, const char *delim,vector<string> & str_v);
#endif

	//oliver, 5/20/2013, for T29 new encryption
	int read_config_security_keys();
    const	char* get_key(int keyidx);
	//end
	char * trim_left( char * p_str);
	char * trim_right( char * p_str, char *p_tail);
	bool has_value(const char* str, const char* del, const char* val);
	string stringToLower(const string& s);
	void string2Lower(string& s);

 
}

#ifndef WIN32
    extern void ms_sleep(uint32 milli_seconds);
    #define stricmp strcasecmp

#ifdef _ASSERTE
#undef _ASSERTE
#define  _ASSERTE(x)
#endif

#endif

extern char g_webex_home_dir[512];

#endif // __T120BASE_H__
