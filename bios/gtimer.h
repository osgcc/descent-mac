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
 * $Source: Smoke:miner:source:bios::RCS:gtimer.h $
 * $Revision: 1.2 $
 * $Author: allender $
 * $Date: 1995/05/11 13:04:25 $
 *
 * Header for timer functions
 *
 * $Log: gtimer.h $
 * Revision 1.2  1995/05/11  13:04:25  allender
 * no a5 references if under powerPC code
 *
 * Revision 1.1  1995/05/05  09:31:09  allender
 * Initial revision
 *
 * Revision 1.1  1995/03/21  13:32:43  allender
 * Initial revision
 *
 *
 * --- PC RCS information ---
 * Revision 1.5  1994/11/15  12:04:15  john
 * Cleaned up timer code a bit... took out unused functions
 * like timer_get_milliseconds, etc.
 * 
 * Revision 1.4  1994/04/28  23:50:08  john
 * Changed calling for init_timer.  Made the function that the
 * timer calls be a far function. All of this was done to make
 * our timer system compatible with the HMI sound stuff.
 * 
 * Revision 1.3  1994/02/17  15:57:12  john
 * Changed key libary to C.
 * 
 * Revision 1.2  1994/01/18  10:58:34  john
 * Added timer_get_fixed_seconds
 * 
 * Revision 1.1  1993/07/10  13:10:41  matt
 * Initial revision
 * 
 *
 */
 
#include "fix.h"
 
typedef struct timer_info
{
	TMTask timer_task;
#ifndef __powerc
	ulong current_a5;
#endif
} timer_info;

//==========================================================================
// This installs the timer services and interrupts at the rate specified by
// count_val.  If 'function' isn't 0, the function pointed to by function will
// be called 'freq' times per second.  Should be > 19 and anything around
// 2-3000 is gonna start slowing down the system.  Count_val should be
// 1,193,180 divided by your target frequency. Use 0 for the normal 18.2 Hz
// interrupt rate.

#define TIMER_FREQUENCY 1193180

extern void timer_init();
extern void timer_close();
extern void timer_set_rate(int count_val);
extern void timer_set_function( void *function );
extern void delay(int d_time);

//==========================================================================
// These functions return the time since the timer was initialized in
// some various units. The total length of reading time varies for each
// one.  They will roll around after they read 2^32.
// There are milliseconds, milliseconds times 10, milliseconds times 100,
// and microseconds.  They time out after 1000 hrs, 100 hrs, 10 hrs, and
// 1 hr, respectively.

extern fix timer_get_fixed_seconds();	// Rolls about every 9 hours...
extern fix timer_get_fixed_secondsX(); // Assume interrupts already disabled

//NOT_USED extern unsigned int timer_get_microseconds();
//NOT_USED extern unsigned int timer_get_milliseconds100();
//NOT_USED extern unsigned int timer_get_milliseconds10();
//NOT_USED extern unsigned int timer_get_milliseconds();
//NOT_USED extern unsigned int timer_get_millisecondsX();	// Assume interrupts disabled

//==========================================================================
// Use to access the BIOS ticker... ie...   i = TICKER
#define TICKER (*(volatile int *)0x46C)
#define USECS_PER_READING( start, stop, frames ) (((stop-start)*54945)/frames)

