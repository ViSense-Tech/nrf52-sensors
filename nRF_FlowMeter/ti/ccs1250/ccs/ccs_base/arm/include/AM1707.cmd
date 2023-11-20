/****************************************************************************/
/*  AM1707.cmd                                                              */
/*  Copyright (c) 2010 Texas Instruments Incorporated                       */
/*  Author: Rafael de Souza                                                 */
/*                                                                          */
/*    Description: This file is a sample linker command file that can be    */
/*                 used for linking programs built with the C compiler and  */
/*                 running the resulting .out file on an AM1707             */
/*                 device.  Use it as a guideline.  You will want to        */
/*                 change the memory layout to match your specific          */
/*                 target system.  You may want to change the allocation    */
/*                 scheme according to the size of your program.            */
/*                                                                          */
/****************************************************************************/

MEMORY
{
    EMIFASDRAM:  o = 0x40000000  l = 0x20000000  /* 64MB SDRAM Data (CS0) */ 
    EMIFACS2:    o = 0x60000000  l = 0x02000000  /* 32MB Async Data (CS2) */ 
    EMIFACS3:    o = 0x62000000  l = 0x02000000  /* 32MB Async Data (CS3) */ 
    EMIFACS4:    o = 0x64000000  l = 0x02000000  /* 32MB Async Data (CS4) */ 
    EMIFACS5:    o = 0x66000000  l = 0x02000000  /* 32MB Async Data (CS5) */ 
    SHRAM:       o = 0x80000000  l = 0x00020000  /* 128kB Shared RAM */      
    EMIFBSDRAM:  o = 0xC0000000  l = 0x20000000  /* 256MB SDRAM Data */      
    ARMRAM:      o = 0xFFFF0000  l = 0x00002000  /* 8kB ARM local RAM */     
}

SECTIONS
{
    .text          >  SHRAM
    .stack         >  SHRAM
    .bss           >  SHRAM
    .cio           >  SHRAM
    .const         >  SHRAM
    .data          >  SHRAM
    .switch        >  SHRAM
    .sysmem        >  SHRAM
    .far           >  SHRAM
    .args          >  SHRAM
    .ppinfo        >  SHRAM
    .ppdata        >  SHRAM
  
      /* TI-ABI sections */
    .pinit         >  SHRAM
    .cinit         >  SHRAM
  
      /* EABI sections */
    .binit         >  SHRAM
    .init_array    >  SHRAM
    .neardata      >  SHRAM
    .fardata       >  SHRAM
    .rodata        >  SHRAM
    .c6xabi.exidx  >  SHRAM
    .c6xabi.extab  >  SHRAM
}
