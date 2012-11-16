/*
THE COMPUTER CODE CONTAINED HEREIN IS THE SOLE PROPERTY OF PARALLAX
SOFTWARE CORPORATION ("PARALLAX").  PARALLAX, IN DISTRIBUTING THE CODE TO
END-USERS, AND SUBJECT TO ALL OF THE TERMS AND CONDITIONS HEREIN, GRANTS A
ROYALTY-FREE, PERPETUAL LICENSE TO SUCH END-USERS FOR USE BY SUCH END-USERS
IN USING, DISPLAYING,  AND CREATING DERIVATIVE WORKS THEREOF, SO LONG AS
SUCH USE, DISPLAY OR CREATION IS FOR NON-COMMERCIAL, ROYALTY OR REVENUE
FREE PURPOSES.  IN NO EVENT SHALL THE END-USER USE THE COMPUTER CODE
CONTAINED HEREIN FOR REVENUE-BEARING PURPOSES.  THE END-USER UNDERSTANDS
AND AGREES TO THE TERMS HEREIN AND ACCEPTS THE SAME BY USE OF THIS FILE.  
COPYRIGHT 1993-1998 PARALLAX SOFTWARE CORPORATION.  ALL RIGHTS RESERVED.
*/
/*
 * $Source: Smoke:miner:source:misc::RCS:byteswap.h $
 * $Revision: 1.4 $
 * $Author: allender $
 * $Date: 1995/08/23 21:28:15 $
 *
 * code to swap bytes because of big/little endian problems.
 * 
 * $Log: byteswap.h $
 * Revision 1.4  1995/08/23  21:28:15  allender
 * fix mcc compiler warning
 *
 * Revision 1.3  1995/08/18  15:51:42  allender
 * put back in old byteswapping code
 *
 * Revision 1.2  1995/05/04  20:10:18  allender
 * proper prototypes
 *
 * Revision 1.1  1995/03/30  15:02:11  allender
 * Initial revision
 *
*/
 
#ifndef _BYTESWAP_
#define _BYTESWAP_

#include "dtypes.h"

extern ushort swapshort(ushort s);
extern uint swapint(uint i);

#if 0
#define swapshort(x)	(							\
						(x << 8) |					\
						(((ushort)x) >> 8)			\
						)
						
#define swapint(x)		(							\
						(x << 24) |					\
						(((ulong)x) >> 24) |		\
						((x & 0x0000ff00) << 8) |	\
						((x & 0x00ff0000) >> 8)		\
						)
#endif

#endif
