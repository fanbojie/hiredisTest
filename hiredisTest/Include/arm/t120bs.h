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

#ifndef __T120BS_H__
#define __T120BS_H__

#include "platform.h"
#include "t120defs.h"
#include "wbxconfid.h"
/////////////////////////////////////////////////////////////////////////////
//  T120_Byte_Stream
//

#if defined(LINUX)
#if !defined(uint64)
typedef  unsigned long long uint64;
#endif

#if !defined(int64)
typedef long long int64;
#endif
#endif//LINUX



#ifdef MACOS
class T120_Byte_Stream
#else
class LIBUTIL_EXPORT T120_Byte_Stream
#endif
{
public :
	T120_Byte_Stream(uint8* buf, uint32 offset, uint32 buf_size);
	virtual ~T120_Byte_Stream();

	void attach(uint8* buf, uint32 offset, uint32 buf_size);
	uint32 seek(uint32 pos);
	uint32 skip(int32 dis);
	uint32 tell();
	uint8* get_data();
	void write(void* data, uint32 length);
	void read(void* data, uint32 length);
	T120_Byte_Stream& operator << (uint8 ch);
	T120_Byte_Stream& operator << (char ch);
	T120_Byte_Stream& operator << (int16 s);
	T120_Byte_Stream& operator << (uint16 s);
	T120_Byte_Stream& operator << (int32 l);
	T120_Byte_Stream& operator << (uint32 l);
    T120_Byte_Stream& operator << (wbxConfId& confid);
#if defined(LINUX)
	T120_Byte_Stream& operator << (int64 ll);
	T120_Byte_Stream& operator << (uint64 ll);
#endif//LINUX
	T120_Byte_Stream& operator << (float32 f);
	T120_Byte_Stream& operator << (float64 d);
	T120_Byte_Stream& operator << (char* str);
	T120_Byte_Stream& operator << (const char str[]);
	T120_Byte_Stream& operator >> (uint8& ch);
	T120_Byte_Stream& operator >> (char& ch);
	T120_Byte_Stream& operator >> (int16& s);
	T120_Byte_Stream& operator >> (uint16& s);
	T120_Byte_Stream& operator >> (int32& l);
	T120_Byte_Stream& operator >> (uint32& l);
#if defined(LINUX)
	T120_Byte_Stream& operator >> (int64 &ll);
	T120_Byte_Stream& operator >> (uint64 &ll);
	int16   read_int16();
	uint16 read_uint16();
	int32   read_int32();
	uint32 read_uint32();
	int64   read_int64();
	uint64 read_uint64();
	static void swap(uint64 &ll);
	//to fix AS issue on SPA, kelvin 2008-12-22
	//->
	//return true, if host byte order is big endian, otherwise, return false
	static boolean s_hbo_is_le();
	static uint16 s_swap_i16(const uint16& s);
	static uint32 s_swap_i32(const uint32& i);
	//<- 
#endif//LINUX
	T120_Byte_Stream& operator >> (float32& f);
	T120_Byte_Stream& operator >> (float64& d);
	T120_Byte_Stream& operator >> (char*& str);
	char* read_string(uint16 max_len);
	void read_string(char* str, uint16 max_len);
        
    T120_Byte_Stream& operator >> (wbxConfId& confid);

	static void swap(void* data, int length);
	static void init();
	uint32 get_buf_size(){return buf_size;}//crabant 090607
protected :
	uint8* buf;
	uint32 cur_pos;
	uint32 buf_size;
	static boolean s_is_little_endian;
};

#endif // __T120BS_H__
