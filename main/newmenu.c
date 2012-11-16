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
 * $Source: BigRed:miner:source:main::RCS:newmenu.c $
 * $Revision: 1.26 $
 * $Author: allender $
 * $Date: 1996/04/14 21:07:35 $
 * 
 * Routines for menus.
 * 
 * $Log: newmenu.c $
 * Revision 1.26  1996/04/14  21:07:35  allender
 * some change for update
 *
 * Revision 1.25  1995/10/31  10:19:25  allender
 * shareware stuff
 *
 * Revision 1.24  1995/10/27  11:09:04  allender
 * always cd to descent dir before any menu processing --
 * sanity check because of way mac does volume mounting and
 * other file stuff
 *
 * Revision 1.23  1995/10/24  18:11:19  allender
 * do_appl_quit saves and restores background -- don't
 * do any special processing.  fixed newmenu_do3 to pass width
 * and height to ...do_4
 *
 * Revision 1.22  1995/10/21  23:26:25  allender
 * can't do cmd-q in multiplayer games
 *
 * Revision 1.21  1995/10/21  22:53:25  allender
 * menus need to be 8 byte multiple wide -- printscreen stuff
 *
 * Revision 1.20  1995/10/20  00:50:15  allender
 * redbook stuff and make esc leave menu always
 *
 * Revision 1.19  1995/10/17  13:14:52  allender
 * mouse support for other menus now operational -- dragging
 * mouse will also move sliders
 *
 * Revision 1.18  1995/10/12  17:35:19  allender
 * mouse support for pilot and demos
 *
 * Revision 1.17  1995/10/11  12:17:47  allender
 * removed event loop processing
 *
 * Revision 1.16  1995/10/10  11:51:29  allender
 * align menus to 8 byte boundry
 *
 * Revision 1.15  1995/10/05  14:09:36  allender
 * lowered starting x location on menus to fixup network
 * status screen chopping off characters
 *
 * Revision 1.14  1995/09/24  10:52:27  allender
 * made close boxes work
 * maybe some other minor stuff?
 *
 * Revision 1.13  1995/09/15  09:02:04  allender
 * started putting mouse support in listboxes
 *
 * Revision 1.12  1995/09/13  08:50:14  allender
 * close box in this rev?  Worked on getting list box better
 * looking
 *
 * Revision 1.11  1995/09/01  10:52:37  allender
 * fixed up list boxes
 *
 * Revision 1.10  1995/08/24  16:23:08  allender
 * mouse support for most menus
 *
 * Revision 1.9  1995/08/08  13:46:56  allender
 * added macsys header file
 *
 * Revision 1.8  1995/08/01  16:03:54  allender
 * added file list with Desalvo's directory stuff
 *
 * Revision 1.7  1995/07/26  17:03:37  allender
 * show then hide cursor during newmenu operations -- not quite
 * right yet
 *
 * Revision 1.6  1995/07/17  08:56:26  allender
 * fixed up menus to look better with new high res fonts
 *
 * Revision 1.5  1995/07/12  10:35:52  allender
 * removed old debug thing
 *
 * Revision 1.4  1995/06/23  10:23:21  allender
 * menus should work in any resolution now
 *
 * Revision 1.3  1995/06/20  09:11:19  allender
 * changed menu system to support 640x480 instead of 320x200
 *
 * Revision 1.2  1995/06/13  13:07:30  allender
 * added special key to move 320x200 window to upper left corner of screen
 *
 * Revision 1.1  1995/05/16  15:29:13  allender
 * Initial revision
 *
 * Revision 2.6  1995/03/21  08:38:46  john
 * Ifdef'd out the NETWORK code.
 * 
 * Revision 2.5  1995/03/15  14:33:29  john
 * Added code to force the Descent CD-rom in the drive.
 * 
 * Revision 2.4  1995/03/14  18:24:28  john
 * Force Destination Saturn to use CD-ROM drive.
 * 
 * Revision 2.3  1995/03/14  16:22:23  john
 * Added cdrom alternate directory stuff.
 * 
 * Revision 2.2  1995/03/06  18:30:51  john
 * Fixed bug with newmenu trashing editor font.
 * 
 * Revision 2.1  1995/03/06  15:23:17  john
 * New screen techniques.
 * 
 * Revision 2.0  1995/02/27  11:27:55  john
 * New version 2.0, which has no anonymous unions, builds with
 * Watcom 10.0, and doesn't require parsing BITMAPS.TBL.
 * 
 * Revision 1.129  1995/02/11  16:19:56  john
 * Added code to make the default mission be the one last played.
 * 
 * Revision 1.128  1995/02/02  19:41:33  john
 * Added 10 save game slots.
 * 
 * Revision 1.127  1995/02/01  18:13:52  john
 * Fixed some constants.
 * 
 * Revision 1.126  1995/02/01  18:04:01  yuan
 * Added 50 characters to list.
 * 
 * Revision 1.125  1995/02/01  13:39:35  john
 * Made menu text that changes not overwrite.
 * 
 * Revision 1.124  1995/01/31  10:47:57  john
 * Added menu that you can specify the width of the menu.
 * 
 * Revision 1.123  1995/01/28  17:18:12  john
 * Added file list box.
 * 
 * Revision 1.122  1995/01/27  17:15:55  john
 * Made prev comment actually work.
 * 
 * Revision 1.121  1995/01/27  16:49:03  john
 * *** empty log message ***
 * 
 * Revision 1.120  1995/01/27  16:46:40  john
 * Made so that input_menu only clears text if -empty-.
 * 
 * Revision 1.119  1995/01/27  15:25:04  john
 * Delete saved game when deleteing a pilot file.
 * 
 * Revision 1.118  1995/01/25  16:36:09  john
 * Made so that when you hit enter during
 * game save, -empty- goes away.
 * 
 * Revision 1.117  1995/01/24  16:59:30  john
 * took out mono debugging text.
 * 
 * Revision 1.116  1995/01/24  16:23:16  john
 * Fixed some bugs with listboxes.
 * 
 * Revision 1.115  1995/01/23  23:47:36  matt
 * Made keypad enter work in menus
 * 
 * Revision 1.114  1995/01/23  19:29:59  john
 * Added scrolling listbox menus.
 * 
 * Revision 1.113  1995/01/19  12:33:34  john
 * Made keys jump to sliders, etc in menus.
 * 
 * Revision 1.112  1995/01/15  14:33:08  rob
 * Fixed problem with nested nm_messageboxes.
 * 
 * Revision 1.111  1995/01/03  17:33:40  john
 * Made scrolling textbox. Used it for scores cool saying.
 * 
 * Revision 1.110  1994/12/28  10:42:58  john
 * More VFX tweaking.
 * 
 * Revision 1.109  1994/12/28  10:26:39  john
 * Fixed some VFX problems.
 * 
 * Revision 1.108  1994/12/15  23:18:10  john
 * Added fix so that VFX mode doesn't hang.
 * 
 * Revision 1.107  1994/12/15  12:19:55  john
 * Made menu use clipped bitblt functions.
 * 
 * Revision 1.106  1994/12/09  00:41:30  mike
 * fix hang in automap print screen
 * 
 * Revision 1.105  1994/12/08  10:01:34  john
 * Changed the way the player callsign stuff works.
 * 
 * Revision 1.104  1994/12/04  15:34:30  john
 * Fixed bug with newmenu not restoring font properly.
 * 
 * Revision 1.103  1994/12/03  17:47:09  john
 * Fixed bug that didn't free filename mem when not .plr files found.
 * 
 * Revision 1.102  1994/12/03  15:06:15  john
 * If no pilot exists, bring up box asking for name.
 * 
 * Revision 1.101  1994/12/03  11:04:02  john
 * Changed newmenu code a bit to fix bug with bogus
 * backgrounds occcasionally.
 * 
 * Revision 1.100  1994/12/01  20:15:48  yuan
 * Localization.
 * 
 * Revision 1.99  1994/12/01  10:33:28  john
 * Fixed bug with large menu backgrounds not drawing correctly.
 * 
 * Revision 1.98  1994/12/01  02:41:56  john
 * Fixed warnining.
 * 
 * Revision 1.97  1994/11/30  22:52:43  john
 * Fixed bug in code that made the backgrounds behind menus.
 * 
 * Revision 1.96  1994/11/30  19:47:42  john
 * Added a check for out o' memory when mallocing background.
 * 
 * Revision 1.95  1994/11/30  19:39:10  john
 * ..
 * 
 * Revision 1.94  1994/11/30  19:38:27  john
 * fixed bug with previous.
 * 
 * Revision 1.93  1994/11/30  19:36:47  john
 * Made Gravis Ultrasound work again.  Made the scores blink
 * at a constant rate.  Revamped the newmenu background storage,
 * which hopefully fixed some bugs.  Made menus in ame not pause
 * sound, except for the pause key.               ^== Game!
 * 
 * Revision 1.92  1994/11/30  18:06:05  matt
 * When player types space in callsign, comes up as underscore
 * 
 * Revision 1.91  1994/11/30  12:28:22  adam
 * added PCX support
 * 
 * Revision 1.90  1994/11/30  12:10:59  adam
 * added support for PCX titles/brief screens
 * 
 * Revision 1.89  1994/11/29  00:59:12  allender
 * change newmenu_get_filename so demo files can be deleted too
 * 
 * Revision 1.88  1994/11/27  21:16:18  allender
 * made some return values in newmenu_get_filename 0 instead of -1
 * 
 * Revision 1.87  1994/11/27  16:58:17  matt
 * Made printscreen work all the time (not just when no ndebug) and made it
 * work when getting a filename.
 * 
 * Revision 1.86  1994/11/27  16:47:51  john
 * Made the call to fade in palette only happen if it needs to be, just
 * because I thought it might reduce code paging with vm in menus.
 * 
 * Revision 1.85  1994/11/26  15:30:16  matt
 * Allow escape out of change pilot menu
 * 
 * Revision 1.84  1994/11/26  14:17:26  matt
 * Player can now only enter valid chars for his name
 * 
 * Revision 1.83  1994/11/23  14:13:17  allender
 * if no demo files, displays less "techy" message
 * 
 * Revision 1.82  1994/11/21  11:55:52  john
 * Fixed some sound pausing in menus bugs.
 * 
 * Revision 1.81  1994/11/19  15:14:58  mike
 * remove unused code and data
 * 
 * Revision 1.80  1994/11/18  23:37:54  john
 * Changed some shorts to ints.
 * 
 * Revision 1.79  1994/11/15  09:29:21  john
 * Made it so that pressing a letter when selecting players moves to 
 * a matching choice.
 * 
 * Revision 1.78  1994/11/14  17:12:28  adam
 * *** empty log message ***
 * 
 * Revision 1.77  1994/11/14  16:58:31  rob
 * Tried to fix a problem with save demo dialog.
 * 
 * Revision 1.76  1994/11/14  16:13:46  matt
 * Fixed handling of players with DOS device names
 * 
 * Revision 1.75  1994/11/13  18:12:53  matt
 * Fixed handling of filenames that are the same as DOS devices
 * 
 * Revision 1.74  1994/11/13  17:20:44  john
 * Fixed text a bit.
 * 
 * Revision 1.73  1994/11/13  17:18:22  john
 * Changed wording of new pilot.
 * 
 * Revision 1.72  1994/11/13  17:14:21  john
 * Fixed bug with player list box.
 * 
 * Revision 1.71  1994/11/13  17:12:48  john
 * Fixed broken demo file list.
 * 
 * Revision 1.70  1994/11/13  17:04:49  john
 * Made the callsign entry be a list box and gave the ability
 * to delete players.
 * 
 * Revision 1.69  1994/11/13  15:38:03  john
 * Added critical error handler to game.  Took out -editor command line
 * option because it didn't work anymore and wasn't worth fixing.  Made scores
 * not use MINER enviroment variable on release version, and made scores
 * not print an error if there is no descent.hi.
 * 
 * Revision 1.68  1994/11/11  18:17:03  rob
 * Made multi_menu_poll return a value to exit menus.
 * 
 * Revision 1.67  1994/11/11  11:07:06  rob
 * Added include of multi.h
 * 
 * Revision 1.66  1994/11/10  20:25:16  rob
 * John's stuff to make network menus work.
 * 
 * Revision 1.65  1994/11/08  14:51:39  john
 * Added nm_messagebox1, (like the original, only you can pass a function).
 * 
 * Revision 1.64  1994/11/08  08:30:39  john
 * Fixed bug with centering titles.
 * 
 * Revision 1.63  1994/11/08  08:27:00  john
 * Made titles and subtitles center.
 * 
 * Revision 1.62  1994/11/07  09:40:48  john
 * Neatend file list box some.
 * 
 * Revision 1.61  1994/11/05  17:22:41  john
 * Fixed lots of sequencing problems with newdemo stuff.
 * 
 * Revision 1.60  1994/11/05  15:04:08  john
 * Added non-popup menu for the main menu, so that scores and credits don't have to save
 * the background.
 * 
 * Revision 1.59  1994/11/05  14:03:52  john
 * Fixed fade transitions between all screens by making gr_palette_fade_in and out keep
 * track of whether the palette is faded in or not.  Then, wherever the code needs to fade out,
 * it just calls gr_palette_fade_out and it will fade out if it isn't already.  The same with fade_in.
 * This eliminates the need for all the flags like Menu_fade_out, game_fade_in palette, etc.
 * 
 * Revision 1.58  1994/11/04  20:11:50  john
 * Neatening up palette stuff with demos.
 * 
 * Revision 1.57  1994/11/04  13:49:24  allender
 * fixed newmenu_get_filename to work with less than 10 files
 * 
 * Revision 1.56  1994/11/03  19:37:44  john
 * Added scrolling file list box
 * 
 * Revision 1.55  1994/10/31  18:16:42  john
 * Made Pad arrows work with menus.
 * 
 * Revision 1.54  1994/10/28  14:54:25  john
 * Added forward dec. for newmenu_close.
 * .\
 * 
 * Revision 1.53  1994/10/28  14:53:00  john
 * Fixed hideous bug that would bomb if you called newmenu_draw_background
 * before any menus were ever displayed.
 * 
 * Revision 1.52  1994/10/24  19:56:53  john
 * Made the new user setup prompt for config options.
 * 
 * Revision 1.51  1994/10/24  15:15:49  john
 * Made Esc exit nm_messagebox's,
 * ,
 * 
 * Revision 1.50  1994/10/21  15:20:20  john
 * Made PrtScr do screen dump, not F2.
 * 
 * Revision 1.49  1994/10/18  12:33:38  john
 * Only used copy the item text into the saved_text field
 * if it is an inputbox or inputbox_menu.
 * 
 * Revision 1.48  1994/10/17  11:04:01  john
 * Made backtab work also.
 * 
 * Revision 1.47  1994/10/17  10:47:49  john
 * MAde Tab work like down arrow.
 * 
 * Revision 1.46  1994/10/17  10:45:10  john
 * Made the player able to abort death by pressing any button or key.
 * 
 * Revision 1.45  1994/10/13  21:52:02  john
 * Made it so that if a messagebox has 1 choice, then
 * Esc will return -1.
 * 
 * Revision 1.44  1994/10/13  11:35:38  john
 * Made Thrustmaster FCS Hat work.  Put a background behind the
 * keyboard configure.  Took out turn_sensitivity.  Changed sound/config
 * menu to new menu. Made F6 be calibrate joystick.
 * 
 * Revision 1.43  1994/10/11  17:18:52  john
 * Fixed bug with sliders always starting at -1.
 * 
 * Revision 1.42  1994/10/11  17:08:29  john
 * Added sliders for volume controls.
 * 
 * Revision 1.41  1994/10/06  16:04:40  john
 * Made text items color differently than others. Adam
 * is gonna make a diff colored font for these.
 * 
 * Revision 1.40  1994/10/06  15:08:23  rob
 * Allowed any negative key value to abort the menu and return.
 * 
 * Revision 1.39  1994/10/04  10:26:06  matt
 * Changed fade in to happen every time a global var is set
 * 
 * Revision 1.38  1994/10/04  09:16:08  john
 * If you pass -1 as choice in newmenu_do1, then
 * no item is highlighted until you press up or
 * down arrows.
 * 
 * Revision 1.37  1994/10/03  23:44:37  matt
 * Save & restore palette effect around menus & pause message
 * 
 * Revision 1.36  1994/10/03  22:59:40  matt
 * Re-enabled backspace to generate Int3()
 * 
 * Revision 1.35  1994/10/03  19:11:21  matt
 * Changed string input cursor to blinking underscore
 * 
 * Revision 1.34  1994/10/03  14:44:15  john
 * Added newmenu_do1, which allows you to pass the starting
 * item to the menu system
 * 
 * Revision 1.33  1994/09/30  11:51:21  john
 * Added Matt's NM_TYPE_INPUT_MENU
 * 
 * Revision 1.32  1994/09/28  17:22:56  matt
 * Added extra space between subtitle and menu items
 * Made shortcut key check ignore leading spaces in text
 * 
 * Revision 1.31  1994/09/15  16:11:22  john
 * Added support for VFX1 head tracking. Fixed bug with memory over-
 * write when using stereo mode.
 * 
 * Revision 1.30  1994/09/12  09:52:59  john
 * Made global flush function that flushes keyboard,mouse, and joystick.
 * 
 * Revision 1.29  1994/09/10  19:10:54  matt
 * Fixed a few things (like arrow key handling) for menus with all
 * text items, such as the key help message.
 * 
 * Revision 1.28  1994/09/01  18:55:38  john
 * freed scores.lbm
 * 
 * Revision 1.27  1994/09/01  18:03:50  john
 * Neatened up scores a bit.
 * 
 * Revision 1.26  1994/08/30  20:38:13  john
 * Passed citem in newmenu sub.
 * 
 * Revision 1.25  1994/08/30  11:13:01  john
 * Added beveled edges to menus.
 * 
 * Revision 1.24  1994/08/26  13:01:58  john
 * Put high score system in.
 * 
 * Revision 1.23  1994/08/16  00:18:44  john
 * Made pressing the first letter of a menu
 * item move to it.
 * 
 * Revision 1.22  1994/08/15  23:17:43  john
 * *** empty log message ***
 * 
 * Revision 1.21  1994/08/15  23:15:28  john
 * Made 1 menu/checkbox return with any keypress.
 * 
 * Revision 1.20  1994/08/12  10:18:23  john
 * *** empty log message ***
 * 
 * Revision 1.19  1994/08/12  10:09:11  john
 * Made borders better.
 * 
 * Revision 1.18  1994/08/12  03:11:16  john
 * Made network be default off; Moved network options into
 * main menu.  Made starting net game check that mines are the
 * same.
 * 
 * Revision 1.17  1994/08/11  22:14:43  john
 * Free'd up some memory that I forgot to free.
 * 
 * Revision 1.16  1994/08/11  19:27:35  john
 * Made the Backspace drop into the debugger only
 * if you're not in an inputbox.
 * 
 * Revision 1.15  1994/08/11  18:01:49  matt
 * Added F2 and BACKSPACE keys to new menu system
 * 
 * Revision 1.14  1994/08/11  14:25:58  john
 * *** empty log message ***
 * 
 * Revision 1.13  1994/08/11  14:25:40  john
 * *** empty log message ***
 * 
 * Revision 1.12  1994/08/11  13:47:02  john
 * Made newmenu have subtitles, passed key through to
 * the newmenu subfunctions.
 * 
 * Revision 1.11  1994/08/11  12:45:08  john
 * *** empty log message ***
 * 
 * Revision 1.10  1994/08/11  12:25:45  john
 * Made right_offset spacing different
 * 
 * Revision 1.9  1994/08/11  12:09:49  john
 * Made work with bitmapped fonts.
 * 
 * Revision 1.8  1994/08/10  19:56:16  john
 * Changed font stuff; Took out old menu; messed up lots of
 * other stuff like game sequencing messages, etc.
 * 
 * Revision 1.7  1994/07/27  16:12:23  john
 * Changed newmenu system to have a callback function.
 * /.
 * 
 * Revision 1.6  1994/07/25  15:10:23  john
 * *** empty log message ***
 * 
 * Revision 1.5  1994/07/25  12:33:35  john
 * Network "pinging" in.
 * 
 * Revision 1.4  1994/07/24  18:21:27  john
 * Took out first time stuff.
 * 
 * Revision 1.3  1994/07/24  17:32:47  john
 * Added percent item.  Also neatend up a bit.
 * 
 * Revision 1.2  1994/07/22  17:48:13  john
 * Added new menuing system.
 * 
 * Revision 1.1  1994/07/22  13:55:38  john
 * Initial revision
 * 
 * 
 */


#pragma off (unreferenced)
static char rcsid[] = "$Id: newmenu.c 1.26 1996/04/14 21:07:35 allender Exp allender $";
#pragma on (unreferenced)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <ctype.h>
#include <Memory.h>

#include "error.h"
#include "dtypes.h"
#include "gr.h"
#include "mono.h"
#include "key.h"
#include "palette.h"
#include "game.h"
#include "text.h"

#include "newmenu.h"
#include "gamefont.h"
#include "network.h"
#include "iff.h"
#include "pcx.h"
#include "mem.h"
#include "mouse.h"
#include "joy.h"
#include "digi.h"

#include "multi.h"
#include "endlevel.h"
#include "screens.h"
#include "vfx.h"
#include "kconfig.h"
#include "player.h"
#include "macsys.h"
#include "direct.h"		// Thanks Chris!
#include "macsys.h"
#include "redbook.h"

#define TITLE_FONT  		(Gamefonts[GFONT_BIG_1])

#define SUBTITLE_FONT	(Gamefonts[GFONT_MEDIUM_3])
#define CURRENT_FONT  	(Gamefonts[GFONT_MEDIUM_2])
#define NORMAL_FONT  	(Gamefonts[GFONT_MEDIUM_1])
#define TEXT_FONT  		(Gamefonts[GFONT_MEDIUM_3])

#if 0
#define NORMAL_CHECK_BOX	""
#define CHECKED_CHECK_BOX	"‚"
#define NORMAL_RADIO_BOX	""
#define CHECKED_RADIO_BOX	"€"
#define CURSOR_STRING		"_"
#define SLIDER_LEFT			"ƒ"		// 131
#define SLIDER_RIGHT			"„"		// 132
#define SLIDER_MIDDLE		"…"		// 133
#define SLIDER_MARKER		"†"		// 134
#endif

#define CURSOR_STRING		"_"
unsigned char NORMAL_CHECK_BOX[2];
unsigned char CHECKED_CHECK_BOX[2];
unsigned char NORMAL_RADIO_BOX[2];
unsigned char CHECKED_RADIO_BOX[2];
unsigned char SLIDER_LEFT[2];
unsigned char SLIDER_RIGHT[2];
unsigned char SLIDER_MIDDLE[2];
unsigned char SLIDER_MARKER[2];

int Newmenu_first_time = 1;
//--unused-- int Newmenu_fade_in = 1;

typedef struct bkg {
	grs_canvas * menu_canvas;
	grs_bitmap * saved;			// The background under the menu.
	grs_bitmap * background;
} bkg;

grs_bitmap nm_background;

//#define MESSAGEBOX_TEXT_SIZE 300		// How many characters in messagebox
//#define MAX_TEXT_WIDTH 	200				// How many pixels wide a input box can be

#define MESSAGEBOX_TEXT_SIZE 600		// How many characters in messagebox
#define MAX_TEXT_WIDTH 	400				// How many pixels wide a input box can be

extern void gr_bm_bitblt(int w, int h, int dx, int dy, int sx, int sy, grs_bitmap * src, grs_bitmap * dest);

void newmenu_close()	{
	if ( nm_background.bm_data )
		myfree(nm_background.bm_data);
	Newmenu_first_time = 1;
}

void nm_draw_background1(char * filename)
{
	int pcx_error;
	grs_bitmap *bmp;
	int x, y;
	ubyte pal[768];

	gr_clear_canvas( BM_XRGB(0,0,0) );
	x = (grd_curcanv->cv_bitmap.bm_w - grd_curscreen->sc_w) / 2;
	y = (grd_curcanv->cv_bitmap.bm_h - grd_curscreen->sc_h) / 2;
	bmp = gr_create_sub_bitmap( &grd_curcanv->cv_bitmap, x, y, grd_curscreen->sc_w, grd_curscreen->sc_h );
	pcx_error = pcx_read_bitmap(filename,bmp,bmp->bm_type,pal);
	Assert(pcx_error == PCX_ERROR_NONE);
	
	gr_free_sub_bitmap(bmp);
}

void nm_draw_background(int x1, int y1, int x2, int y2 )
{
	int w,h;

	if (Newmenu_first_time)	{
		int pcx_error;
		ubyte newpal[768];
		atexit( newmenu_close );
		Newmenu_first_time = 0;

		nm_background.bm_data=NULL;		
		pcx_error = pcx_read_bitmap("SCORES.PCX",&nm_background,BM_LINEAR,newpal);
		Assert(pcx_error == PCX_ERROR_NONE);

		gr_remap_bitmap_good( &nm_background, newpal, -1, -1 );
		
//  Assign character values to special characters;
		sprintf (NORMAL_RADIO_BOX, "%c", 127);
		sprintf (CHECKED_RADIO_BOX, "%c", 128);
		sprintf (NORMAL_CHECK_BOX, "%c", 129);
		sprintf (CHECKED_CHECK_BOX, "%c", 130);
		sprintf (SLIDER_LEFT, "%c", 131);
		sprintf (SLIDER_RIGHT, "%c", 132);
		sprintf (SLIDER_MIDDLE, "%c", 133);
		sprintf (SLIDER_MARKER, "%c", 134);
	}

	if ( x1 < 0 ) x1 = 0;
	if ( y1 < 0 ) y1 = 0;

	w = x2-x1+1;
	h = y2-y1+1;

	if ( w > nm_background.bm_w ) w = nm_background.bm_w;
	if ( h > nm_background.bm_h ) h = nm_background.bm_h;
	
	x2 = x1 + w - 1;
	y2 = y1 + h - 1;

	gr_bm_bitblt(w, h, x1, y1, 0, 0, &nm_background, &(grd_curcanv->cv_bitmap) );

	Gr_scanline_darkening_level = 2*7;

	gr_setcolor( BM_XRGB(0,0,0) );
	gr_urect( x2-5, y1+5, x2-5, y2-5 );
	gr_urect( x2-4, y1+4, x2-4, y2-5 );
	gr_urect( x2-3, y1+3, x2-3, y2-5 );
	gr_urect( x2-2, y1+2, x2-2, y2-5 );
	gr_urect( x2-1, y1+1, x2-1, y2-5 );
	gr_urect( x2+0, y1+0, x2-0, y2-5 );

	gr_urect( x1+5, y2-5, x2, y2-5 );
	gr_urect( x1+4, y2-4, x2, y2-4 );
	gr_urect( x1+3, y2-3, x2, y2-3 );
	gr_urect( x1+2, y2-2, x2, y2-2 );
	gr_urect( x1+1, y2-1, x2, y2-1 );
	gr_urect( x1+0, y2, x2, y2-0 );

	Gr_scanline_darkening_level = GR_FADE_LEVELS;
}

void nm_restore_background( int x, int y, int w, int h )
{
	int x1, x2, y1, y2;

	x1 = x; x2 = x+w-1;
	y1 = y; y2 = y+h-1;

	if ( x1 < 0 ) x1 = 0;
	if ( y1 < 0 ) y1 = 0;

	if ( x2 >= nm_background.bm_w ) x2=nm_background.bm_w-1;
	if ( y2 >= nm_background.bm_h ) y2=nm_background.bm_h-1;

	w = x2 - x1 + 1;
	h = y2 - y1 + 1;

	gr_bm_bitblt(w, h, x1, y1, x1, y1, &nm_background, &(grd_curcanv->cv_bitmap) );
}

// Draw a left justfied string
void nm_string( bkg * b, int w1,int x, int y, char * s )
{
	int w,h,aw;
	char *p,*s1;

	p = strchr( s, '\t' );
	if (p && (w1>0) )	{
		*p = '\0';
		s1 = p+1;
	}

	gr_get_string_size(s, &w, &h, &aw  );

	if (w1 > 0)
		w = w1;

	// CHANGED
	gr_bm_bitblt(b->background->bm_w-15, h, 5, y, 5, y, b->background, &(grd_curcanv->cv_bitmap) );
	//gr_bm_bitblt(w, h, x, y, x, y, b->background, &(grd_curcanv->cv_bitmap) );
	
	gr_string( x, y, s );

	if (p && (w1>0) )	{
		gr_get_string_size(s1, &w, &h, &aw  );

		gr_string( x+w1-w, y, s1 );

		*p = '\t';
	}

}


// Draw a slider and it's string
void nm_string_slider( bkg * b, int w1,int x, int y, char * s )
{
	int w,h,aw;
	char *p,*s1;

	p = strchr( s, '\t' );
	if (p)	{
		*p = '\0';
		s1 = p+1;
	}

	gr_get_string_size(s, &w, &h, &aw  );
	// CHANGED
	gr_bm_bitblt(b->background->bm_w-15, h, 5, y, 5, y, b->background, &(grd_curcanv->cv_bitmap) );
	//gr_bm_bitblt(w, h, x, y, x, y, b->background, &(grd_curcanv->cv_bitmap) );

	gr_string( x, y, s );

	if (p)	{
		gr_get_string_size(s1, &w, &h, &aw  );

		// CHANGED
		gr_bm_bitblt(w, 1, x+w1-w, y, x+w1-w, y, b->background, &(grd_curcanv->cv_bitmap) );
		// CHANGED
		gr_bm_bitblt(w, 1, x+w1-w, y+h-1, x+w1-w, y, b->background, &(grd_curcanv->cv_bitmap) );

		gr_string( x+w1-w, y, s1 );

		*p = '\t';
	}

}


// Draw a left justfied string with black background.
void nm_string_black( bkg * b, int w1,int x, int y, char * s )
{
	int w,h,aw;
	gr_get_string_size(s, &w, &h, &aw  );
	b = b;					
	if (w1 == 0) w1 = w;

	gr_setcolor( BM_XRGB(0,0,0) );
	gr_rect( x, y, x+w1-1, y+h-1 );
	
	gr_string( x, y, s );
}


// Draw a right justfied string
void nm_rstring( bkg * b,int w1,int x, int y, char * s )
{
	int w,h,aw;
	gr_get_string_size(s, &w, &h, &aw  );
	x -= 6;

	if (w1 == 0) w1 = w;

	//mprintf( 0, "Width = %d, string='%s'\n", w, s );

	// CHANGED
	gr_bm_bitblt(w1, h, x-w1, y, x-w1, y, b->background, &(grd_curcanv->cv_bitmap) );
	
	gr_string( x-w, y, s );
}

#include "timer.h"

//for text items, constantly redraw cursor (to achieve flash)
update_cursor( newmenu_item *item)
{
	int w,h,aw;
//	fix time = timer_get_approx_seconds();
	fix time = timer_get_fixed_seconds();
	int x,y;
	char * text = item->text;

	Assert(item->type==NM_TYPE_INPUT_MENU || item->type==NM_TYPE_INPUT);

	while( *text )	{
		gr_get_string_size(text, &w, &h, &aw  );
		if ( w > item->w-10 )
			text++;
		else
			break;
	}
	if (*text==0) 
		w = 0;
	x = item->x+w; y = item->y;

	if (time & 0x8000)
		gr_string( x, y, CURSOR_STRING );
	else {
		gr_setcolor( BM_XRGB(0,0,0) );
		gr_rect( x, y, x+grd_curcanv->cv_font->ft_w-1, y+grd_curcanv->cv_font->ft_h-1 );
	}

}

void nm_string_inputbox( bkg *b, int w, int x, int y, char * text, int current )
{
	int w1,h1,aw;

	while( *text )	{
		gr_get_string_size(text, &w1, &h1, &aw  );
		if ( w1 > w-10 )
			text++;
		else
			break;
	}
	if ( *text == 0 )
		w1 = 0;
	nm_string_black( b, w, x, y, text );

	if ( current )	{
		gr_string( x+w1, y, CURSOR_STRING );
	}
}

void draw_item( bkg * b, newmenu_item *item, int is_current )
{
	if (is_current)
		grd_curcanv->cv_font = CURRENT_FONT;
	else
		grd_curcanv->cv_font = NORMAL_FONT;
	
	switch( item->type )	{
	case NM_TYPE_TEXT:
		grd_curcanv->cv_font=TEXT_FONT;
		// fall through on purpose
	case NM_TYPE_MENU:
		nm_string( b, item->w, item->x, item->y, item->text );
		break;
	case NM_TYPE_SLIDER:	{
		int j;
		
		if (item->value < item->min_value) item->value=item->min_value;
		if (item->value > item->max_value) item->value=item->max_value;
		sprintf( item->saved_text, "%s\t%s", item->text, SLIDER_LEFT );
		for (j=0; j<(item->max_value-item->min_value+1); j++ )	{
			sprintf( item->saved_text, "%s%s", item->saved_text,SLIDER_MIDDLE );
		}
		sprintf( item->saved_text, "%s%s", item->saved_text,SLIDER_RIGHT );
		
		item->saved_text[item->value+1+strlen(item->text)+1] = SLIDER_MARKER[0];
		nm_string_slider( b, item->w, item->x, item->y, item->saved_text );
		}
		break;
	case NM_TYPE_INPUT_MENU:
		if ( item->group==0 )		{
			nm_string( b, item->w, item->x, item->y, item->text );
		} else {
			nm_string_inputbox( b, item->w, item->x, item->y, item->text, is_current );
		}
		break;
	case NM_TYPE_INPUT:
		nm_string_inputbox( b, item->w, item->x, item->y, item->text, is_current );
		break;
	case NM_TYPE_CHECK:
		nm_string( b, item->w, item->x, item->y, item->text );
		if (item->value)
			nm_rstring( b,item->right_offset,item->x, item->y, CHECKED_CHECK_BOX );
		else														  
			nm_rstring( b,item->right_offset,item->x, item->y, NORMAL_CHECK_BOX );
		break;
	case NM_TYPE_RADIO:
		nm_string( b, item->w, item->x, item->y, item->text );
		if (item->value)
			nm_rstring( b,item->right_offset, item->x, item->y, CHECKED_RADIO_BOX );
		else
			nm_rstring( b,item->right_offset, item->x, item->y, NORMAL_RADIO_BOX );
		break;
	case NM_TYPE_NUMBER:	{
		char text[10];
		if (item->value < item->min_value) item->value=item->min_value;
		if (item->value > item->max_value) item->value=item->max_value;
		nm_string( b, item->w, item->x, item->y, item->text );
		sprintf( text, "%d", item->value );
		nm_rstring( b,item->right_offset,item->x, item->y, text );
		}
		break;
	}

}

char *Newmenu_allowed_chars=NULL;

//returns true if char is allowed
char_allowed(char c)
{
	char *p = Newmenu_allowed_chars;

	if (!p)
		return 1;

	while (*p) {
		Assert(p[1]);

		if (c>=p[0] && c<=p[1])
			return 1;

		p += 2;
	}

	return 0;
}


void strip_end_whitespace( char * text )
{
	int i,l;
	l = strlen( text );
	for (i=l-1; i>=0; i-- )	{
//		if ( isspace(text[i]) )
		if ( (text[i] == ' ') || (text[i] == '\t'))
			text[i] = 0;
		else
			return;
	}
}

int newmenu_do( char * title, char * subtitle, int nitems, newmenu_item * item, void (*subfunction)(int nitems,newmenu_item * items, int * last_key, int citem) )
{
	return newmenu_do4( title, subtitle, nitems, item, subfunction, 0, NULL, -1, -1, 0 );
}

int newmenu_do1( char * title, char * subtitle, int nitems, newmenu_item * item, void (*subfunction)(int nitems,newmenu_item * items, int * last_key, int citem), int citem )
{
	return newmenu_do4( title, subtitle, nitems, item, subfunction, citem, NULL, -1, -1, 0 );
}


int newmenu_do2( char * title, char * subtitle, int nitems, newmenu_item * item, void (*subfunction)(int nitems,newmenu_item * items, int * last_key, int citem), int citem, char * filename )
{
	return newmenu_do4( title, subtitle, nitems, item, subfunction, citem, filename, -1, -1, 0 );
}

int newmenu_do3( char * title, char * subtitle, int nitems, newmenu_item * item, void (*subfunction)(int nitems,newmenu_item * items, int * last_key, int citem), int citem, char * filename, int width, int height )
{
	return newmenu_do4( title, subtitle, nitems, item, subfunction, citem, filename, width, height, 0);
}

int newmenu_do4( char * title, char * subtitle, int nitems, newmenu_item * item, void (*subfunction)(int nitems,newmenu_item * items, int * last_key, int citem), int citem, char * filename, int width, int height, int close_box )
{
	int mx, my, x1, x2, y1, y2;
	int old_keyd_repeat, done;
	int  choice,old_choice,i,j,x,y,w,h,aw, tw, th, twidth,fm,right_offset;
	int k, nmenus, nothers, mouse_state, omouse_state;
	grs_canvas * save_canvas;
	grs_font * save_font;
	int string_width, string_height, average_width;
	int close_x, close_y, close_size;
	int ty;
	bkg bg;
	int all_text=0;		//set true if all text items
	int time_stopped=0;
	int r;

	CDToDescentDir();								// safety check to get back where to need to

	if (nitems < 1 )
		return -1;

	set_screen_mode(SCREEN_MENU);

//NO_SOUND_PAUSE	if ( Function_mode == FMODE_GAME )	{
//NO_SOUND_PAUSE		digi_pause_all();
//NO_SOUND_PAUSE		sound_stopped = 1;
//NO_SOUND_PAUSE	}

	if (!((Game_mode & GM_MULTI) && (Function_mode == FMODE_GAME) && (!Endlevel_sequence)) )
	{
		time_stopped = 1;
		stop_time();
	}

total_redraw:		

	save_canvas = grd_curcanv;
	gr_set_current_canvas( NULL );			
	save_font = grd_curcanv->cv_font;

	tw = th = 0;

	if ( title )	{
		grd_curcanv->cv_font = TITLE_FONT;
		gr_get_string_size(title,&string_width,&string_height,&average_width );
		tw = string_width;
		th = string_height;
	}
	if ( subtitle )	{
		grd_curcanv->cv_font = SUBTITLE_FONT;
		gr_get_string_size(subtitle,&string_width,&string_height,&average_width );
		if (string_width > tw )
			tw = string_width;
		th += string_height;
	}

//	th += 8;		//put some space between titles & body
	th += 16;		//put some space between titles & body

	grd_curcanv->cv_font = NORMAL_FONT;

	w = aw = 0;
	h = th;
	nmenus = nothers = 0;

	// Find menu height & width (store in w,h)
	for (i=0; i<nitems; i++ )	{
		item[i].redraw=1;
		item[i].y = h;
		gr_get_string_size(item[i].text,&string_width,&string_height,&average_width );
		item[i].right_offset = 0;

		item[i].saved_text[0] = '\0';

		if ( item[i].type == NM_TYPE_SLIDER )	{
			int w1,h1,aw1;
			nothers++;
			sprintf( item[i].saved_text, "%s", SLIDER_LEFT );
			for (j=0; j<(item[i].max_value-item[i].min_value+1); j++ )	{
				sprintf( item[i].saved_text, "%s%s", item[i].saved_text,SLIDER_MIDDLE );
			}
			sprintf( item[i].saved_text, "%s%s", item[i].saved_text,SLIDER_RIGHT );
			gr_get_string_size(item[i].saved_text,&w1,&h1,&aw1 );
			string_width += w1 + aw;
		}

		if ( item[i].type == NM_TYPE_MENU )	{
			nmenus++;
		}

		if ( item[i].type == NM_TYPE_CHECK )	{
			int w1,h1,aw1;
			nothers++;
			gr_get_string_size(NORMAL_CHECK_BOX, &w1, &h1, &aw1  );
			item[i].right_offset = w1;
			gr_get_string_size(CHECKED_CHECK_BOX, &w1, &h1, &aw1  );
			if (w1 > item[i].right_offset)
				item[i].right_offset = w1;
		}
		
		if (item[i].type == NM_TYPE_RADIO ) {
			int w1,h1,aw1;
			nothers++;
			gr_get_string_size(NORMAL_RADIO_BOX, &w1, &h1, &aw1  );
			item[i].right_offset = w1;
			gr_get_string_size(CHECKED_RADIO_BOX, &w1, &h1, &aw1  );
			if (w1 > item[i].right_offset)
				item[i].right_offset = w1;
		}

		if  (item[i].type==NM_TYPE_NUMBER )	{
			int w1,h1,aw1;
			char test_text[20];
			nothers++;
			sprintf( test_text, "%d", item[i].max_value );
			gr_get_string_size( test_text, &w1, &h1, &aw1 );
			item[i].right_offset = w1;
			sprintf( test_text, "%d", item[i].min_value );
			gr_get_string_size( test_text, &w1, &h1, &aw1 );
			if ( w1 > item[i].right_offset)
				item[i].right_offset = w1;
		}

		if ( item[i].type == NM_TYPE_INPUT )	{
			Assert( strlen(item[i].text) < NM_MAX_TEXT_LEN );
			strcpy(item[i].saved_text, item[i].text );
			nothers++;
			string_width = item[i].text_len*grd_curcanv->cv_font->ft_w+item[i].text_len;
			if ( string_width > MAX_TEXT_WIDTH ) 
				string_width = MAX_TEXT_WIDTH;
			item[i].value = -1;
		}

		if ( item[i].type == NM_TYPE_INPUT_MENU )	{
			Assert( strlen(item[i].text) < NM_MAX_TEXT_LEN );
			strcpy(item[i].saved_text, item[i].text );
			nmenus++;
			string_width = item[i].text_len*grd_curcanv->cv_font->ft_w+item[i].text_len;
			item[i].value = -1;
			item[i].group = 0;
		}

		item[i].w = string_width;
		item[i].h = string_height;

		if ( string_width > w )
			w = string_width;		// Save maximum width
		if ( average_width > aw )
			aw = average_width;
		h += string_height+1;		// Find the height of all strings
	}

	right_offset=0;

	if ( width > -1 )
		w = width;

	if ( height > -1 )
		h = height;

	for (i=0; i<nitems; i++ )	{
		item[i].w = w;
		if (item[i].right_offset > right_offset )
			right_offset = item[i].right_offset;
	}
//mwa	if (right_offset > 0 )
//mwa		right_offset += 3;
	if (right_offset > 0 )
		right_offset += 6;
	
	//mprintf( 0, "Right offset = %d\n", right_offset );

	//gr_get_string_size("",&string_width,&string_height,&average_width );

	w += right_offset;

	twidth = 0;
	if ( tw > w )	{
		twidth = ( tw - w )/2;
		w = tw;
	}
			
	// Find min point of menu border
//	x = (grd_curscreen->sc_w-w)/2;
//	y = (grd_curscreen->sc_h-h)/2;

//mwa	w += 30;
//mwa	h += 30;
	w += 60;
	h += 60;

	
	if (r = (w & 0x7))
		w += (8-r);			// align width to 8 byte boundry
		
	if (w > grd_curcanv->cv_bitmap.bm_w) w = grd_curcanv->cv_bitmap.bm_w;
	if (h > grd_curcanv->cv_bitmap.bm_h) h = grd_curcanv->cv_bitmap.bm_h;

	x = (grd_curcanv->cv_bitmap.bm_w-w)/2;
	if (r = (x & 0x7))
		x -= r;				// align x to 8 byte boundry
	y = (grd_curcanv->cv_bitmap.bm_h-h)/2;

	if ( x < 0 ) x = 0;
	if ( y < 0 ) y = 0;

	if ( filename != NULL )	{
		nm_draw_background1( filename );
	}

	// Save the background of the display
	bg.menu_canvas = gr_create_sub_canvas( &grd_curscreen->sc_canvas, x, y, w, h );
	gr_set_current_canvas( bg.menu_canvas );

	if ( filename == NULL )	{
		// Save the background under the menu...
		bg.saved = gr_create_bitmap( w, h );
		Assert( bg.saved != NULL );
		gr_bm_bitblt(w, h, 0, 0, 0, 0, &grd_curcanv->cv_bitmap, bg.saved );
		bg.background = gr_create_sub_bitmap(&nm_background,0,0,w,h);
		gr_set_current_canvas( NULL );
		nm_draw_background(x,y,x+w-1,y+h-1);
		gr_set_current_canvas( bg.menu_canvas );
	} else {
		bg.saved = NULL;
		bg.background = gr_create_bitmap( w, h );
		Assert( bg.background != NULL );
		gr_bm_bitblt(w, h, 0, 0, 0, 0, &grd_curcanv->cv_bitmap, bg.background );
	}

// ty = 15 + (yborder/4);

	ty = 30;

// draw a close box on the menu

	if (close_box) {
		close_x = close_y = 15;
		close_size = 10;
		gr_setcolor( BM_XRGB(0, 0, 0) );
		gr_rect(close_x, close_y, close_x + close_size, close_y + close_size);
		gr_setcolor( BM_XRGB(21, 21, 21) );
		gr_rect( close_x + 2, close_y + 2, close_x + close_size - 2, close_y + close_size -2 );
	}

	if ( title )	{
		grd_curcanv->cv_font = TITLE_FONT;
		gr_set_fontcolor( GR_GETCOLOR(31,31,31), -1 );
		gr_get_string_size(title,&string_width,&string_height,&average_width );
		tw = string_width;
		th = string_height;
		gr_printf( 0x8000, ty, title );
		ty += th;
	}

	if ( subtitle )	{
		grd_curcanv->cv_font = SUBTITLE_FONT;
		gr_set_fontcolor( GR_GETCOLOR(21,21,21), -1 );
		gr_get_string_size(subtitle,&string_width,&string_height,&average_width );
		tw = string_width;
		th = string_height;
		gr_printf( 0x8000, ty, subtitle );
		ty += th;
	}

	grd_curcanv->cv_font = NORMAL_FONT;
	
	// Update all item's x & y values.
	for (i=0; i<nitems; i++ )	{
		item[i].x = 30 + twidth + right_offset;
		item[i].y += 36;
//		item[i].x = 30 + twidth + right_offset;
//		item[i].y += 30;
		if ( item[i].type==NM_TYPE_RADIO )	{
			fm = -1;	// find first marked one
			for ( j=0; j<nitems; j++ )	{
				if ( item[j].type==NM_TYPE_RADIO && item[j].group==item[i].group )	{
					if (fm==-1 && item[j].value)
						fm = j;
					item[j].value = 0;
				}
			}
			if ( fm>=0 )	
				item[fm].value=1;
			else
				item[i].value=1;
		}
	}

	old_keyd_repeat = keyd_repeat;
	keyd_repeat = 1;

	if (citem==-1)	{
		choice = -1;
	} else {
		if (citem < 0 ) citem = 0;
		if (citem > nitems-1 ) citem = nitems-1;
		choice = citem;
	
		while ( item[choice].type==NM_TYPE_TEXT )	{
			choice++;
			if (choice >= nitems ) {
				choice=0; 
			}
			if (choice == citem ) {
				choice=0; 
				all_text=1;
				break; 
			}
		}
	} 
	done = 0;

	// Clear mouse, joystick to clear button presses.
	game_flush_inputs();
	show_cursor();

	mouse_state = omouse_state = 0;
	
	while(!done)	{
		//network_listen();
		
#ifndef MAC_SHAREWARE
		redbook_restart_track();		// restart any music that should be looping
#endif

// read mouse button every 1/10 second
		omouse_state = mouse_state;	
		mouse_state = mouse_button_state(0);

		k = key_inkey();

		if (subfunction)
			(*subfunction)(nitems,item,&k,choice);

		if (!time_stopped)	{
			// Save current menu box
			#ifdef NETWORK
			if (multi_menu_poll() == -1)
				k = -2;
			#endif
		}

		if ( k<-1 ) {
			choice = k;
			k = -1;
			done = 1;
		}

#if 0			// DON'T NEED THIS CODE.   MOUSE ON MACINTOSH IS ABLE TO SELECT MENU ITEMS			
		switch (Config_control_type) {
		case	CONTROL_JOYSTICK:
		case	CONTROL_FLIGHTSTICK_PRO:
		case	CONTROL_THRUSTMASTER_FCS:
		case	CONTROL_GRAVIS_GAMEPAD:
//			for (i=0; i<4; i++ )	
//		 		if (joy_get_button_down_cnt(i)>0) done=1;
//			break;
		case	CONTROL_MOUSE:
		case	CONTROL_CYBERMAN:
			for (i=0; i<3; i++ )	
				if (mouse_button_down_count(i)>0) done=1;
			break;
		}
#endif
	

//		if ( (nmenus<2) && (k>0) && (nothers==0) )
//			done=1;

		old_choice = choice;

		switch( k )	{
		case KEY_TAB + KEY_SHIFTED:
		case KEY_UP:
		case KEY_PAD8:
			if (all_text) break;
			do {
				choice--;
				if (choice >= nitems ) choice=0;
				if (choice < 0 ) choice=nitems-1;
			} while ( item[choice].type==NM_TYPE_TEXT );
			if ((item[choice].type==NM_TYPE_INPUT) && (choice!=old_choice))	
				item[choice].value = -1;
			if ((old_choice>-1) && (item[old_choice].type==NM_TYPE_INPUT_MENU) && (old_choice!=choice))	{
				item[old_choice].group=0;
				strcpy(item[old_choice].text, item[old_choice].saved_text );
				item[old_choice].value = -1;
			}
			if (old_choice>-1) 
				item[old_choice].redraw = 1;
			item[choice].redraw=1;
			break;
		case KEY_TAB:
		case KEY_DOWN:
		case KEY_PAD2:
			if (all_text) break;
			do {
				choice++;
				if (choice < 0 ) choice=nitems-1;
				if (choice >= nitems ) choice=0;
			} while ( item[choice].type==NM_TYPE_TEXT );
			if ((item[choice].type==NM_TYPE_INPUT) && (choice!=old_choice))	
				item[choice].value = -1;
			if ( (old_choice>-1) && (item[old_choice].type==NM_TYPE_INPUT_MENU) && (old_choice!=choice))	{
				item[old_choice].group=0;
				strcpy(item[old_choice].text, item[old_choice].saved_text );	
				item[old_choice].value = -1;
			}
			if (old_choice>-1)
				item[old_choice].redraw=1;
			item[choice].redraw=1;
			break;
		case KEY_SPACEBAR:
			if ( choice > -1 )	{
				switch( item[choice].type )	{
				case NM_TYPE_MENU:
				case NM_TYPE_INPUT:
				case NM_TYPE_INPUT_MENU:
					break;
				case NM_TYPE_CHECK:
					if ( item[choice].value )
						item[choice].value = 0;
					else
						item[choice].value = 1;
					item[choice].redraw=1;
					break;
				case NM_TYPE_RADIO:
					for (i=0; i<nitems; i++ )	{
						if ((i!=choice) && (item[i].type==NM_TYPE_RADIO) && (item[i].group==item[choice].group) && (item[i].value) )	{
							item[i].value = 0;
							item[i].redraw = 1;
						}
					}
					item[choice].value = 1;
					item[choice].redraw = 1;
					break;
				}	
			}
			break;

		case KEY_ENTER:
		case KEY_PADENTER:
			if ( (choice>-1) && (item[choice].type==NM_TYPE_INPUT_MENU) && (item[choice].group==0))	{
				item[choice].group = 1;
				item[choice].redraw = 1;
//				if ( !strnicmp( item[choice].saved_text, TXT_EMPTY, strlen(TXT_EMPTY) ) )	{
				if ( !strnicmp( item[choice].saved_text, TXT_EMPTY, strlen(TXT_EMPTY) ) )	{
					item[choice].text[0] = 0;
					item[choice].value = -1;
				} else {	
					strip_end_whitespace(item[choice].text);
				}
			} else
				done = 1;
			break;

		case KEY_ESC:
			if ( (choice>-1) && (item[choice].type==NM_TYPE_INPUT_MENU) && (item[choice].group==1))	{
				item[choice].group=0;
				strcpy(item[choice].text, item[choice].saved_text );	
				item[choice].redraw=1;
				item[choice].value = -1;
			} else {
				done = 1;
				choice = -1;
			}
			break;
			
		case KEY_PRINT_SCREEN:
		case KEY_COMMAND+KEY_SHIFTED+KEY_3:
			hide_cursor();
			save_screen_shot(0);
			show_cursor();
			break;

// CD controls follow here

#ifndef MAC_SHAREWARE
		case KEY_COMMAND+KEY_E:
			redbook_eject_disk();
			break;
		case KEY_COMMAND+KEY_RIGHT:
			redbook_next_track();
			break;
		case KEY_COMMAND+KEY_LEFT:
			redbook_previous_track();
			break;
		case KEY_COMMAND+KEY_UP:
			redbook_start_play();
			break;
		case KEY_COMMAND+KEY_DOWN:
			stop_redbook();
			break;
		case KEY_COMMAND+KEY_M:
			redbook_mount_disk();
			break;
#endif
			
		case KEY_COMMAND+KEY_Q:
			if ( !(Game_mode & GM_MULTI) )
				do_appl_quit();
			show_cursor();
			break;

		#ifndef NDEBUG
		case KEY_BACKSP:	
			if ( (choice>-1) && (item[choice].type!=NM_TYPE_INPUT)&&(item[choice].type!=NM_TYPE_INPUT_MENU))
				Int3(); 
			break;
		#endif

		}
		
		if ( !done && mouse_state && !omouse_state && !all_text ) {
			mouse_get_pos(&mx, &my);
			for (i=0; i<nitems; i++ )	{
				x1 = grd_curcanv->cv_bitmap.bm_x + item[i].x - item[i].right_offset - 6;
				x2 = x1 + item[i].w;
				y1 = grd_curcanv->cv_bitmap.bm_y + item[i].y;
				y2 = y1 + item[i].h;
				if (((mx > x1) && (mx < x2)) && ((my > y1) && (my < y2))) {
					choice = i;
					switch( item[choice].type )	{
					case NM_TYPE_CHECK:
						if ( item[choice].value )
							item[choice].value = 0;
						else
							item[choice].value = 1;
						item[choice].redraw=1;
						break;
					case NM_TYPE_RADIO:
						for (i=0; i<nitems; i++ )	{
							if ((i!=choice) && (item[i].type==NM_TYPE_RADIO) && (item[i].group==item[choice].group) && (item[i].value) )	{
								item[i].value = 0;
								item[i].redraw = 1;
							}
						}
						item[choice].value = 1;
						item[choice].redraw = 1;
						break;
					}
					item[old_choice].redraw=1;
					break;
				}
			}
		}

		if (mouse_state && all_text)
			done = 1;
		
		if ( !done && mouse_state && !all_text ) {
			mouse_get_pos(&mx, &my);
			for (i=0; i<nitems; i++ )	{
				x1 = grd_curcanv->cv_bitmap.bm_x + item[i].x - item[i].right_offset - 6;
				x2 = x1 + item[i].w;
				y1 = grd_curcanv->cv_bitmap.bm_y + item[i].y;
				y2 = y1 + item[i].h;
				if (((mx > x1) && (mx < x2)) && ((my > y1) && (my < y2)) && (item[i].type != NM_TYPE_TEXT) ) {
					choice = i;
					if ( item[choice].type == NM_TYPE_SLIDER ) {
						char slider_text[NM_MAX_TEXT_LEN+1], *p, *s1;
						int string_width, slider_width, height, aw, sleft_width, sright_width, smiddle_width;
						
						strcpy(slider_text, item[choice].saved_text);
						p = strchr(slider_text, '\t');
						if (p) {
							*p = '\0';
							s1 = p+1;
						}
						if (p) {
							gr_get_string_size(s1, &slider_width, &height, &aw);
							gr_get_string_size(SLIDER_LEFT, &sleft_width, &height, &aw);
							gr_get_string_size(SLIDER_RIGHT, &sright_width, &height, &aw);
							gr_get_string_size(SLIDER_MIDDLE, &smiddle_width, &height, &aw);

							x1 = grd_curcanv->cv_bitmap.bm_x + item[choice].x + item[choice].w - slider_width;
							x2 = x1 + slider_width + sright_width;
							if ( (mx > x1) && (mx < (x1 + sleft_width)) && (item[choice].value != item[choice].min_value) ) {
								item[choice].value = item[choice].min_value;
								item[choice].redraw = 2;
							} else if ( (mx < x2) && (mx > (x2 - sright_width)) && (item[choice].value != item[choice].max_value) ) {
								item[choice].value = item[choice].max_value;
								item[choice].redraw = 2;
							} else if ( (mx > (x1 + sleft_width)) && (mx < (x2 - sright_width)) ) {
								int num_values, value_width, new_value;
								
								num_values = item[choice].max_value - item[choice].min_value + 1;
								value_width = (slider_width - sleft_width - sright_width) / num_values;
								new_value = (mx - x1 - sleft_width) / value_width;
								if ( item[choice].value != new_value ) {
									item[choice].value = new_value;
									item[choice].redraw = 2;
								}
							}
							*p = '\t';
						}
					}
					if (choice == old_choice)
						break;
					if ((item[choice].type==NM_TYPE_INPUT) && (choice!=old_choice))	
						item[choice].value = -1;
					if ((old_choice>-1) && (item[old_choice].type==NM_TYPE_INPUT_MENU) && (old_choice!=choice))	{
						item[old_choice].group=0;
						strcpy(item[old_choice].text, item[old_choice].saved_text );
						item[old_choice].value = -1;
					}
					if (old_choice>-1) 
						item[old_choice].redraw = 1;
					item[choice].redraw=1;
					break;
				}
			}
		}
		
		if ( !done && !mouse_state && omouse_state && !all_text && (choice != -1) && (item[choice].type == NM_TYPE_MENU) ) {
			mouse_get_pos(&mx, &my);
			x1 = grd_curcanv->cv_bitmap.bm_x + item[choice].x;
			x2 = x1 + item[choice].w;
			y1 = grd_curcanv->cv_bitmap.bm_y + item[choice].y;
			y2 = y1 + item[choice].h;
			if (((mx > x1) && (mx < x2)) && ((my > y1) && (my < y2)))
				done = 1;
		}
		
		if ( !done && !mouse_state && omouse_state && (choice>-1) && (item[choice].type==NM_TYPE_INPUT_MENU) && (item[choice].group==0))	{
			item[choice].group = 1;
			item[choice].redraw = 1;
			if ( !strnicmp( item[choice].saved_text, TXT_EMPTY, strlen(TXT_EMPTY) ) )	{
				item[choice].text[0] = 0;
				item[choice].value = -1;
			} else {	
				strip_end_whitespace(item[choice].text);
			}
		}
		
		if ( !done && !mouse_state && omouse_state && close_box ) {
			mouse_get_pos(&mx, &my);
			x1 = grd_curcanv->cv_bitmap.bm_x + close_x + 2;
			x2 = x1 + close_size - 2;
			y1 = grd_curcanv->cv_bitmap.bm_y + close_y + 2;
			y2 = y1 + close_size - 2;
			if ( ((mx > x1) && (mx < x2)) && ((my > y1) && (my < y2)) ) {
				choice = -1;
				done = 1;
			}
		}
			
		if ( choice > -1 )	{
			unsigned char ascii;

			if ( ((item[choice].type==NM_TYPE_INPUT)||((item[choice].type==NM_TYPE_INPUT_MENU)&&(item[choice].group==1)) )&& (old_choice==choice) )	{
				if ( k==KEY_LEFT || k==KEY_BACKSP || k==KEY_PAD4 )	{
					if (item[choice].value==-1) item[choice].value = strlen(item[choice].text);
					if (item[choice].value > 0)
						item[choice].value--;
					item[choice].text[item[choice].value] = 0;
					item[choice].redraw = 1;	
				} else {
					ascii = key_to_ascii(k);
					if ((ascii < 255 ) && (item[choice].value < item[choice].text_len ))
					{
						int allowed;

						if (item[choice].value==-1) {
							item[choice].value = 0;
						}

						allowed = char_allowed(ascii);

						if (!allowed && ascii==' ' && char_allowed('_')) {
							ascii = '_';
							allowed=1;
						}

						if (allowed) {
							item[choice].text[item[choice].value++] = ascii;
							item[choice].text[item[choice].value] = 0;
							item[choice].redraw=1;	
						}
					}
				}
			} else if ((item[choice].type!=NM_TYPE_INPUT) && (item[choice].type!=NM_TYPE_INPUT_MENU) ) {
				ascii = key_to_ascii(k);
				if (ascii < 255 ) {
					int choice1 = choice;
					ascii = toupper(ascii);
					do {
						int i,ch;
						choice1++;
						if (choice1 >= nitems ) choice1=0;
						for (i=0;(ch=item[choice1].text[i])!=0 && ch==' ';i++);
						if ( ( (item[choice1].type==NM_TYPE_MENU) ||
								 (item[choice1].type==NM_TYPE_CHECK) ||
								 (item[choice1].type==NM_TYPE_RADIO) ||
								 (item[choice1].type==NM_TYPE_NUMBER) ||
								 (item[choice1].type==NM_TYPE_SLIDER) )
								&& (ascii==toupper(ch)) )	{
							k = 0;
							choice = choice1;
							if (old_choice>-1)
								item[old_choice].redraw=1;
							item[choice].redraw=1;
						}
					} while (choice1 != choice );
				}	
			}

			if ( (item[choice].type==NM_TYPE_NUMBER) || (item[choice].type==NM_TYPE_SLIDER)) 	{
				int ov=item[choice].value;
				switch( k ) {
				case KEY_PAD4:
			  	case KEY_LEFT:
			  	case KEY_MINUS:
				case KEY_MINUS+KEY_SHIFTED:
				case KEY_PADMINUS:
					item[choice].value -= 1;
					break;
			  	case KEY_RIGHT:
				case KEY_PAD6:
			  	case KEY_EQUAL:
				case KEY_EQUAL+KEY_SHIFTED:
				case KEY_PADPLUS:
					item[choice].value++;
					break;
				case KEY_PAGEUP:
				case KEY_PAD9:
				case KEY_SPACEBAR:
					item[choice].value += 10;
					break;
				case KEY_PAGEDOWN:
				case KEY_BACKSP:
				case KEY_PAD3:
					item[choice].value -= 10;
					break;
				}
				if (ov!=item[choice].value)
					item[choice].redraw=1;
			}
	
		}

		gr_set_current_canvas(bg.menu_canvas);
		// Redraw everything...
		for (i=0; i<nitems; i++ )	{
			if (item[i].redraw)	{
				hide_cursor();
				draw_item( &bg, &item[i], (i==choice && !all_text) );
				show_cursor();
				item[i].redraw=0;
			}
			else if (i==choice && (item[i].type==NM_TYPE_INPUT || (item[i].type==NM_TYPE_INPUT_MENU && item[i].group)))
				update_cursor( &item[i]);
		}
		bitblt_to_screen();
		if ( gr_palette_faded_out )	{
			gr_palette_fade_in( gr_palette, 32, 0 );
		}
	}
	hide_cursor();
	
	// Restore everything...
	gr_set_current_canvas(bg.menu_canvas);
	if ( filename == NULL )	{
		// Save the background under the menu...
		gr_bitmap(0, 0, bg.saved); 	
		gr_free_bitmap(bg.saved);
		myfree( bg.background );
	} else {
		gr_bitmap(0, 0, bg.background); 	
		gr_free_bitmap(bg.background);
	}

	gr_free_sub_canvas( bg.menu_canvas );

	gr_set_current_canvas( NULL );			
	grd_curcanv->cv_font	= save_font;
	gr_set_current_canvas( save_canvas );			
	keyd_repeat = old_keyd_repeat;

	game_flush_inputs();

	if (time_stopped)
		start_time();

//NO_SOUND_PAUSE	if ( sound_stopped )
//NO_SOUND_PAUSE		digi_resume_all();

	return choice;
	
}


int nm_messagebox1( char *title, void (*subfunction)(int nitems,newmenu_item * items, int * last_key, int citem), int nchoices, ... )
{
	int i;
	char * format;
	va_list args;
	char *s;
	char nm_text[MESSAGEBOX_TEXT_SIZE];
	newmenu_item nm_message_items[5];

	va_start(args, nchoices );

	Assert( nchoices <= 5 );

	for (i=0; i<nchoices; i++ )	{
		s = va_arg( args, char * );
		nm_message_items[i].type = NM_TYPE_MENU; nm_message_items[i].text = s;
	}
	format = va_arg( args, char * );
	sprintf(	nm_text, "" );
	vsprintf(nm_text,format,args);
	va_end(args);

	Assert(strlen(nm_text) < MESSAGEBOX_TEXT_SIZE);

	return newmenu_do( title, nm_text, nchoices, nm_message_items, subfunction );
}

int nm_messagebox( char *title, int nchoices, ... )
{
	int i;
	char * format;
	va_list args;
	char *s;
	char nm_text[MESSAGEBOX_TEXT_SIZE];
	newmenu_item nm_message_items[5];

	va_start(args, nchoices );

	Assert( nchoices <= 5 );

	for (i=0; i<nchoices; i++ )	{
		s = va_arg( args, char * );
		nm_message_items[i].type = NM_TYPE_MENU; nm_message_items[i].text = s;
	}
	format = va_arg( args, char * );
	sprintf(	nm_text, "" );
	vsprintf(nm_text,format,args);
	va_end(args);

	Assert(strlen(nm_text) < MESSAGEBOX_TEXT_SIZE );

	return newmenu_do( title, nm_text, nchoices, nm_message_items, NULL );
}




void newmenu_file_sort( int n, char *list )
{
	int i, j, incr;
	char t[14];

	incr = n / 2;
	while( incr > 0 )		{
		for (i=incr; i<n; i++ )		{
			j = i - incr;
			while (j>=0 )			{
				if (strnicmp(&list[j*14], &list[(j+incr)*14], 12) > 0)				{
					memcpy( t, &list[j*14], 13 );
					memcpy( &list[j*14], &list[(j+incr)*14], 13 );
					memcpy( &list[(j+incr)*14], t, 13 );
					j -= incr;
				}
				else
					break;
			}
		}
		incr = incr / 2;
	}
}

void delete_player_saved_games(char * name)
{
	int i;
	char filename[64];
	
	for (i=0;i<10; i++)	{
		sprintf( filename, ":Players:%s.sg%d", name, i );
		unlink( filename );
	}
}

#define MAX_FILES 200

int MakeNewPlayerFile(int allow_abort);

int newmenu_get_filename( char * title, char * filespec, char * filename, int allow_abort_flag )
{
	int i;
	DIRPtr dir;
	direntPtr entry;
	int mx, my, x1, x2, y1, y2, mouse_state, omouse_state, r;
	int NumFiles=0, key,done, citem, ocitem;
	char * filenames = NULL;
	int NumFiles_displayed = 8;
	int first_item = -1, ofirst_item;
	int old_keyd_repeat = keyd_repeat;
	int player_mode=0;
	int demo_mode=0;
	int demos_deleted=0;
	int initialized = 0;
	int exit_value = 0;
	int w_x, w_y, w_w, w_h;
	int close_x, close_y, close_size, close_box;

	close_box = allow_abort_flag;
	filenames = mymalloc( MAX_FILES * 14 );
	if (filenames==NULL) return 0;

ReadFileNames:
	citem = 0;
	first_item = -1;
	keyd_repeat = 1;

	CDToDescentDir();								// safety check to get back where to need to
	if (!stricmp( filespec, ":Players:*.plr" ))
		player_mode = 1;
	else if (!stricmp( filespec, ":Demos:*.dem" ))
		demo_mode = 1;

//ReadFileNames:
	done = 0;
	NumFiles=0;

#ifndef APPLE_OEM		// no new pilots for special apple oem version
	if (player_mode)	{
		strncpy( &filenames[NumFiles*14], TXT_CREATE_NEW, 13 );
		NumFiles++;
	}
#endif

	dir = opendir(filespec);
	while ((entry = readdir(dir))) {
		if (NumFiles<MAX_FILES)	{
			strncpy( &filenames[NumFiles*14], entry->d_name, 13 );
			if ( player_mode )	{
				char * p;
				p = strchr(&filenames[NumFiles*14],'.');
				if (p) *p = '\0';
			}
			NumFiles++;
		} else {
			break;
		}
	}
	closedir(dir);

#if 0
#ifdef SATURN
	// Seach CD for files if demo_mode and cd_mode
	if ( strlen(destsat_cdpath) && demo_mode )	{
		char temp_spec[128];
		strcpy( temp_spec, destsat_cdpath );
		strcat( temp_spec, filespec );

		if( !_dos_findfirst( temp_spec, 0, &find ) )	{
			do	{
				if (NumFiles<MAX_FILES)	{

					for (i=0; i<NumFiles; i++ )	{
						if (!stricmp( &filenames[i*14], find.name ))
							break;
					}
					if ( i < NumFiles ) continue;		// Don't use same demo twice!

					strncpy( &filenames[NumFiles*14], find.name, 13 );
					if ( player_mode )	{
						char * p;
						p = strchr(&filenames[NumFiles*14],'.');
						if (p) *p = '\0';
					}
					NumFiles++;
				} else {
					break;
				}
			} while( !_dos_findnext( &find ) );
		}
	}
#endif
#endif // #if 0

	if ( (NumFiles < 1) && demos_deleted )	{
		exit_value = 0;
		goto ExitFileMenu;
	}
	if ( (NumFiles < 1) && demo_mode ) {
		nm_messagebox( NULL, 1, TXT_OK, "%s %s\n%s", TXT_NO_DEMO_FILES, TXT_USE_F5, TXT_TO_CREATE_ONE);
		exit_value = 0;
		goto ExitFileMenu;
	}

	#ifndef APPLE_OEM			// really for testing, but this is true since we cannot add players
	if ( (NumFiles < 2) && player_mode ) {
		citem = 0;
		goto ExitFileMenuEarly;
	}
	#endif

	if ( NumFiles<1 )	{
		nm_messagebox( NULL, 1, "Ok", "%s\n '%s' %s", TXT_NO_FILES_MATCHING, filespec, TXT_WERE_FOUND);
		exit_value = 0;
		goto ExitFileMenu;
	}

	if (!initialized) {	
		set_screen_mode(SCREEN_MENU);
		gr_set_current_canvas(NULL);

//mwa		w_w = 230 - 90 + 1 + 30;
//mwa		w_h = 170 - 30 + 1 + 30;
//mwa		if ( w_w > 320 ) w_w = 320;
//mwa		if ( w_h > 200 ) w_h = 200;
		w_w = 342;
		w_h = 410;
		if (w_w > grd_curcanv->cv_bitmap.bm_w) w_w = grd_curcanv->cv_bitmap.bm_w;
		if (w_h > grd_curcanv->cv_bitmap.bm_h) w_h = grd_curcanv->cv_bitmap.bm_h;

		w_x = (grd_curcanv->cv_bitmap.bm_w-w_w)/2;
		if ((r = w_x & 0x7)) {
			for (i = 0; i < r; i++)
				w_x--;
		}
		w_y = (grd_curcanv->cv_bitmap.bm_h-w_h)/2;

		if ( w_x < 0 ) w_x = 0;
		if ( w_y < 0 ) w_y = 0;

		gr_bm_bitblt(grd_curscreen->sc_w, grd_curscreen->sc_h, 0, 0, 0, 0, &(grd_curcanv->cv_bitmap), &(VR_offscreen_buffer->cv_bitmap) );
		nm_draw_background( w_x,w_y,w_x+w_w-1,w_y+w_h-1 );
		bitblt_to_screen();

		grd_curcanv->cv_font = Gamefonts[GFONT_MEDIUM_3];
		gr_string( 0x8000, w_y+20, title );

		if (close_box) {
			close_x = close_y = 15;
			close_size = 10;
			gr_setcolor( BM_XRGB(0, 0, 0) );
			gr_rect(w_x+close_x, w_y+close_y, w_x+close_x + close_size, w_y+close_y + close_size);
			gr_setcolor( BM_XRGB(21, 21, 21) );
			gr_rect( w_x+close_x + 2, w_y+close_y + 2, w_x+close_x + close_size - 2, w_y+close_y + close_size -2 );
		}
	
		initialized = 1;
	}

	if ( !player_mode )	{
		newmenu_file_sort( NumFiles, filenames );
	} else {
		#ifndef APPLE_OEM
		newmenu_file_sort( NumFiles-1, &filenames[14] );		// Don't sort first one!
		#else
		newmenu_file_sort( NumFiles, &filenames[14] );		// sort the first one for apple oem version since you can't add pilots
		#endif
		for ( i=0; i<NumFiles; i++ )	{
			if (!stricmp(Players[Player_num].callsign, &filenames[i*14]) )
				citem = i;
		}
	}

	omouse_state = mouse_state = 0;
	show_cursor();
	
	while(!done)	{
		ocitem = citem;
		ofirst_item = first_item;
		omouse_state = mouse_state;
		mouse_state = mouse_button_state(0);
		key = key_inkey();
		switch(key)	{
		case KEY_COMMAND+KEY_SHIFTED+KEY_3:
		case KEY_PRINT_SCREEN:
			hide_cursor();
			save_screen_shot(0);
			show_cursor();
			break;

		#ifndef APPLE_OEM			// not allowed to delete players in Apple OEM version
		case KEY_CTRLED+KEY_D:
			if ( ((player_mode)&&(citem>0)) || ((demo_mode)&&(citem>=0)) )	{
				int x = 1;
				hide_cursor();
				if (player_mode)
					x = nm_messagebox( NULL, 2, TXT_YES, TXT_NO, "%s %s?", TXT_DELETE_PILOT, &filenames[citem*14]+((player_mode && filenames[citem*14]=='$')?1:0) );
				else if (demo_mode)
					x = nm_messagebox( NULL, 2, TXT_YES, TXT_NO, "%s %s?", TXT_DELETE_DEMO, &filenames[citem*14]+((demo_mode && filenames[citem*14]=='$')?1:0) );
				show_cursor();
 				if (x==0)	{
					char long_name[64];
					char * p;
					int ret;
					long_name[0] = '\0';
					p = &filenames[(citem*14)+strlen(&filenames[citem*14])];
					if (player_mode) {
						*p = '.';
						strcpy(long_name, ":Players:");
					} else if (demo_mode) {
						strcpy(long_name, ":Demos:");
					}
					strcat(long_name, &filenames[citem*14]);
					ret = unlink(long_name);
					if (player_mode)
						*p = 0;

					if ((!ret) && player_mode)	{
						delete_player_saved_games( &filenames[citem*14] );
					}

					if (ret) {
						if (player_mode)
							nm_messagebox( NULL, 1, TXT_OK, "%s %s %s", TXT_COULDNT, TXT_DELETE_PILOT, &filenames[citem*14]+((player_mode && filenames[citem*14]=='$')?1:0) );
						else if (demo_mode)
							nm_messagebox( NULL, 1, TXT_OK, "%s %s %s", TXT_COULDNT, TXT_DELETE_DEMO, &filenames[citem*14]+((demo_mode && filenames[citem*14]=='$')?1:0) );
					} else if (demo_mode)
						demos_deleted = 1;
					first_item = -1;
					goto ReadFileNames;
				}
			}
			break;
		#endif				// ifndef APPLE_OEM
		
#ifndef NDEBUG
		case KEY_BACKSP:
			Int3();
			break;
#endif
		case KEY_HOME:
		case KEY_PAD7:
			citem = 0;
			break;
		case KEY_END:
		case KEY_PAD1:
			citem = NumFiles-1;
			break;
		case KEY_UP:
		case KEY_PAD8:
			citem--;			
			break;
		case KEY_DOWN:
		case KEY_PAD2:
			citem++;			
			break;
 		case KEY_PAGEDOWN:
		case KEY_PAD3:
			citem += NumFiles_displayed;
			break;
		case KEY_PAGEUP:
		case KEY_PAD9:
			citem -= NumFiles_displayed;
			break;
		case KEY_ESC:
			if (allow_abort_flag) {
				citem = -1;
				done = 1;
			}
			break;
		case KEY_ENTER:
		case KEY_PADENTER:
			done = 1;
			break;
		case KEY_COMMAND+KEY_Q:
			if ( !(Game_mode & GM_MULTI) )
				do_appl_quit();
			show_cursor();
			break;
		default:	
			{
				int ascii = key_to_ascii(key);
				if ( ascii < 255 )	{
					int cc,cc1;
					cc=cc1=citem+1;
					if (cc1 < 0 )  cc1 = 0;
					if (cc1 >= NumFiles )  cc1 = 0;
					while(1) {
						if ( cc < 0 ) cc = 0;
						if ( cc >= NumFiles ) cc = 0;
						if ( citem == cc ) break;
	
						if ( toupper(filenames[cc*14]) == toupper(ascii) )	{
							citem = cc;
							break;
						}
						cc++;
					}
				}
			}
		}
		if ( done ) break;

		if (citem<0)
			citem=0;

		if (citem>=NumFiles)
			citem = NumFiles-1;

		if (citem< first_item)
			first_item = citem;

		if (citem>=( first_item+NumFiles_displayed))
			first_item = citem-NumFiles_displayed+1;

		if (NumFiles <= NumFiles_displayed )
			 first_item = 0;

		if (first_item>NumFiles-NumFiles_displayed)
			first_item = NumFiles-NumFiles_displayed;
		if (first_item < 0 ) first_item = 0;

		if (mouse_state) {
			mouse_get_pos(&mx, &my);
			for (i=first_item; i<first_item+NumFiles_displayed; i++ )	{
				x1 = 210;
				x2 = 440;
				y1 = (i-first_item)*29+w_y+108;
				y2 = y1+26;
				if ( ((mx > x1) && (mx < x2)) && ((my > y1) && (my < y2)) ) {
					if (i == citem)
						break;
					citem = i;
					break;
				}
			}
		}
		
		if (!mouse_state && omouse_state) {
			mouse_get_pos(&mx, &my);
			x1 = 210;
			x2 = 440;
			y1 = (citem-first_item)*29+w_y+108;
			y2 = y1+26;
			if ( ((mx > x1) && (mx < x2)) && ((my > y1) && (my < y2)) ) {
				done = 1;
			}
		}

		if ( !mouse_state && omouse_state && close_box ) {
			mouse_get_pos(&mx, &my);
			x1 = w_x + close_x + 2;
			x2 = x1 + close_size - 2;
			y1 = w_y + close_y + 2;
			y2 = y1 + close_size - 2;
			if ( ((mx > x1) && (mx < x2)) && ((my > y1) && (my < y2)) ) {
				citem = -1;
				done = 1;
			}
		}
			
		if (ofirst_item != first_item )	{
			gr_setcolor( BM_XRGB( 0,0,0)  );
			hide_cursor();
			for (i=first_item; i<first_item+NumFiles_displayed; i++ )	{
				int w, h, aw, y;
				y = (i-first_item)*29+w_y+108;
				if ( i >= NumFiles )	{
					gr_setcolor( BM_XRGB(0,0,0));
					gr_rect( 200, y-2, 440, y+26 );
				} else {
					if ( i == citem )	
						grd_curcanv->cv_font = Gamefonts[GFONT_MEDIUM_2];
					else	
						grd_curcanv->cv_font = Gamefonts[GFONT_MEDIUM_1];
					gr_get_string_size(&filenames[i*14], &w, &h, &aw  );
					gr_rect( 200, y-2, 440, y+26 );
					gr_string( 210, y, (&filenames[i*14])+((player_mode && filenames[i*14]=='$')?1:0)  );
				}
			}
			show_cursor();
		} else if ( citem != ocitem )	{
			int w, h, aw, y;

			hide_cursor();
			i = ocitem;
			if ( (i>=0) && (i<NumFiles) )	{
				y = (i-first_item)*29+w_y+108;
				if ( i == citem )	
					grd_curcanv->cv_font = Gamefonts[GFONT_MEDIUM_2];
				else	
					grd_curcanv->cv_font = Gamefonts[GFONT_MEDIUM_1];
				gr_get_string_size(&filenames[i*14], &w, &h, &aw  );
				gr_rect( 200, y-2, 440, y+26 );
				gr_string( 210, y, (&filenames[i*14])+((player_mode && filenames[i*14]=='$')?1:0)  );
			}
			i = citem;
			if ( (i>=0) && (i<NumFiles) )	{
				y = (i-first_item)*29+w_y+108;
				if ( i == citem )	
					grd_curcanv->cv_font = Gamefonts[GFONT_MEDIUM_2];
				else	
					grd_curcanv->cv_font = Gamefonts[GFONT_MEDIUM_1];
				gr_get_string_size(&filenames[i*14], &w, &h, &aw  );
				gr_rect( 200, y-2, 440, y+26 );
				gr_string( 210, y, (&filenames[i*14])+((player_mode && filenames[i*14]=='$')?1:0)  );
			}
			show_cursor();
		}
		bitblt_to_screen();
	}

ExitFileMenuEarly:
	hide_cursor();
	if ( citem > -1 )	{
		strncpy( filename, (&filenames[citem*14])+((player_mode && filenames[citem*14]=='$')?1:0), 13 );
		exit_value = 1;
	} else {
		exit_value = 0;
	}											 

ExitFileMenu:
	keyd_repeat = old_keyd_repeat;

	if ( initialized )	{
		gr_bm_bitblt(grd_curscreen->sc_w, grd_curscreen->sc_h, 0, 0, 0, 0, &(VR_offscreen_buffer->cv_bitmap), &(grd_curcanv->cv_bitmap) );
		bitblt_to_screen();
	}

	if ( filenames )
		myfree(filenames);

	return exit_value;

}


// Example listbox callback function...
// int lb_callback( int * citem, int *nitems, char * items[], int *keypress )
// {
// 	int i;
// 
// 	if ( *keypress = KEY_CTRLED+KEY_D )	{
// 		if ( *nitems > 1 )	{
// 			unlink( items[*citem] );		// Delete the file
// 			for (i=*citem; i<*nitems-1; i++ )	{
// 				items[i] = items[i+1];
// 			}
// 			*nitems = *nitems - 1;
// 			free( items[*nitems] );
// 			items[*nitems] = NULL;
// 			return 1;	// redraw;
// 		}
//			*keypress = 0;
// 	}			
// 	return 0;
// }

#define LB_ITEMS_ON_SCREEN 8

int newmenu_listbox( char * title, int nitems, char * items[], int allow_abort_flag, int (*listbox_callback)( int * citem, int *nitems, char * items[], int *keypress ) )
{
	return newmenu_listbox1( title, nitems, items, allow_abort_flag, 0, listbox_callback, 1 );
}

int newmenu_listbox1( char * title, int nitems, char * items[], int allow_abort_flag, int default_item, int (*listbox_callback)( int * citem, int *nitems, char * items[], int *keypress ), int close_box )
{
	int i;
	int mx, my, x1, x2, y1, y2;
	int done, ocitem,citem, ofirst_item, first_item, key, redraw;
	int old_keyd_repeat = keyd_repeat;
	int width, height, wx, wy, title_height;
	int mouse_state, omouse_state;
	int close_x, close_y, close_size;

	keyd_repeat = 1;

	set_screen_mode(SCREEN_MENU);
	gr_set_current_canvas(NULL);
	grd_curcanv->cv_font = Gamefonts[GFONT_MEDIUM_3];

	width = 0;
	for (i=0; i<nitems; i++ )	{
		int w, h, aw;
		gr_get_string_size( items[i], &w, &h, &aw );		
		if ( w > width )
			width = w;
	}
	height = 26 * LB_ITEMS_ON_SCREEN;

	{
		int w, h, aw;
		gr_get_string_size( title, &w, &h, &aw );		
		if ( w > width )
			width = w;
		title_height = h + 13;
	}
		
	width += 20;
	if ( width > grd_curcanv->cv_bitmap.bm_w - 60 )
		width = grd_curcanv->cv_bitmap.bm_w - 60;
	
	wx = (grd_curcanv->cv_bitmap.bm_w-width)/2;
	wy = (grd_curcanv->cv_bitmap.bm_h-(height+title_height))/2 + title_height;
	if ( wy < title_height )
		wy = title_height;

	gr_bm_bitblt(grd_curcanv->cv_bitmap.bm_w, grd_curcanv->cv_bitmap.bm_h, 0, 0, 0, 0, &(grd_curcanv->cv_bitmap), &(VR_offscreen_buffer->cv_bitmap) );
	nm_draw_background( wx-30,wy-title_height-36,wx+width+30,wy+height+36 );

	gr_string( 0x8000, wy - title_height, title );

	if (close_box) {
		close_x = wx - 30 + 15;
		close_y = wy - title_height - 36 + 15;
		close_size = 10;
		gr_setcolor( BM_XRGB(0, 0, 0) );
		gr_rect(close_x, close_y, close_x + close_size, close_y + close_size);
		gr_setcolor( BM_XRGB(21, 21, 21) );
		gr_rect( close_x + 2, close_y + 2, close_x + close_size - 2, close_y + close_size - 2 );
	}

	done = 0;
	citem = default_item;
	if ( citem < 0 ) citem = 0;
	if ( citem >= nitems ) citem = 0;

	first_item = -1;

	omouse_state = mouse_state = 0;
	show_cursor();
	
	while(!done)	{
		ocitem = citem;
		ofirst_item = first_item;
		omouse_state = mouse_state;
		mouse_state = mouse_button_state(0);
		key = key_inkey();

		if ( listbox_callback )
			redraw = (*listbox_callback)(&citem, &nitems, items, &key );
		else
			redraw = 0;

		if ( key<-1 ) {
			citem = key;
			key = -1;
			done = 1;
		}

		switch(key)	{
		case KEY_PRINT_SCREEN: 		
		case KEY_COMMAND+KEY_SHIFTED+KEY_3:
			hide_cursor();
			save_screen_shot(0); 
			show_cursor();
			break;
		case KEY_HOME:
		case KEY_PAD7:
			citem = 0;
			break;
		case KEY_END:
		case KEY_PAD1:
			citem = nitems-1;
			break;
		case KEY_UP:
		case KEY_PAD8:
			citem--;			
			break;
		case KEY_DOWN:
		case KEY_PAD2:
			citem++;			
			break;
 		case KEY_PAGEDOWN:
		case KEY_PAD3:
			citem += LB_ITEMS_ON_SCREEN;
			break;
		case KEY_PAGEUP:
		case KEY_PAD9:
			citem -= LB_ITEMS_ON_SCREEN;
			break;
		case KEY_ESC:
			if (allow_abort_flag) {
				citem = -1;
				done = 1;
			}
			break;
		case KEY_ENTER:
		case KEY_PADENTER:
			done = 1;
			break;
			
		case KEY_COMMAND+KEY_Q:
			if ( !(Game_mode & GM_MULTI) )
				do_appl_quit();
			show_cursor();
			break;
		default:	
			if ( key > 0 )	{
				int ascii = key_to_ascii(key);
				if ( ascii < 255 )	{
					int cc,cc1;
					cc=cc1=citem+1;
					if (cc1 < 0 )  cc1 = 0;
					if (cc1 >= nitems )  cc1 = 0;
					while(1) {
						if ( cc < 0 ) cc = 0;
						if ( cc >= nitems ) cc = 0;
						if ( citem == cc ) break;
	
						if ( toupper( items[cc][0] ) == toupper(ascii) )	{
							citem = cc;
							break;
						}
						cc++;
					}
				}
			}
		}
		if ( done ) break;

		if (citem<0)
			citem=0;

		if (citem>=nitems)
			citem = nitems-1;

		if (citem< first_item)
			first_item = citem;

		if (citem>=( first_item+LB_ITEMS_ON_SCREEN))
			first_item = citem-LB_ITEMS_ON_SCREEN+1;

		if (nitems <= LB_ITEMS_ON_SCREEN )
			 first_item = 0;

		if (first_item>nitems-LB_ITEMS_ON_SCREEN)
			first_item = nitems-LB_ITEMS_ON_SCREEN;
		if (first_item < 0 ) first_item = 0;

		if (mouse_state) {
			mouse_get_pos(&mx, &my);
			for (i=first_item; i<first_item+LB_ITEMS_ON_SCREEN; i++ )	{
				x1 = wx;
				x2 = wx + width;
				y1 = (i-first_item)*29+wy;
				y2 = y1+26;
				if ( ((mx > x1) && (mx < x2)) && ((my > y1) && (my < y2)) ) {
					if (i == citem)
						break;
					citem = i;
					break;
				}
			}
		}
		
		if (!mouse_state && omouse_state) {
			mouse_get_pos(&mx, &my);
			x1 = wx;
			x2 = wx + width;
			y1 = (citem-first_item)*29+wy;
			y2 = y1+26;
			if ( ((mx > x1) && (mx < x2)) && ((my > y1) && (my < y2)) ) {
				done = 1;
			}
		}

		if ( !mouse_state && omouse_state && close_box ) {
			mouse_get_pos(&mx, &my);
			x1 = close_x + 2;
			x2 = x1 + close_size - 2;
			y1 = close_y + 2;
			y2 = y1 + close_size - 2;
			if ( ((mx > x1) && (mx < x2)) && ((my > y1) && (my < y2)) ) {
				citem = -1;
				done = 1;
			}
		}
			
		if ( (ofirst_item != first_item) || redraw)	{
			hide_cursor();
			gr_setcolor( BM_XRGB( 0,0,0)  );
			for (i=first_item; i<first_item+LB_ITEMS_ON_SCREEN; i++ )	{
				int w, h, aw, y;
				y = (i-first_item)*29+wy;
				if ( i >= nitems )	{
					gr_setcolor( BM_XRGB(0,0,0));
					gr_rect( wx, y-2, wx+width-2, y+26 );
				} else {
					if ( i == citem )	
						grd_curcanv->cv_font = Gamefonts[GFONT_MEDIUM_2];
					else	
						grd_curcanv->cv_font = Gamefonts[GFONT_MEDIUM_1];
					gr_get_string_size(items[i], &w, &h, &aw  );
					gr_rect( wx, y-2, wx+width-2, y+26 );
					gr_string( wx+10, y, items[i]  );
				}
			}		
			show_cursor();
		} else if ( citem != ocitem )	{
			int w, h, aw, y;

			hide_cursor();
			i = ocitem;
			if ( (i>=0) && (i<nitems) )	{
				y = (i-first_item)*29+wy;
				if ( i == citem )	
					grd_curcanv->cv_font = Gamefonts[GFONT_MEDIUM_2];
				else	
					grd_curcanv->cv_font = Gamefonts[GFONT_MEDIUM_1];
				gr_get_string_size(items[i], &w, &h, &aw  );
				gr_rect( wx, y-2, wx+width-2, y+26 );
				gr_string( wx+10, y, items[i]  );
			}
			i = citem;
			if ( (i>=0) && (i<nitems) )	{
				y = (i-first_item)*29+wy;
				if ( i == citem )	
					grd_curcanv->cv_font = Gamefonts[GFONT_MEDIUM_2];
				else	
					grd_curcanv->cv_font = Gamefonts[GFONT_MEDIUM_1];
				gr_get_string_size( items[i], &w, &h, &aw  );
				gr_rect( wx, y-2, wx+width-2, y+26 );
				gr_string( wx+10, y, items[i]  );
			}
			show_cursor();
		}
		bitblt_to_screen();
	}
	hide_cursor();
	keyd_repeat = old_keyd_repeat;

	gr_bm_bitblt(grd_curcanv->cv_bitmap.bm_w, grd_curcanv->cv_bitmap.bm_h, 0, 0, 0, 0, &(VR_offscreen_buffer->cv_bitmap), &(grd_curcanv->cv_bitmap) );
	bitblt_to_screen();

	return citem;
}


// assume chdir'ed to this directory

int newmenu_filelist( char * title, char * filespec, char * filename )
{
	int i, NumFiles;
	char * Filenames[MAX_FILES];
	char FilenameText[MAX_FILES][14];
	DIRPtr dir;
	direntPtr entry;

	NumFiles = 0;
	dir = opendir(filespec);
	while ((entry = readdir(dir))) {
		if (NumFiles<MAX_FILES)	{
			strncpy( FilenameText[NumFiles], entry->d_name, 13 );
			Filenames[NumFiles] = FilenameText[NumFiles];
			NumFiles++;
		} else {
			break;
		}
	}
	closedir(dir);
	i = newmenu_listbox( title, NumFiles, Filenames, 1, NULL );
	if ( i > -1 )	{
		strcpy( filename, Filenames[i] );
		return 1;
	} 
	return 0;
}

