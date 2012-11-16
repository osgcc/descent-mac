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
 * $Source: Smoke:miner:source:main::RCS:CNTRLCEN.H $
 * $Revision: 1.1 $
 * $Author: allender $
 * $Date: 1995/05/16 15:54:54 $
 * 
 * Header for cntrlcen.c
 * 
 * $Log: CNTRLCEN.H $
 * Revision 1.1  1995/05/16  15:54:54  allender
 * Initial revision
 *
 * Revision 2.0  1995/02/27  11:30:40  john
 * New version 2.0, which has no anonymous unions, builds with
 * Watcom 10.0, and doesn't require parsing BITMAPS.TBL.
 * 
 * Revision 1.7  1995/02/01  16:34:14  john
 * Linted.
 * 
 * Revision 1.6  1995/01/03  20:19:14  john
 * Pretty good working version of game save.
 * 
 * Revision 1.5  1994/11/08  12:18:28  mike
 * small explosions on control center.
 * 
 * Revision 1.4  1994/11/02  18:00:12  rob
 * Added extern for Gun_pos array for network hooks.
 * 
 * Revision 1.3  1994/10/20  09:47:37  mike
 * *** empty log message ***
 * 
 * Revision 1.2  1994/10/17  21:35:10  matt
 * Added support for new Control Center/Main Reactor
 * 
 * Revision 1.1  1994/10/17  20:24:28  matt
 * Initial revision
 * 
 * 
 */

#ifndef _CNTRLCEN_H
#define _CNTRLCEN_H

#include "vecmat.h"
#include "object.h"

#define MAX_CONTROLCEN_GUNS 4
#define CONTROLCEN_WEAPON_NUM	6

extern int	N_controlcen_guns;
extern int	Control_center_been_hit;
extern int	Control_center_player_been_seen;
extern int	Control_center_next_fire_time;
extern int	Control_center_present;
extern int Dead_controlcen_object_num;

extern vms_vector controlcen_gun_points[MAX_CONTROLCEN_GUNS];
extern vms_vector controlcen_gun_dirs[MAX_CONTROLCEN_GUNS];
extern vms_vector Gun_pos[MAX_CONTROLCEN_GUNS];

//return the position & orientation of a gun on the control center object 
extern void calc_controlcen_gun_point(vms_vector *gun_point,vms_vector *gun_dir,object *obj,int gun_num);

//do whatever this thing does in a frame
extern void do_controlcen_frame(object *obj);

//	Initialize control center for a level.
//	Call when a new level is started.
extern void init_controlcen_for_level(void);

extern void do_controlcen_destroyed_stuff(object *objp);
extern void do_controlcen_dead_frame(void);

#endif
