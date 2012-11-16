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
 * $Source: Smoke:miner:source:main::RCS:NETIPX.C $
 * $Revision: 1.1 $
 * $Author: allender $
 * $Date: 1995/05/16 15:28:34 $
 * 
 * Routines to access ipx network
 * 
 * $Log: NETIPX.C $
 * Revision 1.1  1995/05/16  15:28:34  allender
 * Initial revision
 *
 * Revision 1.5  1994/07/13  16:05:39  john
 * *** empty log message ***
 * 
 * Revision 1.4  1994/07/13  16:04:15  john
 * *** empty log message ***
 * 
 * Revision 1.3  1994/05/11  19:45:30  john
 * *** empty log message ***
 * 
 * Revision 1.2  1994/05/11  18:44:02  john
 * Added first attemp at networking.
 * 
 * Revision 1.1  1994/05/11  16:06:47  john
 * Initial revision
 * 
 * 
 */


#pragma off (unreferenced)
static char rcsid[] = "$Id: NETIPX.C 1.1 1995/05/16 15:28:34 allender Exp $";
#pragma on (unreferenced)

#include <dos.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include <conio.h>

#include "dtypes.h"
#include "netipx.h"
#include "args.h"
#include "timer.h"

doomcom_t *netipx_common;

void netipx_play_game();

void netipx_get_packet()	{
#if 0
	union REGS regs;

	netipx_common->command = CMD_GET;

	int386( netipx_common->intnum, &regs, &regs );
#endif
}

void netipx_send_packet(int node, int datalen, ubyte * data )	{
#if 0
	union REGS regs;

	if ( datalen < 1 ) return;

	netipx_common->command = CMD_SEND;
	netipx_common->remotenode = node;
	netipx_common->datalength = datalen;
	memcpy( &netipx_common->data[0], data, datalen );

	int386( netipx_common->intnum, &regs, &regs );
#endif
}


void netipx_init()
{
	int i;	//,t = 0;
	//int t1;	//, t2;
	//char c = 0;
	//char text[200];

	if ( (i=FindArg( "-net" )) )	{
		printf( "Value = '%s'\n", Args[i+1] );
		netipx_common = (doomcom_t *)atoi( Args[i+1] );
		printf( "Using shared address space of %d\n", (int)netipx_common );
		printf( "Communicating with vector 0x%x\n", netipx_common->intnum );
		printf( "Console is player %d/%d\n", netipx_common->consoleplayer, netipx_common->numplayers );

	/*	t = 0;
		while(c != 27 )	{
			netipx_get_packet();
			if ( netipx_common->remotenode > -1 )	{
				printf( "Got message of length %d from %d, '%s'\n", netipx_common->datalength,netipx_common->remotenode, netipx_common->data  );
			}
			if ( kbhit() )	{
				c = getch();
				if ( (c==10) || (c==13) )	{
					text[t++] = '\0';
					printf( "Sending '%s'\n", text );
					for (i=1; i < netipx_common->numnodes; i++ )
						netipx_send_packet( i, t, text );
					t = 0;
				} else {
					text[t++] = c;
				}
			}
		}
	*/
		netipx_play_game();
	}
}

typedef struct player {
	int id,x,y;
} player;

player Players[4];
player OldPlayers[4];


#include "key.h"

void netipx_play_game()	
{
	int i, n;
	unsigned short *screen = (unsigned short *)0xB8000;
	player * temp;

	timer_init();
	key_init();

	for (i=0; i < netipx_common->numplayers; i++ )	{
		Players[i].x = i;
		Players[i].y = 0;
	}

	Players[0].id = netipx_common->consoleplayer;

//	if (netipx_common->consoleplayer==0 )	{
//		Players[0].x = 0; Players[0].y = 0;
//		Players[1].x = 79; Players[1].y = 24;
//	} else {
//		Players[1].x = 0; Players[1].y = 0;
//		Players[0].x = 79; Players[0].y = 24;
//	}

	for (i=0; i<25*80; i++ )	{
		screen[i] = (0x07<<8)|32;
	}

	while	(!keyd_pressed[KEY_ESC] )	{
		//k = key_inkey();

		for (i=0; i < netipx_common->numplayers; i++ )	{
			OldPlayers[i] = Players[i];
		}

		Players[0].x += keyd_pressed[KEY_RIGHT] - keyd_pressed[KEY_LEFT];
		Players[0].y += keyd_pressed[KEY_DOWN] - keyd_pressed[KEY_UP];
		if ( Players[0].x < 0 ) Players[0].x = 0;
		if ( Players[0].x > 79 ) Players[0].x = 79;
		if ( Players[0].y < 0 ) Players[0].y = 0;
		if ( Players[0].y > 24 ) Players[0].y = 24;

		for (i=1; i < netipx_common->numnodes; i++ )	{
			netipx_send_packet( i, sizeof(player), (ubyte *)&Players[0] );
		}
		n = 0;

		while( n < netipx_common->numplayers-1 )	{
			netipx_get_packet();
			if (keyd_pressed[KEY_ESC]) break;
			if ( netipx_common->remotenode > -1 )	{
				temp = (player *)netipx_common->data;
				Players[netipx_common->remotenode] = *temp;
				n++;
			}
		}

		for (i=0; i<netipx_common->numplayers; i++ )	{
			screen[OldPlayers[i].y*80+OldPlayers[i].x] = (0x07<<8)|(' ');
			screen[Players[i].y*80+Players[i].x] = (0x07<<8)|(Players[i].id+'0');
		}

		delay(8);

	}
	exit(0);
}

