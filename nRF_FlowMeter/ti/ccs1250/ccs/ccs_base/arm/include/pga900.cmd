/* =============================================================================
*                 Texas Instruments PGA900 Platform Software
* (c) Copyright Texas Instruments, Incorporated. All Rights Reserved.
*
* Use of this software is controlled by the terms and conditions found
* in the license agreement under which this software has been supplied.
* =========================================================================== */
/**
* @file pga900.cmd
*
* This File contains CCS linker configuration file for PGA900
*
* @path $(CSLPATH)\PGA900\
*
* @rev 1.1
*/
/* -----------------------------------------------------------------------------
*!
*! Revision History
*! ===================================
*! 01-July-2013 mf: Modified TusharB. Change required per PGA900
*! to provide initial CCS linker configuration file.
* =========================================================================== */

--retain=g_pfnVectors

/* The following command line options are set as part of the CCS project.    */
/* If you are building using the command line, or for some reason want to    */
/* define them here, you can uncomment and modify these lines as needed.     */
/* If you are using CCS for building, it is probably better to make any such */
/* modifications in your CCS project and leave this file alone.              */
/*                                                                           */
/* --heap_size=0                                                             */
/* --stack_size=256                                                          */
/* --library=rtsv7M3_T_le_eabi.lib                                           */

/* The starting address of the application.  Normally the interrupt vectors  */
/* must be located at the beginning of the application.                      */
#define APP_BASE 0x00000000
#define RAM_BASE 0x20000000

/* System memory map */

MEMORY
{
    /* Application stored in and executes from internal flash */
    OTP (RX) : origin = APP_BASE, length = 0x00002000
    /* Application uses internal RAM for data */
    SRAM (RWX) : origin = 0x20000000, length = 0x00000400
    /* Application can be stored in DRAM and executes from DRAM */
    DRAM (RX) : origin = 0x21000000, length = 0x00002000
}

/* Section allocation in memory */

SECTIONS
{
    .intvecs:   > APP_BASE
    .text   :   > OTP
    .const  :   > OTP
    .cinit  :   > OTP
    .pinit  :   > OTP
    .init_array : > OTP

    .vtable :   > RAM_BASE
    .data   :   > SRAM
    .bss    :   > SRAM
    .sysmem :   > SRAM
    .stack  :   > 0x20000000
}

__STACK_TOP = 0x20000000;
