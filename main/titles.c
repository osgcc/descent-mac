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
 * $Source: Smoke:miner:source:main::RCS:titles.c $
 * $Revision: 1.13 $
 * $Author: allender $
 * $Date: 1995/11/03 12:52:23 $
 * 
 * Routines to display title screens...
 * 
 * $Log: titles.c $
 * Revision 1.13  1995/11/03  12:52:23  allender
 * shareware changes
 *
 * Revision 1.12  1995/10/31  10:17:56  allender
 * shareware stuff
 *
 * Revision 1.11  1995/10/24  18:12:02  allender
 * don't do special processing on do_appl_quit anymore
 *
 * Revision 1.10  1995/10/21  22:25:02  allender
 * added bald guy cheat
 *
 * Revision 1.9  1995/10/17  13:14:30  allender
 * mouse will now move through title stuff
 *
 * Revision 1.8  1995/10/15  23:00:34  allender
 * made mouse move through screens and do event processing
 * at title screens
 *
 * Revision 1.7  1995/10/10  11:52:10  allender
 * use appropriate end01 file for registered
 *
 * Revision 1.6  1995/09/24  10:53:09  allender
 * added cmd-q to quit during titles screens and briefing screens
 *
 * Revision 1.5  1995/08/25  15:39:37  allender
 * save and resotre interpolation method during briefing screens
 *
 * Revision 1.4  1995/08/24  16:10:57  allender
 * endgame screen changes, and fixups to other stuff
 *
 * Revision 1.3  1995/08/14  14:40:37  allender
 * fixed up briefing screens to look correct.
 * made robot canvas smaller for now for speec
 *
 * Revision 1.2  1995/06/13  13:07:05  allender
 * do a bitblt during tight loops to get spinning robots and cursor flashing
 *
 * Revision 1.1  1995/05/16  15:31:52  allender
 * Initial revision
 *
 * Revision 2.7  1995/03/24  13:11:36  john
 * Added save game during briefing screens.
 * 
 * Revision 2.6  1995/03/21  14:41:17  john
 * Ifdef'd out the NETWORK code.
 * 
 * Revision 2.5  1995/03/15  14:33:45  john
 * Added code to force the Descent CD-rom in the drive.
 * 
 * Revision 2.4  1995/03/14  18:24:50  john
 * Force Destination Saturn to use CD-ROM drive.
 * 
 * Revision 2.3  1995/03/10  13:05:52  john
 * Added code so that palette is correct for VFX1 helmets.
 * 
 * Revision 2.2  1995/03/07  14:19:28  mike
 * More destination saturn stuff.
 * 
 * Revision 2.1  1995/03/06  15:24:16  john
 * New screen techniques.
 * 
 * Revision 2.0  1995/02/27  11:32:50  john
 * New version 2.0, which has no anonymous unions, builds with
 * Watcom 10.0, and doesn't require parsing BITMAPS.TBL.
 * 
 * Revision 1.95  1995/02/12  04:07:19  matt
 * After freeing Robot_canv, set ptr to NULL
 * 
 * Revision 1.94  1995/02/11  12:41:57  john
 * Added new song method, with FM bank switching..
 * 
 * Revision 1.93  1995/02/11  09:51:59  john
 * Stripped out all SVGA references.
 * 
 * Revision 1.92  1995/02/07  09:56:10  john
 * Fixed bug with wrong title screen drawing during save btwn lvls.
 * 
 * Revision 1.91  1995/02/04  13:53:16  john
 * Added code to display the correct titles between levels
 * that have robot maps..
 * 
 * Revision 1.90  1995/02/02  16:36:33  adam
 * *** empty log message ***
 * 
 * Revision 1.89  1995/02/02  12:23:30  john
 * Made between level saves have picture.
 * 
 * Revision 1.88  1995/02/02  01:50:16  adam
 * rearranged robot briefings.
 * 
 * Revision 1.87  1995/02/01  22:28:54  mike
 * *** empty log message ***
 * 
 * Revision 1.86  1995/02/01  17:12:21  mike
 * Make score come after endgame screens.
 * 
 * Revision 1.85  1995/02/01  14:04:17  adam
 * mucked with screens
 * 
 * Revision 1.84  1995/01/28  16:59:30  adam
 * added hook for special first briefing music
 * 
 * Revision 1.83  1995/01/21  17:04:35  mike
 * fix endgame text bogosity.
 * 
 * Revision 1.82  1995/01/21  16:26:29  matt
 * Made endlevel briefing work with missions
 * 
 * Revision 1.81  1995/01/21  13:15:20  adam
 * added new robot briefings.
 * 
 * Revision 1.80  1995/01/20  22:47:33  matt
 * Mission system implemented, though imcompletely
 * 
 * Revision 1.79  1995/01/20  14:57:52  mike
 * support arbitrary number of screens/level.
 * 
 * Revision 1.78  1995/01/15  14:29:12  john
 * Made the exit door page in.
 * 
 * Revision 1.77  1995/01/15  14:27:09  adam
 * messed with endgame stuff
 * 
 * Revision 1.76  1995/01/14  15:42:49  mike
 * Make endgame for registered support 3 screens.
 * 
 * Revision 1.75  1995/01/14  14:00:59  adam
 * *** empty log message ***
 * 
 * Revision 1.74  1995/01/09  11:28:53  mike
 * Support new $O thingy for bitmaps which cycle and are not the exit door.
 * 
 * Revision 1.73  1995/01/02  12:39:13  mike
 * fix secret level sequencing.
 * 
 * Revision 1.72  1994/12/12  19:44:14  rob
 * Added kill matrix to end of game sequence.
 * 
 * Revision 1.71  1994/12/09  22:32:57  adam
 * messed with text positioning
 * 
 * Revision 1.70  1994/12/09  14:08:37  mike
 * make briefing text work with hog files.
 * 
 * Revision 1.69  1994/12/09  00:41:47  mike
 * fix hang in automap print screen.
 * 
 * Revision 1.68  1994/12/08  20:56:36  john
 * More cfile stuff.
 * 
 * Revision 1.67  1994/12/08  17:19:11  yuan
 * Cfiling stuff.
 * 
 * Revision 1.66  1994/12/07  11:28:00  matt
 * Did a localization suppport
 * 
 * Revision 1.65  1994/12/06  17:10:23  yuan
 * Fixed missing )
 * 
 * Revision 1.64  1994/12/06  17:00:45  rob
 * Fixed problem with finishing the game in modem/serial mode.
 * 
 * Revision 1.63  1994/12/06  16:58:37  matt
 * Killed warnings
 * 
 * Revision 1.62  1994/12/06  15:54:28  mike
 * fix guy at end...
 * 
 */

#pragma off (unreferenced)
static char rcsid[] = "$Id: titles.c 1.13 1995/11/03 12:52:23 allender Exp $";
#pragma on (unreferenced)

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "dtypes.h"
#include "timer.h"
#include "key.h"
#include "gr.h"
#include "palette.h"
#include "iff.h"
#include "pcx.h"
#include "mem.h"
#include "joy.h"
#include "arcade.h"
#include "coindev.h"
#include "mono.h"
#include "gamefont.h"
#include "cfile.h"
#include "error.h"
#include "polyobj.h"
#include "textures.h"
#include "screens.h"
#include "multi.h"
#include "player.h"
#include "digi.h"
#include "compbit.h"
#include "text.h"
#include "kmatrix.h"
#include "piggy.h"
#include "songs.h"
#include "vfx.h"
#include "newmenu.h"
#include "state.h"
#include "gameseq.h"
#include "texmap.h"
#include "macsys.h"		// for bitblt_to_screen()
#include "redbook.h"

ubyte New_pal[768];
int	New_pal_254_bash;

char	* Briefing_text;

#define	MAX_BRIEFING_COLORS	2

char Ending_text_filename[13] = "endreg.tex";

char Briefing_text_filename[13] = "briefing.tex";

#define	SHAREWARE_ENDING_FILENAME	"ending.tex"

//	Can be set by -noscreens command line option.  Causes bypassing of all briefing screens.
int	Skip_briefing_screens=0;
int	Briefing_foreground_colors[MAX_BRIEFING_COLORS], Briefing_background_colors[MAX_BRIEFING_COLORS];
int	Current_color = 0;
int	Erase_color;

typedef struct {
	char	bs_name[14];						//	filename, eg merc01.  Assumes .lbm suffix.
	byte	level_num;
	byte	message_num;
	short	text_ulx, text_uly;		 	//	upper left x,y of text window
	short	text_width, text_height; 	//	width and height of text window
} briefing_screen;

#define BRIEFING_SECRET_NUM	31			//	This must correspond to the first secret level which must come at the end of the list.
#define BRIEFING_OFFSET_NUM	4			// This must correspond to the first level screen (ie, past the bald guy briefing screens)

//#ifdef SHAREWARE
//#define SHAREWARE_ENDGAME_NUM	11			//	Shareware briefing screen name.
//#else
//#define SHAREWARE_ENDGAME_NUM	34			//	Shareware briefing screen name.
//#define REGISTERED_ENDGAME_NUM	35					//	Registered briefing screen name.
//#define NUM_REGISTERED_ENDGAME_SCREENS	3			//	Number of registered endgame screens
//#endif

#define	SHAREWARE_ENDING_LEVEL_NUM		0x7f
#define	REGISTERED_ENDING_LEVEL_NUM	0x7e

#define NEW_END_GUY1	1
#define NEW_END_GUY2	3

briefing_screen Briefing_screens[] = {
	{ "brief01.pcx",   0,  1,  31, 336, 696, 141 },
	{ "brief02.pcx",   0,  2,  64,  81, 616, 424 },
	{ "brief03.pcx",   0,  3,  48,  52, 616, 424 },
	{ "brief02.pcx",   0,  4,  64,  81, 616, 424 },
	{ "moon01.pcx",    1,  5,  24,  24, 720, 408 },
	{ "moon01.pcx",    2,  6,  24,  24, 720, 408 },
	{ "moon01.pcx",    3,  7,  24,  24, 720, 408 },
#ifndef MAC_SHAREARE
	{ "venus01.pcx",   4,  8,  36,  36, 720, 480 },
	{ "venus01.pcx",   5,  9,  36,  36, 720, 480 },
	{ "brief03.pcx",   6, 10,  48,  52, 616, 424 },
	{ "merc01.pcx",    6, 11,  24,  36, 720, 480 },
	{ "merc01.pcx",    7, 12,  24,  36, 720, 480 },
	{ "brief03.pcx",   8, 13,  48,  52, 616, 424 },
	{ "mars01.pcx",    8, 14,  24, 240, 720, 480 },
	{ "mars01.pcx",    9, 15,  24, 240, 720, 480 },
	{ "brief03.pcx",  10, 16,  48,  52, 616, 424 },
	{ "mars01.pcx",   10, 17,  24, 240, 720, 480 },
	{ "jup01.pcx",    11, 18,  24,  96, 720, 480 },
	{ "jup01.pcx",    12, 19,  24,  96, 720, 480 },
	{ "brief03.pcx",  13, 20,  48,  52, 616, 424 },
	{ "jup01.pcx",    13, 21,  24,  96, 720, 480 },
	{ "jup01.pcx",    14, 22,  24,  96, 720, 480 },
	{ "saturn01.pcx", 15, 23,  24,  96, 720, 480 },
	{ "brief03.pcx",  16, 24,  48,  52, 616, 424 },
	{ "saturn01.pcx", 16, 25,  24,  96, 720, 480 },
	{ "brief03.pcx",  17, 26,  48,  52, 616, 424 },
	{ "saturn01.pcx", 17, 27,  24,  96, 720, 480 },
	{ "uranus01.pcx", 18, 28, 240, 240, 720, 480 },
	{ "uranus01.pcx", 19, 29, 240, 240, 720, 480 },
	{ "uranus01.pcx", 20, 30, 240, 240, 720, 480 },
	{ "uranus01.pcx", 21, 31, 240, 240, 720, 480 },
	{ "neptun01.pcx", 22, 32,  24,  48, 720, 480 },
	{ "neptun01.pcx", 23, 33,  24,  48, 720, 480 },
	{ "neptun01.pcx", 24, 34,  24,  48, 720, 480 },
	{ "pluto01.pcx",  25, 35,  24,  48, 720, 480 },
	{ "pluto01.pcx",  26, 36,  24,  48, 720, 480 },
	{ "pluto01.pcx",  27, 37,  24,  48, 720, 480 },
	{ "aster01.pcx",  -1, 38,  24, 216, 720, 480 },
	{ "aster01.pcx",  -2, 39,  24, 216, 720, 480 },
	{ "aster01.pcx",  -3, 40,  24, 216, 720, 480 },
#endif
	{ "end01.pcx",   127,  1,  55,  96, 768, 480 },
#ifndef MAC_SHAREWARE
	{ "end02.pcx",   126,  1,  12,  12, 720, 480 },
	{ "end01.pcx",   126,  2,  55,  96, 768, 480 },
//	{ "brief03.pcx",   126,  2,  55,  96, 768, 480 },
	{ "end02.pcx",   126,  3,  12,  12, 720, 480 }
//	{ "end01.pcx",   126,  2,  55,  96, 768, 480 },
//	{ "end03.pcx",   126,  3,  12,  12, 720, 480 }
#endif

};

#define	MAX_BRIEFING_SCREEN	(sizeof(Briefing_screens) / sizeof(Briefing_screens[0]))


void title_save_game();

int local_key_inkey(void)
{
	int	rval;

	rval = key_inkey();

	if ( rval==KEY_ALTED+KEY_F2 )	{
	 	title_save_game();
		return 0;
	}

	if ( (rval == KEY_PRINT_SCREEN) || (rval == KEY_COMMAND + KEY_SHIFTED + KEY_3) ) {
		save_screen_shot(0);
		return 0;				//say no key pressed
	}
	
	if ( rval == KEY_Q+KEY_COMMAND )
		do_appl_quit();
		
	if (!rval && mouse_went_down(0))
		rval = KEY_ENTER;

	return rval;
}

int show_title_screen( char * filename, int allow_keys )	
{
	fix timer;
	int pcx_error, i;
	grs_bitmap title_bm;

	title_bm.bm_data=NULL;
	if ((pcx_error=pcx_read_bitmap( filename, &title_bm, BM_LINEAR, New_pal ))!=PCX_ERROR_NONE)	{
//		printf( "File '%s', PCX load error: %s (%i)\n  (No big deal, just no title screen.)\n",filename, pcx_errormsg(pcx_error), pcx_error);
		mprintf((0, "File '%s', PCX load error: %s (%i)\n  (No big deal, just no title screen.)\n",filename, pcx_errormsg(pcx_error), pcx_error));
		Int3();
		return 0;
	}

//	vfx_set_palette_sub( New_pal );
	gr_palette_clear();	
	gr_set_current_canvas( NULL );
	gr_bitmap( 0, 0, &title_bm );
	bitblt_to_screen();
	if (gr_palette_fade_in( New_pal, 32, allow_keys ))	
		return 1;

	gr_palette_load( New_pal );
	timer	= timer_get_fixed_seconds() + i2f(3);
	while (1)	{
		if ( local_key_inkey() && allow_keys ) break;
		if ( timer_get_fixed_seconds() > timer ) break;

		#ifdef ARCADE
		{
			int coins;
			coins = coindev_count(0);
			if (coins>0)	{
				Arcade_timer = F1_0 * ARCADE_FIRST_SECONDS;		// Two minutes to play...
				if (coins>1)
					Arcade_timer += F1_0 * ARCADE_CONTINUE_SECONDS*(coins-1);		// Two minutes to play...
				break;
			}
		}
		#endif
	}			
	if (gr_palette_fade_out( New_pal, 32, allow_keys ))
		return 1;
	myfree(title_bm.bm_data);
	return 0;
}

char * get_briefing_screen( int level_num )
{
	int i, found_level=0, last_level=0;

	for (i = 0; i < MAX_BRIEFING_SCREEN; i++)	{
		if ( found_level && Briefing_screens[i].level_num != level_num )
			return Briefing_screens[last_level].bs_name;
		if (Briefing_screens[i].level_num == level_num )	{
			found_level=1;
			last_level = i;
		}
	}
	return NULL;
}




int	Briefing_text_x, Briefing_text_y;

void init_char_pos(int x, int y)
{
	Briefing_text_x = x;
	Briefing_text_y = y;
}

grs_canvas	*Robot_canv = NULL;
vms_angvec	Robot_angles;
short		Robot_pitch_value = 0;

char	Bitmap_name[32] = "";
#define	EXIT_DOOR_MAX	14
#define	OTHER_THING_MAX	10		//	Adam: This is the number of frames in your new animating thing.
#define	DOOR_DIV_INIT	6
byte	Door_dir=1, Door_div_count=0, Animating_bitmap_type=0;

//	-----------------------------------------------------------------------------
void show_bitmap_frame(void)
{
	grs_canvas	*curcanv_save, *bitmap_canv;
	grs_bitmap	*bitmap_ptr;

	//	Only plot every nth frame.
	if (Door_div_count) {
		Door_div_count--;
		return;
	}

	Door_div_count = DOOR_DIV_INIT;

	if (Bitmap_name[0] != 0) {
		char		*pound_signp;
		int		num, dig1, dig2;

		//	Set supertransparency color to black
		if (!New_pal_254_bash) {
			New_pal_254_bash = 1;
			New_pal[254*3] = 0;
			New_pal[254*3+1] = 0;
			New_pal[254*3+2] = 0;
			gr_palette_load( New_pal );
		}

		switch (Animating_bitmap_type) {
//			case 0:	bitmap_canv = gr_create_sub_canvas(grd_curcanv, 220, 45, 64, 64);	break;
//			case 1:	bitmap_canv = gr_create_sub_canvas(grd_curcanv, 220, 45, 94, 94);	break;	//	Adam: Change here for your new animating bitmap thing. 94, 94 are bitmap size.
			case 0:	bitmap_canv = gr_create_sub_canvas(grd_curcanv, 440, 110, 128, 128);	break;
			case 1:	bitmap_canv = gr_create_sub_canvas(grd_curcanv, 440, 160, 150, 150);	break;	//	Adam: Change here for your new animating bitmap thing. 94, 94 are bitmap size.
			default:	Int3();	//	Impossible, illegal value for Animating_bitmap_type
		}

		curcanv_save = grd_curcanv;
		grd_curcanv = bitmap_canv;

		pound_signp = strchr(Bitmap_name, '#');
		Assert(pound_signp != NULL);

		dig1 = *(pound_signp+1);
		dig2 = *(pound_signp+2);
		if (dig2 == 0)
			num = dig1-'0';
		else
			num = (dig1-'0')*10 + (dig2-'0');

		switch (Animating_bitmap_type) {
			case 0:
				num += Door_dir;
				if (num > EXIT_DOOR_MAX) {
					num = EXIT_DOOR_MAX;
					Door_dir = -1;
				} else if (num < 0) {
					num = 0;
					Door_dir = 1;
				}
				break;
			case 1:
				num++;
				if (num > OTHER_THING_MAX)
					num = 0;
				break;
		}

		Assert(num < 100);
		if (num >= 10) {
			*(pound_signp+1) = (num / 10) + '0';
			*(pound_signp+2) = (num % 10) + '0';
			*(pound_signp+3) = 0;
		} else {
			*(pound_signp+1) = (num % 10) + '0';
			*(pound_signp+2) = 0;
		}

		{
			bitmap_index bi;
			bi = piggy_find_bitmap(Bitmap_name);
			bitmap_ptr = &GameBitmaps[bi.index];
			PIGGY_PAGE_IN( bi );
		}

		gr_bitmapm(0, 0, bitmap_ptr);
		grd_curcanv = curcanv_save;
		myfree(bitmap_canv);

		switch (Animating_bitmap_type) {
			case 0:
				if (num == EXIT_DOOR_MAX) {
					Door_dir = -1;
					Door_div_count = 64;
				} else if (num == 0) {
					Door_dir = 1;
					Door_div_count = 64;
				}
				break;
			case 1:
				break;
		}
	}

}

//	-----------------------------------------------------------------------------
void show_briefing_bitmap(grs_bitmap *bmp)
{
	grs_canvas	*curcanv_save, *bitmap_canv;

#ifdef MAC_SHAREWARE
	bitmap_canv = gr_create_sub_canvas(grd_curcanv, 440, 108, 332, 331);
#else
	bitmap_canv = gr_create_sub_canvas(grd_curcanv, 220, 45, 166, 138);
#endif
	curcanv_save = grd_curcanv;
	grd_curcanv = bitmap_canv;
	gr_bitmapm(0, 0, bmp);
	bitblt_to_screen();
	grd_curcanv = curcanv_save;
	myfree(bitmap_canv);
}

//	-----------------------------------------------------------------------------
void show_spinning_robot_frame(int robot_num)
{
	grs_canvas	*curcanv_save;

	if (robot_num != -1) {
		Robot_angles.h += 300;
#if 0
		Robot_angles.p += Robot_pitch_value;
		if ((Robot_pitch_value > 0) && (Robot_angles.p > 1820))
			Robot_pitch_value = -Robot_pitch_value;
		else if ((Robot_pitch_value < 0) && (Robot_angles.p < -1820))
			Robot_pitch_value = -Robot_pitch_value;
#endif

		curcanv_save = grd_curcanv;
		grd_curcanv = Robot_canv;
		Assert(Robot_info[robot_num].model_num != -1);
		draw_model_picture(Robot_info[robot_num].model_num, &Robot_angles);
		grd_curcanv = curcanv_save;
	}

}

//	-----------------------------------------------------------------------------
void init_spinning_robot(void)
{
	Robot_angles.p = 0;
	Robot_angles.b = 0;
	Robot_angles.h = 0;
	
	Robot_pitch_value = 90;

//	Robot_canv = gr_create_sub_canvas(grd_curcanv, 138, 55, 166, 138);
//	Robot_canv = gr_create_sub_canvas(grd_curcanv, 276, 110, 322, 276);
	Robot_canv = gr_create_sub_canvas(grd_curcanv, 288, 110, 312, 276);
}

//	-----------------------------------------------------------------------------
//	Returns char width.
//	If show_robot_flag set, then show a frame of the spinning robot.
int show_char_delay(char the_char, int delay, int robot_num, int cursor_flag)
{
	int	w, h, aw;
	char	message[2];
	fix	start_time;
	int	i;

	start_time = timer_get_fixed_seconds();

	message[0] = the_char;
	message[1] = 0;

	gr_get_string_size(message, &w, &h, &aw );

	Assert((Current_color >= 0) && (Current_color < MAX_BRIEFING_COLORS));

	//	Draw cursor if there is some delay and caller says to draw cursor
	if (cursor_flag && delay) {
		gr_set_fontcolor(Briefing_foreground_colors[Current_color], -1);
		gr_printf(Briefing_text_x+1, Briefing_text_y, "_" );
	}

	for (i=0; i<2; i++) {
		if ((robot_num != -1) && (delay != 0))
			show_spinning_robot_frame(robot_num);
		if (delay != 0)
			show_bitmap_frame();

		while (timer_get_fixed_seconds() < start_time + delay/2)
			;

		start_time = timer_get_fixed_seconds();
	}

	//	Erase cursor
	if (cursor_flag && delay) {
		gr_set_fontcolor(Erase_color, -1);
		gr_printf(Briefing_text_x+1, Briefing_text_y, "_" );
	}

	//	Draw the character
	gr_set_fontcolor(Briefing_background_colors[Current_color], -1);
	gr_printf(Briefing_text_x, Briefing_text_y, message );

	gr_set_fontcolor(Briefing_foreground_colors[Current_color], -1);
	gr_printf(Briefing_text_x+1, Briefing_text_y, message );

//	if (the_char != ' ')
//		if (!digi_is_sound_playing(231))
//			digi_play_sample( 231, F1_0 );

	return w;
}

#ifndef MAC_SHAREWARE
extern char new_baldguy_pcx[];
ubyte baldguy_cheat = 0;
#endif

//	-----------------------------------------------------------------------------
int load_briefing_screen( int screen_num )
{
	int	pcx_error;

#ifndef MAC_SHAREWARE
	if ( ((screen_num == NEW_END_GUY1) || (screen_num == NEW_END_GUY2)) && baldguy_cheat) {
		if ( bald_guy_load(new_baldguy_pcx, &grd_curcanv->cv_bitmap, grd_curcanv->cv_bitmap.bm_type, New_pal) == 0)
			return 0;
	}
#endif
	if ((pcx_error=pcx_read_bitmap( Briefing_screens[screen_num].bs_name, &grd_curcanv->cv_bitmap, grd_curcanv->cv_bitmap.bm_type, New_pal ))!=PCX_ERROR_NONE)	{
//		printf( "File '%s', PCX load error: %s\n  (It's a briefing screen.  Does this cause you pain?)\n",Briefing_screens[screen_num].bs_name, pcx_errormsg(pcx_error));
		mprintf((0, "File '%s', PCX load error: %s (%i)\n  (It's a briefing screen.  Does this cause you pain?)\n",Briefing_screens[screen_num].bs_name, pcx_errormsg(pcx_error), pcx_error));
		Int3();
		return 0;
	}

	return 0;
}

#define	KEY_DELAY_DEFAULT	((F1_0*28)/1000)

//	-----------------------------------------------------------------------------
int get_message_num(char **message)
{
	int	num=0;

	while (**message == ' ')
		(*message)++;

	while ((**message >= '0') && (**message <= '9')) {
		num = 10*num + **message-'0';
		(*message)++;
	}

	while (*(*message)++ != 10)		//	Get and drop eoln
		;

	return num;
}

void title_save_game()
{
	grs_canvas * save_canv;
	grs_canvas * save_canv_data;
	grs_font * save_font;
	ubyte palette[768];

	if ( Next_level_num == 0 ) return;
	
	save_canv = grd_curcanv;
	save_font = grd_curcanv->cv_font;

	save_canv_data = gr_create_canvas( grd_curcanv->cv_bitmap.bm_w, grd_curcanv->cv_bitmap.bm_h );
	gr_set_current_canvas(save_canv_data);
	gr_ubitmap(0,0,&save_canv->cv_bitmap);
	gr_set_current_canvas(save_canv);
	gr_clear_canvas(gr_find_closest_color_current( 0, 0, 0));
	gr_palette_read( palette );
	gr_palette_load( gr_palette );
	state_save_all(1);
	gr_palette_clear();
	
	gr_set_current_canvas(save_canv);
	gr_ubitmap(0,0,&save_canv_data->cv_bitmap);
	gr_palette_load( palette );
	gr_set_curfont(save_font);
}


//	-----------------------------------------------------------------------------
void get_message_name(char **message, char *result)
{
	while (**message == ' ')
		(*message)++;

	while ((**message != ' ') && (**message != 10)) {
		if (**message != 13)
			*result++ = **message;
		(*message)++;
	}

	if (**message != 10)
		while (*(*message)++ != 10)		//	Get and drop eoln
			;

	*result = 0;
}

//	-----------------------------------------------------------------------------
void flash_cursor(int cursor_flag)
{
	if (cursor_flag == 0)
		return;

	if ((timer_get_fixed_seconds() % (F1_0/2) ) > (F1_0/4))
		gr_set_fontcolor(Briefing_foreground_colors[Current_color], -1);
	else
		gr_set_fontcolor(Erase_color, -1);

	gr_printf(Briefing_text_x+1, Briefing_text_y, "_" );

}

//	-----------------------------------------------------------------------------
//	Return true if message got aborted by user (pressed ESC), else return false.
int show_briefing_message(int screen_num, char *message)
{
	int	prev_ch=-1;
	int	ch, done=0;
	briefing_screen	*bsp = &Briefing_screens[screen_num];
	int	delay_count = KEY_DELAY_DEFAULT;
	int	key_check;
	int	robot_num=-1;
	int	rval=0;
	int	tab_stop=0;
	int	flashing_cursor=0;
	int	new_page=0;

	Bitmap_name[0] = 0;

	Current_color = 0;

	// mprintf((0, "Going to print message [%s] at x=%i, y=%i\n", message, x, y));
	gr_set_curfont( GAME_FONT );    

	init_char_pos(bsp->text_ulx, bsp->text_uly);

	while (!done) {
		ch = *message++;
		if (ch == '$') {
			ch = *message++;
			if (ch == 'C') {
				Current_color = get_message_num(&message)-1;
				Assert((Current_color >= 0) && (Current_color < MAX_BRIEFING_COLORS));
				prev_ch = 10;
			} else if (ch == 'F') {		//	toggle flashing cursor
				flashing_cursor = !flashing_cursor;
				prev_ch = 10;
				while (*message++ != 10)
					;
			} else if (ch == 'T') {
				tab_stop = get_message_num(&message);
				prev_ch = 10;							//	read to eoln
			} else if (ch == 'R') {
				if (Robot_canv != NULL)
					{myfree(Robot_canv); Robot_canv=NULL;}

				init_spinning_robot();
				robot_num = get_message_num(&message);
				prev_ch = 10;							//	read to eoln
			} else if (ch == 'N') {
				//--grs_bitmap	*bitmap_ptr;
				if (Robot_canv != NULL)
					{myfree(Robot_canv); Robot_canv=NULL;}

				get_message_name(&message, Bitmap_name);
				strcat(Bitmap_name, "#0");
				Animating_bitmap_type = 0;
				prev_ch = 10;
			} else if (ch == 'O') {
				if (Robot_canv != NULL)
					{myfree(Robot_canv); Robot_canv=NULL;}

				get_message_name(&message, Bitmap_name);
				strcat(Bitmap_name, "#0");
				Animating_bitmap_type = 1;
				prev_ch = 10;
			} else if (ch == 'B') {
				char			bitmap_name[32];
				grs_bitmap	guy_bitmap;
				ubyte			temp_palette[768];
				int			iff_error;

				if (Robot_canv != NULL)
					{myfree(Robot_canv); Robot_canv=NULL;}

				get_message_name(&message, bitmap_name);
				strcat(bitmap_name, ".bbm");
				guy_bitmap.bm_data = NULL;
				iff_error = iff_read_bitmap(bitmap_name, &guy_bitmap, BM_LINEAR, temp_palette);
				Assert(iff_error == IFF_NO_ERROR);

				show_briefing_bitmap(&guy_bitmap);
				myfree(guy_bitmap.bm_data);
				prev_ch = 10;
//			} else if (ch == 'B') {
//				if (Robot_canv != NULL)
//					{myfree(Robot_canv); Robot_canv=NULL;}
//
//				bitmap_num = get_message_num(&message);
//				if (bitmap_num != -1)
//					show_briefing_bitmap(Textures[bitmap_num]);
//				prev_ch = 10;							//	read to eoln
			} else if (ch == 'S') {
				int	keypress;
				fix	start_time;

				start_time = timer_get_fixed_seconds();
				while ( (keypress = local_key_inkey()) == 0 ) {		//	Wait for a key
					while (timer_get_fixed_seconds() < start_time + KEY_DELAY_DEFAULT/2)
						;
					flash_cursor(flashing_cursor);
					show_spinning_robot_frame(robot_num);
					show_bitmap_frame();
#ifndef MAC_SHAREWARE
					redbook_restart_track();
#endif
					start_time += KEY_DELAY_DEFAULT/2;
					bitblt_to_screen();
						
				}

#ifndef NDEBUG
				if (keypress == KEY_BACKSP)
					Int3();
#endif
				if (keypress == KEY_ESC)
					rval = 1;

				flashing_cursor = 0;
				done = 1;
			} else if (ch == 'P') {		//	New page.
				new_page = 1;
				while (*message != 10) {
					message++;	//	drop carriage return after special escape sequence
				}
				message++;
				prev_ch = 10;
			}
		} else if (ch == '\t') {		//	Tab
			if (Briefing_text_x - bsp->text_ulx < tab_stop)
				Briefing_text_x = bsp->text_ulx + tab_stop;
		} else if ((ch == ';') && (prev_ch == 10)) {
			while (*message++ != 10)
				;
			prev_ch = 10;
		} else if (ch == '\\') {
			prev_ch = ch;
		} else if (ch == 10) {
			if (prev_ch != '\\') {
				prev_ch = ch;
				Briefing_text_y += 16;
				Briefing_text_x = bsp->text_ulx;
				if (Briefing_text_y > bsp->text_uly + bsp->text_height) {
					load_briefing_screen(screen_num);
					Briefing_text_x = bsp->text_ulx;
					Briefing_text_y = bsp->text_uly;
				}
			} else {
				if (ch == 13)
					Int3();
				prev_ch = ch;
			}
		} else {
			prev_ch = ch;
			Briefing_text_x += show_char_delay(ch, delay_count, robot_num, flashing_cursor);
		}

		//	Check for Esc -> abort.
		key_check = local_key_inkey();
		if ( key_check == KEY_ESC ) {
			rval = 1;
			done = 1;
		}

		if ( key_check == KEY_ALTED+KEY_F2 )	
			title_save_game();

		if ((key_check == KEY_SPACEBAR) || (key_check == KEY_ENTER))
			delay_count = 0;

		if (Briefing_text_x > bsp->text_ulx + bsp->text_width) {
			Briefing_text_x = bsp->text_ulx;
			Briefing_text_y += 16;
		}

		if ((new_page) || (Briefing_text_y > bsp->text_uly + bsp->text_height)) {
			fix	start_time = 0;
			int	keypress;

			new_page = 0;
			start_time = timer_get_fixed_seconds();
			while ( (keypress = local_key_inkey()) == 0 ) {		//	Wait for a key
				while (timer_get_fixed_seconds() < start_time + KEY_DELAY_DEFAULT/2)
					;
				flash_cursor(flashing_cursor);
				show_spinning_robot_frame(robot_num);
				show_bitmap_frame();
#ifndef MAC_SHAREWARE
				redbook_restart_track();
#endif
				start_time += KEY_DELAY_DEFAULT/2;
				bitblt_to_screen();
			}

			robot_num = -1;

#ifndef NDEBUG
			if (keypress == KEY_BACKSP)
				Int3();
#endif
			if (keypress == KEY_ESC) {
				rval = 1;
				done = 1;
			}

			load_briefing_screen(screen_num);
			Briefing_text_x = bsp->text_ulx;
			Briefing_text_y = bsp->text_uly;
			delay_count = KEY_DELAY_DEFAULT;
		}
		bitblt_to_screen();
	}

	if (Robot_canv != NULL)
		{myfree(Robot_canv); Robot_canv=NULL;}

	return rval;
}

//	-----------------------------------------------------------------------------
//	Return a pointer to the start of text for screen #screen_num.
char * get_briefing_message(int screen_num)
{
	char	*tptr = Briefing_text;
	int	cur_screen=0;
	int	ch;

	Assert(screen_num >= 0);

	while ( (*tptr != 0 ) && (screen_num != cur_screen)) {
		ch = *tptr++;
		if (ch == '$') {
			ch = *tptr++;
			if (ch == 'S')
				cur_screen = get_message_num(&tptr);
		}
	}

	return tptr;
}

// -----------------------------------------------------------------------------
//	Load Descent briefing text.
void load_screen_text(char *filename, char **buf)
{
	CFILE	*tfile;
	CFILE *ifile;
	int	len, i;
	int	have_binary = 0;

	if ((tfile = cfopen(filename,"rb")) == NULL) {
		char nfilename[30], *ptr;

		strcpy(nfilename, filename);
		ptr = strrchr(nfilename, '.');
		*ptr = '\0';
		strcat(nfilename, ".txb");
		if ((ifile = cfopen(nfilename, "rb")) == NULL)
			Error("Cannot open file %s or %s", filename, nfilename);
		have_binary = 1;

		len = cfilelength(ifile);
		MALLOC(*buf, char, len);
		cfread(*buf, 1, len, ifile);
		cfclose(ifile);
	} else {
		len = cfilelength(tfile);
		MALLOC(*buf, char, len);
		cfread(*buf, 1, len, tfile);
		cfclose(tfile);
	}

	if (have_binary) {
		char *ptr;

		for (i = 0, ptr = *buf; i < len; i++, ptr++) {
			if (*ptr != 0x0a) {
				encode_rotate_left(ptr);
				*ptr = *ptr ^ BITMAP_TBL_XOR;
				encode_rotate_left(ptr);
			}
		}
	}

}

//	-----------------------------------------------------------------------------
//	Return true if message got aborted, else return false.
int show_briefing_text(int screen_num)
{
	char	*message_ptr;

	// briefing_screen	*bsp = &Briefing_screens[screen_num];

	Briefing_foreground_colors[0] = gr_find_closest_color_current( 0, 54, 0);
	Briefing_background_colors[0] = gr_find_closest_color_current( 0, 19, 0);

	Briefing_foreground_colors[1] = gr_find_closest_color_current( 42, 38, 32);
	Briefing_background_colors[1] = gr_find_closest_color_current( 14, 14, 14);

	Erase_color = gr_find_closest_color_current(0, 0, 0);

	message_ptr = get_briefing_message(Briefing_screens[screen_num].message_num);

	return show_briefing_message(screen_num, message_ptr);
}

//	-----------------------------------------------------------------------------
//	Return true if screen got aborted by user, else return false.
int show_briefing_screen( int screen_num, int allow_keys)
{
	int	rval=0;
	int	pcx_error;
	grs_bitmap briefing_bm;
	int imsave;

	New_pal_254_bash = 0;

	if (Skip_briefing_screens) {
		mprintf((0, "Skipping briefing screen [%s]\n", &Briefing_screens[screen_num].bs_name));
		return 0;
	}

	briefing_bm.bm_data=NULL;	
#ifndef MAC_SHAREWARE
	if ( ((screen_num == NEW_END_GUY1) || (screen_num == NEW_END_GUY2)) && baldguy_cheat) {
		if ( bald_guy_load(new_baldguy_pcx, &briefing_bm, BM_LINEAR, New_pal) == PCX_ERROR_NONE)
			goto do_screen;
	}
#endif
	if ((pcx_error=pcx_read_bitmap( Briefing_screens[screen_num].bs_name, &briefing_bm, BM_LINEAR, New_pal ))!=PCX_ERROR_NONE)	{
//		printf( "PCX load error: %s.  File '%s'\n\n", pcx_errormsg(pcx_error), Briefing_screens[screen_num].bs_name);
		mprintf((0, "File '%s', PCX load error: %s (%i)\n  (It's a briefing screen.  Does this cause you pain?)\n",Briefing_screens[screen_num].bs_name, pcx_errormsg(pcx_error), pcx_error));
		Int3();
		return 0;
	}

do_screen:
//	vfx_set_palette_sub( New_pal );
	gr_palette_clear();
	gr_bitmap( 0, 0, &briefing_bm );
	bitblt_to_screen();
	
	if (gr_palette_fade_in( New_pal, 32, allow_keys ))	
		return 1;

	imsave = Interpolation_method;
	Interpolation_method = 1;
	rval = show_briefing_text(screen_num);
	Interpolation_method = imsave;

	if (gr_palette_fade_out( New_pal, 32, allow_keys ))
		return 1;

	myfree(briefing_bm.bm_data);

	return rval;
}


//	-----------------------------------------------------------------------------
void do_briefing_screens(int level_num)
{
	int	abort_briefing_screens = 0;
	int	cur_briefing_screen = 0;

	if (Skip_briefing_screens) {
		mprintf((0, "Skipping all briefing screens.\n"));
		return;
	}

	if (!Briefing_text_filename[0])		//no filename?
		return;

	songs_play_song( SONG_BRIEFING, 1 );

	set_screen_mode( SCREEN_MENU );
	gr_set_current_canvas(NULL);

	key_flush();

	load_screen_text(Briefing_text_filename, &Briefing_text);

	if (level_num == 1) {
		while ((!abort_briefing_screens) && (Briefing_screens[cur_briefing_screen].level_num == 0)) {
			abort_briefing_screens = show_briefing_screen(cur_briefing_screen, 0);
			cur_briefing_screen++;
		}
	}

	if (!abort_briefing_screens) {
		for (cur_briefing_screen = 0; cur_briefing_screen < MAX_BRIEFING_SCREEN; cur_briefing_screen++)
			if (Briefing_screens[cur_briefing_screen].level_num == level_num)
				if (show_briefing_screen(cur_briefing_screen, 0))
					break;
	}


	myfree(Briefing_text);

	key_flush();
}

#ifndef MAC_SHAREWARE
void do_registered_end_game(void)
{
	int	cur_briefing_screen;

	if (!Ending_text_filename[0])		//no filename?
		return;

	if ((Game_mode & GM_MULTI) && !(Game_mode & GM_MULTI_COOP))
	{
		// Special ending for deathmatch!!
		int len = 40;
		
		MALLOC(Briefing_text, char, len);
		sprintf(Briefing_text, "Test");
	}
		
	load_screen_text(Ending_text_filename, &Briefing_text);

	for (cur_briefing_screen = 0; cur_briefing_screen < MAX_BRIEFING_SCREEN; cur_briefing_screen++)
		if (Briefing_screens[cur_briefing_screen].level_num == REGISTERED_ENDING_LEVEL_NUM)
			if (show_briefing_screen(cur_briefing_screen, 0))
				break;

}
#endif

void do_shareware_end_game(void)
{
	int	cur_briefing_screen;

#ifdef NETWORK
	if ((Game_mode & GM_MULTI) && !(Game_mode & GM_MULTI_COOP))
	{
//		// Special ending for deathmatch!!
//		int len = 120;
//		int i;
//		int max_kills = Players[0].net_kills_total;		
//		int winner = 0;
//
//		for (i=1; i < N_players; i++)
//		{
//			if (Players[i].net_kills_total > max_kills)
//			{	
//				winner = i;
//				max_kills = Players[i].net_kills_total;
//			}
//		}
//
		MALLOC(Briefing_text, char, 4); // Dummy
//		sprintf(Briefing_text, "$S1\n$C1\n\n%s!\n\n%s has won with %d kills.\n\n$S2\n", TXT_SHAREWARE_DONE,Players[winner].callsign, Players[winner].net_kills_total);

		kmatrix_view(0);		// for shareware only -- don't do network processing at the end
		return;
	}
	else 
#endif
	{
#ifdef SATURN
			load_screen_text(Ending_text_filename, &Briefing_text);
#else
			load_screen_text(SHAREWARE_ENDING_FILENAME, &Briefing_text);
#endif
	}

	for (cur_briefing_screen = 0; cur_briefing_screen < MAX_BRIEFING_SCREEN; cur_briefing_screen++)
		if (Briefing_screens[cur_briefing_screen].level_num == SHAREWARE_ENDING_LEVEL_NUM)
			if (show_briefing_screen(cur_briefing_screen, 0))
				break;

}

extern void show_order_form(void);

void do_end_game(void)
{
	set_screen_mode( SCREEN_MENU );
	gr_set_current_canvas(NULL);

	key_flush();

	#ifdef MAC_SHAREWARE
	do_shareware_end_game();		//hurrah! you win!
	#else
		#ifdef SATURN
			do_shareware_end_game();		//hurrah! you win!
		#else
			do_registered_end_game();		//hurrah! you win!
		#endif
	#endif

	if (Briefing_text) {
		myfree(Briefing_text);
		Briefing_text = NULL;
	}

	key_flush();

	Function_mode = FMODE_MENU;

	if ((Game_mode & GM_SERIAL) || (Game_mode & GM_MODEM))
		Game_mode |= GM_GAME_OVER;
	else
		Game_mode = GM_GAME_OVER;

#ifdef SATURN
		show_order_form();
#endif

#ifdef MAC_SHAREWARE
	show_order_form();
#endif

}

