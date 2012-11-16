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
 * $Source: Smoke:miner:source:main::RCS:joydefs.c $
 * $Revision: 1.10 $
 * $Author: allender $
 * $Date: 1995/10/18 22:21:21 $
 * 
 * .
 * 
 * $Log: joydefs.c $
 * Revision 1.10  1995/10/18  22:21:21  allender
 * fixed bug with gravis mousestick and call key_flush when
 * calibrating joystick since it used keystrokes for the trigger
 * (at least most of them do)
 *
 * Revision 1.9  1995/10/17  13:12:32  allender
 * fixed up controller support for mac world
 *
 * Revision 1.8  1995/10/15  19:27:04  allender
 * new Dave Denhart controller code
 *
 * Revision 1.7  1995/10/15  16:14:59  allender
 * fixed axis value for Thrustmaster rudders
 *
 * Revision 1.6  1995/09/13  11:39:39  allender
 * made joystick cal menu all text so buttons will work properly
 *
 * Revision 1.5  1995/09/01  13:13:13  allender
 * added close box on controls menu
 *
 * Revision 1.4  1995/08/18  10:22:47  allender
 * if thrustmaster choosen, set joystick at thrustmaster type
 * for proper reading in joyc.c
 *
 * Revision 1.3  1995/07/26  17:00:34  allender
 * put back in code to make joysticks work
 *
 * Revision 1.2  1995/07/17  08:52:21  allender
 * put back in code that was taken out previously
 *
 * Revision 1.1  1995/05/16  15:26:48  allender
 * Initial revision
 *
 * Revision 2.1  1995/04/06  12:13:20  john
 * Made so you can calibrate Gravis Gamepad.
 * 
 * Revision 2.0  1995/02/27  11:30:27  john
 * New version 2.0, which has no anonymous unions, builds with
 * Watcom 10.0, and doesn't require parsing BITMAPS.TBL.
 * 
 * Revision 1.71  1995/02/12  02:06:10  john
 * Fixed bug with joystick incorrectly asking for
 * calibration.
 * 
 * Revision 1.70  1995/01/28  15:58:07  john
 * Made joystick calibration be only when wrong detected in
 * menu or joystick axis changed.
 * 
 * Revision 1.69  1995/01/25  14:37:55  john
 * Made joystick only prompt for calibration once...
 * 
 * Revision 1.68  1995/01/24  16:34:29  john
 * Made so that if you reconfigure joystick and
 * add or subtract an axis, it asks for a recalibration
 * upon leaving.
 * 
 * Revision 1.67  1994/12/29  11:08:51  john
 * Fixed Thrustmaster and Logitech Wingman extreme
 * Hat by reading the y2 axis during the center stage
 * of the calibration, and using 75, 50, 27, and 3 %
 * as values for the 4 positions.
 * 
 * Revision 1.66  1994/12/15  18:17:39  john
 * Fixed warning with previous.
 * 
 * Revision 1.65  1994/12/15  18:15:48  john
 * Made the joy cal only write the .cfg file, not
 * the player file.
 * 
 * Revision 1.64  1994/12/13  14:43:35  john
 * Took out the code in kconfig to build direction array.
 * Called kc_set_controls after selecting a new control type.
 * 
 * Revision 1.63  1994/12/10  12:08:47  john
 * Changed some delays to use TICKER instead of timer_get_fixed_seconds.
 * 
 * Revision 1.62  1994/12/09  11:01:07  mike
 * force calibration of joystick on joystick selection from Controls... menu.
 * 
 * Revision 1.61  1994/12/07  21:50:27  john
 * Put stop/start time around joystick delay.
 * 
 * Revision 1.60  1994/12/07  19:34:39  john
 * Added delay.
 * 
 * Revision 1.59  1994/12/07  18:12:14  john
 * NEatened up joy cal.,
 * 
 * Revision 1.58  1994/12/07  17:07:51  john
 * Fixed up joy cal.
 * 
 * Revision 1.57  1994/12/07  16:48:53  yuan
 * localization
 * 
 * Revision 1.56  1994/12/07  16:05:55  john
 * Changed the way joystick calibration works.
 * 
 * Revision 1.55  1994/12/06  20:15:22  john
 * Took out code that unpauses songs that were never paused.
 * 
 * Revision 1.54  1994/12/06  15:14:09  yuan
 * Localization
 * 
 * Revision 1.53  1994/12/05  16:29:16  john
 * Took out music pause around the cheat menu.
 * 
 * Revision 1.52  1994/12/04  12:39:10  john
 * MAde so that FCS calibration doesn't ask for axis #2.
 * 
 * Revision 1.51  1994/12/03  15:14:59  john
 * Took out the delay mentioned previosuly cause it would
 * cause bigger problems than it helps, especially with netgames.
 * 
 * Revision 1.50  1994/12/03  14:16:14  john
 * Put a delay between screens in joy cal to keep Yuan from
 * double hitting.
 * 
 * Revision 1.49  1994/12/03  11:04:06  john
 * Changed newmenu code a bit to fix bug with bogus
 * backgrounds occcasionally.
 * 
 * Revision 1.48  1994/12/02  11:03:44  yuan
 * Localization.
 * 
 * Revision 1.47  1994/12/02  10:50:33  yuan
 * Localization
 * 
 * Revision 1.46  1994/12/01  12:21:59  john
 * Added code to calibrate 2 joysticks separately.
 * 
 * Revision 1.45  1994/12/01  11:52:31  john
 * Added message when you select FCS to say that if
 * you have WCS, see manuel.
 * 
 * Revision 1.44  1994/11/29  02:26:28  john
 * Made the prompts for upper-left, lower right for joy
 * calibration more obvious.
 * 
 * Revision 1.43  1994/11/26  13:13:59  matt
 * Changed "none" option to "keyboard only"
 * 
 * Revision 1.42  1994/11/21  19:35:13  john
 * Replaced calls to joy_init with if (joy_present)
 * 
 * Revision 1.41  1994/11/21  19:28:34  john
 * Changed warning for no joystick to use nm_messagebox..
 * 
 * Revision 1.40  1994/11/21  19:06:25  john
 * Made it so that it only stops sound when your in game mode. 
 * 
 * Revision 1.39  1994/11/21  11:47:18  john
 * Made sound pause during joystick calibration.
 * 
 * Revision 1.38  1994/11/10  20:34:18  rob
 * Removed menu-specific network mode support in favor in new stuff
 * in newmenu.c
 * 
 * Revision 1.37  1994/11/08  21:21:38  john
 * Made Esc exit joystick calibration.
 * 
 * Revision 1.36  1994/11/08  15:14:42  john
 * Added more calls so net doesn't die in net game.
 * 
 * Revision 1.35  1994/11/08  14:59:12  john
 * Added code to respond to network while in menus.
 * 
 * Revision 1.34  1994/10/24  19:56:32  john
 * Made the new user setup prompt for config options.
 * 
 * Revision 1.33  1994/10/22  14:11:52  mike
 * Suppress compiler warning message.
 * 
 * Revision 1.32  1994/10/19  12:44:24  john
 * Added hours field to player structure.
 * 
 * Revision 1.31  1994/10/17  13:07:13  john
 * Moved the descent.cfg info into the player config file.
 * 
 * Revision 1.30  1994/10/13  21:41:12  john
 * MAde Esc exit out of joystick calibration.
 * 
 * Revision 1.29  1994/10/13  19:22:27  john
 * Added separate config saves for different devices.
 * Made all the devices work together better, such as mice won't
 * get read when you're playing with the joystick.
 * 
 * Revision 1.28  1994/10/13  11:40:18  john
 * Took out warnings.
 * 
 * Revision 1.27  1994/10/13  11:35:23  john
 * Made Thrustmaster FCS Hat work.  Put a background behind the
 * keyboard configure.  Took out turn_sensitivity.  Changed sound/config
 * menu to new menu. Made F6 be calibrate joystick.
 * 
 * Revision 1.26  1994/10/11  21:29:03  matt
 * Made a bunch of menus have good initial selected values
 * 
 * Revision 1.25  1994/10/11  17:08:39  john
 * Added sliders for volume controls.
 * 
 * Revision 1.24  1994/10/10  17:59:21  john
 * Neatend previous.
 * 
 * Revision 1.23  1994/10/10  17:57:59  john
 * Neatend previous.
 * 
 * Revision 1.22  1994/10/10  17:56:11  john
 * Added messagebox that tells that config has been saved.
 * 
 * Revision 1.21  1994/09/30  12:37:26  john
 * Added midi,digi volume to configuration.
 * 
 * Revision 1.20  1994/09/22  16:14:14  john
 * Redid intro sequecing.
 * 
 * Revision 1.19  1994/09/19  18:50:15  john
 * Added switch to disable joystick.
 * 
 * Revision 1.18  1994/09/12  11:47:36  john
 * Made stupid cruise work better.  Make kconfig values get
 * read/written to disk.
 * 
 * Revision 1.17  1994/09/10  15:46:47  john
 * First version of new keyboard configuration.
 * 
 * Revision 1.16  1994/09/06  19:35:44  john
 * Fixed bug that didn';t load new size .cal file.
 * 
 * Revision 1.15  1994/09/06  14:51:58  john
 * Added sensitivity adjustment, fixed bug with joystick button not
 * staying down.
 * 
 * Revision 1.14  1994/09/02  16:13:47  john
 * Made keys fill in position.
 * 
 * Revision 1.13  1994/08/31  17:58:50  john
 * Made a bit simpler.
 * 
 * Revision 1.12  1994/08/31  14:17:54  john
 * *** empty log message ***
 * 
 * Revision 1.11  1994/08/31  14:10:56  john
 * Made keys not work when KEY_DELETE pressed.
 * 
 * Revision 1.10  1994/08/31  13:40:47  mike
 * Change constant
 * 
 * Revision 1.9  1994/08/31  12:56:27  john
 * *** empty log message ***
 * 
 * Revision 1.8  1994/08/30  20:38:29  john
 * Add more config stuff..
 * 
 * Revision 1.7  1994/08/30  16:37:25  john
 * Added menu options to set controls.
 * 
 * Revision 1.6  1994/08/30  09:27:18  john
 * *** empty log message ***
 * 
 * Revision 1.5  1994/08/30  09:12:01  john
 * *** empty log message ***
 * 
 * Revision 1.4  1994/08/29  21:18:32  john
 * First version of new keyboard/oystick remapping stuff.
 * 
 * Revision 1.3  1994/08/24  19:00:29  john
 * Changed key_down_time to return fixed seconds instead of
 * milliseconds.
 * 
 * Revision 1.2  1994/08/17  16:50:37  john
 * Added damaging fireballs, missiles.
 * 
 * Revision 1.1  1994/08/17  10:07:12  john
 * Initial revision
 * 
 * 
 */


#pragma off (unreferenced)
static char rcsid[] = "$Id: joydefs.c 1.10 1995/10/18 22:21:21 allender Exp $";
#pragma on (unreferenced)

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "mono.h"
#include "key.h"
#include "joy.h"
#include "timer.h"
#include "error.h"

#include "inferno.h"
#include "game.h"
#include "object.h"
#include "player.h"

#include "controls.h"
#include "joydefs.h"
#include "victor.h"
#include "render.h"
#include "palette.h"
#include "newmenu.h"
#include "args.h"
#include "text.h"
#include "kconfig.h"
#include "digi.h"
#include "playsave.h"

int joydefs_calibrate_flag = 0;

void joy_delay()
{
	fix t1 = timer_get_fixed_seconds() + (F1_0/4);
	stop_time();
	while (t1 < timer_get_fixed_seconds()) ;
	joy_flush();
	key_flush();
	start_time();
	
}


int joycal_message( char * title, char * text )
{
	int i;
	newmenu_item	m[2];
	m[0].type = NM_TYPE_TEXT; m[0].text = text;
//	m[1].type = NM_TYPE_MENU; m[1].text = TXT_OK;
	i = newmenu_do( title, NULL, 1, m, NULL );
	if ( i < 0 ) 
		return 1;
	return 0;
}

extern int WriteConfigFile();	

void joydefs_calibrate()
{
	ubyte masks;
	int org_axis_min[4];
	int org_axis_center[4];
	int org_axis_max[4];

	int axis_min[4] = { 0, 0, 0, 0 };
	int axis_cen[4] = { 0, 0, 0, 0 };
	int axis_max[4] = { 0, 0, 0, 0 };

	int temp_values[4];
	char title[50];
	char text[50];
	int nsticks = 0;

	joydefs_calibrate_flag = 0;

	if (   (Config_control_type!=CONTROL_JOYSTICK)
		&& (Config_control_type!=CONTROL_FLIGHTSTICK_PRO)
		&& (Config_control_type!=CONTROL_THRUSTMASTER_FCS)
		&& (Config_control_type!=CONTROL_GRAVIS_GAMEPAD) )	
		return;
	
	if ( Config_control_type == CONTROL_THRUSTMASTER_FCS ) {
		axis_cen[0] = axis_cen[1] = axis_cen[2] = 0;
		axis_min[0] = axis_min[1] = axis_min[2] = -127;
		axis_max[0] = axis_max[1] = axis_max[2] = 127;
		axis_min[3] = 0;
		axis_max[3] = 255;
		axis_cen[3] = 128;
		joy_set_cal_vals(axis_min, axis_cen, axis_max);
		return;
	}
		
	joy_get_cal_vals(org_axis_min, org_axis_center, org_axis_max);

	joy_set_cen();
	joystick_read_raw_axis( JOY_ALL_AXIS, temp_values );

//MWA	if (!joy_present)	{
//MWA		nm_messagebox( NULL, 1, TXT_OK, TXT_NO_JOYSTICK );
//MWA		return;
//MWA	}
	
	masks = joy_get_present_mask();
	if ( masks == JOY_ALL_AXIS )
		nsticks = 2;
	else
		nsticks = 1;

	if ( nsticks == 2 )	{
		sprintf( title, "%s #1\n%s", TXT_JOYSTICK, TXT_UPPER_LEFT);
		sprintf( text, "%s #1 %s", TXT_MOVE_JOYSTICK, TXT_TO_UL);
	} else {
		sprintf( title, "%s\n%s", TXT_JOYSTICK, TXT_UPPER_LEFT);
		sprintf( text, "%s %s", TXT_MOVE_JOYSTICK, TXT_TO_UL);
	}
	if (joycal_message( title, text )) {
		joy_set_cal_vals(org_axis_min, org_axis_center, org_axis_max);
		return;
	}
	joystick_read_raw_axis( JOY_ALL_AXIS, temp_values );
	axis_min[0] = temp_values[0];
	axis_min[1] = temp_values[1];
	joy_delay();

	if ( nsticks == 2 )	{
		sprintf( title, "%s #1\n%s", TXT_JOYSTICK, TXT_LOWER_RIGHT);
		sprintf( text, "%s #1 %s", TXT_MOVE_JOYSTICK, TXT_TO_LR);
	} else {
		sprintf( title, "%s\n%s", TXT_JOYSTICK, TXT_LOWER_RIGHT);
		sprintf( text, "%s %s", TXT_MOVE_JOYSTICK, TXT_TO_LR);
	}
	if (joycal_message( title, text)) {
		joy_set_cal_vals(org_axis_min, org_axis_center, org_axis_max);
		return;
	}
	joystick_read_raw_axis( JOY_ALL_AXIS, temp_values );
	axis_max[0] = temp_values[0];
	axis_max[1] = temp_values[1];
	joy_delay();

	if ( nsticks == 2 )	{
		sprintf( title, "%s #1\n%s", TXT_JOYSTICK, TXT_CENTER);
		sprintf( text, "%s #1 %s", TXT_MOVE_JOYSTICK, TXT_TO_C);
	} else {
		sprintf( title, "%s\n%s", TXT_JOYSTICK, TXT_CENTER);
		sprintf( text, "%s %s", TXT_MOVE_JOYSTICK, TXT_TO_C);
	}
	if (joycal_message( title, text)) {
		joy_set_cal_vals(org_axis_min, org_axis_center, org_axis_max);
		return;
	}
	joystick_read_raw_axis( JOY_ALL_AXIS, temp_values );
	axis_cen[0] = temp_values[0];
	axis_cen[1] = temp_values[1];
	joy_delay();

	// The fcs uses axes 3 for hat, so don't calibrate it.
	if ( Config_control_type == CONTROL_THRUSTMASTER_FCS )	{
		axis_min[3] = 0;
		axis_cen[3] = temp_values[3]/2;
		axis_max[3] = temp_values[3];
		joy_delay();
	} else {
		masks = joy_get_present_mask();

		if ( nsticks == 2 )	{
			if ( kconfig_is_axes_used(2) || kconfig_is_axes_used(3) )	{
				sprintf( title, "%s #2\n%s", TXT_JOYSTICK, TXT_UPPER_LEFT);
				sprintf( text, "%s #2 %s", TXT_MOVE_JOYSTICK, TXT_TO_UL);
				if (joycal_message( title, text )) {
					joy_set_cal_vals(org_axis_min, org_axis_center, org_axis_max);
					return;
				}
				joystick_read_raw_axis( JOY_ALL_AXIS, temp_values );
				axis_min[2] = temp_values[2];
				axis_min[3] = temp_values[3];
				joy_delay();

				sprintf( title, "%s #2\n%s", TXT_JOYSTICK, TXT_LOWER_RIGHT);
				sprintf( text, "%s #2 %s", TXT_MOVE_JOYSTICK, TXT_TO_LR);
				if (joycal_message( title, text ))	{
					joy_set_cal_vals(org_axis_min, org_axis_center, org_axis_max); 
					return;
				}
				joystick_read_raw_axis( JOY_ALL_AXIS, temp_values );
				axis_max[2] = temp_values[2];
				axis_max[3] = temp_values[3];
				joy_delay();
		
				sprintf( title, "%s #2\n%s", TXT_JOYSTICK, TXT_CENTER);
				sprintf( text, "%s #2 %s", TXT_MOVE_JOYSTICK, TXT_TO_C);
				if (joycal_message( title, text ))	{
					joy_set_cal_vals(org_axis_min, org_axis_center, org_axis_max);
					return;
				}
				joystick_read_raw_axis( JOY_ALL_AXIS, temp_values );
				axis_cen[2] = temp_values[2];
				axis_cen[3] = temp_values[3];	
				joy_delay();
			}
		} else if ( (!(masks & JOY_2_X_AXIS)) && (masks & JOY_2_Y_AXIS) )	{
			if ( kconfig_is_axes_used(3) )	{
				// A throttle axis!!!!!
				sprintf( title, "%s\n%s", TXT_THROTTLE, TXT_FORWARD);
				if (joycal_message( title, TXT_MOVE_THROTTLE_F))	{
					joy_set_cal_vals(org_axis_min, org_axis_center, org_axis_max);
					return;
				}
				joystick_read_raw_axis( JOY_ALL_AXIS, temp_values );
				axis_min[3] = temp_values[3];
				joy_delay();
		
				sprintf( title, "%s\n%s", TXT_THROTTLE, TXT_REVERSE);
				if (joycal_message( title, TXT_MOVE_THROTTLE_R)) {
					joy_set_cal_vals(org_axis_min, org_axis_center, org_axis_max);
					return;
				}
				joystick_read_raw_axis( JOY_ALL_AXIS, temp_values );
				axis_max[3] = temp_values[3];
				joy_delay();
		
				sprintf( title, "%s\n%s", TXT_THROTTLE, TXT_CENTER);
				if (joycal_message( title, TXT_MOVE_THROTTLE_C)) {
					joy_set_cal_vals(org_axis_min, org_axis_center, org_axis_max);
					return;
				}
				joystick_read_raw_axis( JOY_ALL_AXIS, temp_values );
				axis_cen[3] = temp_values[3];
				joy_delay();
			}
		}
	}
	joy_set_cal_vals(axis_min, axis_cen, axis_max);

	WriteConfigFile();	
}

void joydef_menuset_1(int nitems, newmenu_item * items, int *last_key, int citem )
{
	int i;
	int oc_type = Config_control_type;

	nitems = nitems;
	last_key = last_key;
	citem = citem;		

//	for (i=0; i<CONTROL_MAX_TYPES; i++ )
//		if (items[i].value) Config_control_type = i;

	if (items[0].value)
		Config_control_type = CONTROL_NONE;
	else if (items[1].value)
		Config_control_type = CONTROL_JOYSTICK;
	else if (items[2].value)
		Config_control_type = CONTROL_THRUSTMASTER_FCS;
	else if (items[3].value)
		Config_control_type = CONTROL_GRAVIS_GAMEPAD;
	else if (items[4].value)
		Config_control_type = CONTROL_MOUSE;
	else {
		Int3();
		Config_control_type = CONTROL_NONE;
	}

//	if ( (oc_type != Config_control_type) && (Config_control_type == CONTROL_THRUSTMASTER_FCS ) )	{
//		nm_messagebox( TXT_IMPORTANT_NOTE, 1, TXT_OK, TXT_FCS );
//	}

	if (oc_type != Config_control_type) {
		switch (Config_control_type) {
			case	CONTROL_JOYSTICK:
			case	CONTROL_FLIGHTSTICK_PRO:
				joydefs_calibrate_flag = 1;
		}
		kc_set_controls();
		joydefs_set_type(Config_control_type);
	}
}

void joydefs_config()
{
	int i, old_masks, masks;
	newmenu_item m[12];
	int i1=7;

	do {
		m[0].type = NM_TYPE_RADIO; m[0].text = CONTROL_TEXT(0); m[0].value = 0; m[0].group = 0;
		m[1].type = NM_TYPE_RADIO; m[1].text = CONTROL_TEXT(1); m[1].value = 0; m[1].group = 0;
// CH Flightstick Pro not directly supported		m[2].type = NM_TYPE_RADIO; m[2].text = CONTROL_TEXT(2); m[2].value = 0; m[2].group = 0;
		m[2].type = NM_TYPE_RADIO; m[2].text = CONTROL_TEXT(3); m[2].value = 0; m[2].group = 0;
		m[3].type = NM_TYPE_RADIO; m[3].text = CONTROL_TEXT(4); m[3].value = 0; m[3].group = 0;
		m[4].type = NM_TYPE_RADIO; m[4].text = CONTROL_TEXT(5); m[4].value = 0; m[4].group = 0;
//  CYBERMAN NOT USED!!!		m[6].type = NM_TYPE_RADIO; m[6].text = CONTROL_TEXT(6); m[6].value = 0; m[6].group = 0;
		m[5].type = NM_TYPE_MENU; m[5].text=TXT_CUST_ABOVE;
		m[6].type = NM_TYPE_TEXT; m[6].text="";
		m[7].type = NM_TYPE_MENU; m[7].text=TXT_CUST_KEYBOARD;
		if ( Config_control_type == CONTROL_NONE )
			m[0].value = 1;
		else if ( Config_control_type == CONTROL_JOYSTICK )
			m[1].value = 1;
		else if ( Config_control_type == CONTROL_THRUSTMASTER_FCS )
			m[2].value = 1;
		else if ( Config_control_type == CONTROL_GRAVIS_GAMEPAD )
			m[3].value = 1;
		else if ( Config_control_type == CONTROL_MOUSE)
			m[4].value = 1;
		else
			m[0].value = 1;
	 
		i1 = newmenu_do4( NULL, TXT_CONTROLS, 8, m, joydef_menuset_1, i1, NULL, -1, -1, 1 );

		switch(i1)	{

		case 5: {
				old_masks = 0;
				for (i=0; i<4; i++ )		{
					if (kconfig_is_axes_used(i))
						old_masks |= (1<<i);
				}
				if ( Config_control_type==0 )
					// nothing...
					Config_control_type=0;
				else if ( Config_control_type<5 ) 
					kconfig(1, CONTROL_TEXT(Config_control_type) ); 
				else 
					kconfig(2, CONTROL_TEXT(Config_control_type) ); 

				masks = 0;
				for (i=0; i<4; i++ )		{
					if (kconfig_is_axes_used(i))
						masks |= (1<<i);
				}

				switch (Config_control_type) {
				case	CONTROL_JOYSTICK:
				case	CONTROL_FLIGHTSTICK_PRO:
				case	CONTROL_THRUSTMASTER_FCS:	
					{
						for (i=0; i<4; i++ )	{
							if ( (masks&(1<<i)) && (!(old_masks&(1<<i))))
								joydefs_calibrate_flag = 1;
						}
					}
					break;
				}
			}
			break;
		case 7: 
			kconfig(0, TXT_KEYBOARD); 
			break;
		} 
	} while(i1>-1);


	switch (Config_control_type) {
	case	CONTROL_JOYSTICK:
	case	CONTROL_FLIGHTSTICK_PRO:
	case	CONTROL_THRUSTMASTER_FCS:
	case	CONTROL_GRAVIS_GAMEPAD:
		if ( joydefs_calibrate_flag )
			joydefs_calibrate();
		break;
	}

}

void joydefs_set_type(ubyte type)
{
	ubyte joy_type;
	
	switch (type)
	{
		case	CONTROL_NONE:				joy_type = JOY_AS_NONE;					break;
		case	CONTROL_JOYSTICK:			joy_type = JOY_AS_MOUSE;				break;
		case	CONTROL_FLIGHTSTICK_PRO:	joy_type = JOY_AS_FLIGHTSTICK_PRO;		break;
		case	CONTROL_THRUSTMASTER_FCS:	joy_type = JOY_AS_THRUSTMASTER;			break;
		case	CONTROL_GRAVIS_GAMEPAD:		joy_type = JOY_AS_GRAVIS_MOUSESTICK;	break;
		case	CONTROL_MOUSE:				joy_type = JOY_AS_MOUSE;				break;
		case	CONTROL_CYBERMAN:			joy_type = JOY_AS_MOUSE;				break;
	}
	joy_set_type(joy_type);
}
