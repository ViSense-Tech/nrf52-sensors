/****************************************************************************/
/*  VC5561.cmd                                                              */
/*  Copyright (c) 2012  Texas Instruments Incorporated                      */
/*  Author: Rafael de Souza                                                 */
/*                                                                          */
/*    Description: This file is a sample linker command file that can be    */
/*                 used for linking programs built with the C compiler and  */
/*                 running the resulting .out file on a VC5561              */
/*                 Use it as a guideline.  You will want to                 */
/*                 change the memory layout to match your specific          */
/*                 target system.  You may want to change the allocation    */
/*                 scheme according to the size of your program.            */
/*                                                                          */
/****************************************************************************/

MEMORY
{
    DARAM0:   o = 0x000000  l = 0x004000  /* 16kB Dual Access RAM 0 */
    DARAM1:   o = 0x004000  l = 0x004000  /* 16kB Dual Access RAM 1 */
    DARAM2:   o = 0x008000  l = 0x004000  /* 16kB Dual Access RAM 2 */
    DARAM3:   o = 0x00C000  l = 0x004000  /* 16kB Dual Access RAM 3 */  

    SARAM0:   o = 0x010000  l = 0x010000  /* 64kB Single Access RAM 0 */
    SARAM1:   o = 0x020000  l = 0x010000  /* 64kB Single Access RAM 1 */
    SARAM2:   o = 0x030000  l = 0x010000  /* 64kB Single Access RAM 2 */
    SARAM3:   o = 0x040000  l = 0x010000  /* 64kB Single Access RAM 3 */  
    SARAM4:   o = 0x050000  l = 0x010000  /* 64kB Single Access RAM 4 */
                    
    SHRAM:    o = 0x050000  l = 0x3B0000  /* 768kB Shared RAM */
    ROM:      o = 0xFFF000  l = 0x000F00  /* 4kB ROM (MP/MC=0) */
    VECS:     o = 0xFFFF00  l = 0x000100  /* reset vector */
}                   
                    
SECTIONS            
{                   
    vectors (NOLOAD)  >  VECS  /* If MPNMC = 1, remove the NOLOAD directive */
    .cinit            >  DARAM0
	/* Arbitrary assignment of memory segments to .text section.   */
	/* Can be expanded or reduced observing limitations of SPRAA46 */ 
    .text             >> SARAM0|SARAM1|SARAM2|SARAM3|SARAM4 
    .stack            >  DARAM0
    .sysstack         >  DARAM0
    .sysmem           >  DARAM2
    .data             >  DARAM2
    .cio              >  DARAM0
    .bss              >  DARAM3
    .const            >  DARAM0
}
