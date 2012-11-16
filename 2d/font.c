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
/* $Source: Smoke:miner:source:2d::RCS:font.c $
 * $Revision: 1.14 $
 * $Author: allender $
 * $Date: 1995/10/03 13:08:31 $
 *
 * Graphical routines for drawing fonts.
 *
 * $Log: font.c $
 * Revision 1.14  1995/10/03  13:08:31  allender
 * new font code that doesn't use & as underline marker
 *
 * Revision 1.13  1995/09/24  10:50:23  allender
 * fixed signed/unsigned problem causing incorrect character widths
 * to be generated
 *
 * Revision 1.12  1995/08/14  14:26:01  allender
 * changed transparency color to 0
 *
 * Revision 1.11  1995/07/05  16:05:32  allender
 * transparency/kitchen changes
 *
 * Revision 1.10  1995/05/12  11:52:45  allender
 * changed memory stuff again
 *
 * Revision 1.9  1995/05/11  13:42:00  allender
 * changed char to ubyte in some cases to get extended characters
 *
 * Revision 1.8  1995/05/11  12:48:42  allender
 * change transparency color
 *
 * Revision 1.7  1995/05/04  20:00:07  allender
 * use NewPtr instead of malloc
 *
 * Revision 1.6  1995/05/01  08:38:34  allender
 * memory stuff and other things
 *
 * Revision 1.5  1995/04/27  07:39:06  allender
 * *** empty log message ***
 *
 * Revision 1.4  1995/04/19  14:38:01  allender
 * changed asm code to C
 *
 * Revision 1.3  1995/04/04  11:40:52  allender
 * *** empty log message ***
 *
 * Revision 1.2  1995/03/30  15:07:06  allender
 * *** empty log message ***
 *
 * Revision 1.1  1995/03/09  08:55:04  allender
 * Initial revision
 *
 *
 * --- PC RCS information ---
 * Revision 1.28  1994/11/27  23:08:22  matt
 * Changes for new mprintf calling convention
 * 
 * Revision 1.27  1994/11/18  23:54:50  john
 * Made centering work on x = 0x8000 not -0x8000.
 * 
 * Revision 1.26  1994/11/18  22:50:23  john
 * Changed shorts to ints in parameters.
 * 
 * Revision 1.25  1994/11/04  11:10:31  john
 * Took the & out of string sizing.
 * 
 * Revision 1.24  1994/11/04  10:06:36  john
 * Added fade table for fading fonts. Made font that partially clips
 * not print a warning message.
 * 
 * Revision 1.23  1994/09/29  10:09:06  john
 * Added real clipping to text.
 * 
 * Revision 1.22  1994/09/12  19:27:51  john
 * Fixed bug with unclipped fonts clipping.
 * 
 * Revision 1.21  1994/09/12  17:16:59  john
 * Added clipping.
 * 
 * Revision 1.20  1994/08/28  16:43:01  matt
 * Added centering if x==0x8000
 * 
 * Revision 1.19  1994/08/15  15:01:11  matt
 * Close font file after reading
 * 
 * Revision 1.18  1994/08/12  18:17:42  matt
 * Fixed stupid bug that cause first char in font not to print
 * 
 * Revision 1.17  1994/08/11  18:00:17  matt
 * Cleaned up code, fixed string width bug.
 * 
 * Revision 1.16  1994/08/10  18:46:11  matt
 * Fixed a couple of little things
 * 
 * Revision 1.15  1994/08/10  18:36:20  matt
 * Changed font file format.  Made chars not in font plot as spaces.  Font file
 * now stores palette for color font & remaps on load.
 * 
 * Revision 1.14  1994/08/10  12:27:27  matt
 * Took out unneeded int3
 * 
 * Revision 1.13  1994/08/10  12:25:26  matt
 * Added support for colors fonts & kerned fonts
 * Made our own font file format
 * 
 * Revision 1.12  1994/07/22  17:19:00  john
 * made proportional font width be the max width.
 * 
 * Revision 1.11  1994/05/06  12:50:26  john
 * Added supertransparency; neatend things up; took out warnings.
 * 
 * Revision 1.10  1994/01/31  11:08:12  john
 * fixed bug with order of frees.
 * 
 * Revision 1.9  1994/01/31  10:36:40  john
 * Free'd variable size font data.
 * 
 * Revision 1.8  1994/01/27  17:17:40  john
 * Made error if font file doesn't exist.
 * 
 * Revision 1.7  1993/10/26  13:17:48  john
 * *** empty log message ***
 * 
 * Revision 1.6  1993/10/15  16:23:25  john
 * y
 * 
 * Revision 1.5  1993/09/28  19:05:50  john
 * added support for \n in gr_string and gr_get_string_size
 * 
 * Revision 1.4  1993/09/28  12:46:49  matt
 * On error, now call Error() instead of exit().
 * 
 * Revision 1.3  1993/09/20  11:35:31  john
 * *** empty log message ***
 * 
 * Revision 1.2  1993/09/08  15:54:39  john
 * renamed ReadFile to readfontfile to prevent conflicts with others.
 * 
 * Revision 1.1  1993/09/08  11:43:34  john
 * Initial revision
 * 
 *
 */

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <Memory.h>

#include "mem.h"
#include "gr.h"
#include "grdef.h"
#include "error.h"
#include "mono.h"
#include "cfile.h"
#include "byteswap.h"

#define FONT        grd_curcanv->cv_font
#define FG_COLOR    grd_curcanv->cv_font_fg_color
#define BG_COLOR    grd_curcanv->cv_font_bg_color
#define FWIDTH       FONT->ft_w
#define FHEIGHT      FONT->ft_h
#define FBASELINE    FONT->ft_baseline
#define FFLAGS       FONT->ft_flags
#define FMINCHAR     FONT->ft_minchar
#define FMAXCHAR     FONT->ft_maxchar
#define FDATA        FONT->ft_data
#define FCHARS       FONT->ft_chars
#define FWIDTHS      FONT->ft_widths

#define BITS_TO_BYTES(x)    (((x)+7)>>3)

int gr_internal_string_clipped(int x, int y, char *s );
int gr_internal_string_clipped_m(int x, int y, char *s );

ubyte *find_kern_entry(grs_font *font,ubyte first,ubyte second)
{
	ubyte *p=font->ft_kerndata;

	while (*p!=255)
		if (p[0]==first && p[1]==second)
			return p;
		else p+=3;

	return NULL;

}

//takes the character AFTER being offset into font
#define INFONT(_c) ((_c >= 0) && (_c <= FMAXCHAR-FMINCHAR))

//takes the character BEFORE being offset into current font
get_char_width(ubyte c,ubyte c2,int *width,int *spacing)
{
	int letter;

	letter = c-FMINCHAR;

	if (!INFONT(letter)) {				//not in font, draw as space
		*width=0;
		if (FFLAGS & FT_PROPORTIONAL)
			*spacing = FWIDTH/2;
		else
			*spacing = FWIDTH;
		return;
	}

	if (FFLAGS & FT_PROPORTIONAL)
		*width = FWIDTHS[letter];
	else
		*width = FWIDTH;

	*spacing = *width;

	if (FFLAGS & FT_KERNED)  {
		ubyte *p;

		if (!(c2==0 || c2=='\n')) {
			int letter2;

			letter2 = c2-FMINCHAR;

			if (INFONT(letter2)) {

				p = find_kern_entry(FONT,letter,letter2);

				if (p)
					*spacing = p[2];
			}
		}
	}
}

int get_centered_x(char *s)
{
	int w,w2,s2;

	for (w=0;*s!=0 && *s!='\n';s++) {
		get_char_width(s[0],s[1],&w2,&s2);
		w += s2;
	}

	return ((grd_curcanv->cv_bitmap.bm_w - w) / 2);
}

#define UL_CHAR	0x03

int gr_internal_string0(int x, int y, char *s )
{
	unsigned char * fp;
	ubyte * text_ptr, * next_row, * text_ptr1;
	int r, BitMask, i, bits, width, spacing, letter, underline;

	unsigned int VideoOffset, VideoOffset1;

	VideoOffset1 = y * ROWSIZE + x;

	next_row = s;

	while (next_row != NULL )
	{
		text_ptr1 = next_row;
		next_row = NULL;

		if (x==0x8000) {			//centered
			int xx = get_centered_x(text_ptr1);
			VideoOffset1 = y * ROWSIZE + xx;
		}

		for (r=0; r<FHEIGHT; r++)
		{

			text_ptr = text_ptr1;

			VideoOffset = VideoOffset1;

			while (*text_ptr)
			{
				if (*text_ptr == '\n' )
				{
					next_row = &text_ptr[1];
					break;
				}

				underline = 0;
				if (*text_ptr == UL_CHAR )
				{
					if ((r==FBASELINE+2) || (r==FBASELINE+3))
						underline = 1;
					text_ptr++;
				}

				get_char_width(text_ptr[0],text_ptr[1],&width,&spacing);

				letter = *text_ptr-FMINCHAR;

				if (!INFONT(letter)) {	//not in font, draw as space
					VideoOffset += spacing;
					text_ptr++;
					continue;
				}

				if (FFLAGS & FT_PROPORTIONAL)
					fp = FCHARS[letter];
				else
					fp = FDATA + letter * BITS_TO_BYTES(width)*FHEIGHT;

				if (underline)
					for (i=0; i< width; i++ )
						DATA[VideoOffset++] = FG_COLOR;
				else
				{
					fp += BITS_TO_BYTES(width)*r;

					BitMask = 0;

					for (i=0; i< width; i++ )
					{
						if (BitMask==0) {
							bits = *fp++;
							BitMask = 0x80;
						}

						if (bits & BitMask)
							DATA[VideoOffset++] = FG_COLOR;
						else
							DATA[VideoOffset++] = BG_COLOR;
						BitMask >>= 1;
					}
				}

				VideoOffset += spacing-width;		//for kerning

				text_ptr++;
			}

			VideoOffset1 += ROWSIZE; y++;
		}
	}
	return 0;
}

int gr_internal_string0m(int x, int y, char *s )
{
	unsigned char * fp;
	ubyte * text_ptr, * next_row, * text_ptr1;
	int r, BitMask, i, bits, width, spacing, letter, underline;

	unsigned int VideoOffset, VideoOffset1;

	VideoOffset1 = y * ROWSIZE + x;

	next_row = s;

	while (next_row != NULL )
	{
		text_ptr1 = next_row;
		next_row = NULL;

		if (x==0x8000) {			//centered
			int xx = get_centered_x(text_ptr1);
			VideoOffset1 = y * ROWSIZE + xx;
		}

		for (r=0; r<FHEIGHT; r++)
		{

			text_ptr = text_ptr1;

			VideoOffset = VideoOffset1;

			while (*text_ptr)
			{
				if (*text_ptr == '\n' )
				{
					next_row = &text_ptr[1];
					break;
				}

				underline = 0;
				if (*text_ptr == UL_CHAR )
				{
					if ((r==FBASELINE+2) || (r==FBASELINE+3))
						underline = 1;
					text_ptr++;
				}

				get_char_width(text_ptr[0],text_ptr[1],&width,&spacing);

				letter = *text_ptr-FMINCHAR;

				if (!INFONT(letter)) {	//not in font, draw as space
					VideoOffset += spacing;
					text_ptr++;
					continue;
				}

				if (FFLAGS & FT_PROPORTIONAL)
					fp = FCHARS[letter];
				else
					fp = FDATA + letter * BITS_TO_BYTES(width)*FHEIGHT;

				if (underline)
					for (i=0; i< width; i++ )
						DATA[VideoOffset++] = FG_COLOR;
				else
				{
					fp += BITS_TO_BYTES(width)*r;

					BitMask = 0;

					for (i=0; i< width; i++ )
					{
						if (BitMask==0) {
							bits = *fp++;
							BitMask = 0x80;
						}

						if (bits & BitMask)
							DATA[VideoOffset++] = FG_COLOR;
						else
							VideoOffset++;
						BitMask >>= 1;
					}
				}
				text_ptr++;

				VideoOffset += spacing-width;
			}

			VideoOffset1 += ROWSIZE; y++;
		}
	}
	return 0;
}


//a bitmap for the character
grs_bitmap char_bm = {
				0,0,0,0,						//x,y,w,h
				BM_LINEAR,					//type
				BM_FLAG_TRANSPARENT,		//flags
				0,								//rowsize
				NULL,							//data
				0								//selector
};

int gr_internal_color_string(int x, int y, char *s )
{
	unsigned char * fp;
	ubyte * text_ptr, * next_row, * text_ptr1;
	int width, spacing,letter;
	int xx,yy;

	char_bm.bm_h = FHEIGHT;		//set height for chars of this font

	next_row = s;

	yy = y;

	while (next_row != NULL)
	{
		text_ptr1 = next_row;
		next_row = NULL;

		text_ptr = text_ptr1;

		xx = x;

		if (xx==0x8000)			//centered
			xx = get_centered_x(text_ptr);

		while (*text_ptr)
		{
			if (*text_ptr == '\n' )
			{
				next_row = &text_ptr[1];
				yy += FHEIGHT;
				break;
			}

			letter = *text_ptr-FMINCHAR;

			get_char_width(text_ptr[0],text_ptr[1],&width,&spacing);

			if (!INFONT(letter)) {	//not in font, draw as space
				xx += spacing;
				text_ptr++;
				continue;
			}

			if (FFLAGS & FT_PROPORTIONAL)
				fp = FCHARS[letter];
			else
				fp = FDATA + letter * BITS_TO_BYTES(width)*FHEIGHT;

			char_bm.bm_w = char_bm.bm_rowsize = width;

			char_bm.bm_data = fp;
			gr_bitmapm(xx,yy,&char_bm);

			xx += spacing;

			text_ptr++;
		}

	}
	return 0;
}

int gr_string(int x, int y, char *s )
{
	int w, h, aw;
	int clipped=0;

	if ( x == 0x8000 )	{
		if ( y<0 ) clipped |= 1;
		gr_get_string_size(s, &w, &h, &aw );
		// for x, since this will be centered, only look at
		// width.
		if ( w > grd_curcanv->cv_bitmap.bm_w ) clipped |= 1;	
		if ( (y+h) > grd_curcanv->cv_bitmap.bm_h ) clipped |= 1;	

		if ( (y+h) < 0 ) clipped |= 2;	
		if ( y > grd_curcanv->cv_bitmap.bm_h ) clipped |= 2;	

	} else {
		if ( (x<0) || (y<0) ) clipped |= 1;
		gr_get_string_size(s, &w, &h, &aw );
		if ( (x+w) > grd_curcanv->cv_bitmap.bm_w ) clipped |= 1;	
		if ( (y+h) > grd_curcanv->cv_bitmap.bm_h ) clipped |= 1;	
		if ( (x+w) < 0 ) clipped |= 2;	
		if ( (y+h) < 0 ) clipped |= 2;	
		if ( x > grd_curcanv->cv_bitmap.bm_w ) clipped |= 2;	
		if ( y > grd_curcanv->cv_bitmap.bm_h ) clipped |= 2;	
	}

	if ( !clipped )
		return gr_ustring(x, y, s );
	
	if ( clipped & 2 )	{
		// Completely clipped...
		mprintf( (1, "Text '%s' at (%d,%d) is off screen!\n", s, x, y ));
		return 0;
	}

	if ( clipped & 1 )	{
		// Partially clipped...
		//mprintf( (0, "Text '%s' at (%d,%d) is getting clipped!\n", s, x, y ));
	}

	// Partially clipped...

	if (FFLAGS & FT_COLOR) 
		return gr_internal_color_string( x, y, s);

	if ( BG_COLOR == -1)
		return gr_internal_string_clipped_m( x, y, s );
	
	return gr_internal_string_clipped( x, y, s );
}

int gr_ustring(int x, int y, char *s )
{
	if (FFLAGS & FT_COLOR) {

		return gr_internal_color_string(x,y,s);

	}
	else
		if ( BG_COLOR == -1)
			return gr_internal_string0m(x,y,s);
		else
			return gr_internal_string0(x,y,s);

	return 0;
}


void gr_get_string_size(char *s, int *string_width, int *string_height, int *average_width )
{
	int i = 0, longest_width = 0;
	int width,spacing;

	*string_height = FHEIGHT;
	*string_width = 0;
	*average_width = FWIDTH;

	if (s != NULL )
	{
		*string_width = 0;
		while (*s)
		{
//			if (*s == UL_CHAR)
//				s++;
			while (*s == '\n')
			{
				s++;
				*string_height += FHEIGHT;
				*string_width = 0;
			}

			if (*s == 0) break;

			get_char_width(s[0],s[1],&width,&spacing);

			*string_width += spacing;

			if (*string_width > longest_width)
				longest_width = *string_width;

			i++;
			s++;
		}
	}
	*string_width = longest_width;
}


int gr_uprintf( int x, int y, char * format, ... )
{
	char buffer[1000];
	va_list args;

	va_start(args, format );
	vsprintf(buffer,format,args);
	return gr_ustring( x, y, buffer );
}

int gr_printf( int x, int y, char * format, ... )
{
	char buffer[1000];
	va_list args;

	va_start(args, format );
	vsprintf(buffer,format,args);
	return gr_string( x, y, buffer );
}

void gr_close_font( grs_font * font )
{
	if (font)
	{
		if ( font->ft_chars ) 
			myfree( font->ft_chars );
		myfree( font );
	}
}

grs_font * gr_init_font( char * fontname )
{
	grs_font *font;
	int i;
	unsigned char * ptr;
	int nchars;
	CFILE *fontfile;
	int file_id;
	int datasize;		//size up to (but not including) palette
	ubyte c;

	fontfile = cfopen(fontname, "rb");

	if (!fontfile)
		Error( "Can't open font file %s", fontname );

	cfread(&file_id,sizeof(file_id),1,fontfile);
	cfread(&datasize,sizeof(datasize),1,fontfile);
	file_id = swapint(file_id);
	datasize = swapint(datasize);

	if (file_id != 'NFSP')
		Error( "File %s is not a font file", fontname );

	font = (grs_font *)mymalloc(datasize);

	memset(font, 0, datasize);
	cfread(font,1,datasize,fontfile);

// code to translate endians for font structures

	font->ft_w = swapshort(font->ft_w);
	font->ft_h = swapshort(font->ft_h);
	font->ft_flags = swapshort(font->ft_flags);
	font->ft_bytewidth = swapshort(font->ft_bytewidth);
	font->ft_data = (ubyte *)swapint((int)(font->ft_data));
	font->ft_chars = (ubyte **)swapint((int)(font->ft_chars));
	font->ft_widths = (short *)swapint((int)(font->ft_widths));
	font->ft_kerndata = (ubyte *)swapint((int)(font->ft_kerndata));

	nchars = font->ft_maxchar-font->ft_minchar+1;

	if (font->ft_flags & FT_PROPORTIONAL) {

		font->ft_widths = (short *) (((int) font->ft_widths) + ((ubyte *) font));
		
		for (i = 0; i < nchars; i++)
			font->ft_widths[i] = swapshort(font->ft_widths[i]);

		font->ft_data = ((int) font->ft_data) + ((ubyte *) font);

		font->ft_chars = (unsigned char **)mymalloc( nchars * sizeof(unsigned char *));

		ptr = font->ft_data;

		for (i=0; i< nchars; i++ ) {
			font->ft_chars[i] = ptr;
			if (font->ft_flags & FT_COLOR)
				ptr += font->ft_widths[i] * font->ft_h;
			else
				ptr += BITS_TO_BYTES(font->ft_widths[i]) * font->ft_h;
		}

	} else  {

		font->ft_data = ((unsigned char *) font) + sizeof(*font);

		font->ft_chars	= NULL;
		font->ft_widths = NULL;

		ptr = font->ft_data + (nchars * font->ft_w * font->ft_h);
	}

	if (font->ft_flags & FT_KERNED) 
		font->ft_kerndata = ((int) font->ft_kerndata) + ((ubyte *) font);

	if (font->ft_flags & FT_COLOR) {		//remap palette
		ubyte palette[256*3];
		ubyte colormap[256], c;
		int freq[256], n, i;

		cfread(palette,3,256,fontfile);		//read the palette
		
#ifdef SWAP_0_255
		for (i = 0; i < 3; i++) {
			c = palette[i];
			palette[i] = palette[765+i];
			palette[765+i] = c;
		}
#endif

		build_colormap_good( palette, colormap, freq );

#ifdef SWAP_0_255
		colormap[TRANSPARENCY_COLOR] = TRANSPARENCY_COLOR;
#else
		colormap[255] = 255;
#endif

		decode_data_asm(font->ft_data, ptr-font->ft_data, colormap, freq );

		for (i = 0; i < ptr-font->ft_data; i++) {
			if (font->ft_data[i] == 0)
				font->ft_data[i] = 255;
			else if (font->ft_data[i] == 255)
				font->ft_data[i] = 0;
		}

	}

	cfclose(fontfile);

	//set curcanv vars

	FONT        = font;
	FG_COLOR    = 0;
	BG_COLOR    = 0;

	return font;

}


void gr_set_fontcolor( int fg, int bg )
{
	FG_COLOR    = fg;
	BG_COLOR    = bg;
}

void gr_set_curfont( grs_font * new )
{
	FONT = new;
}


int gr_internal_string_clipped(int x, int y, char *s )
{
	unsigned char * fp;
	char * text_ptr, * next_row, * text_ptr1;
	int r, BitMask, i, bits, width, spacing, letter, underline;
	int x1 = x;
	
	next_row = s;

	while (next_row != NULL )
	{
		text_ptr1 = next_row;
		next_row = NULL;

		x = x1;
		if (x==0x8000)			//centered
			x = get_centered_x(text_ptr1);

		for (r=0; r<FHEIGHT; r++)	{
			text_ptr = text_ptr1;

			while (*text_ptr)	{
				if (*text_ptr == '\n' )	{
					next_row = &text_ptr[1];
					break;
				}

				underline = 0;
				if (*text_ptr == UL_CHAR )	{
					if ((r==FBASELINE+2) || (r==FBASELINE+3))
						underline = 1;
					text_ptr++;
				}

				get_char_width(text_ptr[0],text_ptr[1],&width,&spacing);

				letter = *text_ptr-FMINCHAR;

				if (!INFONT(letter)) {	//not in font, draw as space
					x += spacing;
					text_ptr++;
					continue;
				}

				if (FFLAGS & FT_PROPORTIONAL)
					fp = FCHARS[letter];
				else
					fp = FDATA + letter * BITS_TO_BYTES(width)*FHEIGHT;

				if (underline)	{
					for (i=0; i< width; i++ )	{
						gr_setcolor(FG_COLOR);
						gr_pixel( x++, y );						
					}
				} else {
					fp += BITS_TO_BYTES(width)*r;

					BitMask = 0;

					for (i=0; i< width; i++ )	{
						if (BitMask==0) {
							bits = *fp++;
							BitMask = 0x80;
						}
						if (bits & BitMask)	
							gr_setcolor(FG_COLOR);
						else
							gr_setcolor(BG_COLOR);
						gr_pixel( x++, y );						
						BitMask >>= 1;
					}
				}

				x += spacing-width;		//for kerning

				text_ptr++;
			}
			y++;
		}
	}
	return 0;
}

int gr_internal_string_clipped_m(int x, int y, char *s )
{
	unsigned char * fp;
	char * text_ptr, * next_row, * text_ptr1;
	int r, BitMask, i, bits, width, spacing, letter, underline;
	int x1 = x;
	
	next_row = s;

	while (next_row != NULL )
	{
		text_ptr1 = next_row;
		next_row = NULL;

		x = x1;
		if (x==0x8000)			//centered
			x = get_centered_x(text_ptr1);

		for (r=0; r<FHEIGHT; r++)	{
			text_ptr = text_ptr1;

			while (*text_ptr)	{
				if (*text_ptr == '\n' )	{
					next_row = &text_ptr[1];
					break;
				}

				underline = 0;
				if (*text_ptr == UL_CHAR )	{
					if ((r==FBASELINE+2) || (r==FBASELINE+3))
						underline = 1;
					text_ptr++;
				}

				get_char_width(text_ptr[0],text_ptr[1],&width,&spacing);

				letter = *text_ptr-FMINCHAR;

				if (!INFONT(letter)) {	//not in font, draw as space
					x += spacing;
					text_ptr++;
					continue;
				}

				if (FFLAGS & FT_PROPORTIONAL)
					fp = FCHARS[letter];
				else
					fp = FDATA + letter * BITS_TO_BYTES(width)*FHEIGHT;

				if (underline)	{
					for (i=0; i< width; i++ )	{
						gr_setcolor(FG_COLOR);
						gr_pixel( x++, y );						
					}
				} else {
					fp += BITS_TO_BYTES(width)*r;

					BitMask = 0;

					for (i=0; i< width; i++ )	{
						if (BitMask==0) {
							bits = *fp++;
							BitMask = 0x80;
						}
						if (bits & BitMask)	{
							gr_setcolor(FG_COLOR);
							gr_pixel( x++, y );
						} else {
							x++;
						}						
						BitMask >>= 1;
					}
				}

				x += spacing-width;		//for kerning

				text_ptr++;
			}
			y++;
		}
	}
	return 0;
}
