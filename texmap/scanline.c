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
 * $Source: Smoke:miner:source:texmap::RCS:scanline.c $
 * $Revision: 1.4 $
 * $Author: allender $
 * $Date: 1995/08/14 14:28:28 $
 * 
 * Routines to draw the texture mapped scanlines.
 * 
 * $Log: scanline.c $
 * Revision 1.4  1995/08/14  14:28:28  allender
 * changed transparency color to 0
 *
 * Revision 1.3  1995/07/05  16:22:47  allender
 * all asm verison when necessary
 *
 * Revision 1.2  1995/05/11  12:59:05  allender
 * mike subdivision, plus change transparency color
 *
 * Revision 1.1  1995/05/04  20:14:19  allender
 * Initial revision
 *
 * Revision 1.2  1995/02/20  18:23:39  john
 * Added new module for C versions of inner loops.
 * 
 * Revision 1.1  1995/02/20  17:42:27  john
 * Initial revision
 * 
 * 
 */


#pragma off (unreferenced)
static char rcsid[] = "$Id: scanline.c 1.4 1995/08/14 14:28:28 allender Exp $";
#pragma on (unreferenced)

#include <math.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

#include "fix.h"
#include "mono.h"
#include "gr.h"
#include "grdef.h"
#include "texmap.h"
#include "texmapl.h"
#include "scanline.h"

void c_tmap_scanline_flat()
{
	ubyte *dest;
	int x;

	dest = (ubyte *)(write_buffer + fx_xleft + (bytes_per_row * fx_y )  );

	for (x= fx_xright-fx_xleft+1 ; x > 0; --x ) {
		*dest++ = tmap_flat_color;
	}
}

void c_tmap_scanline_shaded()
{
	int fade;
	ubyte *dest;
	int x;

	dest = (ubyte *)(write_buffer + fx_xleft + (bytes_per_row * fx_y)  );

	fade = tmap_flat_shade_value<<8;
	for (x= fx_xright-fx_xleft+1 ; x > 0; --x ) {
		*dest++ = gr_fade_table[ fade |(*dest)];
	}
}

void c_tmap_scanline_lin_nolight()
{
	ubyte *dest;
	uint c;
	int x;
	fix u,v,dudx, dvdx;

	u = fx_u;
	v = fx_v*64;
	dudx = fx_du_dx; 
	dvdx = fx_dv_dx*64; 

	dest = (ubyte *)(write_buffer + fx_xleft + (bytes_per_row * fx_y)  );

	if (!Transparency_on)	{
		for (x= fx_xright-fx_xleft+1 ; x > 0; --x ) {
			*dest++ = (uint)pixptr[ (f2i(v)&(64*63)) + (f2i(u)&63) ];
			u += dudx;
			v += dvdx;
		}
	} else {
		for (x= fx_xright-fx_xleft+1 ; x > 0; --x ) {
			c = (uint)pixptr[ (f2i(v)&(64*63)) + (f2i(u)&63) ];
			if ( c!=TRANSPARENCY_COLOR)
				*dest = c;
			dest++;
			u += dudx;
			v += dvdx;
		}
	}
}


void c_tmap_scanline_lin()
{
	ubyte *dest;
	uint c;
	int x, j;
	fix u,v,l,dudx, dvdx, dldx;

	u = fx_u;
	v = fx_v*64;
	dudx = fx_du_dx; 
	dvdx = fx_dv_dx*64; 

	l = fx_l>>8;
	dldx = fx_dl_dx>>8;
	dest = (ubyte *)(write_buffer + fx_xleft + (bytes_per_row * fx_y)  );

#if 0
	if (!Transparency_on)	{
		for (x= fx_xright-fx_xleft+1 ; x > 0; --x ) {
			*dest++ = gr_fade_table[ (l&(0xff00)) + (uint)pixptr[ (f2i(v)&(64*63)) + (f2i(u)&63) ] ];
			l += dldx;
			u += dudx;
			v += dvdx;
		}
	} else {
		for (x= fx_xright-fx_xleft+1 ; x > 0; --x ) {
			c = (uint)pixptr[ (f2i(v)&(64*63)) + (f2i(u)&63) ];
			if ( c!=TRANSPARENCY_COLOR)
				*dest = gr_fade_table[ (l&(0xff00)) + c ];
			dest++;
			l += dldx;
			u += dudx;
			v += dvdx;
		}
	}
#else
	if (!Transparency_on)	{
		ubyte*			pixPtrLocalCopy = pixptr;
		ubyte*			fadeTableLocalCopy = gr_fade_table;
		unsigned long	destlong;

		x = fx_xright-fx_xleft+1;

		if ((j = (unsigned long) dest & 3) != 0)
			{
			j = 4 - j;

			if (j > x)
				j = x;

			while (j > 0)
				{	
				*dest++ = (unsigned long) fadeTableLocalCopy[ (l&(0xff00)) + (uint) pixPtrLocalCopy[ (f2i(v)&(64*63)) + (f2i(u)&63) ] ];
				l += dldx;
				u += dudx;
				v += dvdx;
				x--;
				j--;
				}
			}

		j &= ~3;
		while (j > 0)
			{
			destlong = (unsigned long) fadeTableLocalCopy[ (l&(0xff00)) + (uint) pixPtrLocalCopy[ (f2i(v)&(64*63)) + (f2i(u)&63) ] ] << 24;
			l += dldx;
			u += dudx;
			v += dvdx;
			destlong |= (unsigned long) fadeTableLocalCopy[ (l&(0xff00)) + (uint) pixPtrLocalCopy[ (f2i(v)&(64*63)) + (f2i(u)&63) ] ] << 16;
			l += dldx;
			u += dudx;
			v += dvdx;
			destlong |= (unsigned long) fadeTableLocalCopy[ (l&(0xff00)) + (uint) pixPtrLocalCopy[ (f2i(v)&(64*63)) + (f2i(u)&63) ] ] << 8;
			l += dldx;
			u += dudx;
			v += dvdx;
			destlong |= (unsigned long) fadeTableLocalCopy[ (l&(0xff00)) + (uint) pixPtrLocalCopy[ (f2i(v)&(64*63)) + (f2i(u)&63) ] ];
			l += dldx;
			u += dudx;
			v += dvdx;
			*((unsigned long *) dest) = destlong;
			dest += 4;
			x -= 4;
			j -= 4;
			}

		while (x-- > 0)
			{
			*dest++ = (unsigned long) fadeTableLocalCopy[ (l&(0xff00)) + (uint) pixPtrLocalCopy[ (f2i(v)&(64*63)) + (f2i(u)&63) ] ];
			l += dldx;
			u += dudx;
			v += dvdx;
			}

	} else {
		for (x= fx_xright-fx_xleft+1 ; x > 0; --x ) {
			c = (uint)pixptr[ (f2i(v)&(64*63)) + (f2i(u)&63) ];
			if ( c!=TRANSPARENCY_COLOR)
				*dest = gr_fade_table[ (l&(0xff00)) + c ];
			dest++;
			l += dldx;
			u += dudx;
			v += dvdx;
		}
	}
#endif
}


#define	MIN_SUBDIVIDABLE_LENGTH	4
#define	MAX_SUBDIVIDABLE_Z_RATIO (F1_0/4)

// -------------------------------------------------------------------------------------------------------------
//	Mike's subdividing scanline renderer.
void c_tmap_scanline_per_sub(int y, fix xleft, fix xright, fix uleft, fix uright, fix vleft, fix vright, fix zleft, fix zright, fix lleft, fix lright)
{
	int	dx = f2i(xright) - f2i(xleft);

	if (dx >= MIN_SUBDIVIDABLE_LENGTH) {
		int	subdivide = 0;

		if (zleft < zright) {
			if (zright - zleft < fixmul(MAX_SUBDIVIDABLE_Z_RATIO, zleft))
				subdivide = 1;
		} else if (zleft - zright < fixmul(MAX_SUBDIVIDABLE_Z_RATIO, zright))
			subdivide = 1;

		if (subdivide) {
			c_tmap_scanline_per_sub(y, xleft, (xright + xleft)/2, uleft, (uright + uleft)/2, vleft, (vright + vleft)/2, zleft, (zright + zleft)/2, lleft, (lright + lleft)/2);
			c_tmap_scanline_per_sub(y, (xright + xleft)/2, xright, (uright + uleft)/2, uright, (vright + vleft)/2, vright, (zright + zleft)/2, zright, (lright + lleft)/2, lright);
			return;
		}
	}


{
	ubyte *dest;
	uint c;
	int x;
	fix u,v,l,dudx, dvdx, dldx;

	u = fx_u;
	v = fx_v*64;
	dudx = fx_du_dx; 
	dvdx = fx_dv_dx*64; 

	l = fx_l>>8;
	dldx = fx_dl_dx>>8;
	dest = (ubyte *)(write_buffer + fx_xleft + (bytes_per_row * fx_y)  );

	if (!Transparency_on)	{
		for (x= fx_xright-fx_xleft+1 ; x > 0; --x ) {
			*dest++ = gr_fade_table[ (l&(0xff00)) + (uint)pixptr[ (f2i(v)&(64*63)) + (f2i(u)&63) ] ];
			l += dldx;
			u += dudx;
			v += dvdx;
		}
	} else {
		for (x= fx_xright-fx_xleft+1 ; x > 0; --x ) {
			c = (uint)pixptr[ (f2i(v)&(64*63)) + (f2i(u)&63) ];
			if ( c!=TRANSPARENCY_COLOR)
				*dest = gr_fade_table[ (l&(0xff00)) + c ];
			dest++;
			l += dldx;
			u += dudx;
			v += dvdx;
		}
	}
}

}

void c_tmap_scanline_per_nolight()
{
	ubyte *dest;
	uint c;
	int x;
	fix u,v,z,dudx, dvdx, dzdx;

	u = fx_u;
	v = fx_v*64;
	z = fx_z;
	dudx = fx_du_dx; 
	dvdx = fx_dv_dx*64; 
	dzdx = fx_dz_dx;

	dest = (ubyte *)(write_buffer + fx_xleft + (bytes_per_row * fx_y)  );

	if (!Transparency_on)	{
		for (x= fx_xright-fx_xleft+1 ; x > 0; --x ) {
			*dest++ = (uint)pixptr[ ( (v/z)&(64*63) ) + ((u/z)&63) ];
			u += dudx;
			v += dvdx;
			z += dzdx;
		}
	} else {
		for (x= fx_xright-fx_xleft+1 ; x > 0; --x ) {
			c = (uint)pixptr[ ( (v/z)&(64*63) ) + ((u/z)&63) ];
			if ( c!=TRANSPARENCY_COLOR)
				*dest = c;
			dest++;
			u += dudx;
			v += dvdx;
			z += dzdx;
		}
	}
}

void c_tmap_scanline_per()
{
	ubyte *dest;
	uint c;
	int x;
	fix u,v,z,l,dudx, dvdx, dzdx, dldx;

	u = fx_u;
	v = fx_v*64;
	z = fx_z;
	dudx = fx_du_dx; 
	dvdx = fx_dv_dx*64; 
	dzdx = fx_dz_dx;

	l = fx_l>>8;
	dldx = fx_dl_dx>>8;
	dest = (ubyte *)(write_buffer + fx_xleft + (bytes_per_row * fx_y)  );

	if (!Transparency_on)	{
		for (x= fx_xright-fx_xleft+1 ; x > 0; --x ) {
			*dest++ = gr_fade_table[ (l&(0xff00)) + (uint)pixptr[ ( (v/z)&(64*63) ) + ((u/z)&63) ] ];
			l += dldx;
			u += dudx;
			v += dvdx;
			z += dzdx;
		}
	} else {
		for (x= fx_xright-fx_xleft+1 ; x > 0; --x ) {
			c = (uint)pixptr[ ( (v/z)&(64*63) ) + ((u/z)&63) ];
			if ( c!=TRANSPARENCY_COLOR)
				*dest = gr_fade_table[ (l&(0xff00)) + c ];
			dest++;
			l += dldx;
			u += dudx;
			v += dvdx;
			z += dzdx;
		}
	}
}


