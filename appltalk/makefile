#
# $Source: Buggin:miner:source:fix::RCS:makefile $
# $Revision: 1.2 $
# $Author: allender $
# $Date: 1995/05/11 13:03:29 $
#
# Makefile for graphics functions
#

LIBDIR = ::lib:
OBJDIR = :obj:
SRCDIR = :

# What libs to make
LIB = appltalk.lib

# includes to copy to lib directory
GLOBAL_INCLUDES = appltalk.h

# standard libs to link anything with
STD_LIBS = �
	"{CLibraries}"CSANELib.o �
	"{CLibraries}"Math.o �
	"{CLibraries}"StdClib.o �
	"{Libraries}"Runtime.o �
	"{Libraries}"Interface.o

OBJ_DIR = :obj:

# C compiler options
CFLAGS = {SYM_FLAG}

LDFLAGS = �
	{SYM_FLAG}

APPLETALK_OBJS = �
	listener.rsrc {OBJDIR}appltalk.c.o
	
All � {LIB}

{LIB} � {APPLETALK_OBJS}
	Echo "# `Date -t` ----- Building {LIB}"
	{Linker} {LibraryFlags} {OBJ_DIR}� -o {LIB} {SYM_FLAG}
	Echo "# Copying files to lib directory..."
	duplicate -y {LIB} ::lib
	duplicate -y listener.r ::lib
	duplicate -y {GLOBAL_INCLUDES} ::lib
	
clean �
	del -i :listener.rsrc
	del -i :obj:�
	del -i {LIB}

# dependency for obj and source directories
"{OBJDIR}"		�	"{SRCDIR}"

listener.rsrc � listener.a
	Echo `Date -t` ---- Assembling listener.a
	rm -i listener.c.o
	Asm listener.a {AFlags} -o "listener.a.o" -model far �
		|| ( Echo "#####   ### ERROR ###   #####" )
	link -o listener.rsrc -t rsrc -c RSED listener.a.o -rt Sock=128 -m THE_LISTENER
	derez listener.rsrc > listener.r
	rm listener.a.o
	
.c.o	�	.c
	Echo `Date -t` ---- Compiling {default}.c
	rm -i {targDir}{default}.c.o
	{C} "{default}.c" {MyCFlags} {CFlags} �
		-o "{targDir}{default}.c.o"		�
		|| ( Echo "#####   ### ERROR ###   #####" )

### OPUS MKMF:  Do not remove this line!  Generated dependencies follow.

{OBJDIR}listener.a.o � listener.a

{OBJDIR}appltalk.c.o � appltalk.c appltalk.h



