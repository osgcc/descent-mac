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
 * $Source: Smoke:miner:source:main::RCS:fuelcen.c $
 * $Revision: 1.2 $
 * $Author: allender $
 * $Date: 1995/10/31 10:23:40 $
 * 
 * Functions for refueling centers.
 * 
 * $Log: fuelcen.c $
 * Revision 1.2  1995/10/31  10:23:40  allender
 * shareware stuff
 *
 * Revision 1.1  1995/05/16  15:24:50  allender
 * Initial revision
 *
 * Revision 2.3  1995/03/21  08:38:40  john
 * Ifdef'd out the NETWORK code.
 * 
 * Revision 2.2  1995/03/06  15:23:09  john
 * New screen techniques.
 * 
 * Revision 2.1  1995/02/27  13:13:26  john
 * Removed floating point.
 * 
 * Revision 2.0  1995/02/27  11:27:20  john
 * New version 2.0, which has no anonymous unions, builds with
 * Watcom 10.0, and doesn't require parsing BITMAPS.TBL.
 * 
 * Revision 1.159  1995/02/22  13:48:10  allender
 * remove anonymous unions in object structure
 * 
 * Revision 1.158  1995/02/08  11:37:48  mike
 * Check for failures in call to obj_create.
 * 
 * Revision 1.157  1995/02/07  20:39:39  mike
 * fix toasters in multiplayer
 * 
 * 
 * Revision 1.156  1995/02/02  18:40:10  john
 * Fixed bug with full screen cockpit flashing non-white.
 * 
 * Revision 1.155  1995/01/28  15:27:22  yuan
 * Make sure fuelcen nums are valid.
 * 
 * Revision 1.154  1995/01/03  14:26:23  rob
 * Better ifdef for robot centers.
 * 
 * Revision 1.153  1995/01/03  11:27:49  rob
 * Added include of fuelcen.c
 * 
 * Revision 1.152  1995/01/03  09:47:22  john
 * Some ifdef SHAREWARE lines.
 * 
 * Revision 1.151  1995/01/02  21:02:07  rob
 * added matcen support for coop/multirobot.
 * 
 * Revision 1.150  1994/12/15  18:31:22  mike
 * fix confusing precedence problems.
 * 
 * Revision 1.149  1994/12/15  13:04:22  mike
 * Replace Players[Player_num].time_total references with GameTime.
 * 
 * Revision 1.148  1994/12/15  03:05:18  matt
 * Added error checking for NULL return from object_create_explosion()
 * 
 * Revision 1.147  1994/12/13  19:49:12  rob
 * Made the fuelcen noise quieter.
 * 
 * Revision 1.146  1994/12/13  12:03:18  john
 * Made the warning sirens not start until after "desccruction
 * secquence activated voice".
 * 
 * Revision 1.145  1994/12/12  17:18:30  mike
 * make warning siren louder.
 * 
 * Revision 1.144  1994/12/11  23:18:04  john
 * Added -nomusic.
 * Added RealFrameTime.
 * Put in a pause when sound initialization error.
 * Made controlcen countdown and framerate use RealFrameTime.
 * 
 * Revision 1.143  1994/12/11  14:10:16  mike
 * louder sounds.
 * 
 * Revision 1.142  1994/12/06  11:33:19  yuan
 * Fixed bug with fueling when above 100.
 * 
 * Revision 1.141  1994/12/05  23:37:14  matt
 * Took out calls to warning() function
 * 
 * Revision 1.140  1994/12/05  23:19:18  yuan
 * Fixed fuel center refuelers..
 * 
 * Revision 1.139  1994/12/03  12:48:12  mike
 * diminish rocking due to control center destruction.
 * 
 * Revision 1.138  1994/12/02  23:30:32  mike
 * fix bumpiness after toasting control center.
 * 
 * Revision 1.137  1994/12/02  22:48:14  mike
 * rock the ship after toasting the control center!
 * 
 * Revision 1.136  1994/12/02  17:12:11  rob
 * Fixed countdown sounds.
 * 
 * Revision 1.135  1994/11/29  20:59:43  rob
 * Don't run out of fuel in net games (don't want to sync it between machines)
 * 
 * Revision 1.134  1994/11/29  19:10:57  john
 * Took out debugging mprintf.
 * 
 * Revision 1.133  1994/11/29  13:19:40  john
 * Made voice for "destruction actived in t-"
 * be at 12.75 secs.
 * 
 * Revision 1.132  1994/11/29  12:19:46  john
 * MAde the "Mine desctruction will commence"
 * voice play at 12.5 secs.
 * 
 * Revision 1.131  1994/11/29  12:12:54  adam
 * *** empty log message ***
 * 
 * Revision 1.130  1994/11/28  21:04:26  rob
 * Added code to cast noise when player refuels.
 * 
 * Revision 1.129  1994/11/27  23:15:04  matt
 * Made changes for new mprintf calling convention
 * 
 * Revision 1.128  1994/11/21  16:27:51  mike
 * debug code for morphing.
 * 
 * Revision 1.127  1994/11/21  12:33:50  matt
 * For control center explosions, use small fireball, not pseudo-random vclip
 * 
 * Revision 1.126  1994/11/20  22:12:15  mike
 * Fix bug in initializing materialization centers.
 * 
 * Revision 1.125  1994/11/19  15:18:22  mike
 * rip out unused code and data.
 * 
 * Revision 1.124  1994/11/08  12:18:59  mike
 * Initialize Fuelcen_seconds_left.
 * 
 * Revision 1.123  1994/10/30  14:12:33  mike
 * rip out repair center stuff
 * 
 * Revision 1.122  1994/10/28  14:42:45  john
 * Added sound volumes to all sound calls.
 * 
 * Revision 1.121  1994/10/16  12:44:02  mike
 * Make time to exit mine after control center destruction diff level dependent.
 * 
 * Revision 1.120  1994/10/09  22:03:26  mike
 * Adapt to new create_n_segment_path parameters.
 * 
 * Revision 1.119  1994/10/06  14:52:42  mike
 * Remove last of ability to damage fuel centers.
 * 
 * Revision 1.118  1994/10/06  14:08:45  matt
 * Made morph flash effect get orientation from segment
 * 
 * Revision 1.117  1994/10/05  16:09:03  mike
 * Put debugging code into matcen/fuelcen synchronization problem.
 * 
 * Revision 1.116  1994/10/04  15:32:41  john
 * Took out the old PLAY_SOUND??? code and replaced it
 * with direct calls into digi_link_??? so that all sounds
 * can be made 3d.
 * 
 * Revision 1.115  1994/10/03  23:37:57  mike
 * Clean up this mess of confusion to the point where maybe matcens actually work.
 * 
 * Revision 1.114  1994/10/03  13:34:40  matt
 * Added new (and hopefully better) game sequencing functions
 * 
 * Revision 1.113  1994/09/30  14:41:57  matt
 * Fixed bug as per Mike's instructions
 * 
 * Revision 1.112  1994/09/30  00:37:33  mike
 * Balance materialization centers.
 * 
 * Revision 1.111  1994/09/28  23:12:52  matt
 * Macroized palette flash system
 * 
 * Revision 1.110  1994/09/27  15:42:31  mike
 * Add names of Specials.
 * 
 * Revision 1.109  1994/09/27  00:02:23  mike
 * Yet more materialization center stuff.
 * 
 * Revision 1.108  1994/09/26  11:26:23  mike
 * Balance materialization centers.
 * 
 * Revision 1.107  1994/09/25  23:40:47  matt
 * Changed the object load & save code to read/write the structure fields one
 * at a time (rather than the whole structure at once).  This mean that the
 * object structure can be changed without breaking the load/save functions.
 * As a result of this change, the local_object data can be and has been 
 * incorporated into the object array.  Also, timeleft is now a property 
 * of all objects, and the object structure has been otherwise cleaned up.
 * 
 * Revision 1.106  1994/09/25  15:55:58  mike
 * Balance materialization centers, make them emit light, make them re-triggerable after awhile.
 * 
 * Revision 1.105  1994/09/24  17:42:33  mike
 * Making materialization centers be activated by triggers and balancing them.
 * 
 * Revision 1.104  1994/09/24  14:16:06  mike
 * Support new network constants.
 * 
 * Revision 1.103  1994/09/20  19:14:40  john
 * Massaged the sound system; used a better formula for determining
 * which l/r balance, also, put in Mike's stuff that searches for a connection
 * between the 2 sounds' segments, stopping for closed doors, etc.
 * 
 * Revision 1.102  1994/09/17  01:40:51  matt
 * Added status bar/sizable window mode, and in the process revamped the
 * whole cockpit mode system.
 * 
 * Revision 1.101  1994/08/31  20:57:25  matt
 * Cleaned up endlevel/death code
 * 
 * Revision 1.100  1994/08/30  17:54:20  mike
 * Slow down rate of creation of objects by materialization centers.
 * 
 * Revision 1.99  1994/08/29  11:47:01  john
 * Added warning if no control centers in mine.
 * 
 */


#pragma off (unreferenced)
static char rcsid[] = "$Id: fuelcen.c 1.2 1995/10/31 10:23:40 allender Exp $";
#pragma on (unreferenced)

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#include "fuelcen.h"
#include "gameseg.h"
#include "game.h"		// For FrameTime
#include "error.h"
#include "mono.h"
#include "gauges.h"
#include "vclip.h"
#include "fireball.h"
#include "robot.h"

#include "wall.h"
#include "sounds.h"
#include "morph.h"
#include "3d.h"
#include "bm.h"
#include "polyobj.h"
#include "ai.h"
#include "gamemine.h"
#include "gamesave.h"
#include "player.h"
#include "collide.h"
#include "laser.h"
#include "network.h"
#include "multi.h"
#include "multibot.h"

// The max number of fuel stations per mine.

fix Fuelcen_refill_speed = i2f(1);
fix Fuelcen_give_amount = i2f(25);
fix Fuelcen_max_amount = i2f(100);

// Every time a robot is created in the morphing code, it decreases capacity of the morpher
// by this amount... when capacity gets to 0, no more morphers...
fix EnergyToCreateOneRobot = i2f(1);

int Fuelcen_control_center_destroyed = 0;
int Fuelcen_seconds_left = 0;

#define MATCEN_HP_DEFAULT			F1_0*500; // Hitpoints
#define MATCEN_INTERVAL_DEFAULT	F1_0*5;	//  5 seconds

matcen_info RobotCenters[MAX_ROBOT_CENTERS];
int Num_robot_centers;

control_center_triggers ControlCenterTriggers;

FuelCenter Station[MAX_NUM_FUELCENS];
int Num_fuelcenters = 0;

segment * PlayerSegment= NULL;

#ifdef EDITOR
char	Special_names[MAX_CENTER_TYPES][11] = {
	"NOTHING   ",
	"FUELCEN   ",
	"REPAIRCEN ",
	"CONTROLCEN",
	"ROBOTMAKER",
};
#endif

//------------------------------------------------------------
// Resets all fuel center info
void fuelcen_reset()
{
	int i;

	Num_fuelcenters = 0;
	//mprintf( (0, "All fuel centers reset.\n"));

	for(i=0; i<MAX_SEGMENTS; i++ )
		Segments[i].special = SEGMENT_IS_NOTHING;

	Fuelcen_control_center_destroyed = 0;
	Num_robot_centers = 0;

}

#ifndef NDEBUG		//this is sometimes called by people from the debugger
void reset_all_robot_centers() 
{
	int i;

	// Remove all materialization centers
	for (i=0; i<Num_segments; i++)
		if (Segments[i].special == SEGMENT_IS_ROBOTMAKER) {
			Segments[i].special = SEGMENT_IS_NOTHING;
			Segments[i].matcen_num = -1;
		}
}
#endif

//------------------------------------------------------------
// Turns a segment into a fully charged up fuel center...
void fuelcen_create( segment * segp)
{
	int	station_type;

	station_type = segp->special;

	switch( station_type )	{
	case SEGMENT_IS_NOTHING:
		return;
	case SEGMENT_IS_FUELCEN:
	case SEGMENT_IS_REPAIRCEN:
	case SEGMENT_IS_CONTROLCEN:
	case SEGMENT_IS_ROBOTMAKER:
		break;
	default:
		Error( "Invalid station type %d in fuelcen.c\n", station_type );
	}

	Assert( (segp != NULL) );
	if ( segp == NULL ) return;

	Assert( Num_fuelcenters < MAX_NUM_FUELCENS );
	Assert( Num_fuelcenters > -1 );

	segp->value = Num_fuelcenters;
	Station[Num_fuelcenters].Type = station_type;
	Station[Num_fuelcenters].MaxCapacity = Fuelcen_max_amount;
	Station[Num_fuelcenters].Capacity = Station[Num_fuelcenters].MaxCapacity;
	Station[Num_fuelcenters].segnum = segp-Segments;
	Station[Num_fuelcenters].Timer = -1;
	Station[Num_fuelcenters].Flag = 0;
//	Station[Num_fuelcenters].NextRobotType = -1;
//	Station[Num_fuelcenters].last_created_obj=NULL;
//	Station[Num_fuelcenters].last_created_sig = -1;
	compute_segment_center(&Station[Num_fuelcenters].Center, segp );

//	if (station_type == SEGMENT_IS_ROBOTMAKER)
//		Station[Num_fuelcenters].Capacity = i2f(Difficulty_level + 3);

	//mprintf( (0, "Segment %d is assigned to be fuel center %d.\n", Station[Num_fuelcenters].segnum, Num_fuelcenters ));
	Num_fuelcenters++;
}

//------------------------------------------------------------
// Adds a matcen that already is a special type into the Station array.
// This function is separate from other fuelcens because we don't want values reset.
void matcen_create( segment * segp)
{
	int	station_type = segp->special;

	Assert( (segp != NULL) );
	Assert(station_type == SEGMENT_IS_ROBOTMAKER);
	if ( segp == NULL ) return;

	Assert( Num_fuelcenters < MAX_NUM_FUELCENS );
	Assert( Num_fuelcenters > -1 );

	segp->value = Num_fuelcenters;
	Station[Num_fuelcenters].Type = station_type;
	Station[Num_fuelcenters].Capacity = i2f(Difficulty_level + 3);
	Station[Num_fuelcenters].MaxCapacity = Station[Num_fuelcenters].Capacity;

	Station[Num_fuelcenters].segnum = segp-Segments;
	Station[Num_fuelcenters].Timer = -1;
	Station[Num_fuelcenters].Flag = 0;
//	Station[Num_fuelcenters].NextRobotType = -1;
//	Station[Num_fuelcenters].last_created_obj=NULL;
//	Station[Num_fuelcenters].last_created_sig = -1;
	compute_segment_center(&Station[Num_fuelcenters].Center, segp );

	segp->matcen_num = Num_robot_centers;
	Num_robot_centers++;

	RobotCenters[segp->matcen_num].hit_points = MATCEN_HP_DEFAULT;
	RobotCenters[segp->matcen_num].interval = MATCEN_INTERVAL_DEFAULT;
	RobotCenters[segp->matcen_num].segnum = segp-Segments;
	RobotCenters[segp->matcen_num].fuelcen_num = Num_fuelcenters;

	//mprintf( (0, "Segment %d is assigned to be fuel center %d.\n", Station[Num_fuelcenters].segnum, Num_fuelcenters ));
	Num_fuelcenters++;
}

//------------------------------------------------------------
// Adds a segment that already is a special type into the Station array.
void fuelcen_activate( segment * segp, int station_type )
{
	segp->special = station_type;

	if (segp->special == SEGMENT_IS_ROBOTMAKER)
		matcen_create( segp);
	else
		fuelcen_create( segp);
	
}

//	The lower this number is, the more quickly the center can be re-triggered.
//	If it's too low, it can mean all the robots won't be put out, but for about 5
//	robots, that's not real likely.
#define	MATCEN_LIFE (i2f(30-2*Difficulty_level))

//------------------------------------------------------------
//	Trigger (enable) the materialization center in segment segnum
void trigger_matcen(int segnum)
{
	segment		*segp = &Segments[segnum];
	vms_vector	pos, delta;
	FuelCenter	*robotcen;
	int			objnum;

	mprintf((0, "Trigger matcen, segment %i\n", segnum));

	Assert(segp->special == SEGMENT_IS_ROBOTMAKER);
	Assert(segp->matcen_num < Num_fuelcenters);
	Assert((segp->matcen_num >= 0) && (segp->matcen_num <= Highest_segment_index));

	robotcen = &Station[RobotCenters[segp->matcen_num].fuelcen_num];

	if (robotcen->Enabled == 1)
		return;

	if (!robotcen->Lives)
		return;

	robotcen->Lives--;
	robotcen->Timer = F1_0*1000;	//	Make sure the first robot gets emitted right away.
	robotcen->Enabled = 1;			//	Say this center is enabled, it can create robots.
	robotcen->Capacity = i2f(Difficulty_level + 3);
	robotcen->Disable_time = MATCEN_LIFE;

	//	Create a bright object in the segment.
	pos = robotcen->Center;
	vm_vec_sub(&delta, &Vertices[Segments[segnum].verts[0]], &robotcen->Center);
	vm_vec_scale_add2(&pos, &delta, F1_0/2);
	objnum = obj_create( OBJ_LIGHT, 0, segnum, &pos, NULL, 0, CT_LIGHT, MT_NONE, RT_NONE );
	if (objnum != -1) {
		Objects[objnum].lifeleft = MATCEN_LIFE;
		Objects[objnum].ctype.light_info.intensity = i2f(8);	//	Light cast by a fuelcen.
	} else {
		mprintf((1, "Can't create invisible flare for matcen.\n"));
		Int3();
	}
//	mprintf((0, "Created invisibile flare, object=%i, segment=%i, pos=%7.3f %7.3f%7.3f\n", objnum, segnum, f2fl(pos.x), f2fl(pos.y), f2fl(pos.z)));
}

#ifdef EDITOR
//------------------------------------------------------------
// Takes away a segment's fuel center properties.
//	Deletes the segment point entry in the FuelCenter list.
void fuelcen_delete( segment * segp )
{
	int i, j;

Restart: ;

	for (i=0; i<Num_fuelcenters; i++ )	{
		if ( Station[i].segnum == segp-Segments )	{

			// If Robot maker is deleted, fix Segments and RobotCenters.
			if (Station[i].Type == SEGMENT_IS_ROBOTMAKER) {
				Num_robot_centers--;

				for (j=segp->matcen_num; j<Num_robot_centers; j++)
					RobotCenters[j] = RobotCenters[j+1];

				for (j=0; j<Num_fuelcenters; j++) {
					if ( Station[j].Type == SEGMENT_IS_ROBOTMAKER )
						if ( Segments[Station[j].segnum].matcen_num > segp->matcen_num )
							Segments[Station[j].segnum].matcen_num--;
				}
			}
		
			Num_fuelcenters--;
			for (j=i; j<Num_fuelcenters; j++ )	{
				Station[i] = Station[i+1];
				Segments[Station[i].segnum].value = i;
			}
			segp->special = 0;
			goto Restart;
		}
	}

}
#endif

#define	ROBOT_GEN_TIME (i2f(5))

object * create_morph_robot( segment *segp, vms_vector *object_pos, int object_id)
{
	short		objnum;
	object	*obj;
	int		default_behavior;

	Players[Player_num].num_robots_level++;
	Players[Player_num].num_robots_total++;

	objnum = obj_create(OBJ_ROBOT, object_id, segp-Segments, object_pos,
				&vmd_identity_matrix, Polygon_models[Robot_info[object_id].model_num].rad,
				CT_AI, MT_PHYSICS, RT_POLYOBJ);

	if ( objnum < 0 ) {
		mprintf((1, "Can't create morph robot.  Aborting morph.\n"));
		Int3();
		return NULL;
	}

	obj = &Objects[objnum];

	//Set polygon-object-specific data 

	obj->rtype.pobj_info.model_num = Robot_info[obj->id].model_num;
	obj->rtype.pobj_info.subobj_flags = 0;

	//set Physics info

	obj->mtype.phys_info.mass = Robot_info[obj->id].mass;
	obj->mtype.phys_info.drag = Robot_info[obj->id].drag;

	obj->mtype.phys_info.flags |= (PF_LEVELLING);

	obj->shields = Robot_info[obj->id].strength;
	
	default_behavior = AIB_NORMAL;
	if (object_id == 10)						//	This is a toaster guy!
		default_behavior = AIB_RUN_FROM;

	init_ai_object(obj-Objects, default_behavior, -1 );		//	Note, -1 = segment this robot goes to to hide, should probably be something useful

	create_n_segment_path(obj, 6, -1);		//	Create a 6 segment path from creation point.

	if (default_behavior == AIB_RUN_FROM)
		Ai_local_info[objnum].mode = AIM_RUN_FROM_OBJECT;

	return obj;
}

int Num_extry_robots = 15;

#ifndef NDEBUG
int	FrameCount_last_msg = 0;
#endif

//	----------------------------------------------------------------------------------------------------------
void robotmaker_proc( FuelCenter * robotcen )
{
	fix		dist_to_player;
	vms_vector	cur_object_loc; //, direction;
	int		matcen_num, segnum, objnum;
	object	*obj;
	fix		top_time;
	vms_vector	direction;

	if (robotcen->Enabled == 0)
		return;

	if (robotcen->Disable_time > 0) {
		robotcen->Disable_time -= FrameTime;
		if (robotcen->Disable_time <= 0) {
			mprintf((0, "Robot center #%i gets disabled due to time running out.\n", robotcen-Station));
			robotcen->Enabled = 0;
		}
	}

	// mprintf((0, "Capacity of robot maker #%i is %i\n", robotcen - Station, robotcen->Capacity));

	//	No robot making in multiplayer mode.
#ifdef NETWORK
#ifndef MAC_SHAREWARE
	if ((Game_mode & GM_MULTI) && (!(Game_mode & GM_MULTI_ROBOTS) || !network_i_am_master()))
		return;
#else
	if (Game_mode & GM_MULTI)
		return;
#endif
#endif

	// Wait until transmorgafier has capacity to make a robot...
	if ( robotcen->Capacity <= 0 ) {
		return;
	}

	matcen_num = Segments[robotcen->segnum].matcen_num;
	//mprintf((0, "Robotmaker #%i flags = %8x\n", matcen_num, RobotCenters[matcen_num].robot_flags));

	if ( matcen_num == -1 ) {
		mprintf((0, "Non-functional robotcen at %d\n", robotcen->segnum));
		return;
	}

	if (RobotCenters[matcen_num].robot_flags == 0) {
		//mprintf((0, "robot_flags = 0 at robot maker #%i\n", RobotCenters[matcen_num].robot_flags));
		return;
	}

	// Wait until we have a free slot for this puppy...
   //	  <<<<<<<<<<<<<<<< Num robots in mine >>>>>>>>>>>>>>>>>>>>>>>>>>    <<<<<<<<<<<< Max robots in mine >>>>>>>>>>>>>>>
	if ( (Players[Player_num].num_robots_level - Players[Player_num].num_kills_level) >= (Gamesave_num_org_robots + Num_extry_robots ) ) {
		#ifndef NDEBUG
		if (FrameCount > FrameCount_last_msg + 20) {
			mprintf((0, "Cannot morph until you kill one!\n"));
			FrameCount_last_msg = FrameCount;
		}
		#endif
		return;
	}

	robotcen->Timer += FrameTime;

	switch( robotcen->Flag )	{
	case 0:		// Wait until next robot can generate
		if (Game_mode & GM_MULTI) 
		{
			top_time = ROBOT_GEN_TIME;	
		}
		else 
		{
			dist_to_player = vm_vec_dist_quick( &ConsoleObject->pos, &robotcen->Center );
			top_time = dist_to_player/64 + rand() * 2 + F1_0*2;
			if ( top_time > ROBOT_GEN_TIME )
				top_time = ROBOT_GEN_TIME + rand();
			if ( top_time < F1_0*2 )
				top_time = F1_0*3/2 + rand()*2;
		}

 		// mprintf( (0, "Time between morphs %d seconds, dist_to_player = %7.3f\n", f2i(top_time), f2fl(dist_to_player) ));

		if (robotcen->Timer > top_time )	{
			int	count=0;
			int	i, my_station_num = robotcen-Station;
			object *obj;

			//	Make sure this robotmaker hasn't put out its max without having any of them killed.
			for (i=0; i<=Highest_object_index; i++)
				if (Objects[i].type == OBJ_ROBOT)
					if ((Objects[i].matcen_creator^0x80) == my_station_num)
						count++;
			if (count > Difficulty_level + 3) {
				mprintf((0, "Cannot morph: center %i has already put out %i robots.\n", my_station_num, count));
				robotcen->Timer /= 2;
				return;
			}

			//	Whack on any robot or player in the matcen segment.
			count=0;
			segnum = robotcen->segnum;
			for (objnum=Segments[segnum].objects;objnum!=-1;objnum=Objects[objnum].next)	{
				count++;
				if ( count > MAX_OBJECTS )	{
					mprintf((0, "Object list in segment %d is circular.", segnum ));
					Int3();
					return;
				}
				if (Objects[objnum].type==OBJ_ROBOT) {
					collide_robot_and_materialization_center(&Objects[objnum]);
					robotcen->Timer = top_time/2;
					return;
				} else if (Objects[objnum].type==OBJ_PLAYER ) {
					collide_player_and_materialization_center(&Objects[objnum]);
					robotcen->Timer = top_time/2;
					return;
				}
			}

			compute_segment_center(&cur_object_loc, &Segments[robotcen->segnum]);
			// HACK!!! The 10 under here should be something equal to the 1/2 the size of the segment.
			obj = object_create_explosion(robotcen->segnum, &cur_object_loc, i2f(10), VCLIP_MORPHING_ROBOT );

			if (obj)
				extract_orient_from_segment(&obj->orient,&Segments[robotcen->segnum]);

			if ( Vclip[VCLIP_MORPHING_ROBOT].sound_num > -1 )		{
				digi_link_sound_to_pos( Vclip[VCLIP_MORPHING_ROBOT].sound_num, robotcen->segnum, 0, &cur_object_loc, 0, F1_0 );
			}
			robotcen->Flag	= 1;
			robotcen->Timer = 0;

		}
		break;
	case 1:			// Wait until 1/2 second after VCLIP started.
		if (robotcen->Timer > (Vclip[VCLIP_MORPHING_ROBOT].play_time/2) )	{

			robotcen->Capacity -= EnergyToCreateOneRobot;
			robotcen->Flag = 0;

			robotcen->Timer = 0;
			compute_segment_center(&cur_object_loc, &Segments[robotcen->segnum]);

			// If this is the first materialization, set to valid robot.
			if (RobotCenters[matcen_num].robot_flags != 0) {
				int	type;
				uint	flags;
				byte	legal_types[32];		//	32 bits in a word, the width of robot_flags.
				int	num_types, robot_index;

				robot_index = 0;
				num_types = 0;
				flags = RobotCenters[matcen_num].robot_flags;
				while (flags) {
					if (flags & 1)
						legal_types[num_types++] = robot_index;
					flags >>= 1;
					robot_index++;
				}

				//mprintf((0, "Flags = %08x, %2i legal types to morph: \n", RobotCenters[matcen_num].robot_flags, num_types));
				//for (i=0; i<num_types; i++)
				//	mprintf((0, "%2i ", legal_types[i]));
				//mprintf((0, "\n"));

				if (num_types == 1)
					type = legal_types[0];
				else
					type = legal_types[(rand() * num_types) / 32768];

				mprintf((0, "Morph: (type = %i) (seg = %i) (capacity = %08x)\n", type, robotcen->segnum, robotcen->Capacity));
				obj = create_morph_robot(&Segments[robotcen->segnum], &cur_object_loc, type );
				if (obj != NULL) {
#ifndef MAC_SHAREWARE
#ifdef NETWORK
					if (Game_mode & GM_MULTI)
						multi_send_create_robot(robotcen-Station, obj-Objects, type);
#endif
#endif
					obj->matcen_creator = robotcen-Station | 0x80;

					// Make object faces player...
					vm_vec_sub( &direction, &ConsoleObject->pos,&obj->pos );
					vm_vector_2_matrix( &obj->orient, &direction, &obj->orient.uvec, NULL);
	
					morph_start( obj );
					//robotcen->last_created_obj = obj;
					//robotcen->last_created_sig = robotcen->last_created_obj->signature;
				} else
					mprintf((0, "Warning: create_morph_robot returned NULL (no objects left?)\n"));

			}
  
		}
		break;
	default:
		robotcen->Flag = 0;
		robotcen->Timer = 0;
	}
}

#define	BASE_CONTROL_CENTER_EXPLOSION_TIME	30
#define	DIFF_CONTROL_CENTER_EXPLOSION_TIME	(BASE_CONTROL_CENTER_EXPLOSION_TIME + (NDL-Difficulty_level-1)*5)

#define COUNTDOWN_VOICE_TIME (i2f(DIFF_CONTROL_CENTER_EXPLOSION_TIME)-fl2f(12.75))

void controlcen_proc( FuelCenter * controlcen )
{
	fix old_time;
	int	fc;

//	mprintf( (0, "CCT: %.1f\n", f2fl(controlcen->Timer)));

	if (!Fuelcen_control_center_destroyed)	return;

	//	Control center destroyed, rock the player's ship.
	fc = Fuelcen_seconds_left;
	if (fc > 16)
		fc = 16;
	ConsoleObject->mtype.phys_info.rotvel.x += fixmul(rand() - 16384, 3*F1_0/16 + (F1_0*(16-fc))/32);
	ConsoleObject->mtype.phys_info.rotvel.z += fixmul(rand() - 16384, 3*F1_0/16 + (F1_0*(16-fc))/32);
	//	Hook in the rumble sound effect here.

	old_time = controlcen->Timer;
	controlcen->Timer += RealFrameTime;			//timer_get_approx_seconds
	Fuelcen_seconds_left = DIFF_CONTROL_CENTER_EXPLOSION_TIME - f2i(controlcen->Timer);
	if ( (old_time < COUNTDOWN_VOICE_TIME ) && (controlcen->Timer >= COUNTDOWN_VOICE_TIME) )	{
			digi_play_sample( SOUND_COUNTDOWN_13_SECS, F3_0 );
	}
	if ( f2i(old_time) != f2i(controlcen->Timer) )	{
		if ( (Fuelcen_seconds_left>=0) && (Fuelcen_seconds_left<10) ) 
			digi_play_sample( SOUND_COUNTDOWN_0_SECS+Fuelcen_seconds_left, F3_0 );
		if ( Fuelcen_seconds_left==DIFF_CONTROL_CENTER_EXPLOSION_TIME-1)
			digi_play_sample( SOUND_COUNTDOWN_29_SECS, F3_0 );
	}						

	if (controlcen->Timer < i2f(DIFF_CONTROL_CENTER_EXPLOSION_TIME)) {
		vms_vector vp;	//,v,c;
		fix size;
		compute_segment_center(&vp, &Segments[controlcen->segnum]);
		size = (0x50000*f2i(controlcen->Timer)*(FrameTime & 0xF))/16;
		size = controlcen->Timer / (fl2f(0.65));
		old_time = old_time / (fl2f(0.65));
		if (size != old_time && (controlcen->Timer > (5*F1_0) ))		{			// Every 2 seconds!
			//@@object_create_explosion( controlcen->segnum, &vp, size*10, FrameTime & 7);
			object_create_explosion( controlcen->segnum, &vp, size*10, VCLIP_SMALL_EXPLOSION);
			digi_play_sample( SOUND_CONTROL_CENTER_WARNING_SIREN, F3_0 );
		}
	}  else {
		int flash_value;

		if (old_time < i2f(DIFF_CONTROL_CENTER_EXPLOSION_TIME))
			digi_play_sample( SOUND_MINE_BLEW_UP, F1_0 );

		flash_value = f2i( (controlcen->Timer-i2f(DIFF_CONTROL_CENTER_EXPLOSION_TIME))*(64/4));	// 4 seconds to total whiteness
		PALETTE_FLASH_SET(flash_value,flash_value,flash_value);

		//gauge_message( "YOU'RE TOO SLOW! THE MINE BLEW UP!" );
		if (PaletteBlueAdd > 64 )	{
			gr_set_current_canvas( NULL );		
			gr_clear_canvas(BM_XRGB(31,31,31));		//make screen all white to match palette effect
			reset_cockpit();								//force cockpit redraw next time
			reset_palette_add();							//restore palette for death message
			controlcen->Timer = -1;
			controlcen->MaxCapacity = Fuelcen_max_amount;
			//gauge_message( "Control Center Reset" );
			DoPlayerDead();		//kill_player();
		}																				
	}
}

#define M_PI 3.14159

//-------------------------------------------------------------
// Called once per frame, replenishes fuel supply.
void fuelcen_update_all()
{
	int i;
	fix AmountToreplenish;
	
	AmountToreplenish = fixmul(FrameTime,Fuelcen_refill_speed);

	for (i=0; i<Num_fuelcenters; i++ )	{
		if ( Station[i].Type == SEGMENT_IS_ROBOTMAKER )	{
			if (! (Game_suspended & SUSP_ROBOTS))
				robotmaker_proc( &Station[i] );
		} else if ( Station[i].Type == SEGMENT_IS_CONTROLCEN )	{
			controlcen_proc( &Station[i] );
	
		} else if ( (Station[i].MaxCapacity > 0) && (PlayerSegment!=&Segments[Station[i].segnum]) )	{
			if ( Station[i].Capacity < Station[i].MaxCapacity )	{
 				Station[i].Capacity += AmountToreplenish;
				//mprintf( (0, "Fuel center %d replenished to %d.\n", i, f2i(Station[i].Capacity) ));
				if ( Station[i].Capacity >= Station[i].MaxCapacity )		{
					Station[i].Capacity = Station[i].MaxCapacity;
					//gauge_message( "Fuel center is fully recharged!    " );
				}
			}
		}
	}
}

//--unused-- //-------------------------------------------------------------
//--unused-- // replenishes all fuel supplies.
//--unused-- void fuelcen_replenish_all()
//--unused-- {
//--unused-- 	int i;
//--unused-- 
//--unused-- 	for (i=0; i<Num_fuelcenters; i++ )	{
//--unused-- 		Station[i].Capacity = Station[i].MaxCapacity;
//--unused-- 	}
//--unused-- 	//mprintf( (0, "All fuel centers are replenished\n" ));
//--unused-- 
//--unused-- }

//-------------------------------------------------------------
fix fuelcen_give_fuel(segment *segp, fix MaxAmountCanTake )
{
	Assert( segp != NULL );

	PlayerSegment = segp;

	if ( (segp) && (segp->special==SEGMENT_IS_FUELCEN) )	{
		fix amount;

//		if (Station[segp->value].MaxCapacity<=0)	{
//			HUD_init_message( "Fuelcenter %d is destroyed.", segp->value );
//			return 0;
//		}

//		if (Station[segp->value].Capacity<=0)	{
//			HUD_init_message( "Fuelcenter %d is empty.", segp->value );
//			return 0;
//		}

		if (MaxAmountCanTake <= 0 )	{
//			//gauge_message( "Fueled up!");
			return 0;
		}

		amount = fixmul(FrameTime,Fuelcen_give_amount);

		if (amount > MaxAmountCanTake )
			amount = MaxAmountCanTake;

//		if (!(Game_mode & GM_MULTI))
//			if ( Station[segp->value].Capacity < amount  )	{
//				amount = Station[segp->value].Capacity;
//				Station[segp->value].Capacity = 0;
//			} else {
//				Station[segp->value].Capacity -= amount;
//			}

		digi_play_sample( SOUND_REFUEL_STATION_GIVING_FUEL, F1_0/2 );

		#ifdef NETWORK
		if (Game_mode & GM_MULTI)
			multi_send_play_sound(SOUND_REFUEL_STATION_GIVING_FUEL, F1_0/2);
		#endif

		//HUD_init_message( "Fuelcen %d has %d/%d fuel", segp->value,f2i(Station[segp->value].Capacity),f2i(Station[segp->value].MaxCapacity) );
		return amount;

	} else {
		return 0;
	}
}

//--unused-- //-----------------------------------------------------------
//--unused-- // Damages a fuel center
//--unused-- void fuelcen_damage(segment *segp, fix damage )
//--unused-- {
//--unused-- 	//int i;
//--unused-- 	// int	station_num = segp->value;
//--unused-- 
//--unused-- 	Assert( segp != NULL );
//--unused-- 	if ( segp == NULL ) return;
//--unused-- 
//--unused-- 	mprintf((0, "Obsolete function fuelcen_damage() called with seg=%i, damage=%7.3f\n", segp-Segments, f2fl(damage)));
//--unused-- 	switch( segp->special )	{
//--unused-- 	case SEGMENT_IS_NOTHING:
//--unused-- 		return;
//--unused-- 	case SEGMENT_IS_ROBOTMAKER:
//--unused-- //--		// Robotmaker hit by laser
//--unused-- //--		if (Station[station_num].MaxCapacity<=0 )	{
//--unused-- //--			// Shooting a already destroyed materializer
//--unused-- //--		} else {
//--unused-- //--			Station[station_num].MaxCapacity -= damage;
//--unused-- //--			if (Station[station_num].Capacity > Station[station_num].MaxCapacity )	{
//--unused-- //--				Station[station_num].Capacity = Station[station_num].MaxCapacity;
//--unused-- //--			}
//--unused-- //--			if (Station[station_num].MaxCapacity <= 0 )	{
//--unused-- //--				Station[station_num].MaxCapacity = 0;
//--unused-- //--				// Robotmaker dead
//--unused-- //--				for (i=0; i<6; i++ )
//--unused-- //--					segp->sides[i].tmap_num2 = 0;
//--unused-- //--			}
//--unused-- //--		}
//--unused-- //--		//mprintf( (0, "Materializatormografier has %x capacity left\n", Station[station_num].MaxCapacity ));
//--unused-- 		break;
//--unused-- 	case SEGMENT_IS_FUELCEN:	
//--unused-- //--		digi_play_sample( SOUND_REFUEL_STATION_HIT );
//--unused-- //--		if (Station[station_num].MaxCapacity>0 )	{
//--unused-- //--			Station[station_num].MaxCapacity -= damage;
//--unused-- //--			if (Station[station_num].Capacity > Station[station_num].MaxCapacity )	{
//--unused-- //--				Station[station_num].Capacity = Station[station_num].MaxCapacity;
//--unused-- //--			}
//--unused-- //--			if (Station[station_num].MaxCapacity <= 0 )	{
//--unused-- //--				Station[station_num].MaxCapacity = 0;
//--unused-- //--				digi_play_sample( SOUND_REFUEL_STATION_DESTROYED );
//--unused-- //--			}
//--unused-- //--		} else {
//--unused-- //--			Station[station_num].MaxCapacity = 0;
//--unused-- //--		}
//--unused-- //--		HUD_init_message( "Fuelcenter %d damaged", station_num );
//--unused-- 		break;
//--unused-- 	case SEGMENT_IS_REPAIRCEN:
//--unused-- 		break;
//--unused-- 	case SEGMENT_IS_CONTROLCEN:
//--unused-- 		break;
//--unused-- 	default:
//--unused-- 		Error( "Invalid type in fuelcen.c" );
//--unused-- 	}
//--unused-- }

//--unused-- //	----------------------------------------------------------------------------------------------------------
//--unused-- fixang my_delta_ang(fixang a,fixang b)
//--unused-- {
//--unused-- 	fixang delta0,delta1;
//--unused-- 
//--unused-- 	return (abs(delta0 = a - b) < abs(delta1 = b - a)) ? delta0 : delta1;
//--unused-- 
//--unused-- }

//--unused-- //	----------------------------------------------------------------------------------------------------------
//--unused-- //return though which side of seg0 is seg1
//--unused-- int john_find_connect_side(int seg0,int seg1)
//--unused-- {
//--unused-- 	segment *Seg=&Segments[seg0];
//--unused-- 	int i;
//--unused-- 
//--unused-- 	for (i=MAX_SIDES_PER_SEGMENT;i--;) if (Seg->children[i]==seg1) return i;
//--unused-- 
//--unused-- 	return -1;
//--unused-- }

//	----------------------------------------------------------------------------------------------------------
//--unused-- vms_angvec start_angles, delta_angles, goal_angles;
//--unused-- vms_vector start_pos, delta_pos, goal_pos;
//--unused-- int FuelStationSeg;
//--unused-- fix current_time,delta_time;
//--unused-- int next_side, side_index;
//--unused-- int * sidelist;

//--repair-- int Repairing;
//--repair-- vms_vector repair_save_uvec;		//the player's upvec when enter repaircen
//--repair-- object *RepairObj=NULL;		//which object getting repaired
//--repair-- int disable_repair_center=0;
//--repair-- fix repair_rate;
//--repair-- #define FULL_REPAIR_RATE i2f(10)

//--unused-- ubyte save_control_type,save_movement_type;

//--unused-- int SideOrderBack[] = {WFRONT, WRIGHT, WTOP, WLEFT, WBOTTOM, WBACK};
//--unused-- int SideOrderFront[] =  {WBACK, WLEFT, WTOP, WRIGHT, WBOTTOM, WFRONT};
//--unused-- int SideOrderLeft[] =  { WRIGHT, WBACK, WTOP, WFRONT, WBOTTOM, WLEFT };
//--unused-- int SideOrderRight[] =  { WLEFT, WFRONT, WTOP, WBACK, WBOTTOM, WRIGHT };
//--unused-- int SideOrderTop[] =  { WBOTTOM, WLEFT, WBACK, WRIGHT, WFRONT, WTOP };
//--unused-- int SideOrderBottom[] =  { WTOP, WLEFT, WFRONT, WRIGHT, WBACK, WBOTTOM };

//--unused-- int SideUpVector[] = {WBOTTOM, WFRONT, WBOTTOM, WFRONT, WBOTTOM, WBOTTOM };

//--repair-- //	----------------------------------------------------------------------------------------------------------
//--repair-- void refuel_calc_deltas(object *obj, int next_side, int repair_seg)
//--repair-- {
//--repair-- 	vms_vector nextcenter, headfvec, *headuvec;
//--repair-- 	vms_matrix goal_orient;
//--repair-- 
//--repair-- 	// Find time for this movement
//--repair-- 	delta_time = F1_0;		// one second...
//--repair-- 		
//--repair-- 	// Find start and goal position
//--repair-- 	start_pos = obj->pos;
//--repair-- 	
//--repair-- 	// Find delta position to get to goal position
//--repair-- 	compute_segment_center(&goal_pos,&Segments[repair_seg]);
//--repair-- 	vm_vec_sub( &delta_pos,&goal_pos,&start_pos);
//--repair-- 	
//--repair-- 	// Find start angles
//--repair-- 	//angles_from_vector(&start_angles,&obj->orient.fvec);
//--repair-- 	vm_extract_angles_matrix(&start_angles,&obj->orient);
//--repair-- 	
//--repair-- 	// Find delta angles to get to goal orientation
//--repair-- 	med_compute_center_point_on_side(&nextcenter,&Segments[repair_seg],next_side);
//--repair-- 	vm_vec_sub(&headfvec,&nextcenter,&goal_pos);
//--repair-- 	//mprintf( (0, "Next_side = %d, Head fvec = %d,%d,%d\n", next_side, headfvec.x, headfvec.y, headfvec.z ));
//--repair-- 
//--repair-- 	if (next_side == 5)						//last side
//--repair-- 		headuvec = &repair_save_uvec;
//--repair-- 	else
//--repair-- 		headuvec = &Segments[repair_seg].sides[SideUpVector[next_side]].normals[0];
//--repair-- 
//--repair-- 	vm_vector_2_matrix(&goal_orient,&headfvec,headuvec,NULL);
//--repair-- 	vm_extract_angles_matrix(&goal_angles,&goal_orient);
//--repair-- 	delta_angles.p = my_delta_ang(start_angles.p,goal_angles.p);
//--repair-- 	delta_angles.b = my_delta_ang(start_angles.b,goal_angles.b);
//--repair-- 	delta_angles.h = my_delta_ang(start_angles.h,goal_angles.h);
//--repair-- 	current_time = 0;
//--repair-- 	Repairing = 0;
//--repair-- }
//--repair-- 
//--repair-- //	----------------------------------------------------------------------------------------------------------
//--repair-- //if repairing, cut it short
//--repair-- abort_repair_center()
//--repair-- {
//--repair-- 	if (!RepairObj || side_index==5)
//--repair-- 		return;
//--repair-- 
//--repair-- 	current_time = 0;
//--repair-- 	side_index = 5;
//--repair-- 	next_side = sidelist[side_index];
//--repair-- 	refuel_calc_deltas(RepairObj, next_side, FuelStationSeg);
//--repair-- }
//--repair-- 
//--repair-- //	----------------------------------------------------------------------------------------------------------
//--repair-- void repair_ship_damage()
//--repair-- {
//--repair--  	//mprintf((0,"Repairing ship damage\n"));
//--repair-- }
//--repair-- 
//--repair-- //	----------------------------------------------------------------------------------------------------------
//--repair-- int refuel_do_repair_effect( object * obj, int first_time, int repair_seg )	{
//--repair-- 
//--repair-- 	obj->mtype.phys_info.velocity.x = 0;				
//--repair-- 	obj->mtype.phys_info.velocity.y = 0;				
//--repair-- 	obj->mtype.phys_info.velocity.z = 0;				
//--repair-- 
//--repair-- 	if (first_time)	{
//--repair-- 		int entry_side;
//--repair-- 		current_time = 0;
//--repair-- 
//--repair-- 		digi_play_sample( SOUND_REPAIR_STATION_PLAYER_ENTERING, F1_0 );
//--repair-- 
//--repair-- 		entry_side = john_find_connect_side(repair_seg,obj->segnum );
//--repair-- 		Assert( entry_side > -1 );
//--repair-- 
//--repair-- 		switch( entry_side )	{
//--repair-- 		case WBACK: sidelist = SideOrderBack; break;
//--repair-- 		case WFRONT: sidelist = SideOrderFront; break;
//--repair-- 		case WLEFT: sidelist = SideOrderLeft; break;
//--repair-- 		case WRIGHT: sidelist = SideOrderRight; break;
//--repair-- 		case WTOP: sidelist = SideOrderTop; break;
//--repair-- 		case WBOTTOM: sidelist = SideOrderBottom; break;
//--repair-- 		}
//--repair-- 		side_index = 0;
//--repair-- 		next_side = sidelist[side_index];
//--repair-- 
//--repair-- 		refuel_calc_deltas(obj,next_side, repair_seg);
//--repair-- 	} 
//--repair-- 
//--repair-- 	//update shields
//--repair-- 	if (Players[Player_num].shields < MAX_SHIELDS) {	//if above max, don't mess with it
//--repair-- 
//--repair-- 		Players[Player_num].shields += fixmul(FrameTime,repair_rate);
//--repair-- 
//--repair-- 		if (Players[Player_num].shields > MAX_SHIELDS)
//--repair-- 			Players[Player_num].shields = MAX_SHIELDS;
//--repair-- 	}
//--repair-- 
//--repair-- 	current_time += FrameTime;
//--repair-- 
//--repair-- 	if (current_time >= delta_time )	{
//--repair-- 		vms_angvec av;
//--repair-- 		obj->pos = goal_pos;
//--repair-- 		av	= goal_angles;
//--repair-- 		vm_angles_2_matrix(&obj->orient,&av);
//--repair-- 
//--repair-- 		if (side_index >= 5 )	
//--repair-- 			return 1;		// Done being repaired...
//--repair-- 
//--repair-- 		if (Repairing==0)		{
//--repair-- 			//mprintf( (0, "<MACHINE EFFECT ON SIDE %d>\n", next_side ));
//--repair-- 			//digi_play_sample( SOUND_REPAIR_STATION_FIXING );
//--repair-- 			Repairing=1;
//--repair-- 
//--repair-- 			switch( next_side )	{
//--repair-- 			case 0:	digi_play_sample( SOUND_REPAIR_STATION_FIXING_1,F1_0 ); break;
//--repair-- 			case 1:	digi_play_sample( SOUND_REPAIR_STATION_FIXING_2,F1_0 ); break;
//--repair-- 			case 2:	digi_play_sample( SOUND_REPAIR_STATION_FIXING_3,F1_0 ); break;
//--repair-- 			case 3:	digi_play_sample( SOUND_REPAIR_STATION_FIXING_4,F1_0 ); break;
//--repair-- 			case 4:	digi_play_sample( SOUND_REPAIR_STATION_FIXING_1,F1_0 ); break;
//--repair-- 			case 5:	digi_play_sample( SOUND_REPAIR_STATION_FIXING_2,F1_0 ); break;
//--repair-- 			}
//--repair-- 		
//--repair-- 			repair_ship_damage();
//--repair-- 
//--repair-- 		}
//--repair-- 
//--repair-- 		if (current_time >= (delta_time+(F1_0/2)) )	{
//--repair-- 			current_time = 0;
//--repair-- 			// Find next side...
//--repair-- 			side_index++;
//--repair-- 			if (side_index >= 6 ) return 1;
//--repair-- 			next_side = sidelist[side_index];
//--repair-- 	
//--repair-- 			refuel_calc_deltas(obj, next_side, repair_seg);
//--repair-- 		}
//--repair-- 
//--repair-- 	} else {
//--repair-- 		fix factor, p,b,h;	
//--repair-- 		vms_angvec av;
//--repair-- 
//--repair-- 		factor = fixdiv( current_time,delta_time );
//--repair-- 
//--repair-- 		// Find object's current position
//--repair-- 		obj->pos = delta_pos;
//--repair-- 		vm_vec_scale( &obj->pos, factor );
//--repair-- 		vm_vec_add2( &obj->pos, &start_pos );
//--repair-- 			
//--repair-- 		// Find object's current orientation
//--repair-- 		p	= fixmul(delta_angles.p,factor);
//--repair-- 		b	= fixmul(delta_angles.b,factor);
//--repair-- 		h	= fixmul(delta_angles.h,factor);
//--repair-- 		av.p = (fixang)p + start_angles.p;
//--repair-- 		av.b = (fixang)b + start_angles.b;
//--repair-- 		av.h = (fixang)h + start_angles.h;
//--repair-- 		vm_angles_2_matrix(&obj->orient,&av);
//--repair-- 
//--repair-- 	}
//--repair-- 
//--repair-- 	update_object_seg(obj);		//update segment
//--repair-- 
//--repair-- 	return 0;
//--repair-- }
//--repair-- 
//--repair-- //	----------------------------------------------------------------------------------------------------------
//--repair-- //do the repair center for this frame
//--repair-- void do_repair_sequence(object *obj)
//--repair-- {
//--repair-- 	Assert(obj == RepairObj);
//--repair-- 
//--repair-- 	if (refuel_do_repair_effect( obj, 0, FuelStationSeg )) {
//--repair-- 		if (Players[Player_num].shields < MAX_SHIELDS)
//--repair-- 			Players[Player_num].shields = MAX_SHIELDS;
//--repair-- 		obj->control_type = save_control_type;
//--repair-- 		obj->movement_type = save_movement_type;
//--repair-- 		disable_repair_center=1;
//--repair-- 		RepairObj = NULL;
//--repair-- 
//--repair-- 
//--repair-- 		//the two lines below will spit the player out of the rapair center,
//--repair-- 		//but what happen is that the ship just bangs into the door
//--repair-- 		//if (obj->movement_type == MT_PHYSICS)
//--repair-- 		//	vm_vec_copy_scale(&obj->mtype.phys_info.velocity,&obj->orient.fvec,i2f(200));
//--repair-- 	}
//--repair-- 
//--repair-- }
//--repair-- 
//--repair-- //	----------------------------------------------------------------------------------------------------------
//--repair-- //see if we should start the repair center
//--repair-- void check_start_repair_center(object *obj)
//--repair-- {
//--repair-- 	if (RepairObj != NULL) return;		//already in repair center
//--repair-- 
//--repair-- 	if (Lsegments[obj->segnum].special_type & SS_REPAIR_CENTER) {
//--repair-- 
//--repair-- 		if (!disable_repair_center) {
//--repair-- 			//have just entered repair center
//--repair-- 
//--repair-- 			RepairObj = obj;
//--repair-- 			repair_save_uvec = obj->orient.uvec;
//--repair-- 
//--repair-- 			repair_rate = fixmuldiv(FULL_REPAIR_RATE,(MAX_SHIELDS - Players[Player_num].shields),MAX_SHIELDS);
//--repair-- 
//--repair-- 			save_control_type = obj->control_type;
//--repair-- 			save_movement_type = obj->movement_type;
//--repair-- 
//--repair-- 			obj->control_type = CT_REPAIRCEN;
//--repair-- 			obj->movement_type = MT_NONE;
//--repair-- 
//--repair-- 			FuelStationSeg	= Lsegments[obj->segnum].special_segment;
//--repair-- 			Assert(FuelStationSeg != -1);
//--repair-- 
//--repair-- 			if (refuel_do_repair_effect( obj, 1, FuelStationSeg )) {
//--repair-- 				Int3();		//can this happen?
//--repair-- 				obj->control_type = CT_FLYING;
//--repair-- 				obj->movement_type = MT_PHYSICS;
//--repair-- 			}
//--repair-- 		}
//--repair-- 	}
//--repair-- 	else
//--repair-- 		disable_repair_center=0;
//--repair-- 
//--repair-- }

//	--------------------------------------------------------------------------------------------
void disable_matcens(void)
{
	int	i;

	for (i=0; i<Num_robot_centers; i++) {
		Station[i].Enabled = 0;
		Station[i].Disable_time = 0;
	}
}

//	--------------------------------------------------------------------------------------------
//	Initialize all materialization centers.
//	Give them all the right number of lives.
void init_all_matcens(void)
{
	int	i;

	for (i=0; i<Num_fuelcenters; i++)
		if (Station[i].Type == SEGMENT_IS_ROBOTMAKER) {
			Station[i].Lives = 3;
			Station[i].Enabled = 0;
			Station[i].Disable_time = 0;
#ifndef NDEBUG
{
			//	Make sure this fuelcen is pointed at by a matcen.
			int	j;
			for (j=0; j<Num_robot_centers; j++) {
				if (RobotCenters[j].fuelcen_num == i)
					break;
			}
			Assert(j != Num_robot_centers);
}
#endif

		}

#ifndef NDEBUG
	//	Make sure all matcens point at a fuelcen
	for (i=0; i<Num_robot_centers; i++) {
		int	fuelcen_num = RobotCenters[i].fuelcen_num;

		Assert(fuelcen_num < Num_fuelcenters);
		Assert(Station[fuelcen_num].Type == SEGMENT_IS_ROBOTMAKER);
	}
#endif

}
