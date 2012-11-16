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
 * $Source: Smoke:miner:source:bios::RCS:joyc.c $
 * $Revision: 1.6 $
 * $Author: allender $
 * $Date: 1995/10/30 11:10:44 $
 * 
 * Routines for joystick reading.
 * 
 * $Log: joyc.c $
 * Revision 1.6  1995/10/30  11:10:44  allender
 * lock down adb structures for stick info to try and get by
 * VM bug in 7.5 -- not quite yet though
 *
 * Revision 1.5  1995/10/17  15:36:05  allender
 * new joystick code ala Dave D w/o Flightstick pro support
 *
 * Revision 1.4  1995/08/18  10:16:48  allender
 * put back in some joystick functions -- added support
 * for thrustmaster stick direct reading of axis
 *
 * Revision 1.3  1995/07/26  16:58:17  allender
 * get coords right for joystick
 *
 * Revision 1.2  1995/06/25  21:56:04  allender
 * removed and modified joy handling routines for the mac
 *
 * Revision 1.1  1995/05/05  09:55:34  allender
 * Initial revision
 *
 * Revision 1.32  1995/01/12  13:16:40  john
 * Made it so that joystick can't lose an axis
 * by 1 weird reading. Reading has to occurr during
 * calibration for this to happen.
 * 
 * Revision 1.31  1994/12/28  15:56:03  john
 * Fixed bug that refused to read joysticks whose 
 * min,cen,max were less than 100 apart.
 * 
 * Revision 1.30  1994/12/28  15:31:53  john
 * Added code to read joystick axis not all at one time.
 * 
 * Revision 1.29  1994/12/27  15:44:36  john
 * Made the joystick timeout be at 1/100th of a second, 
 * regardless of CPU speed.
 * 
 * Revision 1.28  1994/12/04  11:54:54  john
 * Made stick read at whatever rate the clock is at, not
 * at 18.2 times/second.
 * 
 * Revision 1.27  1994/11/29  02:25:40  john
 * Made it so that the scaled reading returns 0 
 * if the calibration factors look funny..
 * 
 * Revision 1.26  1994/11/22  11:08:07  john
 * Commented out the ARCADE joystick.
 * 
 * Revision 1.25  1994/11/14  19:40:26  john
 * Fixed bug with no joystick being detected.
 * 
 * Revision 1.24  1994/11/14  19:36:40  john
 * Took out initial cheapy calibration.
 * 
 * Revision 1.23  1994/11/14  19:13:27  john
 * Took out the calibration in joy_init
 * 
 * Revision 1.22  1994/10/17  10:09:57  john
 * Made the state look at last_State, so that a joy_flush
 * doesn't cause a new down state to be added next reading.
 * 
 * Revision 1.21  1994/10/13  11:36:23  john
 * Made joy_down_time be kept track of in fixed seconds,
 * not ticks.
 * 
 * Revision 1.20  1994/10/12  16:58:50  john
 * Fixed bug w/ previous comment.
 * 
 * Revision 1.19  1994/10/12  16:57:44  john
 * Added function to set a joystick button's state.
 * 
 * Revision 1.18  1994/10/11  10:20:13  john
 * Fixed Flightstick Pro/
 * ..
 * 
 * Revision 1.17  1994/09/29  18:29:20  john
 * *** empty log message ***
 * 
 * Revision 1.16  1994/09/27  19:17:23  john
 * Added code so that is joy_init is never called, joystick is not
 * used at all.
 * 
 * Revision 1.15  1994/09/22  16:09:23  john
 * Fixed some virtual memory lockdown problems with timer and
 * joystick.
 * 
 * Revision 1.14  1994/09/16  11:44:42  john
 * Fixed bug with slow joystick.
 * 
 * Revision 1.13  1994/09/16  11:36:15  john
 * Fixed bug with reading non-present channels.
 * 
 * Revision 1.12  1994/09/15  20:52:48  john
 * rme john
 * Added support for the Arcade style joystick.
 * 
 * Revision 1.11  1994/09/13  20:04:49  john
 * Fixed bug with joystick button down_time.
 * 
 * Revision 1.10  1994/09/10  13:48:07  john
 * Made all 20 buttons read.
 * 
 * Revision 1.9  1994/08/31  09:55:02  john
 * *** empty log message ***
 * 
 * Revision 1.8  1994/08/29  21:02:14  john
 * Added joy_set_cal_values...
 * 
 * Revision 1.7  1994/08/29  20:52:17  john
 * Added better cyberman support; also, joystick calibration
 * value return funcctiionn,
 * 
 * Revision 1.6  1994/08/24  18:53:12  john
 * Made Cyberman read like normal mouse; added dpmi module; moved
 * mouse from assembly to c. Made mouse buttons return time_down.
 * 
 * Revision 1.5  1994/07/14  22:12:23  john
 * Used intrinsic forms of outp to fix vmm error.
 * 
 * Revision 1.4  1994/07/07  19:52:59  matt
 * Made joy_init() return success/fail flag
 * Made joy_init() properly detect a stick if one is plugged in after joy_init()
 * was called the first time.
 * 
 * Revision 1.3  1994/07/01  10:55:55  john
 * Fixed some bugs... added support for 4 axis.
 * 
 * Revision 1.2  1994/06/30  20:36:55  john
 * Revamped joystick code.
 * 
 * Revision 1.1  1994/06/30  15:42:15  john
 * Initial revision
 * 
 * 
 */


#pragma off (unreferenced)
static char rcsid[] = "$Id: joyc.c 1.6 1995/10/30 11:10:44 allender Exp $";
#pragma on (unreferenced)

#include <stdlib.h>
#include <stdio.h>
#include <Events.h>
#include <DeskBus.h>			// for ADB reading of joysticks

#include "types.h"
#include "mono.h"
#include "joy.h"
#include "mouse.h"
#include "JoyManager.h"			// for CH FlightStick Pro support
#include "macsys.h"


//****** Thrustmaster specific information follows

// CHANGING THE FOLLOWING FORCES RE-INITIALIZATION OF THE DEVICE SETTINGS
#define		THRUSTMASTER_STRUCT_VERSION	11		// STROKES

// OUR DEFAULT ADB ADDRESS AND HANDLER ID AS ISSUED TO THRUSTMASTER
// BY APPLE

#define		THRUSTMASTER_ADB_ADDR		7
#define		THRUSTMASTER_HANDLER_ID		0x5F

typedef struct ThrustmasterDevice {
	// CALIBRATED POSITION DATA FROM DEVICE(S)
		char			roll;		// -127 (left) ...+127 (right)
		char			pitch;		// -127 (forward/down) ...+127 (back/up)
		unsigned char	thrust;		// 0 (back) ...255 (forward)
		char			yaw;		// -127 (left) ...+127 (right)
	// THROTTLE BUTTON BITS:
		short		rockerDown	:1;		// 0 (open), 1 (closed)
		short		rockerUp	:1;
		short		button1		:1;
		short		button2		:1;
		short		button3		:1;
		short		button5		:1;
		short		button6		:1;
		short		button4		:1;
	// STICK BUTTON BITS:
		short		pinkey		:1;
		short		thumbLow	:1;
		short		trigger		:1;
		short		thumbHigh	:1;
		short		hatLeft		:1;
		short		hatRight	:1;
		short		hatDown		:1;
		short		hatUp		:1;
	// PADDING TO 8 BYTES (MAX ADB REGISTER SIZE)
		char	reserveByte1;
		char	reserveByte2;
	// DEVICE STRUCTURE VERSION NUMBER
		char	version;
	// THIS BYTE IS CLEARED BY THE DRIVER EACH TIME NEW DATA IS ACQUIRED AND CALIBRATED
		char	notNew;
	// DEVICE ATTACHMENT INDICATORS
		char	throttleAttached;
		char	rudderAttached;
	// MOUSING STUFF
		char	mouseDefeated;
	// PRIVATE STUFF
		long	dontTouch;
		long	fini;
	} ThrustmasterDevice;

static ThrustmasterDevice *tm_dev = NULL;

uint joy_thrustmaster_init (void);

//****** Thrustmaster specific information ends


//****** Advanced Gravis MouseStick specific information follows

#define		GRAVIS_SIGNATURE		0x4A656666

typedef struct GravisDevice {
	long		signature;				/* our signature */
	char		private1[18];
	short		numSticksConnected;		/* how many gamepads are available */
	char		private2[22];
	
			/* STICK 1 INFO */
	short		stick1_xIn;				/* absolute stick position */
	short		stick1_yIn;				/* absolute stick position */
	ubyte		stick1_buttons;			/* button states */
	ubyte		private3;
	short		stick1_xOut;			/* adjusted cursor position */
	short		stick1_yOut;			/* adjusted cursor position */
	char		stick1_old;				/* true if device is an old mousestick */
	char		private4;
	char		stick1_on;				/* pad is on or off */
	char		private5;	
	char		stick1_cursorCouple;	/* true if stick should move cursor */
	char		stick1_appAware;		/* is driver switching sets? */
	char		private6[152];
	
			/* STICK 2 INFO */
	short		stick2_xIn;				/* absolute stick position */
	short		stick2_yIn;				/* absolute stick position */
	ubyte		stick2_buttons;			/* button states */
	ubyte		private7;
	short		stick2_xOut;			/* adjusted cursor position */
	short		stick2_yOut;			/* adjusted cursor position */
	char		stick2_old;				/* true if device is an old mousestick */
	char		private8;
	char		stick2_on;				/* pad is on or off */
	char		private9;	
	char		stick2_cursorCouple;	/* true if stick should move cursor */
	char		stick2_appAware;		/* is driver switching sets? */
	char		private10[152];
	
	} GravisDevice;

static GravisDevice *ag_dev = NULL;

uint joy_gravis_init (void);

//****** Advanced Gravis MouseStick specific information ends


//****** CH FlightStick Pro specific information follows
#define CH_FLIGHTSTICK_PRO_CODE 0	// disabled since it doesn't work right

#if CH_FLIGHTSTICK_PRO_CODE
static uint flightstick_pro_init = 0;

uint joy_flightstick_pro_init (void);
#endif

//****** CH FlightStick Pro specific information ends

char joy_installed = 0;
char joy_present = 0;
char joy_type = 0;

typedef struct Joy_info {
	int			present_mask;
	int			axis_min[4];
	int			axis_center[4];
	int			axis_max[4];
} Joy_info;

Joy_info joystick;

void joy_get_cal_vals(int *axis_min, int *axis_center, int *axis_max)
{
	int i;

	for (i=0; i<4; i++)		{
		axis_min[i] = joystick.axis_min[i];
		axis_center[i] = joystick.axis_center[i];
		axis_max[i] = joystick.axis_max[i];
	}
}

void joy_set_cal_vals(int *axis_min, int *axis_center, int *axis_max)
{
	int i;

	for (i=0; i<4; i++)		{
		joystick.axis_min[i] = axis_min[i];
		joystick.axis_center[i] = axis_center[i];
		joystick.axis_max[i] = axis_max[i];
	}
}

void joy_set_type(ubyte type)
{
	joy_type = type;
	
	if(joy_type==JOY_AS_THRUSTMASTER)
	{
		if (!joy_thrustmaster_init())
		{
			joy_type = JOY_AS_NONE;
		}
	}
	else if(joy_type==JOY_AS_GRAVIS_MOUSESTICK)
	{
		if (!joy_gravis_init())
		{
			joy_type = JOY_AS_NONE;
		}
	}
#if CH_FLIGHTSTICK_PRO_CODE
	else if(joy_type==JOY_AS_FLIGHTSTICK_PRO)
	{
		if (!joy_flightstick_pro_init())
		{
			joy_type = JOY_AS_NONE;
		}
	}
#else
	else if(joy_type==JOY_AS_FLIGHTSTICK_PRO)
	{
		joy_type = JOY_AS_MOUSE;
	}
#endif	//CH_FLIGHTSTICK_PRO_CODE
}

void joy_flush()
{
	if (!joy_installed) return;

	mouse_flush();
}

ubyte joystick_read_raw_axis( ubyte mask, int * axis )
{
	ubyte read_masks;
	Point mcoords;

	read_masks = 0;	
	axis[0] = 0; axis[1] = 0;
	axis[2] = 0; axis[3] = 0;

	if (!joy_installed) return 0;

	if (joy_type == JOY_AS_MOUSE) {
		GetMouse(&mcoords);
		axis[0] = mcoords.h;
		axis[1] = mcoords.v;
		read_masks = 3;
	}
	else if (joy_type == JOY_AS_THRUSTMASTER) {
		read_masks = 0x3;
		axis[0] = (int)(tm_dev->roll);
		axis[1] = (int)(tm_dev->pitch);
		if (tm_dev->rudderAttached) {
			read_masks |= (1 << 2);
			axis[2] = (int)(tm_dev->yaw);
		}
		if (tm_dev->throttleAttached) {
			read_masks |= (1 << 3);
			axis[3] = (int)(tm_dev->thrust);
		}
	}
	else if (joy_type == JOY_AS_GRAVIS_MOUSESTICK) {
		if (ag_dev->numSticksConnected > 0) {
			read_masks = 0x3;
			axis[0] = (int)(ag_dev->stick1_xIn);
			axis[1] = (int)(ag_dev->stick1_yIn);
		}
		if (ag_dev->numSticksConnected > 1) {
			read_masks |= (1 << 2);
			axis[2] = (int)(ag_dev->stick2_xIn);
			read_masks |= (1 << 3);
			axis[3] = (int)(ag_dev->stick2_yIn);
		}
	}
#if CH_FLIGHTSTICK_PRO_CODE
	else if (joy_type == JOY_AS_FLIGHTSTICK_PRO) {
		OSErr	err;
		JoySimpleData	*joystick;

		err = JoyOpenManager();
		err = JoyEnableDevice(0, 1);
		if(err == noErr)
		{
			joystick = JoyGetSimpleDataPtr();
			
			if (  (joystick->features & kJoyXAxisAvailable) 
				&&(joystick->features & kJoyYAxisAvailable))
			{
				read_masks = 0x3;
				axis[0] = (int)(joystick->xAxisValue) >> 8;
				axis[1] = -((int)(joystick->yAxisValue) >> 8);
			}

			if (joystick->features & kJoyRudderAvailable)
			{
				read_masks |= (1 << 2);
				axis[2] = (int)(joystick->rudderValue) >> 8;
			}

			if (joystick->features & kJoyThrottleAvailable)
			{
				read_masks |= (1 << 3);
				axis[3] = (int)(16384 - joystick->throttleValue) >> 7;
			}
		}
		err = JoyEnableDevice(0, 0);
		JoyCloseManager();
	}
#endif	//CH_FLIGHTSTICK_PRO_CODE

	return read_masks;
}

int joy_init()	
{
	int i;
	int temp_axis[4];

	joy_flush();

	if ( !joy_installed )	{
		joy_present = 0;
		joy_installed = 1;
	}

	// Do initial cheapy calibration...
	joystick.present_mask = JOY_ALL_AXIS;		// Assume they're all present
	joystick.present_mask = joystick_read_raw_axis( JOY_ALL_AXIS, temp_axis );

	if ( joystick.present_mask & 3 )
		joy_present = 1;
	else
		joy_present = 0;

	return joy_present;
}

void joy_close()	
{
	if (!joy_installed) return;
	if ( (tm_dev != NULL) && have_virtual_memory )
		UnholdMemory( tm_dev, sizeof(ThrustmasterDevice) );
	if ( (ag_dev != NULL) && have_virtual_memory )
		UnholdMemory( ag_dev, sizeof(GravisDevice) );
		
	joy_installed = 0;
}

ubyte joy_get_present_mask()
{
	if (!joy_installed) return 0;
	return (ubyte)(joystick.present_mask);
}

void joy_set_ul()	
{
	joystick.present_mask = joystick_read_raw_axis( JOY_ALL_AXIS, joystick.axis_min );
	if ( joystick.present_mask & 3 )
		joy_present = 1;
	else
		joy_present = 0;
}

void joy_set_lr()	
{
	joystick.present_mask = joystick_read_raw_axis( JOY_ALL_AXIS, joystick.axis_max );
	if ( joystick.present_mask & 3 )
		joy_present = 1;
	else
		joy_present = 0;
}

void joy_set_cen() 
{
	joystick.present_mask = joystick_read_raw_axis( JOY_ALL_AXIS, joystick.axis_center );
	if ( joystick.present_mask & 3 )
		joy_present = 1;
	else
		joy_present = 0;
}

void joy_set_cen_fake(int channel)
{

	int i,n=0;
	int minx, maxx, cenx;
	
	minx=maxx=cenx=0;

	for (i=0; i<4; i++ )	{
		if ( (joystick.present_mask & (1<<i)) && (i!=channel) )	{
			n++;
			minx += joystick.axis_min[i];
			maxx += joystick.axis_max[i];
			cenx += joystick.axis_center[i];
		}
	}
	minx /= n;
	maxx /= n;
	cenx /= n;

	joystick.axis_min[channel] = minx;
	joystick.axis_max[channel] = maxx;
	joystick.axis_center[channel] = cenx;
}

int joy_get_scaled_reading( int raw, int axn )
{
	int x, d;

	// Make sure it's calibrated properly.
	if ( joystick.axis_center[axn] - joystick.axis_min[axn] < 5 ) return 0;
	if ( joystick.axis_max[axn] - joystick.axis_center[axn] < 5 ) return 0;

	raw -= joystick.axis_center[axn];

	if ( raw < 0 )	{
		d = joystick.axis_center[axn]-joystick.axis_min[axn];
	} else {
		d = joystick.axis_max[axn]-joystick.axis_center[axn];
	}

	if ( d )
		x = (raw << 7) / d;
	else 
		x = 0;

	if ( x < -128 ) x = -128;
	if ( x > 127 ) x = 127;

	return x;
}

void joy_get_pos( int *x, int *y )
{
	ubyte flags;
	int axis[4];

	if (!joy_installed) { *x=*y=0; return; }

	flags=joystick_read_raw_axis( JOY_1_X_AXIS+JOY_1_Y_AXIS, axis );

	if ( flags & JOY_1_X_AXIS )
		*x = joy_get_scaled_reading( axis[0], 0 );
	else
		*x = 0;

	if ( flags & JOY_1_Y_AXIS )
		*y = joy_get_scaled_reading( axis[1], 1 );
	else
		*y = 0;
}

ubyte joy_read_stick( ubyte masks, int *axis )
{
	ubyte flags;
	int raw_axis[4];

	if (!joy_installed) { 
		axis[0] = 0; axis[1] = 0;
		axis[2] = 0; axis[3] = 0;
		return 0;  
	}

	flags=joystick_read_raw_axis( masks, raw_axis );

	if ( flags & JOY_1_X_AXIS )
		axis[0] = joy_get_scaled_reading( raw_axis[0], 0 );
	else
		axis[0] = 0;

	if ( flags & JOY_1_Y_AXIS )
		axis[1] = joy_get_scaled_reading( raw_axis[1], 1 );
	else
		axis[1] = 0;

	if ( flags & JOY_2_X_AXIS )
		axis[2] = joy_get_scaled_reading( raw_axis[2], 2 );
	else
		axis[2] = 0;

	if ( flags & JOY_2_Y_AXIS )
		axis[3] = joy_get_scaled_reading( raw_axis[3], 3 );
	else
		axis[3] = 0;

	return flags;
}


int joy_get_btns()
{
	if (!joy_installed) return 0;
	return mouse_get_btns();
}

void joy_get_btn_down_cnt( int *btn0, int *btn1 )
{
	if (!joy_installed) { *btn0=*btn1=0; return; }
	*btn0 = mouse_button_down_count(0);
	*btn1 = mouse_button_down_count(1);
}

int joy_get_button_state( int btn )
{
	if (!joy_installed) return 0;
	return  mouse_button_state(btn);
}

#if 0
int joy_get_button_up_cnt( int btn )
{
	if (!joy_installed) return 0;
	return mouse_button_up_cnt(btn);
}
#endif

int joy_get_button_down_cnt( int btn )
{
	if (!joy_installed) return 0;
	return mouse_button_down_count(btn);
}

	
fix joy_get_button_down_time( int btn )
{
	if (!joy_installed) return 0;
	return mouse_button_down_time(btn);
}

#if 0
void joy_get_btn_up_cnt( int *btn0, int *btn1 ) {
	if (!joy_installed) { *btn0=*btn1=0; return; }

//	_disable();
	*btn0 = joystick.buttons[0].upcount;
	joystick.buttons[0].upcount = 0;
	*btn1 = joystick.buttons[1].upcount;
	joystick.buttons[1].upcount = 0;
//	_enable();
}

void joy_set_btn_values( int btn, int state, fix timedown, int downcount, int upcount )
{
//	_disable();
	joystick.buttons[btn].ignore = 1;
	joystick.buttons[btn].state = state;
	joystick.buttons[btn].timedown = fixmuldiv( timedown, 1193180, 65536 );
	joystick.buttons[btn].downcount = downcount;
	joystick.buttons[btn].upcount = upcount;
//	_enable();
}
#endif

uint joy_thrustmaster_init (void)
{
	OSErr			err;
	uint			result = 0;
	char			adb_addr;
	ADBDataBlock	adb_data;

	for (adb_addr = 1; adb_addr < 16; adb_addr++) {
		err = GetADBInfo (&adb_data, adb_addr);
		if (err == noErr) {
			if ((adb_data.origADBAddr == THRUSTMASTER_ADB_ADDR) && (adb_data.devType == THRUSTMASTER_HANDLER_ID)) {
				tm_dev = (ThrustmasterDevice *)(adb_data.dbDataAreaAddr);
				if (have_virtual_memory) {
					HoldMemory( tm_dev, sizeof(ThrustmasterDevice) );
				}
				result = 1;
				break;
			}
		}
	}
	return(result);
}

uint joy_gravis_init (void)
{
	OSErr			err;
	uint			result = 0;
	ADBDataBlock	adbGetInfo;
	short			x, numADB;
	
	numADB = CountADBs();
	for (x = 1; x <= numADB; x++)
	{
		err = GetADBInfo(&adbGetInfo,GetIndADB(&adbGetInfo,x));
		if (err == noErr)
		{
			ag_dev = (GravisDevice *)(adbGetInfo.dbDataAreaAddr);
			if (ag_dev != nil && ag_dev->signature == GRAVIS_SIGNATURE)
			{
				if (have_virtual_memory) {
					HoldMemory( ag_dev, sizeof(GravisDevice) );
				}
				result = 1;
				break;
			}
		}
	}
	return(result);
}

#if CH_FLIGHTSTICK_PRO_CODE
uint joy_flightstick_pro_init (void)
{
	uint	result = 0;
	OSErr	err;

	if(!flightstick_pro_init)
	{
		err = JoyOpenManager();
		if(err == noErr)
		{
			short	count;
			
			count = JoyGetCount();
			if(count != 0)
			{
//				err = JoyEnableDevice(0, 1);
				flightstick_pro_init = 1;
				result = 1;
			}
		}
		JoyCloseManager();
	}
	else
	{
		result = 1;
	}
	return(result);
}
#endif	//CH_FLIGHTSTICK_PRO_CODE
