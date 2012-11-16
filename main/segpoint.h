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
 * $Source: Smoke:miner:source:main::RCS:SEGPOINT.H $
 * $Revision: 1.1 $
 * $Author: allender $
 * $Date: 1995/05/16 16:02:38 $
 * 
 * Hopefully temporary file to hold external definition of Segment_points[]
 * 
 * $Log: SEGPOINT.H $
 * Revision 1.1  1995/05/16  16:02:38  allender
 * Initial revision
 *
 * Revision 2.0  1995/02/27  11:26:54  john
 * New version 2.0, which has no anonymous unions, builds with
 * Watcom 10.0, and doesn't require parsing BITMAPS.TBL.
 * 
 * Revision 1.2  1994/02/16  17:14:40  matt
 * Added include of 3d.h
 * 
 * Revision 1.1  1993/12/06  09:51:37  matt
 * Initial revision
 * 
 * 
 */



#ifndef _SEGPOINTS_H
#define _SEGPOINTS_H

#include "3d.h"

//extern	g3s_point	Segment_points[];
extern g3s_point *Segment_points;

#endif
