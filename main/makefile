#
# $Source: QUANTUM 500 HD:miner:source:2d::RCS:makefile $
# $Revision: 1.1 $
# $Author: allender $
# $Date: 1995/03/09 09:25:59 $
#
# Makefile for graphics functions
#

LIBDIR = ::lib:
RESDIR = ::resource:
OBJDIR = :obj:
SRCDIR = :
RCSDIR = :RCS:
HALEDIR = '::halestorm:'

# test file libraries needed
DESCENT_LIBS = {LIBDIR}gr.lib {LIBDIR}mem.lib {LIBDIR}io.lib {LIBDIR}cfile.lib ¶
	{LIBDIR}misc.lib {LIBDIR}macsys.lib {LIBDIR}vecmat.lib {LIBDIR}3d.lib {LIBDIR}fix.lib ¶
	{LIBDIR}texmap.lib {LIBDIR}iff.lib {LIBDIR}ipx.lib {LIBDIR}appltalk.lib

DESCENT_LIBS_OBJS = ::2d:obj:Å.o ::mem:obj:Å.o ::bios:obj:Å.o ::cfile:obj:Å.o ¶
	::misc:obj:Å.o ::macsys:obj:Å.o ::vecmat:obj:Å.o ::3d:obj:Å.o ::fix:obj:Å.o ¶
	::texmap:obj:Å.o ::iff:obj:Å.o ::ipx:obj:Å.o ::appltalk:obj:Å.o

DESCENT_LIBS_OBJS_68K = ::2d:obj:Å.o ::mem:obj:Å.o ::bios:obj:Å.o ::cfile:obj:Å.o ¶
	::misc:obj:Å.o ::macsys:obj:Å.o ::vecmat.68k:obj:Å.o ::3d:obj:Å.o ::fix.68k:obj:Å.o ¶
	::texmap.68k:obj:Å.o ::iff:obj:Å.o ::ipx:obj:Å.o ::appltalk:obj:Å.o

# standard libs to link anything with
PPC_STD_LIBS = ¶
		"{MWPPCLibraries}MWCRuntime.Lib" ¶
		"{MWPPCLibraries}InterfaceLib" ¶
		"{MWPPCLibraries}ANSI C.PPC.Lib" ¶
		"{MWPPCLibraries}MathLib" ¶
		{HALEDIR}'C_PPCSoundMusicSystem(rev3).lib'
#		'::halestorm:MWPPCSoundMusicSystem(rev3).lib'
#		"{MWPPCLibraries}SIOUX.PPC.Lib"
		
PPC_MPW_STD_LIBS = ¶
	"{PPCLibraries}"InterfaceLib.xcoff	¶
	"{PPCLibraries}"StdCLib.xcoff		¶
	"{PPCLibraries}"MathLib.xcoff		¶
	"{PPCLibraries}"PPCCRuntime.o		¶
	"{PPCLibraries}"StdCRuntime.o		¶
#	"::lib:SpeechLib.xcoff" ¶
	{HALEDIR}'C_PPCSoundMusicSystem(r3).xcoff'

68K_STD_LIBS = ¶
		"{MW68kLibraries}MacOS.Lib" ¶
		"{MW68kLibraries}ANSI (N/4i) C.68k.Lib" ¶
		"{MW68KLibraries}MathLib68K (4i).Lib"
#		"{MW68kLibraries}SIOUX.68k.Lib" ¶
#		"::lib:68Ksnd.lib"


# resource files to be used in test file
PPC_RESOURCES = {RESDIR}descent.r {RESDIR}cfrg.r {RESDIR}getscrn.r {RESDIR}sounds.r {LIBDIR}listener.r {HALEDIR}halemain.r
PPC_RESOURCES_SHARE = {RESDIR}descent.r {RESDIR}cfrg.r {RESDIR}getscrn.r {RESDIR}sndshare.r {LIBDIR}listener.r {HALEDIR}halemain.r {RESDIR}music.r
#68K_RESOURCES = {RESDIR}descent.r {RESDIR}sounds.r {RESDIR}music.r {RESDIR}halemain.r {RESDIR}getscrn.r
68K_RESOURCES = {RESDIR}descent.r {RESDIR}sounds.r {RESDIR}getscrn.r {LIBDIR}listener.r

OBJ_DIR = :obj:

# C compiler options
CFLAGS = {SYM_FLAG} -d NETWORK
	
LDFLAGS = ¶
	{SYM_FLAG}
	
DESCENT_OBJS = ¶
{OBJDIR}inferno.c.o	{OBJDIR}AI.c.o {OBJDIR}GAME.c.o {OBJDIR}MISSION.c.o {OBJDIR}macnet.c.o ¶
{OBJDIR}robot.c.o {OBJDIR}AIPATH.c.o {OBJDIR}GAMEFONT.c.o {OBJDIR}MODEM.c.o       ¶
{OBJDIR}ARGS.c.o {OBJDIR}GAMEMINE.c.o {OBJDIR}MORPH.c.o {OBJDIR}AUTOMAP.c.o ¶
{OBJDIR}GAMESAVE.c.o {OBJDIR}MULTI.c.o {OBJDIR}SCORES.c.o {OBJDIR}BM.c.o ¶
{OBJDIR}GAMESEG.c.o {OBJDIR}MULTIBOT.c.o {OBJDIR}BMREAD.c.o {OBJDIR}redbook.c.o ¶
{OBJDIR}GAMESEQ.c.o {OBJDIR}NETMISC.c.o {OBJDIR}SLEW.c.o {OBJDIR}GAUGES.c.o ¶
{OBJDIR}NETWORK.c.o {OBJDIR}SONGS.c.o {OBJDIR}CNTRLCEN.c.o {OBJDIR}HASH.c.o ¶
{OBJDIR}NEWDEMO.c.o {OBJDIR}STATE.c.o {OBJDIR}COLLIDE.c.o {OBJDIR}HOSTAGE.c.o ¶
{OBJDIR}NEWMENU.c.o {OBJDIR}SWITCH.c.o {OBJDIR}CONFIG.c.o {OBJDIR}OBJECT.c.o ¶
{OBJDIR}TERRAIN.c.o {OBJDIR}CONTROLS.c.o {OBJDIR}HUD.c.o {OBJDIR}CREDITS.c.o ¶
{OBJDIR}TEXMERGE.c.o {OBJDIR}PAGING.c.o {OBJDIR}TEXT.c.o {OBJDIR}JOYDEFS.c.o ¶
{OBJDIR}TITLES.c.o {OBJDIR}DIGI.c.o {OBJDIR}KCONFIG.c.o {OBJDIR}PHYSICS.c.o ¶
{OBJDIR}DUMPMINE.c.o {OBJDIR}KMATRIX.c.o {OBJDIR}PIGGY.c.o {OBJDIR}VCLIP.c.o ¶
{OBJDIR}EFFECTS.c.o {OBJDIR}LASER.c.o {OBJDIR}PLAYSAVE.c.o {OBJDIR}ENDLEVEL.c.o ¶
{OBJDIR}LIGHTING.c.o {OBJDIR}POLYOBJ.c.o {OBJDIR}FIREBALL.c.o {OBJDIR}POWERUP.c.o ¶
{OBJDIR}WALL.c.o {OBJDIR}FUELCEN.c.o {OBJDIR}MENU.c.o {OBJDIR}RENDER.c.o {OBJDIR}WEAPON.c.o ¶
{OBJDIR}FVI.c.o {OBJDIR}MGLOBAL.c.o     

	
All Ä :::game:Descent
	echo "{Targ} done."

update	Ä
	for Header in Å.h Å.c
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

:::game:Descent Ä {DESCENT_OBJS} {DESCENT_LIBS} {PPC_RESOURCES} {68K_RESOURCES}
	del -i {Targ} {Targ}.SYM {Targ}.map
	if {Linker} == "MWLinkPPC"
		{Linker} -t 'APPL' -c 'DCNT' {LinkerFlags} ¶
			"{MPW}"MotoTools:libmoto ¶
			{PPC_STD_LIBS} ¶
			{PROFILE_LIBS} ¶
			{DESCENT_OBJS} ¶
			{DESCENT_LIBS_OBJS} ¶
			-o {Targ} -map descent.map
		ls > x
		rm x
		Rez {PPC_RESOURCES} -m -rd -append -o {Targ}
	else if {Linker} == "PPCLink"
		PPCLink -t 'APPL' -c 'DCNT' -w {LinkerFlags} ¶
#			"{MPW}"MotoTools:libmoto ¶
			{PPC_MPW_STD_LIBS} ¶
			{DESCENT_OBJS} ¶
			{DESCENT_LIBS_OBJS} ¶
			-libRename InterfaceLib.xcoff=InterfaceLib -libRename StdCLib.xcoff=StdCLib	-libRename MathLib.xcoff=MathLib ¶
			-o {Targ} -map descent.map
		Rez {PPC_RESOURCES} -m -rd -append -o {Targ}
	else
		{Linker} -t 'APPL' -c '????' -model far -intsize 4 -single {SYM_FLAG} ¶
			{68K_STD_LIBS} ¶
			{DESCENT_OBJS} ¶
			{DESCENT_LIBS_OBJS_68K} ¶
			-o {Targ} -map descent.map
		Rez {68K_RESOURCES} -m -rd -append -o {Targ}
	end	
	setfile -a B :::game:Descent
	setfile -t 'PGGY' -c 'DCNT' :::game:Data:descent.pig
	setfile -t 'HOG ' -c 'DCNT' :::game:Data:descent.hog

:::shareware:Descent Ä {DESCENT_OBJS} {DESCENT_LIBS} {PPC_RESOURCES_SHARE}
	del -i {Targ} {Targ}.xSYM {Targ}.map
	if {Linker} == "MWLinkPPC"
		{Linker} -t 'APPL' -c 'DCNT' {LinkerFlags} ¶
			"{MPW}"MotoTools:libmoto ¶
			{PPC_STD_LIBS} ¶
			{PROFILE_LIBS} ¶
			{DESCENT_OBJS} ¶
			{DESCENT_LIBS_OBJS} ¶
			-o {Targ} -map descent.map
		ls > x
		rm x
		Rez {PPC_RESOURCES_SHARE} -m -rd -append -o {Targ}
	else if {Linker} == "PPCLink"
		PPCLink -t 'APPL' -c 'DCNT' -w {LinkerFlags} ¶
#			"{MPW}"MotoTools:libmoto ¶
			{PPC_MPW_STD_LIBS} ¶
			{DESCENT_OBJS} ¶
			{DESCENT_LIBS_OBJS} ¶
			-libRename InterfaceLib.xcoff=InterfaceLib -libRename StdCLib.xcoff=StdCLib	-libRename MathLib.xcoff=MathLib ¶
			-o {Targ} -map descent.map
		Rez {PPC_RESOURCES} -m -rd -append -o {Targ}
	else
		{Linker} -t 'APPL' -c '????' -model far -intsize 4 -single {SYM_FLAG} ¶
			{68K_STD_LIBS} ¶
			{DESCENT_OBJS} ¶
			{DESCENT_LIBS_OBJS_68K} ¶
			-o {Targ} -map descent.map
		Rez {68K_RESOURCES} -m -rd -append -o {Targ}
	end	
	setfile -a B :::shareware:Descent
	setfile -t 'PGGY' -c 'DCNT' :::shareware:Data:descent.pig
	setfile -t 'HOG ' -c 'DCNT' :::shareware:Data:descent.hog

clean Ä
	del -i :obj:Å
	del -i :::game:Descent :::game:Descent.xSYM

clean_shareware Ä
	del -i :obj:Å
	del -i :::shareware:Descent :::shareware:Descent.xSYM

# dependency for obj and source directories
"{SRCDIR}".c	Ä	"{RCSDIR}".c
	if ( UPDATE = 1 )
		echo "update"
	else
		echo "you should update"
	end
	
"{OBJDIR}"		Ä	"{SRCDIR}"

.c.o	Ä	.c
	Echo `Date -t` ---- Compiling {default}.c
	rm -i {targDir}{default}.c.o
	{C} "{default}.c" {MyCFlags} {CFlags} ¶
		-o "{targDir}{default}.c.o"		¶
		|| ( Echo "#####   ### ERROR ###   #####" )

.a.o	Ä	.a
	Echo "# `Date -t` ----- Assembling {default}.a..."
	Asm "{default}.a"			¶
		-o "{targDir}{default}.a.o"		¶
		|| ( Echo "#####   ### ERROR ###   #####" )

### OPUS MKMF:  Do not remove this line!  Generated dependencies follow.
{OBJDIR}AI.C.o Ä AI.C inferno.h game.h ::lib:vecmat.h ::lib:fix.h ::lib:dtypes.h object.h ¶
	segment.h gameseg.h aistruct.h ::lib:gr.h piggy.h digi.h sounds.h ::lib:mono.h ¶
	::lib:3d.h render.h ::lib:error.h ai.h laser.h fvi.h polyobj.h robot.h bm.h ¶
	weapon.h physics.h collide.h fuelcen.h switch.h player.h wall.h vclip.h ¶
	fireball.h morph.h effects.h cntrlcen.h multibot.h multi.h gameseq.h mission.h ¶
	network.h ::lib:key.h powerup.h gauges.h text.h ::lib:mem.h
{OBJDIR}AIPATH.C.o Ä AIPATH.C inferno.h ::lib:mono.h ::lib:3d.h ::lib:fix.h ::lib:dtypes.h ¶
	::lib:vecmat.h ::lib:gr.h object.h segment.h gameseg.h aistruct.h piggy.h digi.h ¶
	sounds.h ::lib:error.h ai.h robot.h game.h fvi.h physics.h wall.h player.h ¶
	weapon.h fireball.h
{OBJDIR}ARGS.C.o Ä ARGS.C
{OBJDIR}automap.c.o Ä automap.c ::lib:error.h ::lib:3d.h ::lib:fix.h ::lib:dtypes.h ¶
	::lib:vecmat.h ::lib:gr.h inferno.h ::lib:mem.h render.h object.h segment.h ¶
	gameseg.h aistruct.h piggy.h digi.h sounds.h vclip.h game.h ::lib:mono.h polyobj.h ¶
	robot.h player.h weapon.h bm.h ::lib:key.h screens.h textures.h segpoint.h ¶
	::lib:iff.h ::lib:pcx.h ::lib:palette.h wall.h hostage.h fuelcen.h switch.h ¶
	gameseq.h mission.h gamefont.h network.h multi.h kconfig.h endlevel.h text.h ¶
	gauges.h powerup.h
{OBJDIR}BM.C.o Ä BM.C ::lib:dtypes.h inferno.h ::lib:gr.h ::lib:fix.h ::lib:3d.h ::lib:vecmat.h ¶
	bm.h piggy.h digi.h sounds.h ::lib:mem.h ::lib:mono.h ::lib:error.h object.h segment.h ¶
	gameseg.h aistruct.h vclip.h effects.h polyobj.h robot.h game.h wall.h textures.h ¶
	multi.h gameseq.h player.h weapon.h mission.h ::lib:iff.h ::lib:cfile.h hostage.h ¶
	powerup.h gauges.h fuelcen.h switch.h endlevel.h cntrlcen.h ::lib:byteswap.h
{OBJDIR}BMREAD.C.o Ä BMREAD.C settings.h inferno.h ::lib:gr.h ::lib:dtypes.h ::lib:fix.h bm.h ¶
	piggy.h digi.h ::lib:vecmat.h sounds.h ::lib:mem.h ::lib:mono.h ::lib:error.h object.h ¶
	segment.h gameseg.h aistruct.h vclip.h effects.h polyobj.h ::lib:3d.h robot.h game.h ¶
	wall.h textures.h multi.h gameseq.h player.h weapon.h mission.h ::lib:iff.h ¶
	::lib:cfile.h hostage.h powerup.h laser.h gauges.h fuelcen.h switch.h endlevel.h ¶
	cntrlcen.h compbit.h args.h
{OBJDIR}CNTRLCEN.C.o Ä CNTRLCEN.C ::lib:error.h ::lib:mono.h inferno.h cntrlcen.h ::lib:vecmat.h ¶
	::lib:fix.h ::lib:dtypes.h object.h segment.h gameseg.h aistruct.h ::lib:gr.h ¶
	piggy.h digi.h sounds.h game.h laser.h gameseq.h player.h weapon.h mission.h ai.h ¶
	multi.h fuelcen.h switch.h wall.h robot.h
{OBJDIR}COLLIDE.C.o Ä COLLIDE.C ::lib:rle.h ::lib:gr.h ::lib:dtypes.h ::lib:fix.h inferno.h game.h ¶
	::lib:vecmat.h object.h segment.h gameseg.h aistruct.h piggy.h digi.h sounds.h bm.h ¶
	::lib:mono.h ::lib:3d.h ::lib:texmap.h laser.h ::lib:key.h physics.h fvi.h slew.h ¶
	render.h wall.h vclip.h polyobj.h robot.h fireball.h ::lib:error.h ai.h hostage.h ¶
	fuelcen.h switch.h weapon.h player.h gauges.h powerup.h network.h gameseq.h mission.h ¶
	multi.h newmenu.h scores.h effects.h textures.h cntrlcen.h newdemo.h endlevel.h ¶
	multibot.h text.h collide.h
{OBJDIR}CONFIG.C.o Ä CONFIG.C ::lib:dtypes.h game.h ::lib:vecmat.h ::lib:fix.h object.h segment.h ¶
	gameseg.h aistruct.h inferno.h ::lib:gr.h piggy.h digi.h sounds.h kconfig.h ¶
	::lib:palette.h ::lib:joy.h args.h player.h weapon.h mission.h
{OBJDIR}CONTROLS.C.o Ä CONTROLS.C ::lib:mono.h ::lib:key.h ::lib:fix.h ::lib:dtypes.h ::lib:joy.h ¶
	::lib:error.h inferno.h game.h ::lib:vecmat.h object.h segment.h gameseg.h aistruct.h ¶
	::lib:gr.h piggy.h digi.h sounds.h player.h weapon.h controls.h joydefs.h victor.h ¶
	render.h ::lib:3d.h args.h ::lib:palette.h ::lib:mouse.h kconfig.h
{OBJDIR}CREDITS.C.o Ä CREDITS.C ::lib:error.h ::lib:dtypes.h ::lib:gr.h ::lib:fix.h ::lib:mono.h ¶
	::lib:key.h ::lib:palette.h game.h ::lib:vecmat.h object.h segment.h gameseg.h ¶
	aistruct.h inferno.h piggy.h digi.h sounds.h newmenu.h gamefont.h network.h gameseq.h ¶
	player.h weapon.h mission.h multi.h ::lib:iff.h ::lib:pcx.h ::lib:mem.h ::lib:mouse.h ¶
	::lib:joy.h screens.h ::lib:cfile.h compbit.h vfx.h songs.h ::lib:macsys.h
{OBJDIR}DIGI.C.o Ä DIGI.C ::lib:fix.h ::lib:dtypes.h object.h ::lib:vecmat.h segment.h gameseg.h ¶
	aistruct.h inferno.h ::lib:gr.h piggy.h digi.h sounds.h ::lib:mono.h ::lib:joy.h args.h ¶
	::lib:key.h newdemo.h game.h ::lib:error.h wall.h ::lib:cfile.h text.h kconfig.h
{OBJDIR}DUMPMINE.C.o Ä DUMPMINE.C ::lib:mono.h ::lib:key.h ::lib:fix.h ::lib:dtypes.h ::lib:gr.h ¶
	::lib:palette.h inferno.h ::lib:error.h object.h ::lib:vecmat.h segment.h gameseg.h ¶
	aistruct.h piggy.h digi.h sounds.h wall.h gamemine.h robot.h game.h player.h weapon.h ¶
	newmenu.h textures.h bm.h menu.h switch.h fuelcen.h powerup.h vclip.h hostage.h ¶
	gameseq.h mission.h polyobj.h ::lib:3d.h gamesave.h
{OBJDIR}EFFECTS.C.o Ä EFFECTS.C ::lib:gr.h ::lib:dtypes.h ::lib:fix.h inferno.h game.h ¶
	::lib:vecmat.h object.h segment.h gameseg.h aistruct.h piggy.h digi.h sounds.h ¶
	vclip.h effects.h bm.h ::lib:mono.h ::lib:mem.h textures.h fuelcen.h switch.h ¶
	::lib:error.h
{OBJDIR}ENDLEVEL.C.o Ä ENDLEVEL.C ::lib:3d.h ::lib:fix.h ::lib:dtypes.h ::lib:vecmat.h ::lib:gr.h ¶
	::lib:error.h ::lib:palette.h ::lib:iff.h ::lib:mono.h ::lib:texmap.h fvi.h segment.h ¶
	object.h gameseg.h aistruct.h inferno.h piggy.h digi.h sounds.h ::lib:mem.h endlevel.h ¶
	game.h gauges.h wall.h terrain.h polyobj.h robot.h bm.h gameseq.h player.h weapon.h ¶
	mission.h newdemo.h multi.h vclip.h fireball.h network.h text.h ::lib:cfile.h ¶
	compbit.h songs.h ::lib:key.h ::lib:joy.h
{OBJDIR}FIREBALL.C.o Ä FIREBALL.C ::lib:error.h ::lib:3d.h ::lib:fix.h ::lib:dtypes.h ::lib:vecmat.h ¶
	::lib:gr.h inferno.h object.h segment.h gameseg.h aistruct.h piggy.h digi.h sounds.h ¶
	vclip.h game.h ::lib:mono.h polyobj.h robot.h player.h weapon.h gauges.h powerup.h ¶
	bm.h ai.h fireball.h collide.h newmenu.h network.h gameseq.h mission.h multi.h ¶
	physics.h fvi.h scores.h laser.h wall.h endlevel.h fuelcen.h switch.h
{OBJDIR}FUELCEN.C.o Ä FUELCEN.C fuelcen.h segment.h ::lib:vecmat.h ::lib:fix.h ::lib:dtypes.h ¶
	object.h gameseg.h aistruct.h inferno.h ::lib:gr.h piggy.h digi.h sounds.h switch.h ¶
	game.h ::lib:error.h ::lib:mono.h gauges.h vclip.h fireball.h robot.h wall.h morph.h ¶
	::lib:3d.h bm.h polyobj.h ai.h gamemine.h gamesave.h player.h weapon.h collide.h laser.h ¶
	network.h gameseq.h mission.h multi.h multibot.h
{OBJDIR}FVI.C.o Ä FVI.C ::lib:error.h ::lib:mono.h inferno.h fvi.h ::lib:vecmat.h ::lib:fix.h ¶
	::lib:dtypes.h segment.h object.h gameseg.h aistruct.h ::lib:gr.h piggy.h digi.h ¶
	sounds.h wall.h laser.h ::lib:rle.h robot.h game.h player.h weapon.h textures.h bm.h ¶
	texmerge.h
{OBJDIR}GAME.C.o Ä GAME.C inferno.h game.h ::lib:vecmat.h ::lib:fix.h ::lib:dtypes.h object.h ¶
	segment.h gameseg.h aistruct.h ::lib:gr.h piggy.h digi.h sounds.h ::lib:key.h physics.h ¶
	fvi.h ::lib:error.h ::lib:joy.h ::lib:mono.h ::lib:iff.h ::lib:pcx.h render.h ¶
	::lib:3d.h laser.h screens.h textures.h bm.h slew.h gauges.h ::lib:texmap.h effects.h ¶
	vclip.h ::lib:effect2d.h menu.h wall.h ai.h hostage.h fuelcen.h switch.h gamesave.h ¶
	scores.h ::lib:mem.h ::lib:palette.h morph.h lighting.h newdemo.h titles.h collide.h ¶
	weapon.h args.h gameseq.h player.h mission.h automap.h text.h powerup.h fireball.h ¶
	controls.h newmenu.h network.h multi.h gamefont.h endlevel.h joydefs.h kconfig.h ¶
	::lib:mouse.h coindev.h desc_id.h cntrlcen.h state.h multibot.h arcade.h victor.h vfx.h ::lib:macsys.h
{OBJDIR}GAMEFONT.C.o Ä GAMEFONT.C ::lib:gr.h ::lib:dtypes.h ::lib:fix.h gamefont.h
{OBJDIR}GAMEMINE.C.o Ä GAMEMINE.C ::lib:mono.h inferno.h segment.h ::lib:vecmat.h ::lib:fix.h ¶
	::lib:dtypes.h textures.h bm.h ::lib:gr.h piggy.h digi.h sounds.h wall.h object.h ¶
	gameseg.h aistruct.h gamemine.h ::lib:error.h switch.h game.h newmenu.h ::lib:cfile.h ¶
	fuelcen.h hash.h ::lib:key.h ::lib:byteswap.h
{OBJDIR}gamesave.c.o Ä gamesave.c ::lib:mono.h ::lib:key.h ::lib:fix.h ::lib:dtypes.h ::lib:gr.h ¶
	::lib:palette.h newmenu.h inferno.h ::lib:error.h object.h ::lib:vecmat.h segment.h ¶
	gameseg.h aistruct.h piggy.h digi.h sounds.h game.h screens.h wall.h gamemine.h robot.h ¶
	::lib:cfile.h bm.h menu.h switch.h fuelcen.h powerup.h vclip.h hostage.h weapon.h ¶
	newdemo.h gameseq.h player.h mission.h automap.h polyobj.h ::lib:3d.h text.h gamefont.h ¶
	gamesave.h
{OBJDIR}GAMESEG.C.o Ä GAMESEG.C inferno.h game.h ::lib:vecmat.h ::lib:fix.h ::lib:dtypes.h object.h ¶
	segment.h gameseg.h aistruct.h ::lib:gr.h piggy.h digi.h sounds.h ::lib:error.h ¶
	::lib:mono.h wall.h fuelcen.h switch.h
{OBJDIR}GAMESEQ.C.o Ä GAMESEQ.C inferno.h game.h ::lib:vecmat.h ::lib:fix.h ::lib:dtypes.h object.h ¶
	segment.h gameseg.h aistruct.h ::lib:gr.h piggy.h digi.h sounds.h ::lib:key.h physics.h ¶
	fvi.h ::lib:error.h ::lib:joy.h ::lib:mono.h ::lib:iff.h ::lib:pcx.h render.h ::lib:3d.h ¶
	laser.h screens.h textures.h bm.h slew.h gauges.h ::lib:texmap.h effects.h vclip.h ¶
	::lib:effect2d.h menu.h wall.h ai.h hostage.h fuelcen.h switch.h gamesave.h scores.h ¶
	::lib:mem.h ::lib:palette.h morph.h lighting.h newdemo.h titles.h collide.h weapon.h ¶
	args.h gameseq.h player.h mission.h gamefont.h newmenu.h endlevel.h network.h multi.h ¶
	arcade.h playsave.h fireball.h kconfig.h config.h robot.h automap.h cntrlcen.h ¶
	powerup.h modem.h text.h ::lib:cfile.h texmerge.h paging.h State.h songs.h netmisc.h
{OBJDIR}GAUGES.C.o Ä GAUGES.C inferno.h game.h ::lib:vecmat.h ::lib:fix.h ::lib:dtypes.h object.h ¶
	segment.h gameseg.h aistruct.h ::lib:gr.h piggy.h digi.h sounds.h screens.h gauges.h ¶
	physics.h fvi.h ::lib:error.h menu.h ::lib:mono.h collide.h newdemo.h player.h weapon.h ¶
	gamefont.h hostage.h vclip.h bm.h text.h powerup.h multi.h gameseq.h mission.h network.h ¶
	endlevel.h wall.h render.h ::lib:3d.h
{OBJDIR}HASH.C.o Ä HASH.C ::lib:error.h ::lib:mono.h hash.h ::lib:key.h ::lib:fix.h ::lib:dtypes.h ¶
	::lib:mem.h
{OBJDIR}HOSTAGE.C.o Ä HOSTAGE.C ::lib:error.h ::lib:3d.h ::lib:fix.h ::lib:dtypes.h ::lib:vecmat.h ¶
	::lib:gr.h ::lib:mono.h inferno.h object.h segment.h gameseg.h aistruct.h piggy.h ¶
	digi.h sounds.h game.h player.h weapon.h fireball.h gauges.h hostage.h vclip.h ¶
	lighting.h newdemo.h text.h
{OBJDIR}HUD.C.o Ä HUD.C inferno.h game.h ::lib:vecmat.h ::lib:fix.h ::lib:dtypes.h object.h ¶
	segment.h gameseg.h aistruct.h ::lib:gr.h piggy.h digi.h sounds.h screens.h gauges.h ¶
	physics.h fvi.h ::lib:error.h menu.h ::lib:mono.h collide.h newdemo.h player.h weapon.h ¶
	gamefont.h wall.h arcade.h text.h
{OBJDIR}INFERNO.C.o Ä INFERNO.C ::lib:gr.h ::lib:dtypes.h ::lib:fix.h ::lib:mono.h ::lib:key.h ¶
	::lib:3d.h ::lib:vecmat.h bm.h piggy.h digi.h sounds.h inferno.h ::lib:error.h game.h ¶
	object.h segment.h gameseg.h aistruct.h ::lib:mem.h textures.h segpoint.h screens.h ¶
	::lib:texmap.h texmerge.h menu.h wall.h switch.h polyobj.h robot.h effects.h vclip.h ¶
	::lib:iff.h ::lib:pcx.h ::lib:palette.h args.h titles.h player.h weapon.h text.h ¶
	newdemo.h victor.h network.h gameseq.h mission.h multi.h modem.h gamefont.h kconfig.h ¶
	arcade.h coindev.h ::lib:mouse.h ::lib:joy.h newmenu.h desc_id.h config.h joydefs.h ¶
	iglasses.h songs.h ::lib:cfile.h cdrom.h ::lib:macsys.h vers_id.h
{OBJDIR}joydefs.c.o Ä joydefs.c ::lib:mono.h ::lib:key.h ::lib:fix.h ::lib:dtypes.h ::lib:joy.h ¶
	::lib:error.h inferno.h game.h ::lib:vecmat.h object.h segment.h gameseg.h aistruct.h ¶
	::lib:gr.h piggy.h digi.h sounds.h player.h weapon.h controls.h joydefs.h victor.h ¶
	render.h ::lib:3d.h ::lib:palette.h newmenu.h args.h text.h kconfig.h playsave.h
{OBJDIR}KCONFIG.C.o Ä KCONFIG.C ::lib:error.h ::lib:dtypes.h ::lib:gr.h ::lib:fix.h ::lib:mono.h ¶
	::lib:key.h ::lib:palette.h game.h ::lib:vecmat.h object.h segment.h gameseg.h ¶
	aistruct.h inferno.h piggy.h digi.h sounds.h gamefont.h ::lib:iff.h ::lib:mem.h ¶
	::lib:joy.h ::lib:mouse.h kconfig.h gauges.h joydefs.h vfx1.h render.h ::lib:3d.h ¶
	arcade.h newmenu.h victor.h endlevel.h multi.h gameseq.h player.h weapon.h mission.h ¶
	text.h menu.h iglasses.h ::lib:gtimer.h screens.h ::lib:macsys.h
{OBJDIR}KMATRIX.C.o Ä KMATRIX.C ::lib:error.h ::lib:dtypes.h ::lib:gr.h ::lib:fix.h ::lib:mono.h ¶
	::lib:key.h ::lib:palette.h game.h ::lib:vecmat.h object.h segment.h gameseg.h ¶
	aistruct.h inferno.h piggy.h digi.h sounds.h gamefont.h ::lib:mem.h newmenu.h menu.h ¶
	player.h weapon.h screens.h ::lib:mouse.h ::lib:joy.h text.h multi.h gameseq.h ¶
	mission.h kmatrix.h gauges.h ::lib:pcx.h network.h ::lib:macsys.h
{OBJDIR}LASER.C.o Ä LASER.C inferno.h game.h ::lib:vecmat.h ::lib:fix.h ::lib:dtypes.h object.h ¶
	segment.h gameseg.h aistruct.h ::lib:gr.h piggy.h digi.h sounds.h bm.h laser.h fvi.h ¶
	segpoint.h ::lib:3d.h ::lib:error.h ::lib:mono.h ::lib:key.h ::lib:texmap.h textures.h ¶
	render.h vclip.h fireball.h polyobj.h robot.h weapon.h player.h network.h gameseq.h ¶
	mission.h multi.h ai.h modem.h powerup.h physics.h
{OBJDIR}LIGHTING.C.o Ä LIGHTING.C inferno.h segment.h ::lib:vecmat.h ::lib:fix.h ::lib:dtypes.h ¶
	::lib:error.h ::lib:mono.h render.h ::lib:3d.h ::lib:gr.h object.h gameseg.h aistruct.h ¶
	piggy.h digi.h sounds.h game.h vclip.h lighting.h laser.h player.h weapon.h powerup.h
{OBJDIR}macnet.c.o Ä macnet.c macnet.h network.h multi.h ::lib:byteswap.h ::lib:ipx.h
{OBJDIR}MENU.C.o Ä MENU.C menu.h inferno.h game.h ::lib:vecmat.h ::lib:fix.h ::lib:dtypes.h ¶
	object.h segment.h gameseg.h aistruct.h ::lib:gr.h piggy.h digi.h sounds.h ::lib:key.h ¶
	::lib:iff.h ::lib:mem.h ::lib:error.h bm.h screens.h ::lib:mono.h ::lib:joy.h effects.h ¶
	vclip.h slew.h gamemine.h gamesave.h ::lib:palette.h args.h newdemo.h gameseq.h player.h ¶
	weapon.h mission.h text.h gamefont.h newmenu.h network.h multi.h scores.h joydefs.h ¶
	modem.h playsave.h kconfig.h titles.h credits.h ::lib:texmap.h ::lib:3d.h polyobj.h ¶
	robot.h state.h songs.h config.h
{OBJDIR}MGLOBAL.C.o Ä MGLOBAL.C ::lib:fix.h ::lib:dtypes.h ::lib:vecmat.h inferno.h segment.h ¶
	object.h gameseg.h aistruct.h ::lib:gr.h piggy.h digi.h sounds.h bm.h ::lib:3d.h ¶
	game.h polyobj.h robot.h ai.h ::lib:mem.h
{OBJDIR}MISSION.C.o Ä MISSION.C ::lib:cfile.h inferno.h mission.h ::lib:dtypes.h gameseq.h player.h ¶
	::lib:fix.h ::lib:vecmat.h weapon.h ::lib:gr.h game.h object.h segment.h gameseg.h ¶
	aistruct.h piggy.h digi.h sounds.h titles.h ::lib:mono.h ::lib:error.h
{OBJDIR}MODEM.C.o Ä MODEM.C game.h ::lib:vecmat.h ::lib:fix.h ::lib:dtypes.h object.h segment.h ¶
	gameseg.h aistruct.h inferno.h ::lib:gr.h piggy.h digi.h sounds.h scores.h modem.h ¶
	player.h weapon.h laser.h ::lib:error.h collide.h endlevel.h network.h gameseq.h ¶
	mission.h multi.h ::lib:mono.h gauges.h newmenu.h menu.h gamesave.h netmisc.h fuelcen.h ¶
	switch.h text.h ::lib:pcx.h ::lib:palette.h multibot.h args.h
{OBJDIR}MORPH.C.o Ä MORPH.C ::lib:texmap.h ::lib:fix.h ::lib:dtypes.h ::lib:3d.h ::lib:vecmat.h ¶
	::lib:gr.h ::lib:error.h inferno.h morph.h object.h segment.h gameseg.h aistruct.h ¶
	piggy.h digi.h sounds.h polyobj.h robot.h game.h lighting.h newdemo.h ::lib:mono.h bm.h
{OBJDIR}MULTI.C.o Ä MULTI.C game.h ::lib:vecmat.h ::lib:fix.h ::lib:dtypes.h object.h segment.h ¶
	gameseg.h aistruct.h inferno.h ::lib:gr.h piggy.h digi.h sounds.h modem.h network.h ¶
	gameseq.h player.h weapon.h mission.h multi.h laser.h fuelcen.h switch.h scores.h ¶
	gauges.h collide.h ::lib:error.h fireball.h newmenu.h ::lib:mono.h wall.h cntrlcen.h ¶
	powerup.h vclip.h polyobj.h ::lib:3d.h robot.h bm.h endlevel.h ::lib:key.h playsave.h ¶
	newdemo.h text.h kmatrix.h multibot.h physics.h fvi.h config.h state.h
{OBJDIR}MULTIBOT.C.o Ä MULTIBOT.C ::lib:vecmat.h ::lib:fix.h ::lib:dtypes.h multibot.h game.h ¶
	object.h segment.h gameseg.h aistruct.h inferno.h ::lib:gr.h piggy.h digi.h sounds.h ¶
	modem.h network.h gameseq.h player.h weapon.h mission.h multi.h laser.h ::lib:error.h ¶
	::lib:mono.h text.h ai.h fireball.h robot.h powerup.h vclip.h scores.h gauges.h ¶
	fuelcen.h switch.h morph.h effects.h physics.h fvi.h
{OBJDIR}NETIPX.C.o Ä NETIPX.C ::lib:dtypes.h netipx.h args.h ::lib:key.h ::lib:fix.h
{OBJDIR}NETMISC.C.o Ä NETMISC.C ::lib:dtypes.h ::lib:mono.h
{OBJDIR}NETWORK.C.o Ä NETWORK.C ::lib:dtypes.h args.h ::lib:mono.h newmenu.h ::lib:key.h ::lib:fix.h ¶
	gauges.h ::lib:gr.h piggy.h digi.h ::lib:vecmat.h sounds.h object.h segment.h gameseg.h ¶
	aistruct.h inferno.h ::lib:error.h netmisc.h laser.h gamesave.h gamemine.h player.h ¶
	weapon.h game.h gameseq.h mission.h fireball.h network.h multi.h endlevel.h ¶
	::lib:palette.h fuelcen.h switch.h menu.h text.h kmatrix.h newdemo.h multibot.h wall.h ¶
	bm.h effects.h vclip.h physics.h fvi.h
{OBJDIR}NEWDEMO.C.o Ä NEWDEMO.C inferno.h game.h ::lib:vecmat.h ::lib:fix.h ::lib:dtypes.h object.h ¶
	segment.h gameseg.h aistruct.h ::lib:gr.h piggy.h digi.h sounds.h bm.h ::lib:mono.h ¶
	::lib:3d.h ::lib:texmap.h laser.h ::lib:key.h physics.h fvi.h slew.h render.h wall.h ¶
	vclip.h polyobj.h robot.h fireball.h ::lib:error.h ai.h hostage.h morph.h powerup.h ¶
	fuelcen.h switch.h collide.h lighting.h newdemo.h gameseq.h player.h weapon.h mission.h ¶
	gamesave.h gamemine.h gauges.h newmenu.h args.h ::lib:palette.h multi.h network.h ¶
	text.h cntrlcen.h ::lib:mem.h
{OBJDIR}NEWMENU.C.o Ä NEWMENU.C ::lib:error.h ::lib:dtypes.h ::lib:gr.h ::lib:fix.h ::lib:mono.h ¶
	::lib:key.h ::lib:palette.h game.h ::lib:vecmat.h object.h segment.h gameseg.h aistruct.h ¶
	inferno.h piggy.h digi.h sounds.h text.h newmenu.h gamefont.h network.h gameseq.h ¶
	player.h weapon.h mission.h multi.h ::lib:iff.h ::lib:pcx.h ::lib:mem.h ::lib:mouse.h ¶
	::lib:joy.h endlevel.h screens.h vfx.h kconfig.h ::lib:macsys.h
{OBJDIR}OBJECT.C.o Ä OBJECT.C inferno.h game.h ::lib:vecmat.h ::lib:fix.h ::lib:dtypes.h object.h ¶
	segment.h gameseg.h aistruct.h ::lib:gr.h piggy.h digi.h sounds.h bm.h ::lib:mono.h ¶
	::lib:3d.h ::lib:texmap.h laser.h ::lib:key.h textures.h physics.h fvi.h slew.h render.h ¶
	wall.h vclip.h polyobj.h robot.h fireball.h ::lib:error.h ai.h hostage.h morph.h ¶
	cntrlcen.h powerup.h fuelcen.h switch.h collide.h lighting.h newdemo.h player.h weapon.h ¶
	network.h gameseq.h mission.h multi.h newmenu.h gauges.h arcade.h menu.h args.h text.h
{OBJDIR}PAGING.C.o Ä PAGING.C ::lib:mono.h inferno.h segment.h ::lib:vecmat.h ::lib:fix.h ¶
	::lib:dtypes.h textures.h bm.h ::lib:gr.h piggy.h digi.h sounds.h wall.h object.h ¶
	gameseg.h aistruct.h gamemine.h ::lib:error.h game.h texmerge.h polyobj.h ::lib:3d.h ¶
	robot.h vclip.h effects.h fireball.h weapon.h ::lib:palette.h text.h cntrlcen.h gauges.h
{OBJDIR}PHYSICS.C.o Ä PHYSICS.C ::lib:joy.h ::lib:fix.h ::lib:dtypes.h ::lib:mono.h ::lib:error.h ¶
	inferno.h segment.h ::lib:vecmat.h object.h gameseg.h aistruct.h ::lib:gr.h piggy.h ¶
	digi.h sounds.h physics.h fvi.h ::lib:key.h game.h collide.h newdemo.h ai.h wall.h laser.h
{OBJDIR}PIGGY.C.o Ä PIGGY.C ::lib:dtypes.h inferno.h ::lib:gr.h ::lib:fix.h ::lib:mem.h ::lib:mono.h ¶
	::lib:error.h sounds.h ::lib:vecmat.h digi.h bm.h piggy.h hash.h args.h ::lib:palette.h ¶
	gamefont.h ::lib:rle.h screens.h texmerge.h paging.h game.h object.h segment.h gameseg.h ¶
	aistruct.h text.h ::lib:cfile.h newmenu.h ::lib:macsys.h
{OBJDIR}PLAYSAVE.C.o Ä PLAYSAVE.C ::lib:error.h gameseq.h player.h inferno.h ::lib:fix.h ¶
	::lib:dtypes.h ::lib:vecmat.h weapon.h ::lib:gr.h game.h object.h segment.h gameseg.h ¶
	aistruct.h piggy.h digi.h sounds.h mission.h playsave.h ::lib:joy.h kconfig.h newmenu.h ¶
	joydefs.h ::lib:palette.h multi.h menu.h config.h text.h ::lib:mono.h state.h
{OBJDIR}POLYOBJ.C.o Ä POLYOBJ.C inferno.h polyobj.h ::lib:vecmat.h ::lib:fix.h ::lib:dtypes.h ¶
	::lib:gr.h ::lib:3d.h robot.h object.h segment.h gameseg.h aistruct.h piggy.h digi.h ¶
	sounds.h game.h ::lib:error.h ::lib:mono.h ::lib:mem.h ::lib:texmap.h bm.h textures.h ¶
	lighting.h ::lib:cfile.h
{OBJDIR}POWERUP.C.o Ä POWERUP.C ::lib:3d.h ::lib:fix.h ::lib:dtypes.h ::lib:vecmat.h ::lib:gr.h ¶
	::lib:mono.h inferno.h object.h segment.h gameseg.h aistruct.h piggy.h digi.h sounds.h ¶
	game.h fireball.h powerup.h vclip.h gauges.h player.h weapon.h wall.h text.h laser.h ¶
	scores.h multi.h gameseq.h mission.h newdemo.h
{OBJDIR}RENDER.C.o Ä RENDER.C inferno.h segment.h ::lib:vecmat.h ::lib:fix.h ::lib:dtypes.h ¶
	::lib:error.h bm.h ::lib:gr.h piggy.h digi.h sounds.h ::lib:texmap.h ::lib:3d.h ¶
	::lib:mono.h render.h object.h gameseg.h aistruct.h game.h laser.h textures.h screens.h ¶
	segpoint.h wall.h texmerge.h physics.h fvi.h vclip.h lighting.h newdemo.h automap.h ¶
	endlevel.h ::lib:key.h newmenu.h ::lib:mem.h
{OBJDIR}ROBOT.C.o Ä ROBOT.C ::lib:error.h inferno.h robot.h ::lib:vecmat.h ::lib:fix.h ¶
	::lib:dtypes.h object.h segment.h gameseg.h aistruct.h ::lib:gr.h piggy.h digi.h ¶
	sounds.h game.h polyobj.h ::lib:3d.h ::lib:mono.h
{OBJDIR}SCORES.C.o Ä SCORES.C ::lib:error.h ::lib:dtypes.h ::lib:gr.h ::lib:fix.h ::lib:mono.h ¶
	::lib:key.h ::lib:palette.h game.h ::lib:vecmat.h object.h segment.h gameseg.h aistruct.h ¶
	inferno.h piggy.h digi.h sounds.h gamefont.h ::lib:mem.h newmenu.h menu.h player.h ¶
	weapon.h screens.h ::lib:mouse.h ::lib:joy.h text.h
{OBJDIR}SERIAL.C.o Ä SERIAL.C serial.h
{OBJDIR}SLEW.C.o Ä SLEW.C inferno.h game.h ::lib:vecmat.h ::lib:fix.h ::lib:dtypes.h object.h ¶
	segment.h gameseg.h aistruct.h ::lib:gr.h piggy.h digi.h sounds.h ::lib:key.h ::lib:joy.h ¶
	::lib:error.h physics.h fvi.h joydefs.h kconfig.h
{OBJDIR}SONGS.C.o Ä SONGS.C ::lib:error.h ::lib:dtypes.h songs.h ::lib:mono.h ::lib:cfile.h digi.h ¶
	::lib:vecmat.h ::lib:fix.h
{OBJDIR}STATE.C.o Ä STATE.C ::lib:mono.h inferno.h segment.h ::lib:vecmat.h ::lib:fix.h ¶
	::lib:dtypes.h textures.h bm.h ::lib:gr.h piggy.h digi.h sounds.h wall.h object.h ¶
	gameseg.h aistruct.h gamemine.h ::lib:error.h switch.h game.h newmenu.h ::lib:cfile.h ¶
	fuelcen.h hash.h ::lib:key.h player.h weapon.h cntrlcen.h morph.h render.h ::lib:3d.h ¶
	gameseq.h mission.h gauges.h newdemo.h automap.h paging.h titles.h text.h ::lib:pcx.h ¶
	::lib:mem.h network.h multi.h args.h
{OBJDIR}SWITCH.C.o Ä SWITCH.C gauges.h ::lib:fix.h ::lib:dtypes.h ::lib:gr.h piggy.h digi.h ¶
	::lib:vecmat.h sounds.h game.h object.h segment.h gameseg.h aistruct.h inferno.h ¶
	switch.h ::lib:error.h ::lib:mono.h wall.h ::lib:texmap.h ::lib:3d.h fuelcen.h newdemo.h ¶
	player.h weapon.h endlevel.h gameseq.h mission.h multi.h network.h ::lib:palette.h
{OBJDIR}TERRAIN.C.o Ä TERRAIN.C ::lib:3d.h ::lib:fix.h ::lib:dtypes.h ::lib:vecmat.h ::lib:gr.h ¶
	::lib:error.h ::lib:texmap.h ::lib:iff.h ::lib:mem.h ::lib:mono.h inferno.h textures.h ¶
	bm.h piggy.h digi.h sounds.h object.h segment.h gameseg.h aistruct.h endlevel.h fireball.h
{OBJDIR}TEXMERGE.C.o Ä TEXMERGE.C ::lib:gr.h ::lib:dtypes.h ::lib:fix.h ::lib:error.h game.h ¶
	::lib:vecmat.h object.h segment.h gameseg.h aistruct.h inferno.h piggy.h digi.h sounds.h ¶
	textures.h bm.h ::lib:mono.h ::lib:rle.h
{OBJDIR}TEXT.C.o Ä TEXT.C ::lib:cfile.h ::lib:mem.h ::lib:error.h inferno.h text.h args.h compbit.h
{OBJDIR}TITLES.C.o Ä TITLES.C ::lib:dtypes.h ::lib:key.h ::lib:fix.h ::lib:gr.h ::lib:palette.h ¶
	::lib:iff.h ::lib:pcx.h ::lib:mem.h ::lib:joy.h arcade.h coindev.h ::lib:mono.h ¶
	gamefont.h ::lib:cfile.h ::lib:error.h polyobj.h ::lib:vecmat.h ::lib:3d.h robot.h ¶
	object.h segment.h gameseg.h aistruct.h inferno.h piggy.h digi.h sounds.h game.h ¶
	textures.h bm.h screens.h multi.h gameseq.h player.h weapon.h mission.h compbit.h text.h ¶
	kmatrix.h songs.h vfx.h newmenu.h state.h ::lib:macsys.h
{OBJDIR}VCLIP.C.o Ä VCLIP.C ::lib:error.h inferno.h vclip.h ::lib:gr.h ::lib:dtypes.h ¶
	::lib:fix.h object.h ::lib:vecmat.h segment.h gameseg.h aistruct.h piggy.h digi.h ¶
	sounds.h weapon.h game.h
{OBJDIR}WALL.C.o Ä WALL.C ::lib:mono.h ::lib:gr.h ::lib:dtypes.h ::lib:fix.h wall.h inferno.h ¶
	segment.h ::lib:vecmat.h object.h gameseg.h aistruct.h piggy.h digi.h sounds.h switch.h ¶
	::lib:error.h game.h bm.h vclip.h player.h weapon.h gauges.h text.h fireball.h ¶
	textures.h newdemo.h multi.h gameseq.h mission.h
{OBJDIR}WEAPON.C.o Ä WEAPON.C game.h ::lib:vecmat.h ::lib:fix.h ::lib:dtypes.h object.h segment.h ¶
	gameseg.h aistruct.h inferno.h ::lib:gr.h piggy.h digi.h sounds.h weapon.h ::lib:mono.h ¶
	player.h gauges.h ::lib:error.h text.h powerup.h vclip.h newdemo.h multi.h gameseq.h ¶
	mission.h
{OBJDIR}redbook.c.o Ä redbook.c redbook.h 