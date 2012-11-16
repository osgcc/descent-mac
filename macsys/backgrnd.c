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
 * $Source: Smoke:miner:source:macsys::RCS:backgrnd.c $
 * $Revision: 1.1 $
 * $Author: allender $
 * $Date: 1995/04/07 13:18:00 $
 *
 * Routines to deal with blacking out the background
 *
 * $Log: backgrnd.c $
 * Revision 1.1  1995/04/07  13:18:00  allender
 * Initial revision
 *
 */

#include <stdio.h>
#include <Types.h>
#include <Windows.h>
#include <Quickdraw.h>
#include <ToolUtils.h>
#include <Resources.h>

#include "dtypes.h"
#include "resource.h"

static ubyte initialized = 0;
static ubyte background_hidden = 0;
static WindowPtr background_win = NULL;
static PicHandle background_pict = NULL;

void close_background()
{
	if (background_pict)
		ReleaseResource((Handle)background_pict);
	if (background_win)
		DisposeWindow(background_win);
}

void hide_background(Rect hide_rect)
{
	RgnHandle	deskRgn;
	GrafPtr	savedPort;

	if (!initialized) {
		atexit(close_background);
		initialized = 1;
	}
	
	if (background_hidden)
		return;

	GetPort(&savedPort);
	deskRgn = GetGrayRgn();

	if (!background_win) {
		background_win = NewCWindow(nil, &hide_rect, "\p", 0, NO_BORDER_WIN_ID << 4, (WindowPtr) -0L, 0, 0);
//		background_win = NewCWindow(nil, &(qd.screenBits.bounds), "\p", 0, rDocProc, (WindowPtr)-1, 0, 0);
		if (background_win == nil)
			return;
		background_pict = GetPicture(BLACKBACK_PICT);
		if (!background_pict) {
			DisposeWindow(background_win);
			background_win = NULL;
			return;
		}
		SetWindowPic(background_win, background_pict);
	}
	SendBehind(background_win, nil);
	ShowWindow(background_win);

	SetPort(background_win);
	FillRect(&background_win->portRect, &qd.black);
	SetPort(savedPort);
	background_hidden = 1;
}

void show_background()
{
	if (background_hidden) {
		HideWindow(background_win);
		background_hidden = 0;
	}
}
