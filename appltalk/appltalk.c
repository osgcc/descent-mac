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
 * $Source: Smoke:miner:source:appltalk::RCS:appltalk.c $
 * $Revision: 1.17 $
 * $Author: allender $
 * $Date: 1995/10/18 17:13:12 $
 *
 * Appletalk code for initialization, sending, receiving, etc.
 *
 * $Log: appltalk.c $
 * Revision 1.17  1995/10/18  17:13:12  allender
 * lock down all appletalk stuff
 *
 * Revision 1.16  1995/10/11  01:00:10  allender
 * new implementation of get_zone_names
 *
 * Revision 1.15  1995/10/05  09:28:44  allender
 * increased the MAX_APPLETALK_BUFS to 128...there appeared to be crashes
 * related to running out of queue elements in the free queue for the
 * socket listener
 *
 * Revision 1.14  1995/09/23  09:37:16  allender
 * removed 'free' call on string that didn't need to be freed
 * try and handle NULL zone names properly...does this happen?
 *
 * Revision 1.13  1995/09/21  14:30:58  allender
 * attemp to release NBP binding when registering new game
 *
 * Revision 1.12  1995/09/21  12:57:29  allender
 * use two sockets for appletalk: reading and writing to try
 * and reduce time spent in socket code.  Added DDP packet type
 * for Descent appletalk packets
 *
 * Revision 1.11  1995/09/19  11:45:36  allender
 * don't free pointer after c2pstr
 *
 * Revision 1.10  1995/09/18  08:04:33  allender
 * fixed problem with getting zone names (duplictates
 * and missing ones).  Added function to get my zone name
 *
 * Revision 1.9  1995/09/13  08:40:52  allender
 * removed Warning statements, and beefed up return values.  Call routine
 * ...use variable instead of function to check for vm
 *
 * Revision 1.8  1995/08/31  11:49:29  allender
 * close socket in appletalk_close()  (DOH!!!)
 *
 * Revision 1.7  1995/08/31  10:33:57  allender
 * do_make
 * cd ::network
 * open network.c
 * open network.c
 *
 * Revision 1.6  1995/08/31  10:02:38  allender
 * create seperate data area for queue buffers as opposed
 * to packet buffers to fix nasty bug.
 *
 * Revision 1.5  1995/08/31  07:50:14  allender
 * put in Int3's for debugging
 *
 * Revision 1.4  1995/08/30  19:56:59  allender
 * fixed possible signed/unsigned problem with GetNodeAddress
 *
 * Revision 1.3  1995/08/30  17:13:59  allender
 * fix up packet pitching again!!!
 *
 * Revision 1.2  1995/08/30  16:58:08  allender
 * fix packet get to pitch packets sent from myself.  NPBExtract
 * needs indices from 1, not 0
 *
 * Revision 1.1  1995/08/30  16:10:48  allender
 * Initial revision
 *
 */
 
#include <AppleTalk.h> 
#include <Gestalt.h>
#include <GestaltEqu.h>
#include <Memory.h>
#include <MixedMode.h>
#include <Resources.h>
#include <Types.h>
#include <Errors.h>
#include <OSUtils.h>
#include <Strings.h>
#include "dtypes.h"
#include "appltalk.h"
#include "error.h"
#include "macsys.h"

//  MAX_APPLETALK_BUFS is the constant which defines the maximum number of appletalk
//  buffers that we could receive during a frame.  This constant should be the same
//  as the IPX constant.

#define MAX_APPLETALK_BUFS 		128
#define DEFAULT_LISTEN_SOCKET	0
#define DEFAULT_WRITE_SOCKET	0
#define DESCENT_PACKET_TYPE		0xab				// arbitrary packet type for descent packets
#define NBP_TYPE_NAME			"\pDescentNetGame"
#define NBP_DEFAULT_ZONE_NAME	"\p*"
#define MAX_APPLETALK_GAMES		16
#define MAX_ZONE_LENGTH			33

#ifdef __powerc
#pragma options align=mac68k
#endif

// type apacket_data will what we will receiving on our listening socket.

typedef struct apacket_data {
	int 	packetnum;
	byte	data[APPLETALK_MAX_DATA_SIZE];
} apacket_data;

static apacket_data packet_buffers[MAX_APPLETALK_BUFS];		// maximum number of receiving packets
static apacket_data queue_buffers[MAX_APPLETALK_BUFS];		// buffers for the listener queues
static apacket_data write_buffer;
static short packet_free_list[MAX_APPLETALK_BUFS];
static short packet_size[MAX_APPLETALK_BUFS];
static int largest_packet_index = 0;
static int num_packets = 0;
static int neterrors = 0;

//  structure definitions for the sending buffers.  We will allocate the space for
//  these structure when we initialize appletalk.  We will just pick the next unused
//  buffer for sending just like IPX.

typedef struct ddp_header {
	ubyte	filler[8];				// first 8 unused -- we will supply a pointer to byte 1
									// since we need it to be on an odd address.
	short	network;				// destination network number
	short	res1;
	ubyte	node;					// destination node
	ubyte	res2;
	ubyte	socket;					// destination socket
	ubyte	res3;
	ubyte	packet_type;			// DDP protocol type
} ddp_header;

ddp_header ddp_write_header;			// compiler alignment will ensure that each
									// entry starts on even boundry.

WDSElement wds[3];			// we will always only use two entries in the wds:
							//   1)  one for the ddp header
							//   2)  one for the data
							//   3)  must be zero to mark end of data

MPPParamBlock	write_pb;	// param block used for writing packets.

NamesTableEntry	game_nbp_entry;		// NBP for netgame that we are hosting


#ifdef __powerc
#pragma options align=reset
#endif

static int initialized = 0;
QHdr free_queue, used_queue;
Handle socket_listener;
DDPSocketListenerUPP listenerUPP;

ubyte appletalk_read_socket = DEFAULT_LISTEN_SOCKET;
ubyte appletalk_write_socket = DEFAULT_WRITE_SOCKET;
int appletalk_packetnum;
int Appletalk_active;			// status of appletalk

AddrBlock	my_address;

void appletalk_close()
{
	MPPParamBlock pb;

	if (!initialized)
		return;

	pb.DDP.socket = appletalk_read_socket;
	pb.DDP.csCode = closeSkt;
	pb.DDP.ioCompletion = NULL;
	PCloseSkt(&pb, 0);
	
	pb.DDP.socket = appletalk_write_socket;
	pb.DDP.csCode = closeSkt;
	pb.DDP.ioCompletion = NULL;
	PCloseSkt(&pb, 0);
	
	if (have_virtual_memory) {
		UnholdMemory(queue_buffers, sizeof(queue_buffers));
		UnholdMemory(&free_queue, sizeof(QHdr));
		UnholdMemory(&used_queue, sizeof(QHdr));
		UnholdMemory(*socket_listener, GetHandleSize(socket_listener));
		UnholdMemory(&write_buffer, sizeof(write_buffer));
		UnholdMemory(&ddp_write_header, sizeof(ddp_write_header));
		UnholdMemory(wds, sizeof(wds));
		UnholdMemory(&write_pb, sizeof(write_pb));
	}
	initialized = 0;
}

void free_appletalk_packet( int id )
{
	packet_buffers[id].packetnum = -1;
	packet_free_list[ --num_packets ] = id;
	if (largest_packet_index==id)	
		while ((--largest_packet_index>0) && (packet_buffers[largest_packet_index].packetnum == -1 ));
}

// got_new_appletalk_packet takes the DDP packet and get the appropriate info
// from the fields.

void got_new_appletalk_packet( DDPPacket *packet )
{
	apacket_data *p;
	int id;
	unsigned short datasize;

	datasize = 0;
	if ( (packet->src_addr.aNet != my_address.aNet) || (packet->src_addr.aNode != my_address.aNode) ){
		datasize = packet->length;
		// Find slot to put packet in...
		if ( datasize > 0 && datasize <= sizeof(apacket_data) )	{
			if ( num_packets >= MAX_APPLETALK_BUFS ) {
				Int3();
				//printf( 1, "IPX: Packet buffer overrun!!!\n" );
				neterrors++;
				return;
			}
			p = (apacket_data *)(packet->data);
			id = packet_free_list[ num_packets++ ];
			if (id > largest_packet_index ) largest_packet_index = id;
			packet_size[id] = datasize-sizeof(int);
			packet_buffers[id].packetnum =  p->packetnum;
			if ( packet_buffers[id].packetnum < 0 ) { neterrors++; return; }
			memcpy( packet_buffers[id].data, p->data, packet_size[id] );
		} else {
			neterrors++; return;
		}
	} 
}

// go through the appletalk queue to see if we need to process packets
// this is the queue that we set up for our socket listener

int appletalk_get_packet_data( ubyte * data )
{
	OSErr err;
	int i, n, best, best_id, size;

	best = -1;
	n = 0;
	best_id = -1;

	if(used_queue.qHead) {
		DDPPacket *packet;
		
		packet = (DDPPacket *)used_queue.qHead;	/* get the packet ptr */
		if ( (err = Dequeue((QElemPtr)packet, &used_queue)) == noErr) {
			if ( packet->packet_type == DESCENT_PACKET_TYPE )
				got_new_appletalk_packet(packet);
			Enqueue((QElemPtr)packet, &free_queue);		// requeue the packet for use again.
		}
		else {
			neterrors++;
			return 0;
		}
	}

	for (i=0; i<=largest_packet_index; i++ )	{
		if ( packet_buffers[i].packetnum > -1 ) {
			n++;
			if ( best == -1 || (packet_buffers[i].packetnum<best) )	{
				best = packet_buffers[i].packetnum;
				best_id = i;
			}
		}			
	}

	//mprintf( (0, "Best id = %d, pn = %d, last_ecb = %x, len=%x, ne = %d\n", best_id, best, last_ecb, lastlen, neterrors ));
	//mprintf( (1, "<%d> ", neterrors ));

	if ( best_id < 0 ) return 0;

	size = packet_size[best_id];
	memcpy( data, packet_buffers[best_id].data, size );
	free_appletalk_packet(best_id);

	return size;
}


/*
 *  Initialize appletalk.  Make the appropriate checks to be sure that the correct
 *  version of appletalk is available, and that appletalk is active.  Returns 0 if
 *  appletalk initialized okay, -1 if something is amuk.
*/
int appletalk_init()
{
	OSErr err;
	MPPParamBlock pb;
	ushort node, net;
	int i;
	
	if (initialized)
		return 0;
		
	if (!IsMPPOpen())
		return APPLETALK_NOT_OPEN;
		
//  Initialize the queue structures and enqueue the data onto our free queue

	free_queue.qFlags = used_queue.qFlags = 0;
	free_queue.qHead = used_queue.qHead = nil;
	free_queue.qTail = used_queue.qTail = nil;
		
	for (i = 0; i < MAX_APPLETALK_BUFS; i++)
		Enqueue((QElemPtr)&queue_buffers[i], &free_queue);
		
	if (have_virtual_memory) {
		HoldMemory(queue_buffers, sizeof(queue_buffers));
		HoldMemory(&free_queue, sizeof(QHdr));
		HoldMemory(&used_queue, sizeof(QHdr));
		HoldMemory(&write_buffer, sizeof(write_buffer));
		HoldMemory(&ddp_write_header, sizeof(ddp_write_header));
		HoldMemory(wds, sizeof(wds));
		HoldMemory(&write_pb, sizeof(write_pb));
	}
	
// set up the write data structures to point to the odd address of the ddp headers

	memset(wds, 0, sizeof(wds));
	wds[0].entryLength = 0;
	wds[0].entryPtr = (Ptr)((char *)(&ddp_write_header) + 1);		// point to the odd address
	wds[1].entryPtr = (Ptr)(&write_buffer);
	wds[2].entryLength = 0;
	wds[2].entryPtr = NULL;
	
// Get the code resource for the socket listener.  It is a code resource so this
// code can easily be shared with both 68K and PPC versions.

	if (socket_listener == NULL) {
		socket_listener = GetResource('Sock',128);
		if (socket_listener == nil)
			return 	APPLETALK_BAD_LISTENER;					// shouldn't happen unless something really bad
		MoveHHi(socket_listener);
		HNoPurge(socket_listener);
		HLock(socket_listener);
		err = CallInitSocketListenerProc(((InitSocketListenerProcPtr)((long) *socket_listener + 2)), &free_queue, &used_queue);

// Set up the socket listener

		if (have_virtual_memory)
			HoldMemory(*socket_listener, GetHandleSize(socket_listener));
	}
	initialized = 1;

	err = GetNodeAddress(&node, &net);
	if (err) {
		appletalk_close();
		return APPLETALK_NO_LOCAL_ADDR;
	}
	my_address.aNode = (ubyte)node;
	my_address.aNet = net;

// set up the reading and writing socket.  We will pass the normal listener
// in as the listener code for the writing socket, but it probably should never
// actually be called.

//	listenerUPP = NewDDPSocketListenerProc(*socket_listener);
//	pb.DDP.u.listener = listenerUPP;

	pb.DDP.u.listener = (DDPSocketListenerUPP) *socket_listener;
	pb.DDP.csCode = openSkt;
	pb.DDP.socket = appletalk_read_socket;
	err = POpenSkt(&pb, false);
	if (err) {
		appletalk_close();
		return APPLETALK_NO_SOCKET;
	}
	appletalk_read_socket = pb.DDP.socket;
	my_address.aSocket = appletalk_read_socket;
	
	pb.DDP.u.listener = (DDPSocketListenerUPP) *socket_listener;
	pb.DDP.csCode = openSkt;
	pb.DDP.socket = appletalk_write_socket;
	err = POpenSkt(&pb, false);
	if (err) {
		appletalk_close();
		return APPLETALK_NO_SOCKET;
	}
	appletalk_write_socket = pb.DDP.socket;

// set the self sending mechanism

	pb.SETSELF.newSelfFlag = 1;
	err = PSetSelfSend(&pb, 0);
	
	write_pb.DDP.ioResult = 0;			// zero out the result field 
	
	num_packets = 0;
	largest_packet_index = 0;
	appletalk_packetnum = 0;
	atexit(appletalk_close);
	return 1;
}

ubyte appletalk_get_my_node()
{
	return my_address.aNode;
}

ushort appletalk_get_my_net()
{
	return my_address.aNet;
}

ubyte appletalk_get_my_socket()
{
	return my_address.aSocket;
}

// sends off the information in the wds structure.  We will call PWriteDDP async with
// a completion routine to let us know when the packet is sent.

void appletalk_send_packet()
{
	OSErr err;
	
	write_pb.DDP.csCode = writeDDP;
	write_pb.DDP.socket = appletalk_write_socket;
	write_pb.DDP.checksumFlag = 0;
	write_pb.DDP.u.wdsPointer = (Ptr)wds;
	err = PWriteDDP(&write_pb, 1);
}


void appletalk_send_packet_data( ubyte * data, int datasize, ubyte node, ushort network, ubyte socket )
{
	Assert(initialized);
	Assert(datasize <= APPLETALK_MAX_DATA_SIZE);
	
	// Make sure no one is already sending something
	while ( write_pb.DDP.ioResult == 1 ) ;
	
//	if ( write_pb.DDP.ioResult )
//		Warning( "Send error %d for completion code\n", write_pb.DDP.ioResult );

	memset(&ddp_write_header, 0, sizeof(ddp_write_header));
	
	// Fill in destination address
	ddp_write_header.node = node;
	ddp_write_header.network = network;
	ddp_write_header.socket = socket;
	ddp_write_header.packet_type = DESCENT_PACKET_TYPE;

// set up packetnum information for counting

	write_buffer.packetnum = appletalk_packetnum;
	appletalk_packetnum++;
	
// set up the lenth of the packet to send in the wds structure
	wds[1].entryLength = sizeof(int) + (short)datasize;

	Assert( datasize > 1 );
	Assert( wds[1].entryLength <= APPLETALK_MAX_DATA_SIZE );

	memcpy( write_buffer.data, data, datasize );

	appletalk_send_packet();
}

int appletalk_register_netgame(ubyte *gname, int value)
{
	char *pgname;
	int register_count = 0;
	OSErr err;
	MPPParamBlock pb;
	char buf[100];

// attempt to remove a netgame that might be left over from previous game

	pb.NBP.ioCompletion = NULL;
	pb.NBP.csCode = removeName;
	pb.NBP.nbpPtrs.entityPtr = (Ptr)((char *)(&game_nbp_entry) + 9);
	err = PRemoveName(&pb, 0);

	sprintf(buf, "%s%d", gname, value);
	pgname = c2pstr(buf);
	NBPSetNTE((Ptr)(&game_nbp_entry), pgname, NBP_TYPE_NAME, NBP_DEFAULT_ZONE_NAME, appletalk_read_socket);
	pb.NBP.ioCompletion = NULL;
	pb.NBP.csCode = registerName;
	pb.NBP.interval = 0x07;
	pb.NBP.count = 0x3;
	pb.NBP.nbpPtrs.entityPtr = (Ptr)(&game_nbp_entry);
	pb.NBP.parm.verifyFlag = 1;
	do {
		err = PRegisterName(&pb, 0);
	} while ( (err == tooManyReqs) && (register_count++ < 3) );

	return err;
}

void appletalk_remove_netgame()
{
	int remove_count = 0;
	OSErr err;
	MPPParamBlock pb;
	
	pb.NBP.ioCompletion = NULL;
	pb.NBP.csCode = removeName;
	pb.NBP.nbpPtrs.entityPtr = (Ptr)((char *)(&game_nbp_entry) + 9);
	err = PRemoveName(&pb, 0);
//	if (err)
//		Warning("Problem removing NBP name: %d", err);
}	

// extract a zone name out of a packed array of pascal strings.
// buffer contains the string, total is max number, item is the
// zone name that we want, and name is the buffer.

int extract_zone(char *buffer, int total, int item, char *name)
{
	int i;
	ubyte len;
	char *s;
	
	if ( (item > total) )
		return 0;
		
	s = buffer;
	for (i = 0; i < item; i++) {
		len = (ubyte)*s;
		s += len + 1;
	}
	len = (ubyte)*s;
	if (len > 0)
		memcpy(name, s+1, len);
	name[len] = '\0';
	return 1;
}
	
#if 0
int appletalk_get_zone_names(char **names)
{
	int i, num_zones;
	XPPParamBlock pb;
	OSErr err;
	char zone_buffer[578];		// magic size of zone buffer for GetZoneList call
	char zone_name[33];			// single zone name extracted from list to be added to **names
	
	pb.XCALL.xppTimeout = 3;
	pb.XCALL.xppRetry = 4;
	pb.XCALL.zipBuffPtr = (Ptr)zone_buffer;
	pb.XCALL.zipLastFlag = 0;
	pb.XCALL.zipInfoField[0] = 0;
	pb.XCALL.zipInfoField[1] = 0;

	num_zones = 0;	
	do {
		err = GetZoneList(&pb, 0);
		if (err)
			break;
		for (i = 0; i < pb.XCALL.zipNumZones; i++) {
			if ( extract_zone(zone_buffer, pb.XCALL.zipNumZones, i, zone_name) ) {
				strcpy(names[num_zones], zone_name);
				num_zones++;
			}
		}
	} while ( (!pb.XCALL.zipLastFlag) && (err == noErr) );

	if (err)
		return err;
		
	return num_zones;
}
#endif

int appletalk_get_zone_names(char ***names)
{
	int i, num_zones, max_zones;
	XPPParamBlock pb;
	OSErr err;
	char zone_buffer[578];		// magic size of zone buffer for GetZoneList call
	char zone_name[33];			// single zone name extracted from list to be added to **names
	
	pb.XCALL.xppTimeout = 3;
	pb.XCALL.xppRetry = 4;
	pb.XCALL.zipBuffPtr = (Ptr)zone_buffer;
	pb.XCALL.zipLastFlag = 0;
	pb.XCALL.zipInfoField[0] = 0;
	pb.XCALL.zipInfoField[1] = 0;
	
	max_zones = 0;
	num_zones = 0;	

	do {
		err = GetZoneList(&pb, 0);
		if (err)
			break;
		max_zones += pb.XCALL.zipNumZones;
	} while ( (!pb.XCALL.zipLastFlag) && (err == noErr) );
	
	if ( max_zones == 0 )
		return 0;
	
	*names = (char **)malloc( max_zones*(sizeof(char *)) );
	for (i = 0; i < max_zones; i++)
		(*names)[i] = (char *)malloc(MAX_ZONE_LENGTH);

	pb.XCALL.xppTimeout = 3;
	pb.XCALL.xppRetry = 4;
	pb.XCALL.zipBuffPtr = (Ptr)zone_buffer;
	pb.XCALL.zipLastFlag = 0;
	pb.XCALL.zipInfoField[0] = 0;
	pb.XCALL.zipInfoField[1] = 0;

	do {
		err = GetZoneList(&pb, 0);
		if (err)
			break;

		for (i = 0; i < pb.XCALL.zipNumZones; i++) {
			if ( extract_zone(zone_buffer, pb.XCALL.zipNumZones, i, zone_name) ) {
				strcpy((*names)[num_zones], zone_name);
				num_zones++;
				if ( num_zones == max_zones )
					goto done;
			}
		}
	} while ( (!pb.XCALL.zipLastFlag) && (err == noErr) );

	if (err)
		return err;

done:		
	return num_zones;
}

int appletalk_get_my_zone(char *name)
{
	XPPParamBlock pb;
	OSErr err;
	char buf[33], *cbuf;
	
	pb.XCALL.xppTimeout = 3;
	pb.XCALL.xppRetry = 4;
	pb.XCALL.zipBuffPtr = (Ptr)buf;
	pb.XCALL.zipInfoField[0] = 0;
	pb.XCALL.zipInfoField[1] = 0;
	err = GetMyZone(&pb, 0);
	if (!err) {
		cbuf = p2cstr(buf);
		strcpy(name, cbuf);
	}
	return err;
}

//  This routine sends a game_info request to each registered Descent net game
//  in the given zone.  We will look up the address for the NBP type, then send
//  them our packet.

void appletalk_send_game_info( ubyte *data, int size, char *zone_name)
{
	OSErr err;
	ubyte entity_buf[99], *return_buf;
	MPPParamBlock pb;
	int i, lookup_count = 0;
	EntityName entity;
	AddrBlock addr;
	
// setup the nbp_name variable to get all of the names of the descent nbp type

	return_buf = (ubyte *)malloc(104 * MAX_APPLETALK_GAMES);		// 104 bytes maximum per entity * 16 maximum games.
	if (return_buf == NULL)
		return;
		
try_again:
	NBPSetEntity((Ptr)(entity_buf), "\p=", NBP_TYPE_NAME, zone_name);
	pb.NBP.ioCompletion = NULL;
	pb.NBP.interval = 0x07;
	pb.NBP.count = 0x3;
	pb.NBP.nbpPtrs.entityPtr = (Ptr)entity_buf;
	pb.NBP.parm.Lookup.retBuffPtr = (Ptr)return_buf;
	pb.NBP.parm.Lookup.retBuffSize = (104 * MAX_APPLETALK_GAMES);
	pb.NBP.parm.Lookup.maxToGet = MAX_APPLETALK_GAMES;
	do {
		err = PLookupName(&pb, 0);
	} while ( (err == tooManyReqs) && (lookup_count++ < 3) );

	if (err) {
		free(return_buf);
		return;
	}
	for (i = 0; i < pb.NBP.parm.Lookup.numGotten; i++) {
		if ( ( err = NBPExtract((Ptr)return_buf, pb.NBP.parm.Lookup.numGotten, (i+1), &entity, &addr)) == noErr) {
			appletalk_send_packet_data(data, size, addr.aNode, addr.aNet, addr.aSocket);
		}
	}
	free(return_buf);
}

void appletalk_send_broadcast_packet_data( ubyte *data, int datasize )
{
	appletalk_send_packet_data(data, datasize, 0xff, my_address.aNet, appletalk_write_socket);
}

