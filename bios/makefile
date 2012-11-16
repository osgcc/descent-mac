#
# $Source: Smoke:miner:source:bios::RCS:makefile $
# $Revision: 1.14 $
# $Author: allender $
# $Date: 1995/10/25 09:23:40 $
#
# Makefile for bios functions
#

OBJDIR = :obj:
SRCDIR = :

# What libs to make
LIB = io.lib

# include files to copy to lib directory
GLOBAL_INCLUDES = mono.h joy.h gtimer.h key.h mouse.h

OBJ_DIR = :obj:
RESOURCE_DIR = ::resource:

# C compiler options
CFLAGS = {SYM_FLAG}
	
LDFLAGS = ¶
	{SYM_FLAG}
	
IO_OBJS = ¶
	{OBJDIR}debug.c.o {OBJDIR}key.c.o {OBJDIR}joyc.c.o {OBJDIR}timer.c.o ¶
	{OBJDIR}mouse.c.o {OBJDIR}console.c.o
	
All Ä {LIB}

{LIB} Ä {IO_OBJS}
	Echo "# `Date -t` ----- Building IO library..."
	{Linker} {LibraryFlags} {OBJ_DIR}Å -o {LIB}
	Echo "# Copying files to lib directory..."
	duplicate -y {LIB} ::lib
	duplicate -y {GLOBAL_INCLUDES} ::lib

clean Ä
	del -i :obj:Å
	del -i io.lib

# dependency for obj and source directories
"{OBJDIR}"		Ä	"{SRCDIR}"

.c.o	Ä	.c
	Echo `Date -t` ---- Compiling {default}.c
	{C} "{default}.c" {MyCFlags} {CFlags} ¶
		-o "{targDir}{default}.c.o"		¶
		|| ( Echo "#####   ### ERROR ###   #####" )

.a.o	Ä	.a
	Echo "# `Date -t` ----- Assembling {default}.a..."
	Asm "{depDir}{default}.a"			¶
		-o "{targDir}{default}.a.o"		¶
		|| ( Echo "#####   ### ERROR ###   #####" )

### OPUS MKMF:  Do not remove this line!  Generated dependencies follow.

:obj:debug.c.o Ä debug.c

:obj:joyc.c.o Ä joyc.c mono.h joy.h

:obj:key.c.o Ä key.c ::lib:dtypes.h key.h ::lib:fix.h gtimer.h

:obj:timer.c.o Ä timer.c ::lib:dtypes.h gtimer.h ::lib:fix.h
