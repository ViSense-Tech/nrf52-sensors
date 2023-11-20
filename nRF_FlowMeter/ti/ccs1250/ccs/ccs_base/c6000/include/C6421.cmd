/****************************************************************************/
/*  C6421.cmd                                                               */
/*  Copyright (c) 2012  Texas Instruments Incorporated                      */
/*  Author: Rafael de Souza                                                 */
/*                                                                          */
/*    Description: This file is a sample linker command file that can be    */
/*                 used for linking programs built with the C compiler and  */
/*                 running the resulting .out file on a C6421.              */
/*                 Use it as a guideline.  You will want to                 */
/*                 change the memory layout to match your specific          */
/*                 target system.  You may want to change the allocation    */
/*                 scheme according to the size of your program.            */
/*                                                                          */
/****************************************************************************/

MEMORY
{
    L2RAM:         o = 0x00810000  l = 0x00010000  /* 64kB L2 RAM/Cache */
    L1PRAM:        o = 0x00E0C000  l = 0x00004000  /* 16kB L1 Program RAM/Cache */
    L1DRAM1:       o = 0x00F0C000  l = 0x00004000  /* 16kB L1 Data RAM */
    L1DRAM2:       o = 0x00F10000  l = 0x00008000  /* 32kB L1 Data RAM/Cache */
    L2SHRAM:       o = 0x10810000  l = 0x00010000  /* 64kB Shared L2 RAM/Cache */
    L1PSHRAM:      o = 0x10E0C000  l = 0x00004000  /* 16kB Shared L1 Program RAM/Cache */
    L1DSHRAM1:     o = 0x10F0C000  l = 0x00004000  /* 16kB Shared L1 Data RAM */
    L1DSHRAM2:     o = 0x10F10000  l = 0x00008000  /* 32kB Shared L1 Data RAM/Cache */
    EMIFA_CS2:     o = 0x42000000  l = 0x01000000  /* 16MB EMIFA CE2 */
    EMIFA_CS3:     o = 0x44000000  l = 0x01000000  /* 16MB EMIFA CE3 */
    EMIFA_CS4:     o = 0x46000000  l = 0x01000000  /* 16MB EMIFA CE4 */
    EMIFA_CS5:     o = 0x48000000  l = 0x01000000  /* 16MB EMIFA CE5 */
    DDR2:          o = 0x80000000  l = 0x10000000  /* 256MB External DDR2 */
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
  
    /* TI-ABI or COFF sections */
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

