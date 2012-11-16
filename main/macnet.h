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
 * $Source: Smoke:miner:source:main::RCS:macnet.h $
 * $Revision: 1.3 $
 * $Author: allender $
 * $Date: 1995/09/13 08:47:00 $
 *
 * Header file for macintosh specific networking stuff
 *
 */
 
 #include "dtypes.h"
 #include "network.h"
 #include "multi.h"
 #include "object.h"

void receive_netplayer_info(ubyte *data, netplayer_info *info);
void send_sequence_packet(sequence_packet seq, ubyte *server, ubyte *node, ubyte *net_address);
void receive_sequence_packet(ubyte *data, sequence_packet *seq);

void send_netgame_packet(ubyte *server, ubyte *node);
void receive_netgame_packet(ubyte *data, netgame_info *netgame);

void send_frameinfo_packet(ubyte *server, ubyte *node, ubyte *address);
void receive_frameinto_packet(ubyte *data, frame_info *info);

void send_endlevel_packet(endlevel_info *info, ubyte *server, ubyte *node, ubyte *address);
void receive_endlevel_packet(ubyte *data, endlevel_info *info);

void swap_object(object *obj);
