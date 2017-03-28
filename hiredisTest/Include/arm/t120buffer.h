/*-------------------------------------------------------------------------*/
/*                                                                         */
/*  t120buffer.h                                                           */
/*                                                                         */
/*  History                                                                */
/*      02/12/03     created by E. lo                                     */
/*                                                                         */
/*  Copyright (C) 2002 by WebEx Communications Inc.                        */
/*  All rights reserved                                                    */
/*                                                                         */
/*-------------------------------------------------------------------------*/

#ifndef __T120_BUFFER_H__
#define __T120_BUFFER_H__

#include "platform.h"

#include "t120buffer.h"
 
/////////////////////////////////////////////////////////////////////////////
// class diagram
//
class T120_Circular_Window_Buffer;


/////////////////////////////////////////////////////////////////////////////
// T120_Poller
//
class T120_Circular_Window_Buffer
{
public:

    T120_Circular_Window_Buffer();
    virtual ~T120_Circular_Window_Buffer();

	int get_size();
	
	boolean set_size(int cur_size);
	
	void reset();
	void close();

	int  get_written_size();

	int  write(const void *pbuf, int nlen);
	int  read(void *pbuf, int nlen);

	int  get_last_pos();

	boolean is_filled();

protected:

	uint8	*p_buffer;
	int		buffer_size;

	int		min_pos;
	int		max_pos;

	int		cur_pos;

	boolean b_is_filled;


};

#endif

