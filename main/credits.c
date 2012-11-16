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
 * $Source: Smoke:miner:source:main::RCS:credits.c $
 * $Revision: 1.8 $
 * $Author: allender $
 * $Date: 1995/11/07 13:54:56 $
 * 
 * Routines to display the credits.
 * 
 * $Log: credits.c $
 * Revision 1.8  1995/11/07  13:54:56  allender
 * loop shareware song since it is too short
 *
 * Revision 1.7  1995/10/31  10:24:25  allender
 * shareware stuff
 *
 * Revision 1.6  1995/10/27  15:17:57  allender
 * minor fix to get them to look right at top and bottom
 * of screens
 *
 * Revision 1.5  1995/10/21  22:50:49  allender
 * credits is way cool!!!!
 *
 * Revision 1.3  1995/08/08  13:45:26  allender
 * added macsys header file
 *
 * Revision 1.2  1995/07/17  08:49:48  allender
 * make work in 640x480 -- still needs major work!!
 *
 * Revision 1.1  1995/05/16  15:24:01  allender
 * Initial revision
 *
 * Revision 2.1  1995/03/06  15:23:30  john
 * New screen techniques.
 * 
 * Revision 2.0  1995/02/27  11:29:25  john
 * New version 2.0, which has no anonymous unions, builds with
 * Watcom 10.0, and doesn't require parsing BITMAPS.TBL.
 * 
 * Revision 1.33  1995/02/11  12:41:56  john
 * Added new song method, with FM bank switching..
 * 
 * Revision 1.32  1995/02/03  14:18:06  john
 * Added columns.
 * 
 * Revision 1.31  1994/12/28  10:43:00  john
 * More VFX tweaking.
 * 
 * Revision 1.30  1994/12/20  18:22:31  john
 * Added code to support non-looping songs, and put
 * it in for endlevel and credits.
 * 
 * Revision 1.29  1994/12/15  14:23:00  adam
 * fixed timing.
 * 
 * Revision 1.28  1994/12/14  16:56:33  adam
 * *** empty log message ***
 * 
 * Revision 1.27  1994/12/14  12:18:11  adam
 * messed w/timing
 * 
 * Revision 1.26  1994/12/12  22:52:59  matt
 * Fixed little bug
 * 
 * Revision 1.25  1994/12/12  22:49:35  adam
 * *** empty log message ***
 * 
 * Revision 1.24  1994/12/09  23:16:50  john
 * Make credits.txb load.
 * 
 * Revision 1.23  1994/12/09  00:41:54  mike
 * fix hang in automap print screen.
 * 
 * Revision 1.22  1994/12/09  00:34:22  matt
 * Added support for half-height lines
 * 
 * Revision 1.21  1994/12/08  18:36:03  yuan
 * More HOGfile support.
 * 
 * Revision 1.20  1994/12/04  14:48:17  john
 * Made credits restore playing descent.hmp.
 * 
 * Revision 1.19  1994/12/04  14:30:20  john
 * Added hooks for music..
 * 
 * Revision 1.18  1994/12/04  12:06:46  matt
 * Put in support for large font
 * 
 * Revision 1.17  1994/12/01  10:47:27  john
 * Took out code that allows keypresses to change scroll rate.
 * 
 * Revision 1.16  1994/11/30  12:10:52  adam
 * added support for PCX titles/brief screens
 * 
 * Revision 1.15  1994/11/27  23:12:17  matt
 * Made changes for new mprintf calling convention
 * 
 * Revision 1.14  1994/11/27  19:51:46  matt
 * Made screen shots work in a few more places
 * 
 * Revision 1.13  1994/11/18  16:41:51  adam
 * trimmed some more meat for shareware
 * 
 * Revision 1.12  1994/11/10  20:38:29  john
 * Made credits not loop.
 * 
 * Revision 1.11  1994/11/05  15:04:06  john
 * Added non-popup menu for the main menu, so that scores and credits don't have to save
 * the background.
 * 
 * Revision 1.10  1994/11/05  14:05:52  john
 * Fixed fade transitions between all screens by making gr_palette_fade_in and out keep
 * track of whether the palette is faded in or not.  Then, wherever the code needs to fade out,
 * it just calls gr_palette_fade_out and it will fade out if it isn't already.  The same with fade_in.
 * This eliminates the need for all the flags like Menu_fade_out, game_fade_in palette, etc.
 * 
 * Revision 1.9  1994/11/04  12:02:32  john
 * Fixed fading transitions a bit more.
 * 
 * Revision 1.8  1994/11/04  11:30:44  john
 * Fixed fade transitions between game/menu/credits.
 * 
 * Revision 1.7  1994/11/04  11:06:32  john
 * Added code to support credit fade table.
 * 
 * Revision 1.6  1994/11/04  10:16:13  john
 * Made the credits fade in/out smoothly on top of a bitmap background.
 * 
 * Revision 1.5  1994/11/03  21:24:12  john
 * Made credits exit the instant a key is pressed.
 * Made it scroll a bit slower.
 * 
 * Revision 1.4  1994/11/03  21:20:28  john
 * Working.
 * 
 * Revision 1.3  1994/11/03  21:01:24  john
 * First version of credits that works.
 * 
 * Revision 1.2  1994/11/03  20:17:39  john
 * Added initial code for showing credits.
 * 
 * Revision 1.1  1994/11/03  20:09:05  john
 * Initial revision
 * 
 * 
 */


#pragma off (unreferenced)
static char rcsid[] = "$Id: credits.c 1.8 1995/11/07 13:54:56 allender Exp $";
#pragma on (unreferenced)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <ctype.h>

#include "error.h"
#include "dtypes.h"
#include "gr.h"
#include "mono.h"
#include "key.h"
#include "palette.h"
#include "game.h"
#include "timer.h"

#include "newmenu.h"
#include "gamefont.h"
#include "network.h"
#include "iff.h"
#include "pcx.h"
#include "mem.h"
#include "mouse.h"
#include "joy.h"
#include "screens.h"
#include "digi.h"

#include "cfile.h"
#include "compbit.h"
#include "vfx.h"
#include "songs.h"
#include "macsys.h"
#include "redbook.h"

//#define ROW_SPACING 30 //24		//11
//#define NUM_LINES 16 //21			//19
#define ROW_SPACING 24		//11
#define NUM_LINES 22			//19

ubyte fade_values[480] = { 1,1,1,2,2,2,2,2,3,3,3,3,3,4,4,4,4,4,5,5,5,
5,5,5,6,6,6,6,6,7,7,7,7,7,8,8,8,8,8,9,9,9,9,9,10,10,10,10,10,10,11,11,11,11,11,12,12,12,12,12,12,
13,13,13,13,13,14,14,14,14,14,14,15,15,15,15,15,15,16,16,16,16,16,17,17,17,17,17,17,18,18,
18,18,18,18,18,19,19,19,19,19,19,20,20,20,20,20,20,20,21,21,21,21,21,21,22,22,22,22,22,22,
22,22,23,23,23,23,23,23,23,24,24,24,24,24,24,24,24,25,25,25,25,25,25,25,25,25,26,26,26,26,
26,26,26,26,26,27,27,27,27,27,27,27,27,27,27,28,28,28,28,28,28,28,28,28,28,28,28,29,29,29,
29,29,29,29,29,29,29,29,29,29,29,30,30,30,30,30,30,30,30,30,30,30,30,30,30,30,30,30,30,30,
30,30,31,31,31,31,31,31,31,31,31,31,31,31,31,31,31,31,31,31,31,31,31,31,31,31,31,31,31,31,
31,31,31,31,31,31,31,31,31,31,31,31,31,31,31,31,31,31,31,31,31,31,31,31,31,31,31,30,30,30,
30,30,30,30,30,30,30,30,30,30,30,30,30,30,30,30,30,30,29,29,29,29,29,29,29,29,29,29,29,29,
29,29,28,28,28,28,28,28,28,28,28,28,28,28,27,27,27,27,27,27,27,27,27,27,26,26,26,26,26,26,
26,26,26,25,25,25,25,25,25,25,25,25,24,24,24,24,24,24,24,24,23,23,23,23,23,23,23,22,22,22,
22,22,22,22,22,21,21,21,21,21,21,20,20,20,20,20,20,20,19,19,19,19,19,19,18,18,18,18,18,18,
18,17,17,17,17,17,17,16,16,16,16,16,15,15,15,15,15,15,14,14,14,14,14,14,13,13,13,13,13,12,
12,12,12,12,12,11,11,11,11,11,10,10,10,10,10,10,9,9,9,9,9,8,8,8,8,8,7,7,7,7,7,6,6,6,6,6,5,5,5,5,
5,5,4,4,4,4,4,3,3,3,3,3,2,2,2,2,2,1,1};

extern ubyte *gr_bitblt_fade_table;

grs_font * header_font;
grs_font * title_font;
grs_font * names_font;

typedef struct box {
	uint	left;
	uint	top;
	uint	width;
	uint	height;
} box;

typedef struct rect {
	uint	left;
	uint	top;
	uint	right;
	uint	bottom;
} rect;

void credits_show()
{
	int i, j, l, done;
	CFILE * file;
	char buffer[NUM_LINES][80];
	grs_bitmap backdrop;
	ubyte backdrop_palette[768];
	int pcx_error;
	int buffer_line = 0;
	fix last_time;
	fix time_delay = 4900;	//2180;			// ~ F1_0 / 12.9
	int first_line_offset,extra_inc=0;
	int have_bin_file = 0;
	char * tempp;
	box	dirty_box[NUM_LINES];

	set_screen_mode(SCREEN_MENU);

	// Clear out all tex buffer lines.
	for (i=0; i<NUM_LINES; i++ ) buffer[i][0] = 0;

	// Clear out all dirty boxes.
	for (i=0; i<NUM_LINES; i++ )
	{
		dirty_box[i].top = dirty_box[i].left = dirty_box[i].width = dirty_box[i].height = 0;
	}

	have_bin_file = 0;
	file = cfopen( "credits.tex", "rb" );
	if (file == NULL) {
		file = cfopen("credits.txb", "rb");
		if (file == NULL)
			Error("Missing CREDITS.TEX and CREDITS.TXB file\n");
		have_bin_file = 1;
	}

	gr_use_palette_table( "credits.256" );
	header_font = gr_init_font( "font2-3.fnt" );
	title_font = gr_init_font( "font2-3.fnt" );
	names_font = gr_init_font( "font2-2.fnt" );
	backdrop.bm_data=NULL;
	pcx_error = pcx_read_bitmap("stars.pcx",&backdrop,grd_curcanv->cv_bitmap.bm_type,backdrop_palette);
	if (pcx_error != PCX_ERROR_NONE)		{
		cfclose(file);
		return;
	}

#ifdef MAC_SHAREWARE
	songs_play_song( SONG_CREDITS, 1 );			// shareware song is too short!!!
#else
	songs_play_song( SONG_CREDITS, 0 );			// registered song is just right!!!
#endif

	gr_remap_bitmap_good( &backdrop,backdrop_palette, -1, -1 );

	gr_set_current_canvas(NULL);
	gr_bitmap(0,0,&backdrop);
	bitblt_to_screen();
	gr_palette_fade_in( gr_palette, 32, 0 );
	gr_set_current_canvas(VR_offscreen_buffer);
	gr_bitmap(0,0,&backdrop);

	key_flush();
	last_time = timer_get_fixed_seconds();
	done = 0;
	first_line_offset = 0;
	while( 1 )	{
		int k;

#ifndef MAC_SHAREWARE
		redbook_restart_track();			// maybe kill the credits music if at the end
#endif
		
		do {
			buffer_line = (buffer_line+1) % NUM_LINES;
			if (cfgets( buffer[buffer_line], 80, file ))	{
				char *p;
				if (have_bin_file) {				// is this a binary tbl file
					for (i = 0; i < strlen(buffer[buffer_line]) - 1; i++) {
						encode_rotate_left(&(buffer[buffer_line][i]));
						buffer[buffer_line][i] ^= BITMAP_TBL_XOR;
						encode_rotate_left(&(buffer[buffer_line][i]));
					}
				}
				p = strchr(&buffer[buffer_line][0],'\n');
				if (p) *p = '\0';
			} else	{
				//fseek( file, 0, SEEK_SET);
				buffer[buffer_line][0] = 0;
				done++;
			}
		} while (extra_inc--);
		extra_inc = 0;

		for (i=0; i<ROW_SPACING; i += 2 )	{
			int y;

			y = first_line_offset - i;

			gr_set_current_canvas(VR_offscreen_buffer);
			for (j=0; j<NUM_LINES; j++ )	{
				char *s;

				l = (buffer_line + j + 1 ) %  NUM_LINES;
				s = buffer[l];

				if ( s[0] == '!' ) {
					s++;
				} else if ( s[0] == '$' )	{
					grd_curcanv->cv_font = header_font;
					s++;
				} else if ( s[0] == '*' )	{
					grd_curcanv->cv_font = title_font;
					s++;
				} else
					grd_curcanv->cv_font = names_font;

				gr_bitblt_fade_table = fade_values;

				{
					int w, h, aw;
					gr_get_string_size( s, &w, &h, &aw );
					dirty_box[j].width = w;
					dirty_box[j].height = h;
					dirty_box[j].top = y;
					dirty_box[j].left = (640 - w) / 2;
					gr_printf( 0x8000, y, s );
				}
				gr_bitblt_fade_table = NULL;
				if (buffer[l][0] == '!')
					y += ROW_SPACING/2;
				else
					y += ROW_SPACING;
			}

			{
				box	*new_box;
				
				for (j=0; j<NUM_LINES; j++ )
				{
					new_box = &dirty_box[j];

					gr_bm_bitblt( new_box->width + 1, new_box->height + 2,
									new_box->left, new_box->top, new_box->left, new_box->top,
									&(VR_offscreen_buffer->cv_bitmap), &(grd_curscreen->sc_canvas.cv_bitmap) );
				}

				bitblt_to_screen();

				for (j=0; j<NUM_LINES; j++ )
				{
					new_box = &dirty_box[j];
					gr_bm_bitblt(   new_box->width
									,new_box->height + 2
									,new_box->left
									,new_box->top
									,new_box->left
									,new_box->top
									,&backdrop
									,&(VR_offscreen_buffer->cv_bitmap) );
				}
				
			}

			while( timer_get_fixed_seconds() < last_time+time_delay );
			last_time = timer_get_fixed_seconds();
		

			k = key_inkey();

			#ifndef NDEBUG
			if (k == KEY_BACKSP) {
				Int3();
				k=0;
			}
			#endif

//			{
//				fix ot = time_delay;
//				time_delay += (keyd_pressed[KEY_X] - keyd_pressed[KEY_Z])*100;
//				if (ot!=time_delay)	{
//					mprintf( (0, "[%x] ", time_delay ));
//				}
//			}

			if (k == KEY_PRINT_SCREEN) {
				save_screen_shot(0);
				k = 0;
			}

			if ((k>0)||(done>NUM_LINES))	{
					gr_close_font(header_font);
					gr_close_font(title_font);
					gr_close_font(names_font);
					gr_palette_fade_out( gr_palette, 32, 0 );
					gr_use_palette_table( "palette.256" );
					myfree(backdrop.bm_data);
					cfclose(file);
					songs_play_song( SONG_TITLE, 1 );
					return;
			}
		}

		if (buffer[(buffer_line + 1 ) %  NUM_LINES][0] == '!') {
			first_line_offset -= ROW_SPACING-ROW_SPACING/2;
			if (first_line_offset <= -ROW_SPACING) {
				first_line_offset += ROW_SPACING;
				extra_inc++;
			}
		}
	}

}


