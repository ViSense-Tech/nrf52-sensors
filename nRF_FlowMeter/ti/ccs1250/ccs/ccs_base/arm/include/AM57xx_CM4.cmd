/****************************************************************************/
/*  AM57xx_CM4.cmd                                                          */
/*  Copyright (c) 2015  Texas Instruments Incorporated                      */
/*  Author: Rafael de Souza                                                 */
/*                                                                          */
/*    Description: This file is a sample linker command file that can be    */
/*                 used for linking programs built with the C compiler and  */
/*                 running the resulting .out file on the Cortex M4 core of */
/*                 an AM57xx device.                                        */
/*                 Use it as a guideline.  You will want to                 */
/*                 change the memory layout to match your specific          */
/*                 target system.  You may want to change the allocation    */
/*                 scheme according to the size of your program.            */
/*                                                                          */
/****************************************************************************/

--retain='*(.intvecs)'
--retain='*(.intc_text)'

#ifdef MMU     /* memory map with MMU turned on */

MEMORY
{
    IRAM:      o = 0x00000000 l = 0x00001000   /* 4kB internal SRAM */
    OCMC_RAM1: o = 0x00300000 l = 0x00080000   /* 512kB L3 OCMC SRAM1 */
    OCMC_RAM2: o = 0x00400000 l = 0x00100000   /* 1MB L3 OCMC SRAM2 */
    OCMC_RAM3: o = 0x00500000 l = 0x00100000   /* 1MB L3 OCMC SRAM3 */
	DDR0:      o = 0x80000000 l = 0x40000000   /* 1GB external DDR Bank 0 */
}

#else     /* memory map with MMU turned off */

MEMORY
{
    IRAM:      o = 0x00000000 l = 0x00001000   /* 4kB internal SRAM */
    OCMC_RAM1: o = 0x40300000 l = 0x00080000   /* 512kB L3 OCMC SRAM1 */
    OCMC_RAM2: o = 0x40400000 l = 0x00100000   /* 1MB L3 OCMC SRAM2 */
    OCMC_RAM3: o = 0x40500000 l = 0x00100000   /* 1MB L3 OCMC SRAM3 */
	DDR0:      o = 0x80000000 l = 0x40000000   /* 1GB external DDR Bank 0 */
}

#endif

SECTIONS
{
    .intvecs:    > 0x00000000
    .intc_text:  > IRAM
    .text:       > OCMC_RAM1
    .const:      > OCMC_RAM1
    .cinit:      > OCMC_RAM1
    .init_array: > OCMC_RAM1
    .data:       > OCMC_RAM1 
    .bss:        > OCMC_RAM1 
    .stack:      > OCMC_RAM1
    .sysmem:     > OCMC_RAM1
}
