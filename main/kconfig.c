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
 * $Source: Smoke:miner:source:main::RCS:kconfig.c $
 * $Revision: 1.18 $
 * $Author: allender $
 * $Date: 1995/10/29 20:14:10 $
 * 
 * Routines to configure keyboard, joystick, etc..
 * 
 * $Log: kconfig.c $
 * Revision 1.18  1995/10/29  20:14:10  allender
 * don't read mouse 30x/sec.  Still causes problems -- left with
 * exposure at > 60 frame/s
 *
 * Revision 1.17  1995/10/27  14:16:35  allender
 * don't set lastreadtime when doing mouse stuff if we didn't
 * read mouse this frame
 *
 * Revision 1.16  1995/10/24  18:10:22  allender
 * get mouse stuff working right this time?
 *
 * Revision 1.15  1995/10/23  14:50:50  allender
 * corrected values for control type in kc_set_controls
 *
 * Revision 1.14  1995/10/21  16:36:54  allender
 * fix up mouse read time
 *
 * Revision 1.13  1995/10/20  00:46:53  allender
 * fix up mouse reading problem
 *
 * Revision 1.12  1995/10/19  13:36:38  allender
 * mouse support in kconfig screens
 *
 * Revision 1.11  1995/10/18  21:06:06  allender
 * removed Int3 in cruise stuff -- was in there for debugging and
 * now not needed
 *
 * Revision 1.10  1995/10/17  13:12:47  allender
 * fixed config menus so buttons don't get configured
 *
 * Revision 1.9  1995/10/15  23:07:55  allender
 * added return key as second button for primary fire
 *
 * Revision 1.8  1995/09/05  08:49:47  allender
 * change 'PADRTN' label to 'ENTER'
 *
 * Revision 1.7  1995/09/01  15:38:22  allender
 * took out cap of reading controls max 25 times/sec
 *
 * Revision 1.6  1995/09/01  13:33:59  allender
 * erase all old text
 *
 * Revision 1.5  1995/08/18  10:20:55  allender
 * keep controls reading to 25 times/s max so fast
 * frame rates don't mess up control reading
 *
 * Revision 1.4  1995/07/28  15:43:13  allender
 * make mousebutton control primary fire
 *
 * Revision 1.3  1995/07/26  17:04:32  allender
 * new defaults and make joystick main button work correctly
 *
 * Revision 1.2  1995/07/17  08:51:03  allender
 * fixed up configuration menus to look right
 *
 * Revision 1.1  1995/05/16  15:26:56  allender
 * Initial revision
 *
 * Revision 2.7  1995/03/30  16:36:56  mike
 * text localization.
 * 
 * Revision 2.6  1995/03/21  14:39:31  john
 * Ifdef'd out the NETWORK code.
 * 
 * Revision 2.5  1995/03/16  10:53:07  john
 * Move VFX center to Shift+Z instead of Enter because
 * it conflicted with toggling HUD on/off.
 * 
 * Revision 2.4  1995/03/10  13:47:24  john
 * Added head tracking sensitivity.
 * 
 * Revision 2.3  1995/03/09  18:07:06  john
 * Fixed bug with iglasses tracking not "centering" right.
 * Made VFX have bright headlight lighting.
 * 
 * Revision 2.2  1995/03/08  15:32:39  john
 * Made VictorMaxx head tracking use Greenleaf code.
 * 
 * Revision 2.1  1995/03/06  15:23:31  john
 * New screen techniques.
 * 
 * Revision 2.0  1995/02/27  11:29:26  john
 * New version 2.0, which has no anonymous unions, builds with
 * Watcom 10.0, and doesn't require parsing BITMAPS.TBL.
 * 
 * Revision 1.105  1995/02/22  14:11:58  allender
 * remove anonymous unions from object structure
 * 
 * Revision 1.104  1995/02/13  12:01:56  john
 * Fixed bug with buggin not mmaking player faster.
 * 
 * Revision 1.103  1995/02/09  22:00:46  john
 * Added i-glasses tracking.
 * 
 * Revision 1.102  1995/01/24  21:25:47  john
 * Fixed bug with slide/bank on not working with
 * Cyberman heading.,
 * 
 * Revision 1.101  1995/01/24  16:09:56  john
 * Fixed bug with Wingman extreme customize text overwriting title.
 * 
 * Revision 1.100  1995/01/24  12:37:46  john
 * Made Esc exit key define menu.
 * 
 * Revision 1.99  1995/01/23  23:54:43  matt
 * Made keypad enter work
 * 
 * Revision 1.98  1995/01/23  16:42:00  john
 * Made the external controls always turn banking off, leveling off
 * and passed automap state thru to the tsr.
 * 
 * Revision 1.97  1995/01/12  11:41:33  john
 * Added external control reading.
 * 
 * Revision 1.96  1995/01/05  10:43:58  mike
 * Handle case when timer_get_fixed_seconds() goes negative.  Happens at 9.1
 * hours.  Previously, joystick would stop functioning.  Now will work.
 * 
 * Revision 1.95  1994/12/29  11:17:38  john
 * Took out some warnings and mprintf.
 * 
 * Revision 1.94  1994/12/29  11:07:41  john
 * Fixed Thrustmaster and Logitech Wingman extreme
 * Hat by reading the y2 axis during the center stage
 * of the calibration, and using 75, 50, 27, and 3 %
 * as values for the 4 positions.
 * 
 * Revision 1.93  1994/12/27  12:16:20  john
 * Fixed bug with slide on not working with joystick or mouse buttons.
 * 
 * Revision 1.92  1994/12/20  10:34:15  john
 * Made sensitivity work for mouse & joystick and made
 * it only affect, pitch, heading, and roll.
 * 
 * Revision 1.91  1994/12/16  00:11:23  matt
 * Made delete key act normally when debug out
 * 
 * Revision 1.90  1994/12/14  17:41:15  john
 * Added more buttons so that  Yoke would work.
 * 
 * Revision 1.89  1994/12/13  17:25:35  allender
 * Added Assert for bogus time for joystick reading.
 * 
 * Revision 1.88  1994/12/13  14:48:01  john
 * Took out some debugging mprintf's
 * 
 * 
 * Revision 1.87  1994/12/13  14:43:02  john
 * Took out the code in kconfig to build direction array.
 * Called kc_set_controls after selecting a new control type.
 * 
 * Revision 1.86  1994/12/13  01:11:32  john
 * Fixed bug with message clearing overwriting 
 * right border.
 * 
 * Revision 1.85  1994/12/12  00:35:58  john
 * Added or thing for keys.
 * 
 * Revision 1.84  1994/12/09  17:08:06  john
 * Made mouse a bit less sensitive.
 * 
 * Revision 1.83  1994/12/09  16:04:00  john
 * Increased mouse sensitivity.
 * 
 * Revision 1.82  1994/12/09  00:41:26  mike
 * fix hang in automap print screen
 * 
 * Revision 1.81  1994/12/08  11:50:37  john
 * Made strcpy only copy corect number of chars,.
 * 
 * Revision 1.80  1994/12/07  16:16:06  john
 * Added command to check to see if a joystick axes has been used.
 * 
 * Revision 1.79  1994/12/07  14:52:28  yuan
 * Localization 492
 * 
 * Revision 1.78  1994/12/07  13:37:40  john
 * Made the joystick thrust work in reverse.
 * 
 * Revision 1.77  1994/12/07  11:28:24  matt
 * Did a little localization support
 * 
 * Revision 1.76  1994/12/04  12:30:03  john
 * Made the Thrustmaster stick read every frame, not every 10 frames,
 * because it uses analog axis as buttons.
 * 
 * Revision 1.75  1994/12/03  22:35:25  yuan
 * Localization 412
 * 
 * Revision 1.74  1994/12/03  15:39:24  john
 * Made numeric keypad move in conifg.
 * 
 * Revision 1.73  1994/12/01  16:23:39  john
 * Fixed include mistake.
 * 
 * Revision 1.72  1994/12/01  16:07:57  john
 * Fixed bug that disabled joystick in automap because it used gametime, which is
 * paused during automap. Fixed be used timer_Get_fixed_seconds instead of GameTime.
 * 
 * Revision 1.71  1994/12/01  12:30:49  john
 * Made Ctrl+D delete, not Ctrl+E
 * 
 * Revision 1.70  1994/12/01  11:52:52  john
 * Added default values for GamePad.
 * 
 * Revision 1.69  1994/11/30  00:59:12  mike
 * optimizations.
 * 
 * Revision 1.68  1994/11/29  03:45:50  john
 * Added joystick sensitivity; Added sound channels to detail menu.  Removed -maxchannels
 * command line arg.
 * 
 * Revision 1.67  1994/11/27  23:13:44  matt
 * Made changes for new mprintf calling convention
 * 
 * Revision 1.66  1994/11/27  19:52:12  matt
 * Made screen shots work in a few more places
 * 
 * Revision 1.65  1994/11/22  16:54:50  mike
 * autorepeat on missiles.
 * 
 * Revision 1.64  1994/11/21  11:16:17  rob
 * Changed calls to GameLoop to calls to multi_menu_poll and changed
 * conditions under which they are called.
 * 
 * Revision 1.63  1994/11/19  15:14:48  mike
 * remove unused code and data
 * 
 * Revision 1.62  1994/11/18  23:37:56  john
 * Changed some shorts to ints.
 * 
 * Revision 1.61  1994/11/17  13:36:35  rob
 * Added better network hook in kconfig menu.
 * 
 * Revision 1.60  1994/11/14  20:09:13  john
 * Made Tab be default for automap.
 * 
 * Revision 1.59  1994/11/13  16:34:07  matt
 * Fixed victormaxx angle conversions
 * 
 * Revision 1.58  1994/11/12  14:47:05  john
 * Added support for victor head tracking.
 * 
 * Revision 1.57  1994/11/08  15:14:55  john
 * Added more calls so net doesn't die in net game.
 * 
 * Revision 1.56  1994/11/07  14:01:07  john
 * Changed the gamma correction sequencing.
 * 
 * Revision 1.55  1994/11/01  16:40:08  john
 * Added Gamma correction.
 * 
 * Revision 1.54  1994/10/25  23:09:26  john
 * Made the automap key configurable.
 * 
 * Revision 1.53  1994/10/25  13:11:59  john
 * Made keys the way Adam speced 'em for final game.
 * 
 * Revision 1.52  1994/10/24  17:44:22  john
 * Added stereo channel reversing.
 * 
 * Revision 1.51  1994/10/22  13:23:18  john
 * Made default rear view key be R.
 * 
 * Revision 1.50  1994/10/22  13:20:09  john
 * Took out toggle primary/secondary weapons.  Fixed black
 * background for 'axes' and 'buttons' text.
 * 
 * Revision 1.49  1994/10/21  15:20:15  john
 * Made PrtScr do screen dump, not F2.
 * 
 * Revision 1.48  1994/10/21  13:41:36  john
 * Allowed F2 to screen dump.
 * 
 * Revision 1.47  1994/10/17  13:07:05  john
 * Moved the descent.cfg info into the player config file.
 * 
 * Revision 1.46  1994/10/14  15:30:22  john
 * Added Cyberman default positions.
 * 
 * Revision 1.45  1994/10/14  15:24:54  john
 * Made Cyberman work with config.
 * 
 * Revision 1.44  1994/10/14  12:46:04  john
 * Added the ability to reset all to default.
 * 
 * Revision 1.43  1994/10/14  12:18:31  john
 * Made mouse invert axis always be 0 or 1.
 * 
 * Revision 1.42  1994/10/14  12:16:03  john
 * Changed code so that by doing DEL+F12 saves the current kconfig
 * values as default. Added support for drop_bomb key.  Took out
 * unused slots for keyboard.  Made keyboard use control_type of 0
 * save slots.
 * 
 * Revision 1.41  1994/10/13  21:27:02  john
 * Made axis invert value always be 0 or 1.
n * 
 * Revision 1.40  1994/10/13  20:18:15  john
 * Added some more system keys, such as F? and CAPSLOCK.
 * 
 * Revision 1.39  1994/10/13  19:22:29  john
 * Added separate config saves for different devices.
 * Made all the devices work together better, such as mice won't
 * get read when you're playing with the joystick.
 * 
 * Revision 1.38  1994/10/13  15:41:57  mike
 * Remove afterburner.
 * 
 */


#pragma off (unreferenced)
static char rcsid[] = "$Id: kconfig.c 1.18 1995/10/29 20:14:10 allender Exp $";
#pragma on (unreferenced)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include <dos.h>
//#include <io.h>
#include <stdarg.h>
#include <ctype.h>


#include "error.h"
#include "dtypes.h"
#include "gr.h"
#include "mono.h"
#include "key.h"
#include "palette.h"
#include "game.h"
#include "gamefont.h"
#include "iff.h"
#include "mem.h"
#include "joy.h"
#include "mouse.h"
#include "kconfig.h"
#include "gauges.h"
#include "joydefs.h"
#include "vfx1.h"
#include "render.h"
#include "arcade.h"
#include "digi.h"
#include "newmenu.h"
#include "victor.h"
#include "endlevel.h"
#include "multi.h"
#include "timer.h"
#include "text.h"
#include "player.h"
#include "menu.h"
#include "iglasses.h"
#include "gtimer.h"
#include "macsys.h"

#define TABLE_CREATION 1

int     sense_function1=0;	
int	  vfx1_installed=0;
int     SenseStatus1( void );

// Array used to 'blink' the cursor while waiting for a keypress.
byte fades[64] = { 1,1,1,2,2,3,4,4,5,6,8,9,10,12,13,15,16,17,19,20,22,23,24,26,27,28,28,29,30,30,31,31,31,31,31,30,30,29,28,28,27,26,24,23,22,20,19,17,16,15,13,12,10,9,8,6,5,4,4,3,2,2,1,1 };

//char * invert_text[2] = { "N", "Y" };
//char * joybutton_text[28] = { "BTN 1", "BTN 2", "BTN 3", "BTN 4", "", "TRIG", "LEFT", "HAT Å", "RIGHT", "", "", "HAT Ä", "MID", "", "", "HAT ", "", "", "", "HAT Ç", "TRIG", "LEFT", "RIGHT", "", "UP","DOWN","LEFT", "RIGHT" };
//char * joyaxis_text[4] = { "X1", "Y1", "X2", "Y2" };
//char * mouseaxis_text[2] = { "L/R", "F/B" };
//char * mousebutton_text[3] = { "Left", "Right", "Mid" };

int invert_text[2] = { TNUM_N, TNUM_Y };
int joybutton_text[28] = 
{ TNUM_BTN_1, TNUM_BTN_2, TNUM_BTN_3, TNUM_BTN_4,
  -1, TNUM_TRIG, TNUM_LEFT, TNUM_HAT_L,
 TNUM_RIGHT, -1, TNUM_HAT2_D, TNUM_HAT_R,
 TNUM_MID, -1, TNUM_HAT2_R, TNUM_HAT_U,
 TNUM_HAT2_L, -1, TNUM_HAT2_U, TNUM_HAT_D,
 TNUM_TRIG, TNUM_LEFT, TNUM_RIGHT, -1, 
  TNUM_UP, TNUM_DOWN, TNUM_LEFT, TNUM_RIGHT };
int joyaxis_text[4] = { TNUM_X1, TNUM_Y1, TNUM_X2, TNUM_Y2 };
int mouseaxis_text[2] = { TNUM_L_R, TNUM_F_B };
int mousebutton_text[3] = { TNUM_LEFT, TNUM_RIGHT, TNUM_MID };

char * key_text[256] = {         
"","S","D","F","H","G","Z","X","C","V","","B","Q", "W", "E", "R",
"Y","T","1","2","3","4","6","5","=","9","7","-", "8", "0", "]", "O",
"U","[","I","P","RET","L","J","'","K", ";", "\\", ",", "/", "N", "M", ".",
"TAB","SPC","`","DEL","","ESC","","APL","SHIFT","CAPSL","OPTN","CTRL","","","","A",
"","PAD.","","PAD*","","PAD+","","NMLCK","","","","PAD/","ENTER","","PAD-","",
"","PAD=","PAD0","PAD1","PAD2","PAD3","PAD4","PAD5","PAD6","PAD7","","PAD8","PAD9","","","",
"F5","F6","F7","","F8","F9","","F11","","F13","","F14","","F10","","F12",
"","PAUSE","HELP","HOME","PGUP","DEL","","END","F2","","F1","LARW","RARW","DARW","UARW","",
"","","","","","","","","","","","","","","","",
"","","","","","","","","","","","","","","","",
"","","","","","","","","","","","","","","","",
"","","","","","","","","","","","","","","","",
"","","","","","","","","","","","","","","","",
"","","","","","","","","","","","","","","","",
"","","","","","","","","","","","","","","","",
"","","","","","","","","","","","","","","",""};

ubyte system_keys[] = { KEY_ESC, KEY_F1, KEY_F2, KEY_F3, KEY_F4, KEY_F5, KEY_F6, KEY_F7, KEY_F8, KEY_F9, KEY_F10, KEY_F11, KEY_F12, KEY_0, KEY_1, KEY_2, KEY_3, KEY_4, KEY_5, KEY_6, KEY_7, KEY_8, KEY_9, KEY_0, KEY_MINUS, KEY_EQUAL, KEY_PRINT_SCREEN };

//extern void GameLoop(int, int );

control_info Controls;

ubyte Config_digi_volume = 16;
ubyte Config_midi_volume = 16;
ubyte Config_control_type = 0;
ubyte Config_channels_reversed = 0;
ubyte Config_joystick_sensitivity = 8;

fix Cruise_speed=0;

#define BT_KEY 				0
#define BT_MOUSE_BUTTON 	1
#define BT_MOUSE_AXIS		2
#define BT_JOY_BUTTON 		3
#define BT_JOY_AXIS			4
#define BT_INVERT				5

char *btype_text[] = { "BT_KEY", "BT_MOUSE_BUTTON", "BT_MOUSE_AXIS", "BT_JOY_BUTTON", "BT_JOY_AXIS", "BT_INVERT" };

#define INFO_Y 56

typedef struct kc_item {
	short id;				// The id of this item
	short x, y;				
	short w1;
	short w2;
	short u,d,l,r;
	short text_num1;
	ubyte type;
	ubyte value;		// what key,button,etc
} kc_item;

int Num_items=23;
kc_item *All_items;

ubyte kconfig_settings[CONTROL_MAX_TYPES][MAX_CONTROLS];

//----------- WARNING!!!!!!! -------------------------------------------
// THESE NEXT FOUR BLOCKS OF DATA ARE GENERATED BY PRESSING DEL+F12 WHEN
// IN THE KEYBOARD CONFIG SCREEN.  BASICALLY, THAT PROCEDURE MODIFIES THE
// U,D,L,R FIELDS OF THE ARRAYS AND DUMPS THE NEW ARRAYS INTO KCONFIG.COD
//-------------------------------------------------------------------------
ubyte default_kconfig_settings[CONTROL_MAX_TYPES][MAX_CONTROLS] = {
{0x7e,0x5b,0x7d,0x54,0x7b,0x56,0x7c,0x58,0x3a,0xff,0xff,0x53,0xff,0x55,0xff,0x4e,0xff,0x45,0xff,0xff,0xc,0x59,0xe,0x5c,0x3b,0x24,0x31,0xff,0x3,0xff,0x3f,0xff,0x6,0xff,0xb,0xff,0xf,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x30,0xff,0xff,0xff,0xff,0xff},
{0x0,0x1,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x1,0x0,0x0,0x0,0xff,0x0,0xff,0x0,0xff,0x0,0xff,0x0,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff},
{0x5,0xc,0xff,0xff,0xff,0xff,0x7,0xf,0x13,0xb,0xff,0x6,0x8,0x1,0x0,0x0,0x0,0xff,0x0,0xff,0x0,0xff,0x0,0xff,0x0,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x0,0xff,0xff,0xff},
{0x0,0x1,0xff,0xff,0x2,0xff,0x7,0xf,0x13,0xb,0xff,0xff,0xff,0x1,0x0,0x0,0x0,0xff,0x0,0xff,0x0,0xff,0x0,0xff,0x0,0xff,0x3,0xff,0x3,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff},
{0x3,0x0,0x1,0x2,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x1,0x0,0x0,0x0,0xff,0x0,0xff,0x0,0xff,0x0,0xff,0x0,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff},
{0x0,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x1,0x0,0x0,0x0,0xff,0x0,0xff,0x0,0xff,0x0,0xff,0x0,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff},
{0x0,0x1,0xff,0xff,0x2,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x0,0xff,0x0,0xff,0x0,0xff,0x0,0xff,0x0,0xff,0x0,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff},
};

kc_item kc_keyboard[NUM_KEY_CONTROLS] = {
	{  0, 30, 98,142, 52, 43,  2, 23,  1,378,   0, 255 },
	{  1, 30, 98,200, 52, 22,  3,  0, 24,378,   0, 255 },
	{  2, 30,114,142, 52,  0,  4, 25,  3,379,   0, 255 },
	{  3, 30,114,200, 52,  1,  5,  2, 26,379,   0, 255 },
	{  4, 30,130,142, 52,  2,  6, 27,  5,380,   0, 255 },
	{  5, 30,130,200, 52,  3,  7,  4, 28,380,   0, 255 },
	{  6, 30,146,142, 52,  4,  8, 29,  7,381,   0, 255 },
	{  7, 30,146,200, 52,  5,  9,  6, 34,381,   0, 255 },
	{  8, 30,170,142, 52,  6, 10, 35,  9,382,   0, 255 },
	{  9, 30,170,200, 52,  7, 11,  8, 36,382,   0, 255 },
	{ 10, 30,186,142, 52,  8, 12, 37, 11,383,   0, 255 },
	{ 11, 30,186,200, 52,  9, 13, 10, 44,383,   0, 255 },
	{ 12, 30,202,142, 52, 10, 14, 45, 13,384,   0, 255 },
	{ 13, 30,202,200, 52, 11, 15, 12, 30,384,   0, 255 },
	{ 14, 30,218,142, 52, 12, 16, 31, 15,385,   0, 255 },
	{ 15, 30,218,200, 52, 13, 17, 14, 32,385,   0, 255 },
	{ 16, 30,234,142, 52, 14, 18, 33, 17,386,   0, 255 },
	{ 17, 30,234,200, 52, 15, 19, 16, 38,386,   0, 255 },
	{ 18, 30,258,142, 52, 16, 20, 39, 19,387,   0, 255 },
	{ 19, 30,258,200, 52, 17, 21, 18, 40,387,   0, 255 },
	{ 20, 30,274,142, 52, 18, 22, 41, 21,388,   0, 255 },
	{ 21, 30,274,200, 52, 19, 23, 20, 42,388,   0, 255 },
	{ 22, 30,290,142, 52, 20,  1, 43, 23,389,   0, 255 },
	{ 23, 30,290,200, 52, 21, 24, 22,  0,389,   0, 255 },
	{ 24,316, 98,166, 52, 23, 26,  1, 25,390,   0, 255 },
	{ 25,316, 98,224, 52, 42, 27, 24,  2,390,   0, 255 },
	{ 26,316,114,166, 52, 24, 28,  3, 27,391,   0, 255 },
	{ 27,316,114,224, 52, 25, 29, 26,  4,391,   0, 255 },
	{ 28,316,130,166, 52, 26, 34,  5, 29,392,   0, 255 },
	{ 29,316,130,224, 52, 27, 35, 28,  6,392,   0, 255 },
	{ 30,316,210,166, 52, 44, 32, 13, 31,393,   0, 255 },
	{ 31,316,210,224, 52, 45, 33, 30, 14,393,   0, 255 },
	{ 32,316,226,166, 52, 30, 38, 15, 33,394,   0, 255 },
	{ 33,316,226,224, 52, 31, 39, 32, 16,394,   0, 255 },
	{ 34,316,146,166, 52, 28, 36,  7, 35,395,   0, 255 },
	{ 35,316,146,224, 52, 29, 37, 34,  8,395,   0, 255 },
	{ 36,316,170,166, 52, 34, 44,  9, 37,311,   0, 255 },
	{ 37,316,170,224, 52, 35, 45, 36, 10,311,   0, 255 },
	{ 38,316,250,166, 52, 32, 40, 17, 39,396,   0, 255 },
	{ 39,316,250,224, 52, 33, 41, 38, 18,396,   0, 255 },
	{ 40,316,266,166, 52, 38, 42, 19, 41,397,   0, 255 },
	{ 41,316,266,224, 52, 39, 43, 40, 20,397,   0, 255 },
	{ 42,316,282,166, 52, 40, 25, 21, 43,398,   0, 255 },
	{ 43,316,282,224, 52, 41,  0, 42, 22,398,   0, 255 },
	{ 44,316,186,166, 52, 36, 30, 11, 45,374,   0, 255 },
	{ 45,316,186,224, 52, 37, 31, 44, 12,374,   0, 255 },
};
kc_item kc_joystick[NUM_OTHER_CONTROLS] = {
	{  0, 50, 92,170, 52, 15,  1, 24,  5,390,   3, 255 },
	{  1, 50,108,170, 52,  0,  4,  5,  6,391,   3, 255 },
	{  2, 50,170,170, 52, 26,  3,  9, 10,393,   3, 255 },
	{  3, 50,186,170, 52,  2, 25, 10, 11,394,   3, 255 },
	{  4, 50,124,170, 52,  1, 26,  6,  7,392,   3, 255 },
	{  5,360, 92,118, 52, 23,  6,  0,  1,382,   3, 255 },
	{  6,360,108,118, 52,  5,  7,  1,  4,383,   3, 255 },
	{  7,360,124,118, 52,  6,  8,  4, 26,384,   3, 255 },
	{  8,360,140,118, 52,  7,  9, 26,  9,385,   3, 255 },
	{  9,360,156,118, 52,  8, 10,  8,  2,386,   3, 255 },
	{ 10,360,180,118, 52,  9, 11,  2,  3,387,   3, 255 },
	{ 11,360,196,118, 52, 10, 12,  3, 12,388,   3, 255 },
	{ 12,360,212,118, 52, 11, 18, 11, 25,389,   3, 255 },
	{ 13, 44,292,102, 52, 24, 15, 25, 14,399,   4, 255 },
	{ 14, 44,292,198, 16, 25, 16, 13, 17,399,   5, 255 },
	{ 15, 44,308,102, 52, 13,  0, 18, 16,400,   4, 255 },
	{ 16, 44,308,198, 16, 14, 17, 15, 19,400,   5, 255 },
	{ 17,328,292,116, 52, 16, 19, 14, 18,401,   4, 255 },
	{ 18,328,292,212, 16, 12, 20, 17, 15,401,   5, 255 },
	{ 19,328,308,116, 52, 17, 21, 16, 20,402,   4, 255 },
	{ 20,328,308,212, 16, 18, 22, 19, 21,402,   5, 255 },
	{ 21,328,324,116, 52, 19, 23, 20, 22,403,   4, 255 },
	{ 22,328,324,212, 16, 20, 24, 21, 23,403,   5, 255 },
	{ 23,328,348,116, 52, 21,  5, 22, 24,404,   4, 255 },
	{ 24,328,348,212, 16, 22, 13, 23,  0,404,   5, 255 },
	{ 25, 50,218,170, 52,  3, 14, 12, 13,311,   3, 255 },
	{ 26, 50,140,170, 52,  4,  2,  7,  8,395,   3, 255 },
};
kc_item kc_mouse[NUM_OTHER_CONTROLS] = {
	{  0, 50, 92,170, 52, 12,  1, 24,  5,390,  1, 255 },
	{  1, 50,108,170, 52,  0,  4,  5,  6,391,  1, 255 },
	{  2, 50,170,170, 52, 26,  3,  9, 10,393,  1, 255 },
	{  3, 50,186,170, 52,  2, 25, 10, 11,394,  1, 255 },
	{  4, 50,124,170, 52,  1, 26,  6,  7,392,  1, 255 },
	{  5,360, 92,118, 52, 24,  6,  0,  1,382,  1, 255 },
	{  6,360,108,118, 52,  5,  7,  1,  4,383,  1, 255 },
	{  7,360,124,118, 52,  6,  8,  4, 26,384,  1, 255 },
	{  8,360,140,118, 52,  7,  9, 26,  9,385,  1, 255 },
	{  9,360,156,118, 52,  8, 10,  8,  2,386,  1, 255 },
	{ 10,360,180,118, 52,  9, 11,  2,  3,387,  1, 255 },
	{ 11,360,196,118, 52, 10, 12,  3, 12,388,  1, 255 },
	{ 12,360,212,118, 52, 11,  0, 11, 25,389,  1, 255 },
	{ 13,206,276,116, 52, 25, 15, 25, 14,399,  2, 255 },
	{ 14,206,276,212, 16, 23, 16, 13, 15,399,  5, 255 },
	{ 15,206,292,116, 52, 13, 17, 14, 16,400,  2, 255 },
	{ 16,206,292,212, 16, 14, 18, 15, 17,400,  5, 255 },
	{ 17,206,308,116, 52, 15, 19, 16, 18,401,  2, 255 },
	{ 18,206,308,212, 16, 16, 20, 17, 19,401,  5, 255 },
	{ 19,206,324,116, 52, 17, 21, 18, 20,402,  2, 255 },
	{ 20,206,324,212, 16, 18, 22, 19, 21,402,  5, 255 },
	{ 21,206,340,116, 52, 19, 23, 20, 22,403,  2, 255 },
	{ 22,206,340,212, 16, 20, 24, 21, 23,403,  5, 255 },
	{ 23,206,364,116, 52, 21, 14, 22, 24,404,  2, 255 },
	{ 24,206,364,212, 16, 22,  5, 23,  0,404,  5, 255 },
	{ 25, 50,218,170, 52,  3, 13, 12, 13,311,  1, 255 },
	{ 26, 50,140,170, 52,  4,  2,  7,  8,395,  1, 255 },
};

int kconfig_is_axes_used(int axis)
{
	int i;
	for (i=0; i<NUM_OTHER_CONTROLS; i++ )	{
		if (( kc_joystick[i].type == BT_JOY_AXIS ) && (kc_joystick[i].value == axis ))
			return 1;
	}
	return 0;
}

#ifdef TABLE_CREATION
int find_item_at( kc_item * items, int nitems, int x, int y )
{
	int i;
	
	for (i=0; i<nitems; i++ )	{
		if ( ((items[i].x+items[i].w1)==x) && (items[i].y==y))
			return i;
	}
	return -1;
}

int find_next_item_up( kc_item * items, int nitems, int citem )
{
	int x, y, i;

	y = items[citem].y;
	x = items[citem].x+items[citem].w1;
	
	do {	
		y--;
		if ( y < 0 ) {
			y = grd_curcanv->cv_bitmap.bm_h-1;
			x--;
			if ( x < 0 ) {
				x = grd_curcanv->cv_bitmap.bm_w-1;
			}
		}
		i = find_item_at( items, nitems, x, y );
	} while ( i < 0 );
	
	return i;
}

int find_next_item_down( kc_item * items, int nitems, int citem )
{
	int x, y, i;

	y = items[citem].y;
	x = items[citem].x+items[citem].w1;
	
	do {	
		y++;
		if ( y > grd_curcanv->cv_bitmap.bm_h-1 ) {
			y = 0;
			x++;
			if ( x > grd_curcanv->cv_bitmap.bm_w-1 ) {
				x = 0;
			}
		}
		i = find_item_at( items, nitems, x, y );
	} while ( i < 0 );
	
	return i;
}

int find_next_item_right( kc_item * items, int nitems, int citem )
{
	int x, y, i;

	y = items[citem].y;
	x = items[citem].x+items[citem].w1;
	
	do {	
		x++;
		if ( x > grd_curcanv->cv_bitmap.bm_w-1 ) {
			x = 0;
			y++;
			if ( y > grd_curcanv->cv_bitmap.bm_h-1 ) {
				y = 0;
			}
		}
		i = find_item_at( items, nitems, x, y );
	} while ( i < 0 );
	
	return i;
}

int find_next_item_left( kc_item * items, int nitems, int citem )
{
	int x, y, i;

	y = items[citem].y;
	x = items[citem].x+items[citem].w1;
	
	do {	
		x--;
		if ( x < 0 ) {
			x = grd_curcanv->cv_bitmap.bm_w-1;
			y--;
			if ( y < 0 ) {
				y = grd_curcanv->cv_bitmap.bm_h-1;
			}
		}
		i = find_item_at( items, nitems, x, y );
	} while ( i < 0 );
	
	return i;
}
#endif

void kc_drawitem( kc_item *item, int is_current )
{
	int x, w, h, aw;
	char btext[10];

	if (is_current)
		gr_set_fontcolor( BM_XRGB(20,20,29), -1 );
	else
		gr_set_fontcolor( BM_XRGB(15,15,24), -1 );

	if (item->type == BT_KEY)
		gr_string( item->x, item->y, Text_string[item->text_num1] );
	else if ( (item->type == BT_JOY_AXIS) || (item->type == BT_MOUSE_AXIS) || (item->type == BT_INVERT) )
		gr_string( item->x, item->y - 164, Text_string[item->text_num1] );

	if (item->value==255) {
		sprintf( btext, "" );
	} else {
		switch( item->type )	{
			case BT_KEY:
				strncpy( btext, key_text[item->value], 10 ); break;
			case BT_MOUSE_BUTTON:
				strncpy( btext, Text_string[mousebutton_text[item->value]], 10 ); break;
			case BT_MOUSE_AXIS:
				strncpy( btext, Text_string[mouseaxis_text[item->value]], 10 ); break;
			case BT_JOY_BUTTON:
				if ( joybutton_text[item->value] !=-1 )
					strncpy( btext, Text_string[ joybutton_text[item->value]  ], 10 );
				else
					sprintf( btext, "BTN%d", item->value );
				break;
			case BT_JOY_AXIS:
				strncpy( btext, Text_string[joyaxis_text[item->value]], 10 ); break;
			case BT_INVERT:
				strncpy( btext, Text_string[invert_text[item->value]], 10 ); break;
		}
	}
	gr_get_string_size(btext, &w, &h, &aw  );

	if (is_current)
		gr_setcolor( BM_XRGB(21,0,24) );
	else
		gr_setcolor( BM_XRGB(16,0,19) );
	if (item->type == BT_KEY)
		gr_urect( item->w1+item->x, item->y-1, item->w1+item->x+item->w2, item->y+h );
	else if ( (item->type == BT_JOY_AXIS) || (item->type == BT_MOUSE_AXIS) || (item->type == BT_INVERT) )
		gr_urect( item->w1+item->x, item->y-1 - 164, item->w1+item->x+item->w2, item->y+h-164 );
	
	gr_set_fontcolor( BM_XRGB(28,28,28), -1 );

	x = item->w1+item->x+((item->w2-w)/2);

	if ( item->type == BT_KEY )
		gr_string( x, item->y, btext );
	else if ( (item->type == BT_JOY_AXIS) || (item->type == BT_MOUSE_AXIS) || (item->type == BT_INVERT) )
		gr_string(x, item->y - 164, btext);
}

static int looper=0;

void kc_drawquestion( kc_item *item )
{
	int c, x, w, h, aw;
	
	gr_get_string_size("?", &w, &h, &aw  );

	c = BM_XRGB(21,0,24);

	gr_setcolor( gr_fade_table[fades[looper]*256+c] );
	looper++;
	if (looper>63) looper=0;

//	gr_urect( item->w1+item->x, item->y-1, item->w1+item->x+item->w2, item->y+h );
	
	if (item->type == BT_KEY)
		gr_urect( item->w1+item->x, item->y-1, item->w1+item->x+item->w2, item->y+h );
	else if ( (item->type == BT_JOY_AXIS) || (item->type == BT_MOUSE_AXIS) || (item->type == BT_JOY_AXIS) )
		gr_urect( item->w1+item->x, item->y-1 - 164, item->w1+item->x+item->w2, item->y+h-164 );

	gr_set_fontcolor( BM_XRGB(28,28,28), -1 );

	x = item->w1+item->x+((item->w2-w)/2);

//	gr_string( x, item->y, "?" );

	if ( item->type == BT_KEY )
		gr_string( x, item->y, "?" );
	else if ( (item->type == BT_JOY_AXIS) || (item->type == BT_MOUSE_AXIS) || (item->type == BT_INVERT) )
		gr_string(x, item->y - 164, "?");

}

void kc_change_key( kc_item * item )
{
	int i,n,f,k;
	ubyte keycode;

	gr_set_fontcolor( BM_XRGB(28,28,28), -1 );
	
	gr_string( 0x8000, INFO_Y, TXT_PRESS_NEW_KEY );
	
	game_flush_inputs();
	keycode=255;
	k=255;
	while( (k!=KEY_ESC) && (keycode==255) )	{				
		#ifdef NETWORK
		if ((Game_mode & GM_MULTI) && (Function_mode == FMODE_GAME) && (!Endlevel_sequence))
			multi_menu_poll();
		#endif
//		if ( Game_mode & GM_MULTI )
//			GameLoop( 0, 0 );				// Continue
		k = key_inkey();
		delay(10);
		kc_drawquestion( item );
	
		for (i=0; i<256; i++ )	{
			if ((keyd_pressed[i]) && (strlen(key_text[i])>0))	{
				f = 0;
				for (n=0; n<sizeof(system_keys); n++ )
					if ( system_keys[n] == i )
						f=1;
				if (!f)	
					keycode=i;
			}
		}
		bitblt_to_screen();
	}

	if (k!=KEY_ESC)	{
		for (i=0; i<Num_items; i++ )	{
			n = item - All_items;
			if ( (i!=n) && (All_items[i].type==BT_KEY) && (All_items[i].value==keycode) )		{
				All_items[i].value = 255;
				kc_drawitem( &All_items[i], 0 );
			}
		}
		item->value = keycode;
	}
	kc_drawitem( item, 1 );
	gr_set_fontcolor( BM_XRGB(28,28,28), BM_XRGB(0,0,0) );

	nm_restore_background( 0, INFO_Y, 620, grd_curcanv->cv_font->ft_h );

	game_flush_inputs();

}

void kconfig_set_fcs_button( int btn, int button )
{
#if 0
	int state,time_down,upcount,downcount;
	state = time_down = upcount = downcount = 0;

	if ( joy_get_button_state(btn) ) {
		if ( btn==button )	{
			state = 1;
			time_down = FrameTime;
		} else {
			upcount=1;
		}
	} else {
		if ( btn==button )	{
			state = 1;
			time_down = FrameTime;
			downcount=1;
		} else {
			upcount=1;
		}
	}				
			
	joy_set_btn_values( btn, state, time_down, downcount, upcount );
#endif			
}

void kc_change_joybutton( kc_item * item )
{
#if 0
	int n,i,k;
	ubyte code;

	gr_set_fontcolor( BM_XRGB(28,28,28), -1 );
	
	gr_string( 0x8000, INFO_Y, TXT_PRESS_NEW_JBUTTON );
	
	game_flush_inputs();
	code=255;
	k=255;
	while( (k!=KEY_ESC) && (code==255))	{				
		#ifdef NETWORK
		if ((Game_mode & GM_MULTI) && (Function_mode == FMODE_GAME) && (!Endlevel_sequence))
			multi_menu_poll();
		#endif
//		if ( Game_mode & GM_MULTI )
//			GameLoop( 0, 0 );				// Continue
		k = key_inkey();
		delay(10);

		if (k == KEY_PRINT_SCREEN)
			save_screen_shot(0);

		kc_drawquestion( item );

		if (Config_control_type==CONTROL_FLIGHTSTICK_PRO) {
			for (i=4; i<20; i++ )	{
				if ( joy_get_button_state(i)  )	{
					code = i;
					mprintf(( 0, "JB: %d\n", code ));
				}
			}
		} else {
			for (i=0; i<4; i++ )	{
				if ( joy_get_button_state(i) )
					code = i;
			}
		}
		bitblt_to_screen();
	}
	if (code!=255)	{
		for (i=0; i<Num_items; i++ )	{
			n = item - All_items;
			if ( (i!=n) && (All_items[i].type==BT_JOY_BUTTON) && (All_items[i].value==code) )		{
				All_items[i].value = 255;
				kc_drawitem( &All_items[i], 0 );
			}
		}
		item->value = code;
	}
	kc_drawitem( item, 1 );
	nm_restore_background( 0, INFO_Y, 310, grd_curcanv->cv_font->ft_h );
	game_flush_inputs();
#endif
}

void kc_change_mousebutton( kc_item * item )
{
	int n,i,b,k;
	ubyte code;

	gr_set_fontcolor( BM_XRGB(28,28,28), -1 );
	
	gr_string( 0x8000, INFO_Y, TXT_PRESS_NEW_MBUTTON );
	
	game_flush_inputs();
	code=255;
	k=255;
	while( (k!=KEY_ESC) && (code==255))	{				
		#ifdef NETWORK
		if ((Game_mode & GM_MULTI) && (Function_mode == FMODE_GAME) && (!Endlevel_sequence))
			multi_menu_poll();
		#endif
//		if ( Game_mode & GM_MULTI )
//			GameLoop( 0, 0 );				// Continue
		k = key_inkey();
		delay(10);

		if (k == KEY_PRINT_SCREEN)
			save_screen_shot(0);

		kc_drawquestion( item );

		b = mouse_get_btns();
		for (i=0; i<3; i++ )	{
			if ( b & (1<<i) )	
				code = i;
		}
		bitblt_to_screen();
	}
	if (code!=255)	{
		for (i=0; i<Num_items; i++ )	{
			n = item - All_items;
			if ( (i!=n) && (All_items[i].type==BT_MOUSE_BUTTON) && (All_items[i].value==code) )		{
				All_items[i].value = 255;
				kc_drawitem( &All_items[i], 0 );
			}
		}
		item->value = code;
	}
	kc_drawitem( item, 1 );
	nm_restore_background( 0, INFO_Y, 620, grd_curcanv->cv_font->ft_h );
	game_flush_inputs();

}

void kc_change_joyaxis( kc_item * item )
{
	int axis[4];
	int old_axis[4];
	int n,i,k;
	int dead_zone;
	ubyte code, channels;

	gr_set_fontcolor( BM_XRGB(28,28,28), -1 );
	
	gr_string( 0x8000, INFO_Y, TXT_MOVE_NEW_JOY_AXIS );
	
	game_flush_inputs();
	code=255;
	k=255;

	joystick_read_raw_axis( JOY_ALL_AXIS, old_axis );

	while( (k!=KEY_ESC) && (code==255))	{				
		#ifdef NETWORK
		if ((Game_mode & GM_MULTI) && (Function_mode == FMODE_GAME) && (!Endlevel_sequence))
			multi_menu_poll();
		#endif
//		if ( Game_mode & GM_MULTI )
//			GameLoop( 0, 0 );				// Continue
		k = key_inkey();
		delay(10);

		if (k == KEY_PRINT_SCREEN)
			save_screen_shot(0);

		kc_drawquestion( item );

		channels = joystick_read_raw_axis( JOY_ALL_AXIS, axis );
		
		for (i=0; i<4; i++ )	{
  			if ( ((channels >> i) & 0x1) && abs(axis[i]-old_axis[i])>20 )	{
				code = i;
			}
			old_axis[i] = axis[i];
		}
		bitblt_to_screen();
	}
	if (code!=255)	{
		for (i=0; i<Num_items; i++ )	{
			n = item - All_items;
			if ( (i!=n) && (All_items[i].type==BT_JOY_AXIS) && (All_items[i].value==code) )		{
				All_items[i].value = 255;
				kc_drawitem( &All_items[i], 0 );
			}
		}

		item->value = code;					 
	}
	kc_drawitem( item, 1 );
	nm_restore_background( 0, INFO_Y, 620, grd_curcanv->cv_font->ft_h );
	game_flush_inputs();

}

void kc_change_mouseaxis( kc_item * item )
{
	int i,n,k;
	ubyte code;
	int dx,dy;

	gr_set_fontcolor( BM_XRGB(28,28,28), -1 );
	
	gr_string( 0x8000, INFO_Y, TXT_MOVE_NEW_MSE_AXIS );
	
	game_flush_inputs();
	code=255;
	k=255;

	mouse_get_delta( &dx, &dy );

	while( (k!=KEY_ESC) && (code==255))	{				
		#ifdef NETWORK
		if ((Game_mode & GM_MULTI) && (Function_mode == FMODE_GAME) && (!Endlevel_sequence))
			multi_menu_poll();
		#endif
//		if ( Game_mode & GM_MULTI )
//			GameLoop( 0, 0 );				// Continue
		k = key_inkey();
		delay(10);

		if (k == KEY_PRINT_SCREEN)
			save_screen_shot(0);

		kc_drawquestion( item );

		mouse_get_delta( &dx, &dy );
		if ( abs(dx)>20 ) code = 0;
		if ( abs(dy)>20 )	code = 1;
		bitblt_to_screen();
	}
	if (code!=255)	{
		for (i=0; i<Num_items; i++ )	{
			n = item - All_items;
			if ( (i!=n) && (All_items[i].type==BT_MOUSE_AXIS) && (All_items[i].value==code) )		{
				All_items[i].value = 255;
				kc_drawitem( &All_items[i], 0 );
			}
		}
		item->value = code;
	}
	kc_drawitem( item, 1 );
	nm_restore_background( 0, INFO_Y, 620, grd_curcanv->cv_font->ft_h );
	game_flush_inputs();

}


void kc_change_invert( kc_item * item )
{
	game_flush_inputs();

	if (item->value)
		item->value = 0;
	else 
		item->value = 1;

	kc_drawitem( item, 1 );

}

int get_item_height(kc_item *item)
{
	int x, w, h, aw;
	char btext[10];

	if (item->value==255) {
		sprintf( btext, "" );
	} else {
		switch( item->type )	{
			case BT_KEY:
				strncpy( btext, key_text[item->value], 10 ); break;
			case BT_MOUSE_BUTTON:
				strncpy( btext, Text_string[mousebutton_text[item->value]], 10 ); break;
			case BT_MOUSE_AXIS:
				strncpy( btext, Text_string[mouseaxis_text[item->value]], 10 ); break;
			case BT_JOY_BUTTON:
				if ( joybutton_text[item->value] !=-1 )
					strncpy( btext, Text_string[ joybutton_text[item->value]  ], 10 );
				else
					sprintf( btext, "BTN%d", item->value );
				break;
			case BT_JOY_AXIS:
				strncpy( btext, Text_string[joyaxis_text[item->value]], 10 ); break;
			case BT_INVERT:
				strncpy( btext, Text_string[invert_text[item->value]], 10 ); break;
		}
	}
	gr_get_string_size(btext, &w, &h, &aw  );

	return h;
}


void kconfig_sub(kc_item * items,int nitems, char * title)
{
	grs_canvas * save_canvas;
	grs_font * save_font;
	int old_keyd_repeat;
	int mouse_state, omouse_state;
	int mx, my, x1, x2, y1, y2;
	int close_x, close_y, close_size;
	int i,k,ocitem,citem, new_item;
	int time_stopped = 0;


	All_items = items;
	Num_items = nitems;

	if (!((Game_mode & GM_MULTI) && (Function_mode == FMODE_GAME) && (!Endlevel_sequence)) )
	{
		time_stopped = 1;
		stop_time();
	}

	save_canvas = grd_curcanv;
	gr_set_current_canvas( NULL );			
	save_font = grd_curcanv->cv_font;
	game_flush_inputs();
	old_keyd_repeat = keyd_repeat;
	keyd_repeat = 1;

	//gr_clear_canvas( BM_XRGB(0,0,0) );

	nm_draw_background(0,0,grd_curcanv->cv_bitmap.bm_w, grd_curcanv->cv_bitmap.bm_h );

	grd_curcanv->cv_font = Gamefonts[GFONT_MEDIUM_3];

	{
		char * p;
		p = strchr( title, '\n' );
		if ( p ) *p = 32;
		gr_string( 0x8000, 14, title );
		if ( p ) *p = '\n';
	}


//	if ( items == kc_keyboard )	{
//		gr_string( 0x8000, 8, "Keyboard" );
//	} else if ( items == kc_joystick )	{
//		gr_string( 0x8000, 8, "Joysticks" );
//	} else if ( items == kc_mouse )	{
//		gr_string( 0x8000, 8, "Mouse" );
//	}

	close_x = close_y = 15;
	close_size = 10;
	gr_setcolor( BM_XRGB(0, 0, 0) );
	gr_rect(close_x, close_y, close_x + close_size, close_y + close_size);
	gr_setcolor( BM_XRGB(21, 21, 21) );
	gr_rect( close_x + 2, close_y + 2, close_x + close_size - 2, close_y + close_size -2 );

	grd_curcanv->cv_font = GAME_FONT;
	gr_set_fontcolor( BM_XRGB(28,28,28), -1 );

	gr_string( 0x8000, 40, TXT_KCONFIG_STRING_1 );
	gr_set_fontcolor( BM_XRGB(28,28,28), -1 );
	if ( items == kc_keyboard )	{
		gr_set_fontcolor( BM_XRGB(31,27,6), -1 );
		gr_setcolor( BM_XRGB(31,27,6) );
		
		gr_scanline( 196, 212, 84 );
		gr_scanline( 240, 256, 84 );
		gr_pixel( 196, 86 );						
		gr_pixel( 196, 88 );						
		gr_pixel( 256, 86 );						
		gr_pixel( 256, 88 );						
		
		gr_string( 218, 80, "OR" );

		gr_scanline( 506, 522, 84 );
		gr_scanline( 548, 566, 84 );
		gr_pixel( 506, 86 );						
		gr_pixel( 506, 88 );						
		gr_pixel( 566, 86 );						
		gr_pixel( 566, 88 );						

		gr_string( 528, 80, "OR" );

	} else if ( items == kc_joystick )	{
		gr_set_fontcolor( BM_XRGB(31,27,6), -1 );
		gr_setcolor( BM_XRGB(31,27,6) );
		gr_scanline( 36, 270, 74 );
		gr_scanline( 362, 588, 74 );
//		gr_scanline( 36, 288, 258 );
//		gr_scanline( 348, 588, 258 );
//		gr_string( 0x8000, 70, TXT_BUTTONS );
		gr_string( 0x8000, 70, TXT_AXES );
		gr_set_fontcolor( BM_XRGB(28,28,28), -1 );
		gr_string( 162, 90, TXT_AXIS );
		gr_string( 222, 90, TXT_INVERT );
		gr_string( 444, 90, TXT_AXIS );
		gr_string( 504, 90, TXT_INVERT );
	} else if ( items == kc_mouse )	{
		gr_set_fontcolor( BM_XRGB(31,27,6), -1 );
		gr_setcolor( BM_XRGB(31,27,6) );
		gr_scanline( 36, 270, 74 );
		gr_scanline( 362, 588, 74 );
//		gr_scanline( 36, 288, 248 );
//		gr_scanline( 348, 588, 248 );
//		gr_string( 0x8000, 70, TXT_BUTTONS );
		gr_string( 0x8000, 70, TXT_AXES );
		gr_set_fontcolor( BM_XRGB(28,28,28), -1 );
		gr_string( 338, 90, TXT_AXIS );
		gr_string( 398, 90, TXT_INVERT );
	}

#if 0
	} else if ( items == kc_joystick )	{
		gr_set_fontcolor( BM_XRGB(31,27,6), -1 );
		gr_setcolor( BM_XRGB(31,27,6) );
		gr_scanline( 36, 270, 74 );
		gr_scanline( 362, 588, 74 );
		gr_scanline( 36, 288, 258 );
		gr_scanline( 348, 588, 258 );
		gr_string( 0x8000, 70, TXT_BUTTONS );
		gr_string( 0x8000,254, TXT_AXES );
		gr_set_fontcolor( BM_XRGB(28,28,28), -1 );
		gr_string( 162, 274, TXT_AXIS );
		gr_string( 222, 274, TXT_INVERT );
		gr_string( 444, 274, TXT_AXIS );
		gr_string( 504, 274, TXT_INVERT );
	} else if ( items == kc_mouse )	{
		gr_set_fontcolor( BM_XRGB(31,27,6), -1 );
		gr_setcolor( BM_XRGB(31,27,6) );
		gr_scanline( 36, 270, 74 );
		gr_scanline( 362, 588, 74 );
		gr_scanline( 36, 288, 248 );
		gr_scanline( 348, 588, 248 );
		gr_string( 0x8000, 70, TXT_BUTTONS );
		gr_string( 0x8000,244, TXT_AXES );
		gr_set_fontcolor( BM_XRGB(28,28,28), -1 );
		gr_string( 338, 258, TXT_AXIS );
		gr_string( 398, 258, TXT_INVERT );
	}
#endif
	
	for (i=0; i<nitems; i++ )	{
		kc_drawitem( &items[i], 0 );
	}

	citem = 0;
	if ( (items == kc_mouse) || (items == kc_joystick) ) {
		while (1) {
			if ( ((items == kc_mouse) && (items[citem].type == BT_MOUSE_AXIS)) || ((items == kc_joystick) && (items[citem].type == BT_JOY_AXIS)) )
				break;
			citem = items[citem].d;
		}
	}
	kc_drawitem( &items[citem], 1 );

	show_cursor();
	mouse_state = omouse_state = 0;
	
	while(1)		{
		k = key_inkey();

		omouse_state = mouse_state;	
		mouse_state = mouse_button_state(0);

		if ( !time_stopped ) {
			#ifdef NETWORK
			if (multi_menu_poll() == -1)
				k = -2;
			#endif
		}
		ocitem = citem;
		switch( k )	{
		case KEY_BACKSP:
			Int3();
			break;
		case KEY_PRINT_SCREEN:
			save_screen_shot(0);
			break;							
		case KEY_CTRLED+KEY_D:
			items[citem].value = 255;
			kc_drawitem( &items[citem], 1 );
			break;
		case KEY_CTRLED+KEY_R:	
			if ( items==kc_keyboard )	{
				for (i=0; i<NUM_KEY_CONTROLS; i++ )		{
					items[i].value=default_kconfig_settings[0][i];
					kc_drawitem( &items[i], 0 );
				}
			} else {
				for (i=0; i<NUM_OTHER_CONTROLS; i++ )	{
					items[i].value = default_kconfig_settings[Config_control_type][i];
					kc_drawitem( &items[i], 0 );
				}
			}
			kc_drawitem( &items[citem], 1 );
			break;
		case KEY_UP: 		
		case KEY_PAD8:
#ifdef TABLE_CREATION
			if (items[citem].u==-1) items[citem].u=find_next_item_up( items,nitems, citem);
#endif
			if (items == kc_mouse) {
				while (1) {
					citem = items[citem].u;
					if ( (items[citem].type == BT_MOUSE_AXIS) || (items[citem].type == BT_INVERT) )
						break;
				}
			} else if (items == kc_joystick) {
				while (1) {
					citem = items[citem].u;
 					if ( (items[citem].type == BT_JOY_AXIS) || (items[citem].type == BT_INVERT) )
						break;
				}
			} else
				citem = items[citem].u;
			break;
		case KEY_DOWN: 	
		case KEY_PAD2:
#ifdef TABLE_CREATION
			if (items[citem].d==-1) items[citem].d=find_next_item_down( items,nitems, citem);
#endif
			if (items == kc_mouse) {
				while (1) {
					citem = items[citem].d;
					if ( (items[citem].type == BT_MOUSE_AXIS) || (items[citem].type == BT_INVERT) )
						break;
				}
			} else if (items == kc_joystick) {
				while (1) {
					citem = items[citem].d;
					if ( (items[citem].type == BT_JOY_AXIS) || (items[citem].type == BT_INVERT) )
						break;
				}
			} else
				citem = items[citem].d;
			break;
		case KEY_SHIFTED + KEY_TAB:
		case KEY_LEFT: 	
		case KEY_PAD4:
#ifdef TABLE_CREATION
			if (items[citem].l==-1) items[citem].l=find_next_item_left( items,nitems, citem);
#endif
			if (items == kc_mouse) {
				while (1) {
					citem = items[citem].l;
					if ( (items[citem].type == BT_MOUSE_AXIS) || (items[citem].type == BT_INVERT) )
						break;
				}
			} else if (items == kc_joystick) {
				while (1) {
					citem = items[citem].l;
					if ( (items[citem].type == BT_JOY_AXIS) || (items[citem].type == BT_INVERT) )
						break;
				}
			} else
				citem = items[citem].l;
			break;
		case KEY_TAB:
		case KEY_RIGHT: 	
		case KEY_PAD6:
#ifdef TABLE_CREATION
			if (items[citem].r==-1) items[citem].r=find_next_item_right( items,nitems, citem);
#endif
			if (items == kc_mouse) {
				while (1) {
					citem = items[citem].r;
					if ( (items[citem].type == BT_MOUSE_AXIS) || (items[citem].type == BT_INVERT) )
						break;
				}
			} else if (items == kc_joystick) {
				while (1) {
					citem = items[citem].r;
					if ( (items[citem].type == BT_JOY_AXIS) || (items[citem].type == BT_INVERT) )
						break;
				}
			} else
				citem = items[citem].r;
			break;
		case KEY_ENTER:	
		case KEY_PADENTER:	
			switch( items[citem].type )	{
			case BT_KEY:				kc_change_key( &items[citem] ); break;
			case BT_MOUSE_BUTTON:	kc_change_mousebutton( &items[citem] ); break;
			case BT_MOUSE_AXIS: 		kc_change_mouseaxis( &items[citem] ); break;
			case BT_JOY_BUTTON: 		kc_change_joybutton( &items[citem] ); break;
			case BT_JOY_AXIS: 		kc_change_joyaxis( &items[citem] ); break;
			case BT_INVERT: 			kc_change_invert( &items[citem] ); break;
			}
			break;
		case -2:	
		case KEY_ESC:
			grd_curcanv->cv_font	= save_font;
			gr_set_current_canvas( save_canvas );			
			keyd_repeat = old_keyd_repeat;
			game_flush_inputs();
			hide_cursor();
			if (time_stopped)
				start_time();
			return;
#ifdef TABLE_CREATION
		case KEY_DEBUGGED+KEY_F12:	{
			FILE * fp;
			for (i=0; i<NUM_KEY_CONTROLS; i++ )	{
				kc_keyboard[i].u = find_next_item_up( kc_keyboard,NUM_KEY_CONTROLS, i);
				kc_keyboard[i].d = find_next_item_down( kc_keyboard,NUM_KEY_CONTROLS, i);
				kc_keyboard[i].l = find_next_item_left( kc_keyboard,NUM_KEY_CONTROLS, i);
				kc_keyboard[i].r = find_next_item_right( kc_keyboard,NUM_KEY_CONTROLS, i);
			}
			for (i=0; i<NUM_OTHER_CONTROLS; i++ )	{
				kc_joystick[i].u = find_next_item_up( kc_joystick,NUM_OTHER_CONTROLS, i);
				kc_joystick[i].d = find_next_item_down( kc_joystick,NUM_OTHER_CONTROLS, i);
				kc_joystick[i].l = find_next_item_left( kc_joystick,NUM_OTHER_CONTROLS, i);
				kc_joystick[i].r = find_next_item_right( kc_joystick,NUM_OTHER_CONTROLS, i);
			}
			for (i=0; i<NUM_OTHER_CONTROLS; i++ )	{
				kc_mouse[i].u = find_next_item_up( kc_mouse,NUM_OTHER_CONTROLS, i);
				kc_mouse[i].d = find_next_item_down( kc_mouse,NUM_OTHER_CONTROLS, i);
				kc_mouse[i].l = find_next_item_left( kc_mouse,NUM_OTHER_CONTROLS, i);
				kc_mouse[i].r = find_next_item_right( kc_mouse,NUM_OTHER_CONTROLS, i);
			}
			fp = fopen( "kconfig.cod", "wt" );

			fprintf( fp, "ubyte default_kconfig_settings[CONTROL_MAX_TYPES][MAX_CONTROLS] = {\n" );
			for (i=0; i<CONTROL_MAX_TYPES; i++ )	{
				int j;
				fprintf( fp, "{0x%x", kconfig_settings[i][0] );
				for (j=1; j<MAX_CONTROLS; j++ )
					fprintf( fp, ",0x%x", kconfig_settings[i][j] );
				fprintf( fp, "},\n" );
			}
			fprintf( fp, "};\n" );
		
			fprintf( fp, "\nkc_item kc_keyboard[NUM_KEY_CONTROLS] = {\n" );
			for (i=0; i<NUM_KEY_CONTROLS; i++ )	{
				fprintf( fp, "\t{ %2d,%3d,%3d,%3d,%3d,%3d,%3d,%3d,%3d,%3d, %3d, 255 },\n", 
					kc_keyboard[i].id, kc_keyboard[i].x, kc_keyboard[i].y, kc_keyboard[i].w1, kc_keyboard[i].w2,
					kc_keyboard[i].u, kc_keyboard[i].d, kc_keyboard[i].l, kc_keyboard[i].r,
					kc_keyboard[i].text_num1, kc_keyboard[i].type );
			}
			fprintf( fp, "};" );

			fprintf( fp, "\nkc_item kc_joystick[NUM_OTHER_CONTROLS] = {\n" );
			for (i=0; i<NUM_OTHER_CONTROLS; i++ )	{
				fprintf( fp, "\t{ %2d,%3d,%3d,%3d,%3d,%3d,%3d,%3d,%3d,%3d, %3d, 255 },\n", 
					kc_joystick[i].id, kc_joystick[i].x, kc_joystick[i].y, kc_joystick[i].w1, kc_joystick[i].w2,
					kc_joystick[i].u, kc_joystick[i].d, kc_joystick[i].l, kc_joystick[i].r,
					kc_joystick[i].text_num1, kc_joystick[i].type );
			}
			fprintf( fp, "};" );

			fprintf( fp, "\nkc_item kc_mouse[NUM_OTHER_CONTROLS] = {\n" );
			for (i=0; i<NUM_OTHER_CONTROLS; i++ )	{
				fprintf( fp, "\t{ %2d,%3d,%3d,%3d,%3d,%3d,%3d,%3d,%3d,%3d,%3d, 255 },\n", 
					kc_mouse[i].id, kc_mouse[i].x, kc_mouse[i].y, kc_mouse[i].w1, kc_mouse[i].w2,
					kc_mouse[i].u, kc_mouse[i].d, kc_mouse[i].l, kc_mouse[i].r,
					kc_mouse[i].text_num1, kc_mouse[i].type );
			}
			fprintf( fp, "};" );

			fclose(fp);

			}
			break;
#endif
		}

		if ( (mouse_state && !omouse_state) || (mouse_state && omouse_state) ) {
			int item_height;
			
			mouse_get_pos(&mx, &my);
			for (i=0; i<nitems; i++ )	{
				if ( (items[i].type == BT_MOUSE_BUTTON) || (items[i].type == BT_JOY_BUTTON) )
					continue;
				item_height = get_item_height( &items[i] );
				x1 = grd_curcanv->cv_bitmap.bm_x + items[i].x + items[i].w1;
				x2 = x1 + items[i].w2;
				y1 = grd_curcanv->cv_bitmap.bm_y + items[i].y;
				y2 = y1 + item_height;
				if ( (items[i].type == BT_MOUSE_AXIS) || (items[i].type == BT_JOY_AXIS) || (items[i].type == BT_INVERT) ) {
					y1 -= 164;
					y2 -= 164;
				}
				if (((mx > x1) && (mx < x2)) && ((my > y1) && (my < y2))) {
					citem = i;
					break;
				}
			}
		}
		else if ( !mouse_state && omouse_state ) {
			int item_height;
			
			mouse_get_pos(&mx, &my);
			if ( (items[citem].type == BT_MOUSE_BUTTON) || (items[citem].type == BT_JOY_BUTTON) )
				continue;
			item_height = get_item_height( &items[citem] );
			x1 = grd_curcanv->cv_bitmap.bm_x + items[citem].x + items[citem].w1;
			x2 = x1 + items[citem].w2;
			y1 = grd_curcanv->cv_bitmap.bm_y + items[citem].y;
			y2 = y1 + item_height;
			if ( (items[citem].type == BT_MOUSE_AXIS) || (items[citem].type == BT_JOY_AXIS) || (items[citem].type == BT_INVERT) ) {
				y1 -= 164;
				y2 -= 164;
			}
			if (((mx > x1) && (mx < x2)) && ((my > y1) && (my < y2))) {
				hide_cursor();
				switch( items[citem].type )	{
				case BT_KEY:				kc_change_key( &items[citem] ); break;
				case BT_MOUSE_AXIS: 		kc_change_mouseaxis( &items[citem] ); break;
				case BT_JOY_AXIS: 		kc_change_joyaxis( &items[citem] ); break;
				case BT_INVERT: 			kc_change_invert( &items[citem] ); break;
				}
				show_cursor();
			} else {
				x1 = grd_curcanv->cv_bitmap.bm_x + close_x + 2;
				x2 = x1 + close_size - 2;
				y1 = grd_curcanv->cv_bitmap.bm_y + close_y + 2;
				y2 = y1 + close_size - 2;
				if ( ((mx > x1) && (mx < x2)) && ((my > y1) && (my < y2)) ) {
					grd_curcanv->cv_font	= save_font;
					gr_set_current_canvas( save_canvas );			
					keyd_repeat = old_keyd_repeat;
					game_flush_inputs();
					hide_cursor();
					if (time_stopped)
						start_time();
					return;
				}
			}

		}

		if (ocitem!=citem)	{
			hide_cursor();
			kc_drawitem( &items[ocitem], 0 );
			kc_drawitem( &items[citem], 1 );
			show_cursor();
		}
		bitblt_to_screen();
	}
	hide_cursor();
}


#include "screens.h"

void kconfig(int n, char * title)
{
	int i;
	set_screen_mode( SCREEN_MENU );

	kc_set_controls();

	switch(n)	{
	case 0:kconfig_sub( kc_keyboard, NUM_KEY_CONTROLS, title );break;
	case 1:kconfig_sub( kc_joystick, NUM_OTHER_CONTROLS, title );break;
	case 2:kconfig_sub( kc_mouse, NUM_OTHER_CONTROLS, title ); break;
	default:
		Int3();
		return;
	}

	reset_cockpit();		//force cockpit redraw next time

	// Update save values...
	
	for (i=0; i<NUM_KEY_CONTROLS; i++ )	
		kconfig_settings[0][i] = kc_keyboard[i].value;

	if ( (Config_control_type>0) && (Config_control_type<5))	{
		for (i=0; i<NUM_OTHER_CONTROLS; i++ )	
			kconfig_settings[Config_control_type][i] = kc_joystick[i].value;
	} else if (Config_control_type>4) {
		for (i=0; i<NUM_OTHER_CONTROLS; i++ )	
			kconfig_settings[Config_control_type][i] = kc_mouse[i].value;
	}

}


fix Last_angles_p = 0;
fix Last_angles_b = 0;
fix Last_angles_h = 0;
ubyte Last_angles_read = 0;

extern int			VR_sensitivity;
						
int VR_sense_range[3] = { 25, 50, 75 };

read_head_tracker()
{
	fix yaw, pitch, roll;
	int buttons;
//------ read vfx1 helmet --------

#if 0
	if (vfx1_installed) {
		SenseGetData( sense_function1, DCHTD,&yaw,&pitch, &roll, &buttons);
	} else if (iglasses_headset_installed)	{
		iglasses_read_headset( &yaw, &pitch, &roll );
	} else if (Victor_headset_installed)   {
		victor_read_headset_filtered( &yaw, &pitch, &roll );
	} else {
		return;
	}

	Use_player_head_angles = 0;
	if ( Last_angles_read )	{
		fix yaw1 = yaw;
		
		yaw1 = yaw;
		if ( (Last_angles_h < (F1_0/4) ) && (yaw > ((F1_0*3)/4) ) )	
			yaw1 -= F1_0;
		else if ( (yaw < (F1_0/4) ) && (Last_angles_h > ((F1_0*3)/4) ) )	
			yaw1 += F1_0;
	
		Controls.pitch_time	+= fixmul((pitch- Last_angles_p)*VR_sense_range[VR_sensitivity],FrameTime);
		Controls.heading_time+= fixmul((yaw1 -  Last_angles_h)*VR_sense_range[VR_sensitivity],FrameTime);
		Controls.bank_time	+= fixmul((roll - Last_angles_b)*VR_sense_range[VR_sensitivity],FrameTime);
	}
	Last_angles_read = 1;
	Last_angles_p = pitch;
	Last_angles_h = yaw;
	Last_angles_b = roll;
#endif
	return;
}

#define	PH_SCALE	8
#define	JOYSTICK_READ_TIME	(F1_0/10)		//	Read joystick at 10 Hz.
#define MOUSE_READ_TIME		(F1_0/30)		// read mouse at 30 Hz
fix	LastReadTime = 0;

fix	joy_axis[4];

ubyte 			kc_use_external_control = 0;
ubyte 			kc_external_intno = 0;
control_info	*kc_external_control = NULL;

void kconfig_init_external_controls(int intno, int address)
{
	kc_external_intno = intno;
	kc_external_control	= (control_info *)address;
	kc_use_external_control = 1;

	printf( "%s int: 0x%x, data: 0x%x\n", TXT_EXTERNAL_CONTROL, kc_external_intno, kc_external_control );
}

void kconfig_read_external_controls()
{
#if 0
	union REGS r;

	memset( kc_external_control, 0, sizeof(control_info) );

	if ( grd_curscreen->sc_mode != SM_320x200C )			// (If in automap...)
		kc_external_control->automap_state = 1;
	memset(&r,0,sizeof(r));

	int386 ( kc_external_intno, &r, &r);		// Read external info...

	if ( Player_num > -1 )	{
		Objects[Players[Player_num].objnum].mtype.phys_info.flags &= (~PF_TURNROLL);	// Turn off roll when turning
		Objects[Players[Player_num].objnum].mtype.phys_info.flags &= (~PF_LEVELLING);	// Turn off leveling to nearest side.
		Auto_leveling_on = 0;
	}
	Controls.pitch_time += fixmul(kc_external_control->pitch_time,FrameTime);						
	Controls.vertical_thrust_time += fixmul(kc_external_control->vertical_thrust_time,FrameTime);
	Controls.heading_time += fixmul(kc_external_control->heading_time,FrameTime);
	Controls.sideways_thrust_time += fixmul(kc_external_control->sideways_thrust_time ,FrameTime);
	Controls.bank_time += fixmul(kc_external_control->bank_time ,FrameTime);
	Controls.forward_thrust_time += fixmul(kc_external_control->forward_thrust_time ,FrameTime);
	Controls.rear_view_down_count += kc_external_control->rear_view_down_count;	
	Controls.rear_view_down_state |= kc_external_control->rear_view_down_state;	
	Controls.fire_primary_down_count += kc_external_control->fire_primary_down_count;
	Controls.fire_primary_state |= kc_external_control->fire_primary_state;
	Controls.fire_secondary_state |= kc_external_control->fire_secondary_state;
	Controls.fire_secondary_down_count += kc_external_control->fire_secondary_down_count;
	Controls.fire_flare_down_count += kc_external_control->fire_flare_down_count;
	Controls.drop_bomb_down_count += kc_external_control->drop_bomb_down_count;	
	Controls.automap_down_count += kc_external_control->automap_down_count;
	Controls.automap_state |= kc_external_control->automap_state;
#endif
}

#define CONTROLS_READ_TIME	F1_0/25

void controls_read_all()
{
	int i;
	int slide_on, bank_on;
	int dx, dy;
	int idx, idy;
	fix ctime;
	fix mouse_axis[2];
	int raw_joy_axis[4];
	int mouse_buttons;
	fix k0, k1, k2, k3, kp;
	fix k4, k5, k6, k7, kh;
	ubyte channel_masks;
	int use_mouse, use_joystick;
	int speed_factor=1;
	static fix last_ctime = 0;

	if (Game_turbo_mode)
		speed_factor = 2;
	
	if (Arcade_mode)	{
		arcade_read_controls();
		return;
	}

	{
		fix temp = Controls.heading_time;
		fix temp1 = Controls.pitch_time;
		memset( &Controls, 0, sizeof(control_info) );
		Controls.heading_time = temp;
		Controls.pitch_time = temp1;
	}
	
	slide_on = 0;
	bank_on = 0;

	
	//---------  Read Joystick -----------
	if ((Config_control_type>0) && (Config_control_type<5) ) {
		channel_masks = joystick_read_raw_axis( JOY_ALL_AXIS, raw_joy_axis );
		for (i=0; i<4; i++ )	{
			if (channel_masks&(1<<i))	{
				int joy_null_value = 10;

				raw_joy_axis[i] = joy_get_scaled_reading( raw_joy_axis[i], i );

				if (kc_joystick[23].value==i)		// If this is the throttle
					joy_null_value = 20;				// Then use a larger dead-zone

				if (raw_joy_axis[i] > joy_null_value) 
					raw_joy_axis[i] = ((raw_joy_axis[i]-joy_null_value)*128)/(128-joy_null_value);
				else if (raw_joy_axis[i] < -joy_null_value)
					raw_joy_axis[i] = ((raw_joy_axis[i]+joy_null_value)*128)/(128-joy_null_value);
				else
					raw_joy_axis[i] = 0;
				joy_axis[i]	= (raw_joy_axis[i]*FrameTime)/128;	
			} else {
				joy_axis[i] = 0;
			}
		}	
		use_joystick=1;
	} else {
		for (i=0; i<4; i++ )
			joy_axis[i] = 0;
		use_joystick=0;
	}
	
//	if (Config_control_type==5 ) {

#if 0
	ctime = timer_get_fixed_seconds();
	if (LastReadTime > ctime)
		LastReadTime = ctime;
		
	if ( (ctime - LastReadTime > MOUSE_READ_TIME) && Config_control_type == 5 ) {
#endif

	if ( Config_control_type == 5 ) {
		LastReadTime = ctime;
		//---------  Read Mouse -----------
		mouse_get_delta( &dx, &dy );
		mouse_axis[0] = (dx*FrameTime)/35;
		mouse_axis[1] = (dy*FrameTime)/25;
		mouse_buttons = mouse_get_btns();
		//mprintf(( 0, "Mouse %d,%d b:%d, 0x%x\n", mouse_axis[0], mouse_axis[1], mouse_buttons, FrameTime ));
		use_mouse=1;
#if 0
	} else if (Config_control_type==6 ) {
		//---------  Read Cyberman -----------
		mouse_get_cyberman_pos(&idx,&idy );
		mouse_axis[0] = (idx*FrameTime)/128;
		mouse_axis[1] = (idy*FrameTime)/128;
		mouse_buttons = mouse_get_btns();
		use_mouse=1;
#endif
	} else {
		mouse_axis[0] = 0;
		mouse_axis[1] = 0;
		mouse_buttons = 0;
		use_mouse=0;
	}


//------------- Read slide_on -------------
	
	// From keyboard...
	if ( kc_keyboard[8].value < 255 ) slide_on |= keyd_pressed[ kc_keyboard[8].value ];
	if ( kc_keyboard[9].value < 255 ) slide_on |= keyd_pressed[ kc_keyboard[9].value ];
	// From joystick...
//	if ((use_joystick)&&(kc_joystick[5].value<255)) slide_on |= joy_get_button_state( kc_joystick[5].value );
	// From mouse...
	if ((use_mouse)&&(kc_mouse[5].value<255)) slide_on |= mouse_buttons & (1<<kc_mouse[5].value);

//------------- Read bank_on ---------------

	// From keyboard...
	if ( kc_keyboard[18].value < 255 ) bank_on |= keyd_pressed[ kc_keyboard[18].value ];
	if ( kc_keyboard[19].value < 255 ) bank_on |= keyd_pressed[ kc_keyboard[19].value ];
	// From joystick...
//	if ( (use_joystick)&&(kc_joystick[10].value < 255 )) bank_on |= joy_get_button_state( kc_joystick[10].value );
	// From mouse...
	if ( (use_mouse)&&(kc_mouse[10].value < 255 )) bank_on |= mouse_buttons & (1<<kc_mouse[10].value);

//------------ Read pitch_time -----------
	if ( !slide_on )	{
		// mprintf((0, "pitch: %7.3f %7.3f: %7.3f\n", f2fl(k4), f2fl(k6), f2fl(Controls.heading_time)));
		kp = 0;
		k0 = speed_factor*key_down_time( kc_keyboard[0].value )/2;	// Divide by two since we want pitch to go slower
		k1 = speed_factor*key_down_time( kc_keyboard[1].value )/2;
		k2 = speed_factor*key_down_time( kc_keyboard[2].value )/2;
		k3 = speed_factor*key_down_time( kc_keyboard[3].value )/2;

		// From keyboard...
		if ( kc_keyboard[0].value < 255 ) kp += k0/PH_SCALE;
		if ( kc_keyboard[1].value < 255 ) kp += k1/PH_SCALE;
		if ( kc_keyboard[2].value < 255 ) kp -= k2/PH_SCALE;
		if ( kc_keyboard[3].value < 255 ) kp -= k3/PH_SCALE;

		// From Cyberman...
		if ((use_mouse)&&(Config_control_type==CONTROL_CYBERMAN))	{
			kp += mouse_button_down_time(MB_PITCH_FORWARD)/(PH_SCALE*2);
			kp -= mouse_button_down_time(MB_PITCH_BACKWARD)/(PH_SCALE*2);
		}
	
		if (kp == 0)
			Controls.pitch_time = 0;
		else if (kp > 0) {
			if (Controls.pitch_time < 0)
				Controls.pitch_time = 0;
		} else // kp < 0
			if (Controls.pitch_time > 0)
				Controls.pitch_time = 0;
		Controls.pitch_time += kp;
	
		// From joystick...
		if ( (use_joystick)&&(kc_joystick[13].value < 255 ))	{
			if ( !kc_joystick[14].value )		// If not inverted...
				Controls.pitch_time -= (joy_axis[kc_joystick[13].value]*Config_joystick_sensitivity)/8;
			else
				Controls.pitch_time += (joy_axis[kc_joystick[13].value]*Config_joystick_sensitivity)/8;
		}
	
		// From mouse...
		//mprintf(( 0, "UM: %d, PV: %d\n", use_mouse, kc_mouse[13].value ));
		if ( (use_mouse)&&(kc_mouse[13].value < 255) )	{
			if ( !kc_mouse[14].value )		// If not inverted...
				Controls.pitch_time -= (mouse_axis[kc_mouse[13].value]*Config_joystick_sensitivity)/8;
			else
				Controls.pitch_time += (mouse_axis[kc_mouse[13].value]*Config_joystick_sensitivity)/8;
		}
	} else {
		Controls.pitch_time = 0;
	}


//----------- Read vertical_thrust_time -----------------

	if ( slide_on )	{
		k0 = speed_factor*key_down_time( kc_keyboard[0].value );
		k1 = speed_factor*key_down_time( kc_keyboard[1].value );
		k2 = speed_factor*key_down_time( kc_keyboard[2].value );
		k3 = speed_factor*key_down_time( kc_keyboard[3].value );

		// From keyboard...
		if ( kc_keyboard[0].value < 255 ) Controls.vertical_thrust_time += k0;
		if ( kc_keyboard[1].value < 255 ) Controls.vertical_thrust_time += k1;
		if ( kc_keyboard[2].value < 255 ) Controls.vertical_thrust_time -= k2;
		if ( kc_keyboard[3].value < 255 ) Controls.vertical_thrust_time -= k3;

		// From Cyberman...
		if ((use_mouse)&&(Config_control_type==CONTROL_CYBERMAN))	{
			Controls.vertical_thrust_time -= mouse_button_down_time(MB_PITCH_FORWARD);
			Controls.vertical_thrust_time += mouse_button_down_time(MB_PITCH_BACKWARD);
		}
	
		// From joystick...
		if ((use_joystick)&&( kc_joystick[13].value < 255 ))	{
			if ( !kc_joystick[14].value )		// If not inverted...
				Controls.vertical_thrust_time += joy_axis[kc_joystick[13].value];
			else
				Controls.vertical_thrust_time -= joy_axis[kc_joystick[13].value];
		}
	
		// From mouse...
		if ( (use_mouse)&&(kc_mouse[13].value < 255 ))	{
			if ( !kc_mouse[14].value )		// If not inverted...
				Controls.vertical_thrust_time -= mouse_axis[kc_mouse[13].value];
			else
				Controls.vertical_thrust_time += mouse_axis[kc_mouse[13].value];
		}
	}

	// From keyboard...
	if ( kc_keyboard[14].value < 255 ) Controls.vertical_thrust_time += speed_factor*key_down_time( kc_keyboard[14].value );
	if ( kc_keyboard[15].value < 255 ) Controls.vertical_thrust_time += speed_factor*key_down_time( kc_keyboard[15].value );
	if ( kc_keyboard[16].value < 255 ) Controls.vertical_thrust_time -= speed_factor*key_down_time( kc_keyboard[16].value );
	if ( kc_keyboard[17].value < 255 ) Controls.vertical_thrust_time -= speed_factor*key_down_time( kc_keyboard[17].value );
	
	// From joystick...
	if ((use_joystick)&&( kc_joystick[19].value < 255 ))	{
		if ( !kc_joystick[20].value )		// If not inverted...
			Controls.vertical_thrust_time += joy_axis[kc_joystick[19].value];
		else
			Controls.vertical_thrust_time -= joy_axis[kc_joystick[19].value];
	}

	// From joystick buttons
//	if ( (use_joystick)&&(kc_joystick[8].value < 255 )) Controls.vertical_thrust_time += joy_get_button_down_time( kc_joystick[8].value );
//	if ( (use_joystick)&&(kc_joystick[9].value < 255 )) Controls.vertical_thrust_time -= joy_get_button_down_time( kc_joystick[9].value );

	// From mouse buttons
	if ( (use_mouse)&&(kc_mouse[8].value < 255 )) Controls.vertical_thrust_time += mouse_button_down_time( kc_mouse[8].value );
	if ( (use_mouse)&&(kc_mouse[9].value < 255 )) Controls.vertical_thrust_time -= mouse_button_down_time( kc_mouse[9].value );

	// From mouse...
	if ( (use_mouse)&&(kc_mouse[19].value < 255 ))	{
		if ( !kc_mouse[20].value )		// If not inverted...
			Controls.vertical_thrust_time += mouse_axis[kc_mouse[19].value];
		else
			Controls.vertical_thrust_time -= mouse_axis[kc_mouse[19].value];
	}

	// From Cyberman...
	if ((use_mouse)&&(Config_control_type==CONTROL_CYBERMAN))	{
		Controls.vertical_thrust_time += mouse_button_down_time(MB_Z_UP)/2;
		Controls.vertical_thrust_time -= mouse_button_down_time(MB_Z_DOWN)/2;
	}

//---------- Read heading_time -----------

	if (!slide_on && !bank_on)	{
		//mprintf((0, "heading: %7.3f %7.3f: %7.3f\n", f2fl(k4), f2fl(k6), f2fl(Controls.heading_time)));
		kh = 0;
		k4 = speed_factor*key_down_time( kc_keyboard[4].value );
		k5 = speed_factor*key_down_time( kc_keyboard[5].value );
		k6 = speed_factor*key_down_time( kc_keyboard[6].value );
		k7 = speed_factor*key_down_time( kc_keyboard[7].value );

		// From keyboard...
		if ( kc_keyboard[4].value < 255 ) kh -= k4/PH_SCALE;
		if ( kc_keyboard[5].value < 255 ) kh -= k5/PH_SCALE;
		if ( kc_keyboard[6].value < 255 ) kh += k6/PH_SCALE;
		if ( kc_keyboard[7].value < 255 ) kh += k7/PH_SCALE;

		// From Cyberman...
		if ((use_mouse)&&(Config_control_type==CONTROL_CYBERMAN))	{
			kh -= mouse_button_down_time(MB_HEAD_LEFT)/PH_SCALE;
			kh += mouse_button_down_time(MB_HEAD_RIGHT)/PH_SCALE;
		}
	
		if (kh == 0)
			Controls.heading_time = 0;
		else if (kh > 0) {
			if (Controls.heading_time < 0)
				Controls.heading_time = 0;
		} else // kh < 0
			if (Controls.heading_time > 0)
				Controls.heading_time = 0;
		Controls.heading_time += kh;

		// From joystick...
		if ( (use_joystick)&&(kc_joystick[15].value < 255 ))	{
			if ( !kc_joystick[16].value )		// If not inverted...
				Controls.heading_time += (joy_axis[kc_joystick[15].value]*Config_joystick_sensitivity)/8;
			else
				Controls.heading_time -= (joy_axis[kc_joystick[15].value]*Config_joystick_sensitivity)/8;
		}
	
		// From mouse...
		if ( (use_mouse)&&(kc_mouse[15].value < 255 ))	{
			if ( !kc_mouse[16].value )		// If not inverted...
				Controls.heading_time += (mouse_axis[kc_mouse[15].value]*Config_joystick_sensitivity)/8;
			else
				Controls.heading_time -= (mouse_axis[kc_mouse[15].value]*Config_joystick_sensitivity)/8;
		}
	} else {
		Controls.heading_time = 0;
	}

//----------- Read sideways_thrust_time -----------------

	if ( slide_on )	{
		k0 = speed_factor*key_down_time( kc_keyboard[4].value );
		k1 = speed_factor*key_down_time( kc_keyboard[5].value );
		k2 = speed_factor*key_down_time( kc_keyboard[6].value );
		k3 = speed_factor*key_down_time( kc_keyboard[7].value );

		// From keyboard...
		if ( kc_keyboard[4].value < 255 ) Controls.sideways_thrust_time -= k0;
		if ( kc_keyboard[5].value < 255 ) Controls.sideways_thrust_time -= k1;
		if ( kc_keyboard[6].value < 255 ) Controls.sideways_thrust_time += k2;
		if ( kc_keyboard[7].value < 255 ) Controls.sideways_thrust_time += k3;
	
		// From joystick...
		if ( (use_joystick)&&(kc_joystick[15].value < 255 ))	{
			if ( !kc_joystick[16].value )		// If not inverted...
				Controls.sideways_thrust_time += joy_axis[kc_joystick[15].value];
			else
				Controls.sideways_thrust_time -= joy_axis[kc_joystick[15].value];
		}
		
		// From cyberman
		if ((use_mouse)&&(Config_control_type==CONTROL_CYBERMAN))	{
			Controls.sideways_thrust_time -= mouse_button_down_time(MB_HEAD_LEFT);
			Controls.sideways_thrust_time += mouse_button_down_time(MB_HEAD_RIGHT);
		}
	
		// From mouse...
		if ( (use_mouse)&&(kc_mouse[15].value < 255 ))	{
			if ( !kc_mouse[16].value )		// If not inverted...
				Controls.sideways_thrust_time += mouse_axis[kc_mouse[15].value];
			else
				Controls.sideways_thrust_time -= mouse_axis[kc_mouse[15].value];
		}
	}

	// From keyboard...
	if ( kc_keyboard[10].value < 255 ) Controls.sideways_thrust_time -= speed_factor*key_down_time( kc_keyboard[10].value );
	if ( kc_keyboard[11].value < 255 ) Controls.sideways_thrust_time -= speed_factor*key_down_time( kc_keyboard[11].value );
	if ( kc_keyboard[12].value < 255 ) Controls.sideways_thrust_time += speed_factor*key_down_time( kc_keyboard[12].value );
	if ( kc_keyboard[13].value < 255 ) Controls.sideways_thrust_time += speed_factor*key_down_time( kc_keyboard[13].value );
	
	// From joystick...
	if ( (use_joystick)&&(kc_joystick[17].value < 255 ))	{
		if ( !kc_joystick[18].value )		// If not inverted...
			Controls.sideways_thrust_time -= joy_axis[kc_joystick[17].value];
		else
			Controls.sideways_thrust_time += joy_axis[kc_joystick[17].value];
	}

	// From joystick buttons
//	if ( (use_joystick)&&(kc_joystick[6].value < 255 )) Controls.sideways_thrust_time -= joy_get_button_down_time( kc_joystick[6].value );
//	if ( (use_joystick)&&(kc_joystick[7].value < 255 )) Controls.sideways_thrust_time += joy_get_button_down_time( kc_joystick[7].value );

	// From mouse buttons
	if ( (use_mouse)&&(kc_mouse[6].value < 255 )) Controls.sideways_thrust_time -= mouse_button_down_time( kc_mouse[6].value );
	if ( (use_mouse)&&(kc_mouse[7].value < 255 )) Controls.sideways_thrust_time += mouse_button_down_time( kc_mouse[7].value );

	// From mouse...
	if ( (use_mouse)&&(kc_mouse[17].value < 255 ))	{
		if ( !kc_mouse[18].value )		// If not inverted...
			Controls.sideways_thrust_time += mouse_axis[kc_mouse[17].value];
		else
			Controls.sideways_thrust_time -= mouse_axis[kc_mouse[17].value];
	}

//----------- Read bank_time -----------------

	if ( bank_on )	{
		k0 = speed_factor*key_down_time( kc_keyboard[4].value );
		k1 = speed_factor*key_down_time( kc_keyboard[5].value );
		k2 = speed_factor*key_down_time( kc_keyboard[6].value );
		k3 = speed_factor*key_down_time( kc_keyboard[7].value );

		// From keyboard...
		if ( kc_keyboard[4].value < 255 ) Controls.bank_time += k0;
		if ( kc_keyboard[5].value < 255 ) Controls.bank_time += k1;
		if ( kc_keyboard[6].value < 255 ) Controls.bank_time -= k2;
		if ( kc_keyboard[7].value < 255 ) Controls.bank_time -= k3;

		// From Cyberman...
		if ((use_mouse)&&(Config_control_type==CONTROL_CYBERMAN))	{
			Controls.bank_time -= mouse_button_down_time(MB_HEAD_LEFT);
			Controls.bank_time += mouse_button_down_time(MB_HEAD_RIGHT);
		}

		// From joystick...
		if ( (use_joystick)&&(kc_joystick[15].value < 255) )	{
			if ( !kc_joystick[16].value )		// If not inverted...
				Controls.bank_time -= (joy_axis[kc_joystick[15].value]*Config_joystick_sensitivity)/8;
			else
				Controls.bank_time += (joy_axis[kc_joystick[15].value]*Config_joystick_sensitivity)/8;
		}
	
		// From mouse...
		if ( (use_mouse)&&(kc_mouse[15].value < 255 ))	{
			if ( !kc_mouse[16].value )		// If not inverted...
				Controls.bank_time += (mouse_axis[kc_mouse[15].value]*Config_joystick_sensitivity)/8;
			else
				Controls.bank_time -= (mouse_axis[kc_mouse[15].value]*Config_joystick_sensitivity)/8;
		}
	}

	// From keyboard...
	if ( kc_keyboard[20].value < 255 ) Controls.bank_time += speed_factor*key_down_time( kc_keyboard[20].value );
	if ( kc_keyboard[21].value < 255 ) Controls.bank_time += speed_factor*key_down_time( kc_keyboard[21].value );
	if ( kc_keyboard[22].value < 255 ) Controls.bank_time -= speed_factor*key_down_time( kc_keyboard[22].value );
	if ( kc_keyboard[23].value < 255 ) Controls.bank_time -= speed_factor*key_down_time( kc_keyboard[23].value );

	// From joystick...
	if ( (use_joystick)&&(kc_joystick[21].value < 255) )	{
		if ( !kc_joystick[22].value )		// If not inverted...
			Controls.bank_time -= joy_axis[kc_joystick[21].value];
		else
			Controls.bank_time += joy_axis[kc_joystick[21].value];
	}

	// From joystick buttons
//	if ( (use_joystick)&&(kc_joystick[11].value < 255 )) Controls.bank_time += joy_get_button_down_time( kc_joystick[11].value );
//	if ( (use_joystick)&&(kc_joystick[12].value < 255 )) Controls.bank_time -= joy_get_button_down_time( kc_joystick[12].value );

	// From mouse buttons
	if ( (use_mouse)&&(kc_mouse[11].value < 255 )) Controls.bank_time += mouse_button_down_time( kc_mouse[11].value );
	if ( (use_mouse)&&(kc_mouse[12].value < 255 )) Controls.bank_time -= mouse_button_down_time( kc_mouse[12].value );

	// From mouse...
	if ( (use_mouse)&&(kc_mouse[21].value < 255 ))	{
		if ( !kc_mouse[22].value )		// If not inverted...
			Controls.bank_time += mouse_axis[kc_mouse[21].value];
		else
			Controls.bank_time -= mouse_axis[kc_mouse[21].value];
	}

	// From Cyberman
	if ((use_mouse)&&(Config_control_type==CONTROL_CYBERMAN))	{
		Controls.bank_time += mouse_button_down_time(MB_BANK_LEFT);
		Controls.bank_time -= mouse_button_down_time(MB_BANK_RIGHT);
	}

//----------- Read forward_thrust_time -------------

	// From keyboard...
	if ( kc_keyboard[30].value < 255 ) Controls.forward_thrust_time += speed_factor*key_down_time( kc_keyboard[30].value );
	if ( kc_keyboard[31].value < 255 ) Controls.forward_thrust_time += speed_factor*key_down_time( kc_keyboard[31].value );
	if ( kc_keyboard[32].value < 255 ) Controls.forward_thrust_time -= speed_factor*key_down_time( kc_keyboard[32].value );
	if ( kc_keyboard[33].value < 255 ) Controls.forward_thrust_time -= speed_factor*key_down_time( kc_keyboard[33].value );

	// From joystick...
	if ( (use_joystick)&&(kc_joystick[23].value < 255 ))	{
		if ( !kc_joystick[24].value )		// If not inverted...
			Controls.forward_thrust_time -= joy_axis[kc_joystick[23].value];
		else
			Controls.forward_thrust_time += joy_axis[kc_joystick[23].value];
	}

	// From joystick buttons
//	if ( (use_joystick)&&(kc_joystick[2].value < 255 )) Controls.forward_thrust_time += joy_get_button_down_time( kc_joystick[2].value );
//	if ( (use_joystick)&&(kc_joystick[3].value < 255 )) Controls.forward_thrust_time -= joy_get_button_down_time( kc_joystick[3].value );

	// From mouse...
	if ( (use_mouse)&&(kc_mouse[23].value < 255 ))	{
		if ( !kc_mouse[24].value )		// If not inverted...
			Controls.forward_thrust_time -= mouse_axis[kc_mouse[23].value];
		else
			Controls.forward_thrust_time += mouse_axis[kc_mouse[23].value];
	}

	// From mouse buttons
	if ( (use_mouse)&&(kc_mouse[2].value < 255 )) Controls.forward_thrust_time += mouse_button_down_time( kc_mouse[2].value );
	if ( (use_mouse)&&(kc_mouse[3].value < 255 )) Controls.forward_thrust_time -= mouse_button_down_time( kc_mouse[3].value );
	
//----------- Read fire_primary_down_count
	if (kc_keyboard[24].value < 255 ) Controls.fire_primary_down_count += key_down_count(kc_keyboard[24].value);
	if (kc_keyboard[25].value < 255 ) Controls.fire_primary_down_count += key_down_count(kc_keyboard[25].value);
	if ((use_joystick)&&(kc_joystick[0].value < 255 )) Controls.fire_primary_down_count += joy_get_button_down_cnt(kc_joystick[0].value);
	if ((use_mouse)&&(kc_mouse[0].value < 255 )) Controls.fire_primary_down_count += mouse_button_down_count(kc_mouse[0].value);

//----------- Read fire_primary_state
	if (kc_keyboard[24].value < 255 ) Controls.fire_primary_state |= keyd_pressed[kc_keyboard[24].value];
	if (kc_keyboard[25].value < 255 ) Controls.fire_primary_state |= keyd_pressed[kc_keyboard[25].value];
	if ((use_joystick)&&(kc_joystick[0].value < 255 )) Controls.fire_primary_state |= joy_get_button_state(kc_joystick[0].value);
	if ((use_mouse)&&(kc_mouse[0].value < 255) ) Controls.fire_primary_state |= mouse_button_state(kc_mouse[0].value);

//----------- Read fire_secondary_down_count
	if (kc_keyboard[26].value < 255 ) Controls.fire_secondary_down_count += key_down_count(kc_keyboard[26].value);
	if (kc_keyboard[27].value < 255 ) Controls.fire_secondary_down_count += key_down_count(kc_keyboard[27].value);
//	if ((use_joystick)&&(kc_joystick[1].value < 255 )) Controls.fire_secondary_down_count += joy_get_button_down_cnt(kc_joystick[1].value);
	if ((use_mouse)&&(kc_mouse[1].value < 255 )) Controls.fire_secondary_down_count += mouse_button_down_count(kc_mouse[1].value);

//----------- Read fire_secondary_state
	if (kc_keyboard[26].value < 255 ) Controls.fire_secondary_state |= keyd_pressed[kc_keyboard[26].value];
	if (kc_keyboard[27].value < 255 ) Controls.fire_secondary_state |= keyd_pressed[kc_keyboard[27].value];
//	if ((use_joystick)&&(kc_joystick[1].value < 255 )) Controls.fire_secondary_state |= joy_get_button_state(kc_joystick[1].value);
	if ((use_mouse)&&(kc_mouse[1].value < 255) ) Controls.fire_secondary_state |= mouse_button_state(kc_mouse[1].value);

//----------- Read fire_flare_down_count
	if (kc_keyboard[28].value < 255 ) Controls.fire_flare_down_count += key_down_count(kc_keyboard[28].value);
	if (kc_keyboard[29].value < 255 ) Controls.fire_flare_down_count += key_down_count(kc_keyboard[29].value);
//	if ((use_joystick)&&(kc_joystick[4].value < 255 )) Controls.fire_flare_down_count += joy_get_button_down_cnt(kc_joystick[4].value);
	if ((use_mouse)&&(kc_mouse[4].value < 255 )) Controls.fire_flare_down_count += mouse_button_down_count(kc_mouse[4].value);

//----------- Read drop_bomb_down_count
	if (kc_keyboard[34].value < 255 ) Controls.drop_bomb_down_count += key_down_count(kc_keyboard[34].value);
	if (kc_keyboard[35].value < 255 ) Controls.drop_bomb_down_count += key_down_count(kc_keyboard[35].value);
//	if ((use_joystick)&&(kc_joystick[26].value < 255 )) Controls.drop_bomb_down_count += joy_get_button_down_cnt(kc_joystick[26].value);
	if ((use_mouse)&&(kc_mouse[26].value < 255 )) Controls.drop_bomb_down_count += mouse_button_down_count(kc_mouse[26].value);

//----------- Read rear_view_down_count
	if (kc_keyboard[36].value < 255 ) Controls.rear_view_down_count += key_down_count(kc_keyboard[36].value);
	if (kc_keyboard[37].value < 255 ) Controls.rear_view_down_count += key_down_count(kc_keyboard[37].value);
//	if ((use_joystick)&&(kc_joystick[25].value < 255 )) Controls.rear_view_down_count += joy_get_button_down_cnt(kc_joystick[25].value);
	if ((use_mouse)&&(kc_mouse[25].value < 255 )) Controls.rear_view_down_count += mouse_button_down_count(kc_mouse[25].value);

//----------- Read rear_view_down_state
	if (kc_keyboard[36].value < 255 ) Controls.rear_view_down_state |= keyd_pressed[kc_keyboard[36].value];
	if (kc_keyboard[37].value < 255 ) Controls.rear_view_down_state |= keyd_pressed[kc_keyboard[37].value];
//	if ((use_joystick)&&(kc_joystick[25].value < 255 )) Controls.rear_view_down_state |= joy_get_button_state(kc_joystick[25].value);
	if ((use_mouse)&&(kc_mouse[25].value < 255 )) Controls.rear_view_down_state |= mouse_button_state(kc_mouse[25].value);

//----------- Read automap_down_count
	if (kc_keyboard[44].value < 255 ) Controls.automap_down_count += key_down_count(kc_keyboard[44].value);
	if (kc_keyboard[45].value < 255 ) Controls.automap_down_count += key_down_count(kc_keyboard[45].value);

//----------- Read automap_state
	if (kc_keyboard[44].value < 255 ) Controls.automap_state |= keyd_pressed[kc_keyboard[44].value];
	if (kc_keyboard[45].value < 255 ) Controls.automap_state |= keyd_pressed[kc_keyboard[45].value];

//----------- Read stupid-cruise-control-type of throttle.
	{
		if ( kc_keyboard[38].value < 255 ) Cruise_speed += fixdiv(speed_factor*key_down_time(kc_keyboard[38].value)*5,FrameTime);
		if ( kc_keyboard[39].value < 255 ) Cruise_speed += fixdiv(speed_factor*key_down_time(kc_keyboard[39].value)*5,FrameTime);
		if ( kc_keyboard[40].value < 255 ) Cruise_speed -= fixdiv(speed_factor*key_down_time(kc_keyboard[40].value)*5,FrameTime);
		if ( kc_keyboard[41].value < 255 ) Cruise_speed -= fixdiv(speed_factor*key_down_time(kc_keyboard[41].value)*5,FrameTime);
		if ( (kc_keyboard[42].value < 255) && (key_down_count(kc_keyboard[42].value)) )
			Cruise_speed = 0;
		if ( (kc_keyboard[43].value < 255) && (key_down_count(kc_keyboard[43].value)) )
			Cruise_speed = 0;
	
		if (Cruise_speed > i2f(100) ) Cruise_speed = i2f(100);
		if (Cruise_speed < 0 ) Cruise_speed = 0;
	
		if (Controls.forward_thrust_time==0)
			Controls.forward_thrust_time = fixmul(Cruise_speed,FrameTime)/100;
	}

	read_head_tracker();

	// Read external controls
	if (kc_use_external_control)
		kconfig_read_external_controls();
		
//----------- Clamp values between -FrameTime and FrameTime
	if (FrameTime > F1_0 )
		mprintf( (1, "Bogus frame time of %.2f seconds\n", f2fl(FrameTime) ));

	if (Controls.pitch_time > FrameTime/2 ) Controls.pitch_time = FrameTime/2;
	if (Controls.vertical_thrust_time > FrameTime ) Controls.vertical_thrust_time = FrameTime;
	if (Controls.heading_time > FrameTime ) Controls.heading_time = FrameTime;
	if (Controls.sideways_thrust_time > FrameTime ) Controls.sideways_thrust_time = FrameTime;
	if (Controls.bank_time > FrameTime ) Controls.bank_time = FrameTime;
	if (Controls.forward_thrust_time > FrameTime ) Controls.forward_thrust_time = FrameTime;
//	if (Controls.afterburner_time > FrameTime ) Controls.afterburner_time = FrameTime;

	if (Controls.pitch_time < -FrameTime/2 ) Controls.pitch_time = -FrameTime/2;
	if (Controls.vertical_thrust_time < -FrameTime ) Controls.vertical_thrust_time = -FrameTime;
	if (Controls.heading_time < -FrameTime ) Controls.heading_time = -FrameTime;
	if (Controls.sideways_thrust_time < -FrameTime ) Controls.sideways_thrust_time = -FrameTime;
	if (Controls.bank_time < -FrameTime ) Controls.bank_time = -FrameTime;
	if (Controls.forward_thrust_time < -FrameTime ) Controls.forward_thrust_time = -FrameTime;
//	if (Controls.afterburner_time < -FrameTime ) Controls.afterburner_time = -FrameTime;


	if ( (Cruise_speed == i2f(100)) && (Controls.forward_thrust_time < FrameTime ) )
		Int3();

//--------- Don't do anything if in debug mode
	#ifndef NDEBUG
	if ( keyd_pressed[KEY_DELETE] )	{
		memset( &Controls, 0, sizeof(control_info) );
	}
	#endif
}

void reset_cruise(void)
{
	Cruise_speed=0;
}


void kc_set_controls()
{
	int i;

	for (i=0; i<NUM_KEY_CONTROLS; i++ )	
		kc_keyboard[i].value = kconfig_settings[0][i];

	if ( (Config_control_type>0) && (Config_control_type<5))	{
		for (i=0; i<NUM_OTHER_CONTROLS; i++ ) {
			kc_joystick[i].value = kconfig_settings[Config_control_type][i];
			if (kc_joystick[i].type == BT_INVERT )	{
				if (kc_joystick[i].value!=1)
					kc_joystick[i].value	= 0;
				kconfig_settings[Config_control_type][i] = kc_joystick[i].value;
			}
		}
	} else if (Config_control_type>4) {
		for (i=0; i<NUM_OTHER_CONTROLS; i++ )	{
			kc_mouse[i].value = kconfig_settings[Config_control_type][i];
			if (kc_mouse[i].type == BT_INVERT )	{
				if (kc_mouse[i].value!=1)
					kc_mouse[i].value	= 0;
				kconfig_settings[Config_control_type][i] = kc_mouse[i].value;
			}
		}
	}
}


int SenseStatus1( void )
{
#if 0
	union  REGS     regs;
	struct SREGS    sregs;
	int function, result, i;

	for( i=MIN_SENSE_FUNCTION; i <= MAX_SENSE_FUNCTION; i++ )	{
		result    = i;
		result   |= (SENSE_DRIVER_STATUS << 8);
		function  = SENSE_DRIVER_STATUS;
		function |= (i << 8);        
		memset( &regs, 0, sizeof(regs));
		memset( &sregs, 0, sizeof(sregs));
		regs.x.ecx = 0;
		regs.x.edx = 0;
		regs.x.ebx = 0;
		regs.x.eax = function;
		int386( SENSE_VECTOR, &regs, &regs );
        
		if( regs.x.eax == result )
			return( function & 0xFF00 );
	}
#endif    
	return( 0 );
}

int SenseGetData( int function, int cls, fix *yaw, fix *pitch, fix *roll, int *buttons )
{
#if 0
	union  REGS     regs;
	struct SREGS    sregs;
	memset( &regs, 0, sizeof(regs));
	memset( &sregs, 0, sizeof(sregs));
	regs.x.eax = function | GET_DEVICE_DATA;
	regs.x.ebx = 1 | (cls << 8);

	int386x( SENSE_VECTOR, &regs, &regs, &sregs);
    
	*yaw     = (short)(regs.x.ebx & 0xffff);
	*pitch   = (short)(regs.x.ecx & 0xffff);
	*roll    = (short)(regs.x.edx & 0xffff);
	*yaw *= -1;
	*pitch *= -1;
	*roll *= -1;
	*buttons = regs.x.eax & 0x00FF;
    
	return( (int)(regs.x.eax >> 8) );
#endif
	return 0;
}

//--unused-- int SenseSetVideo( int function, int cls, int mode )
//--unused-- {
//--unused-- 	union  REGS     regs;
//--unused-- 	struct SREGS    sregs;
//--unused-- 	memset( &regs, 0, sizeof(regs));
//--unused-- 	memset( &sregs, 0, sizeof(sregs));
//--unused-- 	regs.x.eax = function | SET_DEVICE_DATA;
//--unused-- 	regs.x.ebx = 1 | (cls << 8);
//--unused-- 	regs.x.ecx = mode;
//--unused-- 
//--unused-- 	int386x( SENSE_VECTOR, &regs, &regs, &sregs);
//--unused--     
//--unused-- 	return( (int)(regs.x.eax >> 8) );
//--unused-- }

void kconfig_center_headset()
{
	if (vfx1_installed)
		SenseSetZero( sense_function1, DCHTD );                    
//	} else if (iglasses_headset_installed)	{
//	} else if (Victor_headset_installed)   {
//	} else {
//	}

}

int SenseSetZero( int function, int cls )
{
#if 0
	union  REGS     regs;
	struct SREGS    sregs;
	memset( &regs, 0, sizeof(regs));
	memset( &sregs, 0, sizeof(sregs));
	regs.x.eax = function | SET_ZERO;
	regs.x.ebx = 1 | (cls << 8);

	int386x( SENSE_VECTOR, &regs, &regs, &sregs);
    
	return( (int)(regs.x.eax >> 8) );
#endif
	return 0;
}

//--unused-- int SenseReSetZero( int function, int cls )
//--unused-- {
//--unused-- 	union  REGS     regs;
//--unused-- 	struct SREGS    sregs;
//--unused-- 	memset( &regs, 0, sizeof(regs));
//--unused-- 	memset( &sregs, 0, sizeof(sregs));
//--unused-- 	regs.x.eax = function | RESET_ZERO;
//--unused-- 	regs.x.ebx = 1 | (cls << 8);
//--unused-- 
//--unused-- 	int386x( SENSE_VECTOR, &regs, &regs, &sregs);
//--unused--     
//--unused-- 	return( (int)(regs.x.eax >> 8) );
//--unused-- }

void kconfig_sense_init()
{
	int ret;
	fix htd_y,htd_p,htd_r;
	int htd_b;

	sense_function1 = SenseStatus1();
//	printf("Sense installed %x\n", sense_function1 );

	if(sense_function1)	{
		ret = SenseGetData( sense_function1,DCHTD,&htd_y,&htd_p,&htd_r,&htd_b);
		if (!ret)	{
			vfx1_installed = 1;
			printf("%s\n", TXT_USING_VFX1 );
		} else {
			printf("%s\n", TXT_VFX1_ERROR1);
		}
	} else {
		printf( TXT_VFX1_ERROR2 );
	}
}

