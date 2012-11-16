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
/****************************************************************************
*
*  File              : soscomp.h
*  Date Created      : 6/1/94
*  Description       : 
*
*  Programmer(s)     : Nick Skrepetos
*  Last Modification : 10/1/94 - 11:37:9 AM
*  Additional Notes  :
*
*****************************************************************************
*            Copyright (c) 1994,  HMI, Inc.  All Rights Reserved            *
****************************************************************************/

#ifndef  _SOS_COMPRESS
#define  _SOS_COMPRESS

// define compression structure
typedef  struct   _tagCOMPRESS_INFO
         {
            // buffers for source and destination
            ubyte * lpSource;
            ubyte * lpDest;

            // compressed size
            int	dwCompSize;

            // uncompressed size
            int	dwUnCompSize;

            // decompress location
            int	dwSampleIndex;

            // predicted sample
            int dwPredicted;

            // difference
            int  dwDifference;

            // code buffer ( tokens )
            short wCodeBuf;

            // 4 bit nibble code
            short wCode;

            // step value
            short wStep;

            // index into step table
            short wIndex;

            // type of sample to uncompress
            short wBitSize;

         } _SOS_COMPRESS_INFO;

// compression/decompression functions
int  sosCODECDecompressData     ( _SOS_COMPRESS_INFO *, int );
int  sosCODECCompressData       ( _SOS_COMPRESS_INFO *, int );
void sosCODECInitStream         ( _SOS_COMPRESS_INFO * );

#endif
