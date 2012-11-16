#
# $Source: Smoke:miner:source:misc::RCS:makefile $
# $Revision: 1.4 $
# $Author: allender $
# $Date: 1995/08/24 10:34:38 $
#
# Makefile for graphics functions
#

LIBDIR = ::lib:
OBJDIR = :obj:
SRCDIR = :

# What libs to make
LIB = misc.lib

# includes to copy to lib directory
GLOBAL_INCLUDES = strutil.h byteswap.h fileutil.h error.h direct.h

# test file libraries needed
TEST_LIBS = {LIBDIR}gr.lib {LIBDIR}mem.lib {LIBDIR}io.lib {LIBDIR}cfile.lib

# standard libs to link anything with
STD_LIBS = ¶
	"{CLibraries}"CSANELib.o ¶
	"{CLibraries}"Math.o ¶
	"{CLibraries}"StdClib.o ¶
	"{Libraries}"Runtime.o ¶
	"{Libraries}"Interface.o

# resource files to be used in test file
TEST_RESOURCES = {LIBDIR}bios.r

OBJ_DIR = :obj:

# C compiler options
CFLAGS = {SYM_FLAG}
	
LDFLAGS = ¶
	{SYM_FLAG}
	
MISC_OBJS = ¶
	{OBJDIR}strutil.c.o {OBJDIR}byteswap.c.o {OBJDIR}fileutil.c.o ¶
	{OBJDIR}error.c.o {OBJDIR}misc.c.o {OBJDIR}direct.c.o
	
All Ä {LIB}

{LIB} Ä {MISC_OBJS}
	Echo "# `Date -t` ----- Building MISC library..."
	{Linker} {LibraryFlags} {OBJ_DIR}Å -o {LIB} {SYM_FLAG}
	Echo "# Copying files to lib directory..."
	duplicate -y {LIB} ::lib
	duplicate -y {GLOBAL_INCLUDES} ::lib
	
testg Ä testg.c.o
	Link -t 'APPL' -c '????' -sym on -model far -mf ¶
		testg.c.o {STD_LIBS} ¶
		{TEST_LIBS} ¶
		-o {Targ}
	Rez {TEST_RESOURCES} -rd -append -o {Targ}

clean Ä
	del -i :obj:Å
	del -i misc.lib

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

