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
 * $Source: Smoke:miner:source:resource::RCS:resource.h $
 * $Revision: 1.4 $
 * $Author: allender $
 * $Date: 1995/10/07 16:57:58 $
 * 
 *  macros and definitions for resource values
 * 
 * $Log: resource.h $
 * Revision 1.4  1995/10/07  16:57:58  allender
 * added MEMORY_ALERT for not enough memory warning
 *
 * Revision 1.3  1995/09/13  08:42:44  allender
 * changed resource ids around
 *
 * Revision 1.2  1995/04/04  13:59:45  allender
 * *** empty log message ***
 *
 * Revision 1.1  1995/03/09  10:03:45  allender
 * Initial revision
 *
 *
 */

#ifndef _RESOURCE_H
#define _RESOURCE_H

// defines for dialog buttons.  Any dialog with OK and CANCEL will have OK as #1
// and CANCEL as #2
#define OK_BUTTON		1
#define CANCEL_BUTTON	2

// defines for the alert resources

#define QUIT_ALERT		128
#define MEMORY_ALERT	129
#define CD_ALERT		130
#define BAD_DATA_ALERT	131
#define WARN_ALERT		200
#define ERROR_ALERT 	200

// defines for PICT resources

#define BLACKBACK_PICT	2000	// black background to cover the desktop

#define MENU_BAR_ID		128

#define APPLE_MENU_ID	128
#define GAME_MENU_ID	129
#define EDIT_MENU_ID	130

// item numbers for the apple menu
#define ABOUT_ITEM		1

// item numbers for the game menu
#define RESUME_ITEM		1
#define QUIT_ITEM		3

// defines for windows
#define BLACK_WINDOW_ID		128
#define NO_BORDER_WIN_ID	128

#define DESCENT_PATH_STR	128

#endif
