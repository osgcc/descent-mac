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
 * $Source: Smoke:miner:source:main::RCS:config.c $
 * $Revision: 1.8 $
 * $Author: allender $
 * $Date: 1995/10/27 10:52:20 $
 * 
 * contains routine(s) to read in the configuration file which contains
 * game configuration stuff like detail level, sound card, etc
 * 
 * $Log: config.c $
 * Revision 1.8  1995/10/27  10:52:20  allender
 * call digi_set_master_volume when prefs are read in to
 * set the master volume of the mac
 *
 * Revision 1.7  1995/10/24  17:08:39  allender
 * Config_master_volume added for saving sound manager volume
 * across games
 *
 * Revision 1.6  1995/10/20  00:49:31  allender
 * use default values when no prefs file
 *
 * Revision 1.5  1995/09/21  10:06:58  allender
 * set digi and midi volume appropriately
 *
 * Revision 1.4  1995/09/13  08:49:38  allender
 * prefs file stuff
 *
 * Revision 1.3  1995/09/05  08:47:37  allender
 * prefs file working
 *
 * Revision 1.2  1995/05/26  06:54:14  allender
 * removed midi and digi references from config file
 *
 * Revision 1.1  1995/05/16  15:23:45  allender
 * Initial revision
 *
 * Revision 2.2  1995/03/27  09:42:59  john
 * Added VR Settings in config file.
 * 
 * Revision 2.1  1995/03/16  11:20:40  john
 * Put in support for Crystal Lake soundcard.
 * 
 * Revision 2.0  1995/02/27  11:30:13  john
 * New version 2.0, which has no anonymous unions, builds with
 * Watcom 10.0, and doesn't require parsing BITMAPS.TBL.
 * 
 * Revision 1.14  1995/02/11  16:19:36  john
 * Added code to make the default mission be the one last played.
 * 
 * Revision 1.13  1995/01/18  13:23:24  matt
 * Made curtom detail level vars initialize properly at load
 * 
 * Revision 1.12  1995/01/04  22:15:36  matt
 * Fixed stupid bug using scanf() to read bytes
 * 
 * Revision 1.11  1995/01/04  13:14:21  matt
 * Made custom detail level settings save in config file
 * 
 * Revision 1.10  1994/12/12  21:35:09  john
 * *** empty log message ***
 * 
 * Revision 1.9  1994/12/12  21:31:51  john
 * Made volume work better by making sure volumes are valid
 * and set correctly at program startup.
 * 
 * Revision 1.8  1994/12/12  13:58:01  john
 * MAde -nomusic work.
 * Fixed GUS hang at exit by deinitializing digi before midi.
 * 
 * Revision 1.7  1994/12/08  10:01:33  john
 * Changed the way the player callsign stuff works.
 * 
 * Revision 1.6  1994/12/01  11:24:07  john
 * Made volume/gamma/joystick sliders all be the same length.  0-->8.
 * 
 * Revision 1.5  1994/11/29  02:01:07  john
 * Added code to look at -volume command line arg.
 * 
 * Revision 1.4  1994/11/14  20:14:11  john
 * Fixed some warnings.
 * 
 * Revision 1.3  1994/11/14  19:51:01  john
 * Added joystick cal values to descent.cfg.
 * 
 * Revision 1.2  1994/11/14  17:53:09  allender
 * read and write descent.cfg file
 * 
 * Revision 1.1  1994/11/14  16:28:08  allender
 * Initial revision
 * 
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "dtypes.h"
#include "game.h"
#include "digi.h"
#include "kconfig.h"
#include "palette.h"
#include "joy.h"
#include "args.h"
#include "player.h"
#include "mission.h"
#include "macsys.h"

#pragma off (unreferenced)
static char rcsid[] = "$Id: config.c 1.8 1995/10/27 10:52:20 allender Exp $";
#pragma on (unreferenced)

#if 0
static char *config_vr_type_str = "VR_type";
static char *config_vr_tracking_str = "VR_tracking";
#endif

#define MAX_CTB_LEN	512

typedef struct preferences {
	ubyte	digi_volume;
	ubyte	midi_volume;
	ubyte	stereo_reverse;
	ubyte	detail_level;
	ubyte	oc;					// object complexity
	ubyte	od;					// object detail
	ubyte	wd;					// wall detail
	ubyte	wrd;				// wall render depth
	ubyte	da;					// debris amount
	ubyte	sc;					// sound channels
	ubyte	gamma_level;
	ubyte	pixel_double;
	int		joy_axis_min[4];
	int		joy_axis_max[4];
	int		joy_axis_center[4];
	char	lastplayer[CALLSIGN_LEN+1];
	char	lastmission[MISSION_NAME_LEN+1];
	char	ctb_config[MAX_CTB_LEN];
	int		ctb_tool;
	ubyte	master_volume;
} Preferences;

char config_last_player[CALLSIGN_LEN+1] = "";
char config_last_mission[MISSION_NAME_LEN+1] = "";
char config_last_ctb_cfg[MAX_CTB_LEN] = "";
int config_last_ctb_tool;
ubyte Config_master_volume = 4;

int Config_vr_type = 0;
int Config_vr_tracking = 0;

extern byte	Object_complexity, Object_detail, Wall_detail, Wall_render_depth, Debris_amount, SoundChannels;
extern void digi_set_master_volume( int volume );

void set_custom_detail_vars(void);

static ubyte have_prefs = 0;

int ReadConfigFile()
{
	int i;
	OSErr err;
	Handle prefs_handle;
	Preferences *prefs;
	char *p;
	
	if (!have_prefs) {			// not initialized....get a handle to the preferences file
		InitPrefsFile('DCNT');
		have_prefs = 1;
	}
	
	prefs_handle = NewHandleClear(sizeof(Preferences));		// new prefs handle
	if (prefs_handle == NULL)
		return;
		
	prefs = (Preferences *)(*prefs_handle);
	err = LoadPrefsFile(prefs_handle);
	if (err) {
		DisposeHandle(prefs_handle);
		return -1;
	}

	p = (char *)prefs;
	for (i = 0; i < sizeof(Preferences); i++) {
		if (*p != 0)
			break;
		p++;
	}
	if ( i == sizeof(Preferences) )
		return -1;
	
	Config_digi_volume = prefs->digi_volume;
	Config_midi_volume = prefs->midi_volume;
	Config_master_volume = prefs->master_volume;
	Config_channels_reversed = prefs->stereo_reverse;
	gr_palette_set_gamma( (int)(prefs->gamma_level) );
	Scanline_double = (int)prefs->pixel_double;
	Detail_level = prefs->detail_level;
	if (Detail_level == NUM_DETAIL_LEVELS-1) {
		Object_complexity = prefs->oc;
		Object_detail = prefs->od;
		Wall_detail = prefs->wd;
		Wall_render_depth = prefs->wrd;
		Debris_amount = prefs->da;
		SoundChannels = prefs->sc;
		set_custom_detail_vars();
	}
	strncpy( config_last_player, prefs->lastplayer, CALLSIGN_LEN );
	p = strchr(config_last_player, '\n' );
	if (p) *p = 0;
	
	strncpy(config_last_mission, prefs->lastmission, MISSION_NAME_LEN);
	p = strchr(config_last_mission, '\n' );
	if (p) *p = 0;

	strcpy(config_last_ctb_cfg, prefs->ctb_config);
	
	if ( Config_digi_volume > 8 ) Config_digi_volume = 8;

	if ( Config_midi_volume > 8 ) Config_midi_volume = 8;

	joy_set_cal_vals( prefs->joy_axis_min, prefs->joy_axis_center, prefs->joy_axis_max);
	digi_set_volume( (Config_digi_volume*256)/8, (Config_midi_volume*256)/8 );
	digi_set_master_volume(Config_master_volume);
	
	DisposeHandle(prefs_handle);
	return 0;
}

int WriteConfigFile()
{
	OSErr err;
	Handle prefs_handle;
	Preferences *prefs;
	
	prefs_handle = NewHandleClear(sizeof(Preferences));		// new prefs handle
	if (prefs_handle == NULL)
		return;
		
	prefs = (Preferences *)(*prefs_handle);
	
	joy_get_cal_vals(prefs->joy_axis_min, prefs->joy_axis_center, prefs->joy_axis_max);
	prefs->digi_volume = Config_digi_volume;
	prefs->midi_volume = Config_midi_volume;
	prefs->stereo_reverse = Config_channels_reversed;
	prefs->detail_level = Detail_level;
	if (Detail_level == NUM_DETAIL_LEVELS-1) {
		prefs->oc = Object_complexity;
		prefs->od = Object_detail;
		prefs->wd = Wall_detail;
		prefs->wrd = Wall_render_depth;
		prefs->da = Debris_amount;
		prefs->sc = SoundChannels;
	}
	prefs->gamma_level = (ubyte)gr_palette_get_gamma();
	prefs->pixel_double = (ubyte)Scanline_double;
	strncpy( prefs->lastplayer, Players[Player_num].callsign, CALLSIGN_LEN );
	strncpy( prefs->lastmission, config_last_mission, MISSION_NAME_LEN );
	strcpy( prefs->ctb_config, config_last_ctb_cfg);
	prefs->ctb_tool = config_last_ctb_tool;
	prefs->master_volume = Config_master_volume;

	err = SavePrefsFile(prefs_handle);
	DisposeHandle(prefs_handle);
	return (int)err;
}		

