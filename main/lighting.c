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
 * $Source: Smoke:miner:source:main::RCS:lighting.c $
 * $Revision: 1.4 $
 * $Author: allender $
 * $Date: 1995/09/20 14:26:12 $
 * 
 * Lighting functions.
 * 
 * $Log: lighting.c $
 * Revision 1.4  1995/09/20  14:26:12  allender
 * more optimizations(?) ala MK
 *
 * Revision 1.2  1995/07/05  21:27:31  allender
 * new and improved lighting code by MK!
 *
 * Revision 2.1  1995/05/22  15:37:51  champaign
 * FROM MIKE: New lighting code, maybe don't leave in
 * 
 * Revision 2.0  1995/02/27  11:27:33  john
 * New version 2.0, which has no anonymous unions, builds with
 * Watcom 10.0, and doesn't require parsing BITMAPS.TBL.
 * 
 * Revision 1.43  1995/02/22  13:57:10  allender
 * remove anonymous union from object structure
 * 
 * Revision 1.42  1995/02/13  20:35:07  john
 * Lintized
 * 
 * Revision 1.41  1995/02/04  21:43:40  matt
 * Changed an assert() to an int3() and deal with the bad case
 * 
 * Revision 1.40  1995/01/15  20:48:27  mike
 * support light field for powerups.
 * 
 * Revision 1.39  1994/12/15  13:04:19  mike
 * Replace Players[Player_num].time_total references with GameTime.
 * 
 * Revision 1.38  1994/11/28  21:50:41  mike
 * optimizations.
 * 
 * Revision 1.37  1994/11/28  01:32:33  mike
 * lighting optimization.
 * 
 * Revision 1.36  1994/11/15  12:01:00  john
 * Changed a bunch of code that uses timer_get_milliseconds to 
 * timer_get_fixed_Seconds.  
 * 
 * Revision 1.35  1994/10/31  21:56:07  matt
 * Fixed bug & added error checking
 * 
 * Revision 1.34  1994/10/21  11:24:57  mike
 * Trap divide overflows in lighting.
 * 
 * Revision 1.33  1994/10/08  14:49:11  matt
 * If viewer changed, don't do smooth lighting hack
 * 
 * Revision 1.32  1994/09/25  23:41:07  matt
 * Changed the object load & save code to read/write the structure fields one
 * at a time (rather than the whole structure at once).  This mean that the
 * object structure can be changed without breaking the load/save functions.
 * As a result of this change, the local_object data can be and has been 
 * incorporated into the object array.  Also, timeleft is now a property 
 * of all objects, and the object structure has been otherwise cleaned up.
 * 
 * Revision 1.31  1994/09/25  15:45:15  matt
 * Added OBJ_LIGHT, a type of object that casts light
 * Added generalized lifeleft, and moved it to local_object
 * 
 * Revision 1.30  1994/09/11  15:48:27  mike
 * Use vm_vec_mag_quick in place of vm_vec_mag in point_dist computation.
 * 
 * Revision 1.29  1994/09/08  21:44:49  matt
 * Made lighting ramp 4x as fast; made only static (ambient) light ramp
 * up, but not headlight & dynamic light
 * 
 * Revision 1.28  1994/09/02  14:00:07  matt
 * Simplified explode_object() & mutliple-stage explosions
 * 
 * Revision 1.27  1994/08/29  19:06:44  mike
 * Make lighting proportional to square of distance, not linear.
 * 
 * Revision 1.26  1994/08/25  18:08:38  matt
 * Made muzzle flash cast 3x as much light
 * 
 * Revision 1.25  1994/08/23  16:38:31  mike
 * Key weapon light off bitmaps.tbl.
 * 
 * Revision 1.24  1994/08/13  12:20:44  john
 * Made the networking uise the Players array.
 * 
 * Revision 1.23  1994/08/12  22:42:18  john
 * Took away Player_stats; added Players array.
 * 
 * Revision 1.22  1994/07/06  10:19:22  matt
 * Changed include
 * 
 * Revision 1.21  1994/06/28  13:20:22  mike
 * Oops, fixed a dumb typo.
 * 
 * Revision 1.20  1994/06/28  12:53:25  mike
 * Change lighting function for flares, make brighter and asynchronously flicker.
 * 
 * Revision 1.19  1994/06/27  18:31:15  mike
 * Add flares.
 * 
 * Revision 1.18  1994/06/20  13:41:17  matt
 * Added time-based gradual lighting hack for objects
 * Took out strobing robots
 * 
 * Revision 1.17  1994/06/19  16:25:54  mike
 * Optimize lighting.
 * 
 * Revision 1.16  1994/06/17  18:08:08  mike
 * Make robots cast more and variable light.
 * 
 * Revision 1.15  1994/06/13  15:15:55  mike
 * Fix phantom light, every 64K milliseconds, muzzle flash would flash again.
 * 
 */


#pragma off (unreferenced)
static char rcsid[] = "$Id: lighting.c 1.4 1995/09/20 14:26:12 allender Exp $";
#pragma on (unreferenced)

#include <stdlib.h>
#include <string.h>	// for memset()

#include "inferno.h"
#include "segment.h"
#include "error.h"
#include "mono.h"
#include "render.h"
#include "game.h"
#include "vclip.h"
#include "lighting.h"
#include "3d.h"
#include "laser.h"
#include "timer.h"
#include "player.h"
#include "weapon.h"
#include "powerup.h"
#include "fvi.h"

//global saying how bright the light beam is
fix	Beam_brightness = (F1_0/2);
// -- optimized out, mk, 11/28/94 -- fix	Face_light_scale = (F1_0/2);
int	use_beam;		//flag for beam effect

int	Do_dynamic_light=1;
int	Use_fvi_lighting = 0;

fix	Dynamic_light[MAX_VERTICES];

#define	LIGHTING_CACHE_SIZE	4096	//	Must be power of 2!
// ----------------------------------------------------------------------------------------------
void apply_light(fix obj_intensity, int obj_seg, vms_vector *obj_pos, int n_render_vertices, short *render_vertices, int objnum)
{
	int	vv;

	if (obj_intensity) {
		fix	obji_64 = obj_intensity*64;

		// for pretty dim sources, only process vertices in object's own segment.
		if (obji_64 <= F1_0*8) {
			short *vp = Segments[obj_seg].verts;

			for (vv=0; vv<MAX_VERTICES_PER_SEGMENT; vv++) {
				int			vertnum;
				vms_vector	*vertpos;
				fix			dist;

				vertnum = vp[vv];
				vertpos = &Vertices[vertnum];
				dist = vm_vec_dist_quick(obj_pos, vertpos);
				dist = fixmul(dist/4, dist/4);
				if (dist < obji_64) {
					if (dist < MIN_LIGHT_DIST)
						dist = MIN_LIGHT_DIST;

					Dynamic_light[vertnum] += fixdiv(obj_intensity, dist);
				}
			}
		} else {
			for (vv=FrameCount&1; vv<n_render_vertices; vv+=2) {
				int			vertnum;
				vms_vector	*vertpos;
				fix			dist;
				int			apply_light;

				vertnum = render_vertices[vv];
				vertpos = &Vertices[vertnum];
				dist = vm_vec_dist_quick(obj_pos, vertpos);
				apply_light = 0;

				if (dist < obji_64) {

					if (dist < MIN_LIGHT_DIST)
						dist = MIN_LIGHT_DIST;

					Dynamic_light[vertnum] += fixdiv(obj_intensity, dist);
				}
			}
		}
	}
}

#define	FLASH_LEN_FIXED_SECONDS	(F1_0/3)
#define	FLASH_SCALE					(3*F1_0/FLASH_LEN_FIXED_SECONDS)

// ----------------------------------------------------------------------------------------------
void cast_muzzle_flash_light(int n_render_vertices, short *render_vertices)
{
	fix current_time;
	int	i;
	short	time_since_flash;

	current_time = timer_get_fixed_seconds();

	for (i=0; i<MUZZLE_QUEUE_MAX; i++) {
		if (Muzzle_data[i].create_time) {
			time_since_flash = current_time - Muzzle_data[i].create_time;
			if (time_since_flash < FLASH_LEN_FIXED_SECONDS)
				apply_light((FLASH_LEN_FIXED_SECONDS - time_since_flash) * FLASH_SCALE, Muzzle_data[i].segnum, &Muzzle_data[i].pos, n_render_vertices, render_vertices, -1);
			else
				Muzzle_data[i].create_time = 0;		// turn off this muzzle flash
		}
	}
}

//	Translation table to make flares flicker at different rates
fix	Obj_light_xlate[16] =
	{0x1234, 0x3321, 0x2468, 0x1735,
	 0x0123, 0x19af, 0x3f03, 0x232a,
	 0x2123, 0x39af, 0x0f03, 0x132a,
	 0x3123, 0x29af, 0x1f03, 0x032a};

//	Flag array of objects lit last frame.  Guaranteed to process this frame if lit last frame.
byte	Lighting_objects[MAX_OBJECTS];

// ---------------------------------------------------------
fix compute_light_intensity(int objnum)
{
	object		*obj = &Objects[objnum];
	int			objtype = obj->type;
          
	switch (objtype) {
		case OBJ_FIREBALL:
			if (obj->id != 0xff) {
				if (obj->lifeleft < F1_0*4)
					return fixmul(fixdiv(obj->lifeleft, Vclip[obj->id].play_time), Vclip[obj->id].light_value);
				else
					return Vclip[obj->id].light_value;
			} else
				 return 0;
			break;
		case OBJ_ROBOT:
//			return F1_0*Robot_info[obj->id].lightcast;
			return (F1_0 / 2);
			break;
		case OBJ_WEAPON: {
			fix tval = Weapon_info[obj->id].light;
			if (obj->id == FLARE_ID )
				return 2* (min(tval, obj->lifeleft) + ((GameTime ^ Obj_light_xlate[objnum&0x0f]) & 0x3fff));
			else
				return tval;
			}
			break;
		case OBJ_POWERUP:
			return Powerup_info[obj->id].light;
			break;
		case OBJ_DEBRIS:
			return F1_0/4;
			break;
		case OBJ_LIGHT:
			return obj->ctype.light_info.intensity;
			break;
		default:
			return 0;
			break;
	}
}

// ----------------------------------------------------------------------------------------------
void set_dynamic_light(void)
{
	int	i, objnum,vertnum;
	int	n_render_vertices;
	short	render_vertices[MAX_VERTICES];
	byte	render_vertex_flags[MAX_VERTICES];
	int	render_seg,segnum, v;
	byte	new_lighting_objects[MAX_OBJECTS];

	if (!Do_dynamic_light)
		return;

	memset(render_vertex_flags, 0, Highest_vertex_index+1);

	//	Create list of vertices that need to be looked at for setting of ambient light.
	n_render_vertices = 0;
	for (render_seg=0; render_seg<N_render_segs; render_seg++) {
		segnum = Render_list[render_seg];
		if (segnum != -1) {
			short	*vp = Segments[segnum].verts;
			for (v=0; v<MAX_VERTICES_PER_SEGMENT; v++) {
				int	vnum = vp[v];
				if (vnum<0 || vnum>Highest_vertex_index) {
					Int3();		//invalid vertex number
					continue;	//ignore it, and go on to next one
				}
				if (!render_vertex_flags[vnum]) {
					render_vertex_flags[vnum] = 1;
					render_vertices[n_render_vertices++] = vnum;
				}
				//--old way-- for (s=0; s<n_render_vertices; s++)
				//--old way-- 	if (render_vertices[s] == vnum)
				//--old way-- 		break;
				//--old way-- if (s == n_render_vertices)
				//--old way-- 	render_vertices[n_render_vertices++] = vnum;
			}
		}
	}

	for (vertnum=FrameCount&1; vertnum<n_render_vertices; vertnum+=2) {
		Assert(render_vertices[vertnum]>=0 && render_vertices[vertnum]<=Highest_vertex_index);
		Dynamic_light[render_vertices[vertnum]] = 0;
	}

	cast_muzzle_flash_light(n_render_vertices, render_vertices);

	for (objnum=0; objnum<=Highest_object_index; objnum++)
		new_lighting_objects[objnum] = 0;

	//	July 5, 1995: New faster dynamic lighting code.  About 5% faster on the PC (un-optimized).
	//	Only objects which are in rendered segments cast dynamic light.  We might want to extend this
	//	one or two segments if we notice light changing as objects go offscreen.  I couldn't see any
	//	serious visual degradation.  In fact, I could see no humorous degradation, either. --MK
	for (render_seg=0; render_seg<N_render_segs; render_seg++) {
		int	segnum = Render_list[render_seg];

		objnum = Segments[segnum].objects;

		while (objnum != -1) {
			object		*obj = &Objects[objnum];
			vms_vector	*objpos = &obj->pos;
			fix			obj_intensity;

			obj_intensity = compute_light_intensity(objnum);

			if (obj_intensity) {
				apply_light(obj_intensity, obj->segnum, objpos, n_render_vertices, render_vertices, obj-Objects);
				new_lighting_objects[objnum] = 1;
			}

			objnum = obj->next;
		}
	}

	//	Now, process all lights from last frame which haven't been processed this frame.
	for (objnum=0; objnum<=Highest_object_index; objnum++) {
		if (Lighting_objects[objnum]) {
			if (!new_lighting_objects[objnum]) {
				//	Lighted last frame, but not this frame.  Get intensity...
				object		*obj = &Objects[objnum];
				vms_vector	*objpos = &obj->pos;
				fix			obj_intensity;

				obj_intensity = compute_light_intensity(objnum);

				if (obj_intensity)
					apply_light(obj_intensity, obj->segnum, objpos, n_render_vertices, render_vertices, objnum);
				else
					Lighting_objects[objnum] = 0;
			}
		} else {
			//	Not lighted last frame, so we don't need to light it.  (Already lit if casting light this frame.)
			//	But copy value from new_lighting_objects to update Lighting_objects array.
			Lighting_objects[objnum] = new_lighting_objects[objnum];
		}
	}
}


// ---------------------------------------------------------

//Compute the lighting from the headlight for a given vertex on a face.
//Takes:
//  point - the 3d coords of the point
//  face_light - a scale factor derived from the surface normal of the face
//If no surface normal effect is wanted, pass F1_0 for face_light
fix compute_headlight_light(vms_vector *point,fix face_light)
{
	fix light;

	light = Beam_brightness;

	if (light) {				//if no beam, don't bother with the rest of this
		fix point_dist;

		if (face_light < 0)
			face_light = 0;

		point_dist = vm_vec_mag_quick(point);

		//note: beam scale not used if !use_beam

		if (point_dist >= MAX_DIST)

			light = 0;

		else {
			fix dist_scale,temp_lightval;

			dist_scale = (MAX_DIST - point_dist) >> MAX_DIST_LOG;

			temp_lightval = f1_0/4 + face_light/2;

			light = Beam_brightness;

			if (use_beam) {
				fix beam_scale;

				beam_scale = fixdiv(point->z,point_dist);
				beam_scale = fixmul(beam_scale,beam_scale);	//square it
				light = fixmul(light,beam_scale);
			}

			light = fixmul(light,fixmul(dist_scale,temp_lightval));

		}

	}

	return light;
}

//compute the average dynamic light in a segment.  Takes the segment number
fix compute_seg_dynamic_light(int segnum)
{
	fix sum;
	segment *seg;
	short *verts;

	seg = &Segments[segnum];

	verts = seg->verts;
	sum = 0;

	sum += Dynamic_light[*verts++];
	sum += Dynamic_light[*verts++];
	sum += Dynamic_light[*verts++];
	sum += Dynamic_light[*verts++];
	sum += Dynamic_light[*verts++];
	sum += Dynamic_light[*verts++];
	sum += Dynamic_light[*verts++];
	sum += Dynamic_light[*verts];

	return sum >> 3;

}

fix object_light[MAX_OBJECTS];
int object_id[MAX_OBJECTS];
object *old_viewer;

#define LIGHT_RATE i2f(4)		//how fast the light ramps up

//compute the lighting for an object.  Takes a pointer to the object,
//and possibly a rotated 3d point.  If the point isn't specified, the
//object's center point is rotated.
fix compute_object_light(object *obj,vms_vector *rotated_pnt)
{
	fix light;
	g3s_point objpnt;
	int objnum = obj-Objects;

	if (!rotated_pnt) {
		g3_rotate_point(&objpnt,&obj->pos);
		rotated_pnt = &objpnt.p3_vec;
	}

	//First, get static light for this segment

	light = Segments[obj->segnum].static_light;

	//return light;


	//Now, maybe return different value to smooth transitions

	if (Viewer==old_viewer && object_id[objnum] == obj->id) {
		fix delta_light,frame_delta;

		delta_light = light - object_light[objnum];

		frame_delta = fixmul(LIGHT_RATE,FrameTime);

		if (abs(delta_light) <= frame_delta)

			object_light[objnum] = light;		//we've hit the goal

		else

			if (delta_light < 0)
				light = object_light[objnum] -= frame_delta;
			else
				light = object_light[objnum] += frame_delta;

	}
	else {		//new object, initialize

		object_id[objnum] = obj->id;
		object_light[objnum] = light;
	}



	//Next, add in headlight on this object

	light += compute_headlight_light(rotated_pnt,f1_0);

	//Finally, add in dynamic light for this segment

	light += compute_seg_dynamic_light(obj->segnum);


	old_viewer = Viewer;

	return light;
}


