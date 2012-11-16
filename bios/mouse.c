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
 * $Source: BigRed:miner:source:bios::RCS:mouse.c $
 * $Revision: 1.8 $
 * $Author: allender $
 * $Date: 1996/02/21 13:57:36 $
 * 
 * Functions to access Mouse and Cyberman...
 * 
 * $Log: mouse.c $
 * Revision 1.8  1996/02/21  13:57:36  allender
 * cursor device manager stuff added here so as not to
 * rely on InterfaceLib anymore
 *
 * Revision 1.7  1995/10/17  15:42:21  allender
 * new mouse function to determine single button press
 *
 * Revision 1.6  1995/10/03  11:27:31  allender
 * fixed up hotspot problems with the mouse on multiple monitors
 *
 * Revision 1.5  1995/07/13  11:27:08  allender
 * trap button checks at MAX_MOUSE_BUTTONS
 *
 * Revision 1.4  1995/06/25  21:56:53  allender
 * added events include
 *
 * Revision 1.3  1995/05/11  17:06:38  allender
 * fixed up mouse routines
 *
 * Revision 1.2  1995/05/11  13:05:53  allender
 * of mouse handler code
 *
 * Revision 1.1  1995/05/05  09:54:45  allender
 * Initial revision
 *
 * Revision 1.9  1995/01/14  19:19:52  john
 * Fixed signed short error cmp with -1 that caused mouse
 * to break under Watcom 10.0
 * 
 * Revision 1.8  1994/12/27  12:38:23  john
 * Made mouse use temporary dos buffer instead of
 * 
 * allocating its own.
 * 
 * 
 * Revision 1.7  1994/12/05  23:54:53  john
 * Fixed bug with mouse_get_delta only returning positive numbers..
 * 
 * Revision 1.6  1994/11/18  23:18:18  john
 * Changed some shorts to ints.
 * 
 * Revision 1.5  1994/09/13  12:34:02  john
 * Added functions to get down count and state.
 * 
 * Revision 1.4  1994/08/29  20:52:19  john
 * Added better cyberman support; also, joystick calibration
 * value return funcctiionn,
 * 
 * Revision 1.3  1994/08/24  18:54:32  john
 * *** empty log message ***
 * 
 * Revision 1.2  1994/08/24  18:53:46  john
 * Made Cyberman read like normal mouse; added dpmi module; moved
 * mouse from assembly to c. Made mouse buttons return time_down.
 * 
 * Revision 1.1  1994/08/24  13:56:37  john
 * Initial revision
 * 
 * 
 */


#pragma off (unreferenced)
static char rcsid[] = "$Id: mouse.c 1.8 1996/02/21 13:57:36 allender Exp $";
#pragma on (unreferenced)

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <Timer.h>
#include <Events.h>
#include <Traps.h>
#include <CursorDevices.h>
#include <Quickdraw.h>

#include "error.h"
#include "fix.h"
#include "mouse.h"
#include "gtimer.h"
#include "macsys.h"

#define ME_CURSOR_MOVED	(1<<0)
#define ME_LB_P 			(1<<1)
#define ME_LB_R 			(1<<2)
#define ME_RB_P 			(1<<3)
#define ME_RB_R 			(1<<4)
#define ME_MB_P 			(1<<5)
#define ME_MB_R 			(1<<6)
#define ME_OB_P 			(1<<7)
#define ME_OB_R 			(1<<8)
#define ME_X_C 			(1<<9)
#define ME_Y_C 			(1<<10)
#define ME_Z_C 			(1<<11)
#define ME_P_C 			(1<<12)
#define ME_B_C 			(1<<13)
#define ME_H_C 			(1<<14)
#define ME_O_C 			(1<<15)

#define MOUSE_MAX_BUTTONS	11

typedef struct event_info {
	short x;
	short y;
	short z;
	short pitch;
	short bank;
	short heading;
	ushort button_status;
	ushort device_dependant;
} event_info;

typedef struct mouse_info {
	fix		ctime;
	ubyte	cyberman;
	int		num_buttons;
	ubyte	pressed[MOUSE_MAX_BUTTONS];
	fix		time_went_down[MOUSE_MAX_BUTTONS];
	fix		time_held_down[MOUSE_MAX_BUTTONS];
	uint	num_downs[MOUSE_MAX_BUTTONS];
	uint	num_ups[MOUSE_MAX_BUTTONS];
	ubyte	went_down;
	event_info *x_info;
	ushort	button_status;
} mouse_info;

typedef struct cyberman_info {
	ubyte device_type;
	ubyte major_version;
	ubyte minor_version;
	ubyte x_descriptor;
	ubyte y_descriptor;
	ubyte z_descriptor;
	ubyte pitch_descriptor;
	ubyte roll_descriptor;
	ubyte yaw_descriptor;
	ubyte reserved;
} cyberman_info;

static mouse_info Mouse;

static int Mouse_installed = 0;

static CursorDevice *mousedev = NULL;

static ubyte use_lowmem=0;
static Point center_p;

#define xRawMouse	0x082C			// low memory global that has current mouse loc
#define xMTemp		0x0828			// low memory global that has current mouse loc
#define xCrsrNew	0x08CE			// set after you change mtemp and rawmouse
#define xCrsrCouple	0x08CF			// true if the cursor is tied to the mouse
#if GENERATINGPOWERPC
enum {
	glueUppCursorDeviceMoveProcInfo =
		kD0DispatchedPascalStackBased |
		DISPATCHED_STACK_ROUTINE_SELECTOR_SIZE(kTwoByteCode) |
		RESULT_SIZE(SIZE_CODE(sizeof (OSErr))) |
		DISPATCHED_STACK_ROUTINE_PARAMETER(1,SIZE_CODE(sizeof (CursorDevicePtr))) |
		DISPATCHED_STACK_ROUTINE_PARAMETER(2,SIZE_CODE(sizeof (long))) |
		DISPATCHED_STACK_ROUTINE_PARAMETER(3,SIZE_CODE(sizeof (long))),
	glueUppCursorDeviceMoveToProcInfo =
		kD0DispatchedPascalStackBased |
		DISPATCHED_STACK_ROUTINE_SELECTOR_SIZE(kTwoByteCode) |
		RESULT_SIZE(SIZE_CODE(sizeof (OSErr))) |
		DISPATCHED_STACK_ROUTINE_PARAMETER(1,SIZE_CODE(sizeof (CursorDevicePtr))) |
		DISPATCHED_STACK_ROUTINE_PARAMETER(2,SIZE_CODE(sizeof (long))) |
		DISPATCHED_STACK_ROUTINE_PARAMETER(3,SIZE_CODE(sizeof (long))),
	glueUppCursorDeviceFlushProcInfo =
		kD0DispatchedPascalStackBased |
		DISPATCHED_STACK_ROUTINE_SELECTOR_SIZE(kTwoByteCode) |
		RESULT_SIZE(SIZE_CODE(sizeof (OSErr))) |
		DISPATCHED_STACK_ROUTINE_PARAMETER(1,SIZE_CODE(sizeof (CursorDevicePtr))),
	glueUppCursorDeviceButtonsProcInfo =
		kD0DispatchedPascalStackBased |
		DISPATCHED_STACK_ROUTINE_SELECTOR_SIZE(kTwoByteCode) |
		RESULT_SIZE(SIZE_CODE(sizeof (OSErr))) |
		DISPATCHED_STACK_ROUTINE_PARAMETER(1,SIZE_CODE(sizeof (CursorDevicePtr))) |
		DISPATCHED_STACK_ROUTINE_PARAMETER(2,SIZE_CODE(sizeof (short))),
	glueUppCursorDeviceButtonDownProcInfo =
		kD0DispatchedPascalStackBased |
		DISPATCHED_STACK_ROUTINE_SELECTOR_SIZE(kTwoByteCode) |
		RESULT_SIZE(SIZE_CODE(sizeof (OSErr))) |
		DISPATCHED_STACK_ROUTINE_PARAMETER(1,SIZE_CODE(sizeof (CursorDevicePtr))),
	glueUppCursorDeviceButtonUpProcInfo =
		kD0DispatchedPascalStackBased |
		DISPATCHED_STACK_ROUTINE_SELECTOR_SIZE(kTwoByteCode) |
		RESULT_SIZE(SIZE_CODE(sizeof (OSErr))) |
		DISPATCHED_STACK_ROUTINE_PARAMETER(1,SIZE_CODE(sizeof (CursorDevicePtr))),
	glueUppCursorDeviceButtonOpProcInfo =
		kD0DispatchedPascalStackBased |
		DISPATCHED_STACK_ROUTINE_SELECTOR_SIZE(kTwoByteCode) |
		RESULT_SIZE(SIZE_CODE(sizeof (OSErr))) |
		DISPATCHED_STACK_ROUTINE_PARAMETER(1,SIZE_CODE(sizeof (CursorDevicePtr))) |
		DISPATCHED_STACK_ROUTINE_PARAMETER(2,SIZE_CODE(sizeof (short))) |
		DISPATCHED_STACK_ROUTINE_PARAMETER(3,SIZE_CODE(sizeof (ButtonOpcode))) |
		DISPATCHED_STACK_ROUTINE_PARAMETER(4,SIZE_CODE(sizeof (long))),
	glueUppCursorDeviceSetButtonsProcInfo =
		kD0DispatchedPascalStackBased |
		DISPATCHED_STACK_ROUTINE_SELECTOR_SIZE(kTwoByteCode) |
		RESULT_SIZE(SIZE_CODE(sizeof (OSErr))) |
		DISPATCHED_STACK_ROUTINE_PARAMETER(1,SIZE_CODE(sizeof (CursorDevicePtr))) |
		DISPATCHED_STACK_ROUTINE_PARAMETER(2,SIZE_CODE(sizeof (short))),
	glueUppCursorDeviceSetAccelerationProcInfo =
		kD0DispatchedPascalStackBased |
		DISPATCHED_STACK_ROUTINE_SELECTOR_SIZE(kTwoByteCode) |
		RESULT_SIZE(SIZE_CODE(sizeof (OSErr))) |
		DISPATCHED_STACK_ROUTINE_PARAMETER(1,SIZE_CODE(sizeof (CursorDevicePtr))) |
		DISPATCHED_STACK_ROUTINE_PARAMETER(2,SIZE_CODE(sizeof (Fixed))),
	glueUppCursorDeviceDoubleTimeProcInfo =
		kD0DispatchedPascalStackBased |
		DISPATCHED_STACK_ROUTINE_SELECTOR_SIZE(kTwoByteCode) |
		RESULT_SIZE(SIZE_CODE(sizeof (OSErr))) |
		DISPATCHED_STACK_ROUTINE_PARAMETER(1,SIZE_CODE(sizeof (CursorDevicePtr))) |
		DISPATCHED_STACK_ROUTINE_PARAMETER(2,SIZE_CODE(sizeof (long))),
	glueUppCursorDeviceUnitsPerInchProcInfo =
		kD0DispatchedPascalStackBased |
		DISPATCHED_STACK_ROUTINE_SELECTOR_SIZE(kTwoByteCode) |
		RESULT_SIZE(SIZE_CODE(sizeof (OSErr))) |
		DISPATCHED_STACK_ROUTINE_PARAMETER(1,SIZE_CODE(sizeof (CursorDevicePtr))) |
		DISPATCHED_STACK_ROUTINE_PARAMETER(2,SIZE_CODE(sizeof (Fixed))),
	glueUppCursorDeviceNextDeviceProcInfo =
		kD0DispatchedPascalStackBased |
		DISPATCHED_STACK_ROUTINE_SELECTOR_SIZE(kTwoByteCode) |
		RESULT_SIZE(SIZE_CODE(sizeof (OSErr))) |
		DISPATCHED_STACK_ROUTINE_PARAMETER(1,SIZE_CODE(sizeof (CursorDevicePtr *))),
	glueUppCursorDeviceNewDeviceProcInfo =
		kD0DispatchedPascalStackBased |
		DISPATCHED_STACK_ROUTINE_SELECTOR_SIZE(kTwoByteCode) |
		RESULT_SIZE(SIZE_CODE(sizeof (OSErr))) |
		DISPATCHED_STACK_ROUTINE_PARAMETER(1,SIZE_CODE(sizeof (CursorDevicePtr *))),
	glueUppCursorDeviceDisposeDeviceProcInfo =
		kD0DispatchedPascalStackBased |
		DISPATCHED_STACK_ROUTINE_SELECTOR_SIZE(kTwoByteCode) |
		RESULT_SIZE(SIZE_CODE(sizeof (OSErr))) |
		DISPATCHED_STACK_ROUTINE_PARAMETER(1,SIZE_CODE(sizeof (CursorDevicePtr)))
};
#endif

OSErr
glueCursorDeviceNextDevice(
	CursorDevicePtr *ourDevice)
{
#if GENERATINGPOWERPC
	return CallUniversalProc(
		GetToolboxTrapAddress(_CursorDeviceDispatch),
		glueUppCursorDeviceNextDeviceProcInfo,
		0xB, ourDevice);
#else
	return CursorDeviceNextDevice(ourDevice);
#endif
}

OSErr
glueCursorDeviceMoveTo(
	CursorDevicePtr ourDevice,
	long absX,
	long absY)
{
#if GENERATINGPOWERPC
	return CallUniversalProc(
		GetToolboxTrapAddress(_CursorDeviceDispatch),
		glueUppCursorDeviceMoveToProcInfo,
		1, ourDevice, absX, absY);
#else
	return CursorDeviceMoveTo(ourDevice, absX, absY);
#endif
}

void
SetMouseDevicePosition(
	Point newPoint)
{
	CursorDevice *firstMouse;
	long delay;

	if (!use_lowmem) {
		firstMouse = NULL;
//		glueCursorDeviceNextDevice(&firstMouse);
//		glueCursorDeviceMoveTo(firstMouse, (long) newPoint.h, (long) newPoint.v);
		glueCursorDeviceMoveTo(mousedev, (long) newPoint.h, (long) newPoint.v);
		Delay(1, &delay);								// why is this necessary?! cbs
	} else {
		*(Point *) xRawMouse = newPoint;
		*(Point *) xMTemp = newPoint;
		*(Ptr) xCrsrNew = *(Ptr) xCrsrCouple;			// Set CrsrNew if coupled
#if !GENERATINGPOWERPC
		CallCursorTask();								// must call jCrsrTask to update system
#endif
	}
}

void mouse_handler()
{
	int button_state;
	
	Mouse.ctime = timer_get_fixed_seconds();
	button_state = Button();
	
	if (button_state) {
		if (!Mouse.pressed[MB_LEFT]) {
			Mouse.pressed[MB_LEFT] = 1;
			Mouse.time_went_down[MB_LEFT] = Mouse.ctime;
			Mouse.went_down = 1;
		}
		Mouse.num_downs[MB_LEFT]++;
	} else {
		if (Mouse.pressed[MB_LEFT]) {
			Mouse.pressed[MB_LEFT] = 0;
			Mouse.time_held_down[MB_LEFT] += Mouse.ctime-Mouse.time_went_down[MB_LEFT];
			Mouse.num_ups[MB_LEFT]++;
			Mouse.went_down = 0;
		}
	}
}

void mouse_flush()
{
	int i;
	fix CurTime;
	
	if (!Mouse_installed)
		return;

//	_disable();
	CurTime = timer_get_fixed_seconds();
	for (i = 0; i < MOUSE_MAX_BUTTONS; i++) {
		Mouse.pressed[i] = 0;
		Mouse.time_went_down[i] = CurTime;
		Mouse.time_held_down[i] = 0;
		Mouse.num_downs[i] = 0;
		Mouse.num_ups[i] = 0;
	}
	Mouse.went_down = 0;
//	_enable();
}

void mouse_set_center()
{
	center_p.h = (*GameMonitor)->gdRect.left + (((*GameMonitor)->gdRect.right - (*GameMonitor)->gdRect.left) / 2);
	center_p.v = (*GameMonitor)->gdRect.top + (((*GameMonitor)->gdRect.bottom - (*GameMonitor)->gdRect.top) / 2);
}

void mouse_close()
{
	if (Mouse_installed)
		Mouse_installed = 0;
}

#define CursorDeviceTrap	0xaadb

int mouse_init()
{
	if (Mouse_installed)
		return Mouse.num_buttons;
		
	if (NGetTrapAddress(CursorDeviceTrap, ToolTrap) != NGetTrapAddress(_Unimplemented, ToolTrap)) {
		glueCursorDeviceNextDevice(&mousedev); // get the next cursor device
	} else {
		use_lowmem = 1;
	}

	Mouse.num_buttons = 1;
	Mouse_installed = 1;
	atexit(mouse_close);
	mouse_flush();
	mouse_set_center();	
	
	return Mouse.num_buttons;
}

void mouse_set_limits( int x1, int y1, int x2, int y2 )
{
}

void mouse_get_pos( int *x, int *y)
{
	Point mcoords;

	GetMouse(&mcoords);
//	*x = mcoords.h + (*GameMonitor)->gdRect.left;
//	*y = mcoords.v + (*GameMonitor)->gdRect.top;
	*x = mcoords.h;
	*y = mcoords.v;
}

void mouse_get_delta( int *dx, int *dy )
{
	Point mcoords;
	
	if (!Mouse_installed) {
		*dx = *dy = 0;
		return;
	}
	GetMouse(&mcoords);
	LocalToGlobal(&mcoords);
	*dx = -(center_p.h - mcoords.h);
	*dy = -(center_p.v - mcoords.v);

// reset the mouse coords to the center of the screen
//	if (!use_lowmem) {
//		glueCursorDeviceMoveTo(mousedev, (long)center_p.h, (long)center_p.v);
//	} else {
//		*(Point *)xRawMouse = mcoords;
//		*(Point *)xMTemp = mcoords;
//		*(Ptr)xCrsrNew = *(Ptr)xCrsrCouple; // Set CrsrNew if coupled
//		CallCrsr();             // must call jCrsrTask to update system
//	}

	SetMouseDevicePosition(center_p);

}

int mouse_get_btns()
{
	int i;
	uint flag=1;
	int status = 0;
	
	if (!Mouse_installed)
		return 0;
		
	for (i = 0; i < MOUSE_MAX_BUTTONS; i++) {
		if (Mouse.pressed[i])
			status |= flag;
		flag <<= 1;
	}
	return status;
}

void mouse_set_pos( int x, int y)
{
}

int mouse_went_down(int button)
{
	int count;
	if (!Mouse_installed)
		return 0;
	if ((button < 0) || (button >= MOUSE_MAX_BUTTONS))
		return 0;

//	_disable();		
	count = (int)Mouse.went_down;
	Mouse.went_down = 0;
// 	_enable();
	return count;
}

// Returns how many times this button has went down since last call.
int mouse_button_down_count(int button)	
{
	int count;
	
	if (!Mouse_installed)
		return 0;
		
	if ((button < 0) || (button >= MOUSE_MAX_BUTTONS))
		return 0;
		
//	_disable();
	count = Mouse.num_downs[button];
	Mouse.num_downs[button] = 0;
//	_enable();
	return count;
}

// Returns 1 if this button is currently down
int mouse_button_state(int button)	
{
	int state;

	if (!Mouse_installed)
		return 0;
	
	if ((button < 0) || (button >= MOUSE_MAX_BUTTONS))
		return 0;

//	_disable();
	state = Mouse.pressed[button];
//	_enable();
	return state;
}

// Returns how long this button has been down since last call.
fix mouse_button_down_time(int button)	
{
	fix time_down, time;
	
	if (!Mouse_installed)
		return 0;
		
	if ((button < 0) || (button >= MOUSE_MAX_BUTTONS))
		return 0;

//	_disable();
	if (!Mouse.pressed[button]) {
		time_down = Mouse.time_held_down[button];
		Mouse.time_held_down[button] = 0;
	} else {
		time = timer_get_fixed_seconds();
		time_down = time - Mouse.time_held_down[button];
		Mouse.time_held_down[button] = 0;
	}
//	_enable();

	return time_down;
}

void mouse_get_cyberman_pos( int *x, int *y )
{
}

