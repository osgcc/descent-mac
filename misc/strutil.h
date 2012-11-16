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
 * $Source: Buggin:miner:source:misc::RCS:strutil.h $
 * $Revision: 1.2 $
 * $Author: allender $
 * $Date: 1995/05/04 20:11:07 $
 *
 * header file for string utilities
 * 
 * $Log: strutil.h $
 * Revision 1.2  1995/05/04  20:11:07  allender
 * add string utilities prototypes
 *
 * Revision 1.1  1995/03/30  15:04:12  allender
 * Initial revision
 *
*/
 
#ifndef _STRUTILS_
#define _STRUTILS_

extern int stricmp(char *str1, char *str2);
extern int strnicmp(char *str1, char *str2, int n);

#ifdef _MPW_
void strlwr( char *s1 );
void strrev( char *s1 );
#endif

#endif
