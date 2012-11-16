#  Makefile to build the .r files from the .rsrc files



#  default rule to derez the compiled resource file.  We can then archive the .r files



SRCDIR = :

TARGET_DIR = ::lib:



RESOURCES = bios.r macsys.r cfrg.r



All Ä {RESOURCES}



.r Ä .rsrc

	Derez {depDir}{default}.rsrc > {targDir}{default}.r

	duplicate -y {depDir}{default}.r "{TARGET_DIR}"{default}.r