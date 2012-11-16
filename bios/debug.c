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
 * $Source: Smoke:miner:source:bios::RCS:debug.c $
 * $Revision: 1.2 $
 * $Author: allender $
 * $Date: 1995/06/16 15:28:57 $
 *
 * Header for monochrome/mprintf functions
 *
 * $Log: debug.c $
 * Revision 1.2  1995/06/16  15:28:57  allender
 * fixed "unused" pragma
 *
 * Revision 1.1  1995/05/05  09:54:14  allender
 * Initial revision
 *
 *
*/

//============================================================================
//
//	This is the Think C 6.0 code to send a message to the DebugWindow server
//	(in other words, this is the code to DebugWindow.Lib that came with your
//	DebugWindow package).  I'm providing this code to document the AppleEvent
//	procedures necessary to communicate with DebugWindow; those of you who
//	need a specialized version, or need to port it to another environment
//	(such as Pascal or MacApp) should find everything that you need to know
//	right here.
//
//	If you implement this into a new environment, I'd appreciate it if you
//	could send me the new modules so that I can include them with the next
//	release of DebugWindow (with the proper credits going to you, of course!).
//
//
//	Here are the necessary steps to send a string to DebugWindow:
//
//		¥ create an AppleEvent for signature 'LdbW' with a type of 'misc/dmsg'
//
//		¥ add a parameter of type 'keyDirectObject/typeChar' passing a pointer
//		  to the string to display and its length
//
//		¥ send it on its way
//
//============================================================================


#include	<stdio.h>
#include	<stdarg.h>
#include	<AppleEvents.h>



void __SendToDebugWindow ( char *stringToSend )
{
	AEAddressDesc	address;
	AppleEvent		appleEvent, reply;
	OSType			targetSig;
	
	targetSig = 'LdbW';

	if ( AECreateDesc ( typeApplSignature, (Ptr)&targetSig, 
						sizeof targetSig, &address ) == 0 ) {

		if ( AECreateAppleEvent ( 'misc', 'dmsg', &address, kAutoGenerateReturnID,
								   kAnyTransactionID, &appleEvent ) == 0 ) {

			if ( AEPutParamPtr ( &appleEvent, keyDirectObject, typeChar,
								 stringToSend, strlen (stringToSend) ) == 0 ) {

				AESend ( &appleEvent, &reply, 
						 kAEWaitReply + kAENeverInteract,
						 kAENormalPriority, 
						 300, 								// up to 5 second wait..
						 nil, nil );
				
				AEDisposeDesc ( &reply );
			}
			AEDisposeDesc ( &appleEvent );
		}
		AEDisposeDesc ( &address );
	}
}

void Debug ( int n, char *format, ... )
{
#pragma unused(n)
	va_list		argptr;
	long		len;
	OSErr		err;
	char		tDebugString [512];

	va_start ( argptr, format );
	len = (long)vsprintf ( tDebugString, format, argptr );
	va_end ( argptr );
	if ( len > 0 )
		__SendToDebugWindow ( tDebugString );
}


void ClearDebugWindow (int c)
{
#pragma unused(c)
	__SendToDebugWindow ( "~c" );
}


void DebugTimestamp (int n)
{
#pragma unused(n)
	__SendToDebugWindow ( "~t" );
}

