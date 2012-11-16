#
# $Source: Buggin:miner:source:texmap::RCS:makefile $
# $Revision: 1.2 $
# $Author: allender $
# $Date: 1995/06/25 21:52:45 $
#
# Makefile for graphics functions
#

LIBDIR = ::lib:
OBJDIR = :obj:
SRCDIR = :

# What libs to make
LIB = texmap.lib

# includes to copy to lib directory
GLOBAL_INCLUDES = texmap.h

# test file libraries needed
TEST_LIBS = {LIBDIR}gr.lib {LIBDIR}mem.lib {LIBDIR}io.lib {LIBDIR}cfile.lib ¶
	{LIBDIR}misc.lib {LIBDIR}macsys.lib

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

# C compiler options
#CFLAGS = {SYM_FLAG} -d NASM
CFLAGS = {SYM_FLAG}

# Asm compiler options
AFLAGS = -sym on
	
LDFLAGS = ¶
	{SYM_FLAG}
	
TEXMAP_OBJS = ¶
	{OBJDIR}ntmap.c.o {OBJDIR}tmapflat.c.o {OBJDIR}scanline.c.o {OBJDIR}tmap_per.a.o
#	{OBJDIR}ntmap.c.o {OBJDIR}tmapflat.c.o {OBJDIR}scanline.c.o
	
All Ä {LIB}

{LIB} Ä {TEXMAP_OBJS}
	Echo "# `Date -t` ----- Building {LIB}"
	{Linker} {LibraryFlags} {OBJ_DIR}Å -o {LIB}
	Echo "# Copying files to lib directory..."
	duplicate -y {LIB} ::lib
	duplicate -y {GLOBAL_INCLUDES} ::lib
	
testg Ä testg.c.o {TEST_LIBS}
	Link -t 'APPL' -c '????' -sym on -model far -mf ¶
		testg.c.o {STD_LIBS} ¶
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
	{C} "{depDir}{default}.c" {MyCFlags} {CFlags} ¶
		-o "{targDir}{default}.c.o"		¶
		|| ( Echo "#####   ### ERROR ###   #####" )

.a.o	Ä	.a
	if "{Asm}" == "PPCAsm"
		Echo "# `Date -t` ----- Assembling {default}.a..."
		{Asm} "{depDir}{default}.a"	{MyAsmFlags}	¶
			-o "{targDir}{default}.a.o"		¶
			|| ( Echo "#####   ### ERROR ###   #####" )
	end
	
### OPUS MKMF:  Do not remove this line!  Generated dependencies follow.

ntmap.c.o Ä makefile ntmap.c ::lib:mono.h ::lib:fix.h ::lib:dtypes.h ::lib:3d.h ::lib:vecmat.h ::lib:gr.h ::lib:error.h ::lib:key.h texmap.h texmapl.h scanline.h

scanline.c.o Ä makefile scanline.c ::lib:fix.h ::lib:dtypes.h ::lib:mono.h ::lib:gr.h texmap.h ::lib:3d.h ::lib:vecmat.h texmapl.h scanline.h

tmap.c.o Ä makefile tmap.c

tmapflat.c.o Ä makefile tmapflat.c ::lib:fix.h ::lib:dtypes.h ::lib:mono.h ::lib:gr.h texmap.h ::lib:3d.h ::lib:vecmat.h texmapl.h scanline.h ::lib:error.h

tmapsky.c.o Ä makefile tmapsky.c ::lib:mono.h ::lib:fix.h ::lib:dtypes.h ::lib:3d.h ::lib:vecmat.h ::lib:gr.h ::lib:error.h texmap.h texmapl.h

tmapv.c.o Ä makefile tmapv.c ::lib:mono.h ::lib:fix.h ::lib:dtypes.h ::lib:3d.h ::lib:vecmat.h ::lib:gr.h ::lib:error.h texmap.h texmapl.h

tmapz.c.o Ä makefile tmapz.c ::lib:fix.h ::lib:dtypes.h ::lib:mono.h ::lib:gr.h texmap.h ::lib:3d.h ::lib:vecmat.h texmapl.h ::lib:error.h

