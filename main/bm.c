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
 * $Source: Buggin:miner:source:main::RCS:bm.c $
 * $Revision: 1.1 $
 * $Author: allender $
 * $Date: 1995/05/16 15:23:08 $
 *
 * Bitmap and palette loading functions.
 *
 * $Log: bm.c $
 * Revision 1.1  1995/05/16  15:23:08  allender
 * Initial revision
 *
 * Revision 2.3  1995/03/14  16:22:04  john
 * Added cdrom alternate directory stuff.
 * 
 * Revision 2.2  1995/03/07  16:51:48  john
 * Fixed robots not moving without edtiro bug.
 * 
 * Revision 2.1  1995/03/06  15:23:06  john
 * New screen techniques.
 * 
 * Revision 2.0  1995/02/27  11:27:05  john
 * New version 2.0, which has no anonymous unions, builds with
 * Watcom 10.0, and doesn't require parsing BITMAPS.TBL.
 * 
 * 
 */

#pragma off (unreferenced)
static char rcsid[] = "$Id: bm.c 1.1 1995/05/16 15:23:08 allender Exp $";
#pragma on (unreferenced)

#include <stdio.h>
#include <stdlib.h>
#include <Memory.h>

#include "dtypes.h"
#include "inferno.h"
#include "gr.h"
#include "3d.h"
#include "bm.h"
#include "mem.h"
#include "mono.h"
#include "error.h"
#include "object.h"
#include "vclip.h"
#include "effects.h"
#include "polyobj.h"
#include "wall.h"
#include "textures.h"
#include "game.h"
#include "multi.h"
#include "iff.h"
#include "cfile.h"
#include "hostage.h"
#include "powerup.h"
#include "sounds.h"
#include "piggy.h"
#include "aistruct.h"
#include "robot.h"
#include "weapon.h"
#include "gauges.h"
#include "player.h"
#include "fuelcen.h"
#include "endlevel.h"
#include "cntrlcen.h"
#include "byteswap.h"
#include "fileutil.h"

ubyte Sounds[MAX_SOUNDS];
ubyte AltSounds[MAX_SOUNDS];

int Num_total_object_types;

byte	ObjType[MAX_OBJTYPE];
byte	ObjId[MAX_OBJTYPE];
fix	ObjStrength[MAX_OBJTYPE];

//for each model, a model number for dying & dead variants, or -1 if none
int Dying_modelnums[MAX_POLYGON_MODELS];
int Dead_modelnums[MAX_POLYGON_MODELS];

//right now there's only one player ship, but we can have another by 
//adding an array and setting the pointer to the active ship.
player_ship only_player_ship,*Player_ship=&only_player_ship;

//----------------- Miscellaneous bitmap pointers ---------------
int					Num_cockpits = 0;
bitmap_index		cockpit_bitmap[N_COCKPIT_BITMAPS];

//---------------- Variables for wall textures ------------------
int 					Num_tmaps;
tmap_info 			TmapInfo[MAX_TEXTURES];

//---------------- Variables for object textures ----------------

int					First_multi_bitmap_num=-1;

bitmap_index		ObjBitmaps[MAX_OBJ_BITMAPS];
ushort				ObjBitmapPtrs[MAX_OBJ_BITMAPS];		// These point back into ObjBitmaps, since some are used twice.

// swap_vclip bytes swaps the elements of a vclip structure
void swap_vclip(vclip *vc)
{
	int i, j;
	
	vc->play_time = (fix)swapint((int)vc->play_time);
	vc->num_frames = swapint(vc->num_frames);
	vc->frame_time = (fix)swapint((int)vc->frame_time);
	vc->flags = swapint(vc->flags);
	vc->sound_num = swapshort(vc->sound_num);
	vc->light_value = (fix)swapint((int)vc->light_value);
	for (j = 0; j < VCLIP_MAX_FRAMES; j++)
		vc->frames[j].index = swapshort(vc->frames[j].index);
}

void read_tmap_info(CFILE *fp)
{
	int i;
	
	for (i = 0; i < MAX_TEXTURES; i++) {
		cfread(TmapInfo[i].filename, 13, 1, fp);
		TmapInfo[i].flags = read_byte(fp);
		TmapInfo[i].lighting = read_fix_swap(fp);
		TmapInfo[i].damage = read_fix_swap(fp);
		TmapInfo[i].eclip_num = read_int_swap(fp);
	}
}

void read_vclip_info(CFILE *fp)
{
	int i, j;
	
	for (i = 0; i < VCLIP_MAXNUM; i++) {
		Vclip[i].play_time = read_fix_swap(fp);
		Vclip[i].num_frames = read_int_swap(fp);
		Vclip[i].frame_time = read_fix_swap(fp);
		Vclip[i].flags = read_int_swap(fp);
		Vclip[i].sound_num = read_short_swap(fp);
		for (j = 0; j < VCLIP_MAX_FRAMES; j++)
			Vclip[i].frames[j].index = read_short_swap(fp);
		Vclip[i].light_value = read_fix_swap(fp);
	}
}

void read_effect_info(CFILE *fp)
{
	int i, j;

	for (i = 0; i < MAX_EFFECTS; i++) {
		Effects[i].vc.play_time = read_fix_swap(fp);
		Effects[i].vc.num_frames = read_int_swap(fp);
		Effects[i].vc.frame_time = read_fix_swap(fp);
		Effects[i].vc.flags = read_int_swap(fp);
		Effects[i].vc.sound_num = read_short_swap(fp);
		for (j = 0; j < VCLIP_MAX_FRAMES; j++)
			Effects[i].vc.frames[j].index = read_short_swap(fp);
		Effects[i].vc.light_value = read_fix_swap(fp);
		Effects[i].time_left = read_fix_swap(fp);
		Effects[i].frame_count = read_int_swap(fp);
		Effects[i].changing_wall_texture = read_short_swap(fp);
		Effects[i].changing_object_texture = read_short_swap(fp);
		Effects[i].flags = read_int_swap(fp);
		Effects[i].crit_clip = read_int_swap(fp);
		Effects[i].dest_bm_num = read_int_swap(fp);
		Effects[i].dest_vclip = read_int_swap(fp);
		Effects[i].dest_eclip = read_int_swap(fp);
		Effects[i].dest_size = read_fix_swap(fp);
		Effects[i].sound_num = read_int_swap(fp);
		Effects[i].segnum = read_int_swap(fp);
		Effects[i].sidenum = read_int_swap(fp);
	}
}

void read_wallanim_info(CFILE *fp)
{
	int i, j;
	
	for (i = 0; i < MAX_WALL_ANIMS; i++) {
		WallAnims[i].play_time = read_fix_swap(fp);;
		WallAnims[i].num_frames = read_short_swap(fp);;
		for (j = 0; j < MAX_CLIP_FRAMES; j++)
			WallAnims[i].frames[j] = read_short_swap(fp);
		WallAnims[i].open_sound = read_short_swap(fp);
		WallAnims[i].close_sound = read_short_swap(fp);
		WallAnims[i].flags = read_short_swap(fp);
		cfread(WallAnims[i].filename, 13, 1, fp);
		WallAnims[i].pad = read_byte(fp);
	}		
}

void read_robot_info(CFILE *fp)
{
	int i, j, k;
	
	for (i = 0; i < MAX_ROBOT_TYPES; i++) {
		Robot_info[i].model_num = read_int_swap(fp);
		Robot_info[i].n_guns = read_int_swap(fp);
		for (j = 0; j < MAX_GUNS; j++) {
			Robot_info[i].gun_points[j].x = read_fix_swap(fp);
			Robot_info[i].gun_points[j].y = read_fix_swap(fp);
			Robot_info[i].gun_points[j].z = read_fix_swap(fp);
		}
		for (j = 0; j < MAX_GUNS; j++)
			Robot_info[i].gun_submodels[j] = read_byte(fp);
		Robot_info[i].exp1_vclip_num = read_short_swap(fp);
		Robot_info[i].exp1_sound_num = read_short_swap(fp);
		Robot_info[i].exp2_vclip_num = read_short_swap(fp);
		Robot_info[i].exp2_sound_num = read_short_swap(fp);
		Robot_info[i].weapon_type = read_short_swap(fp);
		Robot_info[i].contains_id = read_byte(fp);
		Robot_info[i].contains_count = read_byte(fp);
		Robot_info[i].contains_prob = read_byte(fp);
		Robot_info[i].contains_type = read_byte(fp);
		Robot_info[i].score_value = read_int_swap(fp);
		Robot_info[i].lighting = read_fix_swap(fp);
		Robot_info[i].strength = read_fix_swap(fp);
		Robot_info[i].mass = read_fix_swap(fp);
		Robot_info[i].drag = read_fix_swap(fp);
		for (j = 0; j < NDL; j++)
			Robot_info[i].field_of_view[j] = read_fix_swap(fp);
		for (j = 0; j < NDL; j++)
			Robot_info[i].firing_wait[j] = read_fix_swap(fp);
		for (j = 0; j < NDL; j++)
			Robot_info[i].turn_time[j] = read_fix_swap(fp);
		for (j = 0; j < NDL; j++)
			Robot_info[i].fire_power[j] = read_fix_swap(fp);
		for (j = 0; j < NDL; j++)
			Robot_info[i].shield[j] = read_fix_swap(fp);
		for (j = 0; j < NDL; j++)
			Robot_info[i].max_speed[j] = read_fix_swap(fp);
		for (j = 0; j < NDL; j++)
			Robot_info[i].circle_distance[j] = read_fix_swap(fp);
		for (j = 0; j < NDL; j++)
			cfread(&(Robot_info[i].rapidfire_count[j]), sizeof(byte), 1, fp);
		for (j = 0; j < NDL; j++)
			cfread(&(Robot_info[i].evade_speed[j]), sizeof(byte), 1, fp);
		Robot_info[i].cloak_type = read_byte(fp);
		Robot_info[i].attack_type = read_byte(fp);
		Robot_info[i].boss_flag = read_byte(fp);
		Robot_info[i].see_sound = read_byte(fp);
		Robot_info[i].attack_sound = read_byte(fp);
		Robot_info[i].claw_sound = read_byte(fp);

		for (j = 0; j < MAX_GUNS + 1; j++) {
			for (k = 0; k < N_ANIM_STATES; k++) {
				Robot_info[i].anim_states[j][k].n_joints = read_short_swap(fp);
				Robot_info[i].anim_states[j][k].offset = read_short_swap(fp);
			}
		}

		Robot_info[i].always_0xabcd = read_int_swap(fp);
	}
}

void read_robot_joints_info(CFILE *fp)
{
	int i;

	for (i = 0; i < MAX_ROBOT_JOINTS; i++) {
		Robot_joints[i].jointnum = read_short_swap(fp);
		Robot_joints[i].angles.p = read_short_swap(fp);
		Robot_joints[i].angles.b = read_short_swap(fp);
		Robot_joints[i].angles.h = read_short_swap(fp);
	}
}

void read_weapon_info(CFILE *fp)
{
	int i, j;
	
	for (i = 0; i < MAX_WEAPON_TYPES; i++) {
		Weapon_info[i].render_type = read_byte(fp);
		Weapon_info[i].model_num = read_byte(fp);
		Weapon_info[i].model_num_inner = read_byte(fp);
		Weapon_info[i].persistent = read_byte(fp);
		Weapon_info[i].flash_vclip = read_byte(fp);
		Weapon_info[i].flash_sound = read_short_swap(fp);		
		Weapon_info[i].robot_hit_vclip = read_byte(fp);
		Weapon_info[i].robot_hit_sound = read_short_swap(fp);		
		Weapon_info[i].wall_hit_vclip = read_byte(fp);
		Weapon_info[i].wall_hit_sound = read_short_swap(fp);		
		Weapon_info[i].fire_count = read_byte(fp);
		Weapon_info[i].ammo_usage = read_byte(fp);
		Weapon_info[i].weapon_vclip = read_byte(fp);
		Weapon_info[i].destroyable = read_byte(fp);
		Weapon_info[i].matter = read_byte(fp);
		Weapon_info[i].bounce = read_byte(fp);
		Weapon_info[i].homing_flag = read_byte(fp);
		Weapon_info[i].dum1 = read_byte(fp);
		Weapon_info[i].dum2 = read_byte(fp);
		Weapon_info[i].dum3 = read_byte(fp);
		Weapon_info[i].energy_usage = read_fix_swap(fp);
		Weapon_info[i].fire_wait = read_fix_swap(fp);
		Weapon_info[i].bitmap.index = read_short_swap(fp);	// bitmap_index = short
		Weapon_info[i].blob_size = read_fix_swap(fp);
		Weapon_info[i].flash_size = read_fix_swap(fp);
		Weapon_info[i].impact_size = read_fix_swap(fp);
		for (j = 0; j < NDL; j++)
			Weapon_info[i].strength[j] = read_fix_swap(fp);
		for (j = 0; j < NDL; j++)
			Weapon_info[i].speed[j] = read_fix_swap(fp);
		Weapon_info[i].mass = read_fix_swap(fp);
		Weapon_info[i].drag = read_fix_swap(fp);
		Weapon_info[i].thrust = read_fix_swap(fp);

		Weapon_info[i].po_len_to_width_ratio = read_fix_swap(fp);
		Weapon_info[i].light = read_fix_swap(fp);
		Weapon_info[i].lifetime = read_fix_swap(fp);
		Weapon_info[i].damage_radius = read_fix_swap(fp);
		Weapon_info[i].picture.index = read_short_swap(fp);		// bitmap_index is a short
	}
}

void read_powerup_info(CFILE *fp)
{
	int i;
	
	for (i = 0; i < MAX_POWERUP_TYPES; i++) {
		Powerup_info[i].vclip_num = read_int_swap(fp);
		Powerup_info[i].hit_sound = read_int_swap(fp);
		Powerup_info[i].size = read_fix_swap(fp);
		Powerup_info[i].light = read_fix_swap(fp);
	}
}

void read_polygon_models(CFILE *fp)
{
	int i, j;

	Polygon_models = (polymodel *)mymalloc(sizeof(polymodel) * N_polygon_models);
	if (Polygon_models == NULL)
		Error("Cannot allocate space for Polygon_models!!");
	for (i = 0; i < N_polygon_models; i++) {
		Polygon_models[i].n_models = read_int_swap(fp);
		Polygon_models[i].model_data_size = read_int_swap(fp);
		Polygon_models[i].model_data = (ubyte *)read_int_swap(fp);
		for (j = 0; j < MAX_SUBMODELS; j++)
			Polygon_models[i].submodel_ptrs[j] = read_int_swap(fp);
		for (j = 0; j < MAX_SUBMODELS; j++) {
			Polygon_models[i].submodel_offsets[j].x = read_fix_swap(fp);
			Polygon_models[i].submodel_offsets[j].y = read_fix_swap(fp);
			Polygon_models[i].submodel_offsets[j].z = read_fix_swap(fp);
		}
		for (j = 0; j < MAX_SUBMODELS; j++) {
			Polygon_models[i].submodel_norms[j].x = read_fix_swap(fp);
			Polygon_models[i].submodel_norms[j].y = read_fix_swap(fp);
			Polygon_models[i].submodel_norms[j].z = read_fix_swap(fp);
		}
		for (j = 0; j < MAX_SUBMODELS; j++) {
			Polygon_models[i].submodel_pnts[j].x = read_fix_swap(fp);
			Polygon_models[i].submodel_pnts[j].y = read_fix_swap(fp);
			Polygon_models[i].submodel_pnts[j].z = read_fix_swap(fp);
		}
		for (j = 0; j < MAX_SUBMODELS; j++)
			Polygon_models[i].submodel_rads[j] = read_fix_swap(fp);
		for (j = 0; j < MAX_SUBMODELS; j++)
			Polygon_models[i].submodel_parents[j] = read_byte(fp);
		for (j = 0; j < MAX_SUBMODELS; j++) {
			Polygon_models[i].submodel_mins[j].x = read_fix_swap(fp);
			Polygon_models[i].submodel_mins[j].y = read_fix_swap(fp);
			Polygon_models[i].submodel_mins[j].z = read_fix_swap(fp);
		}
		for (j = 0; j < MAX_SUBMODELS; j++) {
			Polygon_models[i].submodel_maxs[j].x = read_fix_swap(fp);
			Polygon_models[i].submodel_maxs[j].y = read_fix_swap(fp);
			Polygon_models[i].submodel_maxs[j].z = read_fix_swap(fp);
		}
		Polygon_models[i].mins.x = read_fix_swap(fp);
		Polygon_models[i].mins.y = read_fix_swap(fp);
		Polygon_models[i].mins.z = read_fix_swap(fp);
		Polygon_models[i].maxs.x = read_fix_swap(fp);
		Polygon_models[i].maxs.y = read_fix_swap(fp);
		Polygon_models[i].maxs.z = read_fix_swap(fp);
		Polygon_models[i].rad = read_fix_swap(fp);		
		Polygon_models[i].n_textures = read_byte(fp);
		Polygon_models[i].first_texture = read_short_swap(fp);
		Polygon_models[i].simpler_model = read_byte(fp);
	}
}

void read_player_ship(CFILE *fp)
{
	int i;
	only_player_ship.model_num = read_int_swap(fp);
	only_player_ship.expl_vclip_num = read_int_swap(fp);
	only_player_ship.mass = read_fix_swap(fp);
	only_player_ship.drag = read_fix_swap(fp);
	only_player_ship.max_thrust = read_fix_swap(fp);
	only_player_ship.reverse_thrust = read_fix_swap(fp);
	only_player_ship.brakes = read_fix_swap(fp);
	only_player_ship.wiggle = read_fix_swap(fp);
	only_player_ship.max_rotthrust = read_fix_swap(fp);
	for (i = 0; i < N_PLAYER_GUNS; i++) {
		only_player_ship.gun_points[i].x = read_fix_swap(fp);
		only_player_ship.gun_points[i].y = read_fix_swap(fp);
		only_player_ship.gun_points[i].z = read_fix_swap(fp);
	}
}

//-----------------------------------------------------------------
// Initializes all bitmaps from BITMAPS.TBL file.
int bm_init()
{
	init_polygon_models();
	piggy_init();				// This calls bm_read_all
	piggy_read_sounds();
	return 0;
}

void bm_read_all(CFILE * fp)
{
	int i, j, k;

//  bitmap_index is a short

	NumTextures = read_int_swap(fp);
	for (i = 0; i < MAX_TEXTURES; i++)
		Textures[i].index = read_short_swap(fp);
		
	read_tmap_info(fp);
	
	cfread( Sounds, sizeof(ubyte), MAX_SOUNDS, fp );
	cfread( AltSounds, sizeof(ubyte), MAX_SOUNDS, fp );

	Num_vclips = read_int_swap(fp);
	read_vclip_info(fp);

	Num_effects = read_int_swap(fp);
	read_effect_info(fp);

	Num_wall_anims = read_int_swap(fp);
	read_wallanim_info(fp);

	N_robot_types = read_int_swap(fp);	
	read_robot_info(fp);

	N_robot_joints = read_int_swap(fp);
	read_robot_joints_info(fp);

	N_weapon_types = read_int_swap(fp);
	read_weapon_info(fp);

	N_powerup_types = read_int_swap(fp);
	read_powerup_info(fp);

	N_polygon_models = read_int_swap(fp);	
	read_polygon_models(fp);
	
	for (i = 0; i < N_polygon_models; i++) {
		Polygon_models[i].model_data = mymalloc(Polygon_models[i].model_data_size);
		Assert(Polygon_models[i].model_data != NULL);
		cfread(Polygon_models[i].model_data, sizeof(ubyte), Polygon_models[i].model_data_size, fp);
		swap_polygon_model_data(Polygon_models[i].model_data);
	}
	
	for (i = 0; i < MAX_GAUGE_BMS; i++)
		Gauges[i].index = read_short_swap(fp);

	for (i = 0; i < MAX_POLYGON_MODELS; i++)
		Dying_modelnums[i] = read_int_swap(fp);
	for (i = 0; i < MAX_POLYGON_MODELS; i++)
		Dead_modelnums[i] = read_int_swap(fp);

	for (i = 0; i < MAX_OBJ_BITMAPS; i++)
		ObjBitmaps[i].index = read_short_swap(fp);
	for (i = 0; i < MAX_OBJ_BITMAPS; i++)
		ObjBitmapPtrs[i] = read_short_swap(fp);

	read_player_ship(fp);

	Num_cockpits = read_int_swap(fp);
	for (i = 0; i < N_COCKPIT_BITMAPS; i++)
		cockpit_bitmap[i].index = read_short_swap(fp);

	cfread( Sounds, sizeof(ubyte), MAX_SOUNDS, fp );
	cfread( AltSounds, sizeof(ubyte), MAX_SOUNDS, fp );

	Num_total_object_types = read_int_swap(fp);
	cfread( ObjType, sizeof(byte), MAX_OBJTYPE, fp );
	cfread( ObjId, sizeof(byte), MAX_OBJTYPE, fp );
	for (i = 0; i < MAX_OBJTYPE; i++)
		ObjStrength[i] = read_fix_swap(fp);

	First_multi_bitmap_num = read_int_swap(fp);
	N_controlcen_guns = read_int_swap(fp);

	for (i = 0; i < MAX_CONTROLCEN_GUNS; i++) {
		controlcen_gun_points[i].x = read_fix_swap(fp);
		controlcen_gun_points[i].y = read_fix_swap(fp);
		controlcen_gun_points[i].z = read_fix_swap(fp);
	}
	for (i = 0; i < MAX_CONTROLCEN_GUNS; i++) {
		controlcen_gun_dirs[i].x = read_fix_swap(fp);
		controlcen_gun_dirs[i].y = read_fix_swap(fp);
		controlcen_gun_dirs[i].z = read_fix_swap(fp);
	}
	
	exit_modelnum = read_int_swap(fp);	
	destroyed_exit_modelnum = read_int_swap(fp);
}


