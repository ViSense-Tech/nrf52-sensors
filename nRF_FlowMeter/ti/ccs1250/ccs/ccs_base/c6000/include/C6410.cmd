/****************************************************************************/
/*  C6410.cmd                                                               */
/*  Copyright (c) 2012 Texas Instruments Incorporated                       */
/*  Author: Rafael de Souza                                                 */
/*                                                                          */
/*    Description: This file is a sample linker command file that can be    */
/*                 used for linking programs built with the C compiler and  */
/*                 running the resulting .out file on an TMS320C6410        */
/*                 device.  Use it as a guideline.  You will want to        */
/*                 change the memory layout to match your specific C6xxx    */
/*                 target system.  You may want to change the allocation    */
/*                 scheme according to the size of your program.            */
/*                                                                          */
/****************************************************************************/

MEMORY
{
    L2RAM:     o = 0x00000000  l = 0x00020000  /* 128kB L2 Internal RAM */
    EMIFACE0:  o = 0x80000000  l = 0x08000000  /* 128MB EMIFA CE0 */
    EMIFACE1:  o = 0x90000000  l = 0x08000000  /* 128MB EMIFA CE1 */
    EMIFACE2:  o = 0xA0000000  l = 0x08000000  /* 128MB EMIFA CE2 */
    EMIFACE3:  o = 0xB0000000  l = 0x08000000  /* 128MB EMIFA CE3 */
}

SECTIONS
{
    .text          >  L2RAM
    .stack         >  L2RAM
    .bss           >  L2RAM
    .cio           >  L2RAM
    .const         >  L2RAM
    .data          >  L2RAM
    .switch        >  L2RAM
    .sysmem        >  L2RAM
    .far           >  L2RAM
    .args          >  L2RAM
    .ppinfo        >  L2RAM
    .ppdata        >  L2RAM
  
    /* COFF sections */
    .pinit         >  L2RAM
    .cinit         >  L2RAM
  
    /* EABI sections */
    .binit         >  L2RAM
    .init_array    >  L2RAM
    .neardata      >  L2RAM
    .fardata       >  L2RAM
    .rodata        >  L2RAM
    .c6xabi.exidx  >  L2RAM
    .c6xabi.extab  >  L2RAM
}
