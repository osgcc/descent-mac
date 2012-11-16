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
 * $Source: Smoke:miner:source:macsys::RCS:scrncpy.c $
 * $Revision: 1.3 $
 * $Author: allender $
 * $Date: 1995/06/12 15:10:58 $
 *
 * $Log: scrncpy.c $
 * Revision 1.3  1995/06/12  15:10:58  allender
 * no more direct to screen.  This is handled through normal gr (2d) calls
 *
 * Revision 1.2  1995/05/17  13:18:18  allender
 * for PPC, call specialized memory copy routine which moves 8 bytes at a time
 *
 * Revision 1.1  1995/05/05  12:40:33  allender
 * Initial revision
 *
 * Revision 1.1  1995/04/07  13:18:30  allender
 * Initial revision
 *
 *
 */

#include <stdio.h>
#include <strings.h>
#include <Quickdraw.h>
#include <QDOffscreen.h>
#include "dtypes.h"
#include "macsys.h"

extern int *RowOffsets;
extern int GlobalX, GlobalY, GWorldRowBytes, GWorldWidth, GWorldHeight;
extern ubyte *GameData;
extern void fp_memcpy(ubyte *d, ubyte *s, int w);

int use_quickdraw = 0;

void copybits_to_screen()
{
}

void
direct_to_screen()
{
	int y;

	for (y = 0; y < GWorldHeight; y++)
#ifndef __powerc
		memcpy(RowOffsets[y + GlobalY] + GlobalX, GameData + (y * GWorldRowBytes), GWorldWidth);
#else
		fp_memcpy((ubyte *)(RowOffsets[y + GlobalY] + GlobalX), (ubyte *)(GameData + (y * GWorldRowBytes)), GWorldWidth);
#endif
}

void bitblt_to_screen()
{
	return;
//	if (use_quickdraw)
//		copybits_to_screen();
//	else
		direct_to_screen();
}
