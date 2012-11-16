;/*
;THE COMPUTER CODE CONTAINED HEREIN IS THE SOLE PROPERTY OF PARALLAX
;SOFTWARE CORPORATION ("PARALLAX").  PARALLAX, IN DISTRIBUTING THE CODE TO
;END-USERS, AND SUBJECT TO ALL OF THE TERMS AND CONDITIONS HEREIN, GRANTS A
;ROYALTY-FREE, PERPETUAL LICENSE TO SUCH END-USERS FOR USE BY SUCH END-USERS
;IN USING, DISPLAYING,  AND CREATING DERIVATIVE WORKS THEREOF, SO LONG AS
;SUCH USE, DISPLAY OR CREATION IS FOR NON-COMMERCIAL, ROYALTY OR REVENUE
;FREE PURPOSES.  IN NO EVENT SHALL THE END-USER USE THE COMPUTER CODE
;CONTAINED HEREIN FOR REVENUE-BEARING PURPOSES.  THE END-USER UNDERSTANDS
;AND AGREES TO THE TERMS HEREIN AND ACCEPTS THE SAME BY USE OF THIS FILE.  
;COPYRIGHT 1993-1998 PARALLAX SOFTWARE CORPORATION.  ALL RIGHTS RESERVED.
;*/

; Common Macintosh macro definitions	IF (&TYPE('_MACROS_INC') = 'UNDEFINED') THEN_MACROS_INC equ 1_Debugger 		OPWORD  	$A9FF_DebugStr 		OPWORD  	$ABFF	MACRO	debug_brk	&str	pea	#&str	_DebugStr	ENDM	MACRO	break_if	&cc,&str	IF (&TYPE('NDEBUG') = 'UNDEFINED') THEN	b&cc..s   @yes_break	bra.s    @skip@yes_break:	pea	#&str       _DebugStr@skip:	ENDIF	ENDM	MACRO&lbl	Push.&s	&parm&lbl	move.&s	&parm,-(sp)	ENDM	MACRO&lbl	Pop.&s	&parm&lbl	move.&s	(sp)+,&parm	ENDM	macro	PUSHM.&w	&m1	movem.&w  &m1,-(a7)	endm	macro	POPM.&w	&m1	movem.&w  (a7)+,&m1	endm	MACRO&lbl	Pushz.&s		;PUSHZ macro&lbl	clr.&s	-(sp)	ENDM	macro	pushf			;push flags	move	sr,-(sp)	endm	macro	popf			;pop flags	move	(sp)+,ccr	endm	MACRO&lbl	clc			;CLC macro&lbl	and	#$fe,ccr	ENDM		MACRO&lbl	stc			;STC macro&lbl	or	#$01,ccr	ENDM	MACRO&lbl	clx			;CLX macro&lbl	and	#%11101111,ccr	ENDM		MACRO&lbl	stx			;STX macro&lbl	or	#%00010000,ccr	ENDM	MACRO&lbl	abs	&var, &tmp_reg&lbl:	bfexts	&var{0,1}, &tmp_reg	eor.l	&tmp_reg, &var	sub.l	&tmp_reg, &var	ENDM	ENDIF	;_MACROS_INC
