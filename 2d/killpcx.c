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
#include <stdio.h>
#include <stdlib.h>
#include "types.h"

ubyte xor_value;

#define START_XOR	55

void restore_pcx(char *filename)
{
	int infile_size, i;
	FILE *infile, *outfile;
	unsigned char c;

	infile = fopen(filename, "rb");
	outfile = fopen("test.pcx", "wb");

	fseek(infile, -1, SEEK_END);
	infile_size = ftell(infile);

	fread(&xor_value, 1, 1, infile);
	xor_value--;
	fseek(infile, -1, SEEK_CUR);

//	p = (char *)malloc(infile_size);

	for (i = 0; i < infile_size; i++) {
		fseek(infile, -1, SEEK_CUR);
		fread(&c, 1, 1, infile);
		c = c ^ xor_value;
		fwrite(&c, 1, 1, outfile);
		xor_value--;
		if (xor_value < 0)
			xor_value = 255;
		fseek(infile, -1, SEEK_CUR);
	}

	fclose(infile);
	fclose(outfile);
}

int kill_pcx(char *filename)
{
	FILE *infile, *outfile;
	long int i, infile_size;
	unsigned char c, *p;

	infile = fopen(filename, "rb");
	outfile = fopen("killed.cow", "wb");

	if (!infile)
		return -1;

	fseek(infile, 0, SEEK_END);
	infile_size = ftell(infile);
	xor_value = START_XOR;

	for (i = 0; i < infile_size; i++) {
		fseek(infile, -1, SEEK_CUR);
		fread(&c, 1, 1, infile);
		c = c ^ xor_value;
		fwrite(&c, 1, 1, outfile);
 		xor_value++;
		if (xor_value > 255)
			xor_value = 0;
		fseek(infile, -1, SEEK_CUR);
	}
	fwrite(&xor_value, 1, 1, outfile);

	fclose(infile);
	fclose(outfile);

	return 0;
}




void main()
{
//	kill_pcx("brief02c.pcx");
	restore_pcx("killed.cow");
}
