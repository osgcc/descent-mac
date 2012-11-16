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
 * $Source: Smoke:miner:source:2d::RCS:palette.c $
 * $Revision: 1.20 $
 * $Author: allender $
 * $Date: 1995/11/07 13:57:52 $
 *
 * Graphical routines for setting the palette
 *
 * $Log: palette.c $
 * Revision 1.20  1995/11/07  13:57:52  allender
 * set gr_palette_gamma_param to 4 as default
 *
 * Revision 1.19  1995/10/18  01:07:55  allender
 * new gamma correction stuff
 *
 * Revision 1.18  1995/10/13  14:39:46  allender
 * chance to appropriate GDevice when changing palette
 *
 * Revision 1.17  1995/09/13  08:39:19  allender
 * added gamma correction table instead of on the fly calculation
 *
 * Revision 1.16  1995/09/05  08:48:57  allender
 * changed palette gamme value to 1.5
 *
 * Revision 1.15  1995/09/04  11:41:36  allender
 * added back the debug_mode to set video mode to b/w on
 * error in case screen is faded.
 *
 * Revision 1.14  1995/08/18  15:49:20  allender
 * added gamma correction value for PC palette entries
 *
 * Revision 1.13  1995/08/14  14:26:20  allender
 * changed transparency color to 0
 *
 * Revision 1.12  1995/07/17  10:41:57  allender
 * get palette read function working
 *
 * Revision 1.11  1995/07/13  13:32:03  allender
 * change init_computed colors back to original form
 *
 * Revision 1.10  1995/07/05  16:06:13  allender
 * don't use palette manager anymore -- directly use the color manager
 * move transparency color back to entry 255 -- what a pain!!!
 *
 * Revision 1.9  1995/06/23  12:28:21  allender
 * fixed gamma step up problems
 *
 * Revision 1.8  1995/06/22  16:58:41  allender
 * moved check in gr_palette_fade_in to return immediatly if palette
 * already faded in
 *
 * Revision 1.7  1995/06/13  13:04:07  allender
 * modfied GWorld changes to execute only if GWorld is defined
 *
 * Revision 1.6  1995/06/06  16:02:38  allender
 * fixed gr_palette_set_up to work more correctly
 *
 * Revision 1.5  1995/05/11  12:49:01  allender
 * change transparency color -- fix up fade tables to reflect this
 *
 * Revision 1.4  1995/04/27  07:38:52  allender
 * use animate palette to do fade in and out's
 *
 * Revision 1.3  1995/04/18  09:49:39  allender
 * *** empty log message ***
 *
 * Revision 1.2  1995/04/07  13:15:01  allender
 * *** empty log message ***
 *
 * Revision 1.1  1995/03/09  09:20:08  allender
 * Initial revision
 *
 *
 * --- PC RCS information ---
 * Revision 1.39  1994/12/01  11:23:27  john
 * Limited Gamma from 0-8.
 * 
 * Revision 1.38  1994/11/28  01:31:08  mike
 * optimize color lookup function, caching recently used colors.
 * 
 * Revision 1.37  1994/11/18  22:50:18  john
 * Changed shorts to ints in parameters.
 * 
 * Revision 1.36  1994/11/15  17:54:59  john
 * Made text palette fade in when game over.
 * 
 * Revision 1.35  1994/11/10  19:53:14  matt
 * Fixed error handling is gr_use_palette_table()
 * 
 * Revision 1.34  1994/11/07  13:53:48  john
 * Added better gamma stufff.
 * 
 * Revision 1.33  1994/11/07  13:37:56  john
 * Added gamma correction stuff.
 * 
 * Revision 1.32  1994/11/05  13:20:14  john
 * Fixed bug with find_closest_color_current not working.
 * 
 * Revision 1.31  1994/11/05  13:08:09  john
 * MAde it return 0 when palette already faded out.
 * 
 * Revision 1.30  1994/11/05  13:05:34  john
 * Added back in code to allow keys during fade.
 * 
 * Revision 1.29  1994/11/05  12:49:50  john
 * Fixed bug with previous comment..
 * 
 * Revision 1.28  1994/11/05  12:48:46  john
 * Made palette only fade in / out when its supposed to.
 * 
 * Revision 1.27  1994/11/05  12:46:43  john
 * Changed palette stuff a bit.
 * 
 * Revision 1.26  1994/11/01  12:59:35  john
 * Reduced palette.256 size.
 * 
 * Revision 1.25  1994/10/26  23:55:35  john
 * Took out roller; Took out inverse table.
 * 
 * Revision 1.24  1994/10/04  22:03:05  matt
 * Fixed bug: palette wasn't fading all the way out or in
 * 
 * Revision 1.23  1994/09/22  16:08:40  john
 * Fixed some palette stuff.
 * 
 * Revision 1.22  1994/09/19  11:44:31  john
 * Changed call to allocate selector to the dpmi module.
 * 
 * Revision 1.21  1994/09/12  19:28:09  john
 * Fixed bug with unclipped fonts clipping.
 * 
 * Revision 1.20  1994/09/12  18:18:39  john
 * Set 254 and 255 to fade to themselves in fadetable
 * 
 * Revision 1.19  1994/09/12  14:40:10  john
 * Neatend.
 * 
 * Revision 1.18  1994/09/09  09:31:55  john
 * Made find_closest_color not look at superx spot of 254
 * 
 * Revision 1.17  1994/08/09  11:27:08  john
 * Add cthru stuff.
 * 
 * Revision 1.16  1994/08/01  11:03:51  john
 * MAde it read in old/new palette.256
 * 
 * Revision 1.15  1994/07/27  18:30:27  john
 * Took away the blending table.
 * 
 * Revision 1.14  1994/06/09  10:39:52  john
 * In fade out.in functions, returned 1 if key was pressed...
 * 
 * Revision 1.13  1994/05/31  19:04:16  john
 * Added key to stop fade if desired.
 * 
 * Revision 1.12  1994/05/06  12:50:20  john
 * Added supertransparency; neatend things up; took out warnings.
 * 
 * Revision 1.11  1994/05/03  19:39:02  john
 * *** empty log message ***
 * 
 * Revision 1.10  1994/04/22  11:16:07  john
 * *** empty log message ***
 * 
 * Revision 1.9  1994/04/08  16:59:40  john
 * Add fading poly's; Made palette fade 32 instead of 16.
 * 
 * Revision 1.8  1994/03/16  17:21:17  john
 * Added slow palette searching options.
 * 
 * Revision 1.7  1994/01/07  11:47:33  john
 * made use cflib
 * 
 * Revision 1.6  1993/12/21  11:41:04  john
 * *** empty log message ***
 * 
 * Revision 1.5  1993/12/09  15:02:47  john
 * Changed palette stuff majorly
 * 
 * Revision 1.4  1993/12/07  12:31:41  john
 * moved bmd_palette to gr_palette
 * 
 * Revision 1.3  1993/10/15  16:22:23  john
 * *** empty log message ***
 * 
 * Revision 1.2  1993/09/26  18:59:46  john
 * fade stuff
 * 
 * Revision 1.1  1993/09/08  11:44:03  john
 * Initial revision
 * 
 *
 */

#include <stdlib.h>
#include <stdio.h>
#include <Quickdraw.h>
#include <Palettes.h>
#include <Memory.h>
#include <math.h>

#include "dtypes.h"
#include "mem.h"
#include "gr.h"
#include "fix.h"
#include "error.h"
#include "macsys.h"
#include "palette.h"
#include "cfile.h"

extern int gr_installed;

ubyte gr_palette[256*3];
ubyte gr_current_pal[256*3];
ubyte gr_fade_table[256*34];
ubyte gr_debug_mode = 0;			// reverse white and black for debugging
ushort gr_mac_gamma[64];
//double gamma_corrections[9] = {1.45,1.5,1.55,1.6,1.65,1.7,1.75,1.8,1.85};
double gamma_corrections[9] = {1.7,1.6,1.5,1.4,1.3,1.2,1.1,1.0,0.9};

//	0,128,362,665,1024,1431,1881,2370,
//	2896,3456,4047,4669,5320,5999,6705,7436,
//	8192,8971,9775,10600,11448,12317,13208,14118,
//	15049,16000,16969,17957,18964,19989,21032,22092,
//	23170,24265,25376,26504,27648,28807,29983,31175,
//	32381,33603,34840,36092,37358,38639,39934,41243,
//	42566,43904,45254,46619,47997,49388,50792,52210,
//	53640,55083,56539,58008,59489,60982,62488,64006
//};			// gamma correction values for the macintosh

ushort gr_palette_selector;
ushort gr_fade_table_selector;

ubyte gr_palette_gamma = 4;
int gr_palette_gamma_param = 4;
ubyte gr_palette_faded_out = 1;

#define kGammaCorrect	1.70	//	Might also try 1.2
//#define kGammaCorrect 1.5

void gr_build_mac_gamma(double correction)
{
	int	i;

	for (i = 0; i < 64; i++)
		gr_mac_gamma[i] = (unsigned short) (pow(i / 64.0, correction) * 65536.0);
}

void gr_palette_set_gamma( int gamma )
{
	if ( gamma < 0 ) gamma = 0;
	if ( gamma > 8 ) gamma = 8;

	if (gr_palette_gamma_param != gamma )	{
		gr_palette_gamma_param = gamma;
		gr_palette_gamma = gamma;
		gr_build_mac_gamma(gamma_corrections[gr_palette_gamma]);
		if (!gr_palette_faded_out)
			gr_palette_load( gr_palette );
	}	
}

int gr_palette_get_gamma()
{
	return gr_palette_gamma_param;
}

void gr_use_palette_table( char * filename )
{
	CFILE *fp;
	int i,j;
	ubyte c;

	fp = cfopen( filename, "rb" );
	if ( fp==NULL)
		Error("Can't open palette file <%s> which is not in the current dir.",filename);

	cfread( gr_palette, 256*3, 1, fp );
	cfread( gr_fade_table, 256*34, 1, fp );
	cfclose(fp);

	// This is the TRANSPARENCY COLOR
	for (i=0; i<GR_FADE_LEVELS; i++ )	{
		gr_fade_table[i*256+255] = 255;
	}
	
// swap colors 0 and 255 of the palette along with fade table entries

#ifdef SWAP_0_255
	for (i = 0; i < 3; i++) {
		c = gr_palette[i];
		gr_palette[i] = gr_palette[765+i];
		gr_palette[765+i] = c;
	}

	for (i = 0; i < GR_FADE_LEVELS * 256; i++) {
		if (gr_fade_table[i] == 0)
			gr_fade_table[i] = 255;
	}
	for (i=0; i<GR_FADE_LEVELS; i++)
		gr_fade_table[i*256] = TRANSPARENCY_COLOR;
#endif
}

#define SQUARE(x) ((x)*(x))

#define	MAX_COMPUTED_COLORS	32

int	Num_computed_colors=0;

typedef struct {
	ubyte	r,g,b,color_num;
} color_record;

color_record Computed_colors[MAX_COMPUTED_COLORS];

//	Add a computed color (by gr_find_closest_color) to list of computed colors in Computed_colors.
//	If list wasn't full already, increment Num_computed_colors.
//	If was full, replace a random one.
void add_computed_color(int r, int g, int b, int color_num)
{
	int	add_index;

	if (Num_computed_colors < MAX_COMPUTED_COLORS) {
		add_index = Num_computed_colors;
		Num_computed_colors++;
	} else
		add_index = (rand() * MAX_COMPUTED_COLORS) >> 15;

	Computed_colors[add_index].r = r;
	Computed_colors[add_index].g = g;
	Computed_colors[add_index].b = b;
	Computed_colors[add_index].color_num = color_num;
}

void init_computed_colors(void)
{
	int	i;

	for (i=0; i<MAX_COMPUTED_COLORS; i++)
		Computed_colors[i].r = 255;		//	Make impossible to match.
}

int gr_find_closest_color( int r, int g, int b )
{
	int i, j;
	int best_value, best_index, value;

	if (Num_computed_colors == 0)
		init_computed_colors();

	//	If we've already computed this color, return it!
	for (i=0; i<Num_computed_colors; i++)
		if (r == Computed_colors[i].r)
			if (g == Computed_colors[i].g)
				if (b == Computed_colors[i].b) {
					if (i > 4) {
						color_record	trec;
						trec = Computed_colors[i-1];
						Computed_colors[i-1] = Computed_colors[i];
						Computed_colors[i] = trec;
						return Computed_colors[i-1].color_num;
					}
					return Computed_colors[i].color_num;
				}

//	r &= 63;
//	g &= 63;
//	b &= 63;

//	best_value = SQUARE(r-gr_palette[0])+SQUARE(g-gr_palette[1])+SQUARE(b-gr_palette[2]);
//	best_index = 0;
	best_value = SQUARE(r-gr_palette[765])+SQUARE(g-gr_palette[766])+SQUARE(b-gr_palette[767]);
	best_index = 255;
	if (best_value==0) {
		add_computed_color(r, g, b, best_index);
 		return best_index;
	}
	j=0;
	// only go to 255, 'cause we dont want to check the transparent color.
	for (i=1; i<254; i++ )	{
		j += 3;
		value = SQUARE(r-gr_palette[j])+SQUARE(g-gr_palette[j+1])+SQUARE(b-gr_palette[j+2]);
		if ( value < best_value )	{
			if (value==0) {
				add_computed_color(r, g, b, i);
				return i;
			}
			best_value = value;
			best_index = i;
		}
	}
	add_computed_color(r, g, b, best_index);
	return best_index;
}

int gr_find_closest_color_15bpp( int rgb )
{
	return gr_find_closest_color( ((rgb>>10)&31)*2, ((rgb>>5)&31)*2, (rgb&31)*2 );
}


int gr_find_closest_color_current( int r, int g, int b )
{
	int i, j;
	int best_value, best_index, value;

//	r &= 63;
//	g &= 63;
//	b &= 63;

//	best_value = SQUARE(r-gr_current_pal[0])+SQUARE(g-gr_current_pal[1])+SQUARE(b-gr_current_pal[2]);
//	best_index = 0;
	best_value = SQUARE(r-gr_palette[765])+SQUARE(g-gr_palette[766])+SQUARE(b-gr_palette[767]);
	best_index = 255;
	if (best_value==0)
 		return best_index;

	j=0;
	// only go to 255, 'cause we dont want to check the transparent color.
	for (i=1; i<254; i++ )	{
		j += 3;
		value = SQUARE(r-gr_current_pal[j])+SQUARE(g-gr_current_pal[j+1])+SQUARE(b-gr_current_pal[j+2]);
		if ( value < best_value )	{
			if (value==0)
				return i;
			best_value = value;
			best_index = i;
		}
	}
	return best_index;
}

static int last_r=0, last_g=0, last_b=0;

void gr_palette_step_up( int r, int g, int b )
{
	int i;
	ubyte *p;
	int temp;
	ColorSpec colors[256];
	GDHandle old_device;
//	PaletteHandle palette;
//	RGBColor color;
//	CTabHandle ctab;

	if (gr_palette_faded_out) return;

	if ( (r==last_r) && (g==last_g) && (b==last_b) ) return;

	last_r = r;
	last_g = g;
	last_b = b;

	p=gr_palette;
//	palette = GetPalette(GameWindow);
	for (i=0; i<256; i++ )	{
		colors[i].value = i;
//		temp = (int)(*p++) + r + gr_palette_gamma;
		temp = (int)(*p++) + r;
		if (temp<0) temp=0;
		else if (temp>63) temp=63;
		colors[i].rgb.red = gr_mac_gamma[temp];
//		temp = (int)(*p++) + g + gr_palette_gamma;
		temp = (int)(*p++) + g;
		if (temp<0) temp=0;
		else if (temp>63) temp=63;
		colors[i].rgb.green = gr_mac_gamma[temp];
//		temp = (int)(*p++) + b + gr_palette_gamma;
		temp = (int)(*p++) + b;
		if (temp<0) temp=0;
		else if (temp>63) temp=63;
		colors[i].rgb.blue = gr_mac_gamma[temp];
//		SetEntryColor(palette, i, &color);
	}
	old_device = GetGDevice();
	SetGDevice(GameMonitor);
	SetEntries(0, 255, colors);
	SetGDevice(old_device);
#if 0
	ctab = (CTabHandle)NewHandle(sizeof(ColorTable));
	Palette2CTab(palette, ctab);
	AnimatePalette(GameWindow, ctab, 0, 0, 256);
	ActivatePalette(GameWindow);
	DisposeHandle((Handle)ctab);

	if (GameGWorld != NULL) {
		ctab = (**GetGWorldPixMap(GameGWorld)).pmTable;	// get the color table for the gWorld.
		CTabChanged(ctab);
		(**ctab).ctSeed = (**(**(*(CGrafPtr)GameWindow).portPixMap).pmTable).ctSeed;
	}
#endif
}

void gr_palette_clear()
{
	int i;
	ColorSpec colors[256];
	GDHandle old_device;
//	PaletteHandle palette;
//	RGBColor color;
//	CTabHandle ctable;

	for (i = 0; i < 256; i++) {
		colors[i].value = i;
		colors[i].rgb.red = 0;
		colors[i].rgb.green = 0;
		colors[i].rgb.blue = 0;
	}
	old_device = GetGDevice();
	SetGDevice(GameMonitor);
	SetEntries(0, 255, colors);
	SetGDevice(old_device);

#if 0
	palette = GetPalette(GameWindow);
	for (i=0; i<256; i++) {
		color.red = 0x0;
		color.green = 0x0;
		color.blue = 0x0;
		SetEntryColor(palette, i, &color);
	}
	ctable = (CTabHandle)NewHandle(sizeof(ColorTable));
	Palette2CTab(palette, ctable);
	AnimatePalette(GameWindow, ctable, 0, 0, 256);
	ActivatePalette(GameWindow);
	
	DisposeHandle((Handle)ctable);

//  make the seeds match for the gworld clut and the window palette.  I don't know if
//  this is necessary, but it doesn't hurt.

	if (GameGWorld != NULL) {
		ctable = (**GetGWorldPixMap(GameGWorld)).pmTable;
		CTabChanged(ctable);
		(**ctable).ctSeed = (**(**(*(CGrafPtr)GameWindow).portPixMap).pmTable).ctSeed;
	}
#endif
	gr_palette_faded_out = 1;
}

void gr_palette_load( ubyte *pal )	
{
	int i, j;
	GDHandle old_device;
	ColorSpec colors[256];
//	PaletteHandle palette;
//	RGBColor color;
//	CTabHandle ctable;

	for (i=0; i<768; i++ ) {
// 		gr_current_pal[i] = pal[i] + gr_palette_gamma;
		gr_current_pal[i] = pal[i];
		if (gr_current_pal[i] > 63) gr_current_pal[i] = 63;
	}
	for (i = 0, j = 0; j < 256; j++) {
		colors[j].value = j;
		colors[j].rgb.red = gr_mac_gamma[gr_current_pal[i++]];
		colors[j].rgb.green = gr_mac_gamma[gr_current_pal[i++]];
		colors[j].rgb.blue = gr_mac_gamma[gr_current_pal[i++]];
	}
	old_device = GetGDevice();
	SetGDevice(GameMonitor);
	SetEntries(0, 255, colors);
	SetGDevice(old_device);

#if 0
	palette = GetPalette(GameWindow);
	for (i = 0; i < 768; i += 3) {
		color.red = gr_current_pal[i] << 9;
		color.green = gr_current_pal[i+1] << 9;
		color.blue = gr_current_pal[i+2] << 9;
		SetEntryColor(palette, i / 3, &color);
	}
	
	ctable = (CTabHandle)NewHandle(sizeof(ColorTable));
	Palette2CTab(palette, ctable);
	AnimatePalette(GameWindow, ctable, 0, 0, 256);
	ActivatePalette(GameWindow);
	
	DisposeHandle((Handle)ctable);

	if (GameGWorld != NULL) {
		ctable = (**GetGWorldPixMap(GameGWorld)).pmTable;	// get the color table for the gWorld.
		CTabChanged(ctable);
		(**ctable).ctSeed = (**(**(*(CGrafPtr)GameWindow).portPixMap).pmTable).ctSeed;
	}
#endif
	gr_palette_faded_out = 0;
	init_computed_colors();
}

int gr_palette_fade_out(ubyte *pal, int nsteps, int allow_keys )	
{
	ubyte c;
	int i,j, k;
	fix fade_palette[768];
	fix fade_palette_delta[768];
	ColorSpec colors[256];
	GDHandle old_device;
//	PaletteHandle palette;
//	RGBColor color;
//	CTabHandle ctable;

	allow_keys  = allow_keys;

	if (gr_palette_faded_out) return 0;

//	palette = GetPalette(GameWindow);

	for (i=0; i<768; i++ )	{
		fade_palette[i] = i2f(pal[i]);
		fade_palette_delta[i] = fade_palette[i] / nsteps;
	}

	for (j=0; j<nsteps; j++ )	{
		for (i=0, k = 0; k < 256; k++)	{
			colors[k].value = k;
			fade_palette[i] -= fade_palette_delta[i];
			if (fade_palette[i] < 0 )
				fade_palette[i] = 0;
//			colors[k].rgb.red = gr_mac_gamma[(f2i(fade_palette[i])+gr_palette_gamma)];
			colors[k].rgb.red = gr_mac_gamma[(f2i(fade_palette[i]))];
			i++;
			fade_palette[i] -= fade_palette_delta[i];
			if (fade_palette[i] < 0 )
				fade_palette[i] = 0;
//			colors[k].rgb.green = gr_mac_gamma[(f2i(fade_palette[i])+gr_palette_gamma)];
			colors[k].rgb.green = gr_mac_gamma[(f2i(fade_palette[i]))];
			i++;
			fade_palette[i] -= fade_palette_delta[i];
			if (fade_palette[i] < 0 )
				fade_palette[i] = 0;
//			colors[k].rgb.blue = gr_mac_gamma[(f2i(fade_palette[i])+gr_palette_gamma)];
			colors[k].rgb.blue = gr_mac_gamma[(f2i(fade_palette[i]))];
			i++;
		}
		old_device = GetGDevice();
		SetGDevice(GameMonitor);
		SetEntries(0, 255, colors);
		SetGDevice(old_device);
	}

#if 0
	for (j=0; j<nsteps; j++ )	{
		for (i=0; i<768; )	{		
			fade_palette[i] -= fade_palette_delta[i];
			if (fade_palette[i] < 0 )
				fade_palette[i] = 0;
			c = f2i(fade_palette[i])+gr_palette_gamma;
			color.red = c << 9;
			i++;
			fade_palette[i] -= fade_palette_delta[i];
			if (fade_palette[i] < 0 )
				fade_palette[i] = 0;
			c = f2i(fade_palette[i])+gr_palette_gamma;
			color.green = c << 9;
			i++;
			fade_palette[i] -= fade_palette_delta[i];
			if (fade_palette[i] < 0 )
				fade_palette[i] = 0;
			c = f2i(fade_palette[i])+gr_palette_gamma;
			color.blue = c << 9;
			i++;
			SetEntryColor(palette, (i / 3) - 1, &color);
		}
		ctable = (CTabHandle)NewHandle(sizeof(ColorTable));
		Palette2CTab(palette, ctable);
		AnimatePalette(GameWindow, ctable, 0, 0, 256);
		ActivatePalette(GameWindow);
		
		DisposeHandle((Handle)ctable);
	}
#endif
	gr_palette_faded_out = 1;
	return 0;
}

int gr_palette_fade_in(ubyte *pal, int nsteps, int allow_keys)	
{
	int i,j, k;
	ubyte c;
	fix fade_palette[768];
	fix fade_palette_delta[768];
	ColorSpec colors[256];
	GDHandle old_device;
//	PaletteHandle palette;
//	RGBColor color;
//	CTabHandle ctable;

	allow_keys  = allow_keys;

	if (!gr_palette_faded_out) return 0;

//	palette = GetPalette(GameWindow);

	for (i=0; i<768; i++ )	{
		gr_current_pal[i] = pal[i];
		fade_palette[i] = 0;
		fade_palette_delta[i] = i2f(pal[i]) / nsteps;
	}

	for (j=0; j<nsteps; j++ )	{
		for (i=0, k = 0; k<256; k++ )	{
			colors[k].value = k;
			fade_palette[i] += fade_palette_delta[i];
			if (fade_palette[i] > i2f(pal[i]) )
				fade_palette[i] = i2f(pal[i]);
//			c = f2i(fade_palette[i])+gr_palette_gamma;
			c = f2i(fade_palette[i]);
			if (c > 63) c = 63;
			colors[k].rgb.red = gr_mac_gamma[c];
			i++;
			fade_palette[i] += fade_palette_delta[i];
			if (fade_palette[i] > i2f(pal[i]) )
				fade_palette[i] = i2f(pal[i]);
//			c = f2i(fade_palette[i])+gr_palette_gamma;
			c = f2i(fade_palette[i]);
			if (c > 63) c = 63;
			colors[k].rgb.green = gr_mac_gamma[c];
			i++;
			fade_palette[i] += fade_palette_delta[i];
			if (fade_palette[i] > i2f(pal[i]) )
				fade_palette[i] = i2f(pal[i]);
//			c = f2i(fade_palette[i])+gr_palette_gamma;
			c = f2i(fade_palette[i]);
			if (c > 63) c = 63;
			colors[k].rgb.blue = gr_mac_gamma[c];
			i++;
		}
		old_device = GetGDevice();
		SetGDevice(GameMonitor);
		SetEntries(0, 255, colors);
		SetGDevice(old_device);
	}

#if 0
	for (i=0; i<768; i++ )	{
		gr_current_pal[i] = pal[i];
		fade_palette[i] = 0;
		fade_palette_delta[i] = i2f(pal[i]) / nsteps;
	}

	for (j=0; j<nsteps; j++ )	{
		for (i=0; i<768;  )	{
			fade_palette[i] += fade_palette_delta[i];
			if (fade_palette[i] > i2f(pal[i]) )
				fade_palette[i] = i2f(pal[i]);
			c = f2i(fade_palette[i])+gr_palette_gamma;
			if (c > 63) c = 63;
			color.red = c << 9;
			i++;
			fade_palette[i] += fade_palette_delta[i];
			if (fade_palette[i] > i2f(pal[i]) )
				fade_palette[i] = i2f(pal[i]);
			c = f2i(fade_palette[i])+gr_palette_gamma;
			if (c > 63) c = 63;
			color.green = c << 9;
			i++;
			fade_palette[i] += fade_palette_delta[i];
			if (fade_palette[i] > i2f(pal[i]) )
				fade_palette[i] = i2f(pal[i]);
			c = f2i(fade_palette[i])+gr_palette_gamma;
			if (c > 63) c = 63;
			color.blue = c << 9;
			i++;
			SetEntryColor(palette, (i / 3) - 1, &color);
		}
		ctable = (CTabHandle)NewHandle(sizeof(ColorTable));
		Palette2CTab(palette, ctable);
		AnimatePalette(GameWindow, ctable, 0, 0, 256);
		ActivatePalette(GameWindow);
		
		DisposeHandle((Handle)ctable);
	}
#endif
	gr_palette_faded_out = 0;
	return 0;
}

void debug_video_mode()
{
	ColorSpec color[2];
	GDHandle old_device;
	
	color[0].value = 0;
	color[0].rgb.red =  0xffff;
	color[0].rgb.blue = 0xffff;
	color[0].rgb.green = 0xffff;
	color[1].value = 255;
	color[1].rgb.red =  0x0;
	color[1].rgb.blue = 0x0;
	color[1].rgb.green = 0x0;
	old_device = GetGDevice();
	SetGDevice(GameMonitor);
	SetEntries(-1, 1, color);
	SetGDevice(old_device);
	gr_debug_mode = 1;
}

void reset_debug_video_mode()
{
	ColorSpec color[2];
	GDHandle old_device;
	
	color[0].value = 255;
	color[0].rgb.red =  0xffff;
	color[0].rgb.blue = 0xffff;
	color[0].rgb.green = 0xffff;
	color[1].value = 0;
	color[1].rgb.red =  0x0;
	color[1].rgb.blue = 0x0;
	color[1].rgb.green = 0x0;
	SetGDevice(GameMonitor);
	old_device = GetGDevice();
	SetEntries(-1, 1, color);
	SetGDevice(old_device);
	gr_debug_mode = 0;
}

void gr_make_cthru_table(ubyte * table, ubyte r, ubyte g, ubyte b )
{
	int i;
	ubyte r1, g1, b1;

	for (i=0; i<256; i++ )	{
		r1 = gr_palette[i*3+0] + r;
		if ( r1 > 63 ) r1 = 63;
		g1 = gr_palette[i*3+1] + g;
		if ( g1 > 63 ) g1 = 63;
		b1 = gr_palette[i*3+2] + b;
		if ( b1 > 63 ) b1 = 63;
		table[i] = gr_find_closest_color( r1, g1, b1 );
	}
}

void gr_palette_read(ubyte * pal)
{
	int i, j;
	char c;
	RGBColor color;
	
	for (i = 0, j=0; i < 256; i++) {
		Index2Color(i, &color);
		c = color.red>>10;
		pal[j++]=c;
		c = color.green>>10;
		pal[j++]=c;
		c = color.blue>>10;
		pal[j++]=c;
	}
}
