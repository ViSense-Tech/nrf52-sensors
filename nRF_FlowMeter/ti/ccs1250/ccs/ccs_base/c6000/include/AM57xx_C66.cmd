/****************************************************************************/
/*  AM57xx_C66.cmd                                                          */
/*  Copyright (c) 2015  Texas Instruments Incorporated                      */
/*  Author: Rafael de Souza                                                 */
/*                                                                          */
/*    Description: This file is a sample linker command file that can be    */
/*                 used for linking programs built with the C compiler and  */
/*                 running the resulting .out file on the C66x DSP core of  */
/*                 an AM57xx device.                                        */
/*                 Use it as a guideline.  You will want to                 */
/*                 change the memory layout to match your specific          */
/*                 target system.  You may want to change the allocation    */
/*                 scheme according to the size of your program.            */
/*                                                                          */
/****************************************************************************/

MEMORY
{
    IRAM_MEM:  o = 0x00800000 l = 0x00008000   /* 32kB internal SRAM */
    OCMC_RAM1: o = 0x40300000 l = 0x00080000   /* 512kB L3 OCMC SRAM1 */
    OCMC_RAM2: o = 0x40400000 l = 0x00100000   /* 1MB L3 OCMC SRAM2 */
    OCMC_RAM3: o = 0x40500000 l = 0x00100000   /* 1MB L3 OCMC SRAM3 */
	DDR0:      o = 0x80000000 l = 0x40000000   /* 1GB external DDR Bank 0 */
}

SECTIONS
{
    .text          >  OCMC_RAM1
    .stack         >  OCMC_RAM1
    .bss           >  OCMC_RAM1
    .cio           >  OCMC_RAM1
    .const         >  OCMC_RAM1
    .data          >  OCMC_RAM1
    .switch        >  OCMC_RAM1
    .sysmem        >  OCMC_RAM1
    .far           >  OCMC_RAM1
    .args          >  OCMC_RAM1
    .ppinfo        >  OCMC_RAM1
    .ppdata        >  OCMC_RAM1
  
    /* COFF sections */
    .pinit         >  OCMC_RAM1
    .cinit         >  OCMC_RAM1
  
    /* EABI sections */
    .binit         >  OCMC_RAM1
    .init_array    >  OCMC_RAM1
    .neardata      >  OCMC_RAM1
    .fardata       >  OCMC_RAM1
    .rodata        >  OCMC_RAM1
    .c6xabi.exidx  >  OCMC_RAM1
    .c6xabi.extab  >  OCMC_RAM1
}


