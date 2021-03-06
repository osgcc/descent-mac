data 'ALRT' (200, "WarningAlert") {
	$"0032 014E 00B4 0266 0080 5555"                      /* .2.N.´.f.UU */
};

data 'ALRT' (201, "ErrorAlert") {
	$"0032 014E 00B4 0266 0081 5555"                      /* .2.N.´.f.UU */
};

data 'DITL' (128) {
	$"0002 0000 0000 0032 000A 007D 010A 8802"            /* .......2...}... */
	$"5E30 0000 0000 000A 000A 002A 002A A002"            /* ^0.........*.* . */
	$"0002 0000 0000 000A 00AA 001E 00E4 0402"            /* .........Ş...ä.. */
	$"4F4B"                                               /* OK */
};

data 'DITL' (129) {
	$"0002 0000 0000 000A 000A 002A 002A A002"            /* ...........*.* . */
	$"0000 0000 0000 0032 000A 0080 010F 8802"            /* .......2...... */
	$"5E30 0000 0000 000A 00AA 001E 00E4 0402"            /* ^0.......Ş...ä.. */
	$"4F4B"                                               /* OK */
};

data 'SIZE' (-1) {
	$"10E0 0098 9680 005B 8D80"                           /* .à..[ */
};

