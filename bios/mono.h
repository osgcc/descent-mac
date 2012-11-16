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
 * $Source: Smoke:miner:source:bios::RCS:mono.h $
 * $Revision: 1.1 $
 * $Author: allender $
 * $Date: 1995/05/05 09:30:23 $
 *
 * Header for monochrome/mprintf functions
 *
 * $Log: mono.h $
 * Revision 1.1  1995/05/05  09:30:23  allender
 * Initial revision
 *
 *
 * --- PC RCS information ---
 * Revision 1.6  1994/12/03  17:07:37  matt
 * Made mono code turn off with either NDEBUG or NMONO
 * 
 * Revision 1.5  1994/11/27  23:07:28  matt
 * Made changes needed to be able to compile out monochrome debugging code
 * 
 * Revision 1.4  1993/12/07  12:33:28  john
 * *** empty log message ***
 * 
 * Revision 1.3  1993/09/14  20:54:50  matt
 * Made minit() check for mono card, return -1 if present, 0 if not
 * 
 * Revision 1.2  1993/07/22  13:05:40  john
 * added macros to print variables
 * 
 * Revision 1.1  1993/07/10  13:10:40  matt
 * Initial revision
 * 
 *
 */

#ifndef _MONO_H
#define _MONO_H

#if !(defined(NDEBUG) || defined(NMONO))		//normal, functioning versions

//==========================================================================
// Opens a scrollable window on the monochrome screen.
extern void mopen( int n, int row, int col, int width, int height, char * title );

//==========================================================================
// Clears a window
extern void ClearDebugWindow( int n );
#define mclear( arg ) ClearDebugWindow(n);

//==========================================================================
// Prints a formatted string on window n
extern void Debug( int n, char * format, ... );

#define mprintf(args) Debug args

#else			//null versions for when debugging turned off

#define minit()
#define mclose()
#define mopen( n, row, col, width, height, title )
#define mDumpD(window, int_var) 
#define mDumpX(window, int_var) 
#define mclear( n )
#define mprintf(args) 
#define mprintf_at(args)
#define mputc( n, c )
#define mputc_at( n, row, col, c )
#define msetcursor( row, col )
#define mrefresh(n)

#endif
#endif


