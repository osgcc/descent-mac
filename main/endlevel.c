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
 * $Source: Smoke:miner:source:main::RCS:endlevel.c $
 * $Revision: 1.5 $
 * $Author: allender $
 * $Date: 1995/10/31 10:24:09 $
 * 
 * Code for rendering external scenes
 * 
 * $Log: endlevel.c $
 * Revision 1.5  1995/10/31  10:24:09  allender
 * shareware stuff
 *
 * Revision 1.4  1995/09/14  16:33:54  allender
 * fixed function return values for those that didn't
 * have them...thanks matt!
 *
 * Revision 1.3  1995/07/28  15:36:26  allender
 * reverse inverse sqrt change
 *
 * Revision 1.2  1995/07/28  15:17:40  allender
 * inverse magnitude fixup
 *
 * Revision 1.1  1995/05/16  15:24:32  allender
 * Initial revision
 *
 * Revision 2.2  1995/03/21  08:40:14  john
 * Ifdef'd out the NETWORK code.
 * 
 * Revision 2.1  1995/03/20  18:15:50  john
 * Added code to not store the normals in the segment structure.
 * 
 * Revision 2.0  1995/02/27  11:30:42  john
 * New version 2.0, which has no anonymous unions, builds with
 * Watcom 10.0, and doesn't require parsing BITMAPS.TBL.
 * 
 * Revision 1.80  1995/02/22  13:24:45  john
 * Removed the vecmat anonymous unions.
 * 
 * Revision 1.79  1995/02/11  12:41:54  john
 * Added new song method, with FM bank switching..
 * 
 * Revision 1.78  1995/02/08  11:37:41  mike
 * Check for failures in call to obj_create.
 * 
 * Revision 1.77  1995/02/05  22:09:49  matt
 * Switch out of rear view when starting endlevel sequence
 * 
 * Revision 1.76  1995/01/30  18:08:28  rob
 * Add palette fade out before ending level on special missions.
 * 
 * Revision 1.75  1995/01/29  16:19:19  rob
 * Fixed endlevel for custom missions.
 * 
 * Revision 1.74  1995/01/26  12:18:10  rob
 * Changed calling convention of network_do_frame.
 * 
 * Revision 1.73  1995/01/21  16:50:03  matt
 * Made endlevel work with new mission stuff
 * 
 * Revision 1.72  1994/12/20  18:22:51  john
 * Added code to support non-looping songs, and put
 * it in for endlevel and credits.
 * 
 * Revision 1.71  1994/12/15  12:23:58  matt
 * Added check for failure to create camera object
 * 
 * Revision 1.70  1994/12/15  03:05:28  matt
 * Added error checking for NULL return from object_create_explosion()
 * 
 * Revision 1.69  1994/12/12  21:41:38  matt
 * Don't start endlevel if OF_SHOULD_BE_DEAD is set for player
 * 
 * Revision 1.68  1994/12/12  15:44:54  rob
 * Rolled back a change to endlevel_start that caused more bugs than
 * it fixed.
 * 
 * Revision 1.67  1994/12/12  12:08:33  rob
 * IF a player is dead upon entering the tunnel, make them not dead.  Not perfect solution
 * but avoids some last-minute weirdness we want to fix.  This should be revisited in new
 * versions if possible!
 * 
 * Revision 1.66  1994/12/11  22:02:13  allender
 * made endlevel data loading work with .txb encoded format (made with
 * compbit -i level0?.end -o level0?.txb)
 * 
 * Revision 1.65  1994/12/11  20:32:47  matt
 * Made camera transition happen 1/3 of the way through exit tunnel
 * 
 * Revision 1.64  1994/12/08  20:56:27  john
 * More cfile stuff.
 * 
 * Revision 1.63  1994/12/07  17:00:52  rob
 * Trying to fix homing tone warning when in exit tunnel.
 * 
 * Revision 1.62  1994/12/06  13:24:47  matt
 * Made exit model come out of bitmaps.tbl
 * 
 * Revision 1.61  1994/12/06  12:06:22  matt
 * Fixed/cleaned up satellite (planet/sun) code
 * 
 * Revision 1.60  1994/12/05  13:37:12  adam
 * removed slew-mode
 * 
 * Revision 1.59  1994/12/05  12:49:37  matt
 * Made satellite a rod (instead of a plane old non-rotating bitmap), and
 * made the size settable in the .end file
 * 
 * Revision 1.58  1994/12/04  21:40:00  matt
 * Added explosion sounds
 * 
 * Revision 1.57  1994/12/04  18:31:41  matt
 * Wasn't coding planet position, causing it to disappear sometimes
 * 
 * Revision 1.56  1994/12/04  14:30:26  john
 * Added hooks for music..
 * 
 * Revision 1.55  1994/12/04  13:53:52  matt
 * Added code to make camera off-centered during lookback
 * 
 * Revision 1.54  1994/12/04  12:30:18  matt
 * Fixed slew for short sequence
 * 
 * Revision 1.53  1994/12/03  19:28:10  matt
 * Added alternate model for exit model after mine destruction
 * 
 * Revision 1.52  1994/12/03  00:17:23  matt
 * Made endlevel sequence cut off early
 * Made exit model and bit explosion always plot last (after all terrain)
 * 
 * Revision 1.51  1994/12/01  20:15:43  yuan
 * Localization.
 * 
 * Revision 1.50  1994/11/30  23:27:35  adam
 * mucked around carelessly
 * 
 * Revision 1.49  1994/11/28  21:50:37  mike
 * optimizations.
 * 
 * Revision 1.48  1994/11/28  00:12:05  allender
 * took out demo code that was in at one time to record endlevel sequence.
 * We are _not_ recording endlevel sequence
 * 
 * Revision 1.47  1994/11/27  23:35:54  allender
 * pause demo recording when starting endlevel sequence.  on demo playback,
 * don't do endlevel at all.
 * 
 * Revision 1.46  1994/11/27  23:13:59  matt
 * Made changes for new mprintf calling convention
 * 
 * Revision 1.45  1994/11/26  23:17:29  matt
 * When camera leaves mine, bank it so it's level with the ground
 * 
 * Revision 1.44  1994/11/23  16:52:13  rob
 * Ended netgame endlevel sequence a bit earlier.
 * 
 * Revision 1.43  1994/11/22  19:20:46  rob
 * Modem support for secret levels.
 * 
 * Revision 1.42  1994/11/22  12:11:03  rob
 * Fixed bug - file handle left open in load_endlevel_data.
 * 
 * Revision 1.41  1994/11/21  17:29:22  matt
 * Cleaned up sequencing & game saving for secret levels
 * 
 * Revision 1.40  1994/11/19  15:14:54  mike
 * remove unused code and data
 * 
 * Revision 1.39  1994/11/19  12:41:32  matt
 * Added system to read endlevel data from file, and to make it work
 * with any exit tunnel.
 * 
 * Revision 1.38  1994/11/17  15:02:24  mike
 * support new segment validation functions.
 * 
 * Revision 1.37  1994/11/17  13:04:45  allender
 * backout out newdemo changes
 * 
 * Revision 1.35  1994/11/16  14:52:33  rob
 * Commented out SLEW_ON on Matt's direction.
 * Changed something to fix demo recording.
 * 
 * Revision 1.34  1994/11/16  11:49:29  matt
 * Added code to rotate terrain to match mine
 * 
 * Revision 1.33  1994/11/14  17:54:54  allender
 * on exit sequence during demo recording, force player exited from mine
 * packet to all other network players
 * 
 * Revision 1.32  1994/11/10  21:27:42  matt
 * Took out printf's
 * 
 * Revision 1.31  1994/11/10  14:02:24  matt
 * Hacked in support for player ships with different textures
 * 
 * Revision 1.30  1994/11/09  10:31:33  matt
 * Don't create explosions if can't find seg to create them in
 * 
 * Revision 1.29  1994/11/05  17:22:37  john
 * Fixed lots of sequencing problems with newdemo stuff.
 * 
 * Revision 1.28  1994/11/03  11:10:39  matt
 * Fixed chase angles code
 * Maybe other things, too.
 * 
 * Revision 1.27  1994/10/30  20:09:21  matt
 * For endlevel: added big explosion at tunnel exit; made lights in tunnel 
 * go out; made more explosions on walls.
 * 
 * Revision 1.26  1994/10/28  16:37:50  allender
 * stop demo recording when endlevel sequence activated
 * 
 * Revision 1.25  1994/10/27  21:15:21  matt
 * Added explosions in mine chasing player
 * 
 * Revision 1.24  1994/10/27  01:03:57  matt
 * Fixed several small bugs in flythrough
 * 
 * Revision 1.23  1994/10/22  01:32:30  matt
 * Don't start endlevel sequence if player dead
 * 
 * Revision 1.22  1994/10/22  00:08:06  matt
 * Fixed up problems with bonus & game sequencing
 * Player doesn't get credit for hostages unless he gets them out alive
 * 
 * 
 * 
 */

#pragma off (unreferenced)
static char rcsid[] = "$Id: endlevel.c 1.5 1995/10/31 10:24:09 allender Exp $";
#pragma on (unreferenced)

//#define SLEW_ON 1

//#define _MARK_ON

#include <stdlib.h>
//#include <wsample.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

#include "3d.h"
#include "error.h"
#include "gr.h"
#include "palette.h"
#include "iff.h"
#include "mono.h"
#include "texmap.h"
#include "fvi.h"
#include "mem.h"
#include "sounds.h"

#include "inferno.h"
#include "endlevel.h"
#include "object.h"
#include "game.h"
#include "gauges.h"
#include "wall.h"
#include "terrain.h"
#include "polyobj.h"
#include "bm.h"
#include "gameseq.h"
#include "newdemo.h"
#include "multi.h"
#include "vclip.h"
#include "fireball.h"
#include "network.h"
#include "text.h"
#include "digi.h"
#include "cfile.h"
#include "compbit.h"
#include "songs.h"

typedef struct flythrough_data {
	object		*obj;
	vms_angvec	angles;			//orientation in angles
	vms_vector	step;				//how far in a second
	vms_vector	angstep;			//rotation per second
	fix			speed;			//how fast object is moving
	vms_vector 	headvec;			//where we want to be pointing
	int			first_time;		//flag for if first time through
	fix			offset_frac;	//how far off-center as portion of way
	fix			offset_dist;	//how far currently off-center
} flythrough_data;

//endlevel sequence states

#define EL_OFF				0		//not in endlevel
#define EL_FLYTHROUGH	1		//auto-flythrough in tunnel
#define EL_LOOKBACK		2		//looking back at player
#define EL_OUTSIDE		3		//flying outside for a while
#define EL_STOPPED		4		//stopped, watching explosion
#define EL_PANNING		5		//panning around, watching player
#define EL_CHASING		6		//chasing player to station

#define SHORT_SEQUENCE	1		//if defined, end sequnce when panning starts
//#define STATION_ENABLED	1		//if defined, load & use space station model

int Endlevel_sequence = 0;

extern fix player_speed;

int transition_segnum,exit_segnum;

object *endlevel_camera;

#define FLY_SPEED i2f(50)

#define FLY_ACCEL i2f(5)

fix cur_fly_speed,desired_fly_speed;

extern int matt_find_connect_side(int seg0,int seg1);

grs_bitmap *satellite_bitmap,*station_bitmap,*terrain_bitmap;	//!!*exit_bitmap,
vms_vector satellite_pos,satellite_upvec;
//!!grs_bitmap **exit_bitmap_list[1];
int station_modelnum,exit_modelnum,destroyed_exit_modelnum;

vms_vector station_pos = {0xf8c4<<10,0x3c1c<<12,0x372<<10};

#ifdef STATION_ENABLED
grs_bitmap *station_bitmap;
grs_bitmap **station_bitmap_list[1];
int station_modelnum;
#endif

vms_vector mine_exit_point;
vms_vector mine_ground_exit_point;
vms_vector mine_side_exit_point;
vms_matrix mine_exit_orient;

int outside_mine;

start_endlevel_flythrough(int n,object *obj,fix speed);

grs_bitmap terrain_bm_instance;
grs_bitmap satellite_bm_instance;

//find delta between two angles
fixang delta_ang(fixang a,fixang b)
{
	fixang delta0,delta1;

	return (abs(delta0 = a - b) < abs(delta1 = b - a)) ? delta0 : delta1;

}

//return though which side of seg0 is seg1
int matt_find_connect_side(int seg0,int seg1)
{
	segment *Seg=&Segments[seg0];
	int i;

	for (i=MAX_SIDES_PER_SEGMENT;i--;) if (Seg->children[i]==seg1) return i;

	return -1;
}

void free_endlevel_data()
{
	if (terrain_bm_instance.bm_data)
		myfree(terrain_bm_instance.bm_data);

	if (satellite_bm_instance.bm_data)
		myfree(satellite_bm_instance.bm_data);
}

void init_endlevel()
{
	//##satellite_bitmap = bm_load("earth.bbm");
	//##terrain_bitmap = bm_load("moon.bbm");
	//##
	//##load_terrain("matt5b.bbm");		//load bitmap as height array
	//##//load_terrain("ttest2.bbm");		//load bitmap as height array
	
	#ifdef STATION_ENABLED
	station_bitmap = bm_load("steel3.bbm");
	station_bitmap_list[0] = &station_bitmap;

	station_modelnum = load_polygon_model("station.pof",1,station_bitmap_list,NULL);
	#endif

//!!	exit_bitmap = bm_load("steel1.bbm");
//!!	exit_bitmap_list[0] = &exit_bitmap;

//!!	exit_modelnum = load_polygon_model("exit01.pof",1,exit_bitmap_list,NULL);
//!!	destroyed_exit_modelnum = load_polygon_model("exit01d.pof",1,exit_bitmap_list,NULL);

	generate_starfield();

	atexit(free_endlevel_data);

	terrain_bm_instance.bm_data = satellite_bm_instance.bm_data = NULL;
}

static int cockpit_mode_save;

object external_explosion;
int ext_expl_playing,mine_destroyed;

extern fix flash_scale;

vms_angvec exit_angles={-0xa00,0,0};

vms_matrix surface_orient;

int endlevel_data_loaded=0;

void start_endlevel_sequence()
{
	int last_segnum,exit_side,tunnel_length;

	if (Newdemo_state == ND_STATE_RECORDING)		// stop demo recording
		Newdemo_state = ND_STATE_PAUSED;

	if (Newdemo_state == ND_STATE_PLAYBACK)		// don't do this if in playback mode
		return;

	if (Player_is_dead || ConsoleObject->flags&OF_SHOULD_BE_DEAD)
		return;				//don't start if dead!

	Players[Player_num].homing_object_dist = -F1_0; // Turn off homing sound.

	reset_rear_view();		//turn off rear view if set

	if (!endlevel_data_loaded) {

		#ifdef NETWORK
		if (Game_mode & GM_MULTI) {
			multi_send_endlevel_start(0);
			#ifdef NETWORK
			network_do_frame(1, 1);
			#endif
		}
		#endif

		gr_palette_fade_out(gr_palette, 32, 0);

		PlayerFinishedLevel(0);		//don't do special sequence
		return;
	}

	{
		int segnum,old_segnum,entry_side,i;

		//count segments in exit tunnel

		old_segnum = ConsoleObject->segnum;
		exit_side = find_exit_side(ConsoleObject);
		segnum = Segments[old_segnum].children[exit_side];
		tunnel_length = 0;
		do {
			entry_side = matt_find_connect_side(segnum,old_segnum);
			exit_side = Side_opposite[entry_side];
			old_segnum = segnum;
			segnum = Segments[segnum].children[exit_side];
			tunnel_length++;
		} while (segnum >= 0);

		if (segnum != -2) {
			PlayerFinishedLevel(0);		//don't do special sequence
			return;
		}

		last_segnum = old_segnum;

		//now pick transition segnum 1/3 of the way in

		old_segnum = ConsoleObject->segnum;
		exit_side = find_exit_side(ConsoleObject);
		segnum = Segments[old_segnum].children[exit_side];
		i=tunnel_length/3;
		while (i--) {
			entry_side = matt_find_connect_side(segnum,old_segnum);
			exit_side = Side_opposite[entry_side];
			old_segnum = segnum;
			segnum = Segments[segnum].children[exit_side];
		}
		transition_segnum = segnum;

	}

	Assert(last_segnum == exit_segnum);

	cockpit_mode_save = Cockpit_mode;

	#ifdef NETWORK
	if (Game_mode & GM_MULTI) {
		multi_send_endlevel_start(0);
		network_do_frame(1, 1);
	}
	#endif

	songs_play_song( SONG_ENDLEVEL, 0 );

	Endlevel_sequence = EL_FLYTHROUGH;

	ConsoleObject->movement_type = MT_NONE;			//movement handled by flythrough
	ConsoleObject->control_type = CT_NONE;

	Game_suspended |= SUSP_ROBOTS;          //robots don't move

	cur_fly_speed = desired_fly_speed = FLY_SPEED;

	start_endlevel_flythrough(0,ConsoleObject,cur_fly_speed);		//initialize

	HUD_init_message( TXT_EXIT_SEQUENCE );

	outside_mine = ext_expl_playing = 0;

	flash_scale = f1_0;

	//init_endlevel();

	mine_destroyed=0;

}

extern flythrough_data fly_objects[];

extern object *slew_obj;

vms_angvec player_angles,player_dest_angles;
vms_angvec camera_desired_angles,camera_cur_angles;

#define CHASE_TURN_RATE (0x4000/4)		//max turn per second

//returns bitmask of which angles are at dest. bits 0,1,2 = p,b,h
int chase_angles(vms_angvec *cur_angles,vms_angvec *desired_angles)
{
	vms_angvec delta_angs,alt_angles,alt_delta_angs;
	fix total_delta,alt_total_delta;
	fix frame_turn;
	int mask=0;

	delta_angs.p = desired_angles->p - cur_angles->p;
	delta_angs.h = desired_angles->h - cur_angles->h;
	delta_angs.b = desired_angles->b - cur_angles->b;
//delta_angs.b = 0;

//printf("chasing angles...desired = %x %x %x, cur = %x %x %x   ",desired_angles->p,desired_angles->b,desired_angles->h,cur_angles->p,cur_angles->b,cur_angles->h);

	total_delta = abs(delta_angs.p) + abs(delta_angs.b) + abs(delta_angs.h);

	alt_angles.p = f1_0/2 - cur_angles->p;
	alt_angles.b = cur_angles->b + f1_0/2;
	alt_angles.h = cur_angles->h + f1_0/2;

	alt_delta_angs.p = desired_angles->p - alt_angles.p;
	alt_delta_angs.h = desired_angles->h - alt_angles.h;
	alt_delta_angs.b = desired_angles->b - alt_angles.b;
//alt_delta_angs.b = 0;

	alt_total_delta = abs(alt_delta_angs.p) + abs(alt_delta_angs.b) + abs(alt_delta_angs.h);

//printf("Total delta = %x, alt total_delta = %x\n",total_delta,alt_total_delta);

	if (alt_total_delta < total_delta) {
		//mprintf((0,"FLIPPING ANGLES!\n"));
		//printf("FLIPPING ANGLES!\n");
		*cur_angles = alt_angles;
		delta_angs = alt_delta_angs;
	}

	frame_turn = fixmul(FrameTime,CHASE_TURN_RATE);

	if (abs(delta_angs.p) < frame_turn) {
		cur_angles->p = desired_angles->p;
		mask |= 1;
	}
	else
		if (delta_angs.p > 0)
			cur_angles->p += frame_turn;
		else
			cur_angles->p -= frame_turn;

	if (abs(delta_angs.b) < frame_turn) {
		cur_angles->b = desired_angles->b;
		mask |= 2;
	}
	else
		if (delta_angs.b > 0)
			cur_angles->b += frame_turn;
		else
			cur_angles->b -= frame_turn;
//cur_angles->b = 0;

	if (abs(delta_angs.h) < frame_turn) {
		cur_angles->h = desired_angles->h;
		mask |= 4;
	}
	else
		if (delta_angs.h > 0)
			cur_angles->h += frame_turn;
		else
			cur_angles->h -= frame_turn;

	return mask;
}

void stop_endlevel_sequence()
{
	Interpolation_method = 0;

	gr_palette_fade_out(gr_palette, 32, 0);

	select_cockpit(cockpit_mode_save);

	Endlevel_sequence = EL_OFF;

	PlayerFinishedLevel(0);

}

#define VCLIP_BIG_PLAYER_EXPLOSION	58

//--unused-- vms_vector upvec = {0,f1_0,0};

//find the angle between the player's heading & the station
get_angs_to_object(vms_angvec *av,vms_vector *targ_pos,vms_vector *cur_pos)
{
	vms_vector tv;

	vm_vec_sub(&tv,targ_pos,cur_pos);

	vm_extract_angles_vector(av,&tv);
}

void do_endlevel_frame()
{
	static fix timer;
	vms_vector save_last_pos;
	static fix explosion_wait1=0;
	static fix explosion_wait2=0;
	static fix bank_rate;
	static fix ext_expl_halflife;

	save_last_pos = ConsoleObject->last_pos;	//don't let move code change this
	object_move_all();
	ConsoleObject->last_pos = save_last_pos;

	if (ext_expl_playing) {

		external_explosion.lifeleft -= FrameTime;
		do_explosion_sequence(&external_explosion);

		if (external_explosion.lifeleft < ext_expl_halflife)
			mine_destroyed = 1;

		if (external_explosion.flags & OF_SHOULD_BE_DEAD)
			ext_expl_playing = 0;
	}

	if (cur_fly_speed != desired_fly_speed) {
		fix delta = desired_fly_speed - cur_fly_speed;
		fix frame_accel = fixmul(FrameTime,FLY_ACCEL);

		if (abs(delta) < frame_accel)
			cur_fly_speed = desired_fly_speed;
		else
			if (delta > 0)
				cur_fly_speed += frame_accel;
			else
				cur_fly_speed -= frame_accel;
	}

	//do big explosions
	if (!outside_mine) {

		if (Endlevel_sequence==EL_OUTSIDE) {
			vms_vector tvec;

			vm_vec_sub(&tvec,&ConsoleObject->pos,&mine_side_exit_point);

			if (vm_vec_dot(&tvec,&mine_exit_orient.fvec) > 0) {
				object *tobj;

				outside_mine = 1;

				tobj = object_create_explosion(exit_segnum,&mine_side_exit_point,i2f(50),VCLIP_BIG_PLAYER_EXPLOSION);

				if (tobj) {
					external_explosion = *tobj;

					tobj->flags |= OF_SHOULD_BE_DEAD;

					flash_scale = 0;	//kill lights in mine

					ext_expl_halflife = tobj->lifeleft;

					ext_expl_playing = 1;
				}
	
				digi_link_sound_to_pos( SOUND_BIG_ENDLEVEL_EXPLOSION, exit_segnum, 0, &mine_side_exit_point, 0, i2f(3)/4 );
			}
		}

		//do explosions chasing player
		if ((explosion_wait1-=FrameTime) < 0) {
			vms_vector tpnt;
			int segnum;
			object *expl;
			static int sound_count;

			vm_vec_scale_add(&tpnt,&ConsoleObject->pos,&ConsoleObject->orient.fvec,-ConsoleObject->size*5);
			vm_vec_scale_add2(&tpnt,&ConsoleObject->orient.rvec,(rand()-RAND_MAX/2)*15);
			vm_vec_scale_add2(&tpnt,&ConsoleObject->orient.uvec,(rand()-RAND_MAX/2)*15);

			segnum = find_point_seg(&tpnt,ConsoleObject->segnum);

			if (segnum != -1) {
				expl = object_create_explosion(segnum,&tpnt,i2f(20),VCLIP_BIG_PLAYER_EXPLOSION);
				if (rand()<10000 || ++sound_count==7) {		//pseudo-random
					digi_link_sound_to_pos( SOUND_TUNNEL_EXPLOSION, segnum, 0, &tpnt, 0, F1_0 );
					sound_count=0;
				}
			}

			explosion_wait1 = 0x2000 + rand()/4;

		}
	}

	//do little explosions on walls
	if (Endlevel_sequence >= EL_FLYTHROUGH && Endlevel_sequence < EL_OUTSIDE)
		if ((explosion_wait2-=FrameTime) < 0) {
			vms_vector tpnt;
			fvi_query fq;
			fvi_info hit_data;

			//create little explosion on wall

			vm_vec_copy_scale(&tpnt,&ConsoleObject->orient.rvec,(rand()-RAND_MAX/2)*100);
			vm_vec_scale_add2(&tpnt,&ConsoleObject->orient.uvec,(rand()-RAND_MAX/2)*100);
			vm_vec_add2(&tpnt,&ConsoleObject->pos);

			if (Endlevel_sequence == EL_FLYTHROUGH)
				vm_vec_scale_add2(&tpnt,&ConsoleObject->orient.fvec,rand()*200);
			else
				vm_vec_scale_add2(&tpnt,&ConsoleObject->orient.fvec,rand()*60);

			//find hit point on wall

			fq.p0 = &ConsoleObject->pos;
			fq.p1 = &tpnt;
			fq.startseg = ConsoleObject->segnum;
			fq.rad = 0;
			fq.thisobjnum = 0;
			fq.ignore_obj_list = NULL;
			fq.flags = 0;

			find_vector_intersection(&fq,&hit_data);

			if (hit_data.hit_type==HIT_WALL && hit_data.hit_seg!=-1)
				object_create_explosion(hit_data.hit_seg,&hit_data.hit_pnt,i2f(3)+rand()*6,VCLIP_SMALL_EXPLOSION);

			explosion_wait2 = (0xa00 + rand()/8)/2;
		}

	switch (Endlevel_sequence) {

		case EL_OFF: return;

		case EL_FLYTHROUGH: {

			do_endlevel_flythrough(0);

			if (ConsoleObject->segnum == transition_segnum) {
				int objnum;

				Endlevel_sequence = EL_LOOKBACK;

				objnum = obj_create(OBJ_CAMERA, 0, 
					ConsoleObject->segnum,&ConsoleObject->pos,&ConsoleObject->orient,0,
					CT_NONE,MT_NONE,RT_NONE);

				if (objnum == -1) {				//can't get object, so abort
					mprintf((1, "Can't get object for endlevel sequence.  Aborting endlevel sequence.\n"));
					stop_endlevel_sequence();
					return;
				}

				Viewer = endlevel_camera = &Objects[objnum];

				select_cockpit(CM_LETTERBOX);

				fly_objects[1] = fly_objects[0];
				fly_objects[1].obj = endlevel_camera;
				fly_objects[1].speed = (5*cur_fly_speed)/4;
				fly_objects[1].offset_frac = 0x4000;

				vm_vec_scale_add2(&endlevel_camera->pos,&endlevel_camera->orient.fvec,i2f(7));

				timer=0x20000;
			}

			break;
		}


		case EL_LOOKBACK: {

			do_endlevel_flythrough(0);
			do_endlevel_flythrough(1);

			if (timer>0) {

				timer -= FrameTime;

				if (timer < 0)		//reduce speed
					fly_objects[1].speed = fly_objects[0].speed;
			}

			if (endlevel_camera->segnum == exit_segnum) {
				vms_angvec cam_angles,exit_seg_angles;

				Endlevel_sequence = EL_OUTSIDE;

				timer = i2f(2);

				vm_vec_negate(&endlevel_camera->orient.fvec);
				vm_vec_negate(&endlevel_camera->orient.rvec);

				vm_extract_angles_matrix(&cam_angles,&endlevel_camera->orient);
				vm_extract_angles_matrix(&exit_seg_angles,&mine_exit_orient);
				bank_rate = (-exit_seg_angles.b - cam_angles.b)/2;

				ConsoleObject->control_type = endlevel_camera->control_type = CT_NONE;

//				_MARK_("Starting outside");

#ifdef SLEW_ON
 slew_obj = endlevel_camera;
#endif
			}
				
			break;
		}

		case EL_OUTSIDE: {
			#ifndef SLEW_ON
			vms_angvec cam_angles;
			#endif

			vm_vec_scale_add2(&ConsoleObject->pos,&ConsoleObject->orient.fvec,fixmul(FrameTime,cur_fly_speed));
#ifndef SLEW_ON
			vm_vec_scale_add2(&endlevel_camera->pos,&endlevel_camera->orient.fvec,fixmul(FrameTime,-2*cur_fly_speed));
			vm_vec_scale_add2(&endlevel_camera->pos,&endlevel_camera->orient.uvec,fixmul(FrameTime,-cur_fly_speed/10));

			vm_extract_angles_matrix(&cam_angles,&endlevel_camera->orient);
			cam_angles.b += fixmul(bank_rate,FrameTime);
			vm_angles_2_matrix(&endlevel_camera->orient,&cam_angles);
#endif

			timer -= FrameTime;

			if (timer < 0) {

				Endlevel_sequence = EL_STOPPED;

				vm_extract_angles_matrix(&player_angles,&ConsoleObject->orient);

				timer = i2f(3);

			}

			break;
		}

		case EL_STOPPED: {

			get_angs_to_object(&player_dest_angles,&station_pos,&ConsoleObject->pos);
			chase_angles(&player_angles,&player_dest_angles);
			vm_angles_2_matrix(&ConsoleObject->orient,&player_angles);

			vm_vec_scale_add2(&ConsoleObject->pos,&ConsoleObject->orient.fvec,fixmul(FrameTime,cur_fly_speed));

			timer -= FrameTime;

			if (timer < 0) {

				#ifdef SLEW_ON
				slew_obj = endlevel_camera;
				_do_slew_movement(endlevel_camera,1,1);
				timer += FrameTime;		//make time stop
				break;
				#else

				#ifdef SHORT_SEQUENCE

				stop_endlevel_sequence();

				#else
				Endlevel_sequence = EL_PANNING;

				vm_extract_angles_matrix(&camera_cur_angles,&endlevel_camera->orient);


				timer = i2f(3);

				if (Game_mode & GM_MULTI) { // try to skip part of the seq if multiplayer
					stop_endlevel_sequence();
					return;
				}

				//mprintf((0,"Switching to pan...\n"));
				#endif		//SHORT_SEQUENCE
				#endif		//SLEW_ON

			}
			break;
		}

		#ifndef SHORT_SEQUENCE
		case EL_PANNING: {
			#ifndef SLEW_ON
			int mask;
			#endif

			get_angs_to_object(&player_dest_angles,&station_pos,&ConsoleObject->pos);
			chase_angles(&player_angles,&player_dest_angles);
			vm_angles_2_matrix(&ConsoleObject->orient,&player_angles);
			vm_vec_scale_add2(&ConsoleObject->pos,&ConsoleObject->orient.fvec,fixmul(FrameTime,cur_fly_speed));

			#ifdef SLEW_ON
			_do_slew_movement(endlevel_camera,1,1);
			#else

			get_angs_to_object(&camera_desired_angles,&ConsoleObject->pos,&endlevel_camera->pos);
			mask = chase_angles(&camera_cur_angles,&camera_desired_angles);
			vm_angles_2_matrix(&endlevel_camera->orient,&camera_cur_angles);

			if ((mask&5) == 5) {

				vms_vector tvec;

				Endlevel_sequence = EL_CHASING;

//				_MARK_("Done outside");

				vm_vec_normalized_dir_quick(&tvec,&station_pos,&ConsoleObject->pos);
				vm_vector_2_matrix(&ConsoleObject->orient,&tvec,&surface_orient.uvec,NULL);

				desired_fly_speed *= 2;

				//mprintf((0,"Switching to chase...\n"));

			}
			#endif

			break;
		}

		case EL_CHASING: {
			fix d,speed_scale;

			#ifdef SLEW_ON
			_do_slew_movement(endlevel_camera,1,1);
			#endif

			get_angs_to_object(&camera_desired_angles,&ConsoleObject->pos,&endlevel_camera->pos);
			chase_angles(&camera_cur_angles,&camera_desired_angles);

			#ifndef SLEW_ON
			vm_angles_2_matrix(&endlevel_camera->orient,&camera_cur_angles);
			#endif

			d = vm_vec_dist_quick(&ConsoleObject->pos,&endlevel_camera->pos);

			speed_scale = fixdiv(d,i2f(0x20));
			if (d<f1_0) d=f1_0;

			get_angs_to_object(&player_dest_angles,&station_pos,&ConsoleObject->pos);
			chase_angles(&player_angles,&player_dest_angles);
			vm_angles_2_matrix(&ConsoleObject->orient,&player_angles);

			vm_vec_scale_add2(&ConsoleObject->pos,&ConsoleObject->orient.fvec,fixmul(FrameTime,cur_fly_speed));
			#ifndef SLEW_ON
			vm_vec_scale_add2(&endlevel_camera->pos,&endlevel_camera->orient.fvec,fixmul(FrameTime,fixmul(speed_scale,cur_fly_speed)));

			if (vm_vec_dist(&ConsoleObject->pos,&station_pos) < i2f(10))
				stop_endlevel_sequence();
			#endif

			break;

		}
		#endif		//ifdef SHORT_SEQUENCE
	}
}


#define MIN_D 0x100

//find which side to fly out of
find_exit_side(object *obj)
{
	int i;
	vms_vector prefvec,segcenter,sidevec;
	fix best_val=-f2_0;
	int best_side;
	segment *pseg = &Segments[obj->segnum];

	//find exit side

	vm_vec_normalized_dir_quick(&prefvec,&obj->pos,&obj->last_pos);

	compute_segment_center(&segcenter,pseg);

	best_side=-1;
	for (i=MAX_SIDES_PER_SEGMENT;--i >= 0;) {
		fix d;

		if (pseg->children[i]!=-1) {

			compute_center_point_on_side(&sidevec,pseg,i);
			vm_vec_normalized_dir_quick(&sidevec,&sidevec,&segcenter);
			d = vm_vec_dotprod(&sidevec,&prefvec);

			if (labs(d) < MIN_D) d=0;

			if (d > best_val) {best_val=d; best_side=i;}

		}
	}

	Assert(best_side!=-1);

	return best_side;
}

extern fix Render_zoom;							//the player's zoom factor

extern vms_vector Viewer_eye;	//valid during render

void render_mine(int start_seg_num,fix eye_offset);

void draw_exit_model()
{
	vms_vector model_pos;
	int f=15,u=0;	//21;

	vm_vec_scale_add(&model_pos,&mine_exit_point,&mine_exit_orient.fvec,i2f(f));
	vm_vec_scale_add2(&model_pos,&mine_exit_orient.uvec,i2f(u));

	draw_polygon_model(&model_pos,&mine_exit_orient,NULL,(mine_destroyed)?destroyed_exit_modelnum:exit_modelnum,0,f1_0,NULL,NULL);

}

int exit_point_bmx,exit_point_bmy;

fix satellite_size = i2f(400);

#define SATELLITE_DIST		i2f(1024)
#define SATELLITE_WIDTH		satellite_size
#define SATELLITE_HEIGHT	((satellite_size*9)/4)		//((satellite_size*5)/2)

void render_external_scene(fix eye_offset)
{

	Viewer_eye = Viewer->pos;

	if (eye_offset)
		vm_vec_scale_add2(&Viewer_eye,&Viewer->orient.rvec,eye_offset);

	g3_set_view_matrix(&Viewer->pos,&Viewer->orient,Render_zoom);

	//g3_draw_horizon(BM_XRGB(0,0,0),BM_XRGB(16,16,16));		//,-1);
	gr_clear_canvas(BM_XRGB(0,0,0));

	g3_start_instance_matrix(&vmd_zero_vector,&surface_orient);
	draw_stars();
	g3_done_instance();

	{	//draw satellite

		vms_vector delta;
		g3s_point p,top_pnt;

		g3_rotate_point(&p,&satellite_pos);
		g3_rotate_delta_vec(&delta,&satellite_upvec);

		g3_add_delta_vec(&top_pnt,&p,&delta);

		if (! (p.p3_codes & CC_BEHIND)) {
			int save_im = Interpolation_method;
			//p.p3_flags &= ~PF_PROJECTED;
			//g3_project_point(&p);
			if (! (p.p3_flags & PF_OVERFLOW)) {
				Interpolation_method = 0;
				//gr_bitmapm(f2i(p.p3_sx)-32,f2i(p.p3_sy)-32,satellite_bitmap);
				g3_draw_rod_tmap(satellite_bitmap,&p,SATELLITE_WIDTH,&top_pnt,SATELLITE_WIDTH,f1_0);
				Interpolation_method = save_im;
			}
		}
	}

	#ifdef STATION_ENABLED
	draw_polygon_model(&station_pos,&vmd_identity_matrix,NULL,station_modelnum,0,f1_0,NULL,NULL);
	#endif

	render_terrain(&mine_ground_exit_point,exit_point_bmx,exit_point_bmy);

	draw_exit_model();
	if (ext_expl_playing)
		draw_fireball(&external_explosion);

	Lighting_on=0;
	render_object(ConsoleObject);
	Lighting_on=1;
}

#define MAX_STARS 500

vms_vector stars[MAX_STARS];

generate_starfield()
{
	int i;

	for (i=0;i<MAX_STARS;i++) {

		stars[i].x = (rand() - RAND_MAX/2) << 14;
		stars[i].z = (rand() - RAND_MAX/2) << 14;
		stars[i].y = (rand()/2) << 14;

	}
}

draw_stars()
{
	int i;
	int intensity=31;
	g3s_point p;

	for (i=0;i<MAX_STARS;i++) {

		if ((i&63) == 0) {
			gr_setcolor(BM_XRGB(intensity,intensity,intensity));
			intensity-=3;
		}			

		//g3_rotate_point(&p,&stars[i]);
		g3_rotate_delta_vec(&p.p3_vec,&stars[i]);
		g3_code_point(&p);

		if (p.p3_codes == 0) {

			p.p3_flags &= ~PF_PROJECTED;

			g3_project_point(&p);

			gr_pixel(f2i(p.p3_sx),f2i(p.p3_sy));
		}
	}

//@@	{
//@@		vms_vector delta;
//@@		g3s_point top_pnt;
//@@
//@@		g3_rotate_point(&p,&satellite_pos);
//@@		g3_rotate_delta_vec(&delta,&satellite_upvec);
//@@
//@@		g3_add_delta_vec(&top_pnt,&p,&delta);
//@@
//@@		if (! (p.p3_codes & CC_BEHIND)) {
//@@			int save_im = Interpolation_method;
//@@			Interpolation_method = 0;
//@@			//p.p3_flags &= ~PF_PROJECTED;
//@@			g3_project_point(&p);
//@@			if (! (p.p3_flags & PF_OVERFLOW))
//@@				//gr_bitmapm(f2i(p.p3_sx)-32,f2i(p.p3_sy)-32,satellite_bitmap);
//@@				g3_draw_rod_tmap(satellite_bitmap,&p,SATELLITE_WIDTH,&top_pnt,SATELLITE_WIDTH,f1_0);
//@@			Interpolation_method = save_im;
//@@		}
//@@	}

}

endlevel_render_mine(fix eye_offset)
{
	int start_seg_num;

	Viewer_eye = Viewer->pos;

	if (Viewer->type == OBJ_PLAYER )
		vm_vec_scale_add2(&Viewer_eye,&Viewer->orient.fvec,(Viewer->size*3)/4);

	if (eye_offset)
		vm_vec_scale_add2(&Viewer_eye,&Viewer->orient.rvec,eye_offset);

	#ifdef EDITOR
	if (Function_mode==FMODE_EDITOR)
		Viewer_eye = Viewer->pos;
	#endif

	if (Endlevel_sequence >= EL_OUTSIDE) {

		start_seg_num = exit_segnum;
	}
	else {
		start_seg_num = find_point_seg(&Viewer_eye,Viewer->segnum);

		if (start_seg_num==-1)
			start_seg_num = Viewer->segnum;
	}

	if (Endlevel_sequence == EL_LOOKBACK) {
		vms_matrix headm,viewm;
		vms_angvec angles = {0,0,0x7fff};

		vm_angles_2_matrix(&headm,&angles);
		vm_matrix_x_matrix(&viewm,&Viewer->orient,&headm);
		g3_set_view_matrix(&Viewer_eye,&viewm,Render_zoom);
	}
	else
		g3_set_view_matrix(&Viewer_eye,&Viewer->orient,Render_zoom);

	render_mine(start_seg_num,eye_offset);
}

void render_endlevel_frame(fix eye_offset)
{

	g3_start_frame();

	if (Endlevel_sequence < EL_OUTSIDE)
		endlevel_render_mine(eye_offset);
	else
		render_external_scene(eye_offset);

	g3_end_frame();

}



///////////////////////// copy of flythrough code for endlevel


#define MAX_FLY_OBJECTS 2

flythrough_data fly_objects[MAX_FLY_OBJECTS];

flythrough_data *flydata;

int matt_find_connect_side(int seg0,int seg1);

void compute_segment_center(vms_vector *vp,segment *sp);

fixang delta_ang(fixang a,fixang b);
fixang interp_angle(fixang dest,fixang src,fixang step);

#define DEFAULT_SPEED i2f(16)

#define MIN_D 0x100

//if speed is zero, use default speed
start_endlevel_flythrough(int n,object *obj,fix speed)
{
	flydata = &fly_objects[n];

	flydata->obj = obj;

	flydata->first_time = 1;

	flydata->speed = speed?speed:DEFAULT_SPEED;

	flydata->offset_frac = 0;
}

static vms_angvec *angvec_add2_scale(vms_angvec *dest,vms_vector *src,fix s)
{
	dest->p += fixmul(src->x,s);
	dest->b  += fixmul(src->z,s);
	dest->h  += fixmul(src->y,s);

	return dest;
}

#define MAX_ANGSTEP	0x4000		//max turn per second

#define MAX_SLIDE_PER_SEGMENT 0x10000

do_endlevel_flythrough(int n)
{
	object *obj;
	segment *pseg;
	int old_player_seg;

	flydata = &fly_objects[n];
	obj = flydata->obj;
	
	old_player_seg = obj->segnum;

	//move the player for this frame

	if (!flydata->first_time) {

		vm_vec_scale_add2(&obj->pos,&flydata->step,FrameTime);
		angvec_add2_scale(&flydata->angles,&flydata->angstep,FrameTime);

		vm_angles_2_matrix(&obj->orient,&flydata->angles);
	}

	//check new player seg

	update_object_seg(obj);
	pseg = &Segments[obj->segnum];

	if (flydata->first_time || obj->segnum != old_player_seg) {		//moved into new seg
		vms_vector curcenter,nextcenter;
		fix step_size,seg_time;
		short entry_side,exit_side;	//what sides we entry and leave through
		vms_vector dest_point;		//where we are heading (center of exit_side)
		vms_angvec dest_angles;		//where we want to be pointing
		vms_matrix dest_orient;
		int up_side;

		//find new exit side

		if (!flydata->first_time) {

			entry_side = matt_find_connect_side(obj->segnum,old_player_seg);
			exit_side = Side_opposite[entry_side];
		}

		if (flydata->first_time || entry_side==-1 || pseg->children[exit_side]==-1)
			exit_side = find_exit_side(obj);

		{										//find closest side to align to
			fix d,largest_d=-f1_0;
			int i;

			for (i=0;i<6;i++) {
				#ifdef COMPACT_SEGS
				vms_vector v1;
				get_side_normal(pseg, i, 0, &v1 );
				d = vm_vec_dot(&v1,&flydata->obj->orient.uvec);
				#else
				d = vm_vec_dot(&pseg->sides[i].normals[0],&flydata->obj->orient.uvec);
				#endif
				if (d > largest_d) {largest_d = d; up_side=i;}
			}

		}

		//update target point & angles

		compute_center_point_on_side(&dest_point,pseg,exit_side);

		//update target point and movement points

		//offset object sideways
		if (flydata->offset_frac) {
			int s0=-1,s1,i;
			vms_vector s0p,s1p;
			fix dist;

			for (i=0;i<6;i++)
				if (i!=entry_side && i!=exit_side && i!=up_side && i!=Side_opposite[up_side])
					if (s0==-1)
						s0 = i;
					else
						s1 = i;

			compute_center_point_on_side(&s0p,pseg,s0);
			compute_center_point_on_side(&s1p,pseg,s1);
			dist = fixmul(vm_vec_dist(&s0p,&s1p),flydata->offset_frac);

			if (dist-flydata->offset_dist > MAX_SLIDE_PER_SEGMENT)
				dist = flydata->offset_dist + MAX_SLIDE_PER_SEGMENT;

			flydata->offset_dist = dist;

			vm_vec_scale_add2(&dest_point,&obj->orient.rvec,dist);

		}

		vm_vec_sub(&flydata->step,&dest_point,&obj->pos);
		step_size = vm_vec_normalize_quick(&flydata->step);
		vm_vec_scale(&flydata->step,flydata->speed);

		compute_segment_center(&curcenter,pseg);
		compute_segment_center(&nextcenter,&Segments[pseg->children[exit_side]]);
		vm_vec_sub(&flydata->headvec,&nextcenter,&curcenter);

		#ifdef COMPACT_SEGS	
		{
			vms_vector _v1;
			get_side_normal(pseg, up_side, 0, &_v1 );
			vm_vector_2_matrix(&dest_orient,&flydata->headvec,&_v1,NULL);
		}
		#else
		vm_vector_2_matrix(&dest_orient,&flydata->headvec,&pseg->sides[up_side].normals[0],NULL);
		#endif
		vm_extract_angles_matrix(&dest_angles,&dest_orient);

		if (flydata->first_time)
			vm_extract_angles_matrix(&flydata->angles,&obj->orient);

		seg_time = fixdiv(step_size,flydata->speed);	//how long through seg

		if (seg_time) {
			flydata->angstep.x = max(-MAX_ANGSTEP,min(MAX_ANGSTEP,fixdiv(delta_ang(flydata->angles.p,dest_angles.p),seg_time)));
			flydata->angstep.z = max(-MAX_ANGSTEP,min(MAX_ANGSTEP,fixdiv(delta_ang(flydata->angles.b,dest_angles.b),seg_time)));
			flydata->angstep.y = max(-MAX_ANGSTEP,min(MAX_ANGSTEP,fixdiv(delta_ang(flydata->angles.h,dest_angles.h),seg_time)));

		}
		else {
			flydata->angles = dest_angles;
			flydata->angstep.x = flydata->angstep.y = flydata->angstep.z = 0;
		}
	}

	flydata->first_time=0;
}

#define JOY_NULL 15
#define ROT_SPEED 8		//rate of rotation while key held down
#define VEL_SPEED (15)	//rate of acceleration while key held down

extern short old_joy_x,old_joy_y;	//position last time around

#include "key.h"
#include "joy.h"

#ifdef SLEW_ON		//this is a special routine for slewing around external scene
int _do_slew_movement(object *obj, int check_keys, int check_joy )
{
	int moved = 0;
	vms_vector svel, movement;				//scaled velocity (per this frame)
	vms_matrix rotmat,new_pm;
	int joy_x,joy_y,btns;
	int joyx_moved,joyy_moved;
	vms_angvec rotang;

	if (keyd_pressed[KEY_PAD5])
		vm_vec_zero(&obj->phys_info.velocity);

	if (check_keys) {
		obj->phys_info.velocity.x += VEL_SPEED * (key_down_time(KEY_PAD9) - key_down_time(KEY_PAD7));
		obj->phys_info.velocity.y += VEL_SPEED * (key_down_time(KEY_PADMINUS) - key_down_time(KEY_PADPLUS));
		obj->phys_info.velocity.z += VEL_SPEED * (key_down_time(KEY_PAD8) - key_down_time(KEY_PAD2));

		rotang.pitch =  (key_down_time(KEY_LBRACKET) - key_down_time(KEY_RBRACKET))/ROT_SPEED;
		rotang.bank  = (key_down_time(KEY_PAD1) - key_down_time(KEY_PAD3))/ROT_SPEED;
		rotang.head  = (key_down_time(KEY_PAD6) - key_down_time(KEY_PAD4))/ROT_SPEED;
	}
	else
		rotang.pitch = rotang.bank  = rotang.head  = 0;

	//check for joystick movement

	if (check_joy && joy_present)	{
		joy_get_pos(&joy_x,&joy_y);
		btns=joy_get_btns();
	
		joyx_moved = (abs(joy_x - old_joy_x)>JOY_NULL);
		joyy_moved = (abs(joy_y - old_joy_y)>JOY_NULL);
	
		if (abs(joy_x) < JOY_NULL) joy_x = 0;
		if (abs(joy_y) < JOY_NULL) joy_y = 0;
	
		if (btns)
			if (!rotang.pitch) rotang.pitch = fixmul(-joy_y * 512,FrameTime); else;
		else
			if (joyy_moved) obj->phys_info.velocity.z = -joy_y * 8192;
	
		if (!rotang.head) rotang.head = fixmul(joy_x * 512,FrameTime);
	
		if (joyx_moved) old_joy_x = joy_x;
		if (joyy_moved) old_joy_y = joy_y;
	}

	moved = rotang.pitch | rotang.bank | rotang.head;

	vm_angles_2_matrix(&rotmat,&rotang);
	vm_matrix_x_matrix(&new_pm,&obj->orient,&rotmat);
	obj->orient = new_pm;
	vm_transpose_matrix(&new_pm);		//make those columns rows

	moved |= obj->phys_info.velocity.x | obj->phys_info.velocity.y | obj->phys_info.velocity.z;

	svel = obj->phys_info.velocity;
	vm_vec_scale(&svel,FrameTime);		//movement in this frame
	vm_vec_rotate(&movement,&svel,&new_pm);

	vm_vec_add2(&obj->pos,&movement);

	moved |= (movement.x || movement.y || movement.z);

	return moved;
}
#endif

#define LINE_LEN	80
#define NUM_VARS	8

#define STATION_DIST	i2f(1024)

int convert_ext( char *dest, char *ext )
{
	char *t;

	t = strchr(dest,'.');

	if (t && (t-dest <= 8)) {
		t[1] = ext[0];			
		t[2] = ext[1];			
		t[3] = ext[2];	
		return 1;
	}
	else
		return 0;
}

#undef isspace
#define isspace(c)		((c == ' ') || (c == '\t') || (c == '\r'))

//called for each level to load & setup the exit sequence
load_endlevel_data(int level_num)
{
	char filename[13];
	char line[LINE_LEN],*p;
	CFILE *ifile;
	int var,segnum,sidenum;
	int exit_side, i;
	int have_binary = 0;

	endlevel_data_loaded = 0;		//not loaded yet

try_again:
	;

#ifdef MAC_SHAREWARE
	sprintf(filename, "level%02d.end", level_num);
#else
	if (level_num<0)		//secret level
		strcpy(filename,Secret_level_names[-level_num-1]);
	else					//normal level
		strcpy(filename,Level_names[level_num-1]);

	if (!convert_ext(filename,"END"))
		return;
#endif

	ifile = cfopen(filename,"rb");

	if (!ifile) {

		convert_ext(filename,"TXB");

		ifile = cfopen(filename,"rb");

		if (!ifile)
			if (level_num==1) {
				return;		//abort
				//Error("Cannot load file text of binary version of <%s>",filename);
			}
			else {
				level_num = 1;
				goto try_again;
			}

		have_binary = 1;
	}

	//ok...this parser is pretty simple.  It ignores comments, but
	//everything else must be in the right place

	var = 0;

	while (cfgets(line,LINE_LEN,ifile)) {

		if (have_binary) {
			for (i = 0; i < strlen(line) - 1; i++) {
				encode_rotate_left(&(line[i]));
				line[i] = line[i] ^ BITMAP_TBL_XOR;
				encode_rotate_left(&(line[i]));
			}
			p = line;
		}

		if ((p=strchr(line,';'))!=NULL)
			*p = 0;		//cut off comment

		for (p=line+strlen(line)-1;p>line && isspace(*p);*p--=0);
		for (p=line;isspace(*p);p++);

		if (!*p)		//empty line
			continue;

		switch (var) {

			case 0: {						//ground terrain
				int iff_error;
				ubyte pal[768];

				if (terrain_bm_instance.bm_data)
					myfree(terrain_bm_instance.bm_data);

				iff_error = iff_read_bitmap(p,&terrain_bm_instance,BM_LINEAR,pal);
				if (iff_error != IFF_NO_ERROR) {
					mprintf((1, "File %s - IFF error: %s",p,iff_errormsg(iff_error)));
					Error("File %s - IFF error: %s",p,iff_errormsg(iff_error));
				}

				terrain_bitmap = &terrain_bm_instance;
				gr_remap_bitmap_good( terrain_bitmap, pal, iff_transparent_color, -1);

				break;
			}

			case 1:							//height map

				load_terrain(p);
				break;


			case 2:

				sscanf(p,"%d,%d",&exit_point_bmx,&exit_point_bmy);
				break;

			case 3:							//exit heading

				exit_angles.h = i2f(atoi(p))/360;
				break;

			case 4: {						//planet bitmap
				int iff_error;
				ubyte pal[768];

				if (satellite_bm_instance.bm_data)
					myfree(satellite_bm_instance.bm_data);

				iff_error = iff_read_bitmap(p,&satellite_bm_instance,BM_LINEAR,pal);
				if (iff_error != IFF_NO_ERROR) {
					mprintf((1, "File %s - IFF error: %s",p,iff_errormsg(iff_error)));
					Error("File %s - IFF error: %s",p,iff_errormsg(iff_error));
				}

				satellite_bitmap = &satellite_bm_instance;
				gr_remap_bitmap_good( satellite_bitmap, pal, iff_transparent_color, -1);

				break;
			}

			case 5:							//earth pos
			case 7: {						//station pos
				vms_matrix tm;
				vms_angvec ta;
				int pitch,head;

				sscanf(p,"%d,%d",&head,&pitch);

				ta.h = i2f(head)/360;
				ta.p = -i2f(pitch)/360;
				ta.b = 0;

				vm_angles_2_matrix(&tm,&ta);

				if (var==5)
					satellite_pos = tm.fvec;
					//vm_vec_copy_scale(&satellite_pos,&tm.fvec,SATELLITE_DIST);
				else
					station_pos = tm.fvec;

				break;
			}

			case 6:						//planet size
				satellite_size = i2f(atoi(p));
				break;
		}

		var++;

	}

	Assert(var == NUM_VARS);


	// OK, now the data is loaded.  Initialize everything

	//find the exit sequence by searching all segments for a side with
	//children == -2

	for (segnum=0,exit_segnum=-1;exit_segnum==-1 && segnum<=Highest_segment_index;segnum++)
		for (sidenum=0;sidenum<6;sidenum++)
			if (Segments[segnum].children[sidenum] == -2) {
				exit_segnum = segnum;
				exit_side = sidenum;
				break;
			}

	Assert(exit_segnum!=-1);

	compute_segment_center(&mine_exit_point,&Segments[exit_segnum]);
	extract_orient_from_segment(&mine_exit_orient,&Segments[exit_segnum]);
	compute_center_point_on_side(&mine_side_exit_point,&Segments[exit_segnum],exit_side);

	vm_vec_scale_add(&mine_ground_exit_point,&mine_exit_point,&mine_exit_orient.uvec,-i2f(20));

	//compute orientation of surface
	{
		vms_vector tv;
		vms_matrix exit_orient,tm;

		vm_angles_2_matrix(&exit_orient,&exit_angles);
		vm_transpose_matrix(&exit_orient);
		vm_matrix_x_matrix(&surface_orient,&mine_exit_orient,&exit_orient);

		vm_copy_transpose_matrix(&tm,&surface_orient);
		vm_vec_rotate(&tv,&station_pos,&tm);
		vm_vec_scale_add(&station_pos,&mine_exit_point,&tv,STATION_DIST);

vm_vec_rotate(&tv,&satellite_pos,&tm);
vm_vec_scale_add(&satellite_pos,&mine_exit_point,&tv,SATELLITE_DIST);

vm_vector_2_matrix(&tm,&tv,&surface_orient.uvec,NULL);
vm_vec_copy_scale(&satellite_upvec,&tm.uvec,SATELLITE_HEIGHT);


	}

	cfclose(ifile);

	endlevel_data_loaded = 1;

}


