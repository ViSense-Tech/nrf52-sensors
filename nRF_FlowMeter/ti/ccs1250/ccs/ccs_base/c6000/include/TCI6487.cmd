/****************************************************************************/
/*  TCI6487.cmd                                                             */
/*  Copyright (c) 2012 Texas Instruments Incorporated                       */
/*  Author: Rafael de Souza                                                 */
/*                                                                          */
/*    Description: This file is a sample linker command file that can be    */
/*                 used for linking programs built with the C compiler and  */
/*                 running the resulting .out file on a TCI6487             */
/*                 device.  Use it as a guideline.  You will want to        */
/*                 change the memory layout to match your specific C6xxx    */
/*                 target system.  You may want to change the allocation    */
/*                 scheme according to the size of your program.            */
/*                                                                          */
/*    Usage:       The map below divides the external memory in segments    */
/*                 Use the linker option --define=COREn=1                   */
/*                 Where n is the core number.                              */
/*                                                                          */
/****************************************************************************/

MEMORY
{
#ifdef CORE0
    CORE0_L2RAM:  o = 0x00800000  l = 0x00100000  /* 1MB Core0 Exclusive L2 RAM */    
#endif
#ifdef CORE1
    CORE1_L2RAM:  o = 0x00800000  l = 0x00100000  /* 1MB Core1 Exclusive L2 RAM */    
#endif
#ifdef CORE2
    CORE2_L2RAM:  o = 0x00800000  l = 0x00100000  /* 1MB Core2 Exclusive L2 RAM */    
#endif
    SHL2RAM:      o = 0x10800000  l = 0x00100000  /* 1MB Shared L2 RAM */  
    CORE0_DDR2:   o = 0x80000000  l = 0x0B000000  /* 184MB DDR2 Core0 */
    CORE1_DDR2:   o = 0x90000000  l = 0x0A800000  /* 176MB DDR2 Core1 */
    CORE2_DDR2:   o = 0x9A800000  l = 0x0A800000  /* 176MB DDR2 Core2 */
}

SECTIONS
{
#ifdef CORE0
    .text          >  CORE0_L2RAM
    .stack         >  CORE0_L2RAM
    .bss           >  CORE0_L2RAM
    .cio           >  CORE0_L2RAM
    .const         >  CORE0_L2RAM
    .data          >  CORE0_L2RAM
    .switch        >  CORE0_L2RAM
    .sysmem        >  CORE0_L2RAM
    .far           >  CORE0_L2RAM
    .args          >  CORE0_L2RAM
    .ppinfo        >  CORE0_L2RAM
    .ppdata        >  CORE0_L2RAM
  
    /* COFF sections */
    .pinit         >  CORE0_L2RAM
    .cinit         >  CORE0_L2RAM
  
    /* EABI sections */
    .binit         >  CORE0_L2RAM
    .init_array    >  CORE0_L2RAM
    .neardata      >  CORE0_L2RAM
    .fardata       >  CORE0_L2RAM
    .rodata        >  CORE0_L2RAM
    .c6xabi.exidx  >  CORE0_L2RAM
    .c6xabi.extab  >  CORE0_L2RAM
#endif

#ifdef CORE1
    .text          >  CORE1_L2RAM
    .stack         >  CORE1_L2RAM
    .bss           >  CORE1_L2RAM
    .cio           >  CORE1_L2RAM
    .const         >  CORE1_L2RAM
    .data          >  CORE1_L2RAM
    .switch        >  CORE1_L2RAM
    .sysmem        >  CORE1_L2RAM
    .far           >  CORE1_L2RAM
    .args          >  CORE1_L2RAM
    .ppinfo        >  CORE1_L2RAM
    .ppdata        >  CORE1_L2RAM
  
    /* COFF sections */
    .pinit         >  CORE1_L2RAM
    .cinit         >  CORE1_L2RAM
  
    /* EABI sections */
    .binit         >  CORE1_L2RAM
    .init_array    >  CORE1_L2RAM
    .neardata      >  CORE1_L2RAM
    .fardata       >  CORE1_L2RAM
    .rodata        >  CORE1_L2RAM
    .c6xabi.exidx  >  CORE1_L2RAM
    .c6xabi.extab  >  CORE1_L2RAM
#endif

#ifdef CORE2
    .text          >  CORE2_L2RAM
    .stack         >  CORE2_L2RAM
    .bss           >  CORE2_L2RAM
    .cio           >  CORE2_L2RAM
    .const         >  CORE2_L2RAM
    .data          >  CORE2_L2RAM
    .switch        >  CORE2_L2RAM
    .sysmem        >  CORE2_L2RAM
    .far           >  CORE2_L2RAM
    .args          >  CORE2_L2RAM
    .ppinfo        >  CORE2_L2RAM
    .ppdata        >  CORE2_L2RAM
  
    /* COFF sections */
    .pinit         >  CORE2_L2RAM
    .cinit         >  CORE2_L2RAM
  
    /* EABI sections */
    .binit         >  CORE2_L2RAM
    .init_array    >  CORE2_L2RAM
    .neardata      >  CORE2_L2RAM
    .fardata       >  CORE2_L2RAM
    .rodata        >  CORE2_L2RAM
    .c6xabi.exidx  >  CORE2_L2RAM
    .c6xabi.extab  >  CORE2_L2RAM
#endif
}
