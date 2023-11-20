/*==========================================================================================
// cyclone.cmd  Linker command file for Cyclone 128
//
//
//    Available Cyclone 128 memory:
//    ---------------------------------
//    P-Flash   128K   0x0000  - 0x1fFFF
//    ROM       8K    0x20000 - 0x21FFF	 
//    D-Flash   2K    0x69800 - 0x69FFF
//    RAM       8K    0x6A000 - 0x6BFFF
//
// Copyright (C) 2013 Texas Instruments Incorporated.
//========================================================================================*/

MEMORY
{
    /*------------------------------------------------------------------------------------*/
    /* ROM       8K    0x20000 - 0x21FFF                                                  */
    /*------------------------------------------------------------------------------------*/
    ROMVECS        : org = 0x00020000, len = 0x00000020    /* Vector table                */
    ROM            : org = 0x00020020, len = 0x00001D5E    /* System ROM                  */
    SINE           : org = 0x00021D7E, len = 0x00000282    /* Sine table                  */

    /*------------------------------------------------------------------------------------*/
    /* P-Flash   128K   0x0  - 0x1FFFF    //this one is set up for only 32K                                               */
    /*------------------------------------------------------------------------------------*/
    FLASHVECS (RX) : org = 0x00000000, len = 0x00000020    /* PFlash "Re-vector" Table    */
    PFLASH    (RX) : org = 0x00000020, len = 0x00007F34    /* PFlash Main Program         */
    DEVICEID  (RX) : org = 0x00007F54, len = 0x00000020    /* Fixed Location for DEVICE_ID*/
    FIXTFA    (RX) : org = 0x00007F74, len = 0x00000004    /* Fixed Step Size for TFA     */
    FIXCONST  (RX) : org = 0x00007F78, len = 0x00000080    /* Fixed-location Constants    */
    FLASHSUM  (RX) : org = 0x00007FF8, len = 0x00000008    /* Flash Checksum              */


    /*------------------------------------------------------------------------------------*/
    /* D-Flash   2K    0x69800 - 0x69FFF                                                  */
    /*------------------------------------------------------------------------------------*/
    DFLASH    (RX) : org = 0x00069800, len = 0x00000800

    /*------------------------------------------------------------------------------------*/
    /* RAM       8K    0x6A000 - 0x6BFFF                                                  */
    /*                                                                                    */
    /*    Partition RAM into 2 parts:                                                  */
    /*     1. General variables.                                                          */
    /*     2. Stacks for the various operating modes.                                     */
    /*        NOTE!!  Stack size must be specified in load.asm too!!!                */
    /*------------------------------------------------------------------------------------*/
    RAM       (RW) : org = 0x0006A000, len = 0x00001E50
    STACKS    (RW) : org = 0x0006BE50, len = 0x000001B0
}

SECTIONS
{
    /*------------------------------------------------------------------------------------*/
    /* P-Flash   32K   0x0  - 0x7FFF                                                      */
    /*                                                                                    */
    /*   Most of these sections are unused for the ROM build.                             */
    /*------------------------------------------------------------------------------------*/ 
    .vectors        : {} > FLASHVECS                 /* Interrupt "re-vectors"            */ 
    .fiq            : {} > 0x001C                    /* Fast Interrupt Handler            */
    .text           : {} > (PFLASH align(16))        /* Code                              */
    .const          : {} > (PFLASH align(16))        /* Constant data                     */
    .cinit          : {} > (PFLASH align(16))        /* Initialization tables             */
     FixedDeviceID  : {} > (DEVICEID)                /* Fixed location for Device ID      */
     FixedTfaStep   : {} > FIXTFA                    /* Fixed location TFA Step Size      */
     FixedConstants : {} > FIXCONST                  /* Fixed location constants          */ 
    .flashi         : {} > FLASHSUM                  /* PFlash Integrity Word             */

    /*------------------------------------------------------------------------------------*/
    /* ROM (8kB   0x20000 - 0x21FFF                                                       */
    /*------------------------------------------------------------------------------------*/
    .romvectors        : {} > ROMVECS
    .sine           : {} > SINE

    /*------------------------------------------------------------------------------------*/
    /* D-Flash   2K    0x69800 - 0x69FFF                                                  */
    /*------------------------------------------------------------------------------------*/
    .dflash         : {} > (DFLASH align(32))
	.CONFIG    : {} > (DFLASH align(32))
    .CONFIG_A  : {} > (DFLASH align(32))
    .CONFIG_B  : {} > (DFLASH align(32))
	.PASSW     : {} > (DFLASH align(32))

    /*------------------------------------------------------------------------------------*/
    /* RAM       8K    0x6A000 - 0x6BFFF   
    /* Note, stacks must be defined in load.asm as well.                                                 */
    /*------------------------------------------------------------------------------------*/
    .bss            : {} > RAM                       /* Global & Static vars              */
    .stack          : {                              /* total = 400 = 0x190               */
                        _StackUSER_  = .            + 184;   /* USER                      */
                        _StackFIQ_   = _StackUSER_  + 112;   /* FIQ                       */
	                    _StackIRQ_   = _StackFIQ_   + 84;    /* IRQ                       */
                        _StackABORT_ = _StackIRQ_   + 4;     /* ABORT                     */
                        _StackUND_   = _StackABORT_ + 4;     /* UND                       */
                        _StackSUPER_ = _StackUND_   + 12;    /* SUPER                     */
	                 } > STACKS                          /* Software System stack     */
}
