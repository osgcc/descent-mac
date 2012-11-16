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
 * $Source: Smoke:miner:source:main::RCS:piggy.c $
 * $Revision: 1.16 $
 * $Author: allender $
 * $Date: 1995/11/09 17:27:47 $
 * 
 * Functions for managing the pig files.
 * 
 * $Log: piggy.c $
 * Revision 1.16  1995/11/09  17:27:47  allender
 * put in missing quote on new gauge name
 *
 * Revision 1.15  1995/11/08  17:28:03  allender
 * add PC gauges to gauge list of non-substitutatble bitmaps
 *
 * Revision 1.14  1995/11/08  15:14:49  allender
 * fixed horrible bug where the piggy cache size was incorrect
 * for mac shareware
 *
 * Revision 1.13  1995/11/03  12:53:37  allender
 * shareware changes
 *
 * Revision 1.12  1995/10/21  22:25:14  allender
 * added bald guy cheat
 *
 * Revision 1.11  1995/10/20  22:42:15  allender
 * changed load path of descent.pig to :data:descent.pig
 *
 * Revision 1.10  1995/10/20  00:08:01  allender
 * put in event loop calls when loading data (hides it nicely
 * from user) so TM can get it's strokes stuff
 *
 * Revision 1.9  1995/09/13  08:48:01  allender
 * added lower memory requirement to load alternate bitmaps
 *
 * Revision 1.8  1995/08/16  09:39:13  allender
 * moved "loading" text up a little
 *
 * Revision 1.7  1995/08/08  13:54:26  allender
 * added macsys header file
 *
 * Revision 1.6  1995/07/12  12:49:56  allender
 * total hack for bitmaps > 512 bytes wide -- check these by name
 *
 * Revision 1.5  1995/07/05  16:47:05  allender
 * kitchen stuff
 *
 * Revision 1.4  1995/06/23  08:55:28  allender
 * make "loading data" text y loc based off of curcanv
 *
 * Revision 1.3  1995/06/08  14:08:52  allender
 * PPC aligned data sets
 *
 * Revision 1.2  1995/05/26  06:54:27  allender
 * removed refences to sound data at end of pig file (since they will
 * now be Macintosh snd resources for effects
 *
 * Revision 1.1  1995/05/16  15:29:51  allender
 * Initial revision
 *
 * Revision 2.9  1995/04/14  14:05:24  john
 * *** empty log message ***
 * 
 * Revision 2.8  1995/04/12  13:39:37  john
 * Fixed bug with -lowmem not working.
 * 
 * Revision 2.7  1995/03/29  23:23:17  john
 * Fixed major bug with sounds not building into pig right.
 * 
 * Revision 2.6  1995/03/28  18:05:00  john
 * Fixed it so you don't have to delete pig after changing bitmaps.tbl
 * 
 * Revision 2.5  1995/03/16  23:13:06  john
 * Fixed bug with piggy paging in bitmap not checking for disk
 * error, hence bogifying textures if you pull the CD out.
 * 
 * Revision 2.4  1995/03/14  16:22:27  john
 * Added cdrom alternate directory stuff.
 * 
 * Revision 2.3  1995/03/06  15:23:20  john
 * New screen techniques.
 * 
 * Revision 2.2  1995/02/27  13:13:40  john
 * Removed floating point.
 * 
 * Revision 2.1  1995/02/27  12:31:25  john
 * Made work without editor.
 * 
 * Revision 2.0  1995/02/27  11:28:02  john
 * New version 2.0, which has no anonymous unions, builds with
 * Watcom 10.0, and doesn't require parsing BITMAPS.TBL.
 * 
 * Revision 1.85  1995/02/09  12:54:24  john
 * Made paged out bitmaps have bm_data be a valid pointer
 * instead of NULL, in case anyone accesses it.
 * 
 * Revision 1.84  1995/02/09  12:50:59  john
 * Bullet-proofed the piggy loading code.
 * 
 * Revision 1.83  1995/02/07  17:08:51  john
 * Added some error handling stuff instead of asserts.
 * 
 * Revision 1.82  1995/02/03  17:06:48  john
 * Changed sound stuff to allow low memory usage.
 * Also, changed so that Sounds isn't an array of digi_sounds, it
 * is a ubyte pointing into GameSounds, this way the digi.c code that
 * locks sounds won't accidentally unlock a sound that is already playing, but
 * since it's Sounds[soundno] is different, it would erroneously be unlocked.
 * 
 * Revision 1.81  1995/02/02  21:56:39  matt
 * Added data for new gauge bitmaps
 * 
 * Revision 1.80  1995/02/01  23:31:57  john
 * Took out loading bar.
 * 
 * Revision 1.79  1995/01/28  15:13:18  allender
 * bumped up Piggy_bitmap_cache_size
 * 
 * Revision 1.78  1995/01/26  12:30:43  john
 * Took out prev.
 * 
 * Revision 1.77  1995/01/26  12:12:17  john
 * Made buffer be big for bitmaps.
 * 
 * Revision 1.76  1995/01/25  20:15:38  john
 * Made editor allocate all mem.
 * 
 * Revision 1.75  1995/01/25  14:52:56  john
 * Made bitmap buffer be 1.5 MB.
 * 
 * Revision 1.74  1995/01/22  16:03:19  mike
 * localization.
 * 
 * Revision 1.73  1995/01/22  15:58:36  mike
 * localization
 * 
 * Revision 1.72  1995/01/18  20:51:20  john
 * Took out warnings.
 * 
 * Revision 1.71  1995/01/18  20:47:21  john
 * Added code to allocate sounds & bitmaps into diff
 * buffers, also made sounds not be compressed for registered.
 * 
 * Revision 1.70  1995/01/18  15:08:41  john
 * Added start/stop time around paging.
 * Made paging clear screen around globe.
 * 
 * Revision 1.69  1995/01/18  10:07:51  john
 * 
 * Took out debugging mprintfs.
 * 
 * Revision 1.68  1995/01/17  14:27:42  john
 * y
 * 
 * Revision 1.67  1995/01/17  12:14:39  john
 * Made walls, object explosion vclips load at level start.
 * 
 * Revision 1.66  1995/01/15  13:15:44  john
 * Made so that paging always happens, lowmem just loads less.
 * Also, make KB load print to hud.
 * 
 * Revision 1.65  1995/01/15  11:56:28  john
 * Working version of paging.
 * 
 * Revision 1.64  1995/01/14  19:17:07  john
 * First version of new bitmap paging code.
 * 
 * Revision 1.63  1994/12/15  12:26:44  john
 * Added -nolowmem function.
 * 
 * Revision 1.62  1994/12/14  21:12:26  john
 * Fixed bug with page fault when exiting and using
 * -nosound.
 * 
 * Revision 1.61  1994/12/14  11:35:31  john
 * Evened out thermometer for pig read.
 * 
 * Revision 1.60  1994/12/14  10:51:00  john
 * Sped up sound loading.
 * 
 * Revision 1.59  1994/12/14  10:12:08  john
 * Sped up pig loading.
 * 
 * Revision 1.58  1994/12/13  09:14:47  john
 * *** empty log message ***
 * 
 * Revision 1.57  1994/12/13  09:12:57  john
 * Made the bar always fill up.
 * 
 * Revision 1.56  1994/12/13  03:49:08  john
 * Made -lowmem not load the unnecessary bitmaps.
 * 
 * Revision 1.55  1994/12/06  16:06:35  john
 * Took out piggy sorting.
 * 
 * Revision 1.54  1994/12/06  15:11:14  john
 * Fixed bug with reading pigs.
 * 
 * Revision 1.53  1994/12/06  14:14:47  john
 * Added code to set low mem based on memory.
 * 
 * Revision 1.52  1994/12/06  14:01:10  john
 * Fixed bug that was causing -lowmem all the time..
 * 
 * Revision 1.51  1994/12/06  13:33:48  john
 * Added lowmem option.
 * 
 * Revision 1.50  1994/12/05  19:40:10  john
 * If -nosound or no sound card selected, don't load sounds from pig.
 * 
 * Revision 1.49  1994/12/05  12:17:44  john
 * Added code that locks/unlocks digital sounds on demand.
 * 
 * Revision 1.48  1994/12/05  11:39:03  matt
 * Fixed little mistake
 * 
 * Revision 1.47  1994/12/05  09:29:22  john
 * Added clength to the sound field.
 * 
 * Revision 1.46  1994/12/04  15:27:15  john
 * Fixed my stupid bug that looked at -nosound instead of digi_driver_card
 * to see whether or not to lock down sound memory.
 * 
 * Revision 1.45  1994/12/03  14:17:00  john
 * Took out my debug mprintf.
 * 
 * Revision 1.44  1994/12/03  13:32:37  john
 * Fixed bug with offscreen bitmap.
 * 
 * Revision 1.43  1994/12/03  13:07:13  john
 * Made the pig read/write compressed sounds.
 * 
 * Revision 1.42  1994/12/03  11:48:51  matt
 * Added option to not dump sounds to pigfile
 * 
 * Revision 1.41  1994/12/02  20:02:20  matt
 * Made sound files constant match constant for table
 * 
 * Revision 1.40  1994/11/29  11:03:09  adam
 * upped # of sounds
 * 
 * Revision 1.39  1994/11/27  23:13:51  matt
 * Made changes for new mprintf calling convention
 * 
 * Revision 1.38  1994/11/20  18:40:34  john
 * MAde the piggy.lst and piggy.all not dump for release.
 * 
 * Revision 1.37  1994/11/19  23:54:45  mike
 * up number of bitmaps for shareware version.
 * 
 * Revision 1.36  1994/11/19  19:53:05  mike
 * change MAX_BITMAP_FILES
 * 
 * Revision 1.35  1994/11/19  10:42:56  matt
 * Increased number of bitmaps for non-shareware version
 * 
 * Revision 1.34  1994/11/19  09:11:52  john
 * Added avg_color to bitmaps saved in pig.
 * 
 * Revision 1.33  1994/11/19  00:07:05  john
 * Fixed bug with 8 char sound filenames not getting read from pig.
 * 
 * Revision 1.32  1994/11/18  22:24:54  john
 * Added -bigpig command line that doesn't rle your pig.
 * 
 * Revision 1.31  1994/11/18  21:56:53  john
 * Added a better, leaner pig format.
 * 
 * Revision 1.30  1994/11/16  12:06:16  john
 * Fixed bug with calling .bbms abms.
 * 
 * Revision 1.29  1994/11/16  12:00:56  john
 * Added piggy.all dump.
 * 
 * Revision 1.28  1994/11/10  21:16:02  adam
 * nothing important
 * 
 * Revision 1.27  1994/11/10  13:42:00  john
 * Made sounds not lock down if using -nosound.
 * 
 * Revision 1.26  1994/11/09  19:55:40  john
 * Added full rle support with texture rle caching.
 * 
 * Revision 1.25  1994/11/09  16:36:42  john
 * First version with RLE bitmaps in Pig.
 * 
 * Revision 1.24  1994/10/27  19:42:59  john
 * Disable the piglet option.
 * 
 * Revision 1.23  1994/10/27  18:51:40  john
 * Added -piglet option that only loads needed textures for a 
 * mine.  Only saved ~1MB, and code still doesn't free textures
 * before you load a new mine.
 * 
 * Revision 1.22  1994/10/25  13:11:42  john
 * Made the sounds sort. Dumped piggy.lst.
 * 
 * Revision 1.21  1994/10/06  17:06:23  john
 * Took out rle stuff.
 * 
 * Revision 1.20  1994/10/06  15:45:36  adam
 * bumped MAX_BITMAP_FILES again!
 * 
 * Revision 1.19  1994/10/06  11:01:17  yuan
 * Upped MAX_BITMAP_FILES
 * 
 * Revision 1.18  1994/10/06  10:44:45  john
 * Added diagnostic message and psuedo run-length-encoder
 * to see how much memory we would save by storing bitmaps
 * in a RLE method.  Also, I commented out the code that
 * stores 4K bitmaps on a 4K boundry to reduce pig size 
 * a bit.
 * 
 * Revision 1.17  1994/10/04  20:03:13  matt
 * Upped maximum number of bitmaps
 * 
 * Revision 1.16  1994/10/03  18:04:20  john
 * Fixed bug with data_offset not set right for bitmaps
 * that are 64x64 and not aligned on a 4k boundry.
 * 
 * Revision 1.15  1994/09/28  11:30:55  john
 * changed inferno.pig to descent.pig, changed the way it
 * is read.
 * 
 * Revision 1.14  1994/09/22  16:14:17  john
 * Redid intro sequecing.
 * 
 * Revision 1.13  1994/09/19  14:42:47  john
 * Locked down sounds with Virtual memory.
 * 
 * Revision 1.12  1994/09/10  17:31:52  mike
 * Increase number of loadable bitmaps.
 * 
 * Revision 1.11  1994/09/01  19:32:49  mike
 * Boost texture map allocation.
 * 
 * Revision 1.10  1994/08/16  11:51:02  john
 * Added grwased pigs.
 * 
 * Revision 1.9  1994/07/06  09:18:03  adam
 * upped bitmap #s
 * 
 * Revision 1.8  1994/06/20  22:02:15  matt
 * Fixed bug from last change
 * 
 * Revision 1.7  1994/06/20  21:33:18  matt
 * Made bm.h not include sounds.h, to reduce dependencies
 * 
 * Revision 1.6  1994/06/20  16:52:19  john
 * cleaned up init output a bit.
 * 
 * Revision 1.5  1994/06/08  14:20:57  john
 * Made piggy dump before going into game.
 * 
 * Revision 1.4  1994/06/02  18:59:22  matt
 * Clear selector field of bitmap loaded from pig file
 * 
 * Revision 1.3  1994/05/06  15:31:41  john
 * Made name field a bit longer.
 * 
 * Revision 1.2  1994/05/06  13:02:44  john
 * Added piggy stuff; worked on supertransparency
 * 
 * Revision 1.1  1994/05/06  11:47:26  john
 * Initial revision
 * 
 * 
 */


#pragma off (unreferenced)
static char rcsid[] = "$Id: piggy.c 1.16 1995/11/09 17:27:47 allender Exp $";
#pragma on (unreferenced)

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <TextUtils.h>

#include "dtypes.h"
#include "inferno.h"
#include "gr.h"
#include "mem.h"
#include "mono.h"
#include "error.h"
#include "sounds.h"
#include "bm.h"
#include "hash.h"
#include "args.h"
#include "palette.h"
#include "gamefont.h"
#include "rle.h"
#include "screens.h"
#include "piggy.h"
#include "texmerge.h"
#include "paging.h"
#include "game.h"
#include "text.h"
#include "cfile.h"
#include "newmenu.h"
#include "fileutil.h"

#include "key.h"
#include "macsys.h"

//#define NO_DUMP_SOUNDS	1		//if set, dump bitmaps but not sounds

ubyte *BitmapBits = NULL;
ubyte *SoundBits = NULL;

typedef struct BitmapFile	{
	char			name[15];
} BitmapFile;

typedef struct SoundFile	{
	char			name[15];
} SoundFile;

hashtable AllBitmapsNames;
hashtable AllDigiSndNames;

int Num_bitmap_files = 0;
int Num_sound_files = 0;

//digi_sound GameSounds[MAX_SOUND_FILES];
//int SoundOffset[MAX_SOUND_FILES];
grs_bitmap *GameBitmaps = NULL;

int Num_bitmap_files_new = 0;
int Num_sound_files_new = 0;
static BitmapFile *AllBitmaps = NULL;
//static SoundFile *AllSounds = NULL;

int piggy_low_memory = 0;

#define DBM_FLAG_LARGE 	128		// Flags added onto the flags struct in b
#define DBM_FLAG_ABM		64
#define RLE_CODE 			0xE0
#define NOT_RLE_CODE		31

char new_baldguy_pcx[] = "btexture.xxx";
int Piggy_bitmap_cache_size = 0;
int Piggy_bitmap_cache_next = 0;
ubyte * Piggy_bitmap_cache_data = NULL;
static int GameBitmapOffset[MAX_BITMAP_FILES];
static ubyte GameBitmapFlags[MAX_BITMAP_FILES];
static ushort GameBitmapXlat[MAX_BITMAP_FILES];
#ifndef MAC_SHAREWARE
static ubyte bald_guy_cheat_index = 0;
#endif

#ifdef MAC_SHAREWARE
#define PIGGY_BUFFER_SIZE		(1536*1024)
#define LOW_PIGGY_BUFFER_SIZE	(1280*1024)
#else
#define PIGGY_BUFFER_SIZE		(2048*1024)
#define LOW_PIGGY_BUFFER_SIZE	(1536*1024)
#endif

int piggy_page_flushed = 0;

#pragma align_array_members on
typedef struct DiskBitmapHeader {
	char name[8];
	ubyte dflags;
	ubyte	width;	
	ubyte height;
	ubyte flags;
	ubyte avg_color;
	int offset;
} DiskBitmapHeader;

typedef struct DiskSoundHeader {
	char name[8];
	int length;
	int data_length;
	int offset;
} DiskSoundHeader;

#pragma align_array_members reset

ubyte BigPig = 0;


//#define BUILD_PSX_DATA 1

#ifdef BUILD_PSX_DATA
FILE * count_file = NULL;

int num_good=0,num_bad=0;
int num_good64=0,num_bad64=0;

void close_count_file()
{
 	if ( count_file )	{
		fprintf( count_file,"Good = %d\n", num_good );
		fprintf( count_file,"Bad = %d\n", num_bad );
		fprintf( count_file,"64Good = %d\n", num_good64 );
		fprintf( count_file,"64Bad = %d\n", num_bad64 );
		fclose(count_file);
		count_file=NULL;
	}
}

void count_colors( int bnum, grs_bitmap * bmp )
{
	int i,colors;
	ushort n[256];

	varquant( bnum, bmp );

	if ( count_file == NULL )	{
		atexit( close_count_file );
		count_file = fopen( "bitmap.cnt", "wt" );
	}
	for (i=0; i<256; i++ )
		n[i] = 0;

	for (i=0; i<bmp->bm_w*bmp->bm_h; i++ )	{
		n[bmp->bm_data[i]]++;
	}

	colors = 0;
	for (i=0; i<256; i++ )
		if (n[i]) colors++;

	if ( colors > 16 )	{
		if ( (bmp->bm_w==64) && (bmp->bm_h==64) ) num_bad64++;
		num_bad++;
		fprintf( count_file, "Bmp has %d colors (%d x %d)\n", colors, bmp->bm_w, bmp->bm_h );
	} else {
		if ( (bmp->bm_w==64) && (bmp->bm_h==64) ) num_good64++;
		num_good++;
	}
}
#endif

bitmap_index piggy_register_bitmap( grs_bitmap * bmp, char * name, int in_file )
{
	bitmap_index temp;
	Assert( Num_bitmap_files < MAX_BITMAP_FILES );

	temp.index = Num_bitmap_files;


	if (!in_file)	{
		if ( !BigPig )	gr_bitmap_rle_compress( bmp );
		Num_bitmap_files_new++;
	}

	strncpy( AllBitmaps[Num_bitmap_files].name, name, 12 );
	hashtable_insert( &AllBitmapsNames, AllBitmaps[Num_bitmap_files].name, Num_bitmap_files );
	GameBitmaps[Num_bitmap_files] = *bmp;
	if ( !in_file )	{
		GameBitmapOffset[Num_bitmap_files] = 0;
		GameBitmapFlags[Num_bitmap_files] = bmp->bm_flags;
	}
	Num_bitmap_files++;

	return temp;
}

#if 0
int piggy_register_sound( digi_sound * snd, char * name, int in_file )
{
	int i;

	Assert( Num_sound_files < MAX_SOUND_FILES );

	strncpy( AllSounds[Num_sound_files].name, name, 12 );
	hashtable_insert( &AllDigiSndNames, AllSounds[Num_sound_files].name, Num_sound_files );
	GameSounds[Num_sound_files] = *snd;
	if ( !in_file )	{
		SoundOffset[Num_sound_files] = 0;	
	}

	i = Num_sound_files;
   
	if (!in_file)
		Num_sound_files_new++;

	Num_sound_files++;
	return i;
}
#endif

bitmap_index piggy_find_bitmap( char * name )	
{
	bitmap_index bmp;
	int i;

	bmp.index = 0;

	i = hashtable_search( &AllBitmapsNames, name );
	Assert( i != 0 );
	if ( i < 0 )
		return bmp;

	bmp.index = i;
	return bmp;
}

int piggy_find_sound( char * name )	
{
	int i;

	i = hashtable_search( &AllDigiSndNames, name );

	if ( i < 0 )
		return 255;

	return i;
}

CFILE * Piggy_fp = NULL;

extern void process_one_event( void );

void piggy_close_file()
{
//	if ( Piggy_fp )	{
//		cfclose( Piggy_fp );
//		Piggy_fp	= NULL;
//	}
}

ubyte bogus_data[64*64];
grs_bitmap bogus_bitmap;
ubyte bogus_bitmap_initialized=0;
digi_sound bogus_sound;

#ifndef MAC_SHAREWARE
#define	BALD_GUY_CHEAT_SIZE	7

ubyte	bald_guy_cheat_1[BALD_GUY_CHEAT_SIZE] = { KEY_B ^ 0xF0 ^ 0xab, 
												KEY_A ^ 0xE0 ^ 0xab, 
												KEY_L ^ 0xD0 ^ 0xab, 
												KEY_D ^ 0xC0 ^ 0xab, 
												KEY_G ^ 0xB0 ^ 0xab, 
												KEY_U ^ 0xA0 ^ 0xab,
												KEY_Y ^ 0x90 ^ 0xab };
#endif

extern void bm_read_all(CFILE * fp);

int piggy_init()
{
	int sbytes = 0;
	char temp_name_read[16];
	char temp_name[16];
	grs_bitmap temp_bitmap;
	digi_sound temp_sound;
	DiskBitmapHeader bmh;
	DiskSoundHeader sndh;
	int header_size, N_bitmaps, N_sounds;
	int i,size, length;
	char * filename;
	int read_sounds = 1;
	int Pigdata_start;

	hashtable_init( &AllBitmapsNames, MAX_BITMAP_FILES );
//	hashtable_init( &AllDigiSndNames, MAX_SOUND_FILES );
	
	if (GameBitmaps == NULL) {
		GameBitmaps = (grs_bitmap *)mymalloc(sizeof(grs_bitmap) * MAX_BITMAP_FILES);
		if (GameBitmaps == NULL)
			Error("Cannot allocate space for game bitmaps in piggy.c");
	}

	if (AllBitmaps == NULL) {
		AllBitmaps = (BitmapFile *)mymalloc(sizeof(BitmapFile) * MAX_BITMAP_FILES);
		if (AllBitmaps == NULL)
			Error("Cannot allocate space for bitmap filenames in piggy.c");
	}
	
#if 0
	if (AllSounds == NULL) {
		AllSounds = (SoundFile *)mymalloc(sizeof(SoundFile) * MAX_SOUND_FILES);
		if (AllSounds == NULL)
			Error("Cannot allocate space for sound filenames in piggy.c");
	}
	
	if ( FindArg( "-nosound" ) || (digi_driver_board<1) )		{
		read_sounds = 0;
		mprintf(( 0, "Not loading sound data!!!!!\n" ));
	}
	
	for (i=0; i<MAX_SOUND_FILES; i++ )	{
		GameSounds[i].length = 0;
		GameSounds[i].data = NULL;
		SoundOffset[i] = 0;
	}
#endif

	for (i=0; i<MAX_BITMAP_FILES; i++ )	
		GameBitmapXlat[i] = i;

	if ( !bogus_bitmap_initialized )	{
		int i;
		ubyte c;
		bogus_bitmap_initialized = 1;
		memset( &bogus_bitmap, 0, sizeof(grs_bitmap) );
		bogus_bitmap.bm_w = bogus_bitmap.bm_h = bogus_bitmap.bm_rowsize = 64;
		bogus_bitmap.bm_data = bogus_data;
		c = gr_find_closest_color( 0, 0, 63 );
		for (i=0; i<4096; i++ ) bogus_data[i] = c;
		c = gr_find_closest_color( 63, 0, 0 );
		// Make a big red X !
		for (i=0; i<64; i++ )	{
			bogus_data[i*64+i] = c;
			bogus_data[i*64+(63-i)] = c;
		}
		piggy_register_bitmap( &bogus_bitmap, "bogus", 1 );
		bogus_sound.length = 64*64;
		bogus_sound.data = bogus_data;
		GameBitmapOffset[0] = 0;
	}

	filename = ":Data:DESCENT.PIG";
	
	if ( FindArg( "-bigpig" ))
		BigPig = 1;

	if ( FindArg( "-lowmem" ))
		piggy_low_memory = 1;

	if ( FindArg( "-nolowmem" ))
		piggy_low_memory = 0;

	if (use_alt_textures)
		piggy_low_memory = 1;
		
//MWA	if (piggy_low_memory)
//MWA		digi_lomem = 1;

	if ( (i=FindArg( "-piggy" )) )	{
		filename	= Args[i+1];
		mprintf( (0, "Using alternate pigfile, '%s'\n", filename ));
	}
	Piggy_fp = cfopen( filename, "rb" );
	if (Piggy_fp==NULL) return 0;

	Pigdata_start = read_int_swap(Piggy_fp);
#ifdef EDITOR
	if ( FindArg("-nobm") )
#endif
	{
		bm_read_all( Piggy_fp );	// Note connection to above if!!!
		for (i = 0; i < MAX_BITMAP_FILES; i++)
			GameBitmapXlat[i] = read_short_swap(Piggy_fp);
		digi_load_sounds();
	}

	cfseek( Piggy_fp, Pigdata_start, SEEK_SET );
	size = cfilelength(Piggy_fp) - Pigdata_start;
	length = size;
	mprintf( (0, "\nReading data (%d KB) ", size/1024 ));

	N_bitmaps = read_int_swap(Piggy_fp);
	size -= sizeof(int);
	N_sounds = read_int_swap(Piggy_fp);
	size -= sizeof(int);

//	header_size = (N_bitmaps*sizeof(DiskBitmapHeader)) + (N_sounds*sizeof(DiskSoundHeader));
	header_size = ((N_bitmaps*17) + (N_sounds*20));

	gr_set_curfont( Gamefonts[GFONT_SMALL] );	
	gr_set_fontcolor(gr_find_closest_color_current( 20, 20, 20 ),-1 );
	gr_printf( 0x8000, grd_curcanv->cv_bitmap.bm_h - 25, "%s...", TXT_LOADING_DATA );
	bitblt_to_screen();

// put a couple of event loop calls here.  This should take care of TM driver!!!
	process_one_event();
	process_one_event();
	process_one_event();
	process_one_event();
	
	for (i=0; i<N_bitmaps; i++ )	{
		cfread(bmh.name, 8, 1, Piggy_fp);
		bmh.dflags = read_byte(Piggy_fp);
		bmh.width = read_byte(Piggy_fp);
		bmh.height = read_byte(Piggy_fp);
		bmh.flags = read_byte(Piggy_fp);
		bmh.avg_color = read_byte(Piggy_fp);
		bmh.offset = read_int_swap(Piggy_fp);
		
		//size -= sizeof(DiskBitmapHeader);
		memcpy( temp_name_read, bmh.name, 8 );
		temp_name_read[8] = 0;
		if ( bmh.dflags & DBM_FLAG_ABM )	
			sprintf( temp_name, "%s#%d", temp_name_read, bmh.dflags & 63 );
		else
			strcpy( temp_name, temp_name_read );
		memset( &temp_bitmap, 0, sizeof(grs_bitmap) );
		if ( bmh.dflags & DBM_FLAG_LARGE )
			temp_bitmap.bm_w = temp_bitmap.bm_rowsize = bmh.width+256;
		else
			temp_bitmap.bm_w = temp_bitmap.bm_rowsize = bmh.width;
		temp_bitmap.bm_h = bmh.height;
		temp_bitmap.bm_flags = BM_FLAG_PAGED_OUT;
		temp_bitmap.avg_color = bmh.avg_color;
		temp_bitmap.bm_data = Piggy_bitmap_cache_data;

// HACK HACK HACK!!!!!
		if (!strnicmp(bmh.name, "cockpit", 7) || !strnicmp(bmh.name, "status", 6) || !strnicmp(bmh.name, "rearview", 8)) {
			temp_bitmap.bm_w = temp_bitmap.bm_rowsize = 640;
		}
		if (!strnicmp(bmh.name, "cockpit", 7) || !strnicmp(bmh.name, "rearview", 8))
			temp_bitmap.bm_h = 480;
			

		GameBitmapFlags[i+1] = 0;
		if ( bmh.flags & BM_FLAG_TRANSPARENT ) GameBitmapFlags[i+1] |= BM_FLAG_TRANSPARENT;
		if ( bmh.flags & BM_FLAG_SUPER_TRANSPARENT ) GameBitmapFlags[i+1] |= BM_FLAG_SUPER_TRANSPARENT;
		if ( bmh.flags & BM_FLAG_NO_LIGHTING ) GameBitmapFlags[i+1] |= BM_FLAG_NO_LIGHTING;
		if ( bmh.flags & BM_FLAG_RLE ) GameBitmapFlags[i+1] |= BM_FLAG_RLE;

		GameBitmapOffset[i+1] = bmh.offset + header_size + (sizeof(int)*2) + Pigdata_start;
		Assert( (i+1) == Num_bitmap_files );
		piggy_register_bitmap( &temp_bitmap, temp_name, 1 );
	}

#if 0
	for (i=0; i<N_sounds; i++ )	{
		cfread(sndh.name, 8, 1, Piggy_fp);
		sndh.length = read_int_swap(Piggy_fp);
		sndh.data_length = read_int_swap(Piggy_fp);
		sndh.offset = read_int_swap(Piggy_fp);
		
		//size -= sizeof(DiskSoundHeader);
		temp_sound.length = sndh.length;
		temp_sound.data = (ubyte *)(sndh.offset + header_size + (sizeof(int)*2)+Pigdata_start);
		SoundOffset[Num_sound_files] = sndh.offset + header_size + (sizeof(int)*2)+Pigdata_start;
		memcpy( temp_name_read, sndh.name, 8 );
		temp_name_read[8] = 0;
		piggy_register_sound( &temp_sound, temp_name_read, 1 );
		sbytes += sndh.length;
		//mprintf(( 0, "%d bytes of sound\n", sbytes ));
	}

	SoundBits = mymalloc( sbytes + 16 );
	if ( SoundBits == NULL )
		Error( "Not enough memory to load DESCENT.PIG sounds\n" );
#endif

#ifdef EDITOR
	Piggy_bitmap_cache_size	= size - header_size - sbytes + 16;
	Assert( Piggy_bitmap_cache_size > 0 );
#else
	if (!piggy_low_memory)
		Piggy_bitmap_cache_size = PIGGY_BUFFER_SIZE;
	else
		Piggy_bitmap_cache_size = LOW_PIGGY_BUFFER_SIZE;
#endif
	BitmapBits = mymalloc( Piggy_bitmap_cache_size );
	if ( BitmapBits == NULL )
		Error( "Not enough memory to load DESCENT.PIG bitmaps\n" );
	Piggy_bitmap_cache_data = BitmapBits;	
	Piggy_bitmap_cache_next = 0;
	
	mprintf(( 0, "\nBitmaps: %d KB   Sounds: %d KB\n", Piggy_bitmap_cache_size/1024, sbytes/1024 ));

	atexit(piggy_close_file);

//	mprintf( (0, "<<<<Paging in all piggy bitmaps...>>>>>" ));
//	for (i=0; i < Num_bitmap_files; i++ )	{
//		bitmap_index bi;
//		bi.index = i;
//		PIGGY_PAGE_IN( bi );
//	}
//	mprintf( (0, "\n (USed %d / %d KB)\n", Piggy_bitmap_cache_next/1024, (size - header_size - sbytes + 16)/1024 ));
//	key_getch();

	return 0;
}

int piggy_is_needed(int soundnum)
{
	int i;

	if ( !digi_lomem ) return 1;

	for (i=0; i<MAX_SOUNDS; i++ )	{
		if ( (AltSounds[i] < 255) && (Sounds[AltSounds[i]] == soundnum) )
			return 1;
	}
	return 0;
}

void piggy_read_sounds()
{
#if 0
	ubyte * ptr;
	int i, sbytes;

	ptr = SoundBits;
	sbytes = 0;

	for (i=0; i<Num_sound_files; i++ )	{
		digi_sound *snd = &GameSounds[i];

		if ( SoundOffset[i] > 0 )	{
			if ( piggy_is_needed(i) )	{
				cfseek( Piggy_fp, SoundOffset[i], SEEK_SET );
	
				// Read in the sound data!!!
				snd->data = ptr;
				ptr += snd->length;
				sbytes += snd->length;
				cfread( snd->data, snd->length, 1, Piggy_fp );
			}
		}
	}

	mprintf(( 0, "\nActual Sound usage: %d KB\n", sbytes/1024 ));
#endif
}

extern int descent_critical_error;
extern unsigned descent_critical_deverror;
extern unsigned descent_critical_errcode;

char * crit_errors[13] = { "Write Protected", "Unknown Unit", "Drive Not Ready", "Unknown Command", "CRC Error", \
"Bad struct length", "Seek Error", "Unknown media type", "Sector not found", "Printer out of paper", "Write Fault", \
"Read fault", "General Failure" };

void piggy_critical_error()
{
	grs_canvas * save_canv;
	grs_font * save_font;
	int i;
	save_canv = grd_curcanv;
	save_font = grd_curcanv->cv_font;
	gr_palette_load( gr_palette );
	i = nm_messagebox( "Disk Error", 2, "Retry", "Exit", "%s\non drive %c:", crit_errors[descent_critical_errcode&0xf], (descent_critical_deverror&0xf)+'A'  );
	if ( i == 1 )
		exit(1);
	gr_set_current_canvas(save_canv);
	grd_curcanv->cv_font = save_font;
}

void piggy_bitmap_page_in( bitmap_index bitmap )
{
	grs_bitmap * bmp;
	int i,org_i,temp;
	char buf[256];
	ubyte *src;
			
	i = bitmap.index;
	Assert( i >= 0 );
	Assert( i < MAX_BITMAP_FILES );
	Assert( i < Num_bitmap_files );
	Assert( Piggy_bitmap_cache_size > 0 );

	if ( GameBitmapOffset[i] == 0 ) return;		// A read-from-disk bitmap!!!

	if ( piggy_low_memory )	{
		org_i = i;
		i = GameBitmapXlat[i];		// Xlat for low-memory settings!
	}
	bmp = &GameBitmaps[i];

	if ( bmp->bm_flags & BM_FLAG_PAGED_OUT )	{
		stop_time();

	ReDoIt:
		descent_critical_error = 0;
		cfseek( Piggy_fp, GameBitmapOffset[i], SEEK_SET );
		if ( descent_critical_error )	{
			piggy_critical_error();
			goto ReDoIt;
		}
		
		bmp->bm_data = &Piggy_bitmap_cache_data[Piggy_bitmap_cache_next];
		bmp->bm_flags = GameBitmapFlags[i];
	
		if ( bmp->bm_flags & BM_FLAG_RLE )	{
			int zsize = 0;
			descent_critical_error = 0;
			zsize = read_int_swap(Piggy_fp);
			if ( descent_critical_error )	{
				piggy_critical_error();
				goto ReDoIt;
			}

			// GET JOHN NOW IF YOU GET THIS ASSERT!!!
			Assert( Piggy_bitmap_cache_next+zsize < Piggy_bitmap_cache_size );	
			if ( Piggy_bitmap_cache_next+zsize >= Piggy_bitmap_cache_size )	{
				piggy_bitmap_page_out_all();
				goto ReDoIt;
			}
			memcpy( &Piggy_bitmap_cache_data[Piggy_bitmap_cache_next], &zsize, sizeof(int) );
			Piggy_bitmap_cache_next += sizeof(int);
			descent_critical_error = 0;
			temp = cfread( &Piggy_bitmap_cache_data[Piggy_bitmap_cache_next], 1, zsize-4, Piggy_fp );
			if ( descent_critical_error )	{
				piggy_critical_error();
				goto ReDoIt;
			}
			Piggy_bitmap_cache_next += zsize-4;
		} else {
			// GET JOHN NOW IF YOU GET THIS ASSERT!!!
			Assert( Piggy_bitmap_cache_next+(bmp->bm_h*bmp->bm_w) < Piggy_bitmap_cache_size );	
			if ( Piggy_bitmap_cache_next+(bmp->bm_h*bmp->bm_w) >= Piggy_bitmap_cache_size )	{
				piggy_bitmap_page_out_all();
				goto ReDoIt;
			}
			descent_critical_error = 0;
			temp = cfread( &Piggy_bitmap_cache_data[Piggy_bitmap_cache_next], 1, bmp->bm_h*bmp->bm_w, Piggy_fp );
			if ( descent_critical_error )	{
				piggy_critical_error();
				goto ReDoIt;
			}
			Piggy_bitmap_cache_next+=bmp->bm_h*bmp->bm_w;
#if 0
			temp = bmp->bm_h*bmp->bm_w;
			src = (ubyte *)bmp->bm_data;
			for (i = 0; i < temp; i++) {
				if (*src == 0)
					*src = 255;
				else if (*src == 255)
					*src = 0;
				src++;
			}
#endif
		}
		start_time();
	}

	if ( piggy_low_memory )	{
		if ( org_i != i )
			GameBitmaps[org_i] = GameBitmaps[i];
	}
}

void piggy_bitmap_page_out_all()
{
	int i;
	
	Piggy_bitmap_cache_next = 0;

	piggy_page_flushed++;

	texmerge_flush();
	rle_cache_flush();

	for (i=0; i<Num_bitmap_files; i++ )		{
		if ( GameBitmapOffset[i] > 0 )	{	// Don't page out bitmaps read from disk!!!
			GameBitmaps[i].bm_flags = BM_FLAG_PAGED_OUT;
			GameBitmaps[i].bm_data = Piggy_bitmap_cache_data;
		}
	}

	mprintf(( 0, "Flushing piggy bitmap cache\n" ));
}

void piggy_load_level_data()
{
	piggy_bitmap_page_out_all();
	paging_touch_all();
}

void piggy_close()
{
	if (BitmapBits)
		myfree(BitmapBits);

	if ( SoundBits )
		myfree( SoundBits );

	hashtable_free( &AllBitmapsNames );
	hashtable_free( &AllDigiSndNames );

}

int piggy_does_bitmap_exist_slow( char * name )
{
	int i;

	for (i=0; i<Num_bitmap_files; i++ )	{
		if ( !strcmp( AllBitmaps[i].name, name) )
			return 1;
	}
	return 0;
}


#define NUM_GAUGE_BITMAPS 14
char * gauge_bitmap_names[NUM_GAUGE_BITMAPS] = { "gauge01", "gauge02", "gauge06", "targ01", "targ02", "targ03", "targ04", "targ05", "targ06", "gauge18", "targ01pc", "targ02pc", "targ03pc", "gaug18pc" };

int piggy_is_gauge_bitmap( char * base_name )
{
	int i;
	for (i=0; i<NUM_GAUGE_BITMAPS; i++ )	{
		if ( !stricmp( base_name, gauge_bitmap_names[i] ))	
			return 1;
	}

	return 0;	
}

#ifndef MAC_SHAREWARE
extern ubyte baldguy_cheat;

void bald_guy_cheat(int key)
{
	if (key == (bald_guy_cheat_1[bald_guy_cheat_index] ^ (0xf0 - (bald_guy_cheat_index << 4)) ^ 0xab)) {
		bald_guy_cheat_index++;
		if (bald_guy_cheat_index == BALD_GUY_CHEAT_SIZE)	{
			baldguy_cheat = 1;
			bald_guy_cheat_index = 0;
		}
	} else
		bald_guy_cheat_index = 0;
}
#endif


int piggy_is_substitutable_bitmap( char * name, char * subst_name )
{
	int frame;
	char * p;
	char base_name[ 16 ];
	
	strcpy( subst_name, name );
	p = strchr( subst_name, '#' );
	if ( p ) 	{
		frame = atoi( &p[1] );
		*p = 0;
		strcpy( base_name, subst_name );
		if ( !piggy_is_gauge_bitmap( base_name ))	{
			sprintf( subst_name, "%s#%d", base_name, frame+1 );
			if ( piggy_does_bitmap_exist_slow( subst_name )  ) 	{
				if ( frame & 1 ) {
					sprintf( subst_name, "%s#%d", base_name, frame-1 );
					return 1;
				}
			}
		}
	}
	strcpy( subst_name, name );
	return 0;
}

