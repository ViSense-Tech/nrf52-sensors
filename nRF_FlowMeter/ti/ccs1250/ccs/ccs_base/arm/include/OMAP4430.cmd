/****************************************************************************/
/*  OMAP4430.cmd                                                            */
/*  Copyright (c) 2011  Texas Instruments Incorporated                      */
/*  Author: Rafael de Souza                                                 */
/*                                                                          */
/*    Description: This file is a sample linker command file that can be    */
/*                 used for linking programs built with the C compiler and  */
/*                 running the resulting .out file on an OMAP4430.          */
/*                 Use it as a guideline.  You will want to                 */
/*                 change the memory layout to match your specific          */
/*                 target system.  You may want to change the allocation    */
/*                 scheme according to the size of your program.            */
/*                                                                          */
/****************************************************************************/

MEMORY
{
#ifndef M3_CORE     /* A9 memory map */

    L3_OCM_RAM      o = 0x40300000  l = 0x0000E000  /* 56kB L3 Internal memory */
    EMIF_CS0_SDRAM  o = 0x80000000  l = 0x10000000  /* 1GB external SDRAM memory on CS0 */
    EMIF_CS1_SDRAM  o = 0xC0000000  l = 0x10000000  /* 1GB external SDRAM memory on CS1 */

#else               /* M3 memory map */

    M3ROM           o = 0x55000000  l = 0x00004000  /* 16kB local ROM */
    M3RAM           o = 0x55020000  l = 0x00010000  /* 64kB local RAM */

#endif
}

SECTIONS
{
#ifndef M3_CORE    /* A9 memory map */

    .text          >  L3_OCM_RAM
    .stack         >  L3_OCM_RAM
    .bss           >  L3_OCM_RAM
    .cio           >  L3_OCM_RAM
    .const         >  L3_OCM_RAM
    .data          >  L3_OCM_RAM
    .switch        >  L3_OCM_RAM
    .sysmem        >  L3_OCM_RAM
    .far           >  L3_OCM_RAM
    .args          >  L3_OCM_RAM
    .ppinfo        >  L3_OCM_RAM
    .ppdata        >  L3_OCM_RAM
  
    /* TI-ABI sections */
    .pinit         >  L3_OCM_RAM
    .cinit         >  L3_OCM_RAM
  
    /* EABI sections */
    .binit         >  L3_OCM_RAM
    .init_array    >  L3_OCM_RAM
    .neardata      >  L3_OCM_RAM
    .fardata       >  L3_OCM_RAM
    .rodata        >  L3_OCM_RAM
    .c6xabi.exidx  >  L3_OCM_RAM
    .c6xabi.extab  >  L3_OCM_RAM

#else              /* M3 memory map */

    .text          >  M3RAM
    .stack         >  M3RAM
    .bss           >  M3RAM
    .cio           >  M3RAM
    .const         >  M3RAM
    .data          >  M3RAM
    .switch        >  M3RAM
    .sysmem        >  M3RAM
    .far           >  M3RAM
    .args          >  M3RAM
    .ppinfo        >  M3RAM
    .ppdata        >  M3RAM
  
    /* TI-ABI or COFF sections */
    .pinit         >  M3RAM
    .cinit         >  M3RAM
  
    /* EABI sections */
    .binit         >  M3RAM
    .init_array    >  M3RAM
    .neardata      >  M3RAM
    .fardata       >  M3RAM
    .rodata        >  M3RAM
    .c6xabi.exidx  >  M3RAM
    .c6xabi.extab  >  M3RAM

#endif
}
