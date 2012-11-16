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
 * $Source: Smoke:miner:source:2d::RCS:gpixel.c $
 * $Revision: 1.1 $
 * $Author: allender $
 * $Date: 1995/03/09 08:55:42 $
 *
 * Graphical routines for getting a pixel's value.
 *
 * $Log: gpixel.c $
 * Revision 1.1  1995/03/09  08:55:42  allender
 * Initial revision
 *
 *
 * --- PC RCS information ---
 * Revision 1.5  1994/11/18  22:50:20  john
 * Changed shorts to ints in parameters.
 * 
 * Revision 1.4  1994/05/06  12:50:08  john
 * Added supertransparency; neatend things up; took out warnings.
 * 
 * Revision 1.3  1993/10/15  16:22:50  john
 * y
 * 
 * Revision 1.2  1993/09/29  16:15:00  john
 * optimized
 * 
 * Revision 1.1  1993/09/08  11:43:40  john
 * Initial revision
 * 
 *
 */
#include "mem.h"
#include "gr.h"
#include "grdef.h"

unsigned char gr_ugpixel( grs_bitmap * bitmap, int x, int y )
{
	return bitmap->bm_data[ bitmap->bm_rowsize*y + x ];
}

unsigned char gr_gpixel( grs_bitmap * bitmap, int x, int y )
{
	if ((x<0) || (y<0) || (x>=bitmap->bm_w) || (y>=bitmap->bm_h)) return 0;

	return bitmap->bm_data[ bitmap->bm_rowsize*y + x ];
}
