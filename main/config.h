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
 * $Source: Smoke:miner:source:main::RCS:config.h $
 * $Revision: 1.3 $
 * $Author: allender $
 * $Date: 1995/09/08 17:12:26 $
 * 
 * prototype definitions for descent.cfg reading/writing
 * 
 * $Log: config.h $
 * Revision 1.3  1995/09/08  17:12:26  allender
 * added modem tool stuff for prefs file
 *
 * Revision 1.2  1995/09/05  08:47:48  allender
 * prefs file working
 *
 * Revision 1.1  1995/05/16  15:55:23  allender
 * Initial revision
 *
 * Revision 2.0  1995/02/27  11:32:48  john
 * New version 2.0, which has no anonymous unions, builds with
 * Watcom 10.0, and doesn't require parsing BITMAPS.TBL.
 * 
 * Revision 1.4  1995/02/11  16:20:06  john
 * Added code to make the default mission be the one last played.
 * 
 * Revision 1.3  1994/12/08  10:01:41  john
 * Changed the way the player callsign stuff works.
 * 
 * Revision 1.2  1994/11/14  17:53:17  allender
 * extern definitions for ReadConfigFile and WriteConfigFile
 * 
 * Revision 1.1  1994/11/14  16:56:17  allender
 * Initial revision
 * 
 * 
 */



#ifndef _CONFIG_H
#define _CONFIG_H

#include "player.h"

extern int ReadConfigFile(void);
extern int WriteConfigFile(void);

extern char config_last_player[CALLSIGN_LEN+1];
extern char config_last_mission[];
extern char config_last_ctb_cfg[];
extern int  config_last_ctb_tool;

#endif
