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
 * $Source: BigRed:miner:source:main::RCS:gamesave.c $
 * $Revision: 1.3 $
 * $Author: allender $
 * $Date: 1996/02/21 13:59:17 $
 * 
 * Save game information
 * 
 * $Log: gamesave.c $
 * Revision 1.3  1996/02/21  13:59:17  allender
 * check Data folder when can't open a level file from a hog
 *
 * Revision 1.2  1995/10/31  10:23:23  allender
 * shareware stuff
 *
 * Revision 1.1  1995/05/16  15:25:37  allender
 * Initial revision
 *
 * Revision 2.1  1995/03/20  18:15:43  john
 * Added code to not store the normals in the segment structure.
 * 
 * Revision 2.0  1995/02/27  11:29:50  john
 * New version 2.0, which has no anonymous unions, builds with
 * Watcom 10.0, and doesn't require parsing BITMAPS.TBL.
 * 
 * Revision 1.207  1995/02/23  10:17:36  allender
 * fixed parameter mismatch with compute_segment_center
 * 
 * Revision 1.206  1995/02/22  14:51:17  allender
 * fixed some things that I missed
 * 
 * Revision 1.205  1995/02/22  13:31:38  allender
 * remove anonymous unions from object structure
 * 
 * Revision 1.204  1995/02/01  20:58:08  john
 * Made editor check hog.
 * 
 * Revision 1.203  1995/01/28  17:40:34  mike
 * correct level names (use rdl, sdl) for dumpmine stuff.
 * 
 * Revision 1.202  1995/01/25  20:03:46  matt
 * Moved matrix check to avoid orthogonalizing an uninitialize matrix
 * 
 * Revision 1.201  1995/01/20  16:56:53  mike
 * remove some mprintfs.
 * 
 * Revision 1.200  1995/01/15  19:42:13  matt
 * Ripped out hostage faces for registered version
 * 
 * Revision 1.199  1995/01/05  16:59:09  yuan
 * Make it so if editor is loaded, don't get error from typo
 * in filename.
 * 
 * Revision 1.198  1994/12/19  12:49:46  mike
 * Change fgets to cfgets.  fgets was getting a pointer mismatch warning.
 * 
 * Revision 1.197  1994/12/12  01:20:03  matt
 * Took out object size hack for green claw guys
 * 
 * Revision 1.196  1994/12/11  13:19:37  matt
 * Restored calls to fix_object_segs() when debugging is turned off, since
 * it's not a big routine, and could fix some possibly bad problems.
 * 
 * Revision 1.195  1994/12/10  16:17:24  mike
 * fix editor bug that was converting transparent walls into rock.
 * 
 * Revision 1.194  1994/12/09  14:59:27  matt
 * Added system to attach a fireball to another object for rendering purposes,
 * so the fireball always renders on top of (after) the object.
 * 
 * Revision 1.193  1994/12/08  17:19:02  yuan
 * Cfiling stuff.
 * 
 * Revision 1.192  1994/12/02  20:01:05  matt
 * Always give vulcan cannon powerup same amount of ammo, regardless of
 * how much it was saved with
 * 
 * Revision 1.191  1994/11/30  17:45:57  yuan
 * Saving files now creates RDL/SDLs instead of CDLs.
 * 
 * Revision 1.190  1994/11/30  17:22:14  matt
 * Ripped out hostage faces in shareware version
 * 
 * Revision 1.189  1994/11/28  00:09:30  allender
 * commented out call to newdemo_record_start_demo in load_level...what is
 * this doing here anyway?????
 * 
 * Revision 1.188  1994/11/27  23:13:48  matt
 * Made changes for new mprintf calling convention
 * 
 * Revision 1.187  1994/11/27  18:06:20  matt
 * Cleaned up LVL/CDL file loading
 * 
 * Revision 1.186  1994/11/25  22:46:29  matt
 * Allow ESC out of compiled/normal menu (esc=compiled).
 * 
 * Revision 1.185  1994/11/23  12:18:35  mike
 * move level names here...a more logical place than dumpmine.
 * 
 * Revision 1.184  1994/11/21  20:29:19  matt
 * If hostage info is bad, fix it.
 * 
 * Revision 1.183  1994/11/21  20:26:07  matt
 * Fixed bug, I hope
 * 
 * Revision 1.182  1994/11/21  20:20:37  matt
 * Fixed stupid mistake
 * 
 * Revision 1.181  1994/11/21  20:18:40  matt
 * Fixed (hopefully) totally bogus writing of hostage data
 * 
 * Revision 1.180  1994/11/20  14:11:56  matt
 * Gracefully handle two hostages having same id
 * 
 * Revision 1.179  1994/11/19  23:55:05  mike
 * remove Assert, put in comment for Matt.
 * 
 * Revision 1.178  1994/11/19  19:53:24  matt
 * Added code to full support different hostage head clip & message for
 * each hostage.
 * 
 * Revision 1.177  1994/11/19  15:15:21  mike
 * remove unused code and data
 * 
 * Revision 1.176  1994/11/19  10:28:28  matt
 * Took out write routines when editor compiled out
 * 
 * Revision 1.175  1994/11/17  20:38:25  john
 * Took out warning.
 * 
 * Revision 1.174  1994/11/17  20:36:34  john
 * Made it so that saving a mine will write the .cdl even
 * if .lvl gets error.
 * 
 * Revision 1.173  1994/11/17  20:26:19  john
 * Made the game load whichever of .cdl or .lvl exists,
 * and if they both exist, prompt the user for which one.
 * 
 * Revision 1.172  1994/11/17  20:11:20  john
 * Fixed warning.
 * 
 * Revision 1.171  1994/11/17  20:09:26  john
 * Added new compiled level format.
 * 
 * Revision 1.170  1994/11/17  14:57:21  mike
 * moved segment validation functions from editor to main.
 * 
 * Revision 1.169  1994/11/17  11:39:21  matt
 * Ripped out code to load old mines
 * 
 * Revision 1.168  1994/11/16  11:24:53  matt
 * Made attack-type robots have smaller radius, so they get closer to player
 * 
 * Revision 1.167  1994/11/15  21:42:47  mike
 * better error messages.
 * 
 * Revision 1.166  1994/11/15  15:30:41  matt
 * Save ptr to name of level being loaded
 * 
 * Revision 1.165  1994/11/14  20:47:46  john
 * Attempted to strip out all the code in the game 
 * directory that uses any ui code.
 * 
 * Revision 1.164  1994/11/14  14:34:23  matt
 * Fixed up handling when textures can't be found during remap
 * 
 * Revision 1.163  1994/11/10  14:02:49  matt
 * Hacked in support for player ships with different textures
 * 
 * Revision 1.162  1994/11/06  14:38:17  mike
 * Remove an apparently unnecessary mprintf.
 * 
 * Revision 1.161  1994/10/30  14:11:28  mike
 * ripout local segments stuff.
 * 
 * Revision 1.160  1994/10/28  12:10:41  matt
 * Check that was supposed to happen only when editor was in was happening
 * only when editor was out.
 * 
 * Revision 1.159  1994/10/27  11:25:32  matt
 * Only do connectivity error check when editor in
 * 
 * Revision 1.158  1994/10/27  10:54:00  matt
 * Made connectivity error checking put up warning if errors found
 * 
 * Revision 1.157  1994/10/25  10:50:54  matt
 * Vulcan cannon powerups now contain ammo count
 * 
 * Revision 1.156  1994/10/23  02:10:43  matt
 * Got rid of obsolete hostage_info stuff
 * 
 * Revision 1.155  1994/10/22  18:57:26  matt
 * Added call to check_segment_connections()
 * 
 * Revision 1.154  1994/10/21  12:19:23  matt
 * Clear transient objects when saving (& loading) games
 * 
 * Revision 1.153  1994/10/21  11:25:10  mike
 * Use new constant IMMORTAL_TIME.
 * 
 * Revision 1.152  1994/10/20  12:46:59  matt
 * Replace old save files (MIN/SAV/HOT) with new LVL files
 * 
 * Revision 1.151  1994/10/19  19:26:32  matt
 * Fixed stupid bug
 * 
 * Revision 1.150  1994/10/19  16:46:21  matt
 * Made tmap overrides for robots remap texture numbers
 * 
 * Revision 1.149  1994/10/18  08:50:27  yuan
 * Fixed correct variable this time.
 * 
 * Revision 1.148  1994/10/18  08:45:02  yuan
 * Oops. forgot load function.
 * 
 * Revision 1.147  1994/10/18  08:42:10  yuan
 * Avoid the int3.
 * 
 * Revision 1.146  1994/10/17  21:34:57  matt
 * Added support for new Control Center/Main Reactor
 * 
 * Revision 1.145  1994/10/15  19:06:34  mike
 * Fix bug, maybe, having to do with something or other, ...
 * 
 * Revision 1.144  1994/10/12  21:07:33  matt
 * Killed unused field in object structure
 * 
 * Revision 1.143  1994/10/06  14:52:55  mike
 * Put check in to detect possibly bogus walls in last segment which leaked through an earlier check
 * due to misuse of Highest_segment_index.
 * 
 * Revision 1.142  1994/10/05  22:12:44  mike
 * Put in cleanup for matcen/fuelcen links.
 * 
 * Revision 1.141  1994/10/03  11:30:05  matt
 * Make sure player in a valid segment before saving
 * 
 * Revision 1.140  1994/09/28  11:14:41  mike
 * Better error messaging on bogus mines: Only bring up dialog box if a "real" (level??.*) level.
 * 
 * Revision 1.139  1994/09/28  09:22:58  mike
 * Comment out a mprintf.
 * 
 * Revision 1.138  1994/09/27  17:08:36  mike
 * Message boxes when you load bogus mines.
 * 
 * Revision 1.137  1994/09/27  15:43:45  mike
 * Move the dump stuff to dumpmine.
 * 
 * Revision 1.136  1994/09/27  00:02:31  mike
 * Dump text files (".txm") when loading a mine, showing all kinds of useful mine info.
 * 
 * Revision 1.135  1994/09/26  11:30:41  matt
 * Took out code which loaded bogus player structure
 * 
 * Revision 1.134  1994/09/26  11:18:44  john
 * Fixed some conflicts with newseg.
 * 
 * Revision 1.133  1994/09/26  10:56:58  matt
 * Fixed inconsistancies in lifeleft for immortal objects
 * 
 * Revision 1.132  1994/09/25  23:41:10  matt
 * Changed the object load & save code to read/write the structure fields one
 * at a time (rather than the whole structure at once).  This mean that the
 * object structure can be changed without breaking the load/save functions.
 * As a result of this change, the local_object data can be and has been 
 * incorporated into the object array.  Also, timeleft is now a property 
 * of all objects, and the object structure has been otherwise cleaned up.
 * 
 */

#pragma off (unreferenced)
static char rcsid[] = "$Id: gamesave.c 1.3 1996/02/21 13:59:17 allender Exp $";
#pragma on (unreferenced)


#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#include "mono.h"
#include "key.h"
#include "gr.h"
#include "palette.h"
#include "newmenu.h"
#include "inferno.h"
#include "error.h"
#include "object.h"
#include "game.h"
#include "screens.h"
#include "wall.h"
#include "gamemine.h"
#include "robot.h"
#include "cfile.h"
#include "bm.h"
#include "menu.h"
#include "switch.h"
#include "fuelcen.h"
#include "powerup.h"
#include "hostage.h"
#include "weapon.h"
#include "newdemo.h"
#include "gameseq.h"
#include "automap.h"
#include "polyobj.h"
#include "text.h"
#include "gamefont.h"
#include "gamesave.h"
#include "fileutil.h"

#ifdef EDITOR
#ifdef SHAREWARE
char *Shareware_level_names[NUM_SHAREWARE_LEVELS] = {
	"level01.sdl",
	"level02.sdl",
	"level03.sdl",
	"level04.sdl",
	"level05.sdl",
	"level06.sdl",
	"level07.sdl"
};
#else
char *Shareware_level_names[NUM_SHAREWARE_LEVELS] = {
	"level01.rdl",
	"level02.rdl",
	"level03.rdl"
};
#endif

char *Registered_level_names[NUM_REGISTERED_LEVELS] = {
	"level08.rdl",
	"level09.rdl",
	"level10.rdl",
	"level11.rdl",
	"level12.rdl",
	"level13.rdl",
	"level14.rdl",
	"level15.rdl",
	"level16.rdl",
	"level17.rdl",
	"level18.rdl",
	"level19.rdl",
	"level20.rdl",
	"level21.rdl",
	"level22.rdl",
	"level23.rdl",
	"level24.rdl",
	"level25.rdl",
	"level26.rdl",
	"level27.rdl",
	"levels1.rdl",
	"levels2.rdl",
	"levels3.rdl"
};
#endif

char Gamesave_current_filename[128];
void dump_mine_info(void);

#define GAME_VERSION					25
#define GAME_COMPATIBLE_VERSION	22

#define MENU_CURSOR_X_MIN			MENU_X
#define MENU_CURSOR_X_MAX			MENU_X+6

#define HOSTAGE_DATA_VERSION	0

struct {
	ushort 	fileinfo_signature;
	ushort	fileinfo_version;
	int		fileinfo_sizeof;
} game_top_fileinfo;    // Should be same as first two fields below...

struct {
	ushort 	fileinfo_signature;
	ushort	fileinfo_version;
	int		fileinfo_sizeof;
	char	mine_filename[15];
	int		level;
	int		player_offset;				// Player info
	int		player_sizeof;
	int		object_offset;				// Object info
	int		object_howmany;    	
	int		object_sizeof;  
	int		walls_offset;
	int		walls_howmany;
	int		walls_sizeof;
	int		doors_offset;
	int		doors_howmany;
	int		doors_sizeof;
	int		triggers_offset;
	int		triggers_howmany;
	int		triggers_sizeof;
	int		links_offset;
	int		links_howmany;
	int		links_sizeof;
	int		control_offset;
	int		control_howmany;
	int		control_sizeof;
	int		matcen_offset;
	int		matcen_howmany;
	int		matcen_sizeof;
} game_fileinfo;

#ifdef EDITOR
extern char mine_filename[];
extern int save_mine_data_compiled(FILE * SaveFile);
//--unused-- #else
//--unused-- char mine_filename[128];
#endif

int Gamesave_num_org_robots = 0;
//--unused-- grs_bitmap * Gamesave_saved_bitmap = NULL;

#ifdef EDITOR
//	Return true if this level has a name of the form "level??"
//	Note that a pathspec can appear at the beginning of the filename.
int is_real_level(char *filename)
{
	int	len = strlen(filename);

	if (len < 6)
		return 0;

	//mprintf((0, "String = [%s]\n", &filename[len-11]));
	return !strnicmp(&filename[len-11], "level", 5);

}

void convert_name_to_CDL( char *dest, char *src )
{
	int i;

	strcpy (dest, src);

#ifdef SHAREWARE
	for (i=1; i<strlen(dest); i++ )
	{
		if (dest[i]=='.'||dest[i]==' '||dest[i]==0)
		{
			dest[i]='.';
			dest[i+1]='S';
			dest[i+2]= 'D';
			dest[i+3]= 'L';
			dest[i+4]=0;
			return;
		}
	}

	if (i < 123)
	{
		dest[i]='.';
		dest[i+1]='S';
		dest[i+2]= 'D';
		dest[i+3]= 'L';
		dest[i+4]=0;
		return;
	}
#else
	for (i=1; i<strlen(dest); i++ )
	{
		if (dest[i]=='.'||dest[i]==' '||dest[i]==0)
		{
			dest[i]='.';
			dest[i+1]='R';
			dest[i+2]= 'D';
			dest[i+3]= 'L';
			dest[i+4]=0;
			return;
		}
	}

	if (i < 123)
	{
		dest[i]='.';
		dest[i+1]='R';
		dest[i+2]= 'D';
		dest[i+3]= 'L';
		dest[i+4]=0;
		return;
	}
#endif




}
#endif

void convert_name_to_LVL( char *dest, char *src )
{
	int i;

	strcpy (dest, src);

	for (i=1; i<strlen(dest); i++ )
	{
		if (dest[i]=='.'||dest[i]==' '||dest[i]==0)
		{
			dest[i]='.';
			dest[i+1]='L';
			dest[i+2]= 'V';
			dest[i+3]= 'L';
			dest[i+4]=0;
			return;
		}
	}

	if (i < 123)
	{
		dest[i]='.';
		dest[i+1]='L';
		dest[i+2]= 'V';
		dest[i+3]= 'L';
		dest[i+4]=0;
		return;
	}
}

//--unused-- vms_angvec zero_angles={0,0,0};

#define vm_angvec_zero(v) do {(v)->p=(v)->b=(v)->h=0;} while (0)

int Gamesave_num_players=0;

int N_save_pof_names=25;
char Save_pof_names[MAX_POLYGON_MODELS][13];

check_and_fix_matrix(vms_matrix *m);

void verify_object( object * obj )	{

	obj->lifeleft = IMMORTAL_TIME;		//all loaded object are immortal, for now

	if ( obj->type == OBJ_ROBOT )	{
		Gamesave_num_org_robots++;

		// Make sure valid id...
		if ( obj->id >= N_robot_types )
			obj->id = obj->id % N_robot_types;

		// Make sure model number & size are correct...		
		if ( obj->render_type == RT_POLYOBJ ) {
			obj->rtype.pobj_info.model_num = Robot_info[obj->id].model_num;
			obj->size = Polygon_models[obj->rtype.pobj_info.model_num].rad;

			//@@if (obj->control_type==CT_AI && Robot_info[obj->id].attack_type)
			//@@	obj->size = obj->size*3/4;
		}

		if (obj->movement_type == MT_PHYSICS) {
			obj->mtype.phys_info.mass = Robot_info[obj->id].mass;
			obj->mtype.phys_info.drag = Robot_info[obj->id].drag;
		}
	}
	else {		//Robots taken care of above

		if ( obj->render_type == RT_POLYOBJ ) {
			int i;
			char *name = Save_pof_names[obj->rtype.pobj_info.model_num];

			for (i=0;i<N_polygon_models;i++)
				if (!stricmp(Pof_names[i],name)) {		//found it!	
					// mprintf((0,"Mapping <%s> to %d (was %d)\n",name,i,obj->rtype.pobj_info.model_num));
					obj->rtype.pobj_info.model_num = i;
					break;
				}
		}
	}

	if ( obj->type == OBJ_POWERUP ) {
		if ( obj->id >= N_powerup_types )	{
			obj->id = 0;
			Assert( obj->render_type != RT_POLYOBJ );
		}
		obj->control_type = CT_POWERUP;

		obj->size = Powerup_info[obj->id].size;
	}

	//if ( obj->type == OBJ_HOSTAGE )	{
	//	if ( obj->id >= N_hostage_types )	{
	//		obj->id = 0;
	//		Assert( obj->render_type == RT_POLYOBJ );
	//	}
	//}

	if ( obj->type == OBJ_WEAPON )	{
		if ( obj->id >= N_weapon_types )	{
			obj->id = 0;
			Assert( obj->render_type != RT_POLYOBJ );
		}
	}

	if ( obj->type == OBJ_CNTRLCEN )	{
		int i;

		obj->render_type = RT_POLYOBJ;
		obj->control_type = CT_CNTRLCEN;

		// Make model number is correct...	
		for (i=0; i<Num_total_object_types; i++ )	
			if ( ObjType[i] == OL_CONTROL_CENTER )		{
				obj->rtype.pobj_info.model_num = ObjId[i];
				obj->shields = ObjStrength[i];
				break;		
			}
	}

	if ( obj->type == OBJ_PLAYER )	{
		//int i;

		//Assert(obj == Player);

		if ( obj == ConsoleObject )		
			init_player_object();
		else
			if (obj->render_type == RT_POLYOBJ)	//recover from Matt's pof file matchup bug
				obj->rtype.pobj_info.model_num = Player_ship->model_num;

		//Make sure orient matrix is orthogonal
		check_and_fix_matrix(&obj->orient);

		obj->id = Gamesave_num_players++;
	}

	if (obj->type == OBJ_HOSTAGE) {

		if (obj->id > N_hostage_types)
			obj->id = 0;

		obj->render_type = RT_HOSTAGE;
		obj->control_type = CT_POWERUP;
		//obj->vclip_info.vclip_num = Hostage_vclip_num[Hostages[obj->id].type];
		//obj->vclip_info.frametime = Vclip[obj->vclip_info.vclip_num].frame_time;
		//obj->vclip_info.framenum = 0;
	}

}

static short read_fixang(CFILE *file)
{
	return (fixang)read_short_swap(file);
}

static void read_vector(vms_vector *v,CFILE *file)
{
	v->x = read_fix_swap(file);
	v->y = read_fix_swap(file);
	v->z = read_fix_swap(file);
}

static void read_matrix(vms_matrix *m,CFILE *file)
{
	read_vector(&m->rvec,file);
	read_vector(&m->uvec,file);
	read_vector(&m->fvec,file);
}

static void read_angvec(vms_angvec *v,CFILE *file)
{
	v->p = read_fixang(file);
	v->b = read_fixang(file);
	v->h = read_fixang(file);
}

//reads one object of the given version from the given file
read_object(object *obj,CFILE *f,int version)
{
	obj->type				= read_byte(f);
	obj->id					= read_byte(f);

	obj->control_type		= read_byte(f);
	obj->movement_type	= read_byte(f);
	obj->render_type		= read_byte(f);
	obj->flags				= read_byte(f);

	obj->segnum				= read_short_swap(f);
	obj->attached_obj		= -1;

	read_vector(&obj->pos,f);
	read_matrix(&obj->orient,f);

	obj->size				= read_fix_swap(f);
	obj->shields			= read_fix_swap(f);

	read_vector(&obj->last_pos,f);

	obj->contains_type	= read_byte(f);
	obj->contains_id		= read_byte(f);
	obj->contains_count	= read_byte(f);

	switch (obj->movement_type) {

		case MT_PHYSICS:

			read_vector(&obj->mtype.phys_info.velocity,f);
			read_vector(&obj->mtype.phys_info.thrust,f);

			obj->mtype.phys_info.mass		= read_fix_swap(f);
			obj->mtype.phys_info.drag		= read_fix_swap(f);
			obj->mtype.phys_info.brakes		= read_fix_swap(f);

			read_vector(&obj->mtype.phys_info.rotvel,f);
			read_vector(&obj->mtype.phys_info.rotthrust,f);

			obj->mtype.phys_info.turnroll	= read_fixang(f);
			obj->mtype.phys_info.flags		= read_short_swap(f);

			break;

		case MT_SPINNING:

			read_vector(&obj->mtype.spin_rate,f);
			break;

		case MT_NONE:
			break;

		default:
			Int3();
	}

	switch (obj->control_type) {

		case CT_AI: {
			int i;

			obj->ctype.ai_info.behavior				= read_byte(f);

			for (i=0;i<MAX_AI_FLAGS;i++)
				obj->ctype.ai_info.flags[i]			= read_byte(f);

			obj->ctype.ai_info.hide_segment			= read_short_swap(f);
			obj->ctype.ai_info.hide_index			= read_short_swap(f);
			obj->ctype.ai_info.path_length			= read_short_swap(f);
			obj->ctype.ai_info.cur_path_index		= read_short_swap(f);

			obj->ctype.ai_info.follow_path_start_seg	= read_short_swap(f);
			obj->ctype.ai_info.follow_path_end_seg		= read_short_swap(f);

			break;
		}

		case CT_EXPLOSION:

			obj->ctype.expl_info.spawn_time		= read_fix_swap(f);
			obj->ctype.expl_info.delete_time	= read_fix_swap(f);
			obj->ctype.expl_info.delete_objnum	= read_short_swap(f);
			obj->ctype.expl_info.next_attach = obj->ctype.expl_info.prev_attach = obj->ctype.expl_info.attach_parent = -1;

			break;

		case CT_WEAPON:

			//do I really need to read these?  Are they even saved to disk?

			obj->ctype.laser_info.parent_type		= read_short_swap(f);
			obj->ctype.laser_info.parent_num		= read_short_swap(f);
			obj->ctype.laser_info.parent_signature	= read_int_swap(f);

			break;

		case CT_LIGHT:

			obj->ctype.light_info.intensity = read_fix_swap(f);
			break;

		case CT_POWERUP:

			if (version >= 25)
				obj->ctype.powerup_info.count = read_int_swap(f);
			else
				obj->ctype.powerup_info.count = 1;

			if (obj->id == POW_VULCAN_WEAPON)
					obj->ctype.powerup_info.count = VULCAN_WEAPON_AMMO_AMOUNT;

			break;


		case CT_NONE:
		case CT_FLYING:
		case CT_DEBRIS:
			break;

		case CT_SLEW:		//the player is generally saved as slew
			break;

		case CT_CNTRLCEN:
			break;

		case CT_MORPH:
		case CT_FLYTHROUGH:
		case CT_REPAIRCEN:
		default:
			Int3();
	
	}

	switch (obj->render_type) {

		case RT_NONE:
			break;

		case RT_MORPH:
		case RT_POLYOBJ: {
			int i,tmo;

			obj->rtype.pobj_info.model_num		= read_int_swap(f);

			for (i=0;i<MAX_SUBMODELS;i++)
				read_angvec(&obj->rtype.pobj_info.anim_angles[i],f);

			obj->rtype.pobj_info.subobj_flags	= read_int_swap(f);

			tmo = read_int_swap(f);

			#ifndef EDITOR
			obj->rtype.pobj_info.tmap_override	= tmo;
			#else
			if (tmo==-1)
				obj->rtype.pobj_info.tmap_override	= -1;
			else {
				int xlated_tmo = tmap_xlate_table[tmo];
				if (xlated_tmo < 0)	{
					mprintf( (0, "Couldn't find texture for demo object, model_num = %d\n", obj->rtype.pobj_info.model_num));
					Int3();
					xlated_tmo = 0;
				}
				obj->rtype.pobj_info.tmap_override	= xlated_tmo;
			}
			#endif

			obj->rtype.pobj_info.alt_textures	= 0;

			break;
		}

		case RT_WEAPON_VCLIP:
		case RT_HOSTAGE:
		case RT_POWERUP:
		case RT_FIREBALL:

			obj->rtype.vclip_info.vclip_num	= read_int_swap(f);
			obj->rtype.vclip_info.frametime	= read_fix_swap(f);
			obj->rtype.vclip_info.framenum	= read_byte(f);

			break;

		case RT_LASER:
			break;

		default:
			Int3();

	}

}

// -----------------------------------------------------------------------------
// Load game 
// Loads all the relevant data for a level.
// If level != -1, it loads the filename with extension changed to .min
// Otherwise it loads the appropriate level mine.
// returns 0=everything ok, 1=old version, -1=error
load_game_data(CFILE *LoadFile)
{
	int i,j;
	int start_offset;

	start_offset = cftell(LoadFile);

	//===================== READ FILE INFO ========================

	// Set default values
	game_fileinfo.level					=	-1;
	game_fileinfo.player_offset		=	-1;
	game_fileinfo.player_sizeof		=	sizeof(player);
 	game_fileinfo.object_offset		=	-1;
	game_fileinfo.object_howmany		=	0;
	game_fileinfo.object_sizeof		=	sizeof(object);  
	game_fileinfo.walls_offset			=	-1;
	game_fileinfo.walls_howmany		=	0;
	game_fileinfo.walls_sizeof			=	sizeof(wall);  
	game_fileinfo.doors_offset			=	-1;
	game_fileinfo.doors_howmany		=	0;
	game_fileinfo.doors_sizeof			=	sizeof(active_door);  
	game_fileinfo.triggers_offset		=	-1;
	game_fileinfo.triggers_howmany	=	0;
	game_fileinfo.triggers_sizeof		=	sizeof(trigger);  
	game_fileinfo.control_offset		=	-1;
	game_fileinfo.control_howmany		=	0;
	game_fileinfo.control_sizeof		=	sizeof(control_center_triggers);
	game_fileinfo.matcen_offset		=	-1;
	game_fileinfo.matcen_howmany		=	0;
	game_fileinfo.matcen_sizeof		=	sizeof(matcen_info);

	if (cfseek(LoadFile, start_offset, SEEK_SET))
		Error("Error seeking in gamesave.c");
		
	// Read in game_top_fileinfo to get size of saved fileinfo.
	game_top_fileinfo.fileinfo_signature = read_short_swap(LoadFile);
	game_top_fileinfo.fileinfo_version = read_short_swap(LoadFile);
	game_top_fileinfo.fileinfo_sizeof = read_int_swap(LoadFile);

	// Check signature
	if (game_top_fileinfo.fileinfo_signature != 0x6705)
		return -1;

	// Check version number
	if (game_top_fileinfo.fileinfo_version < GAME_COMPATIBLE_VERSION )
		return -1;

	// Now, Read in the fileinfo
	if (cfseek( LoadFile, start_offset, SEEK_SET )) 
		Error( "Error seeking to game_fileinfo in gamesave.c" );

	game_fileinfo.fileinfo_signature = read_short_swap(LoadFile);

	game_fileinfo.fileinfo_version = read_short_swap(LoadFile);
	game_fileinfo.fileinfo_sizeof = read_int_swap(LoadFile);
	for(i=0; i<15; i++)
		game_fileinfo.mine_filename[i] = read_byte(LoadFile);
	game_fileinfo.level = read_int_swap(LoadFile);
	game_fileinfo.player_offset = read_int_swap(LoadFile);				// Player info
	game_fileinfo.player_sizeof = read_int_swap(LoadFile);
	game_fileinfo.object_offset = read_int_swap(LoadFile);				// Object info
	game_fileinfo.object_howmany = read_int_swap(LoadFile);    	
	game_fileinfo.object_sizeof = read_int_swap(LoadFile);  
	game_fileinfo.walls_offset = read_int_swap(LoadFile);
	game_fileinfo.walls_howmany = read_int_swap(LoadFile);
	game_fileinfo.walls_sizeof = read_int_swap(LoadFile);
	game_fileinfo.doors_offset = read_int_swap(LoadFile);
	game_fileinfo.doors_howmany = read_int_swap(LoadFile);
	game_fileinfo.doors_sizeof = read_int_swap(LoadFile);
	game_fileinfo.triggers_offset = read_int_swap(LoadFile);
	game_fileinfo.triggers_howmany = read_int_swap(LoadFile);
	game_fileinfo.triggers_sizeof = read_int_swap(LoadFile);
	game_fileinfo.links_offset = read_int_swap(LoadFile);
	game_fileinfo.links_howmany = read_int_swap(LoadFile);
	game_fileinfo.links_sizeof = read_int_swap(LoadFile);
	game_fileinfo.control_offset = read_int_swap(LoadFile);
	game_fileinfo.control_howmany = read_int_swap(LoadFile);
	game_fileinfo.control_sizeof = read_int_swap(LoadFile);
	game_fileinfo.matcen_offset = read_int_swap(LoadFile);
	game_fileinfo.matcen_howmany = read_int_swap(LoadFile);
	game_fileinfo.matcen_sizeof = read_int_swap(LoadFile);

	if (game_top_fileinfo.fileinfo_version >= 14) {	//load mine filename
		char *p=Current_level_name;
		//must do read one char at a time, since no cfgets()
		do *p = cfgetc(LoadFile); while (*p++!=0);
	}
	else
		Current_level_name[0]=0;

	if (game_top_fileinfo.fileinfo_version >= 19) {	//load pof names
		N_save_pof_names = read_short_swap(LoadFile);
		cfread(Save_pof_names,N_save_pof_names,13,LoadFile);
	}

	//===================== READ PLAYER INFO ==========================
	Object_next_signature = 0;

	//===================== READ OBJECT INFO ==========================

	Gamesave_num_org_robots = 0;
	Gamesave_num_players = 0;

	if (game_fileinfo.object_offset > -1) {
		if (cfseek( LoadFile, game_fileinfo.object_offset, SEEK_SET )) 
			Error( "Error seeking to object_offset in gamesave.c" );
	
		for (i=0;i<game_fileinfo.object_howmany;i++)	{
			memset(&(Objects[i]), 0, sizeof(object));
			read_object(&Objects[i],LoadFile,game_top_fileinfo.fileinfo_version);

			Objects[i].signature = Object_next_signature++;
			verify_object( &Objects[i] );
		}

	}

	//===================== READ WALL INFO ============================

	if (game_fileinfo.walls_offset > -1)
	{

		if (!cfseek( LoadFile, game_fileinfo.walls_offset,SEEK_SET ))	{
			for (i=0;i<game_fileinfo.walls_howmany;i++) {
				Assert(sizeof(Walls[i]) == game_fileinfo.walls_sizeof);

				Walls[i].segnum = read_int_swap(LoadFile);
				Walls[i].sidenum = read_int_swap(LoadFile);
				Walls[i].hps = read_fix_swap(LoadFile);
				Walls[i].linked_wall = read_int_swap(LoadFile);
				Walls[i].type = read_byte(LoadFile);
				Walls[i].flags = read_byte(LoadFile);
				Walls[i].state = read_byte(LoadFile);
				Walls[i].trigger = read_byte(LoadFile);
				Walls[i].clip_num = read_byte(LoadFile);
				Walls[i].keys = read_byte(LoadFile);
				Walls[i].pad = read_short_swap(LoadFile);
			}
		}
	}

	//===================== READ DOOR INFO ============================

	if (game_fileinfo.doors_offset > -1)
	{
		if (!cfseek( LoadFile, game_fileinfo.doors_offset,SEEK_SET ))	{
			for (i=0;i<game_fileinfo.doors_howmany;i++) {
				Assert(sizeof(ActiveDoors[i]) == game_fileinfo.doors_sizeof);

				ActiveDoors[i].n_parts = read_int_swap(LoadFile);
				ActiveDoors[i].front_wallnum[0] = read_short_swap(LoadFile);
				ActiveDoors[i].front_wallnum[1] = read_short_swap(LoadFile);
				ActiveDoors[i].back_wallnum[0] = read_short_swap(LoadFile);
				ActiveDoors[i].back_wallnum[1] = read_short_swap(LoadFile);
				ActiveDoors[i].time = read_fix_swap(LoadFile);
			}
		}
	}

	//==================== READ TRIGGER INFO ==========================
	if (game_fileinfo.triggers_offset > -1)		{
		if (!cfseek( LoadFile, game_fileinfo.triggers_offset,SEEK_SET ))	{
			for (i=0;i<game_fileinfo.triggers_howmany;i++)	{
				Triggers[i].type = read_byte(LoadFile);
				Triggers[i].flags = read_short_swap(LoadFile);
				Triggers[i].value = read_int_swap(LoadFile);
				Triggers[i].time = read_int_swap(LoadFile);
				Triggers[i].link_num = read_byte(LoadFile);
				Triggers[i].num_links = read_short_swap(LoadFile);
				for (j=0; j<MAX_WALLS_PER_LINK; j++ )	
					Triggers[i].seg[j] = read_short_swap(LoadFile);
				for (j=0; j<MAX_WALLS_PER_LINK; j++ )
					Triggers[i].side[j] = read_short_swap(LoadFile);
			}
		}
	}

	//================ READ CONTROL CENTER TRIGGER INFO ===============

	if (game_fileinfo.control_offset > -1)
	{
		if (!cfseek( LoadFile, game_fileinfo.control_offset,SEEK_SET ))	{
			for (i=0;i<game_fileinfo.control_howmany;i++) {
				ControlCenterTriggers.num_links = read_short_swap(LoadFile);
				for (j=0; j<MAX_WALLS_PER_LINK; j++ )
					ControlCenterTriggers.seg[j] = read_short_swap( LoadFile );
				for (j=0; j<MAX_WALLS_PER_LINK; j++ )
					ControlCenterTriggers.side[j] = read_short_swap( LoadFile );
			}
		}
	}


	//================ READ MATERIALOGRIFIZATIONATORS INFO ===============

	if (game_fileinfo.matcen_offset > -1)
	{	int	j;

		if (!cfseek( LoadFile, game_fileinfo.matcen_offset,SEEK_SET ))	{
			// mprintf((0, "Reading %i materialization centers.\n", game_fileinfo.matcen_howmany));
			for (i=0;i<game_fileinfo.matcen_howmany;i++) {
				RobotCenters[i].robot_flags = read_int_swap(LoadFile);
				RobotCenters[i].hit_points = read_fix_swap(LoadFile);
				RobotCenters[i].interval = read_fix_swap(LoadFile);
				RobotCenters[i].segnum = read_short_swap(LoadFile);
				RobotCenters[i].fuelcen_num = read_short_swap(LoadFile);

				for (j=0; j<=Highest_segment_index; j++)
					if (Segments[j].special == SEGMENT_IS_ROBOTMAKER)
						if (Segments[j].matcen_num == i)
							RobotCenters[i].fuelcen_num = Segments[j].value;

				// mprintf((0, "   %i: flags = %08x\n", i, RobotCenters[i].robot_flags));
			}
		}
	}


	//========================= UPDATE VARIABLES ======================

	reset_objects(game_fileinfo.object_howmany);

	for (i=0; i<MAX_OBJECTS; i++) {
		Objects[i].next = Objects[i].prev = -1;
		if (Objects[i].type != OBJ_NONE) {
			int objsegnum = Objects[i].segnum;

			if (objsegnum > Highest_segment_index)		//bogus object
				Objects[i].type = OBJ_NONE;
			else {
				Objects[i].segnum = -1;			//avoid Assert()
				obj_link(i,objsegnum);
			}
		}
	}

	clear_transient_objects(1);		//1 means clear proximity bombs

	// Make sure non-transparent doors are set correctly.
	for (i=0; i< Num_segments; i++)
		for (j=0;j<MAX_SIDES_PER_SEGMENT;j++) {
			side	*sidep = &Segments[i].sides[j];
			if ((sidep->wall_num != -1) && (Walls[sidep->wall_num].clip_num != -1)) {
				//mprintf((0, "Checking Wall %d\n", Segments[i].sides[j].wall_num));
				if (WallAnims[Walls[sidep->wall_num].clip_num].flags & WCF_TMAP1) {
					//mprintf((0, "Fixing non-transparent door.\n"));
					sidep->tmap_num = WallAnims[Walls[sidep->wall_num].clip_num].frames[0];
					sidep->tmap_num2 = 0;
				}
			}
		}


	Num_walls = game_fileinfo.walls_howmany;
	reset_walls();

	Num_open_doors = game_fileinfo.doors_howmany;
	Num_triggers = game_fileinfo.triggers_howmany;

	Num_robot_centers = game_fileinfo.matcen_howmany;

	//fix old wall structs
	if (game_top_fileinfo.fileinfo_version < 17) {
		int segnum,sidenum,wallnum;

		for (segnum=0; segnum<=Highest_segment_index; segnum++)
			for (sidenum=0;sidenum<6;sidenum++)
				if ((wallnum=Segments[segnum].sides[sidenum].wall_num) != -1) {
					Walls[wallnum].segnum = segnum;
					Walls[wallnum].sidenum = sidenum;
				}
	}

	#ifndef NDEBUG
	{
		int	sidenum;
		for (sidenum=0; sidenum<6; sidenum++) {
			int	wallnum = Segments[Highest_segment_index].sides[sidenum].wall_num;
			if (wallnum != -1)
				if ((Walls[wallnum].segnum != Highest_segment_index) || (Walls[wallnum].sidenum != sidenum))
					Int3();	//	Error.  Bogus walls in this segment.
								// Consult Yuan or Mike.
		}
	}
	#endif

	//create_local_segment_data();

	fix_object_segs();

	#ifndef NDEBUG
	dump_mine_info();
	#endif

	if (game_top_fileinfo.fileinfo_version < GAME_VERSION)
		return 1;		//means old version
	else
		return 0;
}


int check_segment_connections(void);

// -----------------------------------------------------------------------------
//loads from an already-open file
// returns 0=everything ok, 1=old version, -1=error
int load_mine_data(CFILE *LoadFile);
int load_mine_data_compiled(CFILE *LoadFile);

#define LEVEL_FILE_VERSION		1

#ifndef RELEASE
char *Level_being_loaded=NULL;
#endif

#ifdef COMPACT_SEGS
extern void ncache_flush();
#endif

//loads a level (.LVL) file from disk
int load_level(char * filename_passed)
{
	#ifdef EDITOR
	int use_compiled_level=1;
	#endif
	CFILE * LoadFile;
	char filename[128];
	int sig,version,minedata_offset,gamedata_offset,hostagetext_offset;
	int mine_err,game_err;

	#ifdef COMPACT_SEGS
	ncache_flush();
	#endif

	#ifndef RELEASE
	Level_being_loaded = filename_passed;
	#endif

	strcpy(filename,filename_passed);

	#ifdef EDITOR
	//check extension to see what file type this is
	strupr(filename);

	if (strstr(filename,".LVL"))
		use_compiled_level = 0;
		#ifdef SHAREWARE
	else if (!strstr(filename,".SDL")) {
		convert_name_to_CDL(filename,filename_passed);
		use_compiled_level = 1;
	}
		#else
	else if (!strstr(filename,".RDL")) {
		convert_name_to_CDL(filename,filename_passed);
		use_compiled_level = 1;
	}
		#endif

	// If we're trying to load a CDL, and we can't find it, and we have
	// the editor compiled in, then load the LVL.
	if ( (!cfexist(filename)) && use_compiled_level )	{
		convert_name_to_LVL(filename,filename_passed);
		use_compiled_level = 0;
	}		
	#endif

	LoadFile = cfopen( filename, "rb" );
//CF_READ_MODE );

	if (!LoadFile) {			// couldn't open it from hog -- check data directory
		strcpy(filename, ":Data:");
		strcat(filename, filename_passed);
		LoadFile = cfopen( filename, "rb" );
	}
	
	if (!LoadFile)
		Error("Can't open file <%s>\n",filename);

	strcpy( Gamesave_current_filename, filename );

//	#ifdef NEWDEMO
//	if ( Newdemo_state == ND_STATE_RECORDING )
//		newdemo_record_start_demo();
//	#endif

	sig					= read_int_swap(LoadFile);
	version				= read_int_swap(LoadFile);
	minedata_offset		= read_int_swap(LoadFile);
	gamedata_offset		= read_int_swap(LoadFile);
	hostagetext_offset	= read_int_swap(LoadFile);

	Assert(sig == 'PLVL');

	cfseek(LoadFile,minedata_offset,SEEK_SET);
	#ifdef EDITOR
	if (!use_compiled_level)
		mine_err = load_mine_data(LoadFile);
	else
	#endif
		//NOTE LINK TO ABOVE!!
		mine_err = load_mine_data_compiled(LoadFile);

	if (mine_err == -1)	//error!!
		return 1;

	cfseek(LoadFile,gamedata_offset,SEEK_SET);
	game_err = load_game_data(LoadFile);

	if (game_err == -1)	//error!!
		return 1;

	#ifdef HOSTAGE_FACES
	cfseek(LoadFile,hostagetext_offset,SEEK_SET);
	load_hostage_data(LoadFile,(version>=1));
	#endif

	//======================== CLOSE FILE =============================

	cfclose( LoadFile );

	#ifdef EDITOR
	write_game_text_file(filename);
	if (Errors_in_mine) {
		if (is_real_level(filename)) {
			char  ErrorMessage[200];

			sprintf( ErrorMessage, "Warning: %i errors in %s!\n", Errors_in_mine, Level_being_loaded );
			stop_time();
			gr_palette_load(gr_palette);
			nm_messagebox( NULL, 1, "Continue", ErrorMessage );
			start_time();
		} else
			mprintf((1, "Error: %i errors in %s.\n", Errors_in_mine, Level_being_loaded));
	}
	#endif

	#ifdef EDITOR
	//If an old version, ask the use if he wants to save as new version
	if (((LEVEL_FILE_VERSION>1) && version<LEVEL_FILE_VERSION) || mine_err==1 || game_err==1) {
		char  ErrorMessage[200];

		sprintf( ErrorMessage, "You just loaded a old version level.  Would\n"
						"you like to save it as a current version level?");

		stop_time();
		gr_palette_load(gr_palette);
		if (nm_messagebox( NULL, 2, "Don't Save", "Save", ErrorMessage )==1)
			save_level(filename);
		start_time();
	}
	#endif

	#ifdef EDITOR
	if (Function_mode == FMODE_EDITOR)
		editor_status("Loaded NEW mine %s, \"%s\"",filename,Current_level_name);
	#endif

	#ifdef EDITOR
	if (check_segment_connections())
		nm_messagebox( "ERROR", 1, "Ok", 
				"Connectivity errors detected in\n"
				"mine.  See monochrome screen for\n"
				"details, and contact Matt or Mike." );
	#endif

	return 0;
}

#ifdef EDITOR
void get_level_name()
{
//NO_UI!!!	UI_WINDOW 				*NameWindow = NULL;
//NO_UI!!!	UI_GADGET_INPUTBOX	*NameText;
//NO_UI!!!	UI_GADGET_BUTTON 		*QuitButton;
//NO_UI!!!
//NO_UI!!!	// Open a window with a quit button
//NO_UI!!!	NameWindow = ui_open_window( 20, 20, 300, 110, WIN_DIALOG );
//NO_UI!!!	QuitButton = ui_add_gadget_button( NameWindow, 150-24, 60, 48, 40, "Done", NULL );
//NO_UI!!!
//NO_UI!!!	ui_wprintf_at( NameWindow, 10, 12,"Please enter a name for this mine:" );
//NO_UI!!!	NameText = ui_add_gadget_inputbox( NameWindow, 10, 30, LEVEL_NAME_LEN, LEVEL_NAME_LEN, Current_level_name );
//NO_UI!!!
//NO_UI!!!	NameWindow->keyboard_focus_gadget = (UI_GADGET *)NameText;
//NO_UI!!!	QuitButton->hotkey = KEY_ENTER;
//NO_UI!!!
//NO_UI!!!	ui_gadget_calc_keys(NameWindow);
//NO_UI!!!
//NO_UI!!!	while (!QuitButton->pressed && last_keypress!=KEY_ENTER) {
//NO_UI!!!		ui_mega_process();
//NO_UI!!!		ui_window_do_gadgets(NameWindow);
//NO_UI!!!	}
//NO_UI!!!
//NO_UI!!!	strcpy( Current_level_name, NameText->text );
//NO_UI!!!
//NO_UI!!!	if ( NameWindow!=NULL )	{
//NO_UI!!!		ui_close_window( NameWindow );
//NO_UI!!!		NameWindow = NULL;
//NO_UI!!!	}
//NO_UI!!!

	newmenu_item m[2];

	m[0].type = NM_TYPE_TEXT; m[0].text = "Please enter a name for this mine:";
	m[1].type = NM_TYPE_INPUT; m[1].text = Current_level_name; m[1].text_len = LEVEL_NAME_LEN;

	newmenu_do( NULL, "Enter mine name", 2, m, NULL );

}
#endif


#ifdef EDITOR

int	Errors_in_mine;

// -----------------------------------------------------------------------------
// Save game
int save_game_data(FILE * SaveFile)
{
	int  player_offset, object_offset, walls_offset, doors_offset, triggers_offset, control_offset, matcen_offset; //, links_offset;
	int start_offset,end_offset;

	start_offset = ftell(SaveFile);

	//===================== SAVE FILE INFO ========================

	game_fileinfo.fileinfo_signature =	0x6705;
	game_fileinfo.fileinfo_version	=	GAME_VERSION;
	game_fileinfo.level					=  Current_level_num;
	game_fileinfo.fileinfo_sizeof		=	sizeof(game_fileinfo);
	game_fileinfo.player_offset		=	-1;
	game_fileinfo.player_sizeof		=	sizeof(player);
	game_fileinfo.object_offset		=	-1;
	game_fileinfo.object_howmany		=	Highest_object_index+1;
	game_fileinfo.object_sizeof		=	sizeof(object);
	game_fileinfo.walls_offset			=	-1;
	game_fileinfo.walls_howmany		=	Num_walls;
	game_fileinfo.walls_sizeof			=	sizeof(wall);
	game_fileinfo.doors_offset			=	-1;
	game_fileinfo.doors_howmany		=	Num_open_doors;
	game_fileinfo.doors_sizeof			=	sizeof(active_door);
	game_fileinfo.triggers_offset		=	-1;
	game_fileinfo.triggers_howmany	=	Num_triggers;
	game_fileinfo.triggers_sizeof		=	sizeof(trigger);
	game_fileinfo.control_offset		=	-1;
	game_fileinfo.control_howmany		=  1;
	game_fileinfo.control_sizeof		=  sizeof(control_center_triggers);
 	game_fileinfo.matcen_offset		=	-1;
	game_fileinfo.matcen_howmany		=	Num_robot_centers;
	game_fileinfo.matcen_sizeof		=	sizeof(matcen_info);

	// Write the fileinfo
	fwrite( &game_fileinfo, sizeof(game_fileinfo), 1, SaveFile );

	// Write the mine name
	fprintf(SaveFile,Current_level_name);
	fputc(0,SaveFile);		//terminator for string

	fwrite(&N_save_pof_names,2,1,SaveFile);
	fwrite(Pof_names,N_polygon_models,13,SaveFile);

	//==================== SAVE PLAYER INFO ===========================

	player_offset = ftell(SaveFile);
	fwrite( &Players[Player_num], sizeof(player), 1, SaveFile );

	//==================== SAVE OBJECT INFO ===========================

	object_offset = ftell(SaveFile);
	//fwrite( &Objects, sizeof(object), game_fileinfo.object_howmany, SaveFile );
	{
		int i;
		for (i=0;i<game_fileinfo.object_howmany;i++)
			write_object(&Objects[i],SaveFile);
	}

	//==================== SAVE WALL INFO =============================

	walls_offset = ftell(SaveFile);
	fwrite( Walls, sizeof(wall), game_fileinfo.walls_howmany, SaveFile );

	//==================== SAVE DOOR INFO =============================

	doors_offset = ftell(SaveFile);
	fwrite( ActiveDoors, sizeof(active_door), game_fileinfo.doors_howmany, SaveFile );

	//==================== SAVE TRIGGER INFO =============================

	triggers_offset = ftell(SaveFile);
	fwrite( Triggers, sizeof(trigger), game_fileinfo.triggers_howmany, SaveFile );

	//================ SAVE CONTROL CENTER TRIGGER INFO ===============

	control_offset = ftell(SaveFile);
	fwrite( &ControlCenterTriggers, sizeof(control_center_triggers), 1, SaveFile );


	//================ SAVE MATERIALIZATION CENTER TRIGGER INFO ===============

	matcen_offset = ftell(SaveFile);
	// mprintf((0, "Writing %i materialization centers\n", game_fileinfo.matcen_howmany));
	// { int i;
	// for (i=0; i<game_fileinfo.matcen_howmany; i++)
	// 	mprintf((0, "   %i: robot_flags = %08x\n", i, RobotCenters[i].robot_flags));
	// }
	fwrite( RobotCenters, sizeof(matcen_info), game_fileinfo.matcen_howmany, SaveFile );

	//============= REWRITE FILE INFO, TO SAVE OFFSETS ===============

	// Update the offset fields
	game_fileinfo.player_offset		=	player_offset;
	game_fileinfo.object_offset		=	object_offset;
	game_fileinfo.walls_offset			=	walls_offset;
	game_fileinfo.doors_offset			=	doors_offset;
	game_fileinfo.triggers_offset		=	triggers_offset;
	game_fileinfo.control_offset		=	control_offset;
	game_fileinfo.matcen_offset		=	matcen_offset;


	end_offset = ftell(SaveFile);

	// Write the fileinfo
	fseek(  SaveFile, start_offset, SEEK_SET );  // Move to TOF
	fwrite( &game_fileinfo, sizeof(game_fileinfo), 1, SaveFile );

	// Go back to end of data
	fseek(SaveFile,end_offset,SEEK_SET);

	return 0;
}

int save_mine_data(FILE * SaveFile);

// -----------------------------------------------------------------------------
// Save game
int save_level_sub(char * filename, int compiled_version)
{
	FILE * SaveFile;
	char temp_filename[128];
	int sig = 'PLVL',version=LEVEL_FILE_VERSION;
	int minedata_offset,gamedata_offset,hostagetext_offset;

	if ( !compiled_version )	{
		write_game_text_file(filename);

		if (Errors_in_mine) {
			if (is_real_level(filename)) {
				char  ErrorMessage[200];
	
				sprintf( ErrorMessage, "Warning: %i errors in this mine!\n", Errors_in_mine );
				stop_time();
				gr_palette_load(gr_palette);
	 
				if (nm_messagebox( NULL, 2, "Cancel Save", "Save", ErrorMessage )!=1)	{
					start_time();
					return 1;
				}
				start_time();
			} else
				mprintf((1, "Error: %i errors in this mine.  See the 'txm' file.\n", Errors_in_mine));
		}
		convert_name_to_LVL(temp_filename,filename);
	} else {
		convert_name_to_CDL(temp_filename,filename);
	}

	SaveFile = fopen( temp_filename, "wb" );
	if (!SaveFile)
	{
		char ErrorMessage[256];

		char fname[20];
		_splitpath( temp_filename, NULL, NULL, fname, NULL );

		sprintf( ErrorMessage, \
			"ERROR: Cannot write to '%s'.\nYou probably need to check out a locked\nversion of the file. You should save\nthis under a different filename, and then\ncheck out a locked copy by typing\n\'co -l %s.lvl'\nat the DOS prompt.\n" 
			, temp_filename, fname );
		stop_time();
		gr_palette_load(gr_palette);
		nm_messagebox( NULL, 1, "Ok", ErrorMessage );
		start_time();
		return 1;
	}

	if (Current_level_name[0] == 0)
		strcpy(Current_level_name,"Untitled");

	clear_transient_objects(1);		//1 means clear proximity bombs

	compress_objects();		//after this, Highest_object_index == num objects

	//make sure player is in a segment
	if (update_object_seg(&Objects[Players[0].objnum]) == 0) {
		if (ConsoleObject->segnum > Highest_segment_index)
			ConsoleObject->segnum = 0;
		compute_segment_center(&ConsoleObject->pos,&(Segments[ConsoleObject->segnum]));
	}
 
	fix_object_segs();

	//Write the header

	gs_write_int(sig,SaveFile);
	gs_write_int(version,SaveFile);

	//save placeholders
	gs_write_int(minedata_offset,SaveFile);
	gs_write_int(gamedata_offset,SaveFile);
	gs_write_int(hostagetext_offset,SaveFile);

	//Now write the damn data

	minedata_offset = ftell(SaveFile);
	if ( !compiled_version )	
		save_mine_data(SaveFile);
	else
		save_mine_data_compiled(SaveFile);
	gamedata_offset = ftell(SaveFile);
	save_game_data(SaveFile);
	hostagetext_offset = ftell(SaveFile);

	#ifdef HOSTAGE_FACES
	save_hostage_data(SaveFile);
	#endif

	fseek(SaveFile,sizeof(sig)+sizeof(version),SEEK_SET);
	gs_write_int(minedata_offset,SaveFile);
	gs_write_int(gamedata_offset,SaveFile);
	gs_write_int(hostagetext_offset,SaveFile);

	//==================== CLOSE THE FILE =============================
	fclose(SaveFile);

	if ( !compiled_version )	{
		if (Function_mode == FMODE_EDITOR)
			editor_status("Saved mine %s, \"%s\"",filename,Current_level_name);
	}

	return 0;

}

int save_level(char * filename)
{
	int r1;

	// Save normal version...
	r1 = save_level_sub(filename, 0);

	// Save compiled version...
	save_level_sub(filename, 1);

	return r1;
}


#ifdef HOSTAGE_FACES
void save_hostage_data(FILE * fp)
{
	int i,num_hostages=0;

	// Find number of hostages in mine...
	for (i=0; i<=Highest_object_index; i++ )	{
		int num;
		if ( Objects[i].type == OBJ_HOSTAGE )	{
			num = Objects[i].id;
			#ifndef SHAREWARE
			if (num<0 || num>=MAX_HOSTAGES || Hostage_face_clip[Hostages[num].vclip_num].num_frames<=0)
				num=0;
			#else
			num = 0;
			#endif
			if (num+1 > num_hostages)
				num_hostages = num+1;
		}
	}

	gs_write_int(HOSTAGE_DATA_VERSION,fp);

	for (i=0; i<num_hostages; i++ )	{
		gs_write_int(Hostages[i].vclip_num,fp);
		fputs(Hostages[i].text,fp);
		fputc('\n',fp);		//fgets wants a newline
	}
}
#endif	//HOSTAGE_FACES

#endif	//EDITOR

#ifndef NDEBUG
void dump_mine_info(void)
{
	int	segnum, sidenum;
	fix	min_u, max_u, min_v, max_v, min_l, max_l, max_sl;

	min_u = F1_0*1000;
	min_v = min_u;
	min_l = min_u;

	max_u = -min_u;
	max_v = max_u;
	max_l = max_u;

	max_sl = 0;

	for (segnum=0; segnum<=Highest_segment_index; segnum++) {
		for (sidenum=0; sidenum<MAX_SIDES_PER_SEGMENT; sidenum++) {
			int	vertnum;
			side	*sidep = &Segments[segnum].sides[sidenum];

			if (Segments[segnum].static_light > max_sl)
				max_sl = Segments[segnum].static_light;

			for (vertnum=0; vertnum<4; vertnum++) {
				if (sidep->uvls[vertnum].u < min_u)
					min_u = sidep->uvls[vertnum].u;
				else if (sidep->uvls[vertnum].u > max_u)
					max_u = sidep->uvls[vertnum].u;

				if (sidep->uvls[vertnum].v < min_v)
					min_v = sidep->uvls[vertnum].v;
				else if (sidep->uvls[vertnum].v > max_v)
					max_v = sidep->uvls[vertnum].v;

				if (sidep->uvls[vertnum].l < min_l)
					min_l = sidep->uvls[vertnum].l;
				else if (sidep->uvls[vertnum].l > max_l)
					max_l = sidep->uvls[vertnum].l;
			}

		}
	}

//	mprintf((0, "Smallest uvl = %7.3f %7.3f %7.3f.  Largest uvl = %7.3f %7.3f %7.3f\n", f2fl(min_u), f2fl(min_v), f2fl(min_l), f2fl(max_u), f2fl(max_v), f2fl(max_l)));
//	mprintf((0, "Static light maximum = %7.3f\n", f2fl(max_sl)));
//	mprintf((0, "Number of walls: %i\n", Num_walls));

}

#endif

#ifdef HOSTAGE_FACES
void load_hostage_data(CFILE * fp,int do_read)
{
	int version,i,num,num_hostages;

	hostage_init_all();

	num_hostages = 0;

	// Find number of hostages in mine...
	for (i=0; i<=Highest_object_index; i++ )	{
		if ( Objects[i].type == OBJ_HOSTAGE )	{
			num = Objects[i].id;
			if (num+1 > num_hostages)
				num_hostages = num+1;

			if (Hostages[num].objnum != -1) {		//slot already used
				num = hostage_get_next_slot();		//..so get new slot
				if (num+1 > num_hostages)
					num_hostages = num+1;
				Objects[i].id = num;
			}

			if ( num > -1 && num < MAX_HOSTAGES )	{
				Assert(Hostages[num].objnum == -1);		//make sure not used
				// -- Matt -- commented out by MK on 11/19/94, hit often in level 3, level 4.  Assert(Hostages[num].objnum == -1);		//make sure not used
				Hostages[num].objnum = i;
				Hostages[num].objsig = Objects[i].signature;
			}
		}
	}

	if (do_read) {
		version = read_int_swap(fp);

		for (i=0;i<num_hostages;i++) {

			Assert(Hostages[i].objnum != -1);		//make sure slot filled in

			Hostages[i].vclip_num = read_int_swap(fp);

			#ifndef SHAREWARE
			if (Hostages[i].vclip_num<0 || Hostages[i].vclip_num>=MAX_HOSTAGES || Hostage_face_clip[Hostages[i].vclip_num].num_frames<=0)
				Hostages[i].vclip_num=0;

			Assert(Hostage_face_clip[Hostages[i].vclip_num].num_frames);
			#endif

			cfgets(Hostages[i].text, HOSTAGE_MESSAGE_LEN, fp);

			if (Hostages[i].text[strlen(Hostages[i].text)-1]=='\n')
				Hostages[i].text[strlen(Hostages[i].text)-1] = 0;
		}
	}
	else
		for (i=0;i<num_hostages;i++) {
			Assert(Hostages[i].objnum != -1);		//make sure slot filled in
			Hostages[i].vclip_num = 0;
		}

}
#endif	//HOSTAGE_FACES

