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
 * $Source: Smoke:miner:source:main::RCS:TITLES.H $
 * $Revision: 1.1 $
 * $Author: allender $
 * $Date: 1995/05/16 16:04:28 $
 * 
 * .
 * 
 * $Log: TITLES.H $
 * Revision 1.1  1995/05/16  16:04:28  allender
 * Initial revision
 *
 * Revision 2.0  1995/02/27  11:27:40  john
 * New version 2.0, which has no anonymous unions, builds with
 * Watcom 10.0, and doesn't require parsing BITMAPS.TBL.
 * 
 * Revision 1.12  1995/02/02  12:23:29  john
 * Made between level saves have picture.
 * 
 * Revision 1.11  1995/01/21  16:27:11  matt
 * Made endlevel briefing work with missions
 * 
 * Revision 1.10  1995/01/20  22:48:02  matt
 * Mission system implemented, though imcompletely
 * 
 * Revision 1.9  1994/12/07  19:14:07  matt
 * Kill briefing screen disable switch for release version
 * 
 * Revision 1.8  1994/11/21  16:40:24  matt
 * Added prototype
 * 
 * Revision 1.7  1994/11/05  14:05:54  john
 * Fixed fade transitions between all screens by making gr_palette_fade_in and out keep
 * track of whether the palette is faded in or not.  Then, wherever the code needs to fade out,
 * it just calls gr_palette_fade_out and it will fade out if it isn't already.  The same with fade_in.
 * This eliminates the need for all the flags like Menu_fade_out, game_fade_in palette, etc.
 * 
 * Revision 1.6  1994/11/01  17:57:48  mike
 * Briefing screens.
 * 
 * Revision 1.5  1994/10/31  22:28:04  mike
 * briefing screens
 * 
 * Revision 1.4  1994/09/16  16:14:31  john
 * Added acrade sequencing.
 * 
 * Revision 1.3  1994/06/22  00:26:53  matt
 * Added support for Interplay's animating title sequence
 * 
 * Revision 1.2  1994/06/17  12:13:36  john
 * More newdemo stuff; made editor->game transition start in slew mode.
 * 
 * Revision 1.1  1994/06/17  10:50:12  john
 * Initial revision
 * 
 * 
 */



#ifndef _TITLES_H
#define _TITLES_H

#ifndef RELEASE
extern int	Skip_briefing_screens;
#else
#define Skip_briefing_screens 0
#endif

extern char Briefing_text_filename[13];
extern char Ending_text_filename[13];

extern int show_title_screen( char * filename, int allow_keys );
extern int show_briefing_screen( char * filename, int allow_keys );
extern show_title_flick(char *name, int allow_keys );
extern void do_briefing_screens(int level_num);
extern void do_end_game(void);
extern char * get_briefing_screen( int level_num );


#endif
