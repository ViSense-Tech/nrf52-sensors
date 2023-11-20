;
;  Copyright 2001 by Texas Instruments Incorporated.
;  All rights reserved. Property of Texas Instruments Incorporated.
;  Restricted rights to use, duplicate or disclose this code are
;  granted through contract.
;  U.S. Patent Nos. 5,283,900  5,392,448
;
;  ======== load.asm ========
;
;  C-callable interface to assembly language utility functions for the
;  volume example.

SUP_STACK_TOP   .equ	0x19ffc ;Supervisor mode (SWI stack) starts at top of memory
FIQ_STACK_TOP	.equ	0x19e00 ;allocate 256 bytes to supervisor stack, then do FIQ stack
IRQ_STACK_TOP	.equ	0x19d00 ;allocate 256 bytes to fiq stack, then start irq stack
USER_STACK_TOP	.equ	0x19b00 ;Allocate 512 bytes to irq stack, regular stack gets rest, down to variables
		.global _c_int00
		.global $c_int00
		.global $main
		.global	_undefined_instruction_exception
		.global	_software_interrupt
		.global	_abort_prefetch_exception
		.global	_abort_data_fetch_exception
		.global	_reserved_exception
		.global	_standard_interrupt
		.global	_fast_interrupt
		.global cinit
		.global rom_main
rom_main .equ 0xffffa4dc
		.sect ".vectors"
		.state32
		B	c_int00 
		B	_undefined_instruction_exception
		B	_software_interrupt
		B	_abort_prefetch_exception
		B	_abort_data_fetch_exception
		B	_abort_prefetch_exception
		B	_standard_interrupt
		B	_fast_interrupt
		.align	4
		.sect ".text"
		.state32
c_int00
;		B	c_int00 
		LDR		r13, c_sup_stack_top ; initialize supervisor stack pointer
		LDR		r4,c_mfbalr1_half0 ;point r4 at program flash base address register
		MOV		r0,#0x62 ;make block size 32K, address 0, read only
		STRH	r0,[r4]; store it there
		LDR		r0,c_mfbalr2_half0_load ;set up data flash for write only
		STRH	r0,[r4,#8] ;put it into mfbalr2
		
;*------------------------------------------------------
;* SET TO FIQ MODE, init FIQ stack
;*------------------------------------------------------
        MRS     r0, cpsr
        BIC     r0, r0, #0x1F  ; CLEAR MODES
        ORR     r0, r0, #0x11  ; SET FIQ MODE
        MSR     cpsr_cf, r0;

		LDR		R13, c_fiq_stack_top ; initialize stack pointer

;*------------------------------------------------------
;* SET TO IRQ MODE, init IRQ stack
;*------------------------------------------------------
        MRS     r0, cpsr
        BIC     r0, r0, #0x1F  ; CLEAR MODES
        ORR     r0, r0, #0x12  ; SET IRQ MODE
        MSR     cpsr_cf, r0

		LDR		R13, c_irq_stack_top ; initialize stack pointer

;*------------------------------------------------------
;* SET TO USER MODE, init user stack
;*------------------------------------------------------
        MRS     r0, cpsr
        BIC     r0, r0, #0x1F  ; CLEAR MODES
        ORR     r0, r0, #0x10  ; SET USER MODE
        MSR     cpsr_cf, r0

		ldr	R13, c_user_stack_top ; initialize stack pointer
LOOPY
;		B	LOOPY
;		B	_c_int00

;*------------------------------------------------------
;* CHANGE TO 16 BIT STATE
;*------------------------------------------------------
		ADD	r0, pc, #1
		BX	r0

	.state16

;*----------------
;Clear RAM
;-------------------------		
        MOV       A3, #0     ;zero to store in RAM
;
        MOV       A1, #255	;loop counter
        LSL       A1, A1, #2  ;almost all words cleared 1020 of 1024
;
        MOV       A2, #25	;point at 0x19000 - start of RAM
        LSL       A2, A2, #12
RAM_CLEAR_LOOP:    
        STR       A3, [A2, #0]          ; clear location 
        ADD       A2, #4                ; point to next word 
        SUB       A1, #1                ; decrement loop counter 
        BQNE      RAM_CLEAR_LOOP        ; loop until counter is zero 
;*------------------------------------------------------
;* PERFORM AUTO-INITIALIZATION.  IF CINIT IS -1, THEN
;* THERE IS NONE.
;*------------------------------------------------------
;		BL	$c_int00
;		BL	$c_int00
	LDR	r0, c_cinit
	MOV	r7, #1 
	CMN	r0, r7
	BEQ	_c1_
;
;initialize variables
;
;***************************************************************************
;*  PROCESS INITIALIZATION TABLE.
;*
;*  THE TABLE CONSISTS OF A SEQUENCE OF RECORDS OF THE FOLLOWING FORMAT:
;*                                                                          
;*       .word  <length of data (bytes)>
;*       .word  <address of variable to initialize>                         
;*       .word  <data>
;*                                                                          
;*  THE INITIALIZATION TABLE IS TERMINATED WITH A ZERO LENGTH RECORD.
;*                                                                          
;***************************************************************************

tbl_addr  .set    r0
var_addr  .set    r1
tmp	  .set    r2
length:   .set    r3
data:     .set    r4
three:    .set    r5

	MOV	three, #3		   ;
	B	rec_chk			   ;

        ;*------------------------------------------------------
	;* PROCESS AN INITIALIZATION RECORD
        ;*------------------------------------------------------
record:	LDR	var_addr, [tbl_addr, #4]   ;
	ADD	tbl_addr, #8		   ;

        ;*------------------------------------------------------
	;* COPY THE INITIALIZATION DATA
        ;*------------------------------------------------------
	MOV	tmp, var_addr		   ; DETERMINE ALIGNMENT
	AND	tmp, three		   ; AND COPY BYTE BY BYTE
	BNE	_bcopy			   ; IF NOT WORD ALIGNED

	MOV	tmp, length		   ; FOR WORD COPY, STRIP
	AND	tmp, three		   ; OUT THE NONWORD PART
	BIC	length, three		   ; OF THE LENGTH
	BEQ	_wcont			   ;		

_wcopy:	LDR	data, [tbl_addr]	   ;
	ADD	tbl_addr, #4		   ;
	STR	data, [var_addr]	   ; COPY A WORD OF DATA
	ADD	var_addr, #4		   ;
	SUB	length, #4		   ;
	BNE	_wcopy                     ;
_wcont:	MOV	length, tmp		   ;
	BEQ	_cont			   ;

_bcopy:	LDRB	data, [tbl_addr]	   ;
	ADD	tbl_addr, #1		   ;
	STRB	data, [var_addr]	   ; COPY A BYTE OF DATA
	ADD	var_addr, #1		   ;
	SUB	length, #1		   ;
	BNE	_bcopy                     ;

_cont:	MOV	tmp, tbl_addr	           ;
	AND	tmp, three	           ; MAKE SURE THE ADDRESS
	BEQ	rec_chk			   ; IS WORD ALIGNED
	BIC	tbl_addr, three		   ;
	ADD	tbl_addr, #0x4             ;

rec_chk:LDR	length, [tbl_addr]         ; PROCESS NEXT
	CMP	length, #0                 ; RECORD IF LENGTH IS
	BNE	record                     ; NONZERO 


        ;*------------------------------------------------------
	;* CALL INITIALIZATION ROUTINES FOR CONSTRUCTORS. IF
	;* PINIT IS -1, THEN THERE ARE NONE.
	;* NOTE THAT r7 IS PRESERVED ACROSS AUTO-INITIALIZATION.
        ;*------------------------------------------------------
_c1_:	
		BL	$c_int00
		.align 4					
c_cinit .long    cinit
c_fiq_stack_top .long FIQ_STACK_TOP
c_irq_stack_top .long IRQ_STACK_TOP
c_sup_stack_top .long SUP_STACK_TOP
c_user_stack_top .long USER_STACK_TOP
c_mfbalr1_half0 .long 0xFFFFFE0E ;low 16 bits of memory fine bank address low
c_mfbalr2_half0_load .long	0x8822 ;data flash base address 8800, block size 2K, read only
		.sect ".dflash"
		.end
