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
 * $Source: Buggin:miner:source:vecmat::RCS:vecmat.h $
 * $Revision: 1.1 $
 * $Author: allender $
 * $Date: 1995/04/17 16:18:05 $
 *
 * Header file for vector/matrix library
 *
 * $Log: vecmat.h $
 * Revision 1.1  1995/04/17  16:18:05  allender
 * Initial revision
 *
 *
 * --- PC RCS Information ---
 * Revision 1.37  1995/02/22  13:23:22  john
 * Added the vms_vector_array structure, to access a vms_vector
 * with an array.
 * 
 * Revision 1.36  1995/02/22  12:34:33  john
 * Took out anonymous unions.
 * 
 * Revision 1.35  1994/12/13  14:44:20  matt
 * Added vm_vector_2_matrix_norm()
 * 
 * Revision 1.34  1994/09/11  19:22:55  matt
 * Added vm_vec_normalized_dir_quick()
 * 
 * Revision 1.33  1994/08/04  19:45:38  matt
 * Added option to make a bunch of functions (add, sub, dotprod) inline
 * 
 * Revision 1.32  1994/07/19  18:52:36  matt
 * Added vm_vec_normalize_quick() and vm_vec_copy_normalize_quick()
 * 
 * Revision 1.31  1994/06/16  18:24:30  matt
 * Added vm_vec_mag_quick()
 * 
 * Revision 1.30  1994/06/10  23:19:00  matt
 * New register usage for vm_vec_ang_2_matrix()
 * 
 * Revision 1.29  1994/06/01  17:32:06  matt
 * Fixed modify list for vm_vec_normalized_dir()
 * 
 * Revision 1.28  1994/05/19  12:07:20  matt
 * Fixed globals and macros and added a constant
 * 
 * Revision 1.27  1994/05/19  09:19:15  matt
 * Made vm_vec_normalized_dir() return mag of vector
 * 
 * Revision 1.26  1994/05/18  22:28:57  matt
 * Added function vm_vec_normalized_dir()
 * Added C macros IS_ZERO_VEC(), vm_vec_zero(), and vm_set_identity()
 * Added C global static vars vmd_zero_vector & vmd_identity_matrix
 * 
 * Revision 1.25  1994/05/18  21:45:06  matt
 * Added functions:
 *   vm_extract_angles_vector()
 *   vm_extract_angles_vector_normalized()
 *   vm_vec_copy_normalize()
 * 
 * Revision 1.24  1994/05/13  12:42:16  matt
 * Added new function, vm_vec_dist_quick(), which does an approximation.
 * 
 * Revision 1.23  1994/03/30  13:37:34  matt
 * Added prototype for vm_vec_scale_add(), and fixed typos
 * 
 * Revision 1.22  1994/03/30  13:29:42  matt
 * Header for vm_vec_scale_add2()
 * 
 * Revision 1.21  1994/01/31  19:45:13  matt
 * Added function vm_extract_angles_matrix()
 * 
 * Revision 1.20  1993/12/21  19:46:14  matt
 * Added function vm_dist_to_plane()
 * 
 * Revision 1.19  1993/12/13  17:26:41  matt
 * Added vm_vec_dist()
 * 
 * Revision 1.18  1993/12/02  12:45:11  matt
 * New functions: vm_vec_copy_scale(), vm_vec_scale2()
 * Aliases: vm_transpose(), vm_vec_dot(), vm_vec_cross(), vm_copy_transpose()
 * 
 * Revision 1.17  1993/10/29  22:38:36  matt
 * Changed matrix order, making direction vectors the rows
 * 
 * Revision 1.16  1993/10/25  11:49:57  matt
 * Made vm_vec_delta_ang() take optional forward vector to return signed delta
 * 
 * Revision 1.15  1993/10/20  01:10:05  matt
 * Added vm_vec_delta_ang(), vm_vec_delta_ang_norm(), and vm_vec_ang_2_matrix()
 * 
 * Revision 1.14  1993/10/17  17:02:52  matt
 * vm_vector_2_matrix() now takes optional right vector
 * 
 * Revision 1.13  1993/10/12  19:31:39  matt
 * Added IDENTITY_MATRIX constant
 * 
 * Revision 1.12  1993/10/08  18:10:16  matt
 * Changed vm_vec_make() and vm_angvec_make() to be inline assembly 
 * functions, to get rid of compiler warnings.  Did not change vm_mat_make(),
 * which could still get warnings if the return value is unused.
 * 
 * Revision 1.11  1993/09/29  12:10:07  matt
 * Changed modified regs in pragmas to include return register
 * 
 * Revision 1.10  1993/09/28  12:15:41  matt
 * Added func vm_vector_2_matrix()
 * 
 * Revision 1.9  1993/09/24  21:18:38  matt
 * Added vm_vec_avg(), vm_vec_avg4(), and vm_angvec_make().
 * Documented which functions could have dest==source
 * 
 * Revision 1.8  1993/09/20  14:56:11  matt
 * Added new function, vm_vec_perp()
 * 
 * Revision 1.7  1993/09/20  14:27:42  mike
 * unfix last fix which introduced a bug
 * 
 * Revision 1.6  1993/09/20  10:11:53  mike
 * no changes
 * 
 * Revision 1.5  1993/09/20  09:58:58  mike
 * Re-fix vm_vec_make
 * 
 * Revision 1.4  1993/09/20  09:41:21  mike
 * Correct vm_vec_make and vm_mat_make macros to return the destination
 * as the value of the macro.
 * 
 * Revision 1.3  1993/09/17  11:23:47  matt
 * Added row access (via xrow,yrow,zrow) to vms_matrix
 * Added macro vm_mat_make(), like vm_vec_make()
 * 
 * Revision 1.2  1993/09/17  11:10:32  matt
 * Added vm_vec_add2() and vm_vec_sub2(), which take 2 args (dest==src0)
 * 
 * Revision 1.1  1993/09/16  20:10:01  matt
 * Initial revision
 * 
 *
 */

#ifndef _VECMAT_H
#define _VECMAT_H

#include "fix.h"

//#define INLINE 1		//are some of these functions inline?

//The basic fixed-point vector.  Access elements by name or position
typedef struct vms_vector {
	fix x,y,z;
} vms_vector;

typedef struct vms_vector_array {
	fix xyz[3];
} vms_vector_array;

//Short vector, used for pre-rotation points. 
//Access elements by name or position
typedef struct vms_svec {
	short sv_x,sv_y,sv_z;
} vms_svec;

//Angle vector.  Used to store orientations
typedef struct vms_angvec {
	fixang p,b,h;
} vms_angvec;

//A 3x3 rotation matrix.  Sorry about the numbering starting with one.
//Ordering is across then down, so <m1,m2,m3> is the first row
typedef struct vms_matrix {
	vms_vector rvec,uvec,fvec;
} vms_matrix;

//Macros/functions to fill in fields of structures

//macro to check if vector is zero
#define IS_VEC_NULL(v) (v->x == 0 && v->y == 0 && v->z == 0)

//macro to set a vector to zero.  we could do this with an in-line assembly 
//macro, but it's probably better to let the compiler optimize it.
//Note: NO RETURN VALUE
#define vm_vec_zero(v) (v)->x=(v)->y=(v)->z=0

//macro set set a matrix to the identity. Note: NO RETURN VALUE
#define vm_set_identity(m) do {m->rvec.x = m->uvec.y = m->fvec.z = f1_0;	\
										m->rvec.y = m->rvec.z = \
										m->uvec.x = m->uvec.z = \
										m->fvec.x = m->fvec.y = 0;} while (0)

vms_vector *vm_vec_make(vms_vector *v,fix x,fix y,fix z);

#pragma aux vm_vec_make "*_" parm [eax] [edx] [ebx] [ecx] value [eax] modify exact [] = \
	"mov 0[eax],edx"	\
	"mov 4[eax],ebx"	\
	"mov 8[eax],ecx";

vms_angvec *vm_angvec_make(vms_angvec *v,fixang p,fixang b,fixang h);

#pragma aux vm_angvec_make "*_" parm [eax] [dx] [bx] [cx] value [eax] modify exact [] = \
	"mov 0[eax],dx"	\
	"mov 2[eax],bx"	\
	"mov 4[eax],cx";

//Global constants

extern vms_vector vmd_zero_vector;
extern vms_matrix vmd_identity_matrix;

//Here's a handy constant

#define ZERO_VECTOR {0,0,0}
#define IDENTITY_MATRIX {f1_0,0,0,0,f1_0,0,0,0,f1_0}

//#define vm_vec_make(v,_x,_y,_z) (((v)->x=(_x), (v)->y=(_y), (v)->z=(_z)), (v))

//#pragma off (unreferenced)
////make this local, so compiler can in-line it
//static vms_vector *vm_vec_make(vms_vector *v,fix x,fix y,fix z)
//{
//	v->x = x;
//	v->y = y;
//	v->z = z;
//
//	return v;
//}
//#pragma on (unreferenced)


////macro to fill in elements of a matrix, also for Mike
//#define vm_mat_make(m,_m1,_m2,_m3,_m4,_m5,_m6,_m7,_m8,_m9) \
//	 do {	(m)->m1=(_m1); (m)->m2=(_m2); (m)->m3=(_m3); \
//			(m)->m4=(_m4); (m)->m5=(_m5); (m)->m6=(_m6); \
//			(m)->m7=(_m7); (m)->m8=(_m8); (m)->m9=(_m9);} while (0)

#if 0	//kill this, since bogus with new matrix ordering

//macro to fill in elements of a matrix, also for Mike
#define vm_mat_make(m,_m1,_m2,_m3,_m4,_m5,_m6,_m7,_m8,_m9) \
	 	( ((m)->m1=(_m1), (m)->m2=(_m2), (m)->m3=(_m3), \
			(m)->m4=(_m4), (m)->m5=(_m5), (m)->m6=(_m6), \
			(m)->m7=(_m7), (m)->m8=(_m8), (m)->m9=(_m9)), (m))

#endif

////fills in fields of an angle vector
//#define vm_angvec_make(v,_p,_b,_h) (((v)->p=(_p), (v)->b=(_b), (v)->h=(_h)), (v))

//negate a vector
#define vm_vec_negate(v) do {(v)->x = - (v)->x; (v)->y = - (v)->y; (v)->z = - (v)->z;} while (0);

//Functions in library

#ifndef INLINE

//adds two vectors, fills in dest, returns ptr to dest
//ok for dest to equal either source, but should use vm_vec_add2() if so
vms_vector *vm_vec_add(vms_vector *dest,vms_vector *src0,vms_vector *src1);

//subs two vectors, fills in dest, returns ptr to dest
//ok for dest to equal either source, but should use vm_vec_sub2() if so
vms_vector *vm_vec_sub(vms_vector *dest,vms_vector *src0,vms_vector *src1);

//adds one vector to another. returns ptr to dest
//dest can equal source
vms_vector *vm_vec_add2(vms_vector *dest,vms_vector *src);

//subs one vector from another, returns ptr to dest
//dest can equal source
vms_vector *vm_vec_sub2(vms_vector *dest,vms_vector *src);

#else

#define vm_vec_add(dest,src0,src1) do {	\
	(dest)->x = (src0)->x + (src1)->x;		\
	(dest)->y = (src0)->y + (src1)->y;		\
	(dest)->z = (src0)->z + (src1)->z;		\
} while (0);

#define vm_vec_sub(dest,src0,src1) do {	\
	(dest)->x = (src0)->x - (src1)->x;		\
	(dest)->y = (src0)->y - (src1)->y;		\
	(dest)->z = (src0)->z - (src1)->z;		\
} while (0);

#define vm_vec_add2(dest,src) do {		\
	(dest)->x += (src)->x;					\
	(dest)->y += (src)->y;					\
	(dest)->z += (src)->z;					\
} while (0);

#define vm_vec_sub2(dest,src) do {		\
	(dest)->x -= (src)->x;					\
	(dest)->y -= (src)->y;					\
	(dest)->z -= (src)->z;					\
} while (0);

#endif

//averages two vectors. returns ptr to dest
//dest can equal either source
vms_vector *vm_vec_avg(vms_vector *dest,vms_vector *src0,vms_vector *src1);

//averages four vectors. returns ptr to dest
//dest can equal any source
vms_vector *vm_vec_avg4(vms_vector *dest,vms_vector *src0,vms_vector *src1,vms_vector *src2,vms_vector *src3);

//scales a vector in place.  returns ptr to vector
vms_vector *vm_vec_scale(vms_vector *dest,fix s);

//scales and copies a vector.  returns ptr to dest
vms_vector *vm_vec_copy_scale(vms_vector *dest,vms_vector *src,fix s);

//scales a vector, adds it to another, and stores in a 3rd vector
//dest = src1 + k * src2
vms_vector *vm_vec_scale_add(vms_vector *dest,vms_vector *src1,vms_vector *src2,fix k);

//scales a vector and adds it to another
//dest += k * src
vms_vector *vm_vec_scale_add2(vms_vector *dest,vms_vector *src,fix k);

//scales a vector in place, taking n/d for scale.  returns ptr to vector
//dest *= n/d
vms_vector *vm_vec_scale2(vms_vector *dest,fix n,fix d);

//returns magnitude of a vector
fix vm_vec_mag(vms_vector *v);

//computes the distance between two points. (does sub and mag)
fix vm_vec_dist(vms_vector *v0,vms_vector *v1);

//computes an approximation of the magnitude of the vector
//uses dist = largest + next_largest*3/8 + smallest*3/16
fix vm_vec_mag_quick(vms_vector *v);

//computes an approximation of the distance between two points.
//uses dist = largest + next_largest*3/8 + smallest*3/16
fix vm_vec_dist_quick(vms_vector *v0,vms_vector *v1);


//normalize a vector. returns mag of source vec
fix vm_vec_copy_normalize(vms_vector *dest,vms_vector *src);
fix vm_vec_normalize(vms_vector *v);

//normalize a vector. returns mag of source vec. uses approx mag
fix vm_vec_copy_normalize_quick(vms_vector *dest,vms_vector *src);
fix vm_vec_normalize_quick(vms_vector *v);

//return the normalized direction vector between two points
//dest = normalized(end - start).  Returns mag of direction vector
//NOTE: the order of the parameters matches the vector subtraction
fix vm_vec_normalized_dir(vms_vector *dest,vms_vector *end,vms_vector *start);
fix vm_vec_normalized_dir_quick(vms_vector *dest,vms_vector *end,vms_vector *start);

////returns dot product of two vectors
fix vm_vec_dotprod(vms_vector *v0,vms_vector *v1);
#define vm_vec_dot(v0,v1) vm_vec_dotprod((v0),(v1))

#ifdef INLINE

#pragma aux vm_vec_dotprod parm [esi] [edi] value [eax] modify exact [eax ebx ecx edx] = \
	"mov	eax,[esi]"				\
	"imul	dword ptr [edi]"		\
	"mov	ebx,eax"					\
	"mov	ecx,edx"					\
										\
	"mov	eax,4[esi]"				\
	"imul	dword ptr 4[edi]"		\
	"add	ebx,eax"					\
	"adc	ecx,edx"					\
										\
	"mov	eax,8[esi]"				\
	"imul	dword ptr 8[edi]"		\
	"add	eax,ebx"					\
	"adc	edx,ecx"					\
										\
	"shrd	eax,edx,16";

#endif

//computes cross product of two vectors. returns ptr to dest
//dest CANNOT equal either source
vms_vector *vm_vec_crossprod(vms_vector *dest,vms_vector *src0,vms_vector *src1);
#define vm_vec_cross(dest,src0,src1) vm_vec_crossprod((dest),(src0),(src1))

//computes surface normal from three points. result is normalized
//returns ptr to dest
//dest CANNOT equal either source
vms_vector *vm_vec_normal(vms_vector *dest,vms_vector *p0,vms_vector *p1,vms_vector *p2);

//computes non-normalized surface normal from three points. 
//returns ptr to dest
//dest CANNOT equal either source
vms_vector *vm_vec_perp(vms_vector *dest,vms_vector *p0,vms_vector *p1,vms_vector *p2);

//computes the delta angle between two vectors. 
//vectors need not be normalized. if they are, call vm_vec_delta_ang_norm()
//the forward vector (third parameter) can be NULL, in which case the absolute
//value of the angle in returned.  Otherwise the angle around that vector is
//returned.
fixang vm_vec_delta_ang(vms_vector *v0,vms_vector *v1,vms_vector *fvec);

//computes the delta angle between two normalized vectors. 
fixang vm_vec_delta_ang_norm(vms_vector *v0,vms_vector *v1,vms_vector *fvec);

//computes a matrix from a set of three angles.  returns ptr to matrix
vms_matrix *vm_angles_2_matrix(vms_matrix *m,vms_angvec *a);

//computes a matrix from a forward vector and an angle
vms_matrix *vm_vec_ang_2_matrix(vms_matrix *m,vms_vector *v,fixang a);

//computes a matrix from one or more vectors. The forward vector is required,
//with the other two being optional.  If both up & right vectors are passed,
//the up vector is used.  If only the forward vector is passed, a bank of
//zero is assumed
//returns ptr to matrix
vms_matrix *vm_vector_2_matrix(vms_matrix *m,vms_vector *fvec,vms_vector *uvec,vms_vector *rvec);

//this version of vector_2_matrix requires that the vectors be more-or-less
//normalized and close to perpendicular
vms_matrix *vm_vector_2_matrix_norm(vms_matrix *m,vms_vector *fvec,vms_vector *uvec,vms_vector *rvec);

//rotates a vector through a matrix. returns ptr to dest vector
//dest CANNOT equal either source
vms_vector *vm_vec_rotate(vms_vector *dest,vms_vector *src,vms_matrix *m);

//transpose a matrix in place. returns ptr to matrix
vms_matrix *vm_transpose_matrix(vms_matrix *m);
#define vm_transpose(m) vm_transpose_matrix(m)

//copy and transpose a matrix. returns ptr to matrix
//dest CANNOT equal source. use vm_transpose_matrix() if this is the case
vms_matrix *vm_copy_transpose_matrix(vms_matrix *dest,vms_matrix *src);
#define vm_copy_transpose(dest,src) vm_copy_transpose_matrix((dest),(src))

//mulitply 2 matrices, fill in dest.  returns ptr to dest
//dest CANNOT equal either source
vms_matrix *vm_matrix_x_matrix(vms_matrix *dest,vms_matrix *src0,vms_matrix *src1);

//extract angles from a matrix 
vms_angvec *vm_extract_angles_matrix(vms_angvec *a,vms_matrix *m);

//extract heading and pitch from a vector, assuming bank==0
vms_angvec *vm_extract_angles_vector(vms_angvec *a,vms_vector *v);

//compute the distance from a point to a plane.  takes the normalized normal
//of the plane (ebx), a point on the plane (edi), and the point to check (esi).
//returns distance in eax
//distance is signed, so negative dist is on the back of the plane
fix vm_dist_to_plane(vms_vector *checkp,vms_vector *norm,vms_vector *planep);

#endif

