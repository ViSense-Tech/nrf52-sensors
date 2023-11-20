/****************************************************************************/
/*  OMAP5432.cmd                                                            */
/*  Copyright (c) 2013  Texas Instruments Incorporated                      */
/*  Author: Rafael de Souza                                                 */
/*                                                                          */
/*    Description: This file is a sample linker command file that can be    */
/*                 used for linking programs built with the C compiler and  */
/*                 running the resulting .out file on an OMAP5432.          */
/*                 Use it as a guideline.  You will want to                 */
/*                 change the memory layout to match your specific          */
/*                 target system.  You may want to change the allocation    */
/*                 scheme according to the size of your program.            */
/*                                                                          */
/****************************************************************************/

MEMORY
{
#ifndef M4_CORE     /* A15 memory map */

    OCMC_RAM        o = 0x40300000  l = 0x00020000  /* 128kB L3 Internal memory */
    EMIF_CS0_SDRAM  o = 0x80000000  l = 0x40000000  /* 1GB external SDRAM memory on CS0 */
    EMIF_CS1_SDRAM  o = 0xC0000000  l = 0x40000000  /* 1GB external SDRAM memory on CS1 */

#else               /* M4 memory map */

    M4ROM           o = 0x55000000  l = 0x00004000  /* 16kB local ROM */
    M4RAM           o = 0x55020000  l = 0x00010000  /* 64kB local RAM */

#endif
}

SECTIONS
{
#ifndef M4_CORE    /* A15 memory map */

    .text          >  OCMC_RAM
    .stack         >  OCMC_RAM
    .bss           >  OCMC_RAM
    .cio           >  OCMC_RAM
    .const         >  OCMC_RAM
    .data          >  OCMC_RAM
    .switch        >  OCMC_RAM
    .sysmem        >  OCMC_RAM
    .far           >  OCMC_RAM
    .args          >  OCMC_RAM
    .ppinfo        >  OCMC_RAM
    .ppdata        >  OCMC_RAM
  
    /* TI-ABI sections */
    .pinit         >  OCMC_RAM
    .cinit         >  OCMC_RAM
  
    /* EABI sections */
    .binit         >  OCMC_RAM
    .init_array    >  OCMC_RAM
    .neardata      >  OCMC_RAM
    .fardata       >  OCMC_RAM
    .rodata        >  OCMC_RAM
    .c6xabi.exidx  >  OCMC_RAM
    .c6xabi.extab  >  OCMC_RAM

#else              /* M4 memory map */

    .text          >  M4RAM
    .stack         >  M4RAM
    .bss           >  M4RAM
    .cio           >  M4RAM
    .const         >  M4RAM
    .data          >  M4RAM
    .switch        >  M4RAM
    .sysmem        >  M4RAM
    .far           >  M4RAM
    .args          >  M4RAM
    .ppinfo        >  M4RAM
    .ppdata        >  M4RAM
  
    /* TI-ABI or COFF sections */
    .pinit         >  M4RAM
    .cinit         >  M4RAM
  
    /* EABI sections */
    .binit         >  M4RAM
    .init_array    >  M4RAM
    .neardata      >  M4RAM
    .fardata       >  M4RAM
    .rodata        >  M4RAM
    .c6xabi.exidx  >  M4RAM
    .c6xabi.extab  >  M4RAM

#endif
}
