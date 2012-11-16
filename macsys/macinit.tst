/*
 * $Source: BigRed:miner:source:macsys::RCS:macinit.c $
 * $Revision: 1.21 $
 * $Author: allender $
 * $Date: 1995/11/02 14:13:23 $
 *
 * $Log: macinit.c $
 * Revision 1.21  1995/11/02  14:13:23  allender
 * cd checking only on registered version
 *
 * Revision 1.20  1995/10/28  22:51:12  allender
 * #ifdef RELEASE for cd checking
 *
 * Revision 1.19  1995/10/28  22:22:39  allender
 * added stuff to check for Descent CD at startup
 *
 * Revision 1.18  1995/10/24  18:13:01  allender
 * do screen saver stuff
 *
 * Revision 1.17  1995/10/21  04:54:12  allender
 * low sounds and textures in virtual memory
 *
 * Revision 1.16  1995/10/20  00:10:07  allender
 * new memory stuff (only two possibilities), and fucking
 * correct checking of VM active
 *
 * Revision 1.15  1995/10/15  22:47:53  allender
 * call process_initial_events 4 times since I don't loop
 * there anymore
 *
 * Revision 1.14  1995/10/13  14:41:58  allender
 * tried hiding control strip on startup.  Code is commented
 * out because functions don't appear to exist anywhere
 *
 * Revision 1.13  1995/10/11  13:56:16  allender
 * removed a couple of functions that shouldn't be called here
 *
 * Revision 1.12  1995/10/05  08:57:28  allender
 * chedck to be sure GDevice is valid before performing close
 * operations (fixing up bbp and restoring clut)
 *
 * Revision 1.11  1995/09/18  08:45:00  allender
 * correctly restore device bitplane when done
 *
 * Revision 1.10  1995/09/18  08:11:13  allender
 * added memory stuff.  Descent should run in 5.5 w/VM on PPC
 * now.
 *
 * Revision 1.9  1995/09/13  09:31:18  allender
 * more memory stuff.  Put in mymkdir and mychdir functions
 * to account for some compilers not implementing the
 * normal functions
 *
 * Revision 1.8  1995/09/01  14:14:14  allender
 * determine in VM is on during init
 *
 * Revision 1.7  1995/08/08  14:22:00  allender
 * changed initialization code
 *
 * Revision 1.6  1995/07/17  09:08:49  allender
 * first attempt to change pixel depth of device
 *
 * Revision 1.5  1995/06/13  10:22:50  allender
 * overhauled screen manipulation stuff
 *
 * Revision 1.4  1995/06/12  11:12:18  allender
 * ifdef'ed qd global
 *
 * Revision 1.3  1995/05/11  13:02:02  allender
 * make define for stack size and change error message
 *
 * Revision 1.2  1995/05/04  20:06:10  allender
 * stack and heap handling -- needs work
 *
 * Revision 1.1  1995/04/07  13:20:32  allender
 * Initial revision
 *
*/

#include <stdio.h>
#include <Quickdraw.h>
#include <Palettes.h>
#include <Windows.h>
#include <Fonts.h>
#include <Menus.h>
#include <Dialogs.h>
#include <GestaltEqu.h>
#include <Events.h>
#include <Memory.h>
#include <OSUtils.h>
#include <LowMem.h>
#include <Balloons.h>
#include <ControlStrip.h>
#include <Files.h>
#include <Strings.h>
#include <TextUtils.h>

#include "dtypes.h"
#include "macsys.h"
#include "error.h"
#include "resource.h"
#include "direct.h"

static ubyte initialized = 0;
short SysEvtMask;
ubyte *win_storage;
ubyte have_virtual_memory;
ubyte use_sounds = 1;
ubyte use_alt_textures = 0;
byte help_balloons_active = 0;
byte control_strip_visible = 0;

#ifdef __powerc
#define MORE_STACK_SIZE 10000
#else
#define MORE_STACK_SIZE 150000
#endif

#ifndef __MWERKS__
QDGlobals qd;
#endif

extern void process_initial_events( void );

#define BASE_MEMORY		(1024 * 4000)
#define SOUND_LOW_MARK	(1024 * 806)
#define SOUND_HIGH_MARK	(1024 * 1360)
#define PIGGY_LOW_MARK	(1024 * 1500)
#define PIGGY_HIGH_MARK	(1024 * 2048)

#ifdef RELEASE
extern void CheckForCD();
#endif

void mac_close()
{
	if ( GameMonitor != NULL ) {
		if ( save_bbp != 8 ) 
			SetDepth(GameMonitor, save_bbp, gdDevType, 1);
		RestoreDeviceClut(GameMonitor);
	}
	if ( help_balloons_active )
		HMSetBalloons(1);
//	if ( control_strip_visible )
//		SBShowHideControlStrip(1);

	EnableScreenSavers();
		
	show_cursor();
	show_menubar();
	FlushEvents(everyEvent, 0);
}

//  routine for initialzing the macintosh world.  Nothing to do with
//  GWorlds or anything like that in this routine.  This is for all kinds
//  of initialization that the mac requires.

int mac_init(int hide_back, int hide_menu)
{
	Handle mbar;
	OSErr err;
	long qd_type, mem_type;
	int free_memory;
	short refnum;
	StringHandle shandle;
	Str255 dpath;

	if (initialized)
		return 0;
		
	InitGraf(&(qd.thePort));
	InitFonts();
	InitWindows();
	InitMenus();
	InitDialogs(nil);
	InitCursor();

#ifndef MAC_SHAREWARE
#if defined(RELEASE) && !defined(IOMEGA_OEM)
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
#endif
#endif

	MaxApplZone();
	MoreMasters();			// allocate 240 more master pointers (mainly for snd handles)
	MoreMasters();
	MoreMasters();
	MoreMasters();
	free_memory = FreeMem();
	if (free_memory < (1024 * 1024 * 7.5)) {
		use_sounds = 1;
		use_alt_textures = 1;
	} else {
		use_sounds = 2;
		use_alt_textures = 0;
	}
	
	help_balloons_active = HMGetBalloons();
	if (help_balloons_active)
		HMSetBalloons(0);
//	control_strip_visible = SBIsControlStripVisible();
//	if ( control_strip_visible )
//		SBShowHideControlStrip(0);

//  use the gestalt function to find out if we have 32bit quickdraw and offscreen
//  graphics worlds available.

	err = Gestalt(gestaltQuickdrawVersion, &qd_type);
	if (qd_type < gestalt32BitQD)
		return -1;						// don't have 32 bit quickdraw -- get outta here....
		
	DisableScreenSavers();

// set up event mask
	SysEvtMask = LMGetSysEvtMask();
	SetEventMask(0xffff);
	LMSetSysEvtMask(0xffff);
	
// set the flags for virtual memory on/off
	have_virtual_memory = 0;
	if(Gestalt(gestaltVMAttr, &mem_type) == noErr)
		if (mem_type & 0x1)		// bit 31 (MSBit) tells us if VM is on
			have_virtual_memory = 1;

	if (have_virtual_memory) {
		use_sounds = 1;
		use_alt_textures = 1;
	}
	
// set up the menubar

//	mbar = GetNewMBar(MENU_BAR_ID);
//	SetMenuBar(mbar);
//	DrawMenuBar();	
	
	win_storage = (ubyte *)malloc(sizeof(WindowRecord));

//  check for the existence of required directories:  :Players: and :Demos:
//  create them if they don't exist
	if (mychdir(":Players:")) {
		mymkdir(":Players:");
	} else
		mychdir("::");
	if (mychdir(":Demos:")) {
		mymkdir(":Demos:");
	} else
		mychdir("::");
		
// give some time to event handling to allow joystick and other things
//  to get setup before application fully runs

	process_initial_events();
	process_initial_events();
	process_initial_events();
	process_initial_events();

#ifndef MAC_SHAREWARE	
#ifdef RELEASE
	CheckForCD();
#endif
#endif
	
	atexit(mac_close);
	
	return 0;
}