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
 * $Source: BigRed:miner:source:main::RCS:scores.c $
 * $Revision: 1.1 $
 * $Author: allender $
 * $Date: 1995/12/05 16:06:29 $
 *
 * Inferno High Scores and Statistics System
 *
 * $Log: scores.c $
 * Revision 1.1  1995/12/05  16:06:29  allender
 * Initial revision
 *
 * Revision 1.3  1995/08/14  09:25:16  allender
 * add byteswap header
 *
 * Revision 1.2  1995/07/14  13:45:17  allender
 * fixed up high score code to work and look pretty good
 * needs some work tho'
 *
 * Revision 1.1  1995/05/16  15:30:42  allender
 * Initial revision
 *
 * Revision 2.1  1995/03/06  15:23:57  john
 * New screen techniques.
 * 
 * Revision 2.0  1995/02/27  11:30:53  john
 * New version 2.0, which has no anonymous unions, builds with
 * Watcom 10.0, and doesn't require parsing BITMAPS.TBL.
 * 
 * Revision 1.109  1995/02/09  12:23:19  rob
 * Added assert for length of filename.
 * 
 * Revision 1.108  1995/01/03  17:33:24  john
 * Made scrolling textbox. Used it for scores cool saying.
 * 
 * Revision 1.107  1994/12/28  10:42:51  john
 * More VFX tweaking.
 * 
 * Revision 1.106  1994/12/28  10:26:19  john
 * Fixed some VFX problems.
 * 
 * Revision 1.105  1994/12/15  16:42:12  adam
 * some fix
 * 
 * Revision 1.104  1994/12/14  11:59:19  john
 * Changed the default high scores.
 * 
 * Revision 1.103  1994/12/09  00:41:12  mike
 * fix hang in automap print screen
 * 
 * Revision 1.102  1994/12/07  00:36:26  mike
 * scores sequencing stuff.
 * 
 * Revision 1.101  1994/12/06  15:14:21  yuan
 * Localization
 * 
 * Revision 1.100  1994/12/03  17:07:52  yuan
 * Localization 368
 * 
 * Revision 1.99  1994/12/03  14:49:27  mark
 * Fixed john's bug with previous.
 * 
 * Revision 1.98  1994/12/03  14:43:54  john
 * Added enter, space  to exit scores.
 * 
 * Revision 1.97  1994/12/03  14:32:34  john
 * Added integrated-super-deluxe-ctrl-r to reset high scores.
 * 
 * Revision 1.96  1994/12/01  20:15:20  yuan
 * Localization
 * 
 * Revision 1.95  1994/11/30  19:36:36  john
 * Made Gravis Ultrasound work again.  Made the scores blink
 * at a constant rate.  Revamped the newmenu background storage,
 * which hopefully fixed some bugs.  Made menus in ame not pause
 * sound, except for the pause key.               ^== Game!
 * 
 * Revision 1.94  1994/11/30  12:32:08  john
 * Made secret levels print correctly.
 * 
 * Revision 1.93  1994/11/30  12:06:47  mike
 * fix bug: looper not initialized.
 * 
 * Revision 1.92  1994/11/29  13:20:04  john
 * changed the "Wow! You placed .." to something better.
 * 
 * Revision 1.91  1994/11/29  01:35:38  john
 * Made it so that even if you don't get a high score, you still show
 * up on the chart..
 * 
 * Revision 1.90  1994/11/23  17:29:29  mike
 * fix xx-xx level bug in high scores.
 * 
 * Revision 1.89  1994/11/22  16:55:27  mike
 * allow high scores even in pudly trainee level.
 * 
 * Revision 1.88  1994/11/21  17:28:33  john
 * Changed default score values.
 * 
 * Revision 1.87  1994/11/18  23:37:53  john
 * Changed some shorts to ints.
 * 
 * Revision 1.86  1994/11/13  15:39:24  john
 * Added critical error handler to game.  Took out -editor command line
 * option because it didn't work anymore and wasn't worth fixing.  Made scores
 * not use MINER enviroment variable on release version, and made scores
 * not print an error if there is no descent.hi.
 * 
 * Revision 1.85  1994/11/06  10:15:58  john
 * Took out kill % and hostage %
 * 
 * Revision 1.84  1994/11/05  15:03:39  john
 * Added non-popup menu for the main menu, so that scores and credits don't have to save
 * the background.
 * 
 * Revision 1.83  1994/11/05  14:05:57  john
 * Fixed fade transitions between all screens by making gr_palette_fade_in and out keep
 * track of whether the palette is faded in or not.  Then, wherever the code needs to fade out,
 * it just calls gr_palette_fade_out and it will fade out if it isn't already.  The same with fade_in.
 * This eliminates the need for all the flags like Menu_fade_out, game_fade_in palette, etc.
 * 
 * Revision 1.82  1994/11/04  20:11:41  john
 * Neatening up palette stuff with demos.
 * 
 * Revision 1.81  1994/11/04  12:02:34  john
 * Fixed fading transitions a bit more.
 * 
 * Revision 1.80  1994/10/27  12:10:39  john
 * Moved kill % a little to the right.
 * 
 * Revision 1.79  1994/10/24  20:25:03  john
 * Fixed bug with space at end of 1 line message.
 * Made Enter go between the two input lines.
 * 
 * Revision 1.78  1994/10/24  18:20:18  john
 * Made the current high score flash.
 * 
 * Revision 1.77  1994/10/24  13:37:22  mike
 * Fix grammar error.  --anal Mike.
 * 
 * Revision 1.76  1994/10/22  13:19:19  john
 * Made joy/mouse buttons leave score screen.
 * 
 * Revision 1.75  1994/10/21  15:26:57  john
 * Used PrtScr instead of F2.
 * 
 * Revision 1.74  1994/10/21  13:54:21  matt
 * Replace '1' with special wide '1' to make numbers line up
 * 
 * Revision 1.73  1994/10/19  20:48:01  john
 * Made so that people playing on wimp level
 * can't get high scores.
 * 
 * Revision 1.72  1994/10/19  15:14:05  john
 * Took % hits out of player structure, made %kills work properly.
 * 
 * Revision 1.71  1994/10/19  14:39:27  john
 * Finished up; added keys to prtscr, int3.
 * 
 * Revision 1.70  1994/10/19  12:44:09  john
 * Added hours field to player structure.
 * 
 * Revision 1.69  1994/10/19  11:25:21  john
 * Looking good.
 * 
 * Revision 1.68  1994/10/19  10:54:12  john
 * Test version.
 * 
 * Revision 1.67  1994/10/19  10:00:27  john
 * *** empty log message ***
 * 
 * Revision 1.66  1994/10/19  09:59:03  john
 * Made cool saying have the potential to be up to 50 chars
 * 
 * Revision 1.65  1994/10/19  09:53:30  john
 * Working version of scores.
 * 
 * Revision 1.64  1994/10/18  21:07:46  john
 * Fixed bug that didn't print name correctly.
 * 
 * Revision 1.63  1994/10/18  18:21:46  john
 * NEw score system.
 * 
 * Revision 1.62  1994/10/17  20:31:42  john
 * Made the text for the difficulty labels global so that
 * the high score screen can print "rookie" or whatever.
 * 
 * Revision 1.61  1994/10/17  17:27:44  john
 * Added starting_level to high score system.
 * 
 * Revision 1.60  1994/10/17  16:56:35  john
 * Added starting level to stats menu.
 * 
 * Revision 1.59  1994/10/17  16:55:25  john
 * Added starting level, but didn't hook it to anything.
 * 
 * Revision 1.58  1994/10/17  16:47:17  john
 * Added diff. level.
 * 
 * Revision 1.57  1994/10/17  15:49:53  john
 * Added stats screen.
 * 
 * Revision 1.56  1994/10/03  23:02:29  matt
 * After player added or not to scores, scores are now displayed
 * 
 * Revision 1.55  1994/09/01  18:09:38  john
 * Made commas in scores work correctly .
 * 
 * 
 * Revision 1.54  1994/09/01  18:03:57  john
 * Neatened up scores a bit.
 * 
 * Revision 1.53  1994/08/26  14:27:37  john
 * Made it prompt for name
 * 
 * Revision 1.52  1994/08/26  13:03:17  john
 * *** empty log message ***
 * 
 * Revision 1.51  1994/08/26  13:01:52  john
 * Put high score system in.
 * 
 * Revision 1.50  1994/08/10  19:57:01  john
 * Changed font stuff; Took out old menu; messed up lots of
 * other stuff like game sequencing messages, etc.
 * 
 * Revision 1.49  1994/07/25  15:40:27  matt
 * Took out debugging code accidentally left in.
 * 
 *
 */

#pragma off (unreferenced)
static char rcsid[] = "$Id: scores.c 1.1 1995/12/05 16:06:29 allender Exp allender $";
#pragma on (unreferenced)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
//#include <io.h>
#include <stdarg.h>
//#include <dos.h>
//#include <conio.h>

#include "error.h"
#include "dtypes.h"
#include "gr.h"
#include "mono.h"
#include "key.h"
#include "palette.h"
#include "game.h"
#include "gamefont.h"
#include "mem.h"
#include "newmenu.h"
#include "menu.h"
#include "player.h"
#include "screens.h"
#include "gamefont.h"
#include "mouse.h"
#include "joy.h"
#include "timer.h"
#include "text.h"
#include "byteswap.h"

#define VERSION_NUMBER 		1
#define SCORES_FILENAME 	"DESCENT.HI"
#define COOL_MESSAGE_LEN 	50
#define MAX_HIGH_SCORES 	10

typedef struct stats_info {
	char		name[CALLSIGN_LEN+1];
	int		score;
	byte		starting_level;
	byte		ending_level;
	byte  	diff_level;
	short 	kill_ratio;	// 0-100
	short		hostage_ratio;   // 
	int		seconds;			// How long it took in seconds...
} stats_info;

typedef struct all_scores {
	char			signature[3];			// DHS
	byte			version;					// version
	char			cool_saying[COOL_MESSAGE_LEN];
	stats_info	stats[MAX_HIGH_SCORES];
} all_scores;

static all_scores Scores;

stats_info Last_game;

char scores_filename[128];

#define XX  (14)
#define YY  (-6)

void scores_view(int citem);

char * get_scores_filename()
{
#ifndef RELEASE
	// Only use the MINER variable for internal developement
	char *p;
	p=getenv( "MINER" );
	if (p)	{
		sprintf( scores_filename, "%s\\game\\%s", p, SCORES_FILENAME );
		Assert(strlen(scores_filename) < 128);
		return scores_filename;
	}
#endif
	sprintf( scores_filename, "%s", SCORES_FILENAME );
	return scores_filename;
}


void scores_read()
{
	FILE * fp;
	int fsize, i;

	// clear score array...
	memset( &Scores, 0, sizeof(all_scores) );

	fp = fopen( get_scores_filename(), "rb" );
	if (fp==NULL) {
		int i;

	 	// No error message needed, code will work without a scores file
		sprintf( Scores.cool_saying, TXT_REGISTER_DESCENT );
		sprintf( Scores.stats[0].name, "Parallax" );
		sprintf( Scores.stats[1].name, "Mike" );
		sprintf( Scores.stats[2].name, "Matt" );
		sprintf( Scores.stats[3].name, "John" );
		sprintf( Scores.stats[4].name, "Yuan" );
		sprintf( Scores.stats[5].name, "Adam" );
		sprintf( Scores.stats[6].name, "Mark" );
		sprintf( Scores.stats[7].name, "Allender" );
		sprintf( Scores.stats[8].name, "Jasen" );
		sprintf( Scores.stats[9].name, "Rob" );

		for (i=0; i<10; i++)
			Scores.stats[i].score = (10-i)*1000;
		return;
	}
		
	fsize = filelength( fileno( fp ));

	if ( fsize != 294 )	{
		fclose(fp);
		return;
	}

	// Read 'em in...
	fread( Scores.signature, 3, 1, fp);
	fread( &(Scores.version), 1, 1, fp);
	fread( Scores.cool_saying, COOL_MESSAGE_LEN, 1, fp);
	for (i = 0; i < MAX_HIGH_SCORES; i++) {
		fread( Scores.stats[i].name, CALLSIGN_LEN+1, 1, fp);
		fread( &(Scores.stats[i].score), 4, 1, fp);
		fread( &(Scores.stats[i].starting_level), 1, 1, fp);
		fread( &(Scores.stats[i].ending_level), 1, 1, fp);
		fread( &(Scores.stats[i].diff_level), 1, 1, fp);
		fread( &(Scores.stats[i].kill_ratio), 2, 1, fp);
		fread( &(Scores.stats[i].hostage_ratio), 2, 1, fp);
		fread( &(Scores.stats[i].seconds), 4, 1, fp);
		
		Scores.stats[i].score = swapint(Scores.stats[i].score);
		Scores.stats[i].kill_ratio = swapshort(Scores.stats[i].kill_ratio);
		Scores.stats[i].hostage_ratio = swapshort(Scores.stats[i].hostage_ratio);
		Scores.stats[i].seconds = swapint(Scores.stats[i].seconds);
	}

	fclose(fp);

	if ( (Scores.version!=VERSION_NUMBER)||(Scores.signature[0]!='D')||(Scores.signature[1]!='H')||(Scores.signature[2]!='S') )	{
		memset( &Scores, 0, sizeof(all_scores) );
		return;
	}
}

void scores_write()
{
	FILE * fp;
	int i;

	fp = fopen( get_scores_filename(), "wb" );
	if (fp==NULL) {
		nm_messagebox( TXT_WARNING, 1, TXT_OK, "%s\n'%s'", TXT_UNABLE_TO_OPEN, get_scores_filename()  );
		return;
	}

	Scores.signature[0]='D';
	Scores.signature[1]='H';
	Scores.signature[2]='S';
	Scores.version = VERSION_NUMBER;
	fwrite( Scores.signature, 3, 1, fp);
	fwrite( &(Scores.version), 1, 1, fp);
	fwrite( Scores.cool_saying, COOL_MESSAGE_LEN, 1, fp);
	for (i = 0; i < MAX_HIGH_SCORES; i++) {
		Scores.stats[i].score = swapint(Scores.stats[i].score);
		Scores.stats[i].kill_ratio = swapshort(Scores.stats[i].kill_ratio);
		Scores.stats[i].hostage_ratio = swapshort(Scores.stats[i].hostage_ratio);
		Scores.stats[i].seconds = swapint(Scores.stats[i].seconds);

		fwrite( Scores.stats[i].name, CALLSIGN_LEN+1, 1, fp);
		fwrite( &(Scores.stats[i].score), 4, 1, fp);
		fwrite( &(Scores.stats[i].starting_level), 1, 1, fp);
		fwrite( &(Scores.stats[i].ending_level), 1, 1, fp);
		fwrite( &(Scores.stats[i].diff_level), 1, 1, fp);
		fwrite( &(Scores.stats[i].kill_ratio), 2, 1, fp);
		fwrite( &(Scores.stats[i].hostage_ratio), 2, 1, fp);
		fwrite( &(Scores.stats[i].seconds), 4, 1, fp);

		Scores.stats[i].score = swapint(Scores.stats[i].score);
		Scores.stats[i].kill_ratio = swapshort(Scores.stats[i].kill_ratio);
		Scores.stats[i].hostage_ratio = swapshort(Scores.stats[i].hostage_ratio);
		Scores.stats[i].seconds = swapint(Scores.stats[i].seconds);

	}
	fclose(fp);
}

void int_to_string( int number, char *dest )
{
	int i,l,c;
	char buffer[20],*p;

	sprintf( buffer, "%d", number );

	l = strlen(buffer);
	if (l<=3) {
		// Don't bother with less than 3 digits
		sprintf( dest, "%d", number );
		return;
	}

	c = 0;
	p=dest;
	for (i=l-1; i>=0; i-- )	{
		if (c==3) {
			*p++=',';
			c = 0;
		}
		c++;
		*p++ = buffer[i];
	}
	*p++ = '\0';
	strrev(dest);
}

void scores_fill_struct(stats_info * stats)
{
	strcpy( stats->name, Players[Player_num].callsign );
	stats->score = Players[Player_num].score;
	stats->ending_level = Players[Player_num].level;
	if (Players[Player_num].num_robots_total > 0 )	
		stats->kill_ratio = (Players[Player_num].num_kills_total*100)/Players[Player_num].num_robots_total;
	else
		stats->kill_ratio = 0;

	if (Players[Player_num].hostages_total > 0 )	
		stats->hostage_ratio = (Players[Player_num].hostages_rescued_total*100)/Players[Player_num].hostages_total;
	else
		stats->hostage_ratio = 0;

	stats->seconds = f2i(Players[Player_num].time_total)+(Players[Player_num].hours_total*3600);

	stats->diff_level = Difficulty_level;
	stats->starting_level = Players[Player_num].starting_level;
}

//char * score_placement[10] = { TXT_1ST, TXT_2ND, TXT_3RD, TXT_4TH, TXT_5TH, TXT_6TH, TXT_7TH, TXT_8TH, TXT_9TH, TXT_10TH };

void scores_maybe_add_player(int abort_flag)
{
	char text1[COOL_MESSAGE_LEN+10];
	newmenu_item m[10];
	int i,position;

	#ifdef APPLE_OEM		// no high scores in apple oem version
	return;
	#endif
	
	scores_read();
	
	position = MAX_HIGH_SCORES;
	for (i=0; i<MAX_HIGH_SCORES; i++ )	{
		if ( Players[Player_num].score > Scores.stats[i].score )	{
			position = i;
			break;
		}
	}
	
	if ( position == MAX_HIGH_SCORES ) {
		if (abort_flag)
			return;
		scores_fill_struct( &Last_game );
	} else {
//--		if ( Difficulty_level < 1 )	{
//--			nm_messagebox( "GRADUATION TIME!", 1, "Ok", "If you would had been\nplaying at a higher difficulty\nlevel, you would have placed\n#%d on the high score list.", position+1 );
//--			return;
//--		}

		if ( position==0 )	{
			strcpy( text1,  "" );
			m[0].type = NM_TYPE_TEXT; m[0].text = TXT_COOL_SAYING;
			m[1].type = NM_TYPE_INPUT; m[1].text = text1; m[1].text_len = COOL_MESSAGE_LEN-5;
			newmenu_do( TXT_HIGH_SCORE, TXT_YOU_PLACED_1ST, 2, m, NULL );
			strncpy( Scores.cool_saying, text1, COOL_MESSAGE_LEN );
			if (strlen(Scores.cool_saying)<1)
				sprintf( Scores.cool_saying, "No Comment" );
		} else {
			nm_messagebox( TXT_HIGH_SCORE, 1, TXT_OK, "%s %s!", TXT_YOU_PLACED, *(&TXT_1ST + position) );
		}
	
		// move everyone down...
		for ( i=MAX_HIGH_SCORES-1; i>position; i-- )	{
			Scores.stats[i] = Scores.stats[i-1];
		}

		scores_fill_struct( &Scores.stats[position] );
	
		scores_write();

	}
	scores_view(position);
}

#define TEXT_FONT  		(Gamefonts[GFONT_MEDIUM_3])

void scores_rprintf(int x, int y, char * format, ... )
{
	va_list args;
	char buffer[128];
	int w, h, aw;
	char *p;

	va_start(args, format );
	vsprintf(buffer,format,args);
	va_end(args);

	//replace the digit '1' with special wider 1
	for (p=buffer;*p;p++)
		if (*p=='1') *p=132;

	gr_get_string_size(buffer, &w, &h, &aw );

	gr_string( x-w, y, buffer );
}


void scores_draw_item( int  i, stats_info * stats )
{
	char buffer[20];
	int y;

	y = 14+140+i*18;

	if (i==0) y -= 16;

	if ( i==MAX_HIGH_SCORES ) 	{
		y += 16;
		//scores_rprintf( 17+33+XX, y+YY, "" );
	} else {
		scores_rprintf( 34+66+XX, y+YY, "%d.", i+1 );
	}

	if (strlen(stats->name)==0) {
		gr_printf( 52+66+XX, y+YY, TXT_EMPTY );
		return;
	}
	gr_printf( 52+66+XX, y+YY, "%s", stats->name );
	int_to_string(stats->score, buffer);
	scores_rprintf( 218+66+XX, y+YY, "%s", buffer );

	gr_printf( 250+66+XX, y+YY, "%s", MENU_DIFFICULTY_TEXT(stats->diff_level) );

	if ( (stats->starting_level > 0 ) && (stats->ending_level > 0 ))
		scores_rprintf( 382+66+XX, y+YY, "%d-%d", stats->starting_level, stats->ending_level );
	else if ( (stats->starting_level < 0 ) && (stats->ending_level > 0 ))
		scores_rprintf( 382+66+XX, y+YY, "S%d-%d", -stats->starting_level, stats->ending_level );
	else if ( (stats->starting_level < 0 ) && (stats->ending_level < 0 ))
		scores_rprintf( 382+66+XX, y+YY, "S%d-S%d", -stats->starting_level, -stats->ending_level );
	else if ( (stats->starting_level > 0 ) && (stats->ending_level < 0 ))
		scores_rprintf( 382+66+XX, y+YY, "%d-S%d", stats->starting_level, -stats->ending_level );

	{
		int h, m, s;
		h = stats->seconds/3600;
		s = stats->seconds%3600;
		m = s / 60;
		s = s % 60;
		scores_rprintf( 622-84+XX, y+YY, "%d:%02d:%02d", h, m, s );
	}
}

void scores_view(int citem)
{
	fix t1;
	int i,done,looper;
	int k;
	byte fades[64] = { 1,1,1,2,2,3,4,4,5,6,8,9,10,12,13,15,16,17,19,20,22,23,24,26,27,28,28,29,30,30,31,31,31,31,31,30,30,29,28,28,27,26,24,23,22,20,19,17,16,15,13,12,10,9,8,6,5,4,4,3,2,2,1,1 };

ReshowScores:
	scores_read();

	set_screen_mode(SCREEN_MENU);
	
	gr_set_current_canvas(NULL);
	
	nm_draw_background(0,0,grd_curcanv->cv_bitmap.bm_w, grd_curcanv->cv_bitmap.bm_h );

	grd_curcanv->cv_font = Gamefonts[GFONT_MEDIUM_3];

	gr_string( 0x8000, 30, TXT_HIGH_SCORES );

	grd_curcanv->cv_font = Gamefonts[GFONT_SMALL];

	gr_set_fontcolor( BM_XRGB(31,26,5), -1 );
	gr_string(  62+66+XX, 92+14+YY, TXT_NAME );
	gr_string( 164+66+XX, 92+14+YY, TXT_SCORE );
	gr_string( 254+66+XX, 92+14+YY, TXT_SKILL );
	gr_string( 340+66+XX, 92+14+YY, TXT_LEVELS );
//	gr_string( 202, 46, "Kills" );
//	gr_string( 234, 46, "Rescues" );
	gr_string( 576-84+XX, 92+14+YY, TXT_TIME );

	if ( citem < 0 )	
		gr_string( 0x8000, 350, TXT_PRESS_CTRL_R );

	gr_set_fontcolor( BM_XRGB(28,28,28), -1 );

	gr_printf( 0x8000, 62, "%c%s%c  - %s", 34, Scores.cool_saying, 34, Scores.stats[0].name );
	
	for (i=0; i<MAX_HIGH_SCORES; i++ )		{
		if (i==0)	{
			gr_set_fontcolor( BM_XRGB(28,28,28), -1 );
		} else {
			gr_set_fontcolor( gr_fade_table[BM_XRGB(28,28,28)+((28-i*2)*256)], -1 );
		}														 
		scores_draw_item( i, &Scores.stats[i] );
	}

	gr_palette_fade_in( gr_palette,32, 0);

	game_flush_inputs();

	done = 0;
	looper = 0;

	while(!done)	{
		if ( citem > -1 )	{
	
			t1	= timer_get_fixed_seconds();
			while ( timer_get_fixed_seconds() < t1+F1_0/128 );	

			gr_set_fontcolor( gr_fade_table[fades[looper]*256+BM_XRGB(28,28,28)], -1 );
			looper++;
			if (looper>63) looper=0;
			if ( citem ==  MAX_HIGH_SCORES )
				scores_draw_item( MAX_HIGH_SCORES, &Last_game );
			else
				scores_draw_item( citem, &Scores.stats[citem] );
		}

//		for (i=0; i<4; i++ )	
//			if (joy_get_button_down_cnt(i)>0) done=1;
		for (i=0; i<3; i++ )	
			if (mouse_button_down_count(i)>0) done=1;

		k = key_inkey();
		switch( k )	{
		case KEY_CTRLED+KEY_R:		
			if ( citem < 0 )		{
				// Reset scores...
				if ( nm_messagebox( NULL, 2,  TXT_NO, TXT_YES, TXT_RESET_HIGH_SCORES )==1 )	{
					remove( get_scores_filename() );
					gr_palette_fade_out( gr_palette, 32, 0 );
					goto ReshowScores;
				}
			}
			break;
		case KEY_BACKSP:				Int3(); k = 0; break;
		case KEY_PRINT_SCREEN:		save_screen_shot(0); k = 0; break;
			
		case KEY_ENTER:
		case KEY_SPACEBAR:
		case KEY_ESC:
			done=1;
			break;
		}
	}

// Restore background and exit
	gr_palette_fade_out( gr_palette, 32, 0 );
	gr_set_current_canvas(NULL);

	game_flush_inputs();
	
}

