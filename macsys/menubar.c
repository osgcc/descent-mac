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
 * $Source: Smoke:miner:source:macsys::RCS:menubar.c $
 * $Revision: 1.4 $
 * $Author: allender $
 * $Date: 1995/08/31 15:46:46 $
 *
 * Functions to deal with manipulating the macintosh menubar
 *
 * $Log: menubar.c $
 * Revision 1.4  1995/08/31  15:46:46  allender
 * removed conditional compiles for functions
 *
 * Revision 1.3  1995/06/12  10:33:43  allender
 * change parameters to window fn's because of differnces between compiler
 * prototypes
 *
 * Revision 1.2  1995/05/04  20:07:14  allender
 * use proper prototypes on mac functions
 *
 * Revision 1.1  1995/04/07  13:17:22  allender
 * Initial revision
 *
 */

#include <Quickdraw.h>
#include <LowMem.h>

#include "dtypes.h"

static ubyte menubar_hidden = 0;
static ushort mbar_height;
static RgnHandle desktop_rgn = nil;

void hide_menubar()
{
	RgnHandle menu_rgn;
	Rect menu_rect;
	
	if (!menubar_hidden) {
		menubar_hidden = 1;
		mbar_height = LMGetMBarHeight();
		LMSetMBarHeight(0);
		if (desktop_rgn == nil)
			desktop_rgn = NewRgn();

//  Get the desktop region saved for restoration.  Find the menubar region, and then
//  make the desktop region everything it was plus the menubar.  Call the appropriate
//  window routines to reset the desktop

		CopyRgn(GetGrayRgn(), desktop_rgn);
		menu_rgn = NewRgn();
		menu_rect.top = qd.screenBits.bounds.top;
		menu_rect.left = qd.screenBits.bounds.left;
		menu_rect.right = qd.screenBits.bounds.right;
		menu_rect.bottom = mbar_height;
		RectRgn(menu_rgn, &menu_rect);
		UnionRgn(GetGrayRgn(), menu_rgn, GetGrayRgn());

		PaintBehind((WindowRef)FrontWindow(), menu_rgn);
		CalcVisBehind((WindowRef)FrontWindow(), menu_rgn);

		DisposeRgn(menu_rgn);
	}
}

void show_menubar()
{
	Rect menu_rect;
	RgnHandle menu_rgn;
	
	if (menubar_hidden) {
		menubar_hidden = 0;
		LMSetMBarHeight(mbar_height);
		CopyRgn(desktop_rgn, GetGrayRgn());

		menu_rgn = NewRgn();
		menu_rect.top = qd.screenBits.bounds.top;
		menu_rect.left = qd.screenBits.bounds.left;
		menu_rect.right = qd.screenBits.bounds.right;
		menu_rect.bottom = mbar_height;
		RectRgn(menu_rgn, &menu_rect);
		PaintBehind((WindowRef)FrontWindow(), desktop_rgn);
		CalcVisBehind((WindowRef)FrontWindow(), desktop_rgn);

		ForeColor(blackColor);
		BackColor(whiteColor);

		DrawMenuBar();
		SetEmptyRgn(desktop_rgn);
		DisposeRgn(menu_rgn);
	}
}
