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
 * $Source: Smoke:miner:source:misc::RCS:fileutil.c $
 * $Revision: 1.6 $
 * $Author: allender $
 * $Date: 1995/10/30 11:09:51 $
 *
 * utilities for file manipulation
 * 
 * $Log: fileutil.c $
 * Revision 1.6  1995/10/30  11:09:51  allender
 * use FILE, not CFILE on the write* routines
 *
 * Revision 1.5  1995/05/11  13:00:34  allender
 * added write functions which swap bytes
 *
 * Revision 1.4  1995/05/04  20:10:38  allender
 * remove include for fcntl
 *
 * Revision 1.3  1995/04/26  10:14:39  allender
 * added byteswap header file
 *
 * Revision 1.2  1995/04/26  10:13:21  allender
 *
 * Revision 1.1  1995/03/30  15:02:34  allender
 * Initial revision
 *
*/
 
#include <stdio.h>
#include <stdlib.h>

#include "dtypes.h"
#include "fileutil.h"
#include "cfile.h"
#include "fix.h"
#include "byteswap.h"

int filelength(int fd)
{
	int cur_pos, end_pos;
	
	cur_pos = lseek(fd, 0, SEEK_CUR);
	lseek(fd, 0, SEEK_END);
	end_pos = lseek(fd, 0, SEEK_CUR);
	lseek(fd, cur_pos, SEEK_SET);
	return end_pos;
}

byte read_byte(CFILE *fp)
{
	byte b;
	
	cfread(&b, sizeof(byte), 1, fp);
	return b;
}

short read_short(CFILE *fp)
{
	short s;
	
	cfread(&s, sizeof(short), 1, fp);
	return (s);
}

short read_short_swap(CFILE *fp)
{
	short s;
	
	cfread(&s, sizeof(short), 1, fp);
	return swapshort(s);
}

int read_int(CFILE *fp)
{
	uint i;
	
	cfread(&i, sizeof(uint), 1, fp);
	return i;
}

int read_int_swap(CFILE *fp)
{
	uint i;
	
	cfread(&i, sizeof(uint), 1, fp);
	return swapint(i);
}

fix read_fix(CFILE *fp)
{
	fix f;
	
	cfread(&f, sizeof(fix), 1, fp);
	return f;
}

fix read_fix_swap(CFILE *fp)
{
	fix f;
	
	cfread(&f, sizeof(fix), 1, fp);
	return (fix)swapint((uint)f);
}

int write_byte(FILE *fp, byte b)
{
	return (fwrite(&b, sizeof(byte), 1, fp));
}

int write_short(FILE *fp, short s)
{
	return (fwrite(&s, sizeof(short), 1, fp));
}

int write_short_swap(FILE *fp, short s)
{
	s = swapshort(s);
	return (fwrite(&s, sizeof(short), 1, fp));
}

int write_int(FILE *fp, int i)
{
	return (fwrite(&i,sizeof(int), 1, fp));
}

int write_int_swap(FILE *fp, int i)
{
	i = swapint(i);
	return (fwrite(&i,sizeof(int), 1, fp));
}

int write_fix(FILE *fp, fix f)
{
	return (fwrite(&f, sizeof(fix), 1, fp));
}

int write_fix_swap(FILE *fp, fix f)
{
	f = (fix)swapint((int)f);
	return (fwrite(&f, sizeof(fix), 1, fp));
}
