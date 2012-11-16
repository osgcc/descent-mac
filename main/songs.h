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
 * $Source: Smoke:miner:source:main::RCS:songs.h $
 * $Revision: 1.5 $
 * $Author: allender $
 * $Date: 1995/11/03 12:52:43 $
 * 
 * .
 * 
 * $Log: songs.h $
 * Revision 1.5  1995/11/03  12:52:43  allender
 * shareware changes
 * shareware changes
 *
 * Revision 1.4  1995/10/18  01:51:45  allender
 * redbook fixes
 *
 * Revision 1.3  1995/10/17  13:14:14  allender
 * fixed track numbers for redbook
 *
 * Revision 1.2  1995/07/17  08:50:45  allender
 * changed some constants around
 *
 * Revision 1.1  1995/05/16  16:03:17  allender
 * Initial revision
 *
 * Revision 2.0  1995/02/27  11:30:52  john
 * New version 2.0, which has no anonymous unions, builds with
 * Watcom 10.0, and doesn't require parsing BITMAPS.TBL.
 * 
 * Revision 1.6  1995/02/11  22:21:44  adam
 * *** empty log message ***
 * 
 * Revision 1.5  1995/02/11  19:10:49  adam
 * *** empty log message ***
 * 
 * Revision 1.4  1995/02/11  18:34:40  adam
 * *** empty log message ***
 * 
 * Revision 1.3  1995/02/11  18:04:51  adam
 * upped songs
 * 
 * Revision 1.2  1995/02/11  12:42:12  john
 * Added new song method, with FM bank switching..
 * 
 * Revision 1.1  1995/02/11  10:20:18  john
 * Initial revision
 * 
 * 
 */

#ifndef _SONGS_H
#define _SONGS_H

#ifdef MAC_SHAREWARE

#define SONG_TITLE			1000
#define SONG_BRIEFING		1001
#define SONG_ENDLEVEL		-1
#define SONG_ENDGAME		1002
#define SONG_CREDITS		1003
#define SONG_LEVEL_MUSIC	1004
#define NUM_GAME_SONGS 		3

#else

#define SONG_TITLE			2
#define SONG_BRIEFING		3
#define SONG_ENDLEVEL		4
#define SONG_ENDGAME		3
#define SONG_CREDITS		5
#define SONG_LEVEL_MUSIC	6
#define NUM_GAME_SONGS		8

#endif

extern ubyte shuffle_levels;

void songs_play_song( int songnum, int repeat );
void songs_play_level_song( int levelnum );

#endif
