/****************************************************************************/
/*  AM3715.cmd                                                              */
/*  Copyright (c) 2012  Texas Instruments Incorporated                      */
/*  Author: Rafael de Souza                                                 */
/*                                                                          */
/*    Description: This file is a sample linker command file that can be    */
/*                 used for linking programs built with the C compiler and  */
/*                 running the resulting .out file on an AM3715.            */
/*                 Use it as a guideline.  You will want to                 */
/*                 change the memory layout to match your specific          */
/*                 target system.  You may want to change the allocation    */
/*                 scheme according to the size of your program.            */
/*                                                                          */
/****************************************************************************/

MEMORY
{
    SRAM:       o = 0x40200000  l = 0x00010000  /* 64kB Internal SRAM */
    CS0_SDRAM:  o = 0x80000000  l = 0x20000000  /* 512MB of external mDDR in CS0 */
    CS1_SDRAM:  o = 0xA0000000  l = 0x20000000  /* 512MB of external mDDR in CS1 */
}

SECTIONS
{
    .text          >  SRAM
    .stack         >  SRAM
    .bss           >  SRAM
    .cio           >  SRAM
    .const         >  SRAM
    .data          >  SRAM
    .switch        >  SRAM
    .sysmem        >  SRAM
    .far           >  SRAM
    .args          >  SRAM
    .ppinfo        >  SRAM
    .ppdata        >  SRAM
  
    /* TI-ABI sections */
    .pinit         >  SRAM
    .cinit         >  SRAM
  
    /* EABI sections */
    .binit         >  SRAM
    .init_array    >  SRAM
    .neardata      >  SRAM
    .fardata       >  SRAM
    .rodata        >  SRAM
    .c6xabi.exidx  >  SRAM
    .c6xabi.extab  >  SRAM
}
