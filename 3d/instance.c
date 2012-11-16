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
 * $Source: Smoke:miner:source:3d::RCS:instance.c $
 * $Revision: 1.2 $
 * $Author: allender $
 * $Date: 1995/06/12 12:36:57 $
 * 
 * Instancing routines
 * 
 * $Log: instance.c $
 * Revision 1.2  1995/06/12  12:36:57  allender
 * fixed bug where g3_start_instance_angles recursively called itself
 *
 * Revision 1.1  1995/05/05  08:51:27  allender
 * Initial revision
 *
 * Revision 1.1  1995/04/17  06:43:29  matt
 * Initial revision
 * 
 * 
 */

#pragma off (unreferenced)
static char rcsid[] = "$Id: instance.c 1.2 1995/06/12 12:36:57 allender Exp $";
#pragma on (unreferenced)

#include "error.h"

#include "3d.h"
#include "globvars.h"

#define MAX_INSTANCE_DEPTH	5

struct instance_context {
	vms_matrix m;
	vms_vector p;
} instance_stack[MAX_INSTANCE_DEPTH];

int instance_depth = 0;

//instance at specified point with specified orientation
//if matrix==NULL, don't modify matrix.  This will be like doing an offset   
void g3_start_instance_matrix(vms_vector *pos,vms_matrix *orient)
{
	vms_vector tempv;
	vms_matrix tempm,tempm2;

	Assert(instance_depth<MAX_INSTANCE_DEPTH);

	instance_stack[instance_depth].m = View_matrix;
	instance_stack[instance_depth].p = View_position;
	instance_depth++;

	//step 1: subtract object position from view position

	vm_vec_sub(&tempv,&View_position,pos);


	if (orient) {

		//step 2: rotate view vector through object matrix

		vm_vec_rotate(&View_position,&tempv,orient);

		//step 3: rotate object matrix through view_matrix (vm = ob * vm)

		vm_copy_transpose_matrix(&tempm2,orient);

		vm_matrix_x_matrix(&tempm,&tempm2,&View_matrix);
		View_matrix = tempm;
	}
}


//instance at specified point with specified orientation
//if angles==NULL, don't modify matrix.  This will be like doing an offset
void g3_start_instance_angles(vms_vector *pos,vms_angvec *angles)
{
	vms_matrix tm;

	if (angles==NULL) {
		g3_start_instance_matrix(pos,NULL);
		return;
	}

	vm_angles_2_matrix(&tm,angles);

	g3_start_instance_matrix(pos,&tm);

}


//pops the old context
void g3_done_instance()
{
	instance_depth--;

	Assert(instance_depth >= 0);

	View_position = instance_stack[instance_depth].p;
	View_matrix = instance_stack[instance_depth].m;
}


