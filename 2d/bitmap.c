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
 * $Source: Smoke:miner:source:2d::RCS:bitmap.c $
 * $Revision: 1.11 $
 * $Author: allender $
 * $Date: 1995/08/23 18:46:06 $
 *
 * Graphical routines for manipulating grs_bitmaps.
 *
 * $Log: bitmap.c $
 * Revision 1.11  1995/08/23  18:46:06  allender
 * fixed compiler warning
 *
 * Revision 1.10  1995/08/14  14:25:45  allender
 * changed transparency color to 0
 *
 * Revision 1.9  1995/07/05  16:04:51  allender
 * transparency/game kitchen changes
 *
 * Revision 1.8  1995/06/15  09:50:48  allender
 * new malloc to align bitmap on 8 byte bountry
 *
 * Revision 1.7  1995/05/12  11:52:19  allender
 * changed memory stuff again
 *
 * Revision 1.6  1995/05/11  12:48:34  allender
 * nge transparency color
 *
 * Revision 1.5  1995/05/04  19:59:21  allender
 * use NewPtr instead of malloc
 *
 * Revision 1.4  1995/04/27  07:33:04  allender
 * rearrange functions
 *
 * Revision 1.3  1995/04/19  14:37:17  allender
 * removed dead asm code
 *
 * Revision 1.2  1995/04/18  12:04:51  allender
 * *** empty log message ***
 *
 * Revision 1.1  1995/03/09  08:48:06  allender
 * Initial revision
 *
 *
 * -------  PC version RCS information
 * Revision 1.17  1994/11/18  22:50:25  john
 * Changed shorts to ints in parameters.
 * 
 * Revision 1.16  1994/11/10  15:59:46  john
 * Fixed bugs with canvas's being created with bogus bm_flags.
 * 
 * Revision 1.15  1994/10/26  23:55:53  john
 * Took out roller; Took out inverse table.
 * 
 * Revision 1.14  1994/09/19  14:40:21  john
 * Changed dpmi stuff.
 * 
 * Revision 1.13  1994/09/19  11:44:04  john
 * Changed call to allocate selector to the dpmi module.
 * 
 * Revision 1.12  1994/06/09  13:14:57  john
 * Made selectors zero our
 * out, I meant.
 * 
 * Revision 1.11  1994/05/06  12:50:07  john
 * Added supertransparency; neatend things up; took out warnings.
 * 
 * Revision 1.10  1994/04/08  16:59:39  john
 * Add fading poly's; Made palette fade 32 instead of 16.
 * 
 * Revision 1.9  1994/03/16  17:21:09  john
 * Added slow palette searching options.
 * 
 * Revision 1.8  1994/03/14  17:59:35  john
 * Added function to check bitmap's transparency.
 * 
 * Revision 1.7  1994/03/14  17:16:21  john
 * fixed bug with counting freq of pixels.
 * 
 * Revision 1.6  1994/03/14  16:55:47  john
 * Changed grs_bitmap structure to include bm_flags.
 * 
 * Revision 1.5  1994/02/18  15:32:22  john
 * *** empty log message ***
 * 
 * Revision 1.4  1993/10/15  16:22:49  john
 * *** empty log message ***
 * 
 * Revision 1.3  1993/09/08  17:37:11  john
 * Checking for errors with Yuan...
 * 
 * Revision 1.2  1993/09/08  14:46:27  john
 * looking for possible bugs...
 * 
 * Revision 1.1  1993/09/08  11:43:05  john
 * Initial revision
 * 
 *
 */

#include <stdlib.h>
#include <stdio.h>
#include <Memory.h>

#include "mem.h"
#include "gr.h"
#include "grdef.h"

grs_bitmap *gr_create_bitmap(int w, int h )
{
    grs_bitmap *new;

    new = (grs_bitmap *)mymalloc( sizeof(grs_bitmap) );
	new->bm_x = 0;
	new->bm_y = 0;
    new->bm_w = w;
    new->bm_h = h;
	new->bm_flags = 0;
	new->bm_type = 0;
	new->bm_rowsize = w;
	new->bm_selector = 0;

    new->bm_data = (unsigned char *)mymalloc_align( w*h, 8 );

    return new;
}

grs_bitmap *gr_create_bitmap_raw(int w, int h, unsigned char * raw_data )
{
	grs_bitmap *new;

	new = (grs_bitmap *)mymalloc( sizeof(grs_bitmap) );
	new->bm_x = 0;
	new->bm_y = 0;
	new->bm_w = w;
	new->bm_h = h;
	new->bm_flags = 0;
	new->bm_type = 0;
	new->bm_rowsize = w;
	new->bm_data = raw_data;
	new->bm_selector = 0;

	return new;
}

void gr_init_bitmap( grs_bitmap *bm, int mode, int x, int y, int w, int h, int bytesperline, unsigned char * data )
{
	bm->bm_x = x;
	bm->bm_y = y;
	bm->bm_w = w;
	bm->bm_h = h;
	bm->bm_flags = 0;
	bm->bm_type = mode;
	bm->bm_rowsize = bytesperline;
	bm->bm_data = data;
	bm->bm_selector = 0;
}


grs_bitmap *gr_create_sub_bitmap(grs_bitmap *bm, int x, int y, int w, int h )
{
    grs_bitmap *new;

    new = (grs_bitmap *)mymalloc( sizeof(grs_bitmap) );
	new->bm_x = x+bm->bm_x;
	new->bm_y = y+bm->bm_y;
	new->bm_w = w;
    new->bm_h = h;
	new->bm_flags = bm->bm_flags;
	new->bm_type = bm->bm_type;
	new->bm_rowsize = bm->bm_rowsize;
	new->bm_data = bm->bm_data+(unsigned int)((y*bm->bm_rowsize)+x);
	new->bm_selector = 0;

	return new;
}


void gr_free_bitmap(grs_bitmap *bm )
{
	if (bm->bm_data!=NULL)	
    	myfree(bm->bm_data);
	bm->bm_data = NULL;
	if (bm!=NULL)
    	myfree(bm);
}

void gr_free_sub_bitmap(grs_bitmap *bm )
{
	if (bm!=NULL)
    	myfree(bm);
}

void decode_data_asm(ubyte *data, int num_pixels, ubyte *colormap, int *count)
{
	int i;
	
	for (i = 0; i < num_pixels; i++) {
		count[*data]++;
		*data = colormap[*data];
		data++;
	}
}

void build_colormap_good( ubyte * palette, ubyte * colormap, int * freq )
{
	int i, r, g, b;

	for (i=0; i<256; i++ )	{
		r = *palette++;		
		g = *palette++;		
		b = *palette++;		
 		*colormap++ = gr_find_closest_color( r, g, b );
		*freq++ = 0;
	}
}

void gr_remap_bitmap( grs_bitmap * bmp, ubyte * palette, int transparent_color, int super_transparent_color )
{
	ubyte colormap[256];
	int freq[256], i, n;

	// This should be build_colormap_asm, but we're not using invert table, so...
	build_colormap_good( palette, colormap, freq );

	if ( (super_transparent_color>=0) && (super_transparent_color<=255))
		colormap[super_transparent_color] = 254;

	if ( (transparent_color>=0) && (transparent_color<=255))
		colormap[transparent_color] = TRANSPARENCY_COLOR;

	n = bmp->bm_w * bmp->bm_h;
	for (i = 0; i < n; i++)
		bmp->bm_data[i] = colormap[bmp->bm_data[i]];
	decode_data_asm(bmp->bm_data, bmp->bm_w * bmp->bm_h, colormap, freq );

	if ( (transparent_color>=0) && (transparent_color<=255) && (freq[transparent_color]>0) )
		bmp->bm_flags |= BM_FLAG_TRANSPARENT;

	if ( (super_transparent_color>=0) && (super_transparent_color<=255) && (freq[super_transparent_color]>0) )
		bmp->bm_flags |= BM_FLAG_SUPER_TRANSPARENT;
}

void gr_remap_bitmap_good( grs_bitmap * bmp, ubyte * palette, int transparent_color, int super_transparent_color )
{
	ubyte colormap[256];
	int freq[256];
   
	build_colormap_good( palette, colormap, freq );

	if ( (super_transparent_color>=0) && (super_transparent_color<=255))
		colormap[super_transparent_color] = 254;

	if ( (transparent_color>=0) && (transparent_color<=255))
		colormap[transparent_color] = TRANSPARENCY_COLOR;

	decode_data_asm(bmp->bm_data, bmp->bm_w * bmp->bm_h, colormap, freq );

	if ( (transparent_color>=0) && (transparent_color<=255) && (freq[transparent_color]>0) )
		bmp->bm_flags |= BM_FLAG_TRANSPARENT;

	if ( (super_transparent_color>=0) && (super_transparent_color<=255) && (freq[super_transparent_color]>0) )
		bmp->bm_flags |= BM_FLAG_SUPER_TRANSPARENT;
}


int gr_bitmap_assign_selector( grs_bitmap * bmp )
{
	bmp->bm_selector = 0;
	return 0;
}

void gr_bitmap_check_transparency( grs_bitmap * bmp )
{
	int x, y;
	ubyte * data;

	data = bmp->bm_data;
	
	for (y=0; y<bmp->bm_h; y++ )	{
		for (x=0; x<bmp->bm_w; x++ )	{
			if (*data++ == TRANSPARENCY_COLOR )	{
				bmp->bm_flags = BM_FLAG_TRANSPARENT;
				return;
			}
		}
		data += bmp->bm_rowsize - bmp->bm_w;
	}

	bmp->bm_flags = 0;

}
