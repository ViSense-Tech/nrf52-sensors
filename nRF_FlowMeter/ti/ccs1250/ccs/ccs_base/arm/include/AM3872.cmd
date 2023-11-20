/****************************************************************************/
/*  AM3872.cmd                                                              */
/*  Copyright (c) 2012  Texas Instruments Incorporated                      */
/*  Author: Rafael de Souza                                                 */
/*                                                                          */
/*    Description: This file is a sample linker command file that can be    */
/*                 used for linking programs built with the C compiler and  */
/*                 running the resulting .out file on an AM3872.            */
/*                 Use it as a guideline.  You will want to                 */
/*                 change the memory layout to match your specific          */
/*                 target system.  You may want to change the allocation    */
/*                 scheme according to the size of your program.            */
/*                                                                          */
/****************************************************************************/

MEMORY
{
    ARMRAM    o = 0x402F0400  l = 0x0000FC00  /* 64kB ARM RAM */
    L3OCMC0   o = 0x40300000  l = 0x00020000  /* 128kB L3 OCMC SRAM */
    DDR0      o = 0x80000000  l = 0x40000000  /* 1GB external DDR Bank 0 */
    DDR1      o = 0xC0000000  l = 0x40000000  /* 1GB external DDR Bank 1 */
}

SECTIONS
{
    .text          >  DDR0
    .stack         >  DDR0
    .bss           >  DDR0
    .cio           >  DDR0
    .const         >  DDR0
    .data          >  DDR0
    .switch        >  DDR0
    .sysmem        >  DDR0
    .far           >  DDR0
    .args          >  DDR0
    .ppinfo        >  DDR0
    .ppdata        >  DDR0
  
    /* TI-ABI or COFF sections */
    .pinit         >  DDR0
    .cinit         >  DDR0
  
    /* EABI sections */
    .binit         >  DDR0
    .init_array    >  DDR0
    .neardata      >  DDR0
    .fardata       >  DDR0
    .rodata        >  DDR0
    .c6xabi.exidx  >  DDR0
    .c6xabi.extab  >  DDR0
}
