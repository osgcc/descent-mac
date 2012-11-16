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
 * $Source: Smoke:miner:source:misc::RCS:error.c $
 * $Revision: 1.10 $
 * $Author: allender $
 * $Date: 1995/10/13 14:42:34 $
 * 
 * functions to deal with error and warning dialogs
 * 
 * $Log: error.c $
 * Revision 1.10  1995/10/13  14:42:34  allender
 * *** empty log message ***
 *
 * Revision 1.9  1995/10/12  17:40:45  allender
 * fixed code so error/warning dialogs will display properly
 * on second monitor
 *
 * Revision 1.8  1995/07/31  15:25:53  allender
 * *** empty log message ***
 *
 * Revision 1.7  1995/07/28  13:11:52  allender
 * cursor manipulation during warning and error dialogs
 *
 * Revision 1.6  1995/07/13  11:16:13  allender
 * call to debug_video mode on error or warning
 *
 * Revision 1.5  1995/07/05  16:21:45  allender
 * extern definitions
 *
 * Revision 1.4  1995/06/06  12:19:14  allender
 * call comm_close on error to close the comm port
 *
 * Revision 1.3  1995/05/12  13:06:24  allender
 * removed Error call from MyAssert so tracing out of this
 * function is possible
 *
 * Revision 1.2  1995/05/11  12:57:22  allender
 * added MyAssert function
 *
 * Revision 1.1  1995/05/04  20:12:23  allender
 * Initial revision
 *
 * Revision 1.2  1995/03/17  09:40:01  allender
 * *** empty log message ***
 *
 * Revision 1.1  1995/03/09  09:30:21  allender
 * Initial revision
 *
 *
 */
 
#include <stdio.h>
#include <stdarg.h>
#include <Quickdraw.h>
#include <Dialogs.h>
#include <SegLoad.h>		// for ExitToShell
#include <TextUtils.h>
#include "dtypes.h"
#include "error.h"
#include "resource.h"
#include "macsys.h"
#include "palette.h"

#define ESTRING (unsigned char const *)" "

extern void debug_video_mode();
extern void reset_debug_video_mode();

void Error(char *format, ...)
{
	short item;
	va_list args;
	char tmp_buf[256];

	show_cursor();
	debug_video_mode();
	memset(tmp_buf, 0, 256);	
	va_start(args, format);
	vsprintf(tmp_buf, format, args);
	ParamText((unsigned char const *)c2pstr(tmp_buf), ESTRING, ESTRING, ESTRING);
	
	item = StopAlert(ERROR_ALERT, nil);

	exit(1);	
}

void Warning(char *format, ...)
{
	short item;
	va_list args;
	char tmp_buf[256];
	int reset_device = 0;

	show_cursor();
	if ( gr_palette_faded_out )
		debug_video_mode();
	memset(tmp_buf, 0, 256);	
	va_start(args, format);
	vsprintf(tmp_buf, format, args);
	ParamText((unsigned char const *)c2pstr(tmp_buf), ESTRING, ESTRING, ESTRING);

	item = CautionAlert(WARN_ALERT, nil);
	hide_cursor();
	if ( gr_palette_faded_out )
		reset_debug_video_mode();
}

void MyAssert(int expr, char *expr_text, char *filename, int linenum)
{
	if (!(expr)) {
		Int3();
//		Error("Assertion failed: %s, file %s, line %d", expr_text, filename, linenum);
	}
}
