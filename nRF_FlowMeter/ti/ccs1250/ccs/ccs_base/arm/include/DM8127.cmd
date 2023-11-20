/****************************************************************************/
/*  DM8127.cmd                                                              */
/*  Copyright (c) 2018  Texas Instruments Incorporated                      */
/*  Author: Rafael de Souza                                                 */
/*                                                                          */
/*    Description: This file is a sample linker command file that can be    */
/*                 used for linking programs built with the TI compiler     */
/*                 and running the resulting .out file on an dm8127 device. */
/*                 Use it as a guideline.  You will want to                 */
/*                 change the memory layout to match your specific          */
/*                 target system.  You may want to change the allocation    */
/*                 scheme according to the size of your program.            */
/*                                                                          */
/****************************************************************************/

MEMORY
{
    SRAM :     o = 0x402F0400,  l = 0x0000FC00  /* 64kB internal SRAM */
    L3OCMC0 :  o = 0x40300000,  l = 0x00020000  /* 128kB L3 OCMC SRAM */
    DDR0 :     o = 0x80000000,  l = 0x40000000  /* 1GB external DDR Bank 0 */
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
    .fardata       >  DDR0
    .rodata        >  L3OCMC0
}

