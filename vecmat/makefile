#
# $Source: Buggin:miner:source:vecmat::RCS:makefile $
# $Revision: 1.3 $
# $Author: allender $
# $Date: 1995/06/25 21:51:20 $
#
# Makefile for vecmat library
#

OBJDIR = :obj:
SRCDIR = :
LIBDIR = ::lib:

# What libs to make
LIB = vecmat.lib

# include files to copy to lib directory
GLOBAL_INCLUDES = vecmat.h

# test file libraries needed
TEST_LIBS = {LIBDIR}io.lib {LIBDIR}fix.lib {LIBDIR}vecmat.lib {LIBDIR}macsys.lib

# standard libs to link anything with
STD_LIBS = ¶
	"{CLibraries}"CSANELib.o ¶
	"{CLibraries}"Math.o ¶
	"{CLibraries}"StdClib.o ¶
	"{Libraries}"Runtime.o ¶
	"{Libraries}"Interface.o

# resource files to be used in test file
TEST_RESOURCES = {LIBDIR}bios.r {LIBDIR}macsys.r

OBJ_DIR = :obj:
RESOURCE_DIR = ::resource:

# C compiler options
CFLAGS = {SYM_FLAG}
	
LDFLAGS = ¶
	{SYM_FLAG}
	
VECMAT_OBJS = ¶
	{OBJDIR}vecmat.c.o {OBJDIR}vecmat.a.o
#	{OBJDIR}vecmat.c.o
	
All Ä {LIB}

{LIB} Ä {VECMAT_OBJS}
	Echo "# `Date -t` ----- Building {LIB}..."
	{Linker} {LibraryFlags} {OBJ_DIR}Å -o {LIB}
	Echo "# Copying files to lib directory..."
	duplicate -y {LIB} ::lib
	duplicate -y {GLOBAL_INCLUDES} ::lib

vectest Ä vectest.c.o {TEST_LIBS}
	Link -t 'APPL' -c '????' -sym on -model far -mf ¶
		vectest.c.o {STD_LIBS} ¶
		{TEST_LIBS} ¶
		-o {Targ}
	Rez {TEST_RESOURCES} -rd -append -o {Targ}

clean Ä
	del -i :obj:Å
	del -i "{LIB}"

# dependency for obj and source directories
"{OBJDIR}"		Ä	"{SRCDIR}"

.c.o	Ä	.c
	Echo `Date -t` ---- Compiling {default}.c
	rm -i "{targDir}{default}.c.o"
	{C} "{depDir}{default}.c" {MyCFlags} {CFlags} ¶
		-o "{targDir}{default}.c.o"		¶
		|| ( Echo "#####   ### ERROR ###   #####" )

.a.o	Ä	.a
	Echo "# `Date -t` ----- Assembling {default}.a..."
	if "{Asm}" == "PPCAsm"
		rm -i "{targDir}{default}.a.o"
		{Asm} "{depDir}{default}.a"	-o "{targDir}{default}.a.o"	¶
			|| ( Echo "#####   ### ERROR ###   #####" )
#	else
#		rm -i :obj:fix.a.o
#		{Asm} fix.a	-o :obj:fix.a.o		¶
#			|| ( Echo "#####   ### ERROR ###   #####" )
	end

### OPUS MKMF:  Do not remove this line!  Generated dependencies follow.

:obj:vecmat.c.o Ä makefile vecmat.c vecmat.h
