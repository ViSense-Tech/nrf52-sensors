/****************************************************************************/
/*  TCI6488_unified.cmd                                                     */
/*  Copyright (c) 2012 Texas Instruments Incorporated                       */
/*  Author: Rafael de Souza                                                 */
/*                                                                          */
/*    Description: This file is a sample linker command file that can be    */
/*                 used for linking programs built with the C compiler and  */
/*                 running the resulting .out file on a TCI6488             */
/*                 device.  Use it as a guideline.  You will want to        */
/*                 change the memory layout to match your specific C6xxx    */
/*                 target system.  You may want to change the allocation    */
/*                 scheme according to the size of your program.            */
/*                                                                          */
/****************************************************************************/

MEMORY
{
    SHL2RAM:  o = 0x10800000  l = 0x00100000  /* 1MB Shared L2 RAM */  
    DDR2:     o = 0x80000000  l = 0x20000000  /* 512MB Shared DDR2 */
}

SECTIONS
{
    .text          >  SHL2RAM
    .stack         >  SHL2RAM
    .bss           >  SHL2RAM
    .cio           >  SHL2RAM
    .const         >  SHL2RAM
    .data          >  SHL2RAM
    .switch        >  SHL2RAM
    .sysmem        >  SHL2RAM
    .far           >  SHL2RAM
    .args          >  SHL2RAM
    .ppinfo        >  SHL2RAM
    .ppdata        >  SHL2RAM
  
    /* COFF sections */
    .pinit         >  SHL2RAM
    .cinit         >  SHL2RAM
  
    /* EABI sections */
    .binit         >  SHL2RAM
    .init_array    >  SHL2RAM
    .neardata      >  SHL2RAM
    .fardata       >  SHL2RAM
    .rodata        >  SHL2RAM
    .c6xabi.exidx  >  SHL2RAM
    .c6xabi.extab  >  SHL2RAM
}
