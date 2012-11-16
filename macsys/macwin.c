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
 * $Source: BigRed:miner:source:macsys::RCS:macwin.c $
 * $Revision: 1.30 $
 * $Author: allender $
 * $Date: 1995/11/02 14:13:09 $
 *
 * $Log: macwin.c $
 * Revision 1.30  1995/11/02  14:13:09  allender
 * cd checking only on registered version
 *
 * Revision 1.29  1995/10/28  22:51:24  allender
 * #ifdef RELEASE for CD checking and call do_appl_quit1 so
 * we don't do silly restore/save of monitor background
 *
 * Revision 1.28  1995/10/28  22:22:24  allender
 * added calls to check for Descent CD at startup
 *
 * Revision 1.27  1995/10/24  18:13:13  allender
 * cd back to Descent directory after saving screen shot
 *
 * Revision 1.26  1995/10/20  22:18:05  allender
 * change creator code for PICTS to 'ttxt'
 *
 * Revision 1.25  1995/10/20  00:09:21  allender
 * added correct creator code to PICT files, and now
 * call process_one_event in window code
 *
 * Revision 1.24  1995/10/17  13:19:51  allender
 * show and hide cursor when doing screen shot
 *
 * Revision 1.23  1995/10/15  23:21:48  allender
 * process events after getting game monitor
 *
 * Revision 1.22  1995/10/13  14:40:57  allender
 * don't change to GDevice when monitor is picked
 *
 * Revision 1.21  1995/10/11  13:56:34  allender
 * fixed up window processing -- background black window
 * now covers only game monitor
 *
 * Revision 1.20  1995/10/05  08:54:46  allender
 * close keyboard and show cursor always before bringing up
 * monitor selection box
 *
 * Revision 1.19  1995/10/03  11:27:55  allender
 * fixed multiple monitor problems with game window appearing
 * on wrong monitor
 *
 * Revision 1.18  1995/09/24  10:59:19  allender
 * canceling or cmd-q'ing out of pickamonitor will ask for quit game
 *
 * Revision 1.17  1995/09/19  10:37:49  allender
 * start of copybits compatibility stuff
 *
 * Revision 1.16  1995/09/18  08:45:27  allender
 * bitplane restoration stuff on exit
 *
 * Revision 1.15  1995/09/18  08:10:39  allender
 * handled NULL returned from PickaMonitor.
 *
 * Revision 1.14  1995/09/15  15:52:53  allender
 * better handling of dumping of PICT files
 *
 * Revision 1.13  1995/09/13  09:08:20  allender
 * added PICT screen dumps
 *
 * Revision 1.12  1995/08/31  15:46:22  allender
 * don't show game window
 *
 * Revision 1.11  1995/08/14  14:30:52  allender
 * removed white_window call
 *
 * Revision 1.10  1995/08/08  14:22:23  allender
 * new windowing code (i.e. white and black background windows)
 * plus new code for picking the monitor ala MacPlay
 *
 * Revision 1.9  1995/07/17  09:08:33  allender
 * first attempt to change pixel dpeth of device
 *
 * Revision 1.8  1995/07/05  16:19:40  allender
 * no more palette manager stuff
 *
 * Revision 1.7  1995/06/13  10:23:09  allender
 * overhauled screen manipulation stuff
 *
 * Revision 1.6  1995/05/17  14:40:01  allender
 * added some globals to speed up screen copy
 *
 * Revision 1.5  1995/05/12  11:55:06  allender
 * changed memory stuff again
 *
 * Revision 1.4  1995/05/04  20:06:35  allender
 * change palette stuff to be animated
 *
 * Revision 1.3  1995/04/18  09:52:49  allender
 * *** empty log message ***
 *
 * Revision 1.2  1995/04/07  13:15:27  allender
 * *** empty log message ***
 *
 * Revision 1.1  1995/03/09  09:16:57  allender
 * Initial revision
 *
 */

#include <stdio.h> 
#include <Types.h>
#include <Windows.h>
#include <Quickdraw.h>
#include <QDOffscreen.h>
#include <Palettes.h>
#include <GestaltEqu.h>
#include <Files.h>
#include <StandardFile.h>
#include <Script.h>
#include <Strings.h>
#include <ToolUtils.h>

#include "dtypes.h"
#include "macsys.h"
#include "grdef.h"
#include "gr.h"
#include "palette.h"
#include "mem.h"
#include "resource.h"
#include "direct.h"
#include "key.h"

// globals (?)

WindowPtr background_window = NULL;		// background window
WindowPtr GameWindow = NULL;	// current window that the game is being played in
GWorldPtr GameGWorld = NULL;	// current GWorld we are using
GDHandle GameMonitor;			// current monitor that the game is being run on
int MonitorRowBytes;			// rowbytes for current monitor
ubyte *MonitorData;				// pointer to the screen data for monitor
ubyte save_bbp= 0;				// save the bbp of the monitor for restore when game over
ubyte Compatibility_mode = 0;	// compatibility mode using copybits?

int *RowOffsets = NULL;		// offset table for starting address of rows for the monitor
int GlobalX, GlobalY, GWorldRowBytes, GWorldWidth, GWorldHeight;

extern ubyte *win_storage;

void set_win_size(int x, int y, int w, int h)
{
	Rect new_rect;
	GWorldFlags flags, uflags;
	PixMapHandle pm;
	Point p;

//  deal with changing the GWorld's size first since this involves freeing and then
//  allocating new memory

	
//  Check the state of the pixel map and unlock the pixels.  I think that this will
//  have the effect of allowing the pixel map to be relocated in memory when the
//  UpdateGWorld happens.

	if (GameGWorld != NULL) {
		SetRect(&new_rect, 0, 0, w, h);
		pm = GetGWorldPixMap(GameGWorld);
		flags = GetPixelsState(pm);
		if (flags & pixelsLocked)
			UnlockPixels(pm);
		uflags = UpdateGWorld(&GameGWorld, 8, &new_rect, nil, nil, 0);

// lock the pixels again if they were locked before

		if (flags & pixelsLocked) {
			pm = GetGWorldPixMap(GameGWorld);
			LockPixels(pm);
		}
		if (uflags & newRowBytes) {
			pm = GetGWorldPixMap(GameGWorld);
			GWorldRowBytes = (*pm)->rowBytes & 0x7fff;
		}

		GWorldWidth = GameGWorld->portRect.right - GameGWorld->portRect.left;
		GWorldHeight = GameGWorld->portRect.bottom - GameGWorld->portRect.top;
	}

	SetPort(GameWindow);
	
//  Size the GameWindow.  We need to be sure that the left edge of the window falls on
//  a multiple of 8 byte boundry for speed purposes on the direct screen copy.  The new width
//  will always be some multiple of 16 to ensure that we have a total byte count per row of
//  some multiple of eight bytes.

	SizeWindow(GameWindow, w, h, 1);
	x += (*GameMonitor)->gdRect.left;
	y += (*GameMonitor)->gdRect.top;
	if (((x / 8) * 8) != x)
		x -= (x % 8);
	MoveWindow(GameWindow, x, y, 1);
}

grs_canvas *mac_get_gworld_data(int w, int h)
{
	Ptr buffer;
	PixMapHandle pixmap;
	grs_canvas *new;
	
	pixmap = GetGWorldPixMap(GameGWorld);
	buffer = GetPixBaseAddr(pixmap);
	
	new = (grs_canvas *)mymalloc( sizeof(grs_canvas) );

	new->cv_bitmap.bm_x = 0;
	new->cv_bitmap.bm_y = 0;
	new->cv_bitmap.bm_w = w;
	new->cv_bitmap.bm_h = h;
	new->cv_bitmap.bm_flags = 0;
	new->cv_bitmap.bm_type = BM_LINEAR;
	new->cv_bitmap.bm_rowsize = (**pixmap).rowBytes & 0x3fff;
	new->cv_bitmap.bm_data = (ubyte *)buffer;

	new->cv_color = 0;
	new->cv_drawmode = 0;
	new->cv_font = NULL;
	new->cv_font_fg_color = 0;
	new->cv_font_bg_color = 0;
	return new;
}

void black_window( Rect area )
{
	if (background_window)
		CloseWindow(background_window);
	background_window = GetNewCWindow(BLACK_WINDOW_ID, win_storage, (WindowPtr)-1);
	MoveWindow(background_window, area.left, area.top, 0);
	SizeWindow(background_window, (area.right - area.left), (area.bottom - area.top), 0);
	ShowWindow(background_window);
}

// save a PICT to a file

void SavePictScreen(int multiplayer)
{
	OSErr err;
	int parid, i, count;
	char *pfilename, filename[50], buf[512];
	short fd;
	FSSpec spec;
	PicHandle pict_handle;
	static int multi_count = 0;
	StandardFileReply sf_reply;
	
// dump the contents of the GameWindow into a picture using copybits

	pict_handle = OpenPicture(&GameWindow->portRect);
	if (pict_handle == NULL)
		return;
		
	CopyBits(&GameWindow->portBits, &GameWindow->portBits, &GameWindow->portRect, &GameWindow->portRect, srcCopy, NULL);
	ClosePicture();

// create the fsspec

	sprintf(filename, "screen%d", multi_count++);
	pfilename = c2pstr(filename);
	if (!multiplayer) {
		show_cursor();
		StandardPutFile("\pSave PICT as:", pfilename, &sf_reply);
		if (!sf_reply.sfGood) 
			goto end;
		memcpy( &spec, &(sf_reply.sfFile), sizeof(FSSpec) );
		if (sf_reply.sfReplacing)
			FSpDelete(&spec);
		err = FSpCreate( &spec, 'ttxt', 'PICT', smSystemScript );
		if (err)
			goto end;
	} else {
		parid = GetAppDirId();
		err = FSMakeFSSpec(0, parid, pfilename, &spec);
		if (err == nsvErr)
			goto end;
		if (err != fnfErr)
			FSpDelete(&spec);
		err = FSpCreate(&spec, 'ttxt', 'PICT', smSystemScript);
		if (err != 0)
			goto end;
	}

// write the PICT file
	if ( FSpOpenDF(&spec, fsRdWrPerm, &fd) )
		goto end;
	memset(buf, 0, sizeof(buf));
	count = 512;
	if ( FSWrite(fd, &count, buf) )
		goto end;
	count = GetHandleSize((Handle)pict_handle);
	HLock((Handle)pict_handle);
	if ( FSWrite(fd, &count, *pict_handle) ) {
		FSClose(fd);
		FSpDelete(&spec);
	}

end:
	HUnlock((Handle)pict_handle);
	DisposeHandle((Handle)pict_handle);
	FSClose(fd);
	hide_cursor();
	CDToDescentDir();
}


/*
 *  Creates the window and GWorld.  We won't do any size information.  We will have
 *  seperate routines which will deal with setting the size of the window and GWorld.
*/

extern GDHandle PickAMonitor(int theDepth, Boolean colorRequired, short minWidth, short minHeight);

int macwin_init()
{
	int i, w, h, x, y;
	Rect main_rect;
	WindowPtr main_window;
	GWorldPtr main_gworld;
	CTabHandle ctab;
	PixMapHandle pixmap;
	OSErr err;

#ifndef MAC_SHAREWARE
#if defined(RELEASE) && !defined(IOMEGA_OEM)
	goto check_for_cd;
#endif
#endif
	
remonitor:
	key_close();
	show_cursor();
	GameMonitor = PickAMonitor(8, 1, 640, 480);
	if (GameMonitor == NULL) {
		do_appl_quit1();
		goto remonitor;
	}
		
	hide_cursor();
	key_init();

	if ( GameMonitor == GetMainDevice() )
		hide_menubar();
		
//	SetGDevice(GameMonitor);		// assume good monitor handle here.
	
	save_bbp = (*(*GameMonitor)->gdPMap)->pixelSize;
	
	if (SetDepth(GameMonitor, 8, gdDevType, 1))
		Error("Cannot set monitor to desired depth");

	MonitorRowBytes = (*(*GameMonitor)->gdPMap)->rowBytes & 0x7fff;
	MonitorData = (ubyte *)(*(*GameMonitor)->gdPMap)->baseAddr;
	
	black_window( (*GameMonitor)->gdRect );
	process_one_event();
	process_one_event();

	w = 640;
	h = 480;
#ifdef RELEASE
	x = (((*GameMonitor)->gdRect.right - (*GameMonitor)->gdRect.left - w) / 2) + (*GameMonitor)->gdRect.left;
	y = (((*GameMonitor)->gdRect.bottom - (*GameMonitor)->gdRect.top - h) / 2) + (*GameMonitor)->gdRect.top;
#else
	x = (*GameMonitor)->gdRect.left;
	y = (*GameMonitor)->gdRect.top;
#endif
	
	SetRect(&main_rect, x, y, x + w, y + h);
	main_window = NewCWindow(0L, &main_rect, "\p", false, NO_BORDER_WIN_ID << 4, (WindowPtr)-1L, false, 0L);
	if (main_window == nil)
		return -1;			// failed NewCWindow call;
	GameWindow = main_window;
	SetPort(GameWindow);
	ShowWindow(GameWindow);
	
// check the compatibility_mode.  If we have it, then we need to create the GWorld.  The
// GWorld here will also serve as the buffer in use for the actual gameplay.

	if (Compatibility_mode) {
		if ( NewGWorld(&GameGWorld, 0, &main_rect, NULL, GameMonitor, 0) )
			Error("Cannot create offscreen world!");
		pixmap = GetGWorldPixMap(GameGWorld);
		LockPixels(pixmap);
	}
	
	if (GameGWorld != NULL) {	
		ctab = (**GetGWorldPixMap(GameGWorld)).pmTable;	// get the color table for the gWorld.
		CTabChanged(ctab);
		(**ctab).ctSeed = (**(**(*(CGrafPtr)GameWindow).portPixMap).pmTable).ctSeed;
	}

	return 0;

#if defined(RELEASE) && !defined(IOMEGA_OEM)
check_for_cd:
	{
		OSErr err;
		short refnum;
		Str255 dpath;
		StringHandle shandle;
		
		shandle = GetString(DESCENT_PATH_STR);
		if (shandle == NULL) {
			StopAlert(BAD_DATA_ALERT, NULL);
			exit(1);
		}
		memcpy(dpath, *shandle, GetHandleSize(shandle));
	
		err = HOpen(0, 0, dpath, 0, &refnum);
		if (err) {
			StopAlert(CD_ALERT, NULL);
			exit(1);
		}
		FSClose(refnum);	
	}
	goto remonitor;
#endif
	
}

#ifndef MAC_SHAREWARE
#ifdef RELEASE
void CheckForCD()
{
	OSErr err;
	short refnum;
	Str255 dpath;
	StringHandle shandle;
	
	#if defined(IOMEGA_OEM)
	return;
	#endif
	
	shandle = GetString(DESCENT_PATH_STR);
	if (shandle == NULL) {
		StopAlert(BAD_DATA_ALERT, NULL);
		exit(1);
	}
	memcpy(dpath, *shandle, GetHandleSize(shandle));

	err = HOpen(0, 0, dpath, 0, &refnum);
	if (err) {
		StopAlert(CD_ALERT, NULL);
		exit(1);
	}
	FSClose(refnum);	
}
#endif
#endif

