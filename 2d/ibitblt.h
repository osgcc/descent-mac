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
 * $Source: Smoke:miner:source:2d::RCS:ibitblt.h $
 * $Revision: 1.1 $
 * $Author: allender $
 * $Date: 1995/08/18 15:50:57 $
 *
 *  Header prototypes for inverse bitblt funcitons
 *
 * $Log: ibitblt.h $
 * Revision 1.1  1995/08/18  15:50:57  allender
 * Initial revision
 *
*/

#ifndef _IBITBLT_H
#define _IBITBLT_H

void gr_ibitblt(grs_bitmap *src, grs_bitmap *dest, ubyte pixel_double);
void gr_ibitblt_create_mask(grs_bitmap *mask_bmp, int sx, int sy, int sw, int sh, int srowsize);
void gr_ibitblt_find_hole_size(grs_bitmap *mask_bmp, int *minx, int *miny, int *maxx, int *maxy);

#endif
