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
 * $Source: Smoke:miner:source:macsys::RCS:mevent.c $
 * $Revision: 1.15 $
 * $Author: allender $
 * $Date: 1995/10/28 22:51:55 $
 *
 * $Log: mevent.c $
 * Revision 1.15  1995/10/28  22:51:55  allender
 * make do_appl_quit1 which doesn't save/restore monitor
 * background below quit dialog -- WHAT A HACK!!!!
 *
 * Revision 1.14  1995/10/27  16:56:17  allender
 * fix up the quit thing restoring correctly
 *
 * Revision 1.13  1995/10/27  15:18:55  allender
 * go back to descent dir after events, and make sure
 * that screen behind quit box refreshes correctly on
 * higher than 640x480 mode
 *
 * Revision 1.12  1995/10/27  11:06:55  allender
 * cd back to Descent dir after any event processing
 *
 * Revision 1.11  1995/10/24  15:41:12  allender
 * new quit dialog stuff -- use dialog so that background
 * can be saved and restored easily
 *
 * Revision 1.10  1995/10/20  00:11:02  allender
 * new event code
 *
 * Revision 1.9  1995/10/15  22:48:16  allender
 * don't loop in process_initial_events
 *
 * Revision 1.8  1995/10/13  14:41:37  allender
 * tried putting in standard dialog filter
 *
 * Revision 1.7  1995/10/11  13:57:59  allender
 * added GetDiskInserted for mounting CD's.  Killed
 * the finder
 *
 * Revision 1.6  1995/10/07  16:46:00  allender
 * ode for single event processing
 *
 * Revision 1.5  1995/09/24  11:00:43  allender
 * fixed up do_qppl_quit to get to basic black and white if screen
 * is faded out
 *
 * Revision 1.4  1995/09/18  08:47:42  allender
 * restore back to 8 bits when exiting back to Descent from
 * menubar
 *
 * Revision 1.3  1995/08/31  15:47:48  allender
 * add silly return at eof
 *
 * Revision 1.2  1995/08/31  15:47:26  allender
 * *** empty log message ***
 *
 * Revision 1.1  1995/04/07  13:19:41  allender
 * Initial revision
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <Events.h>
#include <Windows.h>
#include <SegLoad.h>
#include <Menus.h>
#include <ToolUtils.h>
#include <LowMem.h>
#include <Quickdraw.h>
#include <Palettes.h>
#include <Dialogs.h>

#include "dtypes.h"
#include "resource.h"
#include "gr.h"
#include "palette.h"
#include "macsys.h"
#include "key.h"
#include "error.h"
#include "halestrm.h"
#include "direct.h"

#define SLEEP_TIME 60
#define SINGLE_SLEEP_TIME	15

int done = 0;
extern WindowPtr background_window;

extern void OutlineOK( DialogPtr dlog, Boolean enabled );

void do_appl_quit()
{
	grs_canvas *save_canvas;
	grs_bitmap *bg_saved;
	DialogPtr dlog;
	EventRecord event;
	int w, h, sx, sy, r, dx, dy;
	short item;
	char c;

	if ( gr_palette_faded_out )
		debug_video_mode();			// reset palette from all black to basic black and white if faded out!

	hide_cursor();
	dlog = GetNewDialog(QUIT_ALERT, NULL, (WindowPtr)-1);
	if (dlog == NULL)
		return;
	w = dlog->portRect.right - dlog->portRect.left;
	h = dlog->portRect.bottom - dlog->portRect.top;
	if (r = (w & 0x7))
		w += (8-r);			// align width to 8 byte boundry
		
	w += 32;
	h += 32;
		
	sx = ((*GameMonitor)->gdRect.right - (*GameMonitor)->gdRect.left - w) / 2;
	sy = ((*GameMonitor)->gdRect.bottom - (*GameMonitor)->gdRect.top - h) / 2;
	dx = 320 - (w / 2);
	dy = 240 - (h / 2);
	
	if (r = (sx & 0x7))
		sx += (8-r);			// align width to 8 byte boundry

	if (r = (dx & 0x7))
		dx += (8-r);			// align width to 8 byte boundry

// save the info on the screen into a temporary canvas

	save_canvas = grd_curcanv;
	gr_set_current_canvas(NULL);
	bg_saved = gr_create_bitmap(w, h);
	gr_bm_bitblt(w, h, 0, 0, dx-16, dy-16, &(grd_curcanv->cv_bitmap), bg_saved);
	
	SetPort(dlog);
	MoveWindow(dlog, sx + (*GameMonitor)->gdRect.left, sy + (*GameMonitor)->gdRect.top, 1);

// do the dialog stuff
	key_close();
	show_cursor();
	ShowWindow((WindowPtr)dlog);
	OutlineOK(dlog, 1);
	do
	{
		item = 0;
		
		//¥	Get next event from the event queue
		if (GetNextEvent(everyEvent, &event))
		{
			switch (event.what)
			{
				case keyDown:
					c = event.message & charCodeMask;
					if ((event.modifiers & cmdKey) && ((c == '.') || (c == 'q') || (c == 'Q')))
					{
						item = cancel;
						break;
					}
					
					if (c == 0x1B)
					{
						item = cancel;
						break;
					}
					
					if ((c == 0x0D) || (c == 0x03))
					{
						item = ok;
						break;
					}
					
					break;
			
				default:
					//¥	If not, perform regular dialog event processing
					if (IsDialogEvent(&event))
						DialogSelect(&event, &dlog, &item);
			}
		}
	} while ((item != ok) && (item != cancel));

	HideWindow(dlog);
	
	if (item == ok)
		exit(0);

	hide_cursor();
	key_init();

	DisposeDialog(dlog);
	SetPort(GameWindow);
	
// other cleanup
	
	gr_bm_bitblt( w, h, dx-16, dy-16, 0, 0, bg_saved, &(grd_curcanv->cv_bitmap) );
	gr_set_current_canvas(save_canvas);

}

void do_appl_quit1()
{
	DialogPtr dlog;
	EventRecord event;
	short item;
	char c;

	if ( gr_palette_faded_out )
		debug_video_mode();			// reset palette from all black to basic black and white if faded out!

	hide_cursor();
	dlog = GetNewDialog(QUIT_ALERT, NULL, (WindowPtr)-1);
	if (dlog == NULL)
		return;
	SetPort(dlog);
	MoveWindow(dlog, 200, 200, 1);

// do the dialog stuff
	key_close();
	show_cursor();
	ShowWindow((WindowPtr)dlog);
	OutlineOK(dlog, 1);
	do
	{
		item = 0;
		
		//¥	Get next event from the event queue
		if (GetNextEvent(everyEvent, &event))
		{
			switch (event.what)
			{
				case keyDown:
					c = event.message & charCodeMask;
					if ((event.modifiers & cmdKey) && ((c == '.') || (c == 'q') || (c == 'Q')))
					{
						item = cancel;
						break;
					}
					
					if (c == 0x1B)
					{
						item = cancel;
						break;
					}
					
					if ((c == 0x0D) || (c == 0x03))
					{
						item = ok;
						break;
					}
					
					break;
			
				default:
					//¥	If not, perform regular dialog event processing
					if (IsDialogEvent(&event))
						DialogSelect(&event, &dlog, &item);
			}
		}
	} while ((item != ok) && (item != cancel));

	HideWindow(dlog);
	
	if (item == ok)
		exit(0);

	hide_cursor();
	key_init();

	DisposeDialog(dlog);
	SetPort(GameWindow);
	
}

void do_menu(int menu_choice)
{
	short which_menu, which_item;
	
	which_menu = HiWord(menu_choice);
	which_item = LoWord(menu_choice);
	switch (which_menu) {

	case APPLE_MENU_ID:
		if (which_item == ABOUT_ITEM) {
			hide_menubar();
//			credits_show();
			show_menubar();
		}
		break;
	case GAME_MENU_ID:
		if (which_item == QUIT_ITEM)
			do_appl_quit();
		if (which_item == RESUME_ITEM)
			done = 1;
		break;

	case EDIT_MENU_ID:
		break;
	}
	HiliteMenu(0);
}

void do_mouse_down(EventRecord event)
{
	WindowRef window;
	short where;
	
	where = FindWindow(event.where, &window);
	switch(where) {
	
	case inMenuBar:
		do_menu(MenuSelect(event.where));
		break;
			
	case inSysWindow:
		SystemClick(&event, window);
		break;
		
	}
}

void do_update_event(EventRecord event)
{
	WindowPtr window = (WindowPtr)(event.message);
	BeginUpdate(window);
	ShowWindow(window);
	EndUpdate(window);
}

void do_os_event(EventRecord event)
{
	ubyte what_type = (event.message >> 24) & 0xff;
	
	switch(what_type) {
	
	case suspendResumeMessage:
		if (event.message & resumeFlag) {			// resume event.  update everything.
			ShowWindow(background_window);
		} else {
			HideWindow(background_window);
		}
		break;
	}
}

// main event type loop for when user wants the menu bar.  We will assume that the
// palette is faded out at this point.  Bring back the black window and restore the
// device clut at the start of this.
void do_event_loop()
{
	return;
#if 0
	EventRecord event;

#ifdef SHAREWARE	
	PauseSoundMusicSystem();
#endif
	if ( save_bbp != 8 )
		SetDepth(GameMonitor, save_bbp, gdDevType, 1);
	RestoreDeviceClut(GameMonitor);
	key_close();			// our keyboard handler is kind of ugly -- remove it for now
	show_cursor();
	show_menubar();
	done = 0;
	while (!done) {
		if (WaitNextEvent(everyEvent, &event, SLEEP_TIME, NULL)) {
			switch (event.what) {
			
			case mouseDown:
				do_mouse_down(event);
				break;
			case keyDown:
			case autoKey:
				if (event.modifiers & cmdKey)
					do_menu(MenuKey(event.message & charCodeMask));
#ifndef NDEBUG
				if (((event.message >> 8) & 0xff) == KEY_BACKSP)
					Int3();
#endif
				break;
			case updateEvt:
				do_update_event(event);
				break;
			case osEvt:
				do_os_event(event);
				break;
			}
		}
	}
	hide_menubar();
	hide_cursor();
	SetEventMask(0xffff);
	LMSetSysEvtMask(0xffff);
	key_init();			// back to our old tricks
	if (SetDepth(GameMonitor, 8, gdDevType, 1))
		Error("Cannot set monitor to desired depth");
	gr_palette_clear();
#ifdef SHAREWARE
	ResumeSoundMusicSystem();
#endif
#endif
}

void process_one_event()
{
	EventRecord event;

	WaitNextEvent(everyEvent, &event, SINGLE_SLEEP_TIME*4, NULL);
	CDToDescentDir();
}	


void process_initial_events()
{
	int i;
	EventRecord event;

	if (WaitNextEvent(everyEvent, &event, SINGLE_SLEEP_TIME*4, NULL)) {
		switch (event.what) {
		
		case mouseDown:
			break;
		case keyDown:
		case autoKey:
			if ( (((event.message >> 8) & 0xff) == KEY_S) && (event.modifiers & (cmdKey | shiftKey)) )
				use_sounds = 0;
			break;
		case updateEvt:
			do_update_event(event);
			break;
		case osEvt:
			do_os_event(event);
			break;
		}
	}
	CDToDescentDir();
}

int GetDiskInserted()
{
	EventRecord event;
	int ret;
	
	WaitNextEvent(everyEvent, &event, SINGLE_SLEEP_TIME, NULL);
	if (event.what == diskEvt) {
		if ( HiWord(event.message) == noErr) {
			ret = 1;
		}
	} else if (event.what == keyDown) {
		if ( ((event.message >> 8) & 0xff) == KEY_ESC )
			ret = -1;
	} else
		ret = 0;
		
	CDToDescentDir();
	return ret;
}
