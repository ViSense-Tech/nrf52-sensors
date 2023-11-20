/****************************************************************************/
/*  AM3894.cmd                                                              */
/*  Copyright (c) 2012  Texas Instruments Incorporated                      */
/*  Author: Rafael de Souza                                                 */
/*                                                                          */
/*    Description: This file is a sample linker command file that can be    */
/*                 used for linking programs built with the C compiler and  */
/*                 running the resulting .out file on an AM3894.            */
/*                 Use it as a guideline.  You will want to                 */
/*                 change the memory layout to match your specific          */
/*                 target system.  You may want to change the allocation    */
/*                 scheme according to the size of your program.            */
/*                                                                          */
/****************************************************************************/

MEMORY
{
    L3OCMC0:  o = 0x40300000  l = 0x00040000  /* 256kB L3 OCMC SRAM */
    L3OCMC1:  o = 0x40400000  l = 0x00040000  /* 256kB L3 OCMC SRAM */
    DDR0:     o = 0x80000000  l = 0x40000000  /* 1GB external DDR Bank 0 */
    DDR1:     o = 0xC0000000  l = 0x40000000  /* 1GB external DDR Bank 1 */
}

SECTIONS
{
    .text          >  L3OCMC0
    .stack         >  L3OCMC0
    .bss           >  L3OCMC0
    .cio           >  L3OCMC0
    .const         >  L3OCMC0
    .data          >  L3OCMC0
    .switch        >  L3OCMC0
    .sysmem        >  L3OCMC0
    .far           >  L3OCMC0
    .args          >  L3OCMC0
    .ppinfo        >  L3OCMC0
    .ppdata        >  L3OCMC0
  
    /* TI-ABI or COFF sections */
    .pinit         >  L3OCMC0
    .cinit         >  L3OCMC0
  
    /* EABI sections */
    .binit         >  L3OCMC0
    .init_array    >  L3OCMC0
    .neardata      >  L3OCMC0
    .fardata       >  L3OCMC0
    .rodata        >  L3OCMC0
    .c6xabi.exidx  >  L3OCMC0
    .c6xabi.extab  >  L3OCMC0
}
