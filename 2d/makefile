#
# $Source: Smoke:miner:source:2d::RCS:makefile $
# $Revision: 1.9 $
# $Author: allender $
# $Date: 1995/09/14 16:39:56 $
#
# Makefile for graphics functions
#

LIBDIR = ::lib:
OBJDIR = :obj:
SRCDIR = :

# What libs to make
LIB = gr.lib

# includes to copy to lib directory
GLOBAL_INCLUDES = gr.h palette.h grdef.h rle.h pcx.h effect2d.h ibitblt.h

# test file libraries needed
TEST_LIBS = {LIBDIR}gr.lib {LIBDIR}mem.lib {LIBDIR}io.lib {LIBDIR}cfile.lib �
	{LIBDIR}misc.lib {LIBDIR}macsys.lib {LIBDIR}fix.lib
	
# standard libs to link anything with
STD_LIBS = �
	"{CLibraries}"CSANELib.o �
	"{CLibraries}"Math.o �
	"{CLibraries}"StdClib.o �
	"{Libraries}"Runtime.o �
	"{Libraries}"Interface.o

# resource files to be used in test file
TEST_RESOURCES = {LIBDIR}bios.r {LIBDIR}macsys.r

OBJ_DIR = :obj:

# C compiler options
CFLAGS = {SYM_FLAG}
	
LDFLAGS = �
	{SYM_FLAG}

GR_OBJS = �
	{OBJDIR}palette.c.o {OBJDIR}gr.c.o {OBJDIR}canvas.c.o �
	{OBJDIR}pixel.c.o {OBJDIR}rect.c.o {OBJDIR}scanline.c.o {OBJDIR}line.c.o �
	{OBJDIR}box.c.o {OBJDIR}poly.c.o {OBJDIR}disc.c.o {OBJDIR}gpixel.c.o �
	{OBJDIR}font.c.o {OBJDIR}bitmap.c.o {OBJDIR}bitblt.c.o {OBJDIR}pcx.c.o �
	{OBJDIR}rle.c.o {OBJDIR}scale.c.o {OBJDIR}blit.a.o {OBJDIR}ibitblt.c.o {OBJDIR}blit68k.a.o
	
All � {LIB}

update	�
	for Header in �.h �.c
		if `Exists -f "{RCSDIR}{Header}"`
			if `Newer "{RCSDIR}{Header}" "{Header}"`
				if `Exists -w "{Header}"`
					echo "{header} is writeable...aboring co"
					Exit 1
				end
				co -q {header}
			end
		end
	end

{LIB} � {GR_OBJS}
	Echo "# `Date -t` ----- Building GR library..."
	{Linker} {LibraryFlags} {OBJ_DIR}� -o {LIB}
	Echo "# Copying files to lib directory..."
	duplicate -y {LIB} ::lib
	duplicate -y {GLOBAL_INCLUDES} ::lib
	
testc � testc.c.o {TEST_LIBS}
	Link -t 'APPL' -c '????' -sym on -model far -mf �
		testc.c.o {STD_LIBS} �
		{TEST_LIBS} �
		-o {Targ}
	Rez {TEST_RESOURCES} -rd -append -o {Targ}

clean �
	del -i :obj:�
	del -i gr.lib

# dependency for obj and source directories
"{OBJDIR}"		�	"{SRCDIR}"

.c.o	�	.c
	Echo `Date -t` ---- Compiling {default}.c
	{C} "{default}.c" {MyCFlags} {CFlags} �
		-o "{targDir}{default}.c.o"		�
		|| ( Echo "#####   ### ERROR ###   #####" )

:obj:blit.a.o	�	blit.a
	if "{Asm}" == "PPCAsm"
		Echo "# `Date -t` ----- Assembling blit.a..."
		rm -i :obj:blit.a.o
		{Asm} "blit.a"		{AFLAGS}	�
			-o ":obj:blit.a.o"		�
			|| ( Echo "#####   ### ERROR ###   #####" )
	end

:obj:blit68k.a.o	�	blit68k.a
	if "{Asm}" == "Asm"
		Echo "# `Date -t` ----- Assembling blit68k.a..."
		rm -i :obj:blit68k.a.o
		{Asm} "blit68k.a"		{AFLAGS}	�
			-o ":obj:blit68k.a.o"		�
			|| ( Echo "#####   ### ERROR ###   #####" )
	end

### OPUS MKMF:  Do not remove this line!  Generated dependencies follow.

bitblt.obj � fix.h gr.h grdef.h mem.h mono.h rle.h types.h

bitmap.obj � dpmi.h fix.h gr.h grdef.h malloc.h mem.h stdio.h stdlib.h \
	 types.h

box.obj � fix.h gr.h grdef.h mem.h types.h

canvas.obj � fix.h gr.h grdef.h malloc.h mem.h stdio.h stdlib.h types.h

circle.obj � fix.h gr.h grdef.h mem.h types.h

disc.obj � fix.h gr.h grdef.h mem.h types.h

effects.obj � effect2d.h fix.h gr.h grdef.h mem.h stdio.h stdlib.h types.h

font.obj � cfile.h conio.h error.h fcntl.h fix.h gr.h grdef.h io.h mem.h \
	 mono.h stat.h stdarg.h stdio.h stdlib.h types.h

gpixel.obj � fix.h gr.h grdef.h mem.h types.h

gr.obj �	 conio.h dos.h dpmi.h error.h fix.h gr.h grdef.h i86.h malloc.h \
	 mem.h mono.h palette.h stdio.h stdlib.h string.h types.h

ibitblt.obj � conio.h dos.h error.h fix.h gr.h i86.h ibitblt.h mem.h stdio.h \
	 stdlib.h types.h

lbitblt.obj � fix.inc gr.inc psmacros.inc types.inc

line.obj � clip.h fix.h gr.h grdef.h mem.h stdlib.h types.h

linear.obj � psmacros.inc

mspeed.obj � conio.h fix.h gr.h grdef.h math.h stdio.h stdlib.h types.h

paging.obj � psmacros.inc types.inc

palette.obj � cfile.h conio.h error.h fix.h gr.h grdef.h io.h key.h mem.h \
	 mono.h stat.h stdio.h stdlib.h types.h

pflow.obj � psmacros.inc types.inc

pixel.obj � fix.h gr.h grdef.h mem.h types.h

poly.obj � fix.h gr.h grdef.h mem.h types.h

rect.obj � fix.h gr.h grdef.h mem.h types.h

rle.obj � dpmi.h error.h fix.h gr.h grdef.h key.h malloc.h mem.h mono.h \
	 stdio.h stdlib.h string.h types.h

roller.obj � 3d.h conio.h error.h fix.h gr.h limits.h math.h mono.h stdio.h \
	 stdlib.h types.h vecmat.h

scale.obj � conio.h error.h fix.h gr.h limits.h math.h mono.h rle.h stdio.h \
	 stdlib.h types.h

scalea.obj � psmacros.inc types.inc

scanline.obj � fix.h gr.h grdef.h mem.h types.h

selector.obj � psmacros.inc types.inc

testg.obj � conio.h fix.h gr.h grdef.h key.h math.h mono.h palette.h stdio.h \
	 stdlib.h types.h
