/****************************************************************************/
/*  DM368.cmd                                                               */
/*  Copyright (c) 2012  Texas Instruments Incorporated                      */
/*  Author: Rafael de Souza                                                 */
/*                                                                          */
/*    Description: This file is a sample linker command file that can be    */
/*                 used for linking programs built with the C compiler and  */
/*                 running the resulting .out file on an DM368 EVM.         */
/*                 Use it as a guideline.  You will want to                 */
/*                 change the memory layout to match your specific          */
/*                 target system.  You may want to change the allocation    */
/*                 scheme according to the size of your program.            */
/*                                                                          */
/****************************************************************************/

MEMORY
{
    ARM_IRAM0    o = 0x00000000  l = 0x00004000  /* ARM Instruction RAM0 - 16kB */
    ARM_IRAM1    o = 0x00004000  l = 0x00004000  /* ARM Instruction RAM1 - 16kB */
    ARM_IROM     o = 0x00008000  l = 0x00004000  /* ARM Instruction ROM - 16kB  */
    ARM_DRAM0    o = 0x00010000  l = 0x00004000  /* ARM Data RAM0 - 16kB */
    ARM_DRAM1    o = 0x00014000  l = 0x00004000  /* ARM Data RAM1 - 16kB */
    ARM_DROM     o = 0x00018000  l = 0x00004000  /* ARM Data ROM - 16kB  */
    ARM_METB     o = 0x01BC0000  l = 0x00001000  /* ARM ETB Memory - 4kB */
    ARM_RETB     o = 0x01BC1000  l = 0x00000800  /* ARM ETB Registers - 2kB */
    ARM_ICECRSH  o = 0x01BC1800  l = 0x00000100  /* ARM IceCrusher - 256B */
    ARM_CFGBUS   o = 0x01C00000  l = 0x00400000  /* CFG Bus Peripherals - 4MB */
    ARM_DAEMIF   o = 0x02000000  l = 0x08000000  /* ASYNC EMIF Data - 128MB */
    ARM_MJCPD    o = 0x11F00000  l = 0x00020000  /* MJCP DMA Port - 128kB */
    ARM_HDVICPD  o = 0x12000000  l = 0x00080000  /* HDVICP DMA Port - 512kB */
    ARM_RDDR     o = 0x20000000  l = 0x00008000  /* DDR EMIF Control Registers - 32kB */
    ARM_DDR      o = 0x80000000  l = 0x10000000  /* DDR EMIF - 256MB */

} 

SECTIONS
{
    .text          >  ARM_DDR
    .stack         >  ARM_DDR
    .bss           >  ARM_DDR
    .cio           >  ARM_DDR
    .const         >  ARM_DDR
    .data          >  ARM_DDR
    .switch        >  ARM_DDR
    .sysmem        >  ARM_DDR
    .far           >  ARM_DDR
    .args          >  ARM_DDR
    .ppinfo        >  ARM_DDR
    .ppdata        >  ARM_DDR
  
    /* TI-ABI sections */
    .pinit         >  ARM_DDR
    .cinit         >  ARM_DDR
  
    /* EABI sections */
    .binit         >  ARM_DDR
    .init_array    >  ARM_DDR
    .neardata      >  ARM_DDR
    .fardata       >  ARM_DDR
    .rodata        >  ARM_DDR
    .c6xabi.exidx  >  ARM_DDR
    .c6xabi.extab  >  ARM_DDR
}
