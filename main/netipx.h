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
 * $Source: Smoke:miner:source:main::RCS:NETIPX.H $
 * $Revision: 1.1 $
 * $Author: allender $
 * $Date: 1995/05/16 16:00:00 $
 * 
 * .
 * 
 * $Log: NETIPX.H $
 * Revision 1.1  1995/05/16  16:00:00  allender
 * Initial revision
 *
 * Revision 1.3  1994/05/11  19:45:26  john
 * *** empty log message ***
 * 
 * Revision 1.2  1994/05/11  18:44:10  john
 * Added first attemp at networking.
 * 
 * Revision 1.1  1994/05/11  16:07:06  john
 * Initial revision
 * 
 * 
 */


#ifndef _NETIPX_H
#define _NETIPX_H

typedef struct
{
	long	id;
	short	intnum;			// DOOM executes an int to send commands

// communication between DOOM and the driver
	short	command;			// CMD_SEND or CMD_GET
	short	remotenode;		// dest for send, set by get (-1 = no packet)
	short	datalength;		// bytes in doomdata to be sent / bytes read

// info common to all nodes
	short	numnodes;		// console is allways node 0
	short	ticdup;			// 1 = no duplication, 2-5 = dup for slow nets
	short	extratics;		// 1 = send a backup tic in every packet
	short	deathmatch;		// 1 = deathmatch
	short	savegame;		// -1 = new game, 0-5 = load savegame
	short	episode;		// 1-3
	short	map;			// 1-9
	short	skill;			// 1-5

// info specific to this node
	short	consoleplayer;	// 0-3 = player number
	short	numplayers;		// 1-4
	short	angleoffset;	// 1 = left, 0 = center, -1 = right
	short	drone;			// 1 = drone

// packet data to be sent
	char	data[512];
} doomcom_t;

extern doomcom_t *Inferno_net_data;

#define	CMD_SEND		1
#define	CMD_GET		2

void netipx_init();

#endif
