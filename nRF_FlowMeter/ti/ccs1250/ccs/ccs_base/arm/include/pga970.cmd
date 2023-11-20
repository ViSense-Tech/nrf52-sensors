/* =============================================================================
*                 Texas Instruments PGA970 Platform Software
* (c) Copyright Texas Instruments, Incorporated. All Rights Reserved.
*
* Use of this software is controlled by the terms and conditions found
* in the license agreement under which this software has been supplied.
* =========================================================================== */
/**
* @file pga970.cmd
*
* This File contains CCS linker configuration file for PGA970
*
* @path $(CSLPATH)\PGA970\
*
* @rev 1.1
*/
/* -----------------------------------------------------------------------------
*!
*! Revision History
*! ===================================
*! 08-Sept-2014 mf: Modified TusharB. Change required per PGA970
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

    /* Application stored in and executes from internal flash
    Size of  FRAM is 6 KB */
    FRAM_TEXT (RX) : origin = APP_BASE, length = 0x00001800
    FRAM_DATA (RX) : origin = 0x00001800, length = 0x00000800
    /* Application uses internal RAM for data
    Size of SRAM is 2KB */
    SRAM (RWX) : origin = RAM_BASE, length = 0x00000800
    /* Application can be stored in DRAM and executes from DRAM
     Size of DRAM is 6KB */
    DRAM (RX) : origin = 0x21000000, length = 0x00001800
    /* Waveform RAM is 512 bytes */
    WRAM (RX) : origin = 0x20000800, length = 0x00000200
}

/* Section allocation in memory */

SECTIONS
{
    .intvecs:   > APP_BASE
    .text   :   > FRAM_TEXT
    .const  :   > FRAM_TEXT
    .cinit  :   > FRAM_TEXT
    .pinit  :   > FRAM_TEXT
    .init_array : > FRAM_TEXT
    .FRAM_TEXT_checksum   : > 0x000017FC
    .waveform_table       : > WRAM

    .vtable :   > RAM_BASE
    .data   :   > SRAM
    .bss    :   > SRAM
    .sysmem :   > SRAM
    .stack  :   > 0x20000000
}

__STACK_TOP = 0x20000000;
