#
# $Source: Buggin:miner:source:fix::RCS:makefile $
# $Revision: 1.3 $
# $Author: allender $
# $Date: 1995/06/25 21:55:35 $
#
# Makefile for graphics functions
#

LIBDIR = ::lib:
OBJDIR = :obj:
SRCDIR = :

# What libs to make
LIB = fix.lib

# includes to copy to lib directory
GLOBAL_INCLUDES = fix.h

# test file libraries needed
TEST_LIBS = {LIBDIR}fix.lib {LIBDIR}io.lib {LIBDIR}macsys.lib

# standard libs to link anything with
STD_LIBS = ¶
	"{CLibraries}"CSANELib.o ¶
	"{CLibraries}"Math.o ¶
	"{CLibraries}"StdClib.o ¶
	"{Libraries}"Runtime.o ¶
	"{Libraries}"Interface.o

# standard libs to link anything with
STDSC_LIBS = ¶
	"{SCLibraries}"SCMainC.a.o ¶
	"{SCLibraries}"SCLibC.o ¶
	"{CLibraries}"CSANELib.o ¶
	"{CLibraries}"Math.o ¶
	"{Libraries}"Runtime.o ¶
	"{Libraries}"Interface.o

# resource files to be used in test file
TEST_RESOURCES = {LIBDIR}bios.r

OBJ_DIR = :obj:

# C compiler options
CFLAGS = {SYM_FLAG}

LDFLAGS = ¶
	{SYM_FLAG}

FIX_OBJS = ¶
	{OBJDIR}fix.c.o {OBJDIR}tables.c.o {OBJDIR}fix.ppc.a.o
	
All Ä {LIB}

{LIB} Ä {FIX_OBJS}
	Echo "# `Date -t` ----- Building FIX library..."
	{Linker} {LibraryFlags} {OBJ_DIR}Å -o {LIB}
	Echo "# Copying files to lib directory..."
	duplicate -y {LIB} ::lib
	duplicate -y {GLOBAL_INCLUDES} ::lib
	
fixtest Ä fixtest.c.o {TEST_LIBS}
	Link -t 'APPL' -c '????' -sym on -model far -mf ¶
		fixtest.c.o {STD_LIBS} ¶
		{TEST_LIBS} ¶
		-o {Targ}
	Rez {TEST_RESOURCES} -rd -append -o {Targ}

clean Ä
	del -i :obj:Å
	del -i {LIB}

# dependency for obj and source directories
"{OBJDIR}"		Ä	"{SRCDIR}"

.c.o	Ä	.c
	Echo `Date -t` ---- Compiling {default}.c
	rm -i {targDir}{default}.c.o
	{C} "{depDir}{default}.c" {MyCFlags} {CFlags} ¶
		-o "{targDir}{default}.c.o"		¶
		|| ( Echo "#####   ### ERROR ###   #####" )

.a.o	Ä	.a
	if "{Asm}" == "PPCAsm"
		Echo "# `Date -t` ----- Assembling {default}.a..."
		rm -i {targDir}{default}.a.o
		{Asm} "{depDir}{default}.a"		{AFLAGS}	¶
			-o "{targDir}{default}.a.o"		¶
			|| ( Echo "#####   ### ERROR ###   #####" )
	end
#	if "{Asm}" == "PPCAsm"
#		{Asm} fix.ppc.a	-o :obj:fix.a.o		¶
#			|| ( Echo "#####   ### ERROR ###   #####" )
#	else
#		rm -i :obj:fix.a.o
#		{Asm} fix.a	-o :obj:fix.a.o		¶
#			|| ( Echo "#####   ### ERROR ###   #####" )
#	end

### OPUS MKMF:  Do not remove this line!  Generated dependencies follow.

{OBJDIR}fix.c.o Ä fix.h

{OBJDIR}fixtest.c.o Ä fix.h

{OBJDIR}tables.c.o Ä fix.h


