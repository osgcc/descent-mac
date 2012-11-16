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
 * $Source: Smoke:miner:source:main::RCS:polyobj.c $
 * $Revision: 1.3 $
 * $Author: allender $
 * $Date: 1995/10/25 14:07:07 $
 * 
 * Hacked-in polygon objects
 * 
 * $Log: polyobj.c $
 * Revision 1.3  1995/10/25  14:07:07  allender
 * removed load_poly_model function
 *
 * Revision 1.2  1995/09/14  14:10:20  allender
 * two funtions should be void
 *
 * Revision 1.1  1995/05/16  15:30:08  allender
 * Initial revision
 *
 * Revision 2.0  1995/02/27  11:32:44  john
 * New version 2.0, which has no anonymous unions, builds with
 * Watcom 10.0, and doesn't require parsing BITMAPS.TBL.
 * 
 * Revision 1.64  1995/01/14  19:16:43  john
 * First version of new bitmap paging code.
 * 
 * Revision 1.63  1994/12/14  18:06:54  matt
 * Removed compile warnings
 * 
 * Revision 1.62  1994/12/09  17:54:31  john
 * Made the CFILE's close right after reading in data.
 * 
 * Revision 1.61  1994/12/09  16:13:28  mike
 * speedup pof file reading, but still horribly slow using hog file...problem somewhere else.
 * 
 * Revision 1.60  1994/12/08  17:41:20  yuan
 * Cfiling stuff.
 * 
 * Revision 1.59  1994/11/21  11:02:19  matt
 * Added error checking
 * 
 * Revision 1.58  1994/11/14  11:32:49  matt
 * Allow switching to simpler models even when alt_textures specified
 * 
 * Revision 1.57  1994/11/13  21:15:24  matt
 * Added basic support for more than one level of detail simplification
 * 
 * Revision 1.56  1994/11/11  19:29:25  matt
 * Added code to show low detail polygon models
 * 
 * Revision 1.55  1994/11/10  14:02:57  matt
 * Hacked in support for player ships with different textures
 * 
 * Revision 1.54  1994/11/03  11:01:59  matt
 * Made robot pics lighted
 * 
 * Revision 1.53  1994/11/02  16:18:34  matt
 * Moved draw_model_picture() out of editor
 * 
 * Revision 1.52  1994/10/18  14:38:11  matt
 * Restored assert now that bug is fixed
 * 
 * Revision 1.51  1994/10/17  21:35:03  matt
 * Added support for new Control Center/Main Reactor
 * 
 * Revision 1.50  1994/10/14  17:46:23  yuan
 * Made the soft Int3 only work in net mode.
 * 
 * Revision 1.49  1994/10/14  17:43:47  yuan
 * Added soft int3's instead of Asserts  for some common network bugs.
 * 
 * Revision 1.48  1994/10/14  17:09:04  yuan
 * Made Assert on line 610 be if in an attempt
 * to bypass.
 * 
 * Revision 1.47  1994/09/09  14:23:42  matt
 * Added glow code to polygon models for engine glow
 * 
 * Revision 1.46  1994/08/26  18:03:30  matt
 * Added code to remap polygon model numbers by matching filenames
 * 
 * Revision 1.45  1994/08/26  15:35:58  matt
 * Made eclips usable on more than one object at a time
 * 
 * Revision 1.44  1994/08/25  18:11:58  matt
 * Made player's weapons and flares fire from the positions on the 3d model.
 * Also added support for quad lasers.
 * 
 * Revision 1.43  1994/07/25  00:14:18  matt
 * Made a couple of minor changes for the drivethrough
 * 
 * Revision 1.42  1994/07/25  00:02:41  matt
 * Various changes to accomodate new 3d, which no longer takes point numbers
 * as parms, and now only takes pointers to points.
 * 
 */


#pragma off (unreferenced)
static char rcsid[] = "$Id: polyobj.c 1.3 1995/10/25 14:07:07 allender Exp $";
#pragma on (unreferenced)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Memory.h>

#ifdef DRIVE
#include "drive.h"
#else
#include "inferno.h"
#endif

#include "polyobj.h"

#include "vecmat.h"
#include "3d.h"
#include "error.h"
#include "mono.h"
#include "mem.h"

#ifndef DRIVE
#include "texmap.h"
#include "bm.h"
#include "textures.h"
#include "object.h"
#include "lighting.h"
#include "cfile.h"
#include "piggy.h"
#endif

//polymodel Polygon_models[MAX_POLYGON_MODELS];	// = {&bot11,&bot17,&robot_s2,&robot_b2,&bot11,&bot17,&robot_s2,&robot_b2};
polymodel *Polygon_models;

int N_polygon_models = 0;

#define MAX_POLYGON_VECS 1000
g3s_point *robot_points;

#define PM_COMPATIBLE_VERSION 6
#define PM_OBJFILE_VERSION 7

int	Pof_file_end;
int	Pof_addr;

#define	MODEL_BUF_SIZE	32768

void _pof_cfseek(int len,int type)
{
	switch (type) {
		case SEEK_SET:	Pof_addr = len;	break;
		case SEEK_CUR:	Pof_addr += len;	break;
		case SEEK_END:
			Assert(len <= 0);	//	seeking from end, better be moving back.
			Pof_addr = Pof_file_end + len;
			break;
	}

	if (Pof_addr > MODEL_BUF_SIZE)
		Int3();
}

#define pof_cfseek(_buf,_len,_type) _pof_cfseek((_len),(_type))

int pof_read_int(ubyte *bufp)
{
	int i;

	i = *((int *) &bufp[Pof_addr]);
	Pof_addr += 4;
	return i;

}

size_t pof_cfread(void *dst, size_t elsize, size_t nelem, ubyte *bufp)
{
	if (Pof_addr + nelem*elsize > Pof_file_end)
		return 0;

	memcpy(dst, &bufp[Pof_addr], elsize*nelem);

	Pof_addr += elsize*nelem;

	if (Pof_addr > MODEL_BUF_SIZE)
		Int3();

	return nelem;
}

// #define new_read_int(i,f) cfread(&(i),sizeof(i),1,(f))
#define new_pof_read_int(i,f) pof_cfread(&(i),sizeof(i),1,(f))

short pof_read_short(ubyte *bufp)
{
	short s;

	s = *((short *) &bufp[Pof_addr]);
	Pof_addr += 2;
	return s;
}

pof_read_string(char *buf,int max, ubyte *bufp)
{
	int	i;

	for (i=0; i<max; i++) {
		if ((*buf++ = bufp[Pof_addr++]) == 0)
			break;
	}

//	while (max-- && (*buf=cfgetc(f)) != 0) buf++;

}

pof_read_vecs(vms_vector *vecs,int n,ubyte *bufp)
{

	memcpy(vecs, &bufp[Pof_addr], n*sizeof(*vecs));
	Pof_addr += n*sizeof(*vecs);
	
	if (Pof_addr > MODEL_BUF_SIZE)
		Int3();
}

#define ID_OHDR 'RDHO'	//Object header
#define ID_SOBJ 'JBOS'	//Subobject header
#define ID_GUNS 'SNUG'	//List of guns on this object
#define ID_ANIM 'MINA'	//Animation data
#define ID_IDTA 'ATDI'	//Interpreter data
#define ID_TXTR 'RTXT'	//Texture filename list

#ifdef DRIVE
#define robot_info void
#else
vms_angvec anim_angs[N_ANIM_STATES][MAX_SUBMODELS];

//set the animation angles for this robot.  Gun fields of robot info must
//be filled in.
robot_set_angles(robot_info *r,polymodel *pm,vms_angvec angs[N_ANIM_STATES][MAX_SUBMODELS]);
#endif

#if 0
//reads a binary file containing a 3d model
polymodel *read_model_file(polymodel *pm,char *filename,robot_info *r)
{
	CFILE *ifile;
	short version;
	int id,len;
	ubyte	model_buf[MODEL_BUF_SIZE];
	if ((ifile=cfopen(filename,"rb"))==NULL) 
		Error("Can't open file <%s>",filename);

	Assert(ifile->size <= MODEL_BUF_SIZE);

	Pof_addr = 0;
	Pof_file_end = cfread(model_buf, 1, cfilelength(ifile), ifile);
	cfclose(ifile);

	id = pof_read_int(model_buf);

	if (id!='OPSP')
		Error("Bad ID in model file <%s>",filename);

	version = pof_read_short(model_buf);
	
	if (version < PM_COMPATIBLE_VERSION || version > PM_OBJFILE_VERSION)
		Error("Bad version (%d) in model file <%s>",version,filename);

	while (new_pof_read_int(id,model_buf) == 1) {

		//id  = pof_read_int(model_buf);
		len = pof_read_int(model_buf);

		switch (id) {

			case ID_OHDR: {		//Object header
				vms_vector pmmin,pmmax;

				//mprintf(0,"Got chunk OHDR, len=%d\n",len);

				pm->n_models = pof_read_int(model_buf);
				pm->rad = pof_read_int(model_buf);

				Assert(pm->n_models <= MAX_SUBMODELS);

				pof_read_vecs(&pmmin,1,model_buf);
				pof_read_vecs(&pmmax,1,model_buf);

				break;
			}
			
			case ID_SOBJ: {		//Subobject header
				int n;

				//mprintf(0,"Got chunk SOBJ, len=%d\n",len);

				n = pof_read_short(model_buf);

				Assert(n < MAX_SUBMODELS);

				pm->submodel_parents[n] = pof_read_short(model_buf);

				pof_read_vecs(&pm->submodel_norms[n],1,model_buf);
				pof_read_vecs(&pm->submodel_pnts[n],1,model_buf);
				pof_read_vecs(&pm->submodel_offsets[n],1,model_buf);

				pm->submodel_rads[n] = pof_read_int(model_buf);		//radius

				pm->submodel_ptrs[n] = pof_read_int(model_buf);	//offset

				break;

			}
			
			#ifndef DRIVE
			case ID_GUNS: {		//List of guns on this object

				//mprintf(0,"Got chunk GUNS, len=%d\n",len);

				if (r) {
					int i;
					vms_vector gun_dir;

					r->n_guns = pof_read_int(model_buf);

					Assert(r->n_guns <= MAX_GUNS);

					for (i=0;i<r->n_guns;i++) {
						int id;

						id = pof_read_short(model_buf);
						r->gun_submodels[id] = pof_read_short(model_buf);
						Assert(r->gun_submodels[id] != 0xff);
						pof_read_vecs(&r->gun_points[id],1,model_buf);

						if (version >= 7)
							pof_read_vecs(&gun_dir,1,model_buf);
					}
				}
				else
					pof_cfseek(model_buf,len,SEEK_CUR);

				break;
			}
			
			case ID_ANIM:		//Animation data
				//mprintf(0,"Got chunk ANIM, len=%d\n",len);

				if (r) {
					int n_frames,f,m;

					n_frames = pof_read_short(model_buf);

					Assert(n_frames == N_ANIM_STATES);

					for (m=0;m<pm->n_models;m++)
						for (f=0;f<n_frames;f++)
							pof_cfread(&anim_angs[f][m],1,sizeof(vms_angvec),model_buf);

					robot_set_angles(r,pm,anim_angs);
				
				}
				else
					pof_cfseek(model_buf,len,SEEK_CUR);

				break;
			#endif
			
			case ID_TXTR: {		//Texture filename list
				int n;
				char name_buf[128];

				//mprintf(0,"Got chunk TXTR, len=%d\n",len);

				n = pof_read_short(model_buf);
				//mprintf(0,"  num textures = %d\n",n);
				while (n--) {
					pof_read_string(name_buf,128,model_buf);
					//mprintf(0,"<%s>\n",name_buf);
				}

				break;
			}
			
			case ID_IDTA:		//Interpreter data
				//mprintf(0,"Got chunk IDTA, len=%d\n",len);

				pm->model_data = mymalloc(len);
				pm->model_data_size = len;
			
				pof_cfread(pm->model_data,1,len,model_buf);
			
				break;

			default:
				//mprintf(0,"Unknown chunk <%c%c%c%c>, len = %d\n",id,id>>8,id>>16,id>>24,len);
				pof_cfseek(model_buf,len,SEEK_CUR);
				break;

		}



	}

//	for (i=0;i<pm->n_models;i++)
//		pm->submodel_ptrs[i] += (int) pm->model_data;

	return pm;
}
#endif

#if 0
//reads the gun information for a model
//fills in arrays gun_points & gun_dirs, returns the number of guns read
int read_model_guns(char *filename,vms_vector *gun_points, vms_vector *gun_dirs, int *gun_submodels)
{
	CFILE *ifile;
	short version;
	int id,len;
	int n_guns=0;
	ubyte	model_buf[MODEL_BUF_SIZE];

	if ((ifile=cfopen(filename,"rb"))==NULL) 
		Error("Can't open file <%s>",filename);

	Assert(ifile->size <= MODEL_BUF_SIZE);

	Pof_addr = 0;
	Pof_file_end = cfread(model_buf, 1, ifile->size, ifile);
	cfclose(ifile);

	id = pof_read_int(model_buf);

	if (id!='OPSP')
		Error("Bad ID in model file <%s>",filename);

	version = pof_read_short(model_buf);
	
	Assert(version >= 7);		//must be 7 or higher for this data

	if (version < PM_COMPATIBLE_VERSION || version > PM_OBJFILE_VERSION)
		Error("Bad version (%d) in model file <%s>",version,filename);

	while (new_pof_read_int(id,model_buf) == 1) {

		//id  = pof_read_int(model_buf);
		len = pof_read_int(model_buf);

		if (id == ID_GUNS) {		//List of guns on this object

			//mprintf(0,"Got chunk GUNS, len=%d\n",len);

			int i;

			n_guns = pof_read_int(model_buf);

			for (i=0;i<n_guns;i++) {
				int id,sm;

				id = pof_read_short(model_buf);
				sm = pof_read_short(model_buf);
				if (gun_submodels)
					gun_submodels[id] = sm;
				else if (sm!=0)
					Error("Invalid gun submodel in file <%s>",filename);
				pof_read_vecs(&gun_points[id],1,model_buf);

				pof_read_vecs(&gun_dirs[id],1,model_buf);
			}

		}
		else
			pof_cfseek(model_buf,len,SEEK_CUR);

	}

	return n_guns;
}
#endif

//free up a model, getting rid of all its memory
free_model(polymodel *po)
{
	myfree(po->model_data);
}

grs_bitmap *texture_list[MAX_POLYOBJ_TEXTURES];
bitmap_index texture_list_index[MAX_POLYOBJ_TEXTURES];

int Simple_model_threshhold_scale=5;		//switch when this times radius far away


//draw a polygon model

void draw_polygon_model(vms_vector *pos,vms_matrix *orient,vms_angvec *anim_angles,int model_num,int flags,fix light,fix *glow_values,bitmap_index alt_textures[])
{
	polymodel *po;
	int i;

	Assert(model_num < N_polygon_models);

	po=&Polygon_models[model_num];

	//check if should use simple model
	if (po->simpler_model )					//must have a simpler model
		if (flags==0)							//can't switch if this is debris
			//!!if (!alt_textures) {				//alternate textures might not match
			//alt textures might not match, but in the one case we're using this
			//for on 11/14/94, they do match.  So we leave it in.
			{
				int cnt=1;
				fix depth;
	
				depth = g3_calc_point_depth(pos);		//gets 3d depth

				while (po->simpler_model && depth > cnt++ * Simple_model_threshhold_scale * po->rad)
					po = &Polygon_models[po->simpler_model-1];
			}

	if (alt_textures)
		for (i=0;i<po->n_textures;i++)	{
			texture_list_index[i] = alt_textures[i];
			texture_list[i] = &GameBitmaps[alt_textures[i].index];
		}
	else
		for (i=0;i<po->n_textures;i++)	{
			texture_list_index[i] = ObjBitmaps[ObjBitmapPtrs[po->first_texture+i]];
			texture_list[i] = &GameBitmaps[ObjBitmaps[ObjBitmapPtrs[po->first_texture+i]].index];
		}

#ifdef PIGGY_USE_PAGING
	// Make sure the textures for this object are paged in...
	piggy_page_flushed = 0;
	for (i=0;i<po->n_textures;i++)	
		PIGGY_PAGE_IN( texture_list_index[i] );
	// Hmmm... cache got flushed in the middle of paging all these in,
	// so we need to reread them all in.
	if (piggy_page_flushed)	{
		piggy_page_flushed = 0;
		for (i=0;i<po->n_textures;i++)	
			PIGGY_PAGE_IN( texture_list_index[i] );
	}
	// Make sure that they can all fit in memory.
	Assert( piggy_page_flushed == 0 );
#endif

	g3_start_instance_matrix(pos,orient);

	g3_set_interp_points(robot_points);

	if (flags == 0)		//draw entire object

		g3_draw_polygon_model(po->model_data,texture_list,anim_angles,light,glow_values);

	else {
		int i;
	
		for (i=0;flags;flags>>=1,i++)
			if (flags & 1) {
				vms_vector ofs;

				Assert(i < po->n_models);

				//if submodel, rotate around its center point, not pivot point
	
				vm_vec_avg(&ofs,&po->submodel_mins[i],&po->submodel_maxs[i]);
				vm_vec_negate(&ofs);
				g3_start_instance_matrix(&ofs,NULL);
	
				g3_draw_polygon_model(&po->model_data[po->submodel_ptrs[i]],texture_list,anim_angles,light,glow_values);
	
				g3_done_instance();
			}	
	}

	g3_done_instance();

}

void free_polygon_models()
{
	int i;

	for (i=0;i<N_polygon_models;i++) {
		free_model(&Polygon_models[i]);
	}

}

polyobj_find_min_max(polymodel *pm)
{
	ushort nverts;
	vms_vector *vp;
	ushort *data,type;
	int m;
	vms_vector *big_mn,*big_mx;
	
	big_mn = &pm->mins;
	big_mx = &pm->maxs;

	for (m=0;m<pm->n_models;m++) {
		vms_vector *mn,*mx,*ofs;

		mn = &pm->submodel_mins[m];
		mx = &pm->submodel_maxs[m];
		ofs= &pm->submodel_offsets[m];

		data = (ushort *)&pm->model_data[pm->submodel_ptrs[m]];
	
		type = *data++;
	
		Assert(type == 7 || type == 1);
	
		nverts = *data++;
	
		if (type==7)
			data+=2;		//skip start & pad
	
		vp = (vms_vector *) data;
	
		*mn = *mx = *vp++; nverts--;

		if (m==0)
			*big_mn = *big_mx = *mn;
	
		while (nverts--) {
			if (vp->x > mx->x) mx->x = vp->x;
			if (vp->y > mx->y) mx->y = vp->y;
			if (vp->z > mx->z) mx->z = vp->z;
	
			if (vp->x < mn->x) mn->x = vp->x;
			if (vp->y < mn->y) mn->y = vp->y;
			if (vp->z < mn->z) mn->z = vp->z;
	
			if (vp->x+ofs->x > big_mx->x) big_mx->x = vp->x+ofs->x;
			if (vp->y+ofs->y > big_mx->y) big_mx->y = vp->y+ofs->y;
			if (vp->z+ofs->z > big_mx->z) big_mx->z = vp->z+ofs->z;
	
			if (vp->x+ofs->x < big_mn->x) big_mn->x = vp->x+ofs->x;
			if (vp->y+ofs->y < big_mn->y) big_mn->y = vp->y+ofs->y;
			if (vp->z+ofs->z < big_mn->z) big_mn->z = vp->z+ofs->z;
	
			vp++;
		}

//		printf("Submodel %d:  (%8x,%8x) (%8x,%8x) (%8x,%8x)\n",m,mn->x,mx->x,mn->y,mx->y,mn->z,mx->z);
	}

//	printf("Whole model: (%8x,%8x) (%8x,%8x) (%8x,%8x)\n",big_mn->x,big_mx->x,big_mn->y,big_mx->y,big_mn->z,big_mx->z);

}

extern short highest_texture_num;	//from the 3d

char Pof_names[MAX_POLYGON_MODELS][13];

#if 0
//returns the number of this model
#ifndef DRIVE
int load_polygon_model(char *filename,int n_textures,int first_texture,robot_info *r)
#else
int load_polygon_model(char *filename,int n_textures,grs_bitmap ***textures)
#endif
{
	#ifdef DRIVE
	#define r NULL
	#endif

	Assert(N_polygon_models < MAX_POLYGON_MODELS);
	Assert(n_textures < MAX_POLYOBJ_TEXTURES);

	mprintf(( 0, "Used %d/%d polygon model slots\n", N_polygon_models+1, MAX_POLYGON_MODELS ));

	Assert(strlen(filename) <= 12);
	strcpy(Pof_names[N_polygon_models],filename);

	read_model_file(&Polygon_models[N_polygon_models],filename,r);

	polyobj_find_min_max(&Polygon_models[N_polygon_models]);

	g3_init_polygon_model(Polygon_models[N_polygon_models].model_data);

	if (highest_texture_num+1 != n_textures)
		Error("Model <%s> references %d textures but specifies %d.",filename,highest_texture_num+1,n_textures);

	Polygon_models[N_polygon_models].n_textures = n_textures;
	Polygon_models[N_polygon_models].first_texture = first_texture;
	Polygon_models[N_polygon_models].simpler_model = 0;

//	Assert(polygon_models[N_polygon_models]!=NULL);

	N_polygon_models++;

	return N_polygon_models-1;

}
#endif


void init_polygon_models()
{
	N_polygon_models = 0;

	Polygon_models = NULL;
	atexit(free_polygon_models);

}

//compare against this size when figuring how far to place eye for picture
#define BASE_MODEL_SIZE 0x28000

#define DEFAULT_VIEW_DIST 0x60000

//draws the given model in the current canvas.  The distance is set to
//more-or-less fill the canvas.  Note that this routine actually renders
//into an off-screen canvas that it creates, then copies to the current
//canvas.
void draw_model_picture(int mn,vms_angvec *orient_angles)
{
	vms_vector	temp_pos=ZERO_VECTOR;
	vms_matrix	temp_orient = IDENTITY_MATRIX;
	grs_canvas	*save_canv = grd_curcanv,*temp_canv;
	//int			save_light;

	Assert(mn>=0 && mn<N_polygon_models);

	temp_canv = gr_create_canvas(save_canv->cv_bitmap.bm_w,save_canv->cv_bitmap.bm_h);
	gr_set_current_canvas(temp_canv);
	gr_clear_canvas( BM_XRGB(0,0,0) );

	g3_start_frame();
	g3_set_view_matrix(&temp_pos,&temp_orient,0x9000);

	if (Polygon_models[mn].rad != 0)
		temp_pos.z = fixmuldiv(DEFAULT_VIEW_DIST,Polygon_models[mn].rad,BASE_MODEL_SIZE);
	else
		temp_pos.z = DEFAULT_VIEW_DIST;

	vm_angles_2_matrix(&temp_orient, orient_angles);

	//save_light = Lighting_on;
	//Lighting_on = 0;
	draw_polygon_model(&temp_pos,&temp_orient,NULL,mn,0,f1_0,NULL,NULL);
	//Lighting_on = save_light;

	gr_set_current_canvas(save_canv);

	gr_bitmap(0,0,&temp_canv->cv_bitmap);

	gr_free_canvas(temp_canv);
}

