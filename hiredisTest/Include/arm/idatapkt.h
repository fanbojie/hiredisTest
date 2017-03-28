/*-------------------------------------------------------------------------*/
/*                                                                         */
/* ATDEFS.H                                                                */
/*                                                                         */
/* Copyright (C) ActiveTouch Inc.                                          */
/* All rights reserved                                                     */
/*                                                                         */
/* Author                                                                  */
/*      Guanghong Yang (kelveny@activetouch.com)                           */
/*                                                                         */
/* History                                                                 */
/*      04/12/99                                                           */
/*      08/26/99 Add machintosh support by Jack Feng                       */
/*                                                                         */
/*-------------------------------------------------------------------------*/

#ifndef __IDATAPKT_H__
#define __IDATAPKT_H__

#include "platform.h"

class ITP_Data_Packet
{
public:
    virtual void add_reference() = 0;
    virtual void release_reference() = 0;
    virtual uint8* get_packet_buffer() = 0;
    virtual uint32 get_packet_offset() = 0;
    virtual uint32 get_packet_length() = 0;
    //virtual void attach_buffer(uint8* raw_data, uint32 raw_length) = 0;
	//virtual void detach_buffer(uint8* &raw_data, uint32 &raw_length) = 0;
    //virtual void release_buffer() = 0;

public:
	// budingc 12/13/2006, for p2p.
	ITP_Data_Packet() : m_nFlag(DFLAG_CTRL), m_nPriority(3) { }

	typedef uint32 DFLAG;
	enum { 
		DFLAG_NONE = 0, 
		DFLAG_CTRL = 1 << 0,
		DFLAG_DATA = 1 << 1,
		DFLAG_APPS = 1 << 16,
		DFLAG_AUDI = 1 << 17,
		DFLAG_VIDE = 1 << 18,
		DFLAG_ADVD = (DFLAG_AUDI | DFLAG_VIDE),
	};
	DFLAG m_nFlag;
	uint16 m_nPriority;
};

#endif  // !__IDATAPKT_H__

