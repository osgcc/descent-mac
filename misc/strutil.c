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
 * $Source: Smoke:miner:source:misc::RCS:strutil.c $
 * $Revision: 1.3 $
 * $Author: allender $
 * $Date: 1995/07/17 10:44:11 $
 *
 * string manipulation utility code
 * 
 * $Log: strutil.c $
 * Revision 1.3  1995/07/17  10:44:11  allender
 * fixed strrev
 *
 * Revision 1.2  1995/05/04  20:10:59  allender
 * added some string routines
 *
 * Revision 1.1  1995/03/30  15:03:55  allender
 * Initial revision
 *
*/
 
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include "mem.h"

// string compare without regard to case

int stricmp( char *s1, char *s2 )
{
	while( *s1 && *s2 )	{
		if ( tolower(*s1) != tolower(*s2) )	return 1;
		s1++;
		s2++;
	}
	if ( *s1 || *s2 ) return 1;
	return 0;
}

int strnicmp( char *s1, char *s2, int n )
{
	while( *s1 && *s2 && n)	{
		if ( tolower(*s1) != tolower(*s2) )	return 1;
		s1++;
		s2++;
		n--;
	}
	return 0;
}

void strlwr( char *s1 )
{
	while( *s1 )	{
		*s1 = tolower(*s1);
		s1++;
	}
}

void strrev( char *s1 )
{
	int i,l;
	char *s2;
	
	s2 = (char *)mymalloc(strlen(s1) + 1);
	strcpy(s2, s1);
	l = strlen(s2);
	for (i = 0; i < l; i++)
		s1[l-1-i] = s2[i];
	myfree(s2);
}

