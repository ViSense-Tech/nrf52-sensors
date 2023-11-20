/*==========================================================================================
// cyclone.cmd  Linker command file for Cyclone
//
// In addtion to the memory sections specified here, functions existing in the ROM
// are specified by RomFuncs.cmd which is automatically generated in the ROM build
// process.
//
//    Available Cyclone memory:
//    ---------------------------------
//    P-Flash   32K   0x0000  - 0xFFFF
//    ROM       8K    0xA000  - 0xBFFF	 
//    D-Flash   2K    0x18800 - 0x18FFF
//    RAM       4K    0x19000 - 0x19FFF
//
// Copyright (C) 2008 Texas Instruments Incorporated.
//========================================================================================*/

MEMORY
{

    VECS           : org = 0x00000000, len = 0x00000020    /* Vector table                */
    /*------------------------------------------------------------------------------------*/
    /* ROM       8K    0xA000 - 0xBFFF                                                    */
    /*------------------------------------------------------------------------------------*/
    ROM     : org = 0x00020020   len = 0x00000FE0  /* SYSTEM ROM    */
	SINE	: org = 0x00021000   len = 0x00000282  /*sine table in ROM */
	EXP	: org = 0x00021282   len = 0x0000007A  /*exponent table in ROM */

    /*------------------------------------------------------------------------------------*/
    /* P-Flash   32K   0x0  - 0x7FFF                                                   */
    /*------------------------------------------------------------------------------------*/
    PFLASH    (RX) : org = 0x00000020, len = 0x00007F38    /* PFlash Main Program         */
    DEVICEID  (RX) : org = 0x00007F58, len = 0x00000020    /* Fixed Location for DEVICE_ID*/
    FIXTFA    (RX) : org = 0x00007F78, len = 0x00000004    /* Fixed Step Size for TFA     */
    FIXCONST  (RX) : org = 0x00007F7C, len = 0x00000080    /* Fixed-location Constants    */
    FLASHSUM  (RX) : org = 0x00007FFC, len = 0x00000004    /* Flash Checksum              */


    /*------------------------------------------------------------------------------------*/
    /* D-Flash   2K    0x18800 - 0x18FFF                                                  */
    /*------------------------------------------------------------------------------------*/
    DFLASH    (RX) : org = 0x00068800, len = 0x00000800

    /*------------------------------------------------------------------------------------*/
    /* RAM       4K    0x19000 - 0x19FFF                                                  */
    /*                                                                                    */
    /*    Partition RAM into four parts:                                                  */
    /*     1. Fixed at the start of RAM are tester variables.                             */
    /*        that can not move without breaking the tester.                              */
    /*     2. General variables.                                                          */
    /*     3. Stacks for the various operating modes.                                     */
    /*        NOTE!!  Stack size must be specified in build options too!!!                */
    /*     4. The interlock used to prevent rom from returing to flash - rom_flash_lock.  */
    /*------------------------------------------------------------------------------------*/
    RAM       (RW) : org = 0x00069000, len = 0x00001000
}

SECTIONS
{
    /*------------------------------------------------------------------------------------*/
    /* P-Flash   32K   0x0  - 0x7FFF                                                   */
    /*                                                                                    */
    /*   Most of these sections are unused for the ROM build.                             */
    /*------------------------------------------------------------------------------------*/ 

    .fiq            : {} > 0x001C                    /* Fast Interrupt Handler            */
    .text           : {} > (PFLASH align(16))        /* Code                              */
    .const          : {} > (PFLASH align(16))        /* Constant data                     */
    .cinit          : {} > (PFLASH align(16))        /* Initialization tables             */
     FixedDeviceID  : {} > (DEVICEID)                /* Fixed location for Device ID      */
     FixedTfaStep   : {} > FIXTFA                    /* Fixed location TFA Step Size      */
     FixedConstants : {} > FIXCONST                  /* Fixed location constants          */ 
    .flashi         : {} > FLASHSUM                  /* PFlash Integrity Word             */

    /*------------------------------------------------------------------------------------*/
    /* ROM (8kB   0xA000 - 0xBFFF                                                         */
    /*------------------------------------------------------------------------------------*/
    .vectors        : {} > VECS
    .sine           : {} > SINE

    /*------------------------------------------------------------------------------------*/
    /* D-Flash   2K    0x18800 - 0x18FFF                                                  */
    /*------------------------------------------------------------------------------------*/
     .dflash   : {} > (DFLASH align(32))
		//data flash
	.CONFIG    : {} > (DFLASH align(32))
    .CONFIG_A  : {} > (DFLASH align(32))
    .CONFIG_B  : {} > (DFLASH align(32))
	.PASSW     : {} > (DFLASH align(32))
    /*------------------------------------------------------------------------------------*/
    /* RAM       4K    0x19000 - 0x19FFF                                                  */
    /*------------------------------------------------------------------------------------*/
    .bss            : {} > RAM                       /* Global & Static vars              */

}
