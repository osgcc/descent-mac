#
# $Source: Smoke:miner:source:mem::RCS:makefile $
# $Revision: 1.5 $
# $Author: allender $
# $Date: 1995/10/25 12:06:48 $
#
# Makefile for bios functions
#

OBJDIR = :obj:
SRCDIR = :

# What libs to make
LIB = mem.lib

# includes to copy to lib directory
GLOBAL_INCLUDES = mem.h

OBJ_DIR = :obj:

# C compiler options
CFLAGS = {SYM_FLAG}
	
LDFLAGS = �
	{SYM_FLAG}
	
MEM_OBJS = �
	{OBJDIR}mem.c.o
	
TESTMEM_OBJS = �
	{OBJDIR}test_mem.c.o
	
All � {LIB}

{LIB} � {MEM_OBJS}
	Echo "# `Date -t` ----- Building MEM library..."
	{Linker} {LibraryFlags} {OBJ_DIR}� -o {LIB}
	Echo "#  Copying files to lib directory..."
	duplicate -y {LIB} ::lib
	duplicate -y {GLOBAL_INCLUDES} ::lib

clean �
	del :obj:�
	del mem.lib
	
test_mem � {TESTMEM_OBJS} {LIB}
	Link -t APPL -c '????' -sym on -mf �
		{TESTMEM_OBJS} {LIB} �
		"{CLibraries}"CSANELib.o �
		"{CLibraries}"Math.o �
		"{CLibraries}"StdClib.o �
 		"{Libraries}"Runtime.o �
 		"{Libraries}"Interface.o �
		-o test_mem
	
# dependency for obj and source directories
"{OBJDIR}"		�	"{SRCDIR}"

.c.o	�	.c
	Echo `Date -t` ---- Compiling {default}.c
	{C} "{default}.c" {MyCFlags} {CFlags} �
		-o "{targDir}{default}.c.o"		�
		|| ( Echo "#####   ### ERROR ###   #####" )

.a.o	�	.a
	Echo "# `Date -t` ----- Assembling {default}.a..."
	Asm "{depDir}{default}.a"			�
		-o "{targDir}{default}.a.o"		�
		|| ( Echo "#####   ### ERROR ###   #####" )

### OPUS MKMF:  Do not remove this line!  Generated dependencies follow.

mem.c.o � mem.c mem.h mono.h

test_mem.c.o � test_mem.c
