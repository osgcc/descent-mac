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
 * $Source: Smoke:miner:source:main::RCS:LOADPATS.H $
 * $Revision: 1.1 $
 * $Author: allender $
 * $Date: 1995/05/16 15:58:59 $
 * 
 * Function to load patches to the GUS...
 * 
 * $Log: LOADPATS.H $
 * Revision 1.1  1995/05/16  15:58:59  allender
 * Initial revision
 *
 * Revision 1.2  1994/12/01  02:22:37  john
 * Incorporated LOADPATS.EXE into our code.
 * 
 * Revision 1.1  1994/12/01  01:42:25  john
 * Initial revision
 * 
 * 
 */



#ifndef _LOADPATS_H
#define _LOADPATS_H

// Returns 1 if error, else 0.
int loadpats(char * patch_filename);

#endif
