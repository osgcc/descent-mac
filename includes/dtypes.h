/*
 * $Source: f:/miner/source/includes/rcs/types.h $
 * $Revision: 1.2 $
 * $Author: matt $
 * $Date: 1993/09/14 12:12:30 $
 *
 * Common types for use in Miner
 *
 * $Log: types.h $
 * Revision 1.2  1993/09/14  12:12:30  matt
 * Added #define for NULL
 * 
 * Revision 1.1  1993/08/24  12:50:40  matt
 * Initial revision
 * 
 *
 */

#ifndef _TYPES_H
#define _TYPES_H

//define a byte 
typedef signed char byte;

//define unsigned types;
typedef unsigned char ubyte;
typedef unsigned short ushort;
typedef unsigned int uint;
typedef unsigned long ulong;

//define a boolean
typedef ubyte bool;

#ifndef NULL
#define NULL 0
#endif

#endif

