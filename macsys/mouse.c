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
 * $Source: Buggin:miner:source:macsys::RCS:mouse.c $
 * $Revision: 1.1 $
 * $Author: allender $
 * $Date: 1995/04/07 13:17:09 $
 *
 * $Log: mouse.c $
 * Revision 1.1  1995/04/07  13:17:09  allender
 * Initial revision
 *
*/

#include <Quickdraw.h>
#include "dtypes.h"

ubyte cursor_hidden = 0;

void hide_cursor()
{
	if (!cursor_hidden) {
		cursor_hidden = 1;
		HideCursor();
	}
}

void show_cursor()
{
	if (cursor_hidden) {
		cursor_hidden = 0;
		ShowCursor();
	}
}
