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
 * $Source: Smoke:miner:source:main::RCS:render.c $
 * $Revision: 1.9 $
 * $Author: allender $
 * $Date: 1995/11/20 17:17:48 $
 *
 * Sample setup for RCS header
 *
 * $Log: render.c $
 * Revision 1.9  1995/11/20  17:17:48  allender
 * *** empty log message ***
 *
 * Revision 1.8  1995/10/26  14:08:35  allender
 * added assigment for physics optimization
 *
 * Revision 1.7  1995/09/22  14:28:46  allender
 * changed render_zoom to make game match PC aspect
 *
 * Revision 1.6  1995/08/14  14:35:54  allender
 * change transparency to 0
 *
 * Revision 1.5  1995/08/12  11:32:02  allender
 * removed #ifdef NEWDEMO -- always in
 *
 * Revision 1.4  1995/07/05  16:48:31  allender
 * kitchen stuff
 *
 * Revision 1.3  1995/06/23  10:22:54  allender
 * fix outline mode
 *
 * Revision 1.2  1995/06/16  16:11:18  allender
 * changed sort func to accept const parameters
 *
 * Revision 1.1  1995/05/16  15:30:24  allender
 * Initial revision
 *
 * Revision 2.4  1995/03/20  12:15:53  john
 * Added code to not store the normals in the segment structure.
 * 
 * Revision 2.3  1995/03/13  16:11:05  john
 * Maybe fixed bug that lighting didn't work with vr helmets.
 * 
 * Revision 2.2  1995/03/09  15:33:49  john
 * Fixed bug with iglasses timeout too long, and objects
 * disappearing from left eye.
 * 
 * Revision 2.1  1995/03/06  15:23:59  john
 * New screen techniques.
 * 
 * Revision 2.0  1995/02/27  11:31:01  john
 * New version 2.0, which has no anonymous unions, builds with
 * Watcom 10.0, and doesn't require parsing BITMAPS.TBL.
 * 
 * Revision 1.252  1995/02/22  13:49:38  allender
 * remove anonymous unions from object structure
 * 
 * Revision 1.251  1995/02/11  15:07:26  matt
 * Took out code which was mostly intended as part of a larger renderer
 * change which never happened.  This new code was causing problems with
 * the level 4 control center.
 * 
 * Revision 1.250  1995/02/07  16:28:53  matt
 * Fixed problem with new code
 * 
 * Revision 1.249  1995/02/06  14:38:58  matt
 * Took out some code that didn't compile when editor in
 * 
 * Revision 1.248  1995/02/06  13:45:25  matt
 * Structural changes, plus small sorting improvements
 * 
 * Revision 1.247  1995/02/02  15:59:26  matt
 * Changed assert to int3.
 * 
 * Revision 1.246  1995/02/01  21:02:27  matt
 * Added partial fix for rendering bugs
 * Ripped out laser hack system
 * 
 * Revision 1.245  1995/01/20  15:14:30  matt
 * Added parens to fix precedence bug
 * 
 * Revision 1.244  1995/01/14  19:16:59  john
 * First version of new bitmap paging code.
 * 
 * Revision 1.243  1995/01/03  20:19:25  john
 * Pretty good working version of game save.
 * 
 * Revision 1.242  1994/12/29  13:51:05  john
 * Made the floating reticle draw in the spot
 * regardless of the eye offset.
 * 
 * Revision 1.241  1994/12/23  15:02:55  john
 * Tweaked floating reticle.
 * 
 * Revision 1.240  1994/12/23  14:27:45  john
 * Changed offset of floating reticle to line up with
 * lasers a bit better.
 * 
 * Revision 1.239  1994/12/23  14:22:50  john
 * Added floating reticle for VR helments.  
 * 
 * Revision 1.238  1994/12/13  14:07:50  matt
 * Fixed tmap_num2 bug in search mode
 * 
 * Revision 1.237  1994/12/11  00:45:53  matt
 * Fixed problem when object sort buffer got full
 * 
 * Revision 1.236  1994/12/09  18:46:06  matt
 * Added a little debugging
 * 
 * Revision 1.235  1994/12/09  14:59:16  matt
 * Added system to attach a fireball to another object for rendering purposes,
 * so the fireball always renders on top of (after) the object.
 * 
 * Revision 1.234  1994/12/08  15:46:54  matt
 * Fixed buffer overflow that caused seg depth screwup
 * 
 * Revision 1.233  1994/12/08  11:51:53  matt
 * Took out some unused stuff
 * 
 * Revision 1.232  1994/12/06  16:31:48  mike
 * fix detriangulation problems.
 * 
 * Revision 1.231  1994/12/05  15:32:51  matt
 * Changed an assert to an int3 & return
 * 
 * Revision 1.230  1994/12/04  17:28:04  matt
 * Got rid of unused no_render_flag array, and took out box clear when searching
 * 
 * Revision 1.229  1994/12/04  15:51:14  matt
 * Fixed linear tmap transition for objects
 * 
 * Revision 1.228  1994/12/03  20:16:50  matt
 * Turn off window clip for objects
 * 
 * Revision 1.227  1994/12/03  14:48:00  matt
 * Restored some default settings
 * 
 * Revision 1.226  1994/12/03  14:44:32  matt
 * Fixed another difficult bug in the window clip system
 * 
 * Revision 1.225  1994/12/02  13:19:56  matt
 * Fixed rect clears at terminus of rendering
 * Made a bunch of debug code compile out
 * 
 * Revision 1.224  1994/12/02  11:58:21  matt
 * Fixed window clip bug
 * 
 * Revision 1.223  1994/11/28  21:50:42  mike
 * optimizations.
 * 
 * Revision 1.222  1994/11/28  01:32:15  mike
 * turn off window clearing.
 * 
 * Revision 1.221  1994/11/27  23:11:52  matt
 * Made changes for new mprintf calling convention
 * 
 * Revision 1.220  1994/11/20  15:58:55  matt
 * Don't migrate the control center, since it doesn't move out of its segment
 * 
 * Revision 1.219  1994/11/19  23:54:36  mike
 * change window colors.
 * 
 * Revision 1.218  1994/11/19  15:20:25  mike
 * rip out unused code and data
 * 
 * Revision 1.217  1994/11/18  13:21:24  mike
 * Clear only view portals into rest of world based on value of Clear_window.
 * 
 * Revision 1.216  1994/11/15  17:02:10  matt
 * Re-added accidentally deleted variable
 * 
 * Revision 1.215  1994/11/15  16:51:50  matt
 * Made rear view only switch to rear cockpit if cockpit on in front view
 * 
 * Revision 1.214  1994/11/14  20:47:57  john
 * Attempted to strip out all the code in the game 
 * directory that uses any ui code.
 * 
 * Revision 1.213  1994/11/11  15:37:07  mike
 * write orange for background to show render bugs.
 * 
 * Revision 1.212  1994/11/09  22:57:18  matt
 * Keep tract of depth of segments rendered, for detail level optimization
 * 
 * Revision 1.211  1994/11/01  23:40:14  matt
 * Elegantly handler buffer getting full
 * 
 * Revision 1.210  1994/10/31  22:28:13  mike
 * Fix detriangulation bug.
 * 
 * Revision 1.209  1994/10/31  11:48:56  mike
 * Optimize detriangulation, speedup of about 4% in many cases, 0% in many.
 * 
 * Revision 1.208  1994/10/30  20:08:34  matt
 * For endlevel: added big explosion at tunnel exit; made lights in tunnel 
 * go out; made more explosions on walls.
 * 
 * Revision 1.207  1994/10/27  14:14:35  matt
 * Don't do light flash during endlevel sequence
 * 
 * Revision 1.206  1994/10/11  12:05:42  mike
 * Improve detriangulation.
 * 
 * Revision 1.205  1994/10/07  15:27:00  john
 * Commented out the code that moves your eye
 * forward.
 * 
 * Revision 1.204  1994/10/05  16:07:38  mike
 * Don't detriangulate sides if in player's segment.  Prevents player going behind a wall,
 * though there are cases in which it would be ok to detriangulate these.
 * 
 * Revision 1.203  1994/10/03  12:44:05  matt
 * Took out unreferenced code
 * 
 * Revision 1.202  1994/09/28  14:08:45  john
 * Added Zoom stuff back in, but ifdef'd it out.
 * 
 * Revision 1.201  1994/09/25  23:41:49  matt
 * Changed the object load & save code to read/write the structure fields one
 * at a time (rather than the whole structure at once).  This mean that the
 * object structure can be changed without breaking the load/save functions.
 * As a result of this change, the local_object data can be and has been 
 * incorporated into the object array.  Also, timeleft is now a property 
 * of all objects, and the object structure has been otherwise cleaned up.
 * 
 * Revision 1.200  1994/09/25  15:50:10  mike
 * Integrate my debug changes which shows how many textures were rendered
 * this frame.
 * 
 * Revision 1.199  1994/09/25  15:45:22  matt
 * Added OBJ_LIGHT, a type of object that casts light
 * Added generalized lifeleft, and moved it to local_object
 * 
 * Revision 1.198  1994/09/15  21:23:32  matt
 * Changed system to keep track of whether & what cockpit is up
 * 
 * Revision 1.197  1994/09/15  16:30:12  mike
 * Comment out call to object_render_targets, which did nothing.
 * 
 * Revision 1.196  1994/09/07  22:25:51  matt
 * Don't migrate through semi-transparent walls
 * 
 * Revision 1.195  1994/09/07  19:16:21  mike
 * Homing missile.
 * 
 * Revision 1.194  1994/08/31  20:54:17  matt
 * Don't do flash effect while whiting out
 * 
 * Revision 1.193  1994/08/23  17:20:12  john
 * Added rear-view cockpit.
 * 
 * Revision 1.192  1994/08/22  14:36:35  john
 * Made R key make a "reverse" view render.
 * 
 * Revision 1.191  1994/08/19  20:09:26  matt
 * Added end-of-level cut scene with external scene
 * 
 * Revision 1.190  1994/08/10  19:56:17  john
 * Changed font stuff; Took out old menu; messed up lots of
 * other stuff like game sequencing messages, etc.
 * 
 * Revision 1.189  1994/08/10  14:45:05  john
 * *** empty log message ***
 * 
 * Revision 1.188  1994/08/09  16:04:06  john
 * Added network players to editor.
 * 
 * Revision 1.187  1994/08/05  17:07:05  john
 * Made lasers be two objects, one drawing after the other
 * all the time.
 * 
 * Revision 1.186  1994/08/05  10:07:57  matt
 * Disable window check checking (i.e., always use window check)
 * 
 * Revision 1.185  1994/08/04  19:11:30  matt
 * Changed a bunch of vecmat calls to use multiple-function routines, and to
 * allow the use of C macros for some functions
 * 
 * Revision 1.184  1994/08/04  00:21:14  matt
 * Cleaned up fvi & physics error handling; put in code to make sure objects
 * are in correct segment; simplified segment finding for objects and points
 * 
 * Revision 1.183  1994/08/02  19:04:28  matt
 * Cleaned up vertex list functions
 * 
 * Revision 1.182  1994/07/29  15:13:33  matt
 * When window check turned off, cut render depth in half
 * 
 * Revision 1.181  1994/07/29  11:03:50  matt
 * Use highest_segment_index instead of num_segments so render works from
 * the editor
 * 
 * Revision 1.180  1994/07/29  10:04:34  mike
 * Update Cursegp when an object is selected.
 * 
 * Revision 1.179  1994/07/25  00:02:50  matt
 * Various changes to accomodate new 3d, which no longer takes point numbers
 * as parms, and now only takes pointers to points.
 * 
 * Revision 1.178  1994/07/24  14:37:49  matt
 * Added angles for player head
 * 
 * Revision 1.177  1994/07/20  19:08:07  matt
 * If in editor, don't move eye from center of viewer object
 * 
 * 
 */

#pragma off (unreferenced)
static char rcsid[] = "$Id: render.c 1.9 1995/11/20 17:17:48 allender Exp $";
#pragma on (unreferenced)

#include <stdlib.h>
#include <string.h>

#include "inferno.h"
#include "segment.h"
#include "error.h"
#include "bm.h"
#include "texmap.h"
#include "mono.h"
#include "render.h"
#include "game.h"
#include "object.h"
#include "laser.h"
#include "textures.h"
#include "screens.h"
#include "segpoint.h"
#include "wall.h"
#include "texmerge.h"
#include "physics.h"
#include "3d.h"
#include "gameseg.h"
#include "vclip.h"
#include "lighting.h"
#include	"fuelcen.h"
#include "newdemo.h"
#include "automap.h"
#include "endlevel.h"
#include "key.h"
#include "newmenu.h"
#include "mem.h"
#include "piggy.h"

#define	INITIAL_LOCAL_LIGHT	(F1_0/4)		// local light value in segment of occurence (of light emission)

#ifdef EDITOR
#include "editor\editor.h"
#endif

//used for checking if points have been rotated
int	Clear_window_color=-1;
int	Clear_window=2;			//	1 = Clear whole background window, 2 = clear view portals into rest of world, 0 = no clear

int RL_framecount=-1;
short Rotated_last[MAX_VERTICES];

// When any render function needs to know what's looking at it, it should 
// access Viewer members.
object * Viewer = NULL;

vms_vector Viewer_eye;	//valid during render

int	N_render_segs;

//fix Render_zoom = 0x9000;							//the player's zoom factor
fix Render_zoom = 0xB000;

#ifndef NDEBUG
ubyte object_rendered[MAX_OBJECTS];
#endif

#define DEFAULT_RENDER_DEPTH 16
int Render_depth=DEFAULT_RENDER_DEPTH;			//how many segments deep to render

int	Detriangulation_on = 1;					// 1 = allow rendering of triangulated side as a quad, 0 = don't allow

#ifdef EDITOR
int	Render_only_bottom=0;
int	Bottom_bitmap_num = 9;
#endif

fix	Face_reflectivity = (F1_0/2);

void render_mine(int start_seg_num,fix eye_offset);

#if 0		//this stuff could probably just be deleted

int inc_render_depth(void)
{
	return ++Render_depth;
}

int dec_render_depth(void)
{
	return Render_depth==1?Render_depth:--Render_depth;
}

int reset_render_depth(void)
{
	return Render_depth = DEFAULT_RENDER_DEPTH;
}

#endif

#ifdef EDITOR
int _search_mode = 0;			//true if looking for curseg,side,face
short _search_x,_search_y;	//pixel we're looking at
int found_seg,found_side,found_face,found_poly;
#else
#define _search_mode 0
#endif

#ifdef NDEBUG		//if no debug code, set these vars to constants

#define Outline_mode 0
#define Show_only_curside 0

#else

int Outline_mode=0,Show_only_curside=0;

int toggle_outline_mode(void)
{
	return Outline_mode = !Outline_mode;
}

int toggle_show_only_curside(void)
{
	return Show_only_curside = !Show_only_curside;
}

draw_outline(int nverts,g3s_point **pointlist)
{
	int i;

	gr_setcolor(TRANSPARENCY_COLOR);

	for (i=0;i<nverts-1;i++)
		g3_draw_line(pointlist[i],pointlist[i+1]);

	g3_draw_line(pointlist[i],pointlist[0]);

}
#endif

grs_canvas * reticle_canvas = NULL;

void free_reticle_canvas()
{
	if (reticle_canvas)	{
		myfree( reticle_canvas->cv_bitmap.bm_data );
		myfree( reticle_canvas );
		reticle_canvas	= NULL;
	}
}

extern void show_reticle(int force_big);

// Draw the reticle in 3D for head tracking
void draw_3d_reticle(fix eye_offset)
{
	g3s_point 	reticle_points[4];
	g3s_uvl		uvl[4];
	g3s_point	*pointlist[4];
	int 			i;
	vms_vector v1, v2;
	grs_canvas *saved_canvas;
	int saved_interp_method;

//	if (!Use_player_head_angles) return;
	
	for (i=0; i<4; i++ )	{
		pointlist[i] = &reticle_points[i];
		uvl[i].l = MAX_LIGHT;
	}
	uvl[0].u = 0; uvl[0].v = 0;
	uvl[1].u = F1_0; uvl[1].v = 0;
	uvl[2].u = F1_0; uvl[2].v = F1_0;
	uvl[3].u = 0; uvl[3].v = F1_0;

	vm_vec_scale_add( &v1, &Viewer->pos, &Viewer->orient.fvec, F1_0*4 );
	vm_vec_scale_add2(&v1,&Viewer->orient.rvec,eye_offset);

	vm_vec_scale_add( &v2, &v1, &Viewer->orient.rvec, -F1_0*1 );
	vm_vec_scale_add2( &v2, &Viewer->orient.uvec, F1_0*1 );
	g3_rotate_point(&reticle_points[0],&v2);

	vm_vec_scale_add( &v2, &v1, &Viewer->orient.rvec, +F1_0*1 );
	vm_vec_scale_add2( &v2, &Viewer->orient.uvec, F1_0*1 );
	g3_rotate_point(&reticle_points[1],&v2);

	vm_vec_scale_add( &v2, &v1, &Viewer->orient.rvec, +F1_0*1 );
	vm_vec_scale_add2( &v2, &Viewer->orient.uvec, -F1_0*1 );
	g3_rotate_point(&reticle_points[2],&v2);

	vm_vec_scale_add( &v2, &v1, &Viewer->orient.rvec, -F1_0*1 );
	vm_vec_scale_add2( &v2, &Viewer->orient.uvec, -F1_0*1 );
	g3_rotate_point(&reticle_points[3],&v2);

	if ( reticle_canvas == NULL )	{
		reticle_canvas = gr_create_canvas(64,64);
		if ( !reticle_canvas )
			Error( "Couldn't malloc reticle_canvas" );
		atexit( free_reticle_canvas );
		reticle_canvas->cv_bitmap.bm_selector = 0;
		reticle_canvas->cv_bitmap.bm_flags = BM_FLAG_TRANSPARENT;
	}

	saved_canvas = grd_curcanv;
	gr_set_current_canvas(reticle_canvas);
	gr_clear_canvas( TRANSPARENCY_COLOR );		// Clear to Xparent
	show_reticle(1);
	gr_set_current_canvas(saved_canvas);
	
	saved_interp_method=Interpolation_method;
	Interpolation_method	= 3;		// The best, albiet slowest.
	g3_draw_tmap(4,pointlist,uvl,&reticle_canvas->cv_bitmap);
	Interpolation_method	= saved_interp_method;
}


fix flash_scale;

#define FLASH_CYCLE_RATE f1_0

fix flash_rate = FLASH_CYCLE_RATE;

//cycle the flashing light for when mine destroyed
flash_frame()
{
	fix tmp;
	static fixang flash_ang=0;

	if (!Fuelcen_control_center_destroyed)
		return;

	if (Endlevel_sequence)
		return;

	if (PaletteBlueAdd > 10 )		//whiting out
		return;

//	flash_ang += fixmul(FLASH_CYCLE_RATE,FrameTime);
	flash_ang += fixmul(flash_rate,FrameTime);

	fix_fastsincos(flash_ang,&flash_scale,&tmp);

	flash_scale = (flash_scale + f1_0)/2;

}

// -----------------------------------------------------------------------------------
//	Render a face.
//	It would be nice to not have to pass in segnum and sidenum, but they are used for our
//	hideously hacked in headlight system.
//	vp is a pointer to vertex ids.
//	tmap1, tmap2 are texture map ids.  tmap2 is the pasty one.
void render_face(int segnum, int sidenum, int nv, short *vp, int tmap1, int tmap2, uvl *uvlp, vms_vector *norm)
{
	fix			face_light;
	grs_bitmap	*bm;
	fix			reflect;
	uvl			uvl_copy[8];
	int			i;
	g3s_point	*pointlist[8];

	Assert(nv <= 8);

	for (i=0; i<nv; i++) {
		uvl_copy[i] = uvlp[i];
		pointlist[i] = &Segment_points[vp[i]];
	}

	face_light = -vm_vec_dot(&Viewer->orient.fvec,norm);

	if (tmap1 >= NumTextures) {
		mprintf((0,"Invalid tmap number %d, NumTextures=%d, changing to 0\n",tmap1,NumTextures));
		Int3();
		Segments[segnum].sides[sidenum].tmap_num = 0;
	}

	// New code for overlapping textures...
	if (tmap2 != 0)
		bm = texmerge_get_cached_bitmap( tmap1, tmap2 );
	else	{
		bm = &GameBitmaps[Textures[tmap1].index];
		PIGGY_PAGE_IN(Textures[tmap1]);
	}

	Assert( !(bm->bm_flags & BM_FLAG_PAGED_OUT) );

	//reflect = fl2f((1.0-TmapInfo[p->tmap_num].reflect)/2.0 + 0.5);
	//reflect = fl2f((1.0-TmapInfo[p->tmap_num].reflect));

	reflect = Face_reflectivity;		// f1_0;	//until we figure this stuff out...

	//set light values for each vertex & build pointlist
	{
		int i;

		face_light = fixmul(face_light,reflect);

		for (i=0;i<nv;i++) {

			//the uvl struct has static light already in it

			//scale static light for destruction effect
			if (Fuelcen_control_center_destroyed)	//make lights flash
				uvl_copy[i].l = fixmul(flash_scale,uvl_copy[i].l);

			//add in dynamic light (from explosions, etc.)
			uvl_copy[i].l += Dynamic_light[vp[i]];

			//add in light from player's headlight
			uvl_copy[i].l += compute_headlight_light(&Segment_points[vp[i]].p3_vec,face_light);

			//saturate at max value
			if (uvl_copy[i].l > MAX_LIGHT)
				uvl_copy[i].l = MAX_LIGHT;

		}
	}


#ifdef EDITOR
	if ((Render_only_bottom) && (sidenum == WBOTTOM))
		g3_draw_tmap(nv,pointlist,(g3s_uvl *) uvl_copy,&GameBitmaps[Textures[Bottom_bitmap_num].index]);
	else
#endif
		g3_draw_tmap(nv,pointlist,(g3s_uvl *) uvl_copy,bm);

	#ifndef NDEBUG
	if (Outline_mode) draw_outline(nv, pointlist);
	#endif
}

#ifdef EDITOR
// -----------------------------------------------------------------------------------
//	Only called if editor active.
//	Used to determine which face was clicked on.
void check_face(int segnum, int sidenum, int facenum, int nv, short *vp, int tmap1, int tmap2, uvl *uvlp)
{
	int	i;

	if (_search_mode) {
		int save_lighting;
		grs_bitmap *bm;
		uvl uvl_copy[8];
		g3s_point *pointlist[4];

		if (tmap2 > 0 )
			bm = texmerge_get_cached_bitmap( tmap1, tmap2 );
		else
			bm = &GameBitmaps[Textures[tmap1].index];

		for (i=0; i<nv; i++) {
			uvl_copy[i] = uvlp[i];
			pointlist[i] = &Segment_points[vp[i]];
		}

		gr_setcolor(0);
		gr_pixel(_search_x,_search_y);	//set our search pixel to color zero
		gr_setcolor(1);					//and render in color one
 save_lighting = Lighting_on;
 Lighting_on = 2;
		//g3_draw_poly(nv,vp);
		g3_draw_tmap(nv,pointlist, uvl_copy, bm);
 Lighting_on = save_lighting;

		if (gr_ugpixel(&grd_curcanv->cv_bitmap,_search_x,_search_y) == 1) {
			found_seg = segnum;
			found_side = sidenum;
			found_face = facenum;
		}
		
	}
}
#endif

fix	Tulate_min_dot = (F1_0/4);
//--unused-- fix	Tulate_min_ratio = (2*F1_0);
fix	Min_n0_n1_dot	= (F1_0*15/16);

// -----------------------------------------------------------------------------------
//	Render a side.
//	Check for normal facing.  If so, render faces on side dictated by sidep->type.
void render_side(segment *segp, int sidenum)
{
	short			vertnum_list[4];
	side			*sidep = &segp->sides[sidenum];
	vms_vector	tvec;
	fix			v_dot_n0, v_dot_n1;
	uvl			temp_uvls[3];
	fix			min_dot, max_dot;
	vms_vector  normals[2];

	if (!(WALL_IS_DOORWAY(segp,sidenum) & WID_RENDER_FLAG))		//if (WALL_IS_DOORWAY(segp, sidenum) == WID_NO_WALL)
		return;

	#ifdef COMPACT_SEGS	
		get_side_normals(segp, sidenum, &normals[0], &normals[1] );
	#else
		normals[0] = segp->sides[sidenum].normals[0];
		normals[1] = segp->sides[sidenum].normals[1];
	#endif

	//	Regardless of whether this side is comprised of a single quad, or two triangles, we need to know one normal, so
	//	deal with it, get the dot product.
	if (sidep->type == SIDE_IS_TRI_13)
		vm_vec_normalized_dir(&tvec, &Viewer_eye, &Vertices[segp->verts[Side_to_verts[sidenum][1]]]);
	else
		vm_vec_normalized_dir(&tvec, &Viewer_eye, &Vertices[segp->verts[Side_to_verts[sidenum][0]]]);

	get_side_verts(vertnum_list,segp-Segments,sidenum);

	v_dot_n0 = vm_vec_dot(&tvec, &normals[0]);

	if (sidep->type == SIDE_IS_QUAD) {
		if (v_dot_n0 >= 0) {
			render_face(segp-Segments, sidenum, 4, vertnum_list, sidep->tmap_num, sidep->tmap_num2, sidep->uvls, &normals[0]);
			#ifdef EDITOR
			check_face(segp-Segments, sidenum, 0, 4, vertnum_list, sidep->tmap_num, sidep->tmap_num2, sidep->uvls);
			#endif
		}
	} else {
		//	Although this side has been triangulated, because it is not planar, see if it is acceptable
		//	to render it as a single quadrilateral.  This is a function of how far away the viewer is, how non-planar
		//	the face is, how normal to the surfaces the view is.
		//	Now, if both dot products are close to 1.0, then render two triangles as a single quad.
		v_dot_n1 = vm_vec_dot(&tvec, &normals[1]);

		if (v_dot_n0 < v_dot_n1) {
			min_dot = v_dot_n0;
			max_dot = v_dot_n1;
		} else {
			min_dot = v_dot_n1;
			max_dot = v_dot_n0;
		}

		//	Determine whether to detriangulate side: (speed hack, assumes Tulate_min_ratio == F1_0*2, should fixmul(min_dot, Tulate_min_ratio))
		if (Detriangulation_on && ((min_dot+F1_0/256 > max_dot) || ((Viewer->segnum != segp-Segments) &&  (min_dot > Tulate_min_dot) && (max_dot < min_dot*2)))) {
			fix	n0_dot_n1;

			//	The other detriangulation code doesn't deal well with badly non-planar sides.
			n0_dot_n1 = vm_vec_dot(&normals[0], &normals[1]);
			if (n0_dot_n1 < Min_n0_n1_dot)
				goto im_so_ashamed;

			render_face(segp-Segments, sidenum, 4, vertnum_list, sidep->tmap_num, sidep->tmap_num2, sidep->uvls, &normals[0]);
			#ifdef EDITOR
			check_face(segp-Segments, sidenum, 0, 4, vertnum_list, sidep->tmap_num, sidep->tmap_num2, sidep->uvls);
			#endif
		} else {
im_so_ashamed: ;
			if (sidep->type == SIDE_IS_TRI_02) {
				if (v_dot_n0 >= 0) {
					render_face(segp-Segments, sidenum, 3, vertnum_list, sidep->tmap_num, sidep->tmap_num2, sidep->uvls, &normals[0]);
					#ifdef EDITOR
					check_face(segp-Segments, sidenum, 0, 3, vertnum_list, sidep->tmap_num, sidep->tmap_num2, sidep->uvls);
					#endif
				}

				if (v_dot_n1 >= 0) {
					temp_uvls[0] = sidep->uvls[0];		temp_uvls[1] = sidep->uvls[2];		temp_uvls[2] = sidep->uvls[3];
					vertnum_list[1] = vertnum_list[2];	vertnum_list[2] = vertnum_list[3];	// want to render from vertices 0, 2, 3 on side
					render_face(segp-Segments, sidenum, 3, &vertnum_list[0], sidep->tmap_num, sidep->tmap_num2, temp_uvls, &normals[1]);
					#ifdef EDITOR
					check_face(segp-Segments, sidenum, 1, 3, vertnum_list, sidep->tmap_num, sidep->tmap_num2, sidep->uvls);
					#endif
				}
			} else if (sidep->type ==  SIDE_IS_TRI_13) {
				if (v_dot_n1 >= 0) {
					render_face(segp-Segments, sidenum, 3, &vertnum_list[1], sidep->tmap_num, sidep->tmap_num2, &sidep->uvls[1], &normals[1]);	// rendering 1,2,3, so just skip 0
					#ifdef EDITOR
					check_face(segp-Segments, sidenum, 1, 3, &vertnum_list[1], sidep->tmap_num, sidep->tmap_num2, sidep->uvls);
					#endif
				}

				if (v_dot_n0 >= 0) {
					temp_uvls[0] = sidep->uvls[0];		temp_uvls[1] = sidep->uvls[1];		temp_uvls[2] = sidep->uvls[3];
					vertnum_list[2] = vertnum_list[3];		// want to render from vertices 0,1,3
					render_face(segp-Segments, sidenum, 3, vertnum_list, sidep->tmap_num, sidep->tmap_num2, temp_uvls, &normals[0]);
					#ifdef EDITOR
					check_face(segp-Segments, sidenum, 0, 3, vertnum_list, sidep->tmap_num, sidep->tmap_num2, sidep->uvls);
					#endif
				}

			} else
				Error("Illegal side type in render_side, type = %i, segment # = %i, side # = %i\n", sidep->type, segp-Segments, sidenum);
		}
	}

}

#ifdef EDITOR
render_object_search(object *obj)
{
	int changed=0;

	//note that we draw each pixel object twice, since we cannot control
	//what color the object draws in, so we try color 0, then color 1,
	//in case the object itself is rendering color 0

	gr_setcolor(0);
	gr_pixel(_search_x,_search_y);	//set our search pixel to color zero
	render_object(obj);
	if (gr_ugpixel(&grd_curcanv->cv_bitmap,_search_x,_search_y) != 0)
		changed=1;

	gr_setcolor(1);
	gr_pixel(_search_x,_search_y);	//set our search pixel to color zero
	render_object(obj);
	if (gr_ugpixel(&grd_curcanv->cv_bitmap,_search_x,_search_y) != 1)
		changed=1;

	if (changed) {
		if (obj->segnum != -1)
			Cursegp = &Segments[obj->segnum];
		found_seg = -(obj-Objects+1);
	}
}
#endif

extern int object_rendered_last[MAX_OBJECTS];

do_render_object(int objnum)
{
	#ifdef EDITOR
	int save_3d_outline;
	#endif
	object *obj = &Objects[objnum];
	int count = 0;
	int n;

	Assert(objnum < MAX_OBJECTS);

    object_rendered_last[objnum] = FrameCount;

	#ifndef NDEBUG
	if (object_rendered[objnum]) {		//already rendered this...
		Int3();		//get Matt!!!
		return;
	}
	object_rendered[objnum] = 1;
	#endif

	//	Added by MK on 09/07/94 (at about 5:28 pm, CDT, on a beautiful, sunny late summer day!) so
	//	that the guided missile system will know what objects to look at.
	if ((Objects[objnum].type == OBJ_ROBOT) || (Objects[objnum].type == OBJ_PLAYER)) {
		//Assert(Num_rendered_objects < MAX_RENDERED_OBJECTS);
		//	This peculiar piece of code makes us keep track of the most recently rendered objects, which
		//	are probably the higher priority objects, without overflowing the buffer
		if (Num_rendered_objects >= MAX_RENDERED_OBJECTS) {
			Int3();
			Num_rendered_objects /= 2;
		}
		Ordered_rendered_object_list[Num_rendered_objects++] = objnum;
	}

	if ((count++ > MAX_OBJECTS) || (obj->next == objnum)) {
		Int3();					// infinite loop detected
		obj->next = -1;		// won't this clean things up?
		return;					// get out of this infinite loop!
	}

		//g3_draw_object(obj->class_id,&obj->pos,&obj->orient,obj->size);

	//check for editor object

	#ifdef EDITOR
	if (Function_mode==FMODE_EDITOR && objnum==Cur_object_index) {
		save_3d_outline = g3d_interp_outline;
		g3d_interp_outline=1;
	}
	#endif

	#ifdef EDITOR
	if (_search_mode)
		render_object_search(obj);
	else
	#endif
		//NOTE LINK TO ABOVE
		render_object(obj);

	for (n=obj->attached_obj;n!=-1;n=Objects[n].ctype.expl_info.next_attach) {

		Assert(Objects[n].type == OBJ_FIREBALL);
		Assert(Objects[n].control_type == CT_EXPLOSION);
		Assert(Objects[n].flags & OF_ATTACHED);

		render_object(&Objects[n]);
	}


	#ifdef EDITOR
	if (Function_mode==FMODE_EDITOR && objnum==Cur_object_index)
		g3d_interp_outline = save_3d_outline;
	#endif


	//DEBUG mprintf( (0, "%d ", objnum ));

}

#ifndef NDEBUG
int	draw_boxes=0;
int window_check=1,draw_edges=0,new_seg_sorting=1,pre_draw_segs=0;
int no_migrate_segs=1,migrate_objects=1,behind_check=1;
int check_window_check=0;
#else
#define draw_boxes			0
#define window_check			1
#define draw_edges			0
#define new_seg_sorting		1
#define pre_draw_segs		0
#define no_migrate_segs		1
#define migrate_objects		1
#define behind_check			1
#define check_window_check	0
#endif

//increment counter for checking if points rotated
//This must be called at the start of the frame if rotate_list() will be used
void render_start_frame()
{
	RL_framecount++;

	if (RL_framecount==0) {		//wrap!

		memset(Rotated_last,0,sizeof(Rotated_last));		//clear all to zero
		RL_framecount=1;											//and set this frame to 1
	}
}

//Given a lit of point numbers, rotate any that haven't been rotated this frame
g3s_codes rotate_list(int nv,short *pointnumlist)
{
	int i,pnum;
	g3s_point *pnt;
	g3s_codes cc;

	cc.and = 0xff;  cc.or = 0;

	for (i=0;i<nv;i++) {

		pnum = pointnumlist[i];

		pnt = &Segment_points[pnum];

		if (Rotated_last[pnum] != RL_framecount) {

			g3_rotate_point(pnt,&Vertices[pnum]);

			Rotated_last[pnum] = RL_framecount;
		}

		cc.and &= pnt->p3_codes;
		cc.or  |= pnt->p3_codes;
	}

	return cc;

}

//Given a lit of point numbers, project any that haven't been projected
void project_list(int nv,short *pointnumlist)
{
	int i,pnum;

	for (i=0;i<nv;i++) {

		pnum = pointnumlist[i];

		if (!(Segment_points[pnum].p3_flags & PF_PROJECTED))

			g3_project_point(&Segment_points[pnum]);

	}
}


// -----------------------------------------------------------------------------------
void render_segment(int segnum)
{
	segment		*seg = &Segments[segnum];
	g3s_codes 	cc;
	int			sn;

	Assert(segnum!=-1 && segnum<=Highest_segment_index);

	cc=rotate_list(8,seg->verts);

	if (! cc.and) {		//all off screen?

//mprintf( (0, "!"));
		//DEBUG mprintf( (0, "[Segment %d: ", segnum ));

		// set_segment_local_light_value(segnum,INITIAL_LOCAL_LIGHT);

		Automap_visited[segnum]=1;

		for (sn=0; sn<MAX_SIDES_PER_SEGMENT; sn++)
			render_side(seg, sn);
	}

	//draw any objects that happen to be in this segment

	//sort objects!
	//object_sort_segment_objects( seg );
		
	#ifndef NDEBUG
	if (!migrate_objects) {
		int objnum;
		for (objnum=seg->objects;objnum!=-1;objnum=Objects[objnum].next)
			do_render_object(objnum);
	}
	#endif

	//DEBUG mprintf( (0, "]\n", segnum ));

}

// ----- This used to be called when Show_only_curside was set.
// ----- It is wholly and superiorly replaced by render_side.
// -- //render one side of one segment
// -- void render_seg_side(segment *seg,int _side)
// -- {
// -- 	g3s_codes cc;
// -- 	short vertnum_list[4];
// -- 
// -- 	cc=g3_rotate_list(8,&seg->verts);
// -- 
// -- 	if (! cc.and) {		//all off screen?
// -- 		int fn,pn,i;
// -- 		side *s;
// -- 		face *f;
// -- 		poly *p;
// -- 
// -- 		s=&seg->sides[_side];
// -- 
// -- 		for (f=s->faces,fn=s->num_faces;fn;fn--,f++)
// -- 			for (p=f->polys,pn=f->num_polys;pn;pn--,p++) {
// -- 				grs_bitmap *tmap;
// -- 	
// -- 				for (i=0;i<p->num_vertices;i++) vertnum_list[i] = seg->verts[p->verts[i]];
// -- 	
// -- 				if (p->tmap_num >= NumTextures) {
// -- 					Warning("Invalid tmap number %d, NumTextures=%d\n...Changing in poly structure to tmap 0",p->tmap_num,NumTextures);
// -- 					p->tmap_num = 0;		//change it permanantly
// -- 				}
// -- 	
// -- 				tmap = Textures[p->tmap_num];
// -- 	
// -- 				g3_check_and_draw_tmap(p->num_vertices,vertnum_list,(g3s_uvl *) &p->uvls,tmap,&f->normal);
// -- 	
// -- 				if (Outline_mode) draw_outline(p->num_vertices,vertnum_list);
// -- 			}
// -- 		}
// -- 
// -- }

#define CROSS_WIDTH  i2f(8)
#define CROSS_HEIGHT i2f(8)

#ifndef NDEBUG

//draw outline for curside
outline_seg_side(segment *seg,int _side,int edge,int vert)
{
	g3s_codes cc;

	cc=rotate_list(8,seg->verts);

	if (! cc.and) {		//all off screen?
		side *s;
		g3s_point *pnt;

		s=&seg->sides[_side];

		//render curedge of curside of curseg in green

		gr_setcolor(BM_XRGB(0,63,0));
		g3_draw_line(&Segment_points[seg->verts[Side_to_verts[_side][edge]]],&Segment_points[seg->verts[Side_to_verts[_side][(edge+1)%4]]]);

		//draw a little cross at the current vert

		pnt = &Segment_points[seg->verts[Side_to_verts[_side][vert]]];

		g3_project_point(pnt);		//make sure projected

//		gr_setcolor(BM_XRGB(0,0,63));
//		gr_line(pnt->p3_sx-CROSS_WIDTH,pnt->p3_sy,pnt->p3_sx+CROSS_WIDTH,pnt->p3_sy);
//		gr_line(pnt->p3_sx,pnt->p3_sy-CROSS_HEIGHT,pnt->p3_sx,pnt->p3_sy+CROSS_HEIGHT);

		gr_line(pnt->p3_sx-CROSS_WIDTH,pnt->p3_sy,pnt->p3_sx,pnt->p3_sy-CROSS_HEIGHT);
		gr_line(pnt->p3_sx,pnt->p3_sy-CROSS_HEIGHT,pnt->p3_sx+CROSS_WIDTH,pnt->p3_sy);
		gr_line(pnt->p3_sx+CROSS_WIDTH,pnt->p3_sy,pnt->p3_sx,pnt->p3_sy+CROSS_HEIGHT);
		gr_line(pnt->p3_sx,pnt->p3_sy+CROSS_HEIGHT,pnt->p3_sx-CROSS_WIDTH,pnt->p3_sy);
	}
}

#endif

#if 0		//this stuff could probably just be deleted

#define DEFAULT_PERSPECTIVE_DEPTH 6

int Perspective_depth=DEFAULT_PERSPECTIVE_DEPTH;	//how many levels deep to render in perspective

int inc_perspective_depth(void)
{
	return ++Perspective_depth;

}

int dec_perspective_depth(void)
{
	return Perspective_depth==1?Perspective_depth:--Perspective_depth;

}

int reset_perspective_depth(void)
{
	return Perspective_depth = DEFAULT_PERSPECTIVE_DEPTH;

}
#endif

typedef struct window {
	short left,top,right,bot;
} window;

ubyte code_window_point(fix x,fix y,window *w)
{
	ubyte code=0;

	if (x <= w->left)  code |= 1;
	if (x >= w->right) code |= 2;

	if (y <= w->top) code |= 4;
	if (y >= w->bot) code |= 8;

	return code;
}

#ifndef NDEBUG
draw_window_box(int color,short left,short top,short right,short bot)
{
	short l,t,r,b;

	gr_setcolor(color);

	l=left; t=top; r=right; b=bot;

	if ( r<0 || b<0 || l>=grd_curcanv->cv_bitmap.bm_w || t>=grd_curcanv->cv_bitmap.bm_h && b>=grd_curcanv->cv_bitmap.bm_h)
		return;

	if (l<0) l=0;
	if (t<0) t=0;
	if (r>=grd_curcanv->cv_bitmap.bm_w) r=grd_curcanv->cv_bitmap.bm_w-1;
	if (b>=grd_curcanv->cv_bitmap.bm_h) b=grd_curcanv->cv_bitmap.bm_h-1;

	gr_line(i2f(l),i2f(t),i2f(r),i2f(t));
	gr_line(i2f(r),i2f(t),i2f(r),i2f(b));
	gr_line(i2f(r),i2f(b),i2f(l),i2f(b));
	gr_line(i2f(l),i2f(b),i2f(l),i2f(t));

}
#endif

int matt_find_connect_side(int seg0,int seg1);

#ifndef NDEBUG
char visited2[MAX_SEGMENTS];
#endif

char visited[MAX_SEGMENTS];
short Render_list[MAX_RENDER_SEGS];
short Seg_depth[MAX_RENDER_SEGS];		//depth for each seg in Render_list
ubyte processed[MAX_RENDER_SEGS];		//whether each entry has been processed
int	lcnt_save,scnt_save;
//@@short *persp_ptr;
short render_pos[MAX_SEGMENTS];	//where in render_list does this segment appear?
//ubyte no_render_flag[MAX_RENDER_SEGS];
window render_windows[MAX_RENDER_SEGS];

short render_obj_list[MAX_RENDER_SEGS+N_EXTRA_OBJ_LISTS][OBJS_PER_SEG];

//for objects



#define RED   BM_XRGB(63,0,0)
#define WHITE BM_XRGB(63,63,63)

//Global vars for window clip test
int Window_clip_left,Window_clip_top,Window_clip_right,Window_clip_bot;

//Given two sides of segment, tell the two verts which form the 
//edge between them
int Two_sides_to_edge[6][6][2] = {
	{ {-1,-1}, {3,7}, {-1,-1}, {2,6}, {6,7}, {2,3} },
	{ {3,7}, {-1,-1}, {0,4}, {-1,-1}, {4,7}, {0,3} },
	{ {-1,-1}, {0,4}, {-1,-1}, {1,5}, {4,5}, {0,1} },
	{ {2,6}, {-1,-1}, {1,5}, {-1,-1}, {5,6}, {1,2} },
	{ {6,7}, {4,7}, {4,5}, {5,6}, {-1,-1}, {-1,-1} },
	{ {2,3}, {0,3}, {0,1}, {1,2}, {-1,-1}, {-1,-1} }
};

//given an edge specified by two verts, give the two sides on that edge
int Edge_to_sides[8][8][2] = {
	{ {-1,-1}, {2,5}, {-1,-1}, {1,5}, {1,2}, {-1,-1}, {-1,-1}, {-1,-1} },
	{ {2,5}, {-1,-1}, {3,5}, {-1,-1}, {-1,-1}, {2,3}, {-1,-1}, {-1,-1} },
	{ {-1,-1}, {3,5}, {-1,-1}, {0,5}, {-1,-1}, {-1,-1}, {0,3}, {-1,-1} },
	{ {1,5}, {-1,-1}, {0,5}, {-1,-1}, {-1,-1}, {-1,-1}, {-1,-1}, {0,1} },
	{ {1,2}, {-1,-1}, {-1,-1}, {-1,-1}, {-1,-1}, {2,4}, {-1,-1}, {1,4} },
	{ {-1,-1}, {2,3}, {-1,-1}, {-1,-1}, {2,4}, {-1,-1}, {3,4}, {-1,-1} },
	{ {-1,-1}, {-1,-1}, {0,3}, {-1,-1}, {-1,-1}, {3,4}, {-1,-1}, {0,4} },
	{ {-1,-1}, {-1,-1}, {-1,-1}, {0,1}, {1,4}, {-1,-1}, {0,4}, {-1,-1} },
};

//@@//perform simple check on tables
//@@check_check()
//@@{
//@@	int i,j;
//@@
//@@	for (i=0;i<8;i++)
//@@		for (j=0;j<8;j++)
//@@			Assert(Edge_to_sides[i][j][0] == Edge_to_sides[j][i][0] && 
//@@					Edge_to_sides[i][j][1] == Edge_to_sides[j][i][1]);
//@@
//@@	for (i=0;i<6;i++)
//@@		for (j=0;j<6;j++)
//@@			Assert(Two_sides_to_edge[i][j][0] == Two_sides_to_edge[j][i][0] && 
//@@					Two_sides_to_edge[i][j][1] == Two_sides_to_edge[j][i][1]);
//@@
//@@
//@@}


//given an edge, tell what side is on that edge
find_seg_side(segment *seg,short *verts,int notside)
{
	int i;
	int vv0=-1,vv1=-1;
	int side0,side1;
	int *eptr;
	int	v0,v1;
	short	*vp;

//@@	check_check();

	v0 = verts[0];
	v1 = verts[1];
	vp = seg->verts;

	for (i=0; i<8; i++) {
		int svv = *vp++;	// seg->verts[i];

		if (vv0==-1 && svv == v0) {
			vv0 = i;
			if (vv1 != -1)
				break;
		}

		if (vv1==-1 && svv == v1) {
			vv1 = i;
			if (vv0 != -1)
				break;
		}
	}

	Assert(vv0!=-1 && vv1!=-1);

	eptr = Edge_to_sides[vv0][vv1];

	side0 = eptr[0];
	side1 = eptr[1];

	Assert(side0!=-1 && side1!=-1);

	if (side0 != notside) {
		Assert(side1==notside);
		return side0;
	}
	else {
		Assert(side0==notside);
		return side1;
	}

}

//find the two segments that join a given seg though two sides, and
//the sides of those segments the abut. 
find_joining_side_norms(vms_vector *norm0_0,vms_vector *norm0_1,vms_vector *norm1_0,vms_vector *norm1_1,vms_vector **pnt0,vms_vector **pnt1,segment *seg,int s0,int s1)
{
	segment *seg0,*seg1;
	short edge_verts[2];
	int notside0,notside1;
	int edgeside0,edgeside1;

	Assert(s0!=-1 && s1!=-1);

	seg0 = &Segments[seg->children[s0]];
	seg1 = &Segments[seg->children[s1]];

	edge_verts[0] = seg->verts[Two_sides_to_edge[s0][s1][0]];
	edge_verts[1] = seg->verts[Two_sides_to_edge[s0][s1][1]];

	Assert(edge_verts[0]!=-1 && edge_verts[1]!=-1);

	notside0 = find_connect_side(seg,seg0);
	Assert(notside0 != -1);
	notside1 = find_connect_side(seg,seg1);
	Assert(notside1 != -1);

	edgeside0 = find_seg_side(seg0,edge_verts,notside0);
	edgeside1 = find_seg_side(seg1,edge_verts,notside1);

	//deal with the case where an edge is shared by more than two segments

//@@	if (IS_CHILD(seg0->children[edgeside0])) {
//@@		segment *seg00;
//@@		int notside00;
//@@
//@@		seg00 = &Segments[seg0->children[edgeside0]];
//@@
//@@		if (seg00 != seg1) {
//@@
//@@			notside00 = find_connect_side(seg0,seg00);
//@@			Assert(notside00 != -1);
//@@
//@@			edgeside0 = find_seg_side(seg00,edge_verts,notside00);
//@@	 		seg0 = seg00;
//@@		}
//@@
//@@	}
//@@
//@@	if (IS_CHILD(seg1->children[edgeside1])) {
//@@		segment *seg11;
//@@		int notside11;
//@@
//@@		seg11 = &Segments[seg1->children[edgeside1]];
//@@
//@@		if (seg11 != seg0) {
//@@			notside11 = find_connect_side(seg1,seg11);
//@@			Assert(notside11 != -1);
//@@
//@@			edgeside1 = find_seg_side(seg11,edge_verts,notside11);
//@@ 			seg1 = seg11;
//@@		}
//@@	}

//	if ( IS_CHILD(seg0->children[edgeside0]) ||
//		  IS_CHILD(seg1->children[edgeside1])) 
//		return 0;

	#ifdef COMPACT_SEGS
		get_side_normals(seg0, edgeside0, norm0_0, norm0_1 );
		get_side_normals(seg1, edgeside1, norm1_0, norm1_1 );
	#else 
		*norm0_0 = seg0->sides[edgeside0].normals[0];
		*norm0_1 = seg0->sides[edgeside0].normals[1];
		*norm1_0 = seg1->sides[edgeside1].normals[0];
		*norm1_1 = seg1->sides[edgeside1].normals[1];
	#endif

	*pnt0 = &Vertices[seg0->verts[Side_to_verts[edgeside0][seg0->sides[edgeside0].type==3?1:0]]];
	*pnt1 = &Vertices[seg1->verts[Side_to_verts[edgeside1][seg1->sides[edgeside1].type==3?1:0]]];

	return 1;
}

//see if the order matters for these two children.
//returns 0 if order doesn't matter, 1 if c0 before c1, -1 if c1 before c0
compare_children(segment *seg,short c0,short c1)
{
	vms_vector norm0_0,norm0_1,*pnt0,temp;
	vms_vector norm1_0,norm1_1,*pnt1;
	fix d0_0,d0_1,d1_0,d1_1,d0,d1;
int t;

	if (Side_opposite[c0] == c1) return 0;

	Assert(c0!=-1 && c1!=-1);

	//find normals of adjoining sides

	t = find_joining_side_norms(&norm0_0,&norm0_1,&norm1_0,&norm1_1,&pnt0,&pnt1,seg,c0,c1);

//if (!t)
// return 0;

	vm_vec_sub(&temp,&Viewer_eye,pnt0);
	d0_0 = vm_vec_dot(&norm0_0,&temp);
	d0_1 = vm_vec_dot(&norm0_1,&temp);

	vm_vec_sub(&temp,&Viewer_eye,pnt1);
	d1_0 = vm_vec_dot(&norm1_0,&temp);
	d1_1 = vm_vec_dot(&norm1_1,&temp);

	d0 = (d0_0 < 0 || d0_1 < 0)?-1:1;
	d1 = (d1_0 < 0 || d1_1 < 0)?-1:1;

	if (d0 < 0 && d1 < 0)
		return 0;

	if (d0 < 0)
		return 1;
	else if (d1 < 0)
		return -1;
	else
		return 0;

}

int ssc_total=0,ssc_swaps=0;

//short the children of segment to render in the correct order
//returns non-zero if swaps were made
int sort_seg_children(segment *seg,int n_children,short *child_list)
{
	int i,j;
	int r;
	int made_swaps,count;

	if (n_children == 0) return 0;

 ssc_total++;

	//for each child,  compare with other children and see if order matters
	//if order matters, fix if wrong

	count = 0;

	do {
		made_swaps = 0;

		for (i=0;i<n_children-1;i++)
			for (j=i+1;child_list[i]!=-1 && j<n_children;j++)
				if (child_list[j]!=-1) {
					r = compare_children(seg,child_list[i],child_list[j]);

					if (r == 1) {
						int temp = child_list[i];
						child_list[i] = child_list[j];
						child_list[j] = temp;
						made_swaps=1;
					}
				}

	} while (made_swaps && ++count<n_children);

 if (count)
  ssc_swaps++;

	return count;
}

add_obj_to_seglist(int objnum,int listnum)
{
	int i,checkn,marker;

	checkn = listnum;

	//first, find a slot

//mprintf((0,"adding obj %d to %d",objnum,listnum));

	do {

		for (i=0;render_obj_list[checkn][i] >= 0;i++);
	
		Assert(i < OBJS_PER_SEG);
	
		marker = render_obj_list[checkn][i];

		if (marker != -1) {
			checkn = -marker;
			//Assert(checkn < MAX_RENDER_SEGS+N_EXTRA_OBJ_LISTS);
			if (checkn >= MAX_RENDER_SEGS+N_EXTRA_OBJ_LISTS) {
				Int3();
				return;
			}
		}

	} while (marker != -1);

//mprintf((0,"  slot %d,%d",checkn,i));


	//now we have found a slot.  put object in it

	if (i != OBJS_PER_SEG-1) {

		render_obj_list[checkn][i] = objnum;
		render_obj_list[checkn][i+1] = -1;
	}
	else {				//chain to additional list
		int lookn;

		//find an available sublist

		for (lookn=MAX_RENDER_SEGS;render_obj_list[lookn][0]!=-1 && lookn<MAX_RENDER_SEGS+N_EXTRA_OBJ_LISTS;lookn++);

		//Assert(lookn<MAX_RENDER_SEGS+N_EXTRA_OBJ_LISTS);
		if (lookn >= MAX_RENDER_SEGS+N_EXTRA_OBJ_LISTS) {
			Int3();
			return;
		}

		render_obj_list[checkn][i] = -lookn;
		render_obj_list[lookn][0] = objnum;
		render_obj_list[lookn][1] = -1;

	}

//mprintf((0,"  added!\n"));

}

#define SORT_LIST_SIZE 50

typedef struct sort_item {
	int objnum;
	fix dist;
} sort_item;

sort_item sort_list[SORT_LIST_SIZE];
int n_sort_items;

//compare function for object sort. 
int sort_func(const sort_item *a, const sort_item *b)
{
	fix delta_dist;
	object *obj_a,*obj_b;

	delta_dist = a->dist - b->dist;

	obj_a = &Objects[a->objnum];
	obj_b = &Objects[b->objnum];

	if (abs(delta_dist) < (obj_a->size + obj_b->size)) {		//same position

		//these two objects are in the same position.  see if one is a fireball
		//or laser or something that should plot on top

		if (obj_a->type == OBJ_WEAPON || obj_a->type == OBJ_FIREBALL)
			if (!(obj_b->type == OBJ_WEAPON || obj_b->type == OBJ_FIREBALL))
				return -1;	//a is weapon, b is not, so say a is closer
			else;				//both are weapons 
		else
			if (obj_b->type == OBJ_WEAPON || obj_b->type == OBJ_FIREBALL)
				return 1;	//b is weapon, a is not, so say a is farther

		//no special case, fall through to normal return
	}

	return delta_dist;	//return distance
}

build_object_lists(int n_segs)
{
	int nn;

//mprintf((0,"build n_segs=%d",n_segs));

	for (nn=0;nn<MAX_RENDER_SEGS+N_EXTRA_OBJ_LISTS;nn++)
		render_obj_list[nn][0] = -1;

	for (nn=0;nn<n_segs;nn++) {
		int segnum;

		segnum = Render_list[nn];

//mprintf((0,"nn=%d seg=%d ",nn,segnum));

		if (segnum != -1) {
			int objnum;
			object *obj;

			for (objnum=Segments[segnum].objects;objnum!=-1;objnum = obj->next) {
				int new_segnum,did_migrate,list_pos;

				obj = &Objects[objnum];

				Assert( obj->segnum == segnum );

				if (obj->flags & OF_ATTACHED)
					continue;		//ignore this object

				new_segnum = segnum;
				list_pos = nn;

//mprintf((0,"objnum=%d ",objnum));
				if (obj->type != OBJ_CNTRLCEN)		//don't migrate controlcen
				do {
					segmasks m;

					did_migrate = 0;
	
					m = get_seg_masks(&obj->pos,new_segnum,obj->size);
	
					if (m.sidemask) {
						int sn,sf;

						for (sn=0,sf=1;sn<6;sn++,sf<<=1)
							if (m.sidemask & sf) {
								segment *seg = &Segments[obj->segnum];
		
								if (WALL_IS_DOORWAY(seg,sn) & WID_FLY_FLAG) {		//can explosion migrate through
									int child = seg->children[sn];
									int checknp;
		
									for (checknp=list_pos;checknp--;)
										if (Render_list[checknp] == child) {
//mprintf((0,"mig from %d to %d ",new_segnum,child));
											new_segnum = child;
											list_pos = checknp;
											did_migrate = 1;
										}
								}
							}
					}
	
				} while (did_migrate);

				add_obj_to_seglist(objnum,list_pos);
	
			}

		}
	}

//mprintf((0,"done build "));

	//now that there's a list for each segment, sort the items in those lists
	for (nn=0;nn<n_segs;nn++) {
		int segnum;

		segnum = Render_list[nn];

//mprintf((0,"nn=%d seg=%d ",nn,segnum));

		if (segnum != -1) {
			int t,lookn,i,n;

			//first count the number of objects & copy into sort list

			lookn = nn;
			i = n_sort_items = 0;
			while ((t=render_obj_list[lookn][i++])!=-1)
				if (t<0)
					{lookn = -t; i=0;}
				else
					if (n_sort_items < SORT_LIST_SIZE-1) {		//add if room
						sort_list[n_sort_items].objnum = t;
						//NOTE: maybe use depth, not dist - quicker computation
						sort_list[n_sort_items].dist = vm_vec_dist_quick(&Objects[t].pos,&Viewer_eye);
						n_sort_items++;
					}


			//now call qsort

			qsort(sort_list,n_sort_items,sizeof(*sort_list),sort_func);

			//now copy back into list

			lookn = nn;
			i = 0;
			n = n_sort_items;
			while ((t=render_obj_list[lookn][i])!=-1 && n>0)
				if (t<0)
					{lookn = -t; i=0;}
				else
					render_obj_list[lookn][i++] = sort_list[--n].objnum;
			render_obj_list[lookn][i] = -1;	//mark (possibly new) end
		}
	}
}

int Use_player_head_angles = 0;
vms_angvec Player_head_angles;

extern int Num_tmaps_drawn;
extern int Total_pixels;
//--unused-- int Total_num_tmaps_drawn=0;

int Rear_view=0;

#ifdef JOHN_ZOOM
fix Zoom_factor=F1_0;
#endif
//renders onto current canvas
void render_frame(fix eye_offset)
{
	int start_seg_num;

//Total_num_tmaps_drawn += Num_tmaps_drawn;
//if ((FrameCount > 0) && (Total_num_tmaps_drawn))
//	mprintf((0, "Frame: %4i, total = %6i, Avg = %7.3f, Avgpix=%7.3f\n", Num_tmaps_drawn, Total_num_tmaps_drawn, (float) Total_num_tmaps_drawn/FrameCount, (float) Total_pixels/Total_num_tmaps_drawn));
//Num_tmaps_drawn = 0;

	if (Endlevel_sequence) {
		render_endlevel_frame(eye_offset);
		FrameCount++;
		return;
	}

	if ( Newdemo_state == ND_STATE_RECORDING )	{
		newdemo_record_start_frame(FrameCount, FrameTime );
		newdemo_record_viewer_object(Viewer);
	}

	g3_start_frame();

	Viewer_eye = Viewer->pos;

//	if (Viewer->type == OBJ_PLAYER && (Cockpit_mode!=CM_REAR_VIEW))
//		vm_vec_scale_add2(&Viewer_eye,&Viewer->orient.fvec,(Viewer->size*3)/4);

	if (eye_offset)	{
		vm_vec_scale_add2(&Viewer_eye,&Viewer->orient.rvec,eye_offset);
	}

	#ifdef EDITOR
	if (Function_mode==FMODE_EDITOR)
		Viewer_eye = Viewer->pos;
	#endif

	start_seg_num = find_point_seg(&Viewer_eye,Viewer->segnum);

	if (start_seg_num==-1)
		start_seg_num = Viewer->segnum;

	if (Viewer==ConsoleObject && Use_player_head_angles) {
		vms_matrix headm,viewm;
		vm_angles_2_matrix(&headm,&Player_head_angles);
		vm_matrix_x_matrix(&viewm,&Viewer->orient,&headm);
		g3_set_view_matrix(&Viewer_eye,&viewm,Render_zoom);
	//@@} else if ((Cockpit_mode==CM_REAR_VIEW) && (Viewer==ConsoleObject)) {
	} else if (Rear_view && (Viewer==ConsoleObject)) {
		vms_matrix headm,viewm;
		Player_head_angles.p = Player_head_angles.b = 0;
		Player_head_angles.h = 0x7fff;
		vm_angles_2_matrix(&headm,&Player_head_angles);
		vm_matrix_x_matrix(&viewm,&Viewer->orient,&headm);
		g3_set_view_matrix(&Viewer_eye,&viewm,Render_zoom);
	} else	{
#ifdef JOHN_ZOOM
		if (keyd_pressed[KEY_RSHIFT] )	{
			Zoom_factor += FrameTime*4;
			if (Zoom_factor > F1_0*5 ) Zoom_factor=F1_0*5;
		} else {
			Zoom_factor -= FrameTime*4;
			if (Zoom_factor < F1_0 ) Zoom_factor = F1_0;
		}
		g3_set_view_matrix(&Viewer_eye,&Viewer->orient,fixdiv(Render_zoom,Zoom_factor));
#else
		g3_set_view_matrix(&Viewer_eye,&Viewer->orient,Render_zoom);
#endif
	}

	if (Clear_window == 1) {
		if (Clear_window_color == -1)
			Clear_window_color = BM_XRGB(0, 0, 0);	//BM_XRGB(31, 15, 7);
		gr_clear_canvas(Clear_window_color);
	}

	render_mine(start_seg_num,eye_offset);

	if (Use_player_head_angles ) 
		draw_3d_reticle(eye_offset);

	g3_end_frame();

	FrameCount++;		//we have rendered a frame
}

int first_terminal_seg;

//build a list of segments to be rendered
//fills in Render_list & N_render_segs
build_segment_list(int start_seg_num)
{
	int	lcnt,scnt,ecnt;
	int	l,c;
	int	ch;

	memset(visited, 0, sizeof(visited[0])*(Highest_segment_index+1));
	memset(render_pos, -1, sizeof(render_pos[0])*(Highest_segment_index+1));
	//memset(no_render_flag, 0, sizeof(no_render_flag[0])*(MAX_RENDER_SEGS));
	memset(processed, 0, sizeof(processed));

	#ifndef NDEBUG
	memset(visited2, 0, sizeof(visited2[0])*(Highest_segment_index+1));
	#endif

	lcnt = scnt = 0;

	Render_list[lcnt] = start_seg_num; visited[start_seg_num]=1;
	Seg_depth[lcnt] = 0;
	lcnt++;
	ecnt = lcnt;
	render_pos[start_seg_num] = 0;

	#ifndef NDEBUG
	if (pre_draw_segs)
		render_segment(start_seg_num);
	#endif

	render_windows[0].left=render_windows[0].top=0;
	render_windows[0].right=grd_curcanv->cv_bitmap.bm_w-1;
	render_windows[0].bot=grd_curcanv->cv_bitmap.bm_h-1;

	//breadth-first renderer

	//build list

	for (l=0;l<Render_depth;l++) {

		//while (scnt < ecnt) {
		for (scnt=0;scnt < ecnt;scnt++) {
			int rotated,segnum;
			window *check_w;
			short child_list[MAX_SIDES_PER_SEGMENT];		//list of ordered sides to process
			int n_children;										//how many sides in child_list
			segment *seg;

			if (processed[scnt])
				continue;

			processed[scnt]=1;

			segnum = Render_list[scnt];
			check_w = &render_windows[scnt];

			#ifndef NDEBUG
			if (draw_boxes)
				draw_window_box(RED,check_w->left,check_w->top,check_w->right,check_w->bot);
			#endif

			if (segnum == -1) continue;

			seg = &Segments[segnum];
			rotated=0;

			//look at all sides of this segment.
			//tricky code to look at sides in correct order follows

			for (c=n_children=0;c<MAX_SIDES_PER_SEGMENT;c++) {		//build list of sides
				int wid;

				wid = WALL_IS_DOORWAY(seg, c);

				ch=seg->children[c];

				if ( (window_check || !visited[ch]) && (wid & WID_RENDPAST_FLAG) ) {
					if (behind_check) {
						byte *sv = Side_to_verts[c];
						ubyte codes_and=0xff;
						int i;

						rotate_list(8,seg->verts);
						rotated=1;

						for (i=0;i<4;i++)
							codes_and &= Segment_points[seg->verts[sv[i]]].p3_codes;

						if (codes_and & CC_BEHIND) continue;

					}
					child_list[n_children++] = c;
				}
			}

			//now order the sides in some magical way

			if (new_seg_sorting)
				sort_seg_children(seg,n_children,child_list);

			//for (c=0;c<MAX_SIDES_PER_SEGMENT;c++)	{
			//	ch=seg->children[c];

			for (c=0;c<n_children;c++) {
				int siden;

				siden = child_list[c];
				ch=seg->children[siden];
				//if ( (window_check || !visited[ch])&& (WALL_IS_DOORWAY(seg, c))) {
				{
					if (window_check) {
						int i;
						ubyte codes_and_3d,codes_and_2d;
						short _x,_y,min_x=32767,max_x=-32767,min_y=32767,max_y=-32767;
						int no_proj_flag=0;	//a point wasn't projected

						if (rotated<2) {
							if (!rotated)
								rotate_list(8,seg->verts);
							project_list(8,seg->verts);
							rotated=2;
						}

						for (i=0,codes_and_3d=codes_and_2d=0xff;i<4;i++) {
							int p = seg->verts[Side_to_verts[siden][i]];
							g3s_point *pnt = &Segment_points[p];

							if (! (pnt->p3_flags&PF_PROJECTED)) {no_proj_flag=1; break;}

							_x = f2i(pnt->p3_sx);
							_y = f2i(pnt->p3_sy);

							codes_and_3d &= pnt->p3_codes;
							codes_and_2d &= code_window_point(_x,_y,check_w);

							#ifndef NDEBUG
							if (draw_edges) {
								gr_setcolor(BM_XRGB(31,0,31));
								gr_line(pnt->p3_sx,pnt->p3_sy,
									Segment_points[seg->verts[Side_to_verts[siden][(i+1)%4]]].p3_sx,
									Segment_points[seg->verts[Side_to_verts[siden][(i+1)%4]]].p3_sy);
							}
							#endif

							if (_x < min_x) min_x = _x;
							if (_x > max_x) max_x = _x;

							if (_y < min_y) min_y = _y;
							if (_y > max_y) max_y = _y;

						}

						#ifndef NDEBUG
						if (draw_boxes)
							draw_window_box(WHITE,min_x,min_y,max_x,max_y);
						#endif

						if (no_proj_flag || (!codes_and_3d && !codes_and_2d)) {	//maybe add this segment
							int rp = render_pos[ch];
							window *new_w = &render_windows[lcnt];

							if (no_proj_flag) *new_w = *check_w;
							else {
								new_w->left  = max(check_w->left,min_x);
								new_w->right = min(check_w->right,max_x);
								new_w->top   = max(check_w->top,min_y);
								new_w->bot   = min(check_w->bot,max_y);
							}

							//see if this seg already visited, and if so, does current window
							//expand the old window?
							if (rp != -1) {
								if (new_w->left < render_windows[rp].left ||
										 new_w->top < render_windows[rp].top ||
										 new_w->right > render_windows[rp].right ||
										 new_w->bot > render_windows[rp].bot) {

									new_w->left  = min(new_w->left,render_windows[rp].left);
									new_w->right = max(new_w->right,render_windows[rp].right);
									new_w->top   = min(new_w->top,render_windows[rp].top);
									new_w->bot   = max(new_w->bot,render_windows[rp].bot);

									if (no_migrate_segs) {
										//no_render_flag[lcnt] = 1;
										Render_list[lcnt] = -1;
										render_windows[rp] = *new_w;		//get updated window
										processed[rp] = 0;		//force reprocess
										goto no_add;
									}
									else
										Render_list[rp]=-1;
								}
								else goto no_add;
							}

							#ifndef NDEBUG
							if (draw_boxes)
								draw_window_box(5,new_w->left,new_w->top,new_w->right,new_w->bot);
							#endif

							render_pos[ch] = lcnt;
							Render_list[lcnt] = ch;
							Seg_depth[lcnt] = l;
							lcnt++;
							if (lcnt >= MAX_RENDER_SEGS) {mprintf((0,"Too many segs in render list!!\n")); goto done_list;}
							visited[ch] = 1;

							#ifndef NDEBUG
							if (pre_draw_segs)
								render_segment(ch);
							#endif
no_add:
	;

						}
					}
					else {
						Render_list[lcnt] = ch;
						Seg_depth[lcnt] = l;
						lcnt++;
						if (lcnt >= MAX_RENDER_SEGS) {mprintf((0,"Too many segs in render list!!\n")); goto done_list;}
						visited[ch] = 1;
					}
				}
			}
		}

		scnt = ecnt;
		ecnt = lcnt;

	}
done_list:

	lcnt_save = lcnt;
	scnt_save = scnt;

	first_terminal_seg = scnt;
	N_render_segs = lcnt;

}

//renders onto current canvas
void render_mine(int start_seg_num,fix eye_offset)
{
	int		i;
	int		nn;

	//	Initialize number of objects (actually, robots!) rendered this frame.
	Num_rendered_objects = 0;

#ifdef LASER_HACK
	Hack_nlasers = 0;
#endif

	#ifndef NDEBUG
	for (i=0;i<=Highest_object_index;i++)
		object_rendered[i] = 0;
	#endif

	//set up for rendering

	render_start_frame();


	#if defined(EDITOR) && !defined(NDEUBG)
	if (Show_only_curside) {
		rotate_list(8,&Cursegp->verts);
		render_side(Cursegp,Curside);
		goto done_rendering;
	}
	#endif


	#ifdef EDITOR
	if (_search_mode || eye_offset>0)	{
		//lcnt = lcnt_save;
		//scnt = scnt_save;
	}
	else
	#endif
		//NOTE LINK TO ABOVE!!
		build_segment_list(start_seg_num);		//fills in Render_list & N_render_segs

	//render away

	#ifndef NDEBUG
	if (!window_check) {
		Window_clip_left  = Window_clip_top = 0;
		Window_clip_right = grd_curcanv->cv_bitmap.bm_w-1;
		Window_clip_bot   = grd_curcanv->cv_bitmap.bm_h-1;
	}
	#endif

	#ifndef NDEBUG
	if (!(_search_mode || eye_offset>0)) {
		int i;

		for (i=0;i<N_render_segs;i++) {
			int segnum;

			segnum = Render_list[i];

			if (segnum != -1)
				if (visited2[segnum]) {
					Int3();		//get Matt
				}
				else
					visited2[segnum] = 1;
		}
	}
	#endif

//	if (!(_search_mode || eye_offset>0) && migrate_objects)
	if (!(_search_mode))
		build_object_lists(N_render_segs);

	if (eye_offset<=0)		// Do for left eye or zero.
		set_dynamic_light();

	if (!_search_mode && Clear_window == 2) {
		if (first_terminal_seg < N_render_segs) {
			int i;

			if (Clear_window_color == -1)
				Clear_window_color = BM_XRGB(0, 0, 0);	//BM_XRGB(31, 15, 7);
	
			gr_setcolor(Clear_window_color);
	
			for (i=first_terminal_seg; i<N_render_segs; i++) {
				if (Render_list[i] != -1) {
					#ifndef NDEBUG
					if ((render_windows[i].left == -1) || (render_windows[i].top == -1) || (render_windows[i].right == -1) || (render_windows[i].bot == -1))
						{Int3();}
					else
					#endif
						//NOTE LINK TO ABOVE!
						gr_rect(render_windows[i].left, render_windows[i].top, render_windows[i].right, render_windows[i].bot);
				}
			}
		}
	}

	for (nn=N_render_segs;nn--;) {
		int segnum;
		int objnp;

		// Interpolation_method = 0;
		segnum = Render_list[nn];
		Current_seg_depth = Seg_depth[nn];

		//if (!no_render_flag[nn])
		if (segnum!=-1 && (_search_mode || eye_offset>0 || visited[segnum]!=255)) {
			//set global render window vars

			if (window_check) {
				Window_clip_left  = render_windows[nn].left;
				Window_clip_top   = render_windows[nn].top;
				Window_clip_right = render_windows[nn].right;
				Window_clip_bot   = render_windows[nn].bot;
			}

			//mprintf((0," %d",segnum));

			render_segment(segnum); 
			visited[segnum]=255;

			if (window_check) {		//reset for objects
				Window_clip_left  = Window_clip_top = 0;
				Window_clip_right = grd_curcanv->cv_bitmap.bm_w-1;
				Window_clip_bot   = grd_curcanv->cv_bitmap.bm_h-1;
			}

			if (migrate_objects) {
				//int n_expl_objs=0,expl_objs[5],i;
				int listnum;
				int save_linear_depth = Max_linear_depth;

				Max_linear_depth = Max_linear_depth_objects;

				listnum = nn;

				//mprintf((0,"render objs seg %d",segnum));

				for (objnp=0;render_obj_list[listnum][objnp]!=-1;)	{
					int ObjNumber = render_obj_list[listnum][objnp];

					if (ObjNumber >= 0) {

						//mprintf( (0, "Type: %d\n", Objects[ObjNumber].type ));
	
						//if (Objects[ObjNumber].type == OBJ_FIREBALL && n_expl_objs<5)	{
						//	expl_objs[n_expl_objs++] = ObjNumber;
	 					//} else
						#ifdef LASER_HACK
						if ( 	(Objects[ObjNumber].type==OBJ_WEAPON) && 								//if its a weapon
								(Objects[ObjNumber].lifeleft==Laser_max_time ) && 	//  and its in it's first frame
								(Hack_nlasers< MAX_HACKED_LASERS) && 									//  and we have space for it
								(Objects[ObjNumber].laser_info.parent_num>-1) &&					//  and it has a parent
								((Viewer-Objects)==Objects[ObjNumber].laser_info.parent_num)	//  and it's parent is the viewer
						   )		{
							Hack_laser_list[Hack_nlasers++] = ObjNumber;								//then make it draw after everything else.
							//mprintf( (0, "O%d ", ObjNumber ));
						} else	
						#endif
							do_render_object(ObjNumber);	// note link to above else

						objnp++;
					}
					else {

						listnum = -ObjNumber;
						objnp = 0;

					}

				}

				//for (i=0;i<n_expl_objs;i++)
				//	do_render_object(expl_objs[i]);

				//mprintf((0,"done seg %d\n",segnum));

				Max_linear_depth = save_linear_depth;

			}

		}
	}

	//mprintf((0,"\n"));

								
#ifdef LASER_HACK								
	// Draw the hacked lasers last
	for (i=0; i < Hack_nlasers; i++ )	{
		//mprintf( (0, "D%d ", Hack_laser_list[i] ));
		do_render_object(Hack_laser_list[i]);
	}
#endif

	// -- commented out by mk on 09/14/94...did i do a good thing??  object_render_targets();

#ifdef EDITOR
	#ifndef NDEUBG
	//draw curedge stuff
	if (Outline_mode) outline_seg_side(Cursegp,Curside,Curedge,Curvert);
	#endif

done_rendering:
	;

#endif

}
#ifdef EDITOR

extern int render_3d_in_big_window;

//finds what segment is at a given x&y -  seg,side,face are filled in
//works on last frame rendered. returns true if found
//if seg<0, then an object was found, and the object number is -seg-1
int find_seg_side_face(short x,short y,int *seg,int *side,int *face,int *poly)
{
	_search_mode = -1;

	_search_x = x; _search_y = y;

	found_seg = -1;

	if (render_3d_in_big_window) {
		grs_canvas temp_canvas;

		gr_init_sub_canvas(&temp_canvas,canv_offscreen,0,0,
			LargeView.ev_canv->cv_bitmap.bm_w,LargeView.ev_canv->cv_bitmap.bm_h);

		gr_set_current_canvas(&temp_canvas);

		render_frame(0);
	}
	else {
		gr_set_current_canvas(&VR_render_sub_buffer[0]);	//render off-screen
		render_frame(0);
	}

	_search_mode = 0;

	*seg = found_seg;
	*side = found_side;
	*face = found_face;
	*poly = found_poly;

//	mprintf((0,"found seg=%d, side=%d, face=%d, poly=%d\n",found_seg,found_side,found_face,found_poly));

	return (found_seg!=-1);

}

#endif
