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
 * $Source: Smoke:miner:source:2d::RCS:gr.h $
 * $Revision: 1.7 $
 * $Author: allender $
 * $Date: 1995/09/13 08:39:44 $
 *
 * Definitions for graphics lib.
 *
 * $Log: gr.h $
 * Revision 1.7  1995/09/13  08:39:44  allender
 * added prototype for gr_bitblt_cockpit
 *
 * Revision 1.6  1995/08/23  18:47:01  allender
 * fixed compiler warnings on mcc
 *
 * Revision 1.5  1995/08/14  15:51:01  allender
 * added #define for transparency color
 *
 * Revision 1.4  1995/06/13  13:03:55  allender
 * added graphics mode
 *
 * Revision 1.3  1995/04/18  09:50:16  allender
 * *** empty log message ***
 *
 * Revision 1.2  1995/04/07  07:32:33  allender
 * *** empty log message ***
 *
 * Revision 1.1  1995/03/09  09:04:16  allender
 * Initial revision
 *
 *
 * --- PC RCS information ---
 * Revision 1.45  1994/11/18  22:50:21  john
 * Changed shorts to ints in parameters.
 * 
 * Revision 1.44  1994/11/13  13:04:07  john
 * Added paged out bit in bitmap structure.  Commented out the
 * poly code that is never used.
 * 
 * Revision 1.43  1994/11/09  23:04:56  mike
 * Add avg_color field.
 * 
 * Revision 1.42  1994/10/27  00:53:35  john
 * Added RLE Flag to bitmap structere.
 * 
 * Revision 1.41  1994/10/26  23:55:52  john
 * Took out roller; Took out inverse table.
 * 
 * Revision 1.40  1994/08/11  17:59:12  mike
 * Assembler merge functions written for 3 rotations of bitmaps.
 * 
 * Revision 1.39  1994/08/10  12:24:56  matt
 * Added support for colors fonts & kerned fonts
 * Made our own font file format
 * 
 * Revision 1.38  1994/07/27  18:30:18  john
 * Took away the blending table.
 * 
 * Revision 1.37  1994/06/16  15:25:06  mike
 * Add flag BM_FLAG_NO_LIGHTING.
 * 
 * Revision 1.36  1994/05/31  10:01:22  john
 * *** empty log message ***
 * 
 * Revision 1.35  1994/05/31  07:53:34  john
 * *** empty log message ***
 * 
 * Revision 1.34  1994/05/14  17:19:41  matt
 * Added externs
 * 
 * Revision 1.33  1994/05/12  17:33:09  john
 * Added circle code.
 * 
 * Revision 1.32  1994/05/06  12:50:16  john
 * Added supertransparency; neatend things up; took out warnings.
 * 
 * Revision 1.31  1994/05/04  10:06:06  john
 * Added flag for bitmap super-transparency.
 * 
 * Revision 1.30  1994/05/03  19:38:56  john
 * *** empty log message ***
 * 
 * Revision 1.29  1994/04/22  11:16:05  john
 * *** empty log message ***
 * 
 * Revision 1.28  1994/04/08  16:59:32  john
 * Add fading poly's; Made palette fade 32 instead of 16.
 * 
 * Revision 1.27  1994/03/16  17:29:52  john
 * *** empty log message ***
 * 
 * Revision 1.26  1994/03/16  17:20:51  john
 * Added slow palette searching options.
 * 
 * Revision 1.25  1994/03/14  17:59:20  john
 * Added function to check bitmap's transparency.
 * 
 * Revision 1.24  1994/03/14  16:56:26  john
 * Changed grs_bitmap structure to include bm_flags.
 * 
 * Revision 1.23  1994/02/18  15:32:30  john
 * *** empty log message ***
 * 
 * Revision 1.22  1994/01/25  11:40:48  john
 * Added gr_check_mode function.
 * 
 * Revision 1.21  1994/01/12  13:45:24  john
 * Added scaler.
 * 
 * Revision 1.20  1993/12/21  19:58:24  john
 * added selector stuff
 * 
 * Revision 1.19  1993/12/21  11:40:40  john
 * *** empty log message ***
 * 
 * Revision 1.18  1993/12/09  15:02:08  john
 * Changed palette stuff majorly
 * 
 * Revision 1.17  1993/12/07  12:32:05  john
 * moved bmd_palette to gr_palette
 * 
 * Revision 1.16  1993/11/28  12:08:06  mike
 * Change prototype for rotate_bitmap.
 * 
 * Revision 1.15  1993/11/18  14:22:51  mike
 * Add prototype for rotate_bitmap.
 * 
 * Revision 1.14  1993/11/17  19:00:59  mike
 * Add prototype for test_rotate_bitmap
 * 
 * Revision 1.13  1993/11/16  11:28:58  john
 * *** empty log message ***
 * 
 * Revision 1.12  1993/10/26  13:17:43  john
 * *** empty log message ***
 * 
 * Revision 1.11  1993/10/15  16:23:37  john
 * y
 * 
 * Revision 1.10  1993/09/28  15:32:33  john
 * added def for save/restore vidmode
 * 
 * Revision 1.9  1993/09/28  12:51:46  matt
 * Added aspect ratio to grs_screen structure
 * 
 * Revision 1.8  1993/09/26  22:45:12  matt
 * Changed prototypes for line functions to take fixes, not ints.
 * 
 * Revision 1.7  1993/09/26  18:58:16  john
 * fadein/out stuff
 * 
 * Revision 1.6  1993/09/14  16:26:44  matt
 * Changed gr_change_mode() to be gr_set_mode()
 * 
 * Revision 1.4  1993/09/14  13:08:45  john
 * added gr_change_mode
 * 
 * Revision 1.3  1993/09/08  13:56:03  matt
 * Put 'if' block around body of file; added bitmap type BM_RGB15
 * 
 * Revision 1.2  1993/09/08  13:02:14  john
 * Changed structure definitions a bit.
 * 
 * Revision 1.1  1993/09/08  11:25:15  john
 * Initial revision
 * 
 *
 */

#ifndef _GR_H
#define _GR_H

#include <QDOffscreen.h>
#include "dtypes.h"
#include "fix.h"

#define SWAP_0_255			1			// swap black and white
#define TRANSPARENCY_COLOR	0			// palette entry of transparency color -- 255 on the PC

#define GR_FADE_LEVELS 34
#define GR_ACTUAL_FADE_LEVELS 32

extern int Gr_scanline_darkening_level;

typedef struct _grs_point {
	fix	x,y;
} grs_point;

typedef struct _grs_font {
	short		ft_w,ft_h;		// Width and height in pixels
	short		ft_flags;		// Proportional?
	short		ft_baseline;	//
	ubyte		ft_minchar,		// The first and last chars defined by
				ft_maxchar;		// This font
	short		ft_bytewidth;	// Width in unsigned chars
	ubyte	* 	ft_data;			// Ptr to raw data.
	ubyte	**	ft_chars;		// Ptrs to data for each char (required for prop font)
	short	*	ft_widths;		// Array of widths (required for prop font)
	ubyte *  ft_kerndata;	// Array of kerning triplet data
} grs_font;

#define BM_LINEAR   0

#define BM_FLAG_TRANSPARENT			1
#define BM_FLAG_SUPER_TRANSPARENT	2
#define BM_FLAG_NO_LIGHTING			4
#define BM_FLAG_RLE						8			// A run-length encoded bitmap.
#define BM_FLAG_PAGED_OUT				16			// This bitmap's data is paged out.

typedef struct _grs_bitmap {
	short       bm_x,bm_y;      // Offset from parent's origin
	short       bm_w,bm_h;      // width,height
	byte       	bm_type;        // 0=Linear, 1=ModeX, 2=SVGA
	byte		bm_flags;		// bit 0 on means it has transparency.
								// bit 1 on means it has supertransparency
								// bit 2 on means it doesn't get passed through lighting.
	short	    bm_rowsize;     // unsigned char offset to next row
	unsigned char *bm_data;		// ptr to pixel data...
								//   Linear = *parent+(rowsize*y+x)
								//   ModeX = *parent+(rowsize*y+x/4)
								//   SVGA = *parent+(rowsize*y+x)
	unsigned short bm_selector;
	ubyte			avg_color;	//	Average color of all pixels in texture map.
	byte			unused;		//	to 4-byte align.
} grs_bitmap;

typedef struct _grs_canvas {
	grs_bitmap  cv_bitmap;      // the bitmap for this canvas
	short       cv_color;       // current color
	short       cv_drawmode;    // fill,XOR,etc.
	grs_font *  cv_font;        // the currently selected font
	short       cv_font_fg_color;   // current font foreground color (-1==Invisible)
	short       cv_font_bg_color;   // current font background color (-1==Invisible)
} grs_canvas;

typedef struct _grs_screen {     // This is a video screen
	grs_canvas  sc_canvas;      // Represents the entire screen
	short       sc_mode;        // Video mode number
	short       sc_w, sc_h;     // Actual Width and Height
	fix			sc_aspect;		//aspect ratio (w/h) for this screen
} grs_screen;

// Num Cols Rows Bpp Mode Pages Aspect
// --- ---- ---- --- ---- ----- ------
// 0   320  200  8   C    1.0   1.2:1
// 1   320  200  8   U    4.0   1.2
// 2   320  240  8   U    3.4   1.0
// 3   360  200  8   U    3.6   1.4
// 4   360  240  8   U    3.0   1.1
// 5   376  282  8   U    2.5   1.0
// 6   320  400  8   U    2.0   0.6
// 7   320  480  8   U    1.7   0.5
// 8   360  400  8   U    1.8   0.7
// 9   360  480  8   U    1.5   0.6
// 10  360  360  8   U    2.0   0.8
// 11  376  308  8   U    2.3   0.9
// 12  376  564  8   U    1.2   0.5
// 13  640  400  8   V    4.1   1.2     (Assuming 1 Meg video RAM)
// 14  640  480  8   V    3.4   1.0
// 15  800  600  8   V    2.2   1.0
// 16  1024 768  8   V    1.0   1.0
// 17  640  480  15  V    1.0   1.0
// 18  800  600  15  V    1.0   1.0

#define SM_ORIGINAL		-1
//#define SM_320x200C     0
//#define SM_320x200U     1
#define SM_320x240U     2
#define SM_360x200U     3
#define SM_360x240U     4
#define SM_376x282U     5
#define SM_320x400U     6
#define SM_320x480U     7
#define SM_360x400U     8
#define SM_360x480U     9
#define SM_360x360U     10
#define SM_376x308U     11
#define SM_376x564U     12
#define SM_640x400V     13
#define SM_640x480V     14
#define SM_800x600V     15
#define SM_1024x768V    16
#define SM_640x480V15   17
#define SM_800x600V15   18

#define SM_320x200x8	1
#define SM_320x200x8UL	2
#define SM_320x200x16	3

////=========================================================================
// System functions:
// setup and set mode. this creates a grs_screen structure and sets
// grd_curscreen to point to it.  grs_curcanv points to this screen's
// canvas.  Saves the current VGA state and screen mode.

int gr_init();
void gr_enable_default_palette_loading();
void gr_disable_default_palette_loading();

// These 4 functions actuall change screen colors.
extern void gr_pal_fade_out(unsigned char * pal);
extern void gr_pal_fade_in(unsigned char * pal);
extern void gr_pal_clear();
extern void gr_pal_setblock( int start, int number, unsigned char * pal );
extern void gr_pal_getblock( int start, int number, unsigned char * pal );

//shut down the 2d.  Restore the screen mode.
void gr_close();

//  0=Mode set OK
//  1=No VGA adapter installed
//  2=Program doesn't support this VESA granularity
//  3=Monitor doesn't support that VESA mode.:
//  4=Video card doesn't support that VESA mode.
//  5=No VESA driver found.
//  6=Bad Status after VESA call/
//  7=Not enough DOS memory to call VESA functions.
//  8=Error using DPMI.
//  9=Error setting logical line width.
// 10=Error allocating selector for A0000h
// 11=Not a valid mode support by gr.lib
// Returns one of the above without setting mode
int gr_check_mode(int mode);	


//=========================================================================
// Canvas functions:

// Makes a new canvas. allocates memory for the canvas and its bitmap,
// including the raw pixel buffer.

grs_canvas *gr_create_canvas(int w, int h);

// Creates a canvas that is part of another canvas.  this can be used to make
// a window on the screen.  the canvas structure is malloc'd; the address of
// the raw pixel data is inherited from the parent canvas.

grs_canvas *gr_create_sub_canvas(grs_canvas *canv,int x,int y,int w, int h);

// Initialize the specified canvas. the raw pixel data buffer is passed as
// a parameter. no memory allocation is performed.

void gr_init_canvas(grs_canvas *canv,unsigned char *pixdata,int pixtype, int w,int h);

// Initialize the specified sub canvas. no memory allocation is performed.

void gr_init_sub_canvas(grs_canvas *new,grs_canvas *src,int x,int y,int w, int h);

// Free up the canvas and its pixel data.

void gr_free_canvas(grs_canvas *canv);

// Free up the canvas. do not free the pixel data, which belongs to the
// parent canvas.

void gr_free_sub_canvas(grs_canvas *canv);

// Clear the current canvas to the specified color
void gr_clear_canvas(int color);

//=========================================================================
// Bitmap functions:

// Allocate a bitmap and its pixel data buffer.
grs_bitmap *gr_create_bitmap(int w,int h);

// Allocated a bitmap and makes its data be raw_data that is already somewhere.
grs_bitmap *gr_create_bitmap_raw(int w, int h, unsigned char * raw_data );

// Creates a bitmap which is part of another bitmap
grs_bitmap *gr_create_sub_bitmap(grs_bitmap *bm,int x,int y,int w, int h);

// Free the bitmap and its pixel data
void gr_free_bitmap(grs_bitmap *bm);

// Free the bitmap, but not the pixel data buffer
void gr_free_sub_bitmap(grs_bitmap *bm);

void gr_bm_pixel( grs_bitmap * bm, int x, int y, unsigned char color );
void gr_bm_upixel( grs_bitmap * bm, int x, int y, unsigned char color );
void gr_bm_ubitblt( int w, int h, int dx, int dy, int sx, int sy, grs_bitmap * src, grs_bitmap * dest);
void gr_bm_ubitbltm(int w, int h, int dx, int dy, int sx, int sy, grs_bitmap * src, grs_bitmap * dest);

void gr_bitblt_cockpit(grs_bitmap *bm);

void gr_update_buffer( void * sbuf1, void * sbuf2, void * dbuf, int size );

//=========================================================================
// Color functions:

// When this function is called, the guns are set to gr_palette, and
// the palette stays the same until gr_close is called

void gr_use_palette_table(char * filename );

//=========================================================================
// Drawing functions:

// For solid, XOR, or other fill modes.
void gr_set_drawmode(int mode);

// Sets the color in the current canvas.  should be a macro
// Use: gr_setcolor(int color);
void gr_setcolor(int color);

// Draw a polygon into the current canvas in the current color and drawmode.
// verts points to an ordered list of x,y pairs.  the polygon should be
// convex; a concave polygon will be handled in some reasonable manner,
// but not necessarily shaded as a concave polygon. It shouldn't hang.
// probably good solution is to shade from minx to maxx on each scan line.
// int should really be fix
void gr_poly(int nverts,int *verts);
void gr_upoly(int nverts,int *verts);


// Draws a point into the current canvas in the current color and drawmode.
void gr_pixel(int x,int y);
void gr_upixel(int x,int y);

// Gets a pixel;
unsigned char gr_gpixel( grs_bitmap * bitmap, int x, int y );
unsigned char gr_ugpixel( grs_bitmap * bitmap, int x, int y );

// Draws a line into the current canvas in the current color and drawmode.
int gr_line(fix x0,fix y0,fix x1,fix y1);
int gr_uline(fix x0,fix y0,fix x1,fix y1);

// Draws an anti-aliased line into the current canvas in the current color and drawmode.
int gr_aaline(fix x0,fix y0,fix x1,fix y1);
int gr_uaaline(fix x0,fix y0,fix x1,fix y1);

// Draw the bitmap into the current canvas at the specified location.
void gr_bitmap(int x,int y,grs_bitmap *bm);
void gr_ubitmap(int x,int y,grs_bitmap *bm);
// bitmap function with transparency
void gr_bitmapm( int x, int y, grs_bitmap *bm );
void gr_ubitmapm( int x, int y, grs_bitmap *bm );

// Draw a rectangle into the current canvas.
void gr_rect(int left,int top,int right,int bot);
void gr_urect(int left,int top,int right,int bot);

// Draw a filled circle
int gr_disk(fix x,fix y,fix r);
int gr_udisk(fix x,fix y,fix r);

// Draw an outline circle
void gr_circle(fix x,fix y,fix r);
void gr_ucircle(fix x,fix y,fix r);

// Draw an unfilled rectangle into the current canvas
void gr_box(int left,int top,int right,int bot);
void gr_ubox(int left,int top,int right,int bot);

void gr_scanline( int x1, int x2, int y );
void gr_uscanline( int x1, int x2, int y );


// Reads in a font file... current font set to this one.
grs_font * gr_init_font( char * fontfile );
void gr_close_font( grs_font * font );

// Writes a string using current font. Returns the next column after last char.
void gr_set_fontcolor( int fg, int bg );
void gr_set_curfont( grs_font * new );
int gr_string(int x, int y, char *s );
int gr_ustring(int x, int y, char *s );
int gr_printf( int x, int y, char * format, ... );
int gr_uprintf( int x, int y, char * format, ... );
void gr_get_string_size(char *s, int *string_width, int *string_height, int *average_width );


//	From roller.c
void rotate_bitmap(grs_bitmap *bp, grs_point *vertbuf, int light_value);

// From scale.c
void scale_bitmap(grs_bitmap *bp, grs_point *vertbuf );

//===========================================================================
// Global variables
extern grs_canvas *grd_curcanv;             //active canvas
extern grs_screen *grd_curscreen;           //active screen
extern unsigned char Test_bitmap_data[64*64];

extern unsigned int FixDivide( unsigned int x, unsigned int y );

extern void gr_show_canvas( grs_canvas *canv );
extern void gr_set_current_canvas( grs_canvas *canv );

//flags for fonts
#define FT_COLOR			1
#define FT_PROPORTIONAL	2
#define FT_KERNED			4

// Special effects
extern void gr_snow_out(int num_dots);

extern void test_rotate_bitmap(void);
extern void rotate_bitmap(grs_bitmap *bp, grs_point *vertbuf, int light_value);

extern ubyte gr_palette[256*3];
extern ubyte gr_fade_table[256*GR_FADE_LEVELS];
extern ubyte gr_inverse_table[32*32*32];

extern ushort gr_palette_selector;
extern ushort gr_inverse_table_selector;
extern ushort gr_fade_table_selector;

// Remaps a bitmap into the current palette. If transparent_color is between 0 and 255
// then all occurances of that color are mapped to whatever color the 2d uses for 
// transparency. This is normally used right after a call to iff_read_bitmap like
// this:
//		iff_error = iff_read_bitmap(filename,new,BM_LINEAR,newpal);
//		if (iff_error != IFF_NO_ERROR) Error("Can't load IFF file <%s>, error=%d",filename,iff_error);
//		if ( iff_has_transparency )
//			gr_remap_bitmap( new, newpal, iff_transparent_color );
//		else
//			gr_remap_bitmap( new, newpal, -1 );
extern void gr_remap_bitmap( grs_bitmap * bmp, ubyte * palette, int transparent_color, int super_transparent_color );

// Same as above, but searches using gr_find_closest_color which uses 18-bit accurracy
// instaed of 15bit when translating colors.
extern void gr_remap_bitmap_good( grs_bitmap * bmp, ubyte * palette, int transparent_color, int super_transparent_color );

extern void gr_palette_step_up( int r, int g, int b );

extern void gr_bitmap_check_transparency( grs_bitmap * bmp );

// Allocates a selector that has a base address at 'address' and length 'size'.
// Returns 0 if successful... BE SURE TO CHECK the return value since there
// is a limited number of selectors available!!!
extern int get_selector( void * address, int size, unsigned int * selector );

// Assigns a selector to a bitmap. Returns 0 if successful.  BE SURE TO CHECK
// this return value since there is a limited number of selectors!!!!!!!
extern int gr_bitmap_assign_selector( grs_bitmap * bmp );

//#define GR_GETCOLOR(r,g,b) (gr_inverse_table[( (((r)&31)<<10) | (((g)&31)<<5) | ((b)&31) )])
//#define gr_getcolor(r,g,b) (gr_inverse_table[( (((r)&31)<<10) | (((g)&31)<<5) | ((b)&31) )])
//#define BM_XRGB(r,g,b) (gr_inverse_table[( (((r)&31)<<10) | (((g)&31)<<5) | ((b)&31) )])

#define BM_RGB(r,g,b) ( (((r)&31)<<10) | (((g)&31)<<5) | ((b)&31) )
#define BM_XRGB(r,g,b) gr_find_closest_color( (r)*2,(g)*2,(b)*2 )
#define GR_GETCOLOR(r,g,b) gr_find_closest_color( (r)*2,(g)*2,(b)*2 )
#define gr_getcolor(r,g,b) gr_find_closest_color( (r)*2,(g)*2,(b)*2 )

// Given: r,g,b, each in range of 0-63, return the color index that
// best matches the input.
int gr_find_closest_color( int r, int g, int b );

extern void gr_merge_textures( ubyte * lower, ubyte * upper, ubyte * dest );
extern void gr_merge_textures_1( ubyte * lower, ubyte * upper, ubyte * dest );
extern void gr_merge_textures_2( ubyte * lower, ubyte * upper, ubyte * dest );
extern void gr_merge_textures_3( ubyte * lower, ubyte * upper, ubyte * dest );

#endif
