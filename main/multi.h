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
 * $Source: Smoke:miner:source:main::RCS:multi.h $
 * $Revision: 1.7 $
 * $Author: allender $
 * $Date: 1995/11/07 17:06:30 $
 * 
 * Defines and exported variables for multi.c
 * 
 * $Log: multi.h $
 * Revision 1.7  1995/11/07  17:06:30  allender
 * changed max_message_len so that player files save and restore
 * correctly
 *
 * Revision 1.6  1995/11/03  12:54:13  allender
 * shareware changes
 *
 * Revision 1.5  1995/10/31  10:20:55  allender
 * shareware stuff
 *
 * Revision 1.4  1995/08/31  15:52:21  allender
 * added union in netplayer_info to include
 * appletalk information and ipx information
 *
 * Revision 1.3  1995/07/26  17:02:47  allender
 * implemented and working on mac
 *
 * Revision 1.2  1995/06/08  12:56:19  allender
 * couple of prototypes to be unsigned char
 *
 * Revision 1.1  1995/05/16  15:59:44  allender
 * Initial revision
 *
 * Revision 2.3  1995/04/03  08:49:50  john
 * Added code to get someone's player struct.
 * 
 * Revision 2.2  1995/03/27  12:59:17  john
 * Initial version of multiplayer save games.
 * 
 * Revision 2.1  1995/03/21  14:39:06  john
 * Ifdef'd out the NETWORK code.
 * 
 * Revision 2.0  1995/02/27  11:28:34  john
 * New version 2.0, which has no anonymous unions, builds with
 * Watcom 10.0, and doesn't require parsing BITMAPS.TBL.
 * 
 * Revision 1.74  1995/02/11  11:36:42  rob
 * Added new var.
 * 
 * Revision 1.73  1995/02/08  18:17:41  rob
 * Added prototype for reset function.
 * 
 * Revision 1.72  1995/02/05  14:37:42  rob
 * Made object mapping more efficient.
 * 
 * Revision 1.71  1995/02/01  18:07:36  rob
 * Change object mapping to int functions.
 * 
 * Revision 1.70  1995/02/01  12:55:00  rob
 * Changed message type.
 * 
 * Revision 1.69  1995/01/31  12:46:12  rob
 * Fixed a bug with object overflow handling.
 * 
 * Revision 1.68  1995/01/27  11:15:13  rob
 * removed extern of variable no longer in multi.c
 * 
 * Revision 1.67  1995/01/24  11:53:13  john
 * Added better macro defining code.
 * 
 * Revision 1.66  1995/01/24  11:32:03  john
 * Added new defining macro method.
 * 
 * Revision 1.65  1995/01/23  17:17:06  john
 * Added multi_sending_message.
 * 
 * Revision 1.64  1995/01/23  16:02:42  rob
 * Added prototype for mission select function.
 * 
 * Revision 1.63  1995/01/18  19:01:21  rob
 * Added new message for hostage door sync.
 * 
 * Revision 1.62  1995/01/14  18:39:57  rob
 * Added new message type for dropping robot powerups.
 * 
 * Revision 1.61  1995/01/12  21:41:13  rob
 * Fixed incompat. with 1.0 and 1.1.
 * 
 * Revision 1.60  1995/01/04  21:40:55  rob
 * Added new type for boss actions in coop.
 * 
 * Revision 1.59  1995/01/04  11:38:09  rob
 * Fixed problem with lost character in messages.
 * 
 * Revision 1.58  1995/01/03  20:12:44  rob
 * Made max message length in shareware = 40.
 * 
 * Revision 1.57  1995/01/03  14:27:25  rob
 * ADded trigger messages.
 * 
 * Revision 1.56  1995/01/02  20:08:21  rob
 * Added robot creation.
 * 
 * Revision 1.55  1995/01/02  14:41:30  rob
 * Added score syncing.
 * 
 * Revision 1.54  1994/12/21  21:02:01  rob
 * Added new message type for ROBOT_FIRE
 * 
 * Revision 1.53  1994/12/21  17:27:25  rob
 * Changed the format for send_create_powerup messages.
 * 
 * 
 * Revision 1.52  1994/12/20  20:41:39  rob
 * ADded robot release message type.
 * 
 * Revision 1.51  1994/12/19  19:00:12  rob
 * Changed buf to multibuf so it can be safely externed.
 * 
 * Revision 1.50  1994/12/19  16:41:14  rob
 * Added new message types for robot support.
 * Added prototype for external use of multi_send_data (from multibot.c)
 * 
 * Revision 1.49  1994/12/11  13:30:13  rob
 * Added new variables to get players out of nested menus.
 * 
 * Revision 1.48  1994/12/11  01:58:57  rob
 * Added variable to track menu deth..
 * 
 * Revision 1.47  1994/12/08  12:41:17  rob
 * Added audio taunts.
 * 
 * Revision 1.46  1994/12/07  21:53:12  rob
 * Fixing sequencing bugginess in modem/serial.
 * 
 * Revision 1.45  1994/12/07  16:46:58  rob
 * Added prototype.
 * 
 * Revision 1.44  1994/12/01  12:22:31  rob
 * Added de-cloak message for demo.
 * 
 * Revision 1.43  1994/12/01  00:54:14  rob
 * Added variable for tracking homing missiles.
 * 
 * Revision 1.42  1994/11/30  16:04:39  rob
 * Added show reticle name variable for team games.
 * 
 * Revision 1.41  1994/11/29  19:33:38  rob
 * Team support.
 * 
 * Revision 1.40  1994/11/29  12:49:37  rob
 * Added more team support stuff.
 * 
 * Revision 1.39  1994/11/28  21:20:49  rob
 * Cleaned up the .h file, removed an unused function.
 * 
 * Revision 1.38  1994/11/28  21:04:50  rob
 * Added support for network sound-casting.
 * 
 * Revision 1.37  1994/11/28  14:02:08  rob
 * Added protocol versioning for registered versus shareware.
 * 
 * Revision 1.36  1994/11/28  13:30:04  rob
 * Added a define for protocol version.
 * 
 * Revision 1.35  1994/11/22  19:19:48  rob
 * remove unused function.
 * 
 * Revision 1.34  1994/11/22  18:47:34  rob
 * Added hooks for modem support for secret levels.
 * 
 * Revision 1.33  1994/11/22  17:10:50  rob
 * Fix for secret levels in network play mode.
 * 
 * Revision 1.32  1994/11/21  16:00:28  rob
 * Added secret-level hooks.
 * 
 * Revision 1.31  1994/11/18  18:28:50  rob
 * Added new function for multiplayer score screen.
 * 
 * Revision 1.30  1994/11/18  16:31:05  rob
 * Added kill list timer variable.
 * 
 * Revision 1.29  1994/11/17  16:38:15  rob
 * Added creation of net powerups.
 * 
 * Revision 1.28  1994/11/17  13:37:33  rob
 * Added prototype for multi_new_game.
 * 
 * Revision 1.27  1994/11/17  12:58:45  rob
 * Added kill matrix.
 * 
 * Revision 1.26  1994/11/16  20:35:24  rob
 * Changed explosion hook.
 * 
 * Revision 1.25  1994/11/15  21:31:13  rob
 * Bumped max message size, was giving modem.c fits.
 * 
 * Revision 1.24  1994/11/15  19:28:37  matt
 * Added prototypes
 * 
 * Revision 1.23  1994/11/14  17:22:19  rob
 * Added extern for message macros.
 * 
 * Revision 1.22  1994/11/11  18:16:44  rob
 * Made multi_menu_poll return a value to exit menus.
 * 
 * Revision 1.21  1994/11/11  11:06:19  rob
 * Added prototype for multi_menu_poll.
 * 
 * Revision 1.20  1994/11/10  21:48:41  rob
 * Changed multi_endlevel to return an int.
 * 
 * Revision 1.19  1994/11/08  17:48:14  rob
 * Fixing endlevel stuff.
 * 
 * Revision 1.18  1994/11/07  17:49:07  rob
 * Changed prototype for object mapping funcs.
 * 
 * Revision 1.17  1994/11/07  15:46:32  rob
 * Changed the way remote object number mapping works, and it was a real
 * pain in the ass..  I think it will work more reliably now.
 * 
 * Revision 1.16  1994/11/04  19:53:01  rob
 * Added a new message type for Player_leave 'explosions'.
 * Added a prototype for function moved over from network.c
 * 
 * Revision 1.15  1994/11/02  18:02:33  rob
 * Added message type for control center firing.
 * 
 * Revision 1.14  1994/11/02  11:38:00  rob
 * Added player-in-process-of-dying explosions to network game.
 * 
 * Revision 1.13  1994/11/01  19:31:44  rob
 * Bumped max_net_create_objects to 20 to accomodate a fully equipped
 * character blowing up.
 * 
 * Revision 1.12  1994/10/31  13:48:02  rob
 * Fixed bug in opening doors over network/modem.  Added a new message
 * type to multi.c that communicates door openings across the net. 
 * Changed includes in multi.c and wall.c to accomplish this.
 * 
 * Revision 1.11  1994/10/09  20:08:20  rob
 * Added some exported func prototypes.
 * Changed max net message length to 25 (from 30).
 * Removed some message types no longer used.
 * 
 * Revision 1.10  1994/10/08  20:06:10  rob
 * fixed a typo.
 * 
 * Revision 1.9  1994/10/08  19:59:43  rob
 * Moved MAX_MESSAGE_LEN to here.
 * 
 * Revision 1.8  1994/10/07  23:09:54  rob
 * Fixed some prototypes.
 * 
 * Revision 1.7  1994/10/07  18:11:19  rob
 * Added multi_do_death to multi.c.
 * 
 * Revision 1.6  1994/10/07  16:14:32  rob
 * Added new message type for player reappear
 * 
 * Revision 1.5  1994/10/07  12:58:17  rob
 * Added multi_leave_game.
 * 
 * Revision 1.4  1994/10/07  12:17:17  rob
 * Fixed some stuff in multi_do_frame and exported the message_length
 * array.
 * 
 * Revision 1.3  1994/10/07  11:10:17  john
 * Added function to parse multiple messages into individual
 * messages.
 * 
 * Revision 1.2  1994/10/07  10:28:06  rob
 * Headers and stuff for multi.c (obviously)
 * 
 * Revision 1.1  1994/10/06  16:07:39  rob
 * Initial revision
 * 
 * 
 */



#ifndef _MULTI_H
#define _MULTI_H

#define MAX_MESSAGE_LEN 35
#define SHAREWARE_MAX_MESSAGE_LEN 25

#ifdef NETWORK

// Defines
#include "Appletalk.h"
#include "gameseq.h"
#include "piggy.h"

// What version of the multiplayer protocol is this?

#ifdef MAC_SHAREWARE
#define MULTI_PROTO_VERSION 	1
#else
#define MULTI_PROTO_VERSION	2
#endif

// How many simultaneous network players do we support?

#define MAX_NUM_NET_PLAYERS 8

#define MULTI_POSITION			0
#define MULTI_REAPPEAR   		1
#define MULTI_FIRE				2
#define MULTI_KILL 				3
#define MULTI_REMOVE_OBJECT	4
#define MULTI_PLAYER_EXPLODE	5
#define MULTI_MESSAGE			6
#define MULTI_QUIT				7
#define MULTI_PLAY_SOUND		8
#define MULTI_BEGIN_SYNC		9
#define MULTI_CONTROLCEN		10
#define MULTI_ROBOT_CLAIM		11
#define MULTI_END_SYNC			12
#define MULTI_CLOAK				13
#define MULTI_ENDLEVEL_START	14
#define MULTI_DOOR_OPEN			15
#define MULTI_CREATE_EXPLOSION 16
#define MULTI_CONTROLCEN_FIRE	17
#define MULTI_PLAYER_DROP		18
#define MULTI_CREATE_POWERUP	19
#define MULTI_CONSISTENCY		20
#define MULTI_DECLOAK			21
#define MULTI_MENU_CHOICE		22

#ifndef MAC_SHAREWARE
#define MULTI_ROBOT_POSITION	23
#define MULTI_ROBOT_EXPLODE	24
#define MULTI_ROBOT_RELEASE	25
#define MULTI_ROBOT_FIRE		26
#define MULTI_SCORE				27
#define MULTI_CREATE_ROBOT		28
#define MULTI_TRIGGER			29
#define MULTI_BOSS_ACTIONS		30
#define MULTI_CREATE_ROBOT_POWERUPS	31
#define MULTI_HOSTAGE_DOOR		32
#endif

#define MULTI_SAVE_GAME			33
#define MULTI_RESTORE_GAME		34

#define MULTI_REQ_PLAYER		35		// Someone requests my player structure
#define MULTI_SEND_PLAYER		36		// Sending someone my player structure

#ifndef MAC_SHAREWARE
#define MULTI_MAX_TYPE			36
#else
#define MULTI_MAX_TYPE			22
#endif

#ifdef MAC_SHAREWARE
#define MAX_NET_CREATE_OBJECTS 19 
#else
#define MAX_NET_CREATE_OBJECTS 20
#endif

#define MAX_MULTI_MESSAGE_LEN 90

// Exported functions

int objnum_remote_to_local(int remote_obj, int owner);
int objnum_local_to_remote(int local_obj, byte *owner);
void map_objnum_local_to_remote(int local, int remote, int owner);
void map_objnum_local_to_local(int objnum);

void multi_init_objects(void);
void multi_show_player_list(void);
void multi_do_frame(void);

void multi_send_fire(void);
void multi_send_destroy_controlcen(int objnum, int player);
void multi_send_endlevel_start(int);
void multi_send_player_explode(char type);
void multi_send_message(void);
void multi_send_position(int objnum);
void multi_send_reappear();
void multi_send_kill(int objnum);
void multi_send_remobj(int objnum);
void multi_send_quit(int why);
void multi_send_door_open(int segnum, int side);
void multi_send_create_explosion(int player_num);
void multi_send_controlcen_fire(vms_vector *to_target, int gun_num, int objnum);
void multi_send_cloak(void);
void multi_send_decloak(void);
void multi_send_create_powerup(int powerup_type, int segnum, int objnum, vms_vector *pos);
void multi_send_play_sound(int sound_num, fix volume);
void multi_send_audio_taunt(int taunt_num);
void multi_send_score(void);
void multi_send_trigger(int trigger);
void multi_send_hostage_door_status(int wallnum);
void multi_send_netplayer_stats_request(ubyte player_num);

void multi_endlevel_score(void);
void multi_prep_level(void);
int multi_endlevel(int *secret);
int multi_menu_poll(void);
void multi_leave_game(void);
void multi_process_data(unsigned char *dat, int len);
void multi_process_bigdata(unsigned char *buf, int len);		
void multi_do_death(int objnum);
void multi_send_message_dialog(void);
int multi_delete_extra_objects(void);
void multi_make_ghost_player(int objnum);
void multi_make_player_ghost(int objnum);
void multi_define_macro(int key);
void multi_send_macro(int key);
int multi_get_kill_list(int *plist);
void multi_new_game(void);
void multi_sort_kill_list(void);
int multi_choose_mission(int *anarchy_only);
void multi_reset_stuff(void);

void multi_send_data(unsigned char *buf, int len, int repeat);

int get_team(int pnum);

// Exported variables

extern int Network_active;
extern int Network_laser_gun;
extern int Network_laser_fired;
extern int Network_laser_level;
extern int Network_laser_flags;

extern int message_length[MULTI_MAX_TYPE+1];
extern char multibuf[MAX_MULTI_MESSAGE_LEN+4];
extern short Network_laser_track;

extern int who_killed_controlcen;

extern int Net_create_objnums[MAX_NET_CREATE_OBJECTS];
extern int Net_create_loc;

extern short kill_matrix[MAX_NUM_NET_PLAYERS][MAX_NUM_NET_PLAYERS];
extern short team_kills[2];

extern int multi_goto_secret;

//do we draw the kill list on the HUD?
extern int Show_kill_list;
extern int Show_reticle_name;
extern fix Show_kill_list_timer;

// Used to send network messages

extern char	Network_message[MAX_MESSAGE_LEN];
extern char Network_message_macro[4][MAX_MESSAGE_LEN];
extern int Network_message_reciever;

// Used to map network to local object numbers

extern short remote_to_local[MAX_NUM_NET_PLAYERS][MAX_OBJECTS];  // Network object num for each 
extern short local_to_remote[MAX_OBJECTS];   // Local object num for each network objnum
extern byte object_owner[MAX_OBJECTS]; // Who 'owns' each local object for network purposes

extern int multi_in_menu; // Flag to tell if we're executing GameLoop from within a newmenu.
extern int multi_leave_menu;
extern int multi_quit_game;

extern int multi_sending_message;
extern int multi_defining_message;
extern void multi_message_input_sub( int key );
extern void multi_send_message_start();

extern int control_invul_time;

#define N_PLAYER_SHIP_TEXTURES 6

extern bitmap_index multi_player_textures[MAX_NUM_NET_PLAYERS][N_PLAYER_SHIP_TEXTURES];

#define NETGAME_FLAG_CLOSED 	1
#define NETGAME_FLAG_SHOW_ID	2
#define NETGAME_FLAG_SHOW_MAP 4

#define NETGAME_NAME_LEN				15

typedef struct ipx_net_info {
	ubyte		server[4];							// 4
	ubyte		node[6];							// 6
	ushort		socket;								// 2
} ipx_net_info;

typedef struct netplayer_info {
	char		callsign[CALLSIGN_LEN+1];			// 9
	byte 		connected;							// 1
	union {
		ipx_net_info	ipx_info;
		AddrBlock		appletalk_info;
	} network_info;
} netplayer_info;

typedef struct netgame_info {
	ubyte					type;								//  1
	char					game_name[NETGAME_NAME_LEN+1];		// 16
	char					team_name[2][CALLSIGN_LEN+1];		// 18
	ubyte					gamemode;							//  1
	ubyte					difficulty;							//  1
	ubyte 					game_status;						//  1
	ubyte					numplayers;							//  1
	ubyte					max_numplayers;						//  1
	ubyte					game_flags;							//  1     --->   41 bytes total
	netplayer_info			players[MAX_PLAYERS];				//  starts byte 42  22*8 = 176
	int						locations[MAX_PLAYERS];
	short					kills[MAX_PLAYERS][MAX_PLAYERS];
	int						levelnum;
	ubyte					protocol_version;
	ubyte					team_vector;
	ushort					segments_checksum;
	short					team_kills[2];
	short					killed[MAX_PLAYERS];
	short					player_kills[MAX_PLAYERS];

#ifndef MAC_SHAREWARE
	fix						level_time;
	int						control_invul_time;
	int 					monitor_vector;
	int						player_score[MAX_PLAYERS];
	ubyte					player_flags[MAX_PLAYERS];
	char					mission_name[9];
	char					mission_title[MISSION_NAME_LEN+1];
#endif

} netgame_info;

extern struct netgame_info Netgame;

int network_i_am_master(void);
void change_playernum_to(int new_pnum);

#endif

#endif
