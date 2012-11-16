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
 * $Source: Smoke:miner:source:main::RCS:songs.c $
 * $Revision: 1.5 $
 * $Author: allender $
 * $Date: 1995/11/03 12:52:59 $
 * 
 * Routines to manage the songs in Descent.
 * 
 * $Log: songs.c $
 * Revision 1.5  1995/11/03  12:52:59  allender
 * shareware changes
 *
 * Revision 1.4  1995/10/18  01:51:33  allender
 * fixed up stuff for redbook
 *
 * Revision 1.3  1995/10/17  13:13:44  allender
 * dont' add resource value to songs to play -- now done in digi
 * code
 *
 * Revision 1.2  1995/07/17  08:50:35  allender
 * make work with new music system
 *
 * Revision 1.1  1995/05/16  15:31:05  allender
 * Initial revision
 *
 * Revision 2.0  1995/02/27  11:27:13  john
 * New version 2.0, which has no anonymous unions, builds with
 * Watcom 10.0, and doesn't require parsing BITMAPS.TBL.
 * 
 * Revision 1.2  1995/02/11  12:42:12  john
 * Added new song method, with FM bank switching..
 * 
 * Revision 1.1  1995/02/11  10:20:33  john
 * Initial revision
 * 
 * 
 */


#pragma off (unreferenced)
static char rcsid[] = "$Id: songs.c 1.5 1995/11/03 12:52:59 allender Exp $";
#pragma on (unreferenced)

#include <stdlib.h>
#include <string.h>

#include "error.h"
#include "dtypes.h"
#include "songs.h"
#include "mono.h"
#include "cfile.h"
#include "digi.h"

ubyte shuffle_levels = 0;

void songs_play_song( int songnum, int repeat )
{
	digi_play_midi_song( songnum, repeat );
}

void songs_play_level_song( int levelnum )
{
	int songnum;

	Assert( levelnum != 0 );

#ifdef MAC_SHAREWARE
	songnum = levelnum-1;
#else
	if (!shuffle_levels) {
		if (levelnum < 0)	
			songnum = (-levelnum) % NUM_GAME_SONGS;
		else 
			songnum = (levelnum-1) % NUM_GAME_SONGS;
	} else 
		songnum = rand() % NUM_GAME_SONGS;
#endif


	songnum += SONG_LEVEL_MUSIC;
	digi_play_midi_song( songnum, 1 );
}
