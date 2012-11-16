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
 * $Source: Smoke:miner:source:macsys::RCS:macsys.h $
 * $Revision: 1.16 $
 * $Author: allender $
 * $Date: 1995/10/25 09:19:11 $
 *
 * $Log: macsys.h $
 * Revision 1.16  1995/10/25  09:19:11  allender
 * end file with newline to get rid of warnings on compile
 *
 * Revision 1.15  1995/10/23  10:46:06  allender
 * removed drv_num from GetDiskInserted
 *
 * Revision 1.14  1995/10/23  09:41:27  allender
 * changed param to GetDiskInserted to be drv_num
 *
 * Revision 1.13  1995/10/11  13:57:42  allender
 * added prototype for GetDiskInserted
 *
 * Revision 1.12  1995/09/24  11:00:11  allender
 * extern do_appl_quit function
 *
 * Revision 1.11  1995/09/19  10:38:02  allender
 * start of compatibility stuff...added function prototype
 *
 * Revision 1.10  1995/09/18  09:16:18  allender
 * added Compatibility_mode variable
 *
 * Revision 1.9  1995/09/15  13:43:32  allender
 * changed parameter to SavePictScreen
 *
 * Revision 1.8  1995/09/13  08:41:52  allender
 * added two variable to control memory usage
 *
 * Revision 1.7  1995/09/05  08:48:15  allender
 * added prefs header stuff
 *
 * Revision 1.6  1995/09/01  14:14:28  allender
 * have_virtual_memory global variable added
 *
 * Revision 1.5  1995/08/31  15:46:03  allender
 * new headers and stuff
 *
 * Revision 1.4  1995/07/10  20:39:59  allender
 * added save_bbp as extern
 *
 * Revision 1.3  1995/06/13  10:22:37  allender
 * overhauled screen manipulation stuff
 *
 * Revision 1.2  1995/06/13  09:08:29  allender
 * changed window init code -- now called from gr_init
 *
 * Revision 1.1  1995/04/07  13:19:04  allender
 * Initial revision
 *
*/

#ifndef _MAC_SYS
#define _MAC_SYS

#include <Types.h>
#include <Windows.h>
#include <QDOffscreen.h>

#include "gr.h"

// global defintions for the window and gworld on which the game is currently
// being played on and drawn to

extern WindowPtr GameWindow;		// window for the game
extern GWorldPtr GameGWorld;		// offscreen world for the game
extern GDHandle GameMonitor;		// device being used for the game
extern int MonitorRowBytes;			// row bytes for monitor being used
extern ubyte *MonitorData;			// pointer to screen data for monitor;
extern ubyte save_bbp;				// saved bbp for restore when game over
extern short SysEvtMask;			// saved system event mask
extern ubyte have_virtual_memory;	// is virtual memory turned on??
extern ubyte use_sounds;			// what type of sound usage
extern ubyte use_alt_textures;		// what type of texture usage
extern ubyte Compatibility_mode;	// use CopyBits for compatibility

extern int mac_init(int hide_backgroud, int hide_menubar);
extern int macwin_init();
extern void set_win_size(int x, int y, int w, int h);
extern void restore_device_clut();		// restore the CLUT to the original setting

// functions for event handling
void do_event_loop();

// functions for hiding and showing the mouse
extern void hide_cursor();
extern void show_cursor();

// functions for blitting to the window
#define bitblt_to_screen() ((void)0)
//extern void direct_to_screen();
//extern void copybits_to_screen();
// functions for hiding and showing the menubar
extern void hide_menubar();
extern void show_menubar();

// functions for hiding and showing the background
extern void black_window();
extern void hide_background();
extern void hide_foreground();

// functions for preference files
extern void InitPrefsFile(OSType creator);
extern OSErr LoadPrefsFile(Handle prefsHdl);
extern OSErr SavePrefsFile(Handle prefHdl);

// screen shot saver
extern void SavePictScreen(int multiplayer);

// functions for offscreen compatibility stuff
extern grs_canvas *mac_get_gworld_data( int w, int h );

// global function that will quit application
extern void do_appl_quit( void );

extern int GetDiskInserted( void );

#endif
