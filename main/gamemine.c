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
 * $Source: Smoke:miner:source:main::RCS:gamemine.c $
 * $Revision: 1.2 $
 * $Author: allender $
 * $Date: 1995/10/31 10:15:58 $
 * 
 * Functions for loading mines in the game
 * 
 * $Log: gamemine.c $
 * Revision 1.2  1995/10/31  10:15:58  allender
 * code for shareware levels
 *
 * Revision 1.1  1995/05/16  15:25:29  allender
 * Initial revision
 *
 * Revision 2.2  1995/03/06  15:23:14  john
 * New screen techniques.
 * 
 * Revision 2.1  1995/02/27  13:13:37  john
 * Removed floating point.
 * 
 * Revision 2.0  1995/02/27  11:27:45  john
 * New version 2.0, which has no anonymous unions, builds with
 * Watcom 10.0, and doesn't require parsing BITMAPS.TBL.
 * 
 * Revision 1.70  1995/02/13  20:35:09  john
 * Lintized
 * 
 * Revision 1.69  1995/02/07  17:12:03  rob
 * Added ifdef's for Editor.
 * 
 * Revision 1.68  1995/02/07  16:51:48  mike
 * fix gray rock josh problem.
 * 
 * Revision 1.67  1995/02/01  15:46:26  yuan
 * Fixed matcen_nums.
 * 
 * Revision 1.66  1995/01/19  15:19:28  mike
 * new super-compressed registered file format.
 * 
 * Revision 1.65  1994/12/10  16:44:59  matt
 * Added debugging code to track down door that turns into rock
 * 
 * Revision 1.64  1994/12/10  14:58:24  yuan
 * *** empty log message ***
 * 
 * Revision 1.63  1994/12/08  17:19:10  yuan
 * Cfiling stuff.
 * 
 * Revision 1.62  1994/12/07  14:05:33  yuan
 * Fixed wall assert problem... Bashed highest_segment
 * _index before WALL_IS_DOORWAY check.
 * 
 * Revision 1.61  1994/11/27  23:14:52  matt
 * Made changes for new mprintf calling convention
 * 
 * Revision 1.60  1994/11/27  18:05:20  matt
 * Compile out LVL reader when editor compiled out
 * 
 * Revision 1.59  1994/11/26  22:51:45  matt
 * Removed editor-only fields from segment structure when editor is compiled
 * out, and padded segment structure to even multiple of 4 bytes.
 * 
 * Revision 1.58  1994/11/26  21:48:02  matt
 * Fixed saturation in short light value 
 * 
 * Revision 1.57  1994/11/20  22:11:49  mike
 * comment out an apparently unnecessary call to fuelcen_reset().
 * 
 * Revision 1.56  1994/11/18  21:56:42  john
 * Added a better, leaner pig format.
 * 
 * Revision 1.55  1994/11/17  20:09:18  john
 * Added new compiled level format.
 * 
 * Revision 1.54  1994/11/17  15:40:17  mike
 * Comment out mprintf which was causing important information to scroll away.
 * 
 * Revision 1.53  1994/11/17  14:56:37  mike
 * moved segment validation functions from editor to main.
 * 
 * Revision 1.52  1994/11/17  11:39:35  matt
 * Ripped out code to load old mines
 * 
 * Revision 1.51  1994/11/14  20:47:53  john
 * Attempted to strip out all the code in the game 
 * directory that uses any ui code.
 * 
 * Revision 1.50  1994/11/14  16:05:38  matt
 * Fixed, maybe, again, errors when can't find texture during remap
 * 
 * Revision 1.49  1994/11/14  14:34:03  matt
 * Fixed up handling when textures can't be found during remap
 * 
 * Revision 1.48  1994/11/14  13:01:55  matt
 * Added Int3() when can't find texture
 * 
 * Revision 1.47  1994/10/30  14:12:21  mike
 * rip out local segments stuff.
 * 
 * Revision 1.46  1994/10/27  19:43:07  john
 * Disable the piglet option.
 * 
 * Revision 1.45  1994/10/27  18:51:42  john
 * Added -piglet option that only loads needed textures for a 
 * mine.  Only saved ~1MB, and code still doesn't free textures
 * before you load a new mine.
 * 
 * Revision 1.44  1994/10/20  12:47:22  matt
 * Replace old save files (MIN/SAV/HOT) with new LVL files
 * 
 * Revision 1.43  1994/10/19  16:46:40  matt
 * Made tmap overrides for robots remap texture numbers
 * 
 * Revision 1.42  1994/10/03  23:37:01  mike
 * Adapt to changed fuelcen_activate parameters.
 * 
 * Revision 1.41  1994/09/23  22:14:49  matt
 * Took out obsolete structure fields
 * 
 * Revision 1.40  1994/08/01  11:04:11  yuan
 * New materialization centers.
 * 
 * Revision 1.39  1994/07/21  19:01:47  mike
 * Call Lsegment stuff.
 * 
 * 
 */

#pragma off (unreferenced)
static char rcsid[] = "$Id: gamemine.c 1.2 1995/10/31 10:15:58 allender Exp $";
#pragma on (unreferenced)

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#include "mono.h"

#include "inferno.h"
#include "segment.h"
#include "textures.h"
#include "wall.h"
#include "object.h"
#include "gamemine.h"
#include "error.h"
#include "gameseg.h"
#include "switch.h"

#include "game.h"
#include "newmenu.h"

#ifdef EDITOR
#include "editor\editor.h"
#endif

#include "cfile.h"		
#include "fuelcen.h"

#include "hash.h"
#include "key.h"
#include "piggy.h"
#include "byteswap.h"
#include "fileutil.h"

#define REMOVE_EXT(s)  (*(strchr( (s), '.' ))='\0')

struct mtfi mine_top_fileinfo;    // Should be same as first two fields below...
struct mfi mine_fileinfo;
struct mh mine_header;
struct me mine_editor;

int CreateDefaultNewSegment();

#define COMPILED_MINE_VERSION 0

int	New_file_format_load = 1;

int load_mine_data_compiled(CFILE *LoadFile)
{
	int i,segnum,sidenum;
	ubyte version;
	short temp_short;
	ushort temp_ushort;

#ifndef MAC_SHAREWARE
	if (New_file_format_load)
		return load_mine_data_compiled_new(LoadFile);
#endif

	//	For compiled levels, textures map to themselves, prevent tmap_override always being gray,
	//	bug which Matt and John refused to acknowledge, so here is Mike, fixing it.
	// 
	// Although in a cloud of arrogant glee, he forgot to ifdef it on EDITOR!
	// (Matt told me to write that!)
#ifdef EDITOR
	for (i=0; i<MAX_TEXTURES; i++)
		tmap_xlate_table[i] = i;
#endif
//	memset( Segments, 0, sizeof(segment)*MAX_SEGMENTS );
	fuelcen_reset();

	//=============================== Reading part ==============================
	cfread( &version, sizeof(ubyte), 1, LoadFile );						// 1 byte = compiled version
	Assert( version==COMPILED_MINE_VERSION );
//	cfread( &Num_vertices, sizeof(int), 1, LoadFile );					// 4 bytes = Num_vertices
	Num_vertices = read_int_swap(LoadFile);
	Assert( Num_vertices <= MAX_VERTICES );
//	cfread( &Num_segments, sizeof(int), 1, LoadFile );					// 4 bytes = Num_segments
	Num_segments = read_int_swap(LoadFile);
	Assert( Num_segments <= MAX_SEGMENTS );
//	cfread( Vertices, sizeof(vms_vector), Num_vertices, LoadFile );

	for (i = 0; i < Num_vertices; i++) {
		Vertices[i].x = read_fix_swap(LoadFile);
		Vertices[i].y = read_fix_swap(LoadFile);
		Vertices[i].z = read_fix_swap(LoadFile);
	}


	for (segnum=0; segnum<Num_segments; segnum++ )	{
		#ifdef EDITOR
		Segments[segnum].segnum = segnum;
		Segments[segnum].group = 0;
		#endif

		// Read short Segments[segnum].children[MAX_SIDES_PER_SEGMENT]
// 		cfread( Segments[segnum].children, sizeof(short), MAX_SIDES_PER_SEGMENT, LoadFile );
		for (i = 0; i < MAX_SIDES_PER_SEGMENT; i++)
			Segments[segnum].children[i] = read_short_swap(LoadFile);


		// Read short Segments[segnum].verts[MAX_VERTICES_PER_SEGMENT]
//		cfread( Segments[segnum].verts, sizeof(short), MAX_VERTICES_PER_SEGMENT, LoadFile );
		for (i = 0; i < MAX_VERTICES_PER_SEGMENT; i++)
			Segments[segnum].verts[i] = read_short_swap(LoadFile);

		Segments[segnum].objects = -1;

		// Read ubyte	Segments[segnum].special
		cfread( &Segments[segnum].special, sizeof(ubyte), 1, LoadFile );
		// Read byte	Segments[segnum].matcen_num
		cfread( &Segments[segnum].matcen_num, sizeof(ubyte), 1, LoadFile );
		// Read short	Segments[segnum].value
//		cfread( &Segments[segnum].value, sizeof(short), 1, LoadFile );
		Segments[segnum].value = read_short_swap(LoadFile);

		// Read fix	Segments[segnum].static_light (shift down 5 bits, write as short)
//		cfread( &temp_ushort, sizeof(temp_ushort), 1, LoadFile );
		temp_ushort = read_short_swap(LoadFile);
		Segments[segnum].static_light	= ((fix)temp_ushort) << 4;
		//cfread( &Segments[segnum].static_light, sizeof(fix), 1, LoadFile );
	
		// Read the walls as a 6 byte array
		for (sidenum=0; sidenum<MAX_SIDES_PER_SEGMENT; sidenum++ )	{
			ubyte byte_wallnum;
			Segments[segnum].sides[sidenum].pad = 0;
			cfread( &byte_wallnum, sizeof(ubyte), 1, LoadFile );
			if ( byte_wallnum == 255 )			
				Segments[segnum].sides[sidenum].wall_num = -1;
			else		
				Segments[segnum].sides[sidenum].wall_num = byte_wallnum;
		}

		for (sidenum=0; sidenum<MAX_SIDES_PER_SEGMENT; sidenum++ )	{

			if ( (Segments[segnum].children[sidenum]==-1) || (Segments[segnum].sides[sidenum].wall_num!=-1) )	{
				// Read short Segments[segnum].sides[sidenum].tmap_num;
//				cfread( &Segments[segnum].sides[sidenum].tmap_num, sizeof(short), 1, LoadFile );
				Segments[segnum].sides[sidenum].tmap_num = read_short_swap(LoadFile);
				// Read short Segments[segnum].sides[sidenum].tmap_num2;
//				cfread( &Segments[segnum].sides[sidenum].tmap_num2, sizeof(short), 1, LoadFile );
				Segments[segnum].sides[sidenum].tmap_num2 = read_short_swap(LoadFile);
				// Read uvl Segments[segnum].sides[sidenum].uvls[4] (u,v>>5, write as short, l>>1 write as short)
				for (i=0; i<4; i++ )	{
//					cfread( &temp_short, sizeof(short), 1, LoadFile );
					temp_short = read_short_swap(LoadFile);
					Segments[segnum].sides[sidenum].uvls[i].u = ((fix)temp_short) << 5;
//					cfread( &temp_short, sizeof(short), 1, LoadFile );
					temp_short = read_short_swap(LoadFile);
					Segments[segnum].sides[sidenum].uvls[i].v = ((fix)temp_short) << 5;
//					cfread( &temp_ushort, sizeof(temp_ushort), 1, LoadFile );
					temp_ushort = read_short_swap(LoadFile);
					Segments[segnum].sides[sidenum].uvls[i].l = ((fix)temp_ushort) << 1;
//					cfread( &Segments[segnum].sides[sidenum].uvls[i].l, sizeof(fix), 1, LoadFile );
				}	
			} else {
				Segments[segnum].sides[sidenum].tmap_num = 0;
				Segments[segnum].sides[sidenum].tmap_num2 = 0;
				for (i=0; i<4; i++ )	{
					Segments[segnum].sides[sidenum].uvls[i].u = 0;
					Segments[segnum].sides[sidenum].uvls[i].v = 0;
					Segments[segnum].sides[sidenum].uvls[i].l = 0;
				}	
			}
		}
	}

	Highest_vertex_index = Num_vertices-1;
	Highest_segment_index = Num_segments-1;

	validate_segment_all();			// Fill in side type and normals.

	// Activate fuelcentes
	for (i=0; i< Num_segments; i++ ) {
		fuelcen_activate( &Segments[i], Segments[i].special );
	}

	reset_objects(1);		//one object, the player

	return 0;
}

#ifndef MAC_SHAREWARE
int load_mine_data_compiled_new(CFILE *LoadFile)
{
	int		i,segnum,sidenum;
	ubyte		version;
	short		temp_short;
	ushort	temp_ushort;
	ubyte		bit_mask;

	//	For compiled levels, textures map to themselves, prevent tmap_override always being gray,
	//	bug which Matt and John refused to acknowledge, so here is Mike, fixing it.
#ifdef EDITOR
	for (i=0; i<MAX_TEXTURES; i++)
		tmap_xlate_table[i] = i;
#endif

//	memset( Segments, 0, sizeof(segment)*MAX_SEGMENTS );
	fuelcen_reset();

	//=============================== Reading part ==============================
	cfread( &version, sizeof(ubyte), 1, LoadFile );						// 1 byte = compiled version
	Assert( version==COMPILED_MINE_VERSION );

	Num_vertices = read_short_swap(LoadFile);
	Assert( Num_vertices <= MAX_VERTICES );

	Num_segments = read_short_swap(LoadFile);
	Assert( Num_segments <= MAX_SEGMENTS );

	for (i = 0; i < Num_vertices; i++) {
		Vertices[i].x = read_fix_swap(LoadFile);
		Vertices[i].y = read_fix_swap(LoadFile);
		Vertices[i].z = read_fix_swap(LoadFile);
	}
	
	for (segnum=0; segnum<Num_segments; segnum++ )	{
		int	bit;

		#ifdef EDITOR
		Segments[segnum].segnum = segnum;
		Segments[segnum].group = 0;
		#endif

		bit_mask = read_byte(LoadFile);

		for (bit=0; bit<MAX_SIDES_PER_SEGMENT; bit++) {
			if (bit_mask & (1 << bit))
				Segments[segnum].children[bit] = read_short_swap(LoadFile);
			else
				Segments[segnum].children[bit] = -1;
		}

		// Read short Segments[segnum].verts[MAX_VERTICES_PER_SEGMENT]
		for (i = 0; i < MAX_VERTICES_PER_SEGMENT; i++)
			Segments[segnum].verts[i] = read_short_swap(LoadFile);

		Segments[segnum].objects = -1;

		if (bit_mask & (1 << MAX_SIDES_PER_SEGMENT)) {
			// Read ubyte	Segments[segnum].special
			Segments[segnum].special = read_byte(LoadFile);
			// Read byte	Segments[segnum].matcen_num
			Segments[segnum].matcen_num = read_byte(LoadFile);
			// Read short	Segments[segnum].value
			Segments[segnum].value = read_short_swap(LoadFile);
		} else {
			Segments[segnum].special = 0;
			Segments[segnum].matcen_num = -1;
			Segments[segnum].value = 0;
		}

		// Read fix	Segments[segnum].static_light (shift down 5 bits, write as short)
		temp_ushort = read_short_swap(LoadFile);
		Segments[segnum].static_light	= ((fix)temp_ushort) << 4;
	
		// Read the walls as a 6 byte array
		for (sidenum=0; sidenum<MAX_SIDES_PER_SEGMENT; sidenum++ )	{
			Segments[segnum].sides[sidenum].pad = 0;
		}

		bit_mask = read_byte(LoadFile);
		for (sidenum=0; sidenum<MAX_SIDES_PER_SEGMENT; sidenum++) {
			ubyte byte_wallnum;

			if (bit_mask & (1 << sidenum)) {
				byte_wallnum = read_byte(LoadFile);
				if ( byte_wallnum == 255 )			
					Segments[segnum].sides[sidenum].wall_num = -1;
				else		
					Segments[segnum].sides[sidenum].wall_num = byte_wallnum;
			} else
					Segments[segnum].sides[sidenum].wall_num = -1;
		}

		for (sidenum=0; sidenum<MAX_SIDES_PER_SEGMENT; sidenum++ )	{

			if ( (Segments[segnum].children[sidenum]==-1) || (Segments[segnum].sides[sidenum].wall_num!=-1) )	{
				// Read short Segments[segnum].sides[sidenum].tmap_num;
				temp_ushort = read_short_swap(LoadFile);
				Segments[segnum].sides[sidenum].tmap_num = temp_ushort & 0x7fff;

				if (!(temp_ushort & 0x8000))
					Segments[segnum].sides[sidenum].tmap_num2 = 0;
				else {
					// Read short Segments[segnum].sides[sidenum].tmap_num2;
					Segments[segnum].sides[sidenum].tmap_num2 = read_short_swap(LoadFile);
				}

				// Read uvl Segments[segnum].sides[sidenum].uvls[4] (u,v>>5, write as short, l>>1 write as short)
				for (i=0; i<4; i++ )	{
					temp_short = read_short_swap(LoadFile);
					Segments[segnum].sides[sidenum].uvls[i].u = ((fix)temp_short) << 5;
					temp_short = read_short_swap(LoadFile);
					Segments[segnum].sides[sidenum].uvls[i].v = ((fix)temp_short) << 5;
					temp_ushort = read_short_swap(LoadFile);
					Segments[segnum].sides[sidenum].uvls[i].l = ((fix)temp_ushort) << 1;
				}	
			} else {
				Segments[segnum].sides[sidenum].tmap_num = 0;
				Segments[segnum].sides[sidenum].tmap_num2 = 0;
				for (i=0; i<4; i++ )	{
					Segments[segnum].sides[sidenum].uvls[i].u = 0;
					Segments[segnum].sides[sidenum].uvls[i].v = 0;
					Segments[segnum].sides[sidenum].uvls[i].l = 0;
				}	
			}
		}
	}
	
	Highest_vertex_index = Num_vertices-1;
	Highest_segment_index = Num_segments-1;

	validate_segment_all();			// Fill in side type and normals.

	// Activate fuelcentes
	for (i=0; i< Num_segments; i++ ) {
		fuelcen_activate( &Segments[i], Segments[i].special );
	}

	reset_objects(1);		//one object, the player

	return 0;
}

#endif
