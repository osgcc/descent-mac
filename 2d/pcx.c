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
 * $Source: Smoke:miner:source:2d::RCS:pcx.c $
 * $Revision: 1.11 $
 * $Author: allender $
 * $Date: 1995/11/02 14:11:35 $
 * 
 * Routines to read/write pcx images.
 * 
 * $Log: pcx.c $
 * Revision 1.11  1995/11/02  14:11:35  allender
 * shareware only code
 *
 * Revision 1.10  1995/10/30  11:12:13  allender
 * added new pcx code
 *
 * Revision 1.9  1995/10/21  00:14:35  allender
 * sped up pcx reading code
 *
 * Revision 1.8  1995/07/17  10:41:21  allender
 * get pcx writting working
 *
 * Revision 1.7  1995/07/05  16:07:05  allender
 * transparency/kitchen changes
 *
 * Revision 1.6  1995/05/12  11:53:06  allender
 * changed memory stuff again
 *
 * Revision 1.5  1995/04/27  07:38:35  allender
 * switch last and first palette entries when reading pcx file
 *
 * Revision 1.4  1995/04/19  14:38:38  allender
 * rearranged some functions
 *
 * Revision 1.3  1995/04/04  11:41:11  allender
 * *** empty log message ***
 *
 * Revision 1.2  1995/03/30  15:06:41  allender
 * *** empty log message ***
 *
 * Revision 1.1  1995/03/23  12:40:05  allender
 * Initial revision
 *
 *
 * --- PC RCS information ---
 * Revision 1.6  1995/03/01  15:38:12  john
 * Better ModeX support.
 * 
 * Revision 1.5  1995/01/21  17:54:17  john
 * Added pcx reader for modes other than modex.
 * 
 * Revision 1.4  1994/12/08  19:03:56  john
 * Made functions use cfile.
 * 
 * Revision 1.3  1994/11/29  02:53:24  john
 * Added error messages; made call be more similiar to iff.
 * 
 * Revision 1.2  1994/11/28  20:03:50  john
 * Added PCX functions.
 * 
 * Revision 1.1  1994/11/28  19:57:56  john
 * Initial revision
 * 
 * 
 */


#pragma off (unreferenced)
static char rcsid[] = "$Id: pcx.c 1.11 1995/11/02 14:11:35 allender Exp $";
#pragma on (unreferenced)

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "gr.h"
#include "mem.h"
#include "pcx.h"
#include "cfile.h"
#include "byteswap.h"
#include "error.h"

/* PCX Header data type */
typedef struct	{
	ubyte		Manufacturer;
	ubyte		Version;
	ubyte		Encoding;
	ubyte		BitsPerPixel;
	short		Xmin;
	short		Ymin;
	short		Xmax;
	short		Ymax;
	short		Hdpi;
	short		Vdpi;
	ubyte		ColorMap[16][3];
	ubyte		Reserved;
	ubyte		Nplanes;
	short		BytesPerLine;
	ubyte		filler[60];
} PCXHeader;

#ifndef MAC_SHAREWARE
int bald_guy_load( char * filename, grs_bitmap * bmp,int bitmap_type ,ubyte * palette )
{
	PCXHeader header;
	CFILE * PCXfile;
	int i, row, col, count, xsize, ysize, fsize;
	ubyte data, c, xor_value, *pixdata;
	ubyte cdata, *bguy_data, *bguy_data1, *p;

	PCXfile = cfopen( filename , "rb" );
	if ( !PCXfile )
		return PCX_ERROR_OPENING;
		
	cfseek(PCXfile, -1, SEEK_END);
	fsize = cftell(PCXfile);
	cfread(&xor_value, 1, 1, PCXfile);
	xor_value--;
	cfseek(PCXfile, 0, SEEK_SET);

	bguy_data = (ubyte *)malloc(fsize);
	bguy_data1 = (ubyte *)malloc(fsize);
	
	cfread(bguy_data1, 1, fsize, PCXfile);
	
	for (i = 0; i < fsize; i++) {
		c = bguy_data1[fsize - i - 1] ^ xor_value;
		bguy_data[i] = c;
		xor_value--;
		if (xor_value < 0)
			xor_value = 255;
	}
	cfclose(PCXfile);
	free(bguy_data1);
	
	p = bguy_data;
	memcpy( &header, p, sizeof(PCXHeader) );
	p += sizeof(PCXHeader);

	// Is it a 256 color PCX file?
	if ((header.Manufacturer != 10)||(header.Encoding != 1)||(header.Nplanes != 1)||(header.BitsPerPixel != 8)||(header.Version != 5))	{
		free(bguy_data);
		return PCX_ERROR_WRONG_VERSION;
	}
	header.Xmin= swapshort(header.Xmin);
	header.Xmax = swapshort(header.Xmax);
	header.Ymin = swapshort(header.Ymin);
	header.Ymax = swapshort(header.Ymax);

	// Find the size of the image
	xsize = header.Xmax - header.Xmin + 1;
	ysize = header.Ymax - header.Ymin + 1;

	if ( bmp->bm_data == NULL )	{
		memset( bmp, 0, sizeof( grs_bitmap ) );
		bmp->bm_data = mymalloc( xsize * ysize );
		if ( bmp->bm_data == NULL )	{
			free(bguy_data);
			return PCX_ERROR_MEMORY;
		}
		bmp->bm_w = bmp->bm_rowsize = xsize;
		bmp->bm_h = ysize;
		bmp->bm_type = bitmap_type;
	}

	for (row=0; row< ysize ; row++)      {
		for (row=0; row< ysize ; row++)      {
			pixdata = &bmp->bm_data[bmp->bm_rowsize*row];
			for (col=0; col< xsize ; )      {
				data = *p;
				p++;
				if ((data & 0xC0) == 0xC0)     {
					count =  data & 0x3F;
					data = *p;
					p++;
					memset( pixdata, data, count );
					pixdata += count;
					col += count;
				} else {
					*pixdata++ = data;
					col++;
				}
			}
		}
	}


	// Read the extended palette at the end of PCX file
	// Read in a character which should be 12 to be extended palette file

	p++;
	if (palette != NULL) {
		for (i = 0; i < 768; i++) {
			palette[i] = *p;
			palette[i] >>= 2;
			p++;
		}
	}


	free(bguy_data);

	return PCX_ERROR_NONE;
}
#endif

int pcx_read_bitmap( char * filename, grs_bitmap * bmp,int bitmap_type ,ubyte * palette )
{
	PCXHeader header;
	CFILE * PCXfile;
	int i, row, col, count, xsize, ysize;
	ubyte data, *pixdata, c;

	PCXfile = cfopen( filename , "rb" );
	if ( !PCXfile )
		return PCX_ERROR_OPENING;

	// read 128 char PCX header
	if (cfread( &header, sizeof(PCXHeader), 1, PCXfile )!=1)	{
		cfclose( PCXfile );
		return PCX_ERROR_NO_HEADER;
	}

	// Is it a 256 color PCX file?
	if ((header.Manufacturer != 10)||(header.Encoding != 1)||(header.Nplanes != 1)||(header.BitsPerPixel != 8)||(header.Version != 5))	{
		cfclose( PCXfile );
		return PCX_ERROR_WRONG_VERSION;
	}
	header.Xmin= swapshort(header.Xmin);
	header.Xmax = swapshort(header.Xmax);
	header.Ymin = swapshort(header.Ymin);
	header.Ymax = swapshort(header.Ymax);

	// Find the size of the image
	xsize = header.Xmax - header.Xmin + 1;
	ysize = header.Ymax - header.Ymin + 1;

	if ( bitmap_type == BM_LINEAR )	{
		if ( bmp->bm_data == NULL )	{
			memset( bmp, 0, sizeof( grs_bitmap ) );
			bmp->bm_data = mymalloc( xsize * ysize );
			if ( bmp->bm_data == NULL )	{
				cfclose( PCXfile );
				return PCX_ERROR_MEMORY;
			}
			bmp->bm_w = bmp->bm_rowsize = xsize;
			bmp->bm_h = ysize;
			bmp->bm_type = bitmap_type;
		}
	}

	if ( bmp->bm_type == BM_LINEAR )	{
		for (row=0; row< ysize ; row++)      {
			pixdata = &bmp->bm_data[bmp->bm_rowsize*row];
			for (col=0; col< xsize ; )      {
				if (cfread( &data, 1, 1, PCXfile )!=1 )	{
					cfclose( PCXfile );	
					return PCX_ERROR_READING;
				}
				if ((data & 0xC0) == 0xC0)     {
					count =  data & 0x3F;
					if (cfread( &data, 1, 1, PCXfile )!=1 )	{
						cfclose( PCXfile );	
						return PCX_ERROR_READING;
					}
#if 0
					if (data == 0)
						data = 0xff;
					else if (data == 0xff)
						data = 0;
#endif
					memset( pixdata, data, count );
					pixdata += count;
					col += count;
				} else {
#if 0
					if (data == 0)
						data = 0xff;
					else if (data == 0xff)
						data = 0;
#endif
					*pixdata++ = data;
					col++;
				}
			}
		}
	} else {
		for (row=0; row< ysize ; row++)      {
			for (col=0; col< xsize ; )      {
				if (cfread( &data, 1, 1, PCXfile )!=1 )	{
					cfclose( PCXfile );	
					return PCX_ERROR_READING;
				}
				if ((data & 0xC0) == 0xC0)     {
					count =  data & 0x3F;
					if (cfread( &data, 1, 1, PCXfile )!=1 )	{
						cfclose( PCXfile );	
						return PCX_ERROR_READING;
					}
					for (i=0;i<count;i++)
						gr_bm_pixel( bmp, col+i, row, data );
					col += count;
				} else {
					gr_bm_pixel( bmp, col, row, data );
					col++;
				}
			}
		}
	}

	// Read the extended palette at the end of PCX file
	if ( palette != NULL )	{
		// Read in a character which should be 12 to be extended palette file
		if (cfread( &data, 1, 1, PCXfile )==1)	{
			if ( data == 12 )	{
				if (cfread(palette,768, 1, PCXfile)!=1)	{
					cfclose( PCXfile );
					return PCX_ERROR_READING;
				}
				for (i=0; i<768; i++ )
					palette[i] >>= 2;
					
//				for (i = 0; i < 3; i++) {
//					c = palette[i];
//					palette[i] = palette[765+i];
//					palette[765+i] = c;
//				}
			}
		} else {
			cfclose( PCXfile );	
			return PCX_ERROR_NO_PALETTE;
		}
	}
	cfclose(PCXfile);
	return PCX_ERROR_NONE;
}

#if 0		// NEW WAY
int pcx_read_bitmap( char * filename, grs_bitmap * bmp,int bitmap_type ,ubyte * palette )
{
	PCXHeader header;
	CFILE * PCXfile;
	int i, row, col, count, xsize, ysize;
	ubyte data, c;
	ubyte row_data[640], *row_ptr, cdata;
	int buffer_size, buffer_pos;
	ubyte buffer[1024];
	ushort colors[256];

	PCXfile = cfopen( filename , "rb" );
	if ( !PCXfile )
		return PCX_ERROR_OPENING;

	// read 128 char PCX header
	if (cfread( &header, sizeof(PCXHeader), 1, PCXfile )!=1)	{
		cfclose( PCXfile );
		return PCX_ERROR_NO_HEADER;
	}

	// Is it a 256 color PCX file?
	if ((header.Manufacturer != 10)||(header.Encoding != 1)||(header.Nplanes != 1)||(header.BitsPerPixel != 8)||(header.Version != 5))	{
		cfclose( PCXfile );
		return PCX_ERROR_WRONG_VERSION;
	}
	header.Xmin= swapshort(header.Xmin);
	header.Xmax = swapshort(header.Xmax);
	header.Ymin = swapshort(header.Ymin);
	header.Ymax = swapshort(header.Ymax);

	// Find the size of the image
	xsize = header.Xmax - header.Xmin + 1;
	ysize = header.Ymax - header.Ymin + 1;

	if ( bmp->bm_data == NULL )	{
		memset( bmp, 0, sizeof( grs_bitmap ) );
		bmp->bm_data = mymalloc( xsize * ysize );
		if ( bmp->bm_data == NULL )	{
			cfclose( PCXfile );
			return PCX_ERROR_MEMORY;
		}
		bmp->bm_w = bmp->bm_rowsize = xsize;
		bmp->bm_h = ysize;
		bmp->bm_type = bitmap_type;
	}

	// Read the extended palette at the end of PCX file
	// Read in a character which should be 12 to be extended palette file

	if (palette != NULL) {
		cfseek( PCXfile, -768, SEEK_END );
		cfread( palette, 3, 256, PCXfile );
		cfseek( PCXfile, sizeof(PCXHeader), SEEK_SET );
		for (i=0; i<768; i++ )
			palette[i] >>= 2;
	}

	buffer_size = 1024;
	buffer_pos = 0;
	
	Assert( buffer_size == 1024 );
	buffer_size = cfread( buffer, 1, buffer_size, PCXfile );

	for (row=0; row< ysize ; row++)      {
		row_ptr = row_data;
		for (col=0; col< xsize ; )      {
			data = buffer[buffer_pos++];
			if ( buffer_pos == buffer_size )	{
				buffer_size = cfread( buffer, 1, buffer_size, PCXfile );
				buffer_pos = 0;
			}
			//cfread( &data, 1, 1, PCXfile )!=1 )	{
			if ((data & 0xC0) == 0xC0)     {
				count =  data & 0x3F;
				//cfread( &data, 1, 1, PCXfile );
				data = buffer[buffer_pos++];
				if ( buffer_pos == buffer_size )	{
					buffer_size = cfread( buffer, 1, buffer_size, PCXfile );
					buffer_pos = 0;
				}
				for (i = 0; i<count;i++)
					*row_ptr++ = data;
				col += count;
			} else {
				*row_ptr++ = data;
				col++;
			}
		}
		gr_linear_movsd(row_data, &(bmp->bm_data[row * bmp->bm_rowsize]), bmp->bm_w );
	}

#if 0
	// Read the extended palette at the end of PCX file
	if ( palette != NULL )	{
		// Read in a character which should be 12 to be extended palette file
		if (cfread( &data, 1, 1, PCXfile )==1)	{
			if ( data == 12 )	{
				if (cfread(palette,768, 1, PCXfile)!=1)	{
					cfclose( PCXfile );
					return PCX_ERROR_READING;
				}
				for (i=0; i<768; i++ )
					palette[i] >>= 2;
			}
		} else {
			cfclose( PCXfile );	
			return PCX_ERROR_NO_PALETTE;
		}
	}
#endif

	cfclose(PCXfile);
	return PCX_ERROR_NONE;
}
#endif

int pcx_write_bitmap( char * filename, grs_bitmap * bmp, ubyte * palette )
{
	int retval;
	int i;
	ubyte data;
	PCXHeader header;
	FILE * PCXfile;

	memset( &header, 0, sizeof( PCXHeader ) );

	header.Manufacturer = 10;
	header.Encoding = 1;
	header.Nplanes = 1;
	header.BitsPerPixel = 8;
	header.Version = 5;
	header.Xmax = swapshort((ushort)(bmp->bm_w-1));
	header.Ymax = swapshort((ushort)(bmp->bm_h-1));
	header.BytesPerLine = swapshort((ushort)bmp->bm_w);

	PCXfile = fopen( filename , "wb" );
	if ( !PCXfile )
		return PCX_ERROR_OPENING;

	if ( fwrite( &header, sizeof( PCXHeader ), 1, PCXfile ) != 1 )	{
		fclose( PCXfile );
		return PCX_ERROR_WRITING;
	}

	for (i=0; i<bmp->bm_h; i++ )	{
		if (!pcx_encode_line( &bmp->bm_data[bmp->bm_rowsize*i], bmp->bm_w, PCXfile ))	{
			fclose( PCXfile );
			return PCX_ERROR_WRITING;
		}
	}

	// Mark an extended palette	
	data = 12;
	if (fwrite( &data, 1, 1, PCXfile )!=1)	{
		fclose( PCXfile );
		return PCX_ERROR_WRITING;
	}

	// Write the extended palette
	for (i=0; i<768; i++ )	
		palette[i] <<= 2;
	
	retval = fwrite( palette, 768, 1, PCXfile );

	for (i=0; i<768; i++ )	
		palette[i] >>= 2;

	if (retval !=1)	{
		fclose( PCXfile );
		return PCX_ERROR_WRITING;
	}

	fclose( PCXfile );
	return PCX_ERROR_NONE;

}

// subroutine for writing an encoded byte pair 
// returns count of bytes written, 0 if error
int pcx_encode_byte(ubyte byt, ubyte cnt, FILE * fid) 
{
	ubyte c0 = 0xc0;
	
	if (cnt) {
		if ( (cnt==1) && (0xc0 != (0xc0 & byt)) )	{
			if(EOF == putc(byt, fid))
				return 0; 	// disk write error (probably full)
			return 1;
		} else {
			if(EOF == putc(0xC0 | cnt, fid))
				return 0; 	// disk write error
			if(EOF == putc(byt, fid))
				return 0; 	// disk write error
			return 2;
		}
	}
	return 0;
}

// returns number of bytes written into outBuff, 0 if failed 
int pcx_encode_line(ubyte *inBuff, int inLen, FILE * fp)
{  
	ubyte this, last;
	int srcIndex, i;
	register int total;
	register ubyte runCount; 	// max single runlength is 63
	total = 0;
	last = *(inBuff);		
	runCount = 1;

	for (srcIndex = 1; srcIndex < inLen; srcIndex++) {
		this = *(++inBuff);
		if (this == last)	{
			runCount++;			// it encodes
			if (runCount == 63)	{
				if (!(i=pcx_encode_byte(last, runCount, fp)))
					return(0);
				total += i;
				runCount = 0;
			}
		} else {   	// this != last
			if (runCount)	{
				if (!(i=pcx_encode_byte(last, runCount, fp)))
					return(0);
				total += i;
			}
			last = this;
			runCount = 1;
		}
	}	

	if (runCount)	{		// finish up
		if (!(i=pcx_encode_byte(last, runCount, fp)))
			return 0;
		return total + i;
	}
	return total;
}

//text for error messges
char pcx_error_messages[] = {
	"No error.\0"
	"Error opening file.\0"
	"Couldn't read PCX header.\0"
	"Unsupported PCX version.\0"
	"Error reading data.\0"
	"Couldn't find palette information.\0"
	"Error writing data.\0"
};


//function to return pointer to error message
char *pcx_errormsg(int error_number)
{
	char *p = pcx_error_messages;

	while (error_number--) {

		if (!p) return NULL;

		p += strlen(p)+1;

	}

	return p;

}
