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
 * $Source: Smoke:miner:source:appltalk::RCS:appltalk.h $
 * $Revision: 1.5 $
 * $Author: allender $
 * $Date: 1995/10/11 01:00:31 $
 *
 *  header file which defines appletalk constants and structures
 *
 * $Log: appltalk.h $
 * Revision 1.5  1995/10/11  01:00:31  allender
 * changed prototype for get_zone_names
 *
 * Revision 1.4  1995/09/18  08:05:06  allender
 * added function to get my zone name
 *
 * Revision 1.3  1995/09/12  09:19:36  allender
 * added value to register netgame to help avoid name conflicts
 *
 * Revision 1.2  1995/09/08  17:14:15  allender
 * fixed typedefs for 68K build
 *
 * Revision 1.1  1995/08/30  16:10:54  allender
 * Initial revision
 *
 */
 
#ifndef _APPLETALK_H
#define _APPLETALK_H

#include <Appletalk.h>
#include <MixedMode.h>


enum {
	uppInitListenerProcInfo = kPascalStackBased
		 | RESULT_SIZE(SIZE_CODE(sizeof(OSErr)))
		 | STACK_ROUTINE_PARAMETER(1, SIZE_CODE(sizeof(QHdrPtr)))
		 | STACK_ROUTINE_PARAMETER(2, SIZE_CODE(sizeof(QHdrPtr)))
};

typedef pascal OSErr (*InitSocketListenerProcPtr)(QHdr *freeQ, QHdr *usedQ);

#if USESROUTINEDESCRIPTORS
typedef UniversalProcPtr	InitSktListenerUPP;

#define CallInitSocketListenerProc(userRoutine, freeQ, usedQ)	\
		CallUniversalProc((UniversalProcPtr)(userRoutine), uppInitListenerProcInfo, (freeQ), (usedQ))
#define NewInitSocketListenerProc(userRoutine)		\
		(InitSktListenerUPP) NewRoutineDescriptor((ProcPtr)userRoutine, uppInitListenerProcInfo, kM68kISA)
#else
typedef InitSocketListenerProcPtr	InitSktListenerUPP;

#define CallInitSocketListenerProc(userRoutine, freeQ, usedQ)	\
		(userRoutine)(freeQ, usedQ)
#define NewInitSocketListenerProc(userRoutine)		\
		(InitSktListenerUPP)(userRoutine)

	// add definition for accessing A5 which is in LowMem.h that doesn't get included when we
	// compile for 68K
#define LMGetCurrentA5() (* (Ptr *) 0x0904)
#endif

// definition for out packet structure in appletalk.  This structure is equivalent to the
// ECB structure used for IPX networking.  This is the format of the packet that we will get when
// we pull a buffer from the queue that our socket listener set up.

#if powerc
#pragma options align=mac68k
#endif

#define APPLETALK_MAX_DATA_SIZE 	586		// maximum amount of data we can send in a packet

typedef struct DDPPacket {
		QElemPtr	qLink;
		short		qType;
		short		packet_type;				/* DDP Type */
		short		dest_node;					/* Destination Node */
		AddrBlock	src_addr;					/* Source Address in AddrBlock format */
		ushort		length;						/* length of DDP datagram */
		char		data[APPLETALK_MAX_DATA_SIZE];	/* the DDP datagram */
} DDPPacket;

#if powerc
#pragma options align=reset
#endif

// errors returned from appletalk_init
#define APPLETALK_NOT_OPEN		-1
#define APPLETALK_BAD_LISTENER	-2
#define APPLETALK_NO_LOCAL_ADDR	-3
#define APPLETALK_NO_SOCKET		-4

extern int Appletalk_active;

int appletalk_init(void);
int get_appletalk_packet_data( ubyte *data );
void appletalk_send_packet_data(ubyte *data, int len, ubyte node, ushort net, ubyte socket);
ubyte appletalk_get_my_node(void);
ushort appletalk_get_my_net(void);
ubyte appletalk_get_my_socket(void);

// NBP type functions that are global

int appletalk_register_netgame(ubyte *gname, int value);
void appletalk_remove_netgame();
int appletalk_lookup_active_games(char *zone_name);
int appletalk_get_zone_names(char ***names);
int appletalk_get_my_zone(char *name);
void appletalk_send_game_info( ubyte *data, int size, char *zone_name);

#endif  // _APPLETALK_H
