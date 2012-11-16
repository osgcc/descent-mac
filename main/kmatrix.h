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
 * $Source: Smoke:miner:source:main::RCS:KMATRIX.H $
 * $Revision: 1.1 $
 * $Author: allender $
 * $Date: 1995/05/16 15:58:35 $
 * 
 * Kill matrix.
 * 
 * $Log: KMATRIX.H $
 * Revision 1.1  1995/05/16  15:58:35  allender
 * Initial revision
 *
 * Revision 2.0  1995/02/27  11:28:51  john
 * New version 2.0, which has no anonymous unions, builds with
 * Watcom 10.0, and doesn't require parsing BITMAPS.TBL.
 * 
 * Revision 1.3  1995/02/15  14:47:39  john
 * Added code to keep track of kills during endlevel.
 * 
 * Revision 1.2  1994/12/09  16:19:46  yuan
 * kill matrix stuff.
 * 
 * Revision 1.1  1994/12/09  15:58:33  yuan
 * Initial revision
 * 
 * 
 */



#ifndef _KMATRIX_H
#define _KMATRIX_H

extern int kmatrix_kills_changed;

void kmatrix_view();

#endif
