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
 * $Source: Smoke:miner:source:2d::RCS:grdef.h $
 * $Revision: 1.5 $
 * $Author: allender $
 * $Date: 1995/09/14 15:36:33 $
 *
 * Internal definitions for graphics lib.
 *
 * $Log: grdef.h $
 * Revision 1.5  1995/09/14  15:36:33  allender
 * added stuff for 68k version
 *
 * Revision 1.4  1995/07/05  16:10:57  allender
 * gr_linear_movsd prototype changes
 *
 * Revision 1.3  1995/04/19  14:39:28  allender
 * changed function prototype
 *
 * Revision 1.2  1995/04/18  09:49:53  allender
 * *** empty log message ***
 *
 * Revision 1.1  1995/03/09  09:04:56  allender
 * Initial revision
 *
 *
 * --- PC RCS information ---
 * Revision 1.8  1994/05/06  12:50:09  john
 * Added supertransparency; neatend things up; took out warnings.
 * 
 * Revision 1.7  1994/01/25  11:40:29  john
 * Added gr_check_mode function.
 * 
 * Revision 1.6  1993/10/15  16:22:53  john
 * y
 * 
 * Revision 1.5  1993/09/29  17:31:00  john
 * added gr_vesa_pixel
 * 
 * Revision 1.4  1993/09/29  16:14:43  john
 * added global canvas descriptors.
 * 
 * Revision 1.3  1993/09/08  17:38:02  john
 * Looking for errors
 * 
 * Revision 1.2  1993/09/08  15:54:29  john
 * *** empty log message ***
 * 
 * Revision 1.1  1993/09/08  11:37:57  john
 * Initial revision
 * 
 *
 */
#define USE_2D_ASM 1
 
extern void gr_set_buffer(int w, int h, int r, int (*buffer_func)());

extern void gr_pal_setblock( int start, int n, unsigned char * palette );
extern void gr_pal_getblock( int start, int n, unsigned char * palette );
extern void gr_pal_setone( int index, unsigned char red, unsigned char green, unsigned char blue );

void gr_linear_movsb( ubyte * source, ubyte * dest, int nbytes);
void gr_linear_movsw( ubyte * source, ubyte * dest, int nbytes);
#if ( defined(__MWERKS__) && defined(__MC68K__) && defined(USE_2D_ASM) )
void gr_linear_movsd(ubyte * src:__A0, ubyte * dest:__A1, uint num_pixels:__D0 );
#else
void gr_linear_movsd( ubyte * source, ubyte * dest, uint nbytes);
#endif
void gr_linear_stosd( ubyte * source, unsigned char color, int nbytes);
extern unsigned int gr_var_color;
extern unsigned int gr_var_bwidth;
extern unsigned char * gr_var_bitmap;

void gr_linear_line( int x0, int y0, int x1, int y1);

extern unsigned int Table8to32[256];

extern unsigned char * gr_video_memory;

#define WIDTH   grd_curcanv->cv_bitmap.bm_w
#define HEIGHT  grd_curcanv->cv_bitmap.bm_h
#define MINX    0
#define MINY    0
#define MAXX    (WIDTH-1)
#define MAXY    (HEIGHT-1)
#define TYPE    grd_curcanv->cv_bitmap.bm_type
#define DATA    grd_curcanv->cv_bitmap.bm_data
#define XOFFSET grd_curcanv->cv_bitmap.bm_x
#define YOFFSET grd_curcanv->cv_bitmap.bm_y
#define ROWSIZE grd_curcanv->cv_bitmap.bm_rowsize
#define COLOR   grd_curcanv->cv_color


void order( int *x1, int *x2 );
