#
# $Source: Smoke:miner:source:macsys::RCS:makefile $
# $Revision: 1.11 $
# $Author: allender $
# $Date: 1995/10/25 13:56:11 $
#
# Makefile for graphics functions
#

LIBDIR = ::lib:
OBJDIR = :obj:
SRCDIR = :

# What libs to make
LIB = macsys.lib

# includes to copy to lib directory
GLOBAL_INCLUDES = macsys.h

# test file libraries needed
TEST_LIBS = {LIBDIR}gr.lib {LIBDIR}mem.lib {LIBDIR}io.lib {LIBDIR}cfile.lib �
	{LIBDIR}misc.lib

# standard libs to link anything with
STD_LIBS = �
	"{CLibraries}"CSANELib.o �
	"{CLibraries}"Math.o �
	"{CLibraries}"StdClib.o �
	"{Libraries}"Runtime.o �
	"{Libraries}"Interface.o

# resource files to be used in test file
TEST_RESOURCES = {LIBDIR}bios.r

OBJ_DIR = :obj:

# C compiler options
CFLAGS = {SYM_FLAG}
	
LDFLAGS = �
	{SYM_FLAG}
	
MACSYS_OBJS = �
	{OBJDIR}macinit.c.o {OBJDIR}mouse.c.o {OBJDIR}menubar.c.o  {OBJDIR}getscrn.c.o �
	{OBJDIR}macwin.c.o {OBJDIR}mevent.c.o {OBJDIR}prefs.c.o {OBJDIR}scsaver.c.o
	
All � {LIB}

{LIB} � {MACSYS_OBJS}
	Echo "# `Date -t` ----- Building MACSYS library..."
	{Linker} {LibraryFlags} {OBJ_DIR}� -o {LIB}
	Echo "# Copying files to lib directory..."
	duplicate -y {LIB} ::lib
	duplicate -y {GLOBAL_INCLUDES} ::lib
	
clean �
	del -i :obj:�
	del -i macsys.lib

# dependency for obj and source directories
"{OBJDIR}"		�	"{SRCDIR}"

.c.o	�	.c
	Echo `Date -t` ---- Compiling {default}.c
	{C} "{default}.c" {MyCFlags} {CFlags} �
		-o "{targDir}{default}.c.o"		�
		|| ( Echo "#####   ### ERROR ###   #####" )

.a.o	�	.a
	Echo "# `Date -t` ----- Assembling {default}.a..."
	if "{Asm}" == "PPCAsm"
		rm -i "{targDir}{default}.a.o"
		{Asm} "{default}.a"	-o "{targDir}{default}.a.o"	�
			|| ( Echo "#####   ### ERROR ###   #####" )
#	else
#		rm -i :obj:fix.a.o
#		{Asm} fix.a	-o :obj:fix.a.o		�
#			|| ( Echo "#####   ### ERROR ###   #####" )
	end

### OPUS MKMF:  Do not remove this line!  Generated dependencies follow.
:obj:backgrnd.c.o � backgrnd.c ::lib:dtypes.h ::lib:resource.h

:obj:scrncpy.c.o � scrncpy.c macsys.h

:obj:macinit.c.o � macinit.c ::lib:dtypes.h macsys.h

:obj:macwin.c.o � macwin.c ::lib:dtypes.h macsys.h ::lib:gr.h ::lib:fix.h

:obj:menubar.c.o � menubar.c ::lib:dtypes.h

:obj:mevent.c.o � mevent.c

:obj:mouse.c.o � mouse.c ::lib:dtypes.h
