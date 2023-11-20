//*****************************************************************************
//
// startup_ccs.c - Startup code for use with TI's Code Composer Studio.
//
// Copyright (c) 2009-2012 Texas Instruments Incorporated.  All rights reserved.
// Software License Agreement
// 
// Texas Instruments (TI) is supplying this software for use solely and
// exclusively on TI's microcontroller products. The software is owned by
// TI and/or its suppliers, and is protected under applicable copyright
// laws. You may not combine this software with "viral" open-source
// software in order to form a larger program.
// 
// THIS SOFTWARE IS PROVIDED "AS IS" AND WITH ALL FAULTS.
// NO WARRANTIES, WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING, BUT
// NOT LIMITED TO, IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE. TI SHALL NOT, UNDER ANY
// CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL, OR CONSEQUENTIAL
// DAMAGES, FOR ANY REASON WHATSOEVER.
// 
// This is part of revision 9453 of the DK-LM3S9D96 Firmware Package.
//
//*****************************************************************************

//*****************************************************************************
//
// Forward declaration of the default fault handlers.
//
//*****************************************************************************
#include "pga900.h"

void ResetISR(void);
static void NmiSR(void);
static void FaultISR(void);
static void IntDefaultHandler(void);

//*****************************************************************************
//
// External declaration for the reset handler that is to be called when the
// processor is started
//
//*****************************************************************************
extern void _c_int00(void);
//*****************************************************************************
//
// Linker variable that marks the top of the stack.
//
//*****************************************************************************
extern unsigned long __STACK_TOP;

//*****************************************************************************
//
// The vector table.  Note that the proper constructs must be placed on this to
// ensure that it ends up at physical address 0x0000.0000 or at the start of
// the program if located at a start address other than 0.
//
//*****************************************************************************
#pragma DATA_SECTION(g_pfnVectors, ".intvecs")
void (* const g_pfnVectors[])(void) =
{
   (void (*)(void))((unsigned long)&__STACK_TOP),
                                           // The initial stack pointer
   ResetISR,                               // The reset handler
   NmiSR,                                  // The NMI handler
   FaultISR,                               // The hard fault handler
   IntDefaultHandler,                      // The MPU fault handler
   IntDefaultHandler,                      // The bus fault handler
   IntDefaultHandler,                      // The usage fault handler
   0,                                      // Reserved
   0,                                      // Reserved
   0,                                      // Reserved
   0,                                      // Reserved
   IntDefaultHandler,                      // SVCall handler
   IntDefaultHandler,                      // Debug monitor handler
   0,                                      // Reserved
   IntDefaultHandler,                      // The PendSV handler
   IntDefaultHandler,                      // The M0 System timer handler
   IntDefaultHandler,                      // PADC handler
   IntDefaultHandler,                      // TADC handler
   IntDefaultHandler,                      // OWI Activation handler
   IntDefaultHandler,                      // COMBUF RX handler
   IntDefaultHandler,                      // UART handler
   IntDefaultHandler,                      //
   IntDefaultHandler,                      //
   IntDefaultHandler,                      //
   IntDefaultHandler,                      //
   IntDefaultHandler,                      //
   IntDefaultHandler,                      //
   IntDefaultHandler,                      //
   IntDefaultHandler,                      //
   IntDefaultHandler,                      //
   IntDefaultHandler,                      //
   IntDefaultHandler,                      //
   IntDefaultHandler,                      //
   IntDefaultHandler,                      //
   IntDefaultHandler,                      //
   IntDefaultHandler,                      //
   IntDefaultHandler,                      //
   IntDefaultHandler,                      //
   IntDefaultHandler,                      //
   IntDefaultHandler,                      //
   IntDefaultHandler,                      //
   IntDefaultHandler,                      //
   IntDefaultHandler,                      //
   IntDefaultHandler,                      //
   IntDefaultHandler,                      //
   IntDefaultHandler,                      //
   IntDefaultHandler,                      //
   IntDefaultHandler,                      //
};

//*****************************************************************************
//
// This is the code that gets called when the processor first starts execution
// following a reset event.  Only the absolutely necessary set is performed,
// after which the application supplied entry() routine is called.  Any fancy
// actions (such as making decisions based on the reset cause register, and
// resetting the bits in that register) are left solely in the hands of the
// application.
//
//*****************************************************************************
void
ResetISR(void)
{
   //
   // Jump to the CCS C initialization routine.
   //
   __asm("    .global _c_int00\n"
         "    bl     _c_int00");
}

//*****************************************************************************
//
// This is the code that gets called when the processor receives a NMI.  This
// simply enters an infinite loop, preserving the system state for examination
// by a debugger.
//
//*****************************************************************************
static void
NmiSR(void)
{
   //
   // Enter an infinite loop.
   //
   while(1)
   {
   }
}

//*****************************************************************************
//
// This is the code that gets called when the processor receives a fault
// interrupt.  This simply enters an infinite loop, preserving the system state
// for examination by a debugger.
//
//*****************************************************************************
static void
FaultISR(void)
{
   //
   // Enter an infinite loop.
   //
   while(1)
   {
   }
}

//*****************************************************************************
//
// This is the code that gets called when the processor receives an unexpected
// interrupt.  This simply enters an infinite loop, preserving the system state
// for examination by a debugger.
//
//*****************************************************************************
static void
IntDefaultHandler(void)
{
   //
   // Go into an infinite loop.
   //
   while(1)
   {
   }
}
