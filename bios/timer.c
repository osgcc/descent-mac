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
 * $Source: Smoke:miner:source:bios::RCS:timer.c $
 * $Revision: 1.7 $
 * $Author: allender $
 * $Date: 1995/09/13 08:38:08 $
 * 
 * Functions for timers.
 * 
 * $Log: timer.c $
 * Revision 1.7  1995/09/13  08:38:08  allender
 * added control macros and put in correct support for 68k
 *
 * Revision 1.6  1995/08/31  14:40:09  allender
 * multiply by F1_0/160 instead of dividing
 *
 * Revision 1.5  1995/05/15  13:55:52  allender
 * change prototype for timer_proc
 *
 * Revision 1.4  1995/05/11  13:06:07  allender
 * remove a5 references under PowerPC code
 *
 * Revision 1.3  1995/05/04  20:03:03  allender
 * added two functions, timer_approx_seconds, and delay
 *
 * Revision 1.2  1995/03/21  13:40:01  allender
 * *** empty log message ***
 *
 * Revision 1.1  1995/03/21  13:31:33  allender
 * Initial revision
 *
 */
 
#include <Timer.h>
#include <GestaltEqu.h>
#include "dtypes.h"
#include "gtimer.h"

#define COUNTER_TIME	-6250
#define COUNTER_RATE	160
#define INV_TIMER_COUNT	0.00625

static int Installed = 0;
static uint timer_count;

timer_info ctimer_info;

#ifdef __powerc
UniversalProcPtr timer_proc;
#else
TimerUPP timer_proc;
#endif

#define _disable_timer()	RmvTime((QElemPtr)(&ctimer_info))
#ifdef __powerc
#define _enable_timer() \
	ctimer_info.timer_task.tmAddr = timer_proc; \
	ctimer_info.timer_task.tmWakeUp = 0; \
	ctimer_info.timer_task.tmReserved = 0; \
	InsXTime((QElemPtr)(&ctimer_info)); \
	PrimeTime((QElemPtr)(&ctimer_info), COUNTER_TIME);
#else
#define _enable_timer() \
	ctimer_info.timer_task.tmAddr = timer_proc; \
	ctimer_info.timer_task.tmWakeUp = 0; \
	ctimer_info.timer_task.tmReserved = 0; \
	ctimer_info.current_a5 = SetCurrentA5(); \
	InsXTime((QElemPtr)(&ctimer_info)); \
	PrimeTime((QElemPtr)(&ctimer_info), COUNTER_TIME);
#endif


#ifndef __powerc
timer_info *GetTMInfo(void) = { 0x2e89 };
#endif

fix timer_get_approx_seconds()
{
	int x;
	
	x = timer_count;
#ifdef __powerc
	return (fix)(((double)x * INV_TIMER_COUNT) * F1_0);
#else
	return fixmuldiv(x, 65536, COUNTER_RATE);
#endif
}

fix timer_get_fixed_seconds()
{
	int x;

//	_disable_timer();	
	x = timer_count;
//	_enable_timer();
#ifdef __powerc
	return (fix)(((double)x * INV_TIMER_COUNT) * F1_0);
#else
	return fixmuldiv(x, 65536, COUNTER_RATE);
#endif
}

void delay(int d_time)
{
	fix t, total;
	
	total = (F1_0 * d_time) / 1000;
	t = timer_get_fixed_seconds();
	while (timer_get_fixed_seconds() - t < total) ;
}

#ifndef __powerc
pascal void counter_timer()
#else
void counter_timer(timer_info *tm_info)
#endif
{
#ifndef __powerc
	timer_info *tminfo;
	long olda5;
	
	tminfo = GetTMInfo();
	olda5 = SetA5(tminfo->current_a5);
#endif

	timer_count++;
	PrimeTime((QElemPtr)(&ctimer_info), COUNTER_TIME);
	
#ifndef __powerc
	olda5 = SetA5(olda5);
#endif
}

void timer_close()
{
	if (!Installed)
		return;
//	RmvTime((QElemPtr)(&ctimer_info));
	_disable_timer();
	Installed = 0;
}

void timer_init()
{
	long tm_ver;

	if (Installed)
		return;

	if (Installed)
		return;
	Installed = 1;		
	
//  first, install the time task which just keeps track of elapsed seconds for
//  us.  We will set the timer rate equal to that of the PC timer for convenience.

	timer_proc = NewTimerProc(counter_timer);
	timer_count = 0;
	_enable_timer();

#if 0
	ctimer_info.timer_task.tmAddr = timer_proc;
	ctimer_info.timer_task.tmWakeUp = 0;
	ctimer_info.timer_task.tmReserved = 0;
	
#ifndef __powerc
	ctimer_info.current_a5 = SetCurrentA5();
#endif

	InsXTime((QElemPtr)(&ctimer_info));
	
//  prime the timer.

	PrimeTime((QElemPtr)(&ctimer_info), COUNTER_TIME);
#endif
	
	atexit(timer_close);
}
