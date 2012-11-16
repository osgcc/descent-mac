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
 * $Source: Smoke:miner:source:main::RCS:INFERNO.H $
 * $Revision: 1.1 $
 * $Author: allender $
 * $Date: 1995/05/16 15:58:12 $
 *
 * Header file for Inferno.  Should be included in all source files. 
 *
 */

#ifndef _INFERNO_H
#define _INFERNO_H

#include	"settings.h"	//include personal settings

/**
 **	Constants
 **/

//	How close two points must be in all dimensions to be considered the same point.
#define	FIX_EPSILON	10

//for Function_mode variable
#define FMODE_EXIT		0		//leaving the program
#define FMODE_MENU		1		//Using the menu
#define FMODE_GAME		2		//running the game
#define FMODE_EDITOR		3		//running the editor

//This constant doesn't really belong here, but it is because of horrible
//circular dependencies involving object.h, aistruct.h, polyobj.h, & robot.h
#define MAX_SUBMODELS 10			//how many animating sub-objects per model

/**
 **	Global variables
 **/

extern int Function_mode;			//in game or editor?
extern int Screen_mode;				//editor screen or game screen?
extern char Menu_pcx_name[13];

#ifdef SATURN
extern char destsat_cdpath[128];
#endif

#endif


