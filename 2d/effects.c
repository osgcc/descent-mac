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
 * $Source: Smoke:miner:source:2d::RCS:effects.c $
 * $Revision: 1.1 $
 * $Author: allender $
 * $Date: 1995/03/09 08:53:09 $
 * 
 * special effects stuff
 * 
 * $Log: effects.c $
 * Revision 1.1  1995/03/09  08:53:09  allender
 * Initial revision
 *
 *
 * --- PC RCS information ---
 * Revision 1.2  1993/10/26  13:18:15  john
 * *** empty log message ***
 * 
 * Revision 1.1  1993/10/25  14:56:56  john
 * Initial revision
 * 
 * 
 */


#pragma off (unreferenced)
static char rcsid[] = "$Id: effects.c 1.1 1995/03/09 08:53:09 allender Exp $";
#pragma on (unreferenced)

#include <stdlib.h>
#include <stdio.h>

#include "effects.h"

#include "mem.h"
#include "gr.h"
#include "grdef.h"
#include "bm.h"

int bitwidth(unsigned int n)
{
	int width = 0;

	while ( n!=0 )  {
		n >>= 1;
		width++;
	}
	return width;
}

long randmasks[] = { 0,0,0x03,0x06,0x0c,0x14,0x30,0x60,0xb8,\
0x110,0x240,0x500,0xca0,0x1b00,0x3500,0x6000,0xb400,\
0x12000,0x204000,0x720000,0x90000,0x140000,0x300000,0x400000,\
0xd80000,0x1200000,0x3880000,0x7200000,0x9000000,0x14000000,\
0x32800000,0x48000000,0xa3000000 };

void dissolve_in(grs_bitmap * bitmap )
{
	int height, width, zz;
	int rwidth, cwidth;     /* bit width for rows, for columns */
	int regwidth;           /* "width" of sequence generator */
	long mask;     /* mask to XOR with to create sequence */
	int rowshift;  /* shift distance to get row  */
													/* from element */
	int colmask; /* mask to extract column from element */
	unsigned long element; /* one element of random */                                                                 /* sequence */
	int row, column;    /* row and column for one pixel */

	/* Find the mask to produce all rows and columns. */
	height = bitmap->bm_h;
	width = bitmap->bm_w;

	rwidth = bitwidth (height); /* how many bits needed for height? */
	cwidth = bitwidth (width);  /* how many bits needed for width? */
	regwidth = rwidth + cwidth; /* how wide must the register be? */
	mask = randmasks[regwidth]; /* which mask is for that width? */

	/* Find values to extract row and col numbers from each element. */
	rowshift = cwidth; /* find dist to shift to get top bits (row) */
	colmask = (1<<cwidth)-1;        /* find mask to extract  */
												/* bottom bits (col) */

	/* Now cycle through all sequence elements. */

	element = 1;    /* 1st element (could be any nonzero) */
	do {
		for (zz=0; zz < 100; zz++);
		row = element >> rowshift; /* find row number for this pixel */
		column = element & colmask; /* and how many columns across? */
		/* does element fall in the array? */
		/* ...must check row AND column */

		if ((row < height) && (column < width)) {
			// Draw the (r,c)'th pixel
			gr_setcolor(gr_ugpixel( bitmap, column, row ));
			gr_upixel(column, row);
		}

		/* Compute the next sequence element */
		if (element & 1)                /* is the low bit set? */
			element = (element >>1)^mask; /* yes: shift value, */
		else
			element = (element >>1); /* no: just shift the value */
	} while (element != 1);         /* loop until we return to */
									/*  original element */

	gr_setcolor(gr_ugpixel( bitmap, 0, 0 ));
	gr_upixel(0,0);

}

void gr_snow_out(int num_dots)
{
	int num_done;
	int height, width;
	int rwidth, cwidth;     /* bit width for rows, for columns */
	int regwidth;           /* "width" of sequence generator */
	long mask;     /* mask to XOR with to create sequence */
	int rowshift;  /* shift distance to get row  */
													/* from element */
	int colmask; /* mask to extract column from element */
	unsigned long element; /* one element of random */                                                                 /* sequence */
	int row, column;    /* row and column for one pixel */

	/* Find the mask to produce all rows and columns. */
	height = grd_curcanv->cv_bitmap.bm_h;
	width = grd_curcanv->cv_bitmap.bm_w;

	rwidth = bitwidth (height); /* how many bits needed for height? */
	cwidth = bitwidth (width);  /* how many bits needed for width? */
	regwidth = rwidth + cwidth; /* how wide must the register be? */
	mask = randmasks[regwidth]; /* which mask is for that width? */

	/* Find values to extract row and col numbers from each element. */
	rowshift = cwidth; /* find dist to shift to get top bits (row) */
	colmask = (1<<cwidth)-1;        /* find mask to extract  */
									/* bottom bits (col) */

	/* Now cycle through all sequence elements. */

	element = 1;    /* 1st element (could be any nonzero) */

	num_done = 0;

	do {
		row = element >> rowshift; /* find row number for this pixel */
		column = element & colmask; /* and how many columns across? */
		/* does element fall in the array? */
		/* ...must check row AND column */

		if ((row < height) && (column < width)) {
			// Draw the (r,c)'th pixel
			gr_upixel(column, row);
		}

		/* Compute the next sequence element */
		if (element & 1)                /* is the low bit set? */
			element = (element >>1)^mask; /* yes: shift value, */
		else
			element = (element >>1); /* no: just shift the value */
	} while ((element != 1)  && (num_done++ < num_dots) );         /* loop until we return to */
									/*  original element */
	gr_upixel(0,0);

}


// Fade = 0: blacken,  15:no change.

void gr_fade_canvas(int fade)
{
	int height, width;
	int x, y, pixel;
	
	height = grd_curcanv->cv_bitmap.bm_h;
	width = grd_curcanv->cv_bitmap.bm_w;

	fade = (15-fade)*256;
						
	for (y=0; y<height; y++ )
		for (x=0; x<width; x++ )
		{
			pixel = gr_ugpixel( &grd_curcanv->cv_bitmap, x, y );
			gr_setcolor(bmd_fade_table[ pixel + fade ] );
			gr_upixel( x, y );
		}
}

void gr_deaccent_canvas()
{
	int height, width;
	int x, y, pixel;
	
	height = grd_curcanv->cv_bitmap.bm_h;
	width = grd_curcanv->cv_bitmap.bm_w;

	for (y=0; y<height; y++ )
		for (x=0; x<width; x++ )
		{
			if ( (x+y) & 1 )
				gr_upixel( x, y );
		}
}

static char ygrey[800];

void gr_grey_canvas()
{
	int height, width;
	int x, y, pixel;
	int r,g,b, grey, lastgrey, diff;
	grs_bitmap * bm;
	unsigned int offset;

	bm = &grd_curcanv->cv_bitmap;
	height = grd_curcanv->cv_bitmap.bm_h;
	width = grd_curcanv->cv_bitmap.bm_w;

	for (x=0; x<width; x++ )
		ygrey[x] = 16;

	offset = (unsigned int)bm->bm_data;

	for (y=0; y<height; y++ )
	{
		for (x=0; x<width; x++ )
		{
			gr_vesa_setpage( offset >> 16 );

			pixel = gr_video_memory[offset & 0xFFFF];

			r = grd_curscreen->pal[pixel*3+0];
			g = grd_curscreen->pal[pixel*3+1];
			b = grd_curscreen->pal[pixel*3+2];

			lastgrey = grey;
			grey = (r+g+b)/6;

			diff = (grey-lastgrey) + (grey-ygrey[x]) + 16;
			ygrey[x] = grey;

			if (diff<0) diff=0;
			if (diff>31) diff=31;

			gr_video_memory[offset & 0xFFFF] = bmd_inverse_table[ (diff<<10) | (diff<<5) | (diff) ];
			offset++;
		}
		offset += bm->bm_rowsize - width;
	}
}
