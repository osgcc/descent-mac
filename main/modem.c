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
 * $Source: Smoke:miner:source:main::RCS:modem.c $
 * $Revision: 1.20 $
 * $Author: allender $
 * $Date: 1995/11/14 14:26:07 $
 * 
 * Modem support code
 *
 * $Log: modem.c $
 * Revision 1.20  1995/11/14  14:26:07  allender
 * fixed memory leak with conn_handle being reallocated
 * each time modem/serial game was started
 *
 * Revision 1.19  1995/11/13  13:40:03  allender
 * reset contest variable on modem game start
 *
 * Revision 1.18  1995/11/08  17:15:55  allender
 * fix horrendous bug which may affect registered in which
 * during modem play, player num gets set to the same value
 * when playing against a PC
 *
 * Revision 1.17  1995/11/08  15:13:50  allender
 * new faster(?) serial port reading/writing code for mac
 *
 * Revision 1.16  1995/11/03  12:54:46  allender
 * shareware changes
 *
 * Revision 1.15  1995/10/31  10:21:24  allender
 * shareware stuff
 *
 * Revision 1.14  1995/10/24  18:10:53  allender
 * save backdrop and restore when cmchoose is cancelled
 *
 * Revision 1.13  1995/10/24  11:51:51  allender
 * change hang up modem text to close link text
 *
 * Revision 1.12  1995/10/17  13:18:40  allender
 * com menu now has close box
 *
 * Revision 1.11  1995/10/15  16:04:18  allender
 * fixed up modem menus
 *
 * Revision 1.10  1995/10/13  14:42:55  allender
 * *** empty log message ***
 *
 * Revision 1.9  1995/10/12  17:35:50  allender
 * make CMChoose dialog work on secondary monitor
 *
 * Revision 1.8  1995/09/18  17:01:55  allender
 * CMAccept must *accept* the connection!!! DOH!
 *
 * Revision 1.7  1995/09/13  08:49:49  allender
 * modem stuff working a little better?
 *
 * Revision 1.6  1995/09/12  15:46:52  allender
 * fixed motorola compiler error
 *
 * Revision 1.5  1995/09/12  14:19:52  allender
 * new connection oriented tool stuff
 *
 * Revision 1.4  1995/09/05  14:06:17  allender
 * checkpoint again
 *
 * Revision 1.3  1995/06/25  22:06:15  allender
 * macintosh checkpoint
 *
 * Revision 1.2  1995/06/08  12:55:14  allender
 * start of macintosh port.  most ctb stuff in and working (except for modem)
 *
 * Revision 1.1  1995/05/16  15:27:56  allender
 * Initial revision
 *
 * Revision 2.9  1995/04/09  14:43:20  john
 * Took out mem-overwrite error when > 25 char phone numbers.
 * 
 * Revision 2.8  1995/04/06  12:13:36  john
 * Made phone numbers be 32 characters max.
 * 
 * Revision 2.7  1995/03/31  14:16:33  john
 * Mode phone numbers 30 chars long.
 * 
 * Revision 2.6  1995/03/30  16:39:44  john
 * Incread phone numbers to 25 characters.
 * 
 * Revision 2.5  1995/03/30  16:04:49  john
 * Increased modem number length.
 *  
 * 
 * Revision 2.4  1995/03/29  15:33:23  john
 * Took out RTS/CTS handshaking. Made it enabled with -RTSCTS.
 * 
 * Revision 2.3  1995/03/21  14:41:10  john
 * Ifdef'd out the NETWORK code.
 * 
 * Revision 2.2  1995/03/06  16:47:50  mike
 * destination saturn
 * 
 * Revision 2.1  1995/03/02  15:58:31  john
 * Made menu support modex.
 * 
 * Revision 2.0  1995/02/27  11:32:34  john
 * New version 2.0, which has no anonymous unions, builds with
 * Watcom 10.0, and doesn't require parsing BITMAPS.TBL.
 * 
 * Revision 1.157  1995/02/15  15:35:12  john
 * Added code to support modem tracking of kills during endlevel..
 * 
 * Revision 1.156  1995/02/15  15:27:16  john
 * Mode modem code work with kills after you leave mine.
 * 
 * Revision 1.155  1995/02/12  19:53:04  rob
 * Fixed up com flush.
 * 
 * Revision 1.154  1995/02/11  17:13:25  rob
 * Took out code fill stuff.
 * 
 * Revision 1.153  1995/02/11  14:26:25  rob
 * Added support for invul. controlcen.
 * 
 * Revision 1.152  1995/02/09  02:59:44  mike
 * check code for 00066xxx bugs.
 * 
 * Revision 1.151  1995/02/08  19:18:56  rob
 * Took out show IDs on HUD option.
 * 
 * Revision 1.150  1995/02/08  11:30:29  rob
 * Fixed some pretty minor bugs.
 * 
 * Revision 1.149  1995/02/07  20:39:54  rob
 * Added new modem game options for hud id's and automap show.
 * 
 * Revision 1.148  1995/02/06  18:42:09  rob
 * Removed debugging crap.
 * 
 * Revision 1.147  1995/02/06  18:17:17  rob
 * Fixed bug in killed tallys in modem game.
 * 
 * Revision 1.146  1995/02/05  17:04:29  rob
 * Removed performance monitoring debug message.
 * 
 * Revision 1.145  1995/02/05  17:02:48  rob
 * Speeding up cooperative/robo-anarchy modes.
 * 
 * Revision 1.142  1995/02/03  18:09:40  rob
 * Small fixes to modem setup menu..
 * 
 * Revision 1.141  1995/02/03  11:12:15  rob
 * Fixed a bug (again).  Somehow last checkin got lost.
 * 
 * Revision 1.140  1995/02/02  22:06:20  rob
 * Removed a function frm shareware.
 * 
 * Revision 1.139  1995/02/01  23:20:32  rob
 * Put baud rate in connect subtitle.
 * 
 * Revision 1.138  1995/01/30  21:22:11  rob
 * Fixed bug in sync pack memcpy len.
 * 
 * Revision 1.137  1995/01/30  21:18:31  rob
 * Simplified mission loading support.
 * 
 * Revision 1.136  1995/01/30  18:32:08  rob
 * Added include of multibot.h
 * 
 * Revision 1.135  1995/01/30  17:16:04  rob
 * Added new system for sending robots positions in modem games.
 * 
 * Revision 1.134  1995/01/30  15:29:44  rob
 * Localizing.
 * 
 * Revision 1.133  1995/01/29  15:20:21  rob
 * Fixed a bug in secret level sequencing for modem games.
 * 
 * Revision 1.132  1995/01/24  15:48:51  rob
 * fixed error dialog.
 * 
 * Revision 1.131  1995/01/23  18:51:59  rob
 * Added RTS/CTS to null-modem games to help IHHD folks.
 * Fixed a bad assert.
 * Added support for user-written mission files.
 * 
 * Revision 1.130  1995/01/23  16:01:36  rob
 * More reliable syncing.
 * Added mission selection.
 * 
 * Revision 1.129  1995/01/20  22:47:35  matt
 * Mission system implemented, though imcompletely
 * 
 * Revision 1.128  1995/01/19  18:18:05  rob
 * Fixed kill list display.
 * 
 * Revision 1.127  1995/01/19  16:33:48  rob
 * removed ambigous variable name in check_message.
 * 
 * Revision 1.126  1995/01/19  11:56:38  rob
 * Take out Int3 that could never get hit.
 * 
 * Revision 1.125  1995/01/18  19:01:46  rob
 * Added new asserts to check for proper game staus.
 * 
 * 
 * Revision 1.124  1995/01/18  15:39:25  rob
 * Fixed title of serial menu.
 * 
 * Revision 1.123  1995/01/18  11:54:23  rob
 * Fixing a bug with connect status.
 * 
 * Revision 1.122  1995/01/17  22:16:07  rob
 * Changed timer calls.
 * 
 * Revision 1.121  1995/01/17  13:58:31  rob
 * Fixed problem with not allowing non-anarchy modes in registered.
 * 
 * Revision 1.120  1995/01/15  15:46:18  rob
 * Fixed lost character on serial menu messages.
 * 
 * Revision 1.119  1995/01/12  22:03:15  rob
 * Added sound cue when connection is established.
 * 
 * Revision 1.118  1995/01/12  11:42:05  john
 * added better UART detection.
 * /.
 * Works under OS/2 and DOS.
 * 
 * 
 */

#ifdef NETWORK

#define DOS4G

#pragma off (unreferenced)
static char rcsid[] = "$Id: modem.c 1.20 1995/11/14 14:26:07 allender Exp $";
#pragma on (unreferenced)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include <Types.h>
#include <Connections.h>
#include <CommResources.h>
#include <Traps.h>
#include <MixedMode.h>

#include "game.h"
#include "scores.h"
#include "modem.h"
#include "object.h"
#include "player.h"
#include "laser.h"
#include "error.h"
#include "collide.h"
#include "endlevel.h"
#include "network.h"
#include "mono.h"
#include "gauges.h"
#include "newmenu.h"
#include "menu.h"
#include "gamesave.h"
#include "netmisc.h"
#include "fuelcen.h"
#include "multi.h"
#include "timer.h"
#include "text.h"
#include "pcx.h"
#include "palette.h"
#include "sounds.h"
#include "digi.h"
#include "multibot.h"
#include "args.h"
#include "key.h"
#include "config.h"

#include "byteswap.h"
#include "macsys.h"

#define MIN_COMM_GAP 8000
#define INIT_STRING_LEN 20
#define LEN_PHONE_NUM_OLD 15
#define LEN_PHONE_NUM 	32
#define LEN_PHONE_NAME 12
#define NUM_PHONE_NUM 8

#define MODEM_PORT 		1
#define PRINTER_PORT 	2

#define DIAL_TONE		1
#define DIAL_PULSE		2

// How many times to repeat 'reliable' messages

#define EOR_MARK 0xaa

#define COM_PROCESS_NORMAL 0
#define COM_PROCESS_ENDLEVEL 1
#define COM_PROCESS_SYNC 2
#define COM_PROCESS_MENU 3

#define SELECTION_STARTGAME		1
#define SELECTION_NO_START			2
#define SELECTION_YES_START		3
#define SELECTION_STARTGAME_ABORT	4
#define SELECTION_CLOSE_LINK		5

#define MODEM_TOOL_NAME "\pApple Modem Tool"
#define SERIAL_TOOL_NAME "\pSerial Tool"

ConnHandle conn_handle = NULL;
static char comm_initialized = 0;
ConnectionCompletionUPP completion_proc;

#ifdef MAC_SHAREWARE
extern ubyte contest_active;			// for silly little contest from MacPlay
#endif

//	Code to support modem/null-modem play

// Program determined variables for serial play

typedef struct com_sync_pack {
	char type;
	byte proto_version;
	long sync_time;
	byte level_num;
	ubyte difficulty;
	ubyte game_mode;
	char callsign[CALLSIGN_LEN+1];
	short kills[2];
	ushort seg_checksum;
#ifndef MAC_SHAREWARE
	byte sync_id;
	char mission_name[9];
	short killed;
	ubyte game_flags;
#endif
	char	dummy[3]; // Extra space for checksum & sequence number
} com_sync_pack;

int serial_active;
int com_baud_rate = 0;
//--unused-- int sync_time = 0;
int com_open = 0;
int got_sync = 0;
int other_got_sync = 0;
static long synccnt;
static ubyte rx_seqnum = 0xff;
static ubyte tx_seqnum = 0;
int OtherPlayer; // Player num for modem opponent
int com_process_mode = COM_PROCESS_NORMAL;
int master = -1; // Am I the master or is the other guy the master?
com_sync_pack my_sync, other_sync;
int start_level_num;

int com_custom_port = -1;
int com_custom_irq = -1;
int com_custom_base = -1;

int other_menu_choice = 0;

int chars_sent = 0;

// Com buffers

static unsigned char syncbuffer[MAX_MULTI_MESSAGE_LEN+4];
static unsigned char sendbuf[MAX_MULTI_MESSAGE_LEN+4]; // +4 because of +1 for null and +3 for checksum/sequence
static unsigned char mac_sendbuf[MAX_MULTI_MESSAGE_LEN*2+4];	// for macintosh only to create buffer to send all at once

// Serial setup variables

int com_port_num = -1;
int com_speed = -1;
char modem_init_string[INIT_STRING_LEN+1];
char phone_name[NUM_PHONE_NUM][LEN_PHONE_NAME+1];
char dial_type = 1;

fix  SerialLastMessage = 0;

/* Function prototypes for functions not exported through modem.h */

void com_start_game(void);
void tool_dialout(void);
void tool_listen(void);
int com_sync(int id);
void com_sync_poll(int nitem, newmenu_item *menus, int *key, int citem);

void com_send_choice(int choice);
void add_phone_number( char * src, char * num );
void serial_link_start(void);
void serial_sync_abort(int val);
void com_process_sync(char *buf, int len);

#if !defined(NDEBUG) && !defined(NMONO)
void
com_dump_string(char *string)
{
	mprintf((0, "%s\n", string));
}
#else
#define com_dump_string()
#endif

// macintosh completion routines for communcations stuff

void connect_completion(ConnHandle conn)
{
	if ((*conn)->errCode == noErr)
		CMSetRefCon(conn, 1);
	else
		CMSetRefCon(conn, -1);
	return;
}

int GetConnectionStatus()
{
	CMBufferSizes sizes;
	CMStatFlags flags;
	CMErr err;
	
	if (!conn_handle)
		return 0;
		
	err = CMStatus(conn_handle, sizes, &flags);
	if (err)
		return 0;
	return flags;
}

// speciailized macintosh routine to initialize the communications toolbox.

void comm_close()
{
	if (!comm_initialized)
		return;
		
	comm_initialized = 0;
		
	if (conn_handle == NULL)
		return;
		
	CMClose(conn_handle, 0, NULL, -1, 1);
	CMDispose(conn_handle);
	DisposeRoutineDescriptor(completion_proc);
	conn_handle = NULL;
}

int comm_init()
{
	OSErr err;

	if (NGetTrapAddress(_CommToolboxDispatch, OSTrap) == NGetTrapAddress(_Unimplemented, OSTrap))
		return -1;
		
	if ((err = InitCRM()) != crmNoErr)
		return err;
	if ((err = InitCTBUtilities()) != ctbuNoErr)
		return err;
	if ((err = InitCM()) != cmNoErr)
		return err;

	comm_initialized = 1;
	atexit(comm_close);
}

void
com_disable()
{
	// close the com port and free associated structures.

	OSErr err;
	CMBufferSizes sizes;
	CMStatFlags flags;

	show_boxed_message("Closing connection");
	CMAbort(conn_handle);			// in case of pending open	
	err = CMClose(conn_handle, 0, NULL, -1, 1);

	if ( (err != noErr) && (err != cmNotOpen) ) {
		Int3();
		#ifndef NDEBUG
		mprintf((1, "PortClose returned %d!\n", err));
		#endif
	}
	clear_boxed_message();
	
	com_open = 0;

	master = -1;

	#ifndef NDEBUG
	mprintf((0, "Com port released.\n"));
	#endif
}

void
com_abort(void)
{
	// this is the safest way to get out of some modem/serial negotiation
	// and back to the main menu.  Use this whenever this have gone too far
	// awry to repair.

	com_disable();

	N_players = 0;

	change_playernum_to(0);

	Viewer = ConsoleObject = &Objects[0];
	Game_mode = GM_GAME_OVER; // Force main menu selection
}

void
com_hangup(void)
{
	// Close the serial link

	com_send_choice(SELECTION_CLOSE_LINK);
	com_abort();
}

void
com_carrier_lost(void)
{
	// Carrier lost, inform and abort

	if (multi_in_menu > 0)
	{
		multi_leave_menu = 1;
		return;
	}

	Function_mode = FMODE_MENU;

	multi_quit_game = 1;
	nm_messagebox(NULL, 1, TXT_OK, TXT_CARRIER_LOST);
	com_abort();
}

extern ubyte cockpit_mode_save; // From object.c
extern int old_cockpit_mode; // From game.c

com_reset_game(void)
{
	int i;

	// Reset various parameters before starting a new game
	
	N_players = 2;

	for (i = 0; i < N_players; i++)
	{
		Players[i].connected = 1;
	}

//	master = -1;

	multi_new_game(); // Reset kill list, among other things
	Fuelcen_control_center_destroyed = 0;
	Endlevel_sequence = 0;
	
	// Yes, this really IS as ugly as it gets, kids...

	if (Cockpit_mode == CM_LETTERBOX)
	{
		select_cockpit(cockpit_mode_save);
	}
	else if (Cockpit_mode == CM_REAR_VIEW)
	{
		select_cockpit(old_cockpit_mode);
	}
}

void
serial_leave_game(void)
{
	#ifndef NDEBUG
	mprintf((0, "Called serial_leave_game.\n"));
	#endif
//	com_abort();
	serial_sync_abort(0); // Just in case the other guy is in sync mode
	Game_mode |= GM_GAME_OVER;
	Function_mode = FMODE_MENU;
}

com_send_ptr(unsigned char *ptr, int len)
{
	register	int count;
	int dcount;
	unsigned char dat;
	long num_bytes;
	OSErr err;
//	CMFlags flags = cmFlagsEOM;
	CMFlags flags = 0;

	for (count = 0, dcount = 0, dat=ptr[0]; count < len; dat=ptr[++count])
	{
		mac_sendbuf[dcount++] = dat;
		if (dat == EOR_MARK)
			mac_sendbuf[dcount++] = dat;
	}
	mac_sendbuf[dcount++] = EOR_MARK;
	mac_sendbuf[dcount++] = 0;
	err = CMWrite(conn_handle, mac_sendbuf, &dcount, cmData, 0, nil, 0, flags);
	CMIdle(conn_handle);

#if 0		// old way
	for (count = 0, dat=ptr[0]; count < len; dat=ptr[++count])
	{
//		WriteChar(com_port, dat);
		num_bytes = 1;
		err = CMWrite(conn_handle, &dat, &num_bytes, cmData, 0, nil, 0, flags);
		if (dat == EOR_MARK) {
			num_bytes = 1;
			err = CMWrite(conn_handle, &dat, &num_bytes, cmData, 0, nil, 0, flags);	// double inband endmarkers
		}
	}
	dat = EOR_MARK;
	num_bytes = 1;
	err = CMWrite(conn_handle, &dat, &num_bytes, cmData, 0, nil, 0, flags);
	dat = 0;
	num_bytes = 1;
	err = CMWrite(conn_handle, &dat, &num_bytes, cmData, 0, nil, 0, flags);
	CMIdle(conn_handle);
#endif
}

void
com_send_data(char *ptr, int len, int repeat)
{
	int i;

	// Take the raw packet data specified by ptr and append the sequence
	// number and checksum, and pass it to com_send_ptr

	if (!conn_handle)
		return;

	if (Game_mode & GM_MODEM)
	{
//		i = GetCd(com_port);
//		if (i == 0)
		if ( !(GetConnectionStatus() & cmStatusOpen) )
			mprintf((0, "CARRIER LOST!\n"));
	}
	
	len += 3; // Checksum data is 3 bytes

	*(ubyte *)(ptr+(len-3)) = (tx_seqnum+1)%256;
	tx_seqnum = (tx_seqnum+1)%256;

	*(ushort *)(ptr+(len-2)) = swapshort(netmisc_calc_checksum(ptr, len-2));

	com_send_ptr(ptr, len);
	if (repeat)
		for (i = 0; i < repeat; i++)
			com_send_ptr((unsigned char *)ptr, len);
}

void
com_flush()
{
	// Get rid of all waiting data in the serial buffer
	OSErr err;
	int i = -1;
	int num_read;
	unsigned char c;
	CMFlags flags = 0;

	if (!com_open)	
		return;

	mprintf((0, "COM FLUSH:"));

	err = cmNoErr;
	while (err == cmNoErr) {
		i++;
		num_read = 1;
		err = CMRead(conn_handle, &c, &num_read, cmData, 0, nil, 0, &flags);
	}
//	while (ReadCharTimed(com_port, 100) >= 0)
//		i++;
	mprintf((0, "%d characters.\n", i));
}

#define SERIAL_IDLE_TIMEOUT F1_0*10

void
com_do_frame(void)
{
	static fix last_comm_time = 0;
	static int last_pos_skipped = 0;
	int rval = 0;

	if (Endlevel_sequence || (com_process_mode==COM_PROCESS_ENDLEVEL)) {	// Only recieve during endlevel
		int old_Endlevel_sequence = Endlevel_sequence;
		Endlevel_sequence = 1;
		com_process_input();
		Endlevel_sequence = old_Endlevel_sequence;
		return;
	}

	last_comm_time += FrameTime;

	if ((last_comm_time > MIN_COMM_GAP) || Network_laser_fired)
	{
#ifndef MAC_SHAREWARE
		if ((Game_mode & GM_MULTI_ROBOTS) && !last_pos_skipped) {
			rval = multi_send_robot_frame(0);
		}
		if (rval && !Network_laser_fired)
		{
			last_pos_skipped = 1;
			goto skippos;
		}
#endif
		last_pos_skipped = 0;
		multi_send_position(Players[Player_num].objnum);
		multi_send_fire(); // Will return w/o sending if we haven't fired

skippos:
//		mprintf((0, "%d chars sent, %f cps.\n", chars_sent, f2fl(fixdiv((chars_sent*F1_0),last_comm_time)) ));
		chars_sent = 0;
		last_comm_time = 0;
	}
//	else
//		multi_send_robot_frame(1);

	com_process_input();

	if (!Fuelcen_control_center_destroyed && (Function_mode == FMODE_GAME) && (SerialLastMessage+SERIAL_IDLE_TIMEOUT < GameTime))
	{
		SerialLastMessage = 0x7fffffff-SERIAL_IDLE_TIMEOUT; // Give no further warnings until next message arrives!
		nm_messagebox(TXT_WARNING, 1, TXT_OK, TXT_CONNECT_LOST, Players[OtherPlayer].callsign);
	}

	return;
}

int
com_check_message(unsigned char *checkbuf, int len)
{
	ushort check;
	int seqnum;

	if (len < 4)
	{
		#ifndef NDEBUG
		mprintf((0, "message type %d too short to be a real message!\n", checkbuf[0]));
		#endif
		goto error;
	}

	if (checkbuf[0] > MULTI_MAX_TYPE)
	{
		#ifndef NDEBUG
		mprintf((1, "message type %d out of range.\n", checkbuf[0]));
		#endif
		goto error;
	}

	if ( (len-3) != message_length[checkbuf[0]])
	{
		#ifndef NDEBUG
		mprintf((1, "message length %d != %d.\n", len-3, message_length[checkbuf[0]]));
		#endif
		goto error;
	}

	check = swapshort(netmisc_calc_checksum(checkbuf, len-2));
	if (check != *(ushort *)(checkbuf+(len-2)))
	{
		#ifndef NDEBUG
		mprintf((0, "error in message type %d, length %d, checksum %d != %d\n", checkbuf[0], len, check, *(ushort *)(checkbuf+(len-2))));	
		#endif
		goto error;
	}

	seqnum = checkbuf[(len-3)];

	if (seqnum == rx_seqnum)
	{
		return -1;
	}
	
	if (seqnum != (rx_seqnum+1)%256)
	{
		#ifndef NDEBUG
		mprintf((0, "Warning, missed 1 or more messages.\n"));	
		#endif
	}
	rx_seqnum = seqnum;
//	mprintf((0, "message type %d len %d OK!\n", checkbuf[0], len));
	return 0; 

error:
//	mprintf((1,"Line status: %d.\n", GetLineStatus(com_port)));
//	ClearLineStatus(com_port);
	return -1;
}
	
void
com_process_menu(unsigned char *buf, int len)
{
	char text[80];

	len = len;

	mprintf((0, "com_process_menu: type %d.\n", buf[0]));

	switch(buf[0])
	{
		case MULTI_MESSAGE:
#ifndef MAC_SHAREWARE
			sprintf(text, "%s %s\n'%s'", Players[OtherPlayer].callsign, TXT_SAYS, buf+2);
#else
			sprintf(text, "%s %s\n'%s'", Players[OtherPlayer].callsign, TXT_SAYS, buf+3);
#endif
			hide_cursor();
			nm_messagebox(NULL, 1, TXT_OK, text);
			show_cursor();
			break;
		case MULTI_MENU_CHOICE:
			other_menu_choice = buf[1];
			mprintf((0, "Other menu choice = %d.\n", other_menu_choice));
			break;
		case MULTI_BEGIN_SYNC:
			// If we get a sync at the menu, send an abort sync, we're not ready yet!
			serial_sync_abort(0);
			break;
	}
}

int
com_getmessage(int *len)
{
	int min_length, dcount, i;
	register OSErr err;
	CMFlags flags;
	long num_read;
	unsigned char c;
	static int eor_recv = 0;

	// return values:
	//  -1 = Nothing in buffer
 	//  -2 = End of record

	if (!com_open)
		return(-1);

	if ( *len == 0 ) {			// read a new com message
		num_read = 1;
		err = CMRead(conn_handle, &c, &num_read, cmData, 0, nil, 0, &flags);
		if ( err == cmTimeOut)
			return -1;

		min_length = message_length[c] + 4;		// 5 extra bytes at end of real multi message -- but already read first one!
		dcount = 0;
		mac_sendbuf[dcount++] = c;
		err = CMRead(conn_handle, &(mac_sendbuf[1]), &min_length, cmData, 0, nil, 0, &flags);
		dcount += min_length;
	
		for (i = 0; i < dcount; i++) {
			c = mac_sendbuf[i];
			if ((c == EOR_MARK) || eor_recv)
			{
				if (!eor_recv) {
					i++;
					c = mac_sendbuf[i];
				}
				if (i == dcount)
				{
					eor_recv = 1;
					return(-1);
				}
				else if (c == EOR_MARK) 
				{
					eor_recv = 0;
					syncbuffer[*len] = c;
					(*len)++;
				}
				else
				{
#ifndef NDEBUG
					if (c != 0) {
						mprintf((0, "EOR followed by unexpected value %d.\n", c));
					}
#endif
					eor_recv = 0;
					return(-2);							
				}
			}
			else {
				syncbuffer[*len] = c;
				(*len)++;
			}
		}
	}
	
// if we get here, then we haven't read in the EOR_MARK followed by 0 yet.

	while (1) {				// we will return from middle of function if timeout or done.	
		num_read = 1;
		err = CMRead(conn_handle, &c, &num_read, cmData, 0, nil, 0, &flags);
	
		if (err == cmTimeOut) {
			return (-1);
		}
	
		if ((c == EOR_MARK) || eor_recv)
		{
			if (!eor_recv) {
				num_read = 1;
				err = CMRead(conn_handle, &c, &num_read, cmData, 0, nil, 0, &flags);
			}
			if (err == cmTimeOut)
			{
				eor_recv = 1;
				return(-1);
			}
			else if (c == EOR_MARK) 
			{
				eor_recv = 0;
				syncbuffer[*len] = c;
				(*len)++;
			}
			else
			{
#ifndef NDEBUG
				if (c != 0) {
					mprintf((0, "EOR followed by unexpected value %d.\n", c));
				}
#endif
				eor_recv = 0;
				return(-2);							
			}
		}
		else {
			syncbuffer[*len] = c;
			(*len)++;
		}
	}

#if 0			// old way
	num_read = 1;
	err = CMRead(conn_handle, &c, &num_read, cmData, 0, nil, 0, &flags);

	if (err == cmTimeOut)
		return (-1);

	if ((c == EOR_MARK) || eor_recv)
	{
		if (!eor_recv) {
			num_read = 1;
			err = CMRead(conn_handle, &c, &num_read, cmData, 0, nil, 0, &flags);
		}

		if (err == cmTimeOut)
		{
//			Assert(eor_recv == 0);
			eor_recv = 1;
			return(-1);
		}
		else if (c == EOR_MARK) 
		{
			eor_recv = 0;
			return(EOR_MARK); // Doubled EOR returns the character
		}
		else
		{
#ifndef NDEBUG
			if (c != 0) {
				mprintf((0, "EOR followed by unexpected value %d.\n", c));
			}
#endif
			eor_recv = 0;
			return(-2);							
		}
	}
	return((int)c);
#endif
}

void
com_process_input(void)
{
	// Read all complete messages from the serial buffer and process
	// the contents.  Messages are read into global array snycbuffer.

	static int len = 0;
	int entry_com_mode = com_process_mode;
	register	int dat;

	if (!conn_handle)
		return;

nextmessage:
//	if (Game_mode & GM_MODEM)
	if ( com_open )
	{
//		if (!GetCd(com_port))
		if (!(GetConnectionStatus() & cmStatusOpen))
			com_carrier_lost();
	}

	if (!conn_handle) {
		if (!multi_in_menu) {
			multi_quit_game = 1;
		}
		else {
			multi_leave_menu = 1;
		}
	}

	if (com_process_mode != entry_com_mode)
	{
//		mprintf((0, "Exiting com_process_input due to mode switch.\n"));
		return;
	}

	dat = com_getmessage(&len);
#if 0
	while ( (len <= MAX_MULTI_MESSAGE_LEN) && (dat = com_getchar()) > -1) // Returns -1 when serial pipe empty
	{
		syncbuffer[len++] = dat;
	}
#endif

	if ((dat == -2) || (len > MAX_MULTI_MESSAGE_LEN)) // Returns -2 when end of message reached
	{
		// End of message
		SerialLastMessage = GameTime;

		if (!com_check_message(syncbuffer, len))
		{
			switch(com_process_mode)
			{
				case COM_PROCESS_NORMAL:
				case COM_PROCESS_ENDLEVEL:
					multi_process_data(syncbuffer, len); break;
				case COM_PROCESS_MENU:
					if (!Endlevel_sequence) com_process_menu(syncbuffer, len); break;
				case COM_PROCESS_SYNC:
					if (!Endlevel_sequence) com_process_sync(syncbuffer, len); break;
				default:
					Int3(); // Bad com_process_mode switch set!
			}
		}
		len = 0;
		goto nextmessage;
	}
	if (dat == -3) // Returns -3 when carrier lost
	{
		com_abort();
		len = 0;
	}
	return ;
}

int
com_connect()
{
	my_sync.type = MULTI_BEGIN_SYNC;
	my_sync.difficulty = 0;
	memcpy(my_sync.callsign, Players[Player_num].callsign, CALLSIGN_LEN+1);
	my_sync.seg_checksum = 0;
	my_sync.game_mode = Game_mode;
	my_sync.level_num = 0;
								 
	#ifndef NDEBUG
	mprintf((0, "com_connect()\n"));
	#endif

	if(com_sync(-1))
		return(-1); // Failure in sync

	if (master == -1)
	{
		#ifndef NDEBUG
		mprintf((0, "My rand = %d, other rand = %d.\n", my_sync.sync_time, other_sync.sync_time));
		#endif

		// Figure out who is the master
		if (swapint(my_sync.sync_time) > swapint(other_sync.sync_time))
		{
			mprintf((0, "Swtiching player to master.\n"));
			master=1;
			change_playernum_to(0);
		}
		else if (swapint(my_sync.sync_time) < swapint(other_sync.sync_time))
		{
			mprintf((0, "Switching player to slave.\n"));
			master = 0;
			change_playernum_to(1);
		}
		else
			return(-1);  // Didn't sync properly, try again
	}
	
	// Copy the remote sync data into local variables
	
	OtherPlayer = (Player_num+1)%2;
	mprintf((0, "Other player is #%d.\n", OtherPlayer));
	memcpy(Players[OtherPlayer].callsign, other_sync.callsign, CALLSIGN_LEN+1);

	return(0);
}

#define ADD_ITEM(t,value,key)  do { m[num_options].type=NM_TYPE_MENU; menu_choice[num_options]=value; m[num_options].text=t; num_options++; } while (0)

#define MENU_MODEM_CALL				0
#define MENU_MODEM_ANSWER			1
#define MENU_SERIAL_LINK_START 	2
#define MENU_SERIAL_SETUP 			3
#define MENU_MODEM_HANGUP			4
#define MENU_SERIAL_GAME_START	5
#define MENU_SEND_MESSAGE			6

void
com_menu_poll(int nitems, newmenu_item *menus, int *key, int citem)
{
	// Watch the serial stream if we are connected and take appropriate actions

	int old_game_mode;

	menus = menus;
	citem = citem;
	nitems = nitems;

	if (! ( (Game_mode & GM_SERIAL) || (Game_mode & GM_MODEM) ) )
		return;

	com_process_mode = COM_PROCESS_MENU;
	old_game_mode = Game_mode;
	other_menu_choice = 0;	

	com_process_input();

	if ((old_game_mode != Game_mode) || other_menu_choice || (com_process_mode != COM_PROCESS_MENU))
		*key = -2;
	if (multi_leave_menu)
		*key = -2;
}

void
com_send_choice(int choice)
{
	sendbuf[0] = (char)MULTI_MENU_CHOICE;
	sendbuf[1] = (char)choice;

	com_send_data(sendbuf, 2, 1);
}

void
com_ready_to_start(void)
{
	newmenu_item m[2];
	int choice;

	m[0].type = m[1].type = NM_TYPE_MENU;
	m[0].text = TXT_YES;
	m[1].text = TXT_NO;

	choice = newmenu_do1(NULL, TXT_READY_DESCENT, 2, m, com_menu_poll, 0 );
	if (choice == 0)
	{
		// Yes
		com_send_choice(SELECTION_YES_START);
		other_menu_choice = SELECTION_STARTGAME;
		com_start_game();
	}		
	else 
	{
		com_send_choice(SELECTION_NO_START);
	}
}

void
com_process_other_menu_choice(void)
{
	if (other_menu_choice == SELECTION_STARTGAME)	
		com_ready_to_start();
	else if (other_menu_choice == SELECTION_CLOSE_LINK) 
	{
		nm_messagebox(NULL, 1, TXT_OK, TXT_CLOSED_LINK);
		com_hangup();
	}
}

#define SUBTITLE_LEN 120

void
com_main_menu(void)
{
	newmenu_item m[10];
	int menu_choice[10];
	int num_options = 0;
	int choice=0;
	int old_game_mode;
	char subtitle[SUBTITLE_LEN];
	int pcx_error, tool_id;
	OSErr err;
	Point pnt;
	CMBufferSizes csizes;
	CMRecFlags cflags;
	grs_canvas *save_canvas;

	if (!comm_initialized) {
		err = comm_init();
		if (err) {
			nm_messagebox(NULL, 1, TXT_OK, "Error Initializing Communications\nToolbox.");
			return;
		}
	}
	
// new connection handle

	if (conn_handle == NULL) {

//		if (config_last_ctb_tool)
//			tool_id = config_last_ctb_tool;
//		else
			tool_id = CMGetProcID(MODEM_TOOL_NAME);
		if (tool_id == -1) {
			nm_messagebox(TXT_ERROR, 1, TXT_OK, "Couldn't locate desired communication\ntool  Check extensions folder.");
			return;
		}
		config_last_ctb_tool = tool_id;
		cflags = cmNoMenus | cmQuiet;
//		cflags = cmNoMenus;
		csizes[0] = csizes[1] = csizes[2] = csizes[3] = csizes[4] = csizes[5] = 0;
		conn_handle = CMNew(tool_id, cflags, csizes, 0, 0);
		if (conn_handle == NULL) {
			nm_messagebox(TXT_ERROR, 1, TXT_OK, "Error getting connection handle.\nPlease free memory and rerun Descent.");
			return;
		}
//  put in the old configuration string if any
		CMSetConfig(conn_handle, config_last_ctb_cfg);

		completion_proc = NewConnectionCompletionProc(connect_completion);
	}

// get a new connection handle.  We will supply 'Apple Modem Tool' by default here...check the
// user prefs file to get all of the saved values.

	if ( !((Game_mode & GM_SERIAL) || (Game_mode & GM_MODEM)) ) {
		char *cfg_str;

		pnt.h = (*GameMonitor)->gdRect.left + 40;
		pnt.v = (*GameMonitor)->gdRect.top + 40;

// save off current screen to offscreen buffer
		save_canvas = grd_curcanv;
		gr_set_current_canvas(NULL);
		gr_bm_bitblt( 640, 480, 0, 0, 0, 0, &(grd_curcanv->cv_bitmap), &(VR_offscreen_buffer->cv_bitmap) );
		gr_set_current_canvas(save_canvas);

		key_close();
		show_cursor();
		err = CMChoose(&conn_handle, pnt, NULL);
		hide_cursor();
		key_init();
			
		if ( (err == chooseDisaster ) || (err == chooseFailed) || (err == chooseAborted) || (err == chooseCancel) ) {
			save_canvas = grd_curcanv;
			gr_set_current_canvas(NULL);
			gr_bm_bitblt( 640, 480, 0, 0, 0, 0, &(VR_offscreen_buffer->cv_bitmap), &(grd_curcanv->cv_bitmap) );
			gr_set_current_canvas(save_canvas);
			return;
		}
		
		cfg_str = CMGetConfig(conn_handle);
		strcpy(config_last_ctb_cfg, cfg_str);
		WriteConfigFile();
		if (cfg_str)
			free(cfg_str);
	}	

	setjmp(LeaveGame);

	gr_set_current_canvas(NULL);
	pcx_error = pcx_read_bitmap(Menu_pcx_name,&grd_curcanv->cv_bitmap,grd_curcanv->cv_bitmap.bm_type,NULL);
	Assert(pcx_error == PCX_ERROR_NONE);

	com_process_mode = COM_PROCESS_MENU;

newmenu:
	num_options = 0;

	if (! ((Game_mode & GM_SERIAL) || (Game_mode & GM_MODEM)) )
	{
		// We haven't established any type of link

		ADD_ITEM("Initiate Connection", MENU_MODEM_CALL, KEY_I);
		ADD_ITEM("Listen for Connection", MENU_MODEM_ANSWER, KEY_L);
	}
	else
	{
		ADD_ITEM(TXT_START_GAME, MENU_SERIAL_GAME_START, KEY_S);
		ADD_ITEM(TXT_SEND_MESSAGEP, MENU_SEND_MESSAGE, KEY_S);
	}
	if (Game_mode & GM_MODEM)
		ADD_ITEM(TXT_CLOSE_LINK, MENU_MODEM_HANGUP, KEY_H);
	
	if (Game_mode & GM_SERIAL)
		ADD_ITEM(TXT_CLOSE_LINK, MENU_MODEM_HANGUP, KEY_C);

	sprintf(subtitle, "%s\n\n", TXT_SERIAL_GAME);

//	if (Game_mode & GM_SERIAL)
//		sprintf(subtitle+strlen(subtitle), "%s %s\n%s", TXT_SERIAL, TXT_LINK_ACTIVE, Players[OtherPlayer].callsign);
//	else if (Game_mode & GM_MODEM)
//		sprintf(subtitle+strlen(subtitle), "%d %s %s %s\n%s", com_baud_rate, TXT_BAUD, TXT_MODEM, TXT_LINK_ACTIVE, Players[OtherPlayer].callsign);	
	if ( (Game_mode & GM_SERIAL) || (Game_mode & GM_MODEM) )
		sprintf(subtitle+strlen(subtitle), "%s\n%s", TXT_LINK_ACTIVE, Players[OtherPlayer].callsign);
	else
		sprintf(subtitle+strlen(subtitle), TXT_NOT_CONNECTED);

	multi_leave_menu = 0;


	Assert(strlen(subtitle) < SUBTITLE_LEN);

	choice = newmenu_do4(NULL, subtitle, num_options, m, com_menu_poll, 0, NULL, -1, -1, 1);

	mprintf((0, "main menu choice was %d.\n", choice));

	if (choice == -1)
	{
		if (!((Game_mode & GM_SERIAL) || (Game_mode & GM_MODEM)))
		{
			com_disable();
			return;
		}
		m[0].text = TXT_YES; m[1].text = TXT_NO;
		m[0].type = m[1].type = NM_TYPE_MENU;

		choice = newmenu_do1(NULL, TXT_EXIT_WILL_CLOSE, 2, m, com_menu_poll, 0);
		if (choice == 0)
		{
			com_send_choice(SELECTION_CLOSE_LINK);
			com_hangup();
			return;
		}
		if ((choice == -2) && (other_menu_choice))
			com_process_other_menu_choice();

		goto newmenu;
	}

	if (choice == -2)
	{
		// Menu poll loop caused a re-draw
		if (other_menu_choice == SELECTION_STARTGAME)	
			com_ready_to_start();
		else if (other_menu_choice == SELECTION_CLOSE_LINK) 
		{
			nm_messagebox(NULL, 1, TXT_OK, TXT_CLOSED_LINK);
			com_hangup();
		}
			
		if (Function_mode == FMODE_GAME)
			return;	

		if (!conn_handle)
			Game_mode = GM_GAME_OVER;

		goto newmenu;
	}		

	if (choice > -1) 
	{
		old_game_mode=Game_mode;
		switch (menu_choice[choice])
		{
			case MENU_SERIAL_GAME_START:
				com_start_game();
				if (Function_mode != FMODE_GAME) 
					goto newmenu;
				break;
			case MENU_MODEM_CALL:
				tool_dialout();
				goto newmenu;
				break;
			case MENU_MODEM_ANSWER:
				tool_listen();
				goto newmenu;
				break;
			case MENU_SEND_MESSAGE:
				multi_send_message_dialog();
				if (Network_message_reciever != -1)
					multi_send_message();
				multi_sending_message = 0;
				goto newmenu;
				break;
//			case MENU_SERIAL_LINK_START:
//				serial_link_start();
//				goto newmenu;
//				break;
			case MENU_MODEM_HANGUP:
				com_hangup();
				return;
			default: 
				Int3();
				return;
		}
	}
}

// Handshaking to start a serial game, 2 players only

int com_start_game_menu(void)
{
	newmenu_item m[12];
	char level[5];
	int choice = 0;
	int opt, diff_opt, mode_opt, options_opt;
	char level_text[32];

#ifndef MAC_SHAREWARE
	int new_mission_num, anarchy_only = 0;

	new_mission_num = multi_choose_mission(&anarchy_only);

	if (new_mission_num < 0)
		return 0;

	strcpy(my_sync.mission_name, Mission_list[new_mission_num].filename);
#endif

	sprintf(level, "1");

	Game_mode &= ~GM_MULTI_COOP;
	Game_mode &= ~GM_MULTI_ROBOTS;
	Netgame.game_flags = 0;

	sprintf(level_text, "%s (1-%d)", TXT_LEVEL_, Last_level);
	if (Last_secret_level < -1)
		sprintf(level_text+strlen(level_text)-1, ", S1-S%d)", -Last_secret_level);
	else if (Last_secret_level == -1)
		sprintf(level_text+strlen(level_text)-1, ", S1)");

	Assert(strlen(level_text) < 32);

	// Put up menu for user choices controlling gameplay

newmenu:
	opt = 0;
	m[opt].type = NM_TYPE_TEXT; m[opt].text = level_text; opt++;
	m[opt].type = NM_TYPE_INPUT; m[opt].text_len = 4; m[opt].text = level; opt++;
	m[opt].type = NM_TYPE_TEXT; m[opt].text = TXT_MODE;
	mode_opt = opt; 
	m[opt].type = NM_TYPE_RADIO; m[opt].text = TXT_ANARCHY; m[opt].value=!(Game_mode & GM_MULTI_ROBOTS); m[opt].group = 0; opt++;
	m[opt].type = NM_TYPE_RADIO; m[opt].text = TXT_ANARCHY_W_ROBOTS; m[opt].value=(!(Game_mode & GM_MULTI_COOP) && (Game_mode & GM_MULTI_ROBOTS)); m[opt].group = 0; opt++;
	m[opt].type = NM_TYPE_RADIO; m[opt].text = TXT_COOPERATIVE; m[opt].value=(Game_mode & GM_MULTI_COOP);m[opt].group = 0; opt++;
	diff_opt = opt;
	m[opt].type = NM_TYPE_SLIDER; m[opt].text = TXT_DIFFICULTY; m[opt].value = Player_default_difficulty; m[opt].min_value = 0; m[opt].max_value = (NDL-1); opt++;

#ifndef MAC_SHAREWARE
	options_opt = opt;
//	m[opt].type = NM_TYPE_CHECK; m[opt].text = TXT_SHOW_IDS; m[opt].value=0; opt++;
	m[opt].type = NM_TYPE_CHECK; m[opt].text = TXT_SHOW_ON_MAP; m[opt].value=0; opt++;
#endif

	Assert(opt <= 12);

	choice = newmenu_do1(NULL, TXT_SERIAL_GAME_SETUP, opt, m, NULL, 1);
	if (choice > -1) 
	{
		if (m[mode_opt].value)
			Game_mode &= ~(GM_MULTI_COOP | GM_MULTI_ROBOTS);
#ifdef MAC_SHAREWARE
		else {
			nm_messagebox(NULL, 1, TXT_OK, TXT_ONLY_ANARCHY);
			goto newmenu;
		}
#else
		else if (anarchy_only) {
			nm_messagebox(NULL, 1, TXT_OK, TXT_ANARCHY_ONLY_MISSION);
			goto newmenu;
		}
		else if (m[mode_opt+1].value)
		{
			Game_mode &= ~GM_MULTI_COOP;
			Game_mode |= GM_MULTI_ROBOTS;
		}
		else
			Game_mode |= (GM_MULTI_COOP | GM_MULTI_ROBOTS);

//		if (m[options_opt].value)
//			Netgame.game_flags |= NETGAME_FLAG_SHOW_ID;
		if (m[options_opt].value)
			Netgame.game_flags |= NETGAME_FLAG_SHOW_MAP;
		if (!strnicmp(level, "s", 1))
			start_level_num = -atoi(level+1);
		else
#endif
			start_level_num = atoi(level);

		if ((start_level_num < Last_secret_level) || (start_level_num > Last_level) || (start_level_num == 0))
		{
			nm_messagebox(TXT_ERROR, 1, TXT_OK, TXT_LEVEL_OUT_RANGE);
			sprintf(level, "1");
			goto newmenu;
		}

		Difficulty_level = m[diff_opt].value;

		return(1); // Go for game!
	}
	return 0; // No game
}

int
com_ask_to_start()
{	
	// Ask the other player if its OK to start now

	newmenu_item m[1];
	int choice;

	com_send_choice(SELECTION_STARTGAME);

	m[0].type = NM_TYPE_TEXT; m[0].text = TXT_ESC_ABORT;
menu:
	choice = newmenu_do(NULL, TXT_WAIT_FOR_OK, 1, m, com_menu_poll);

	if (choice == -1)
	{
		com_send_choice(SELECTION_STARTGAME_ABORT);
		return(0);
	}
	if (choice == -2)
	{
		if (other_menu_choice == SELECTION_YES_START)
			return(1);
		else if (other_menu_choice == SELECTION_STARTGAME)
		{
			com_send_choice(SELECTION_YES_START);
			return(1);
		}
		else 
			return(0);
	}
	goto menu;
}
		
void
com_start_game()
{
	// Start a serial game after being linked

	mprintf((0, "Entered com_start_game\n"));

	com_reset_game();

	if (! ( (Game_mode & GM_MODEM) || (Game_mode & GM_SERIAL) ) ) 
		return;
	
	Assert (master != -1);

	if (other_menu_choice != SELECTION_STARTGAME)
	{
		if (!com_ask_to_start())
			return;
	}

	if (master == 1) // Master chooses options
	{
		if (com_start_game_menu())
		{
			OtherPlayer = 1;
			change_playernum_to(0);
			my_sync.level_num = start_level_num;
			my_sync.difficulty = Difficulty_level;
			my_sync.game_mode = Game_mode;
			memcpy(my_sync.callsign, Players[Player_num].callsign, CALLSIGN_LEN+1);
#ifndef MAC_SHAREWARE
			my_sync.sync_time = control_invul_time;
			my_sync.game_flags = Netgame.game_flags;
			Netgame.control_invul_time = control_invul_time;
#endif
			com_sync(0);
		}
	}
	else // Slave
	{
		OtherPlayer = 0;
		change_playernum_to(1);
		memcpy(my_sync.callsign, Players[Player_num].callsign, CALLSIGN_LEN+1);
	
		my_sync.level_num = 1;
		
		com_sync(0);
		if (com_process_mode == COM_PROCESS_NORMAL)
		{
			Difficulty_level = other_sync.difficulty;
			start_level_num = other_sync.level_num;
			Game_mode = other_sync.game_mode;
#ifndef MAC_SHAREWARE
			Netgame.game_flags = other_sync.game_flags;
			Netgame.control_invul_time = other_sync.sync_time;
			if (!load_mission_by_name(other_sync.mission_name))
			{
				mprintf((0, "Mission not found: %s!\n", other_sync.mission_name));
				nm_messagebox(NULL, 1, TXT_OK, TXT_MISSION_NOT_FOUND);
				my_sync.sync_id = start_level_num;
				serial_sync_abort(0);
				return;
			}
#endif
		}
	}
	if (com_process_mode != COM_PROCESS_NORMAL)
		return;

	memcpy(Players[OtherPlayer].callsign, other_sync.callsign, CALLSIGN_LEN+1);
	Function_mode = FMODE_GAME;
	Game_mode &= ~GM_GAME_OVER;
	Show_kill_list = 1;
	init_player_stats_game();
	init_player_stats_level();
//	Assert(start_level_num > 0);
  	Assert((start_level_num >= Last_secret_level) && (start_level_num <= Last_level));
  	StartNewLevel(start_level_num);
	
#ifdef MAC_SHAREWARE
	contest_active = 0;
#endif
}

void
com_wait_for_connect(int nitems, newmenu_item *menus, int *key, int citem)
{
	char *cfg_str, *s, *s1;
	int i, baud, connected;
	CMErr err;
	ConnEnvironRec environment;

	menus = menus;
	nitems = nitems;
	citem = citem;

	CMIdle(conn_handle);
	connected = CMGetRefCon(conn_handle);
	if (!connected)
		return;
		
	if (connected == -1) {
		err = CMGetUserData(conn_handle);
		*key = -3;
		return;
	}

	memset(&environment, 0, sizeof(environment));
	if (CMGetConnEnvirons(conn_handle, &environment) != noErr) {
		Int3();
		*key = -3;
		return;
	}
	
	if (environment.baudRate < 9600)
	{
		nm_messagebox(NULL, 1, TXT_OK, TXT_BAUD_GREATER_9600);
		*key = -3;
		return;
	}

	com_baud_rate = environment.baudRate;

	*key = -2;
	return;			// good open
}

void tool_dialout(void)
{
	newmenu_item m[5];
	char *cfg_str, *s, *s1, text[50];
	int choice;
	CMStatFlags cflags;
	CMErr err;
	
main:

	rx_seqnum = 0xff;
	tx_seqnum = 0;

	CMSetRefCon(conn_handle, 0);	

	err = CMOpen(conn_handle, 1, completion_proc, 0);
//	if (err == cmUserCancel) {
//		com_abort();
//		return;
//	}
	
//	if (err != cmNoErr) {
//		nm_messagebox(NULL, 1, TXT_OK, "Error trying to establish connection.");
//		com_abort();
//		return;
//	}

	m[0].type=NM_TYPE_TEXT; m[0].text=TXT_ESC_ABORT;

//	sprintf(text, "%s\n%s", TXT_DIALING, phone_number);

	choice = newmenu_do(NULL, "Establishing Connection", 1, m, com_wait_for_connect);
	
	if (choice == -1) {			// user aborted
		com_abort();
		return;
	}
	
	if (choice != -2) {
		nm_messagebox(NULL, 1, TXT_OK, "Error trying to establish connection.");
		com_abort();
		return;
	}
	
//	com_open = 1;
//	N_players = 2;
//	master = 1;   // The person who dialed is the master of the connection
//	change_playernum_to(0);


	cfg_str = CMGetConfig(conn_handle);
	if (cfg_str) {
		strlwr(cfg_str);
		if ( strstr(cfg_str, "dial") || strstr(cfg_str, "modemtype") || strstr(cfg_str, "typeofcall") ) {
			master = 1;
			change_playernum_to(0);
		} else {
			master = -1;
		}
		free(cfg_str);
	} else
		master = -1;

	com_open = 1;
	N_players = 2;
	synccnt = 0;
	srand(clock());
	my_sync.sync_time = swapint(rand());
	if (!com_connect())
	{
		Game_mode |= GM_MODEM;
		digi_play_sample(SOUND_HUD_MESSAGE, F1_0);
	}
	else {
		com_abort();
	}
}
									 	
void
com_listen_for_connect(int nitems, newmenu_item *menus, int *key, int citem)
{
	int i, connected;
	CMErr err;

	menus = menus;
	nitems = nitems;
	citem = citem;

	CMIdle(conn_handle);
	connected = CMGetRefCon(conn_handle);
	if (!connected)
		return;
		
	if (connected == -1) {
		err = (*conn_handle)->errCode;
		if (err == cmNotSupported)
			*key = -3;
		else
			*key = -2;
		return;
	}

	*key = -4;

	return;
	
}

void tool_listen(void)
{
	int choice;
	newmenu_item m[3];
	CMErr err;
	char *cfg_str;

	rx_seqnum = 0xff;
	tx_seqnum = 0;

	CMSetRefCon(conn_handle, 0);	
	err = CMListen(conn_handle, 1, completion_proc, -1);

	if (!err) {
		m[0].type=NM_TYPE_TEXT; m[0].text=TXT_ESC_ABORT;

//	sprintf(text, "%s\n%s", TXT_DIALING, phone_number);

		choice = newmenu_do(NULL, "Establishing Connection", 1, m, com_listen_for_connect);
	} else if (err == cmNotSupported) {
		choice = -3;
	} else {
		choice = -2;
	}

	if (choice == -1) {
		com_abort();
		return;
	}
	
	if (choice == -2) {
		nm_messagebox(NULL, 1, TXT_OK, "Error trying to listen\nfor connection.");
		com_abort();
		return;
	}	
		
	if (choice == -3) {
		CMSetRefCon(conn_handle, 0);	
		err = CMOpen(conn_handle, 1, completion_proc, -1);

		m[0].type=NM_TYPE_TEXT; m[0].text=TXT_ESC_ABORT;

//	sprintf(text, "%s\n%s", TXT_DIALING, phone_number);

		choice = newmenu_do(NULL, "Establishing Connection", 1, m, com_wait_for_connect);

		if (choice == -1) {			// user aborted
			com_abort();
			return;
		}
		
		if (choice != -2) {
			nm_messagebox(NULL, 1, TXT_OK, "Error trying to establish connection.");
			com_abort();
			return;
		}
	} else {
	
		if ( !(GetConnectionStatus() & cmStatusIncomingCallPresent) ) {
			nm_messagebox(NULL, 1, TXT_OK, "Error trying to establish connection.");
			com_abort();
			return;
		}
		
		if (CMAccept(conn_handle, 1)) {
			nm_messagebox(TXT_ERROR, 1, TXT_OK, "Error accepting call.");
			com_abort();
			return;
		}
		
	}
	
	// We are now connected to the other modem
	
//	com_open = 1;
//	N_players = 2;
//	master = 0;

	cfg_str = CMGetConfig(conn_handle);
	if (cfg_str) {
		strlwr(cfg_str);
		if ( strstr(cfg_str, "dial") || strstr(cfg_str, "modemtype") || strstr(cfg_str, "typeofcall") ) {
			master = 0;
			change_playernum_to(0);
		} else {
			master = -1;
		}
		free(cfg_str);
	} else
		master = -1;

	com_open = 1;
	N_players = 2;
	synccnt = 0;
	srand(clock());
	my_sync.sync_time = swapint(rand());
	mprintf((0, "My rand set to %d.\n", my_sync.sync_time));

	if (!com_connect()) 
	{
		Game_mode |= GM_MODEM;
		digi_play_sample(SOUND_HUD_MESSAGE, F1_0);
	}
	else {
		com_abort();
	}
}

//
// Syncronization functions
//

void
serial_sync_abort(int val)
{
	// Send "I got Sync but it was no good!" packet

	sendbuf[0] = (char)MULTI_END_SYNC;
	sendbuf[1] = Player_num;
	sendbuf[2] = (char)val; // Indicated failure
#ifndef MAC_SHAREWARE
	sendbuf[3] = my_sync.sync_id;
	com_send_data(sendbuf, 4, 1);
#else
	com_send_data(sendbuf, 3, 1);
#endif
}

extern ushort mac_calc_segment_checksum();
	
int
com_level_sync(void)
{
	// Send between-level sync stuff

	mprintf((0, "entered com_level_sync()\n"));

	Function_mode = FMODE_MENU; // Prevent the game loop from running during the menus!

	// At this point, the new level is loaded but the extra objects or players have not 
	// been removed

	my_sync.level_num = (byte)Current_level_num;
	my_sync.seg_checksum = mac_calc_segment_checksum();
	my_sync.seg_checksum = swapshort(my_sync.seg_checksum);
	my_sync.kills[0] = swapshort(kill_matrix[Player_num][0]);
	my_sync.kills[1] = swapshort(kill_matrix[Player_num][1]);
	my_sync.proto_version = MULTI_PROTO_VERSION;
#ifndef MAC_SHAREWARE
	my_sync.killed = swapshort(Players[Player_num].net_killed_total);
#endif
	srand(clock());

	if (Game_mode & GM_MULTI_COOP)
		my_sync.difficulty = Player_num;
	else
		my_sync.difficulty = rand()%MAX_NUM_NET_PLAYERS; // My starting position

	if (com_sync(Current_level_num))
	{
		com_process_mode = COM_PROCESS_MENU;
		nm_messagebox(TXT_ERROR, 1, TXT_OK, TXT_NEGOTIATION_FAIL );
		longjmp(LeaveGame, 0);
	}

	if (my_sync.level_num != other_sync.level_num)
	{
		// Fatal error
		nm_messagebox(TXT_ERROR, 1, TXT_OK, "%s %d\n%s %d", TXT_FATAL_ERROR_LEVEL, my_sync.level_num, TXT_OTHER_LEVEL, other_sync.level_num);
		longjmp(LeaveGame, 0);
	}

	if (swapshort(my_sync.seg_checksum) != swapshort(other_sync.seg_checksum))
	{
		// Checksum failure
		mprintf((1, "My check %d, other check %d.\n", my_sync.seg_checksum, other_sync.seg_checksum));
		nm_messagebox(TXT_ERROR, 1, TXT_OK, "%s %d %s %s%s", TXT_YOUR_LEVEL, my_sync.level_num, TXT_LVL_NO_MATCH, other_sync.callsign, TXT_CHECK_VERSION);
#ifdef NDEBUG
		longjmp(LeaveGame, 0);
#endif
	}

	if (my_sync.proto_version != other_sync.proto_version)
	{
		// Version mismatch
		nm_messagebox(TXT_ERROR, 1, TXT_OK, TXT_DESCENT_NO_MATCH);
		longjmp(LeaveGame, 0);
	}

	mprintf((0, "My pos = %d, other pos = %d.\n", my_sync.difficulty, other_sync.difficulty));

	if ((other_sync.difficulty == my_sync.difficulty) && !master)
	{
		// If we chose the same position and I am the slave, choose another
		my_sync.difficulty = (my_sync.difficulty+1) % MAX_NUM_NET_PLAYERS;
	}

	Objects[Players[OtherPlayer].objnum].pos = Player_init[other_sync.difficulty].pos;
	Objects[Players[OtherPlayer].objnum].orient = Player_init[other_sync.difficulty].orient;
	obj_relink(Players[OtherPlayer].objnum,Player_init[other_sync.difficulty].segnum);
	Objects[Players[OtherPlayer].objnum].type = OBJ_PLAYER;

	Objects[Players[Player_num].objnum].pos = Player_init[my_sync.difficulty].pos;
	Objects[Players[Player_num].objnum].orient = Player_init[my_sync.difficulty].orient;
	obj_relink(Players[Player_num].objnum, Player_init[my_sync.difficulty].segnum);
	Objects[Players[Player_num].objnum].type = OBJ_PLAYER;

	SerialLastMessage = GameTime;

	kill_matrix[OtherPlayer][0] = swapshort(other_sync.kills[0]);
	kill_matrix[OtherPlayer][1] = swapshort(other_sync.kills[1]);
	Players[Player_num].net_kills_total = kill_matrix[Player_num][OtherPlayer] - kill_matrix[Player_num][Player_num];
	Players[OtherPlayer].net_kills_total = kill_matrix[OtherPlayer][Player_num] - kill_matrix[OtherPlayer][OtherPlayer];
//	Players[Player_num].net_killed_total = kill_matrix[0][Player_num] + kill_matrix[1][Player_num];
#ifdef MAC_SHAREWARE
	Players[OtherPlayer].net_killed_total = kill_matrix[0][OtherPlayer] + kill_matrix[1][OtherPlayer];
#else
	Players[OtherPlayer].net_killed_total = swapshort(other_sync.killed);
#endif
	Players[OtherPlayer].connected = Players[Player_num].connected = 1;

	Assert(N_players == 2);
	Assert(Player_num != OtherPlayer);

	gr_palette_fade_out(gr_palette, 32, 0);

	Function_mode = FMODE_GAME;
	com_process_mode = COM_PROCESS_NORMAL;
	multi_sort_kill_list();
	return(0);
}

void
com_send_end_sync(void)
{
	// Send "I got Sync" packet

	sendbuf[0] = (char)MULTI_END_SYNC;
	sendbuf[1] = Player_num;
	sendbuf[2] = 1; // Indicates success
#ifndef MAC_SHAREWARE
	sendbuf[3] = my_sync.sync_id;
	com_send_data(sendbuf, 4, 2);
#else
	com_send_data(sendbuf, 3, 2);
#endif
}

void
com_send_begin_sync(void)
{
	mprintf((0, "Sending my sync.\n"));
#ifdef MAC_SHAREWARE
	com_send_data((char *)&my_sync, sizeof(com_sync_pack)-4, 1);		// PAD BYTE ADDED BY MACINTOSH
#else
	com_send_data((char *)&my_sync, sizeof(com_sync_pack)-3, 1);
#endif
}

void
com_process_end_sync(byte *buf)
{
	// Process incoming end-sync packet

	if (buf[2] != 1) {
		com_process_mode = COM_PROCESS_MENU;
		return;
	}

#ifndef MAC_SHAREWARE
	if (buf[3] == my_sync.sync_id)
#endif
		other_got_sync = 1;
}

void
com_process_sync(char *buf, int len)
{
	len = len;
	switch(buf[0])
	{
		case MULTI_END_SYNC:
		{
			com_process_end_sync(buf);
			break;
		}
		case MULTI_BEGIN_SYNC:
		{
			mprintf((0, "Incoming begin_sync message.\n"));
			if (got_sync)
				break;

#ifdef MAC_SHAREWARE
			memcpy(&other_sync, buf, sizeof(com_sync_pack)-4);		// PAD BYTE ADDED BY MACINTOSH
#else
			memcpy(&other_sync, buf, sizeof(com_sync_pack)-3);
#endif
#ifndef MAC_SHAREWARE
			if (other_sync.sync_id != my_sync.sync_id) 
			{
				mprintf((0, "Other sync invalid id, %d != %d.\n", other_sync.sync_id, my_sync.sync_id));
			}
			else
#endif
			{			
				mprintf((0, "got other sync size %d.\n", sizeof(com_sync_pack)-3));
				got_sync = 1;
				com_send_end_sync();
			}
			break;
		}
	} // switch

	if (got_sync && other_got_sync)
	{
		// OK to start game
//		mprintf((1, "Starting game.\n"));
		got_sync = 0;
		other_got_sync = 0;
		com_process_mode = COM_PROCESS_NORMAL;
	}
}
	
void
com_send_sync(void)
{
	// Send sync information, depending on the situation

	if (!other_got_sync)
	{
		com_send_begin_sync();
	}
	if (got_sync)
	{
		com_send_end_sync();
	}
}

void com_sync_poll(int nitems, newmenu_item *menus, int *key, int citem)
{
	static fix t1 = 0;

	menus = menus;
	nitems = nitems;
	citem = citem;

	if (!com_open)
	{
		*key = -3;
		return;
	}

	if (timer_get_approx_seconds() > t1+F1_0)
	{
		com_send_sync();
		t1 = timer_get_approx_seconds();
	}

	Assert(com_process_mode == COM_PROCESS_SYNC);
		
	com_process_input();

	if (com_process_mode == COM_PROCESS_NORMAL)
	{
		*key = -2;
		com_send_sync();
		mprintf((0, "Sync finished.\n"));
		return;
	}
	if (com_process_mode == COM_PROCESS_MENU)
	{
		*key = -3;
		mprintf((0, "Sync denied by other side.\n"));
		return;
	}
	return;
}

int
com_sync(int id)
{
	// How to handle the end of the level and start of the next level
	// returns 0 for success or 1 for failure

	int choice;
	newmenu_item m[3];
	int pcx_error;

	mprintf((0, "Entered com_sync\n"));

	gr_set_current_canvas(NULL);
	pcx_error = pcx_read_bitmap(Menu_pcx_name, &grd_curcanv->cv_bitmap,grd_curcanv->cv_bitmap.bm_type,NULL);
	Assert(pcx_error == PCX_ERROR_NONE);

	com_process_mode = COM_PROCESS_SYNC;
	got_sync = other_got_sync = 0;

	com_flush();
	com_flush();

#ifndef MAC_SHAREWARE
	my_sync.sync_id = id;
#endif

	m[0].type=NM_TYPE_TEXT; m[0].text=TXT_ESC_ABORT;
	m[1].type = m[2].type = NM_TYPE_MENU;
	m[1].text = TXT_YES; 
	m[2].text = TXT_NO;

repeat:
	choice = newmenu_do(NULL, TXT_WAIT_OPPONENT, 1, m, com_sync_poll);

	if (choice == -1) 
	{
		choice = newmenu_do1(NULL, TXT_SURE_ABORT_SYNC, 2, m+1, com_sync_poll, 1);
		if (choice == -1)
			choice = 1;
		if (choice == 0)
			choice = -1;
	}

	if ((choice == -1) || (choice == -3)) {
		return(-1);
	}
	else if (choice != -2)
		goto repeat;

	return(0);
}

void
com_endlevel(int *secret)
{
	// What do we do between levels?

#ifdef MAC_SHAREWARE

	gr_palette_fade_out(gr_palette, 32, 0);
	if (multi_goto_secret == 1)
		*secret = 1;
	multi_goto_secret = 0;

#else

	Function_mode = FMODE_MENU;

	gr_palette_fade_out(gr_palette, 32, 0);

	my_sync.level_num = multi_goto_secret;

	if (com_sync(-3))
	{
		com_process_mode = COM_PROCESS_MENU;
		nm_messagebox(TXT_ERROR, 1, TXT_OK, TXT_NEGOTIATION_FAIL);
		longjmp(LeaveGame, 0);
	}

	com_process_mode = COM_PROCESS_ENDLEVEL;

	if ((multi_goto_secret == 1) || (other_sync.level_num == 1))
		*secret = 1;
	else
		*secret = 0;

	multi_goto_secret = 0;
#endif
	return;
}

#endif

