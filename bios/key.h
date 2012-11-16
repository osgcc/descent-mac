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
 * $Source: Smoke:miner:source:bios::RCS:key.h $
 * $Revision: 1.9 $
 * $Author: allender $
 * $Date: 1995/09/06 13:08:42 $
 *
 * Header for keyboard functions
 *
 * $Log: key.h $
 * Revision 1.9  1995/09/06  13:08:42  allender
 * fixed command modifier
 *
 * Revision 1.8  1995/07/26  16:57:57  allender
 * added command key to key list
 *
 * Revision 1.7  1995/05/12  14:53:58  allender
 * changed key_to_ascii to return unsigned char now!
 *
 * Revision 1.6  1995/05/12  14:49:38  allender
 * changed prototype of key_to_ascii to return int instead of
 * char
 *
 * Revision 1.5  1995/05/11  13:05:09  allender
 * remove a5 references for powerPC
 *
 * Revision 1.4  1995/05/05  16:34:32  allender
 * hanges types.h to dtypes.h
 *
 * Revision 1.3  1995/04/05  11:41:13  allender
 * *** empty log message ***
 *
 * Revision 1.2  1995/03/27  14:53:26  allender
 * *** empty log message ***
 *
 * Revision 1.1  1995/03/09  09:32:51  allender
 * Initial revision
 *
 *
 * --- PC RCS information ---
 * Revision 1.19  1994/10/24  13:58:12  john
 * Hacked in support for pause key onto code 0x61.
 * 
 * Revision 1.18  1994/10/21  15:17:10  john
 * Added KEY_PRINT_SCREEN
 * 
 * Revision 1.17  1994/08/31  12:22:13  john
 * Added KEY_DEBUGGED
 * 
 * Revision 1.16  1994/08/24  18:53:50  john
 * Made Cyberman read like normal mouse; added dpmi module; moved
 * mouse from assembly to c. Made mouse buttons return time_down.
 * 
 * Revision 1.15  1994/08/18  14:56:16  john
 * *** empty log message ***
 * 
 * Revision 1.14  1994/08/08  10:43:24  john
 * Recorded when a key was pressed for key_inkey_time.
 * 
 * Revision 1.13  1994/06/17  17:17:28  john
 * Added keyd_time_last_key_was_pressed or something like that.
 * 
 * Revision 1.12  1994/04/29  12:14:19  john
 * Locked all memory used during interrupts so that program
 * won't hang when using virtual memory.
 * 
 * Revision 1.11  1994/02/17  15:57:14  john
 * Changed key libary to C.
 * 
 * Revision 1.10  1994/01/31  08:34:09  john
 * Fixed reversed lshift/rshift keys.
 * 
 * Revision 1.9  1994/01/18  10:58:17  john
 * *** empty log message ***
 * 
 * Revision 1.8  1993/10/16  19:24:43  matt
 * Added new function key_clear_times() & key_clear_counts()
 * 
 * Revision 1.7  1993/10/15  10:17:09  john
 * added keyd_last_key_pressed and released for use with recorder.
 * 
 * Revision 1.6  1993/10/06  16:20:37  john
 * fixed down arrow bug
 * 
 * Revision 1.5  1993/10/04  13:26:42  john
 * changed the #defines for scan codes.
 * 
 * Revision 1.4  1993/09/28  11:35:20  john
 * added key_peekkey
 * 
 * Revision 1.3  1993/09/20  18:36:43  john
 * *** empty log message ***
 * 
 * Revision 1.1  1993/07/10  13:10:39  matt
 * Initial revision
 * 
 *
 */

#ifndef _KEY_H
#define _KEY_H 

#include "fix.h"
#include "dtypes.h"

//==========================================================================
// This installs the int9 vector and initializes the keyboard in buffered
// ASCII mode. key_close simply undoes that.
extern void key_init();
extern void key_close();

//==========================================================================
// These are configuration parameters to setup how the buffer works.
// set keyd_buffer_type to 0 for no key buffering.
// set it to 1 and it will buffer scancodes.
extern unsigned char keyd_buffer_type;
extern unsigned char keyd_repeat;        // 1=allow repeating, 0=dont allow repeat

// keyd_editor_mode... 0=game mode, 1=editor mode.
// Editor mode makes key_down_time always return 0 if modifiers are down.
extern char keyd_editor_mode;		

// Time in seconds when last key was pressed...
extern volatile int keyd_time_when_last_pressed;

//==========================================================================
// These are the "buffered" keypress routines.  Use them by setting the
// "keyd_buffer_type" variable.

extern void key_flush();    // Clears the 256 char buffer
extern int key_checkch();   // Returns 1 if a char is waiting
extern int key_getch();     // Gets key if one waiting other waits for one.
extern int key_inkey();     // Gets key if one, other returns 0.
extern int key_inkey_time(fix *time);     // Same as inkey, but returns the time the key was pressed down.
extern int key_peekkey();   // Same as inkey, but doesn't remove key from buffer.

extern unsigned char key_to_ascii(int keycode );

extern void key_debug();    // Does an INT3

//==========================================================================
// These are the unbuffered routines. Index by the keyboard scancode.

// Set to 1 if the key is currently down, else 0
extern volatile unsigned char keyd_pressed[];
extern volatile unsigned char keyd_last_pressed;
extern volatile unsigned char keyd_last_released;

// Returns the seconds this key has been down since last call.
extern fix key_down_time(int scancode);

// Returns number of times key has went from up to down since last call.
extern unsigned int key_down_count(int scancode);

// Returns number of times key has went from down to up since last call.
extern unsigned int key_up_count(int scancode);

// Clears the times & counts used by the above functions
// Took out... use key_flush();
//void key_clear_times();
//void key_clear_counts();

//  definition for the keyboard handler.  externed to timer.c because all of the
//  timer routines reside there
extern void keyboard_handler(void);


#define KEY_SHIFTED     0x100
#define KEY_ALTED       0x200
#define KEY_CTRLED      0x400
#define KEY_DEBUGGED	0x800
#define KEY_COMMAND		0x1000

#define KEY_0           0x1D
#define KEY_1           0x12
#define KEY_2           0x13
#define KEY_3           0x14
#define KEY_4           0x15
#define KEY_5           0x17
#define KEY_6           0x16
#define KEY_7           0x1A
#define KEY_8           0x1C
#define KEY_9           0x19

#define KEY_A           0x3F
#define KEY_B           0x0B
#define KEY_C           0x08
#define KEY_D           0x02
#define KEY_E           0x0E
#define KEY_F           0x03
#define KEY_G           0x05
#define KEY_H           0x04
#define KEY_I           0x22
#define KEY_J           0x26
#define KEY_K           0x28
#define KEY_L           0x25
#define KEY_M           0x2E
#define KEY_N           0x2D
#define KEY_O           0x1F
#define KEY_P           0x23
#define KEY_Q           0x0C
#define KEY_R           0x0F
#define KEY_S           0x01
#define KEY_T           0x11
#define KEY_U           0x20
#define KEY_V           0x09
#define KEY_W           0x0D
#define KEY_X           0x07
#define KEY_Y           0x10
#define KEY_Z           0x06

#define KEY_MINUS       0x1B
#define KEY_EQUAL       0x18
#define KEY_DIVIDE      0x2C
#define KEY_SLASH       0x2A
#define KEY_COMMA       0x2B
#define KEY_PERIOD      0x2F
#define KEY_SEMICOL     0x29

#define KEY_LBRACKET    0x21
#define KEY_RBRACKET    0x1E

#define KEY_RAPOSTRO    0x27
#define KEY_LAPOSTRO    0x32

#define KEY_ESC         0x35
#define KEY_ENTER       0x24
#define KEY_BACKSP      0x33
#define KEY_TAB         0x30
#define KEY_SPACEBAR    0x31

#define KEY_NUMLOCK     0x47
#define KEY_SCROLLOCK   0x6B
#define KEY_CAPSLOCK    0x39

#define KEY_LSHIFT      0x38
#define KEY_RSHIFT      0x38

#define KEY_LALT        0x3A
#define KEY_RALT        0x3A

#define KEY_LCTRL       0x3B
#define KEY_RCTRL       0x3B

#define KEY_CMD			0x37

#define KEY_F1          0x7A
#define KEY_F2          0x78
#define KEY_F3          0x63
#define KEY_F4          0x76
#define KEY_F5          0x60
#define KEY_F6          0x61
#define KEY_F7          0x62
#define KEY_F8          0x64
#define KEY_F9          0x65
#define KEY_F10         0x6D
#define KEY_F11         0x67
#define KEY_F12         0x6F

#define KEY_PAD0        0x52
#define KEY_PAD1        0x53
#define KEY_PAD2        0x54
#define KEY_PAD3        0x55
#define KEY_PAD4        0x56
#define KEY_PAD5        0x57
#define KEY_PAD6        0x58
#define KEY_PAD7        0x59
#define KEY_PAD8        0x5B
#define KEY_PAD9        0x5C
#define KEY_PADMINUS    0x4E
#define KEY_PADPLUS     0x45
#define KEY_PADPERIOD   0x41
#define KEY_PADDIVIDE   0x4B
#define KEY_PADMULTIPLY 0x43
#define KEY_PADENTER    0x4C

#define KEY_INSERT      0x72
#define KEY_HOME        0x73
#define KEY_PAGEUP      0x74
#define KEY_DELETE      0x75
#define KEY_END         0x77
#define KEY_PAGEDOWN    0x79
#define KEY_UP          0x7E
#define KEY_DOWN        0x7D
#define KEY_LEFT        0x7B
#define KEY_RIGHT       0x7C

#define KEY_PRINT_SCREEN	0x69
#define KEY_PAUSE			0x71

#endif
