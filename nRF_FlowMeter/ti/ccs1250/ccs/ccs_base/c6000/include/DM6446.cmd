/****************************************************************************/
/*  DM6446.cmd                                                              */
/*  Copyright (c) 2009  Texas Instruments Incorporated                      */
/*  Author: Rafael de Souza                                                 */
/*                                                                          */
/*    Description: This file is a sample linker command file that can be    */
/*                 used for linking programs built with the C compiler and  */
/*                 running the resulting .out file on a DM6446.             */
/*                 Use it as a guideline.  You will want to                 */
/*                 change the memory layout to match your specific          */
/*                 target system.  You may want to change the allocation    */
/*                 scheme according to the size of your program.            */
/*                                                                          */
/****************************************************************************/

MEMORY
{
#ifndef DSP_CORE   /* ARM exclusive memory regions */

    ARM_IRAM:      o = 0x00000000  l = 0x00004000  /* 16kB Internal ARM instruction RAM */
    ARM_IROM:      o = 0x00004000  l = 0x00002000  /* 8kB Internal ARM instruction ROM */
    ARM_DRAM:      o = 0x00008000  l = 0x00004000  /* 16kB Internal ARM data RAM */
    ARM_DROM:      o = 0x0000C000  l = 0x00002000  /* 8kB Internal ARM data ROM */

#endif
#ifdef DSP_CORE    /* DSP exclusive memory regions */

    DSP_L2:        o = 0x00800000  l = 0x00010000  /* 64kB DSP L2 RAM/CACHE */
    DSP_L1P:       o = 0x00E08000  l = 0x00008000  /* 32kB DSP L1 Program CACHE */
    DSP_L1D:       o = 0x00F04000  l = 0x0000B000  /* 48kB DSP L1 Data RAM */
    DSP_L1D_C:     o = 0x00F10000  l = 0x00008000  /* 32kB DSP L1 Data CACHE */
    SH_ARM_DRAM:   o = 0x10008000  l = 0x00004000  /* 16kB Shared Internal ARM data RAM */
    SH_ARM_DROM:   o = 0x1000C000  l = 0x00002000  /* 8kB Shared Internal ARM data ROM */

#endif
    EMIFA:         o = 0x02000000  l = 0x08000000  /* 128MB EMIFA ARM Code/Data - DSP Data*/
    SH_DSP_L2:     o = 0x11800000  l = 0x00010000  /* 64kB Shared DSP L2 RAM/CACHE */
    SH_DSP_L1P:    o = 0x11E08000  l = 0x00008000  /* 32kB Shared DSP L1 Program CACHE */
    SH_DSP_L1D:    o = 0x11F04000  l = 0x0000B000  /* 48kB Shared DSP L1 Data RAM */
    SH_DSP_L1D_C:  o = 0x11F10000  l = 0x00008000  /* 32kB Shared DSP L1 Data CACHE */
    EMIFA_CS2:     o = 0x42000000  l = 0x08000000  /* 128MB EMIFA DSP Shadow - Code/Data */
    DDR2:          o = 0x80000000  l = 0x10000000  /* 256MB of external DDR */
} 

SECTIONS
{
    .text          >  DDR2
    .stack         >  DDR2
    .bss           >  DDR2
    .cio           >  DDR2
    .const         >  DDR2
    .data          >  DDR2
    .switch        >  DDR2
    .sysmem        >  DDR2
    .far           >  DDR2
    .args          >  DDR2
    .ppinfo        >  DDR2
    .ppdata        >  DDR2
  
    /* TI-ABI or COFF sections */
    .pinit         >  DDR2
    .cinit         >  DDR2
  
    /* EABI sections */
    .binit         >  DDR2
    .init_array    >  DDR2
    .neardata      >  DDR2
    .fardata       >  DDR2
    .rodata        >  DDR2
    .c6xabi.exidx  >  DDR2
    .c6xabi.extab  >  DDR2
}

