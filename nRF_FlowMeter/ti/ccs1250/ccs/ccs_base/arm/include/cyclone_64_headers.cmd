
/*
//###########################################################################
//
// FILE:    cyclone_headers.cmd
//
// TITLE:   Cyclone Peripheral registers linker command file 
//
// DESCRIPTION: 
// 
//          Linker command file to place the peripheral structures 
//          used within the Spartan header files into the correct memory
//          mapped locations.
//
//###########################################################################
//
//  Ver  | dd mmm yyyy | Who  | Description of changes
// ======|=============|======|==============================================
//  1.00 | 20 Aug 2009 | CMF  | Started with Spartan version.
//       |             |      | Updated for 1.0 Memory map document.
//       |             |      |
//
//  Texas Instruments, Inc
//  Copyright Texas Instruments 2009. All rights reserved.
//###########################################################################
*/

MEMORY
{
   ERRLOG      : origin = 0xFFF00000, length = 0x04     /* Errlog Registers         */
   LOOP_MUX    : origin = 0x00120000, length = 0x78     /* Loop Mux Registers       */			
   FAULT_MUX   : origin = 0x00130000, length = 0x80     /* Fault Mux Registers      */	
   I2C         : origin = 0xFFF7E400, length = 0x24     /* I2C Registers            */
   SPI         : origin = 0xFFF7E800, length = 0x30     /* SPI Registers            */
   UART0       : origin = 0xFFF7EC00, length = 0x38     /* UART0 Registers          */
   UART1       : origin = 0xFFF7ED00, length = 0x38     /* UART1 Registers          */
   ADC         : origin = 0x00140000, length = 0x98     /* ADC                      */
   DPWM3       : origin = 0x00150000, length = 0x8C     /* DPWM3 Registers          */
   FILTER2     : origin = 0x00160000, length = 0x64     /* Filter 2 Registers       */
   DPWM2       : origin = 0x00170000, length = 0x8C     /* DPWM1 Registers          */
   FE_CTRL2    : origin = 0x00180000, length = 0x44     /* Front End Control 2 Regs */
   FILTER1     : origin = 0x00190000, length = 0x64     /* Filter 1 Registers       */
   DPWM1       : origin = 0x001A0000, length = 0x8C     /* DPWM2 Registers          */
   FE_CTRL1    : origin = 0x001B0000, length = 0x44     /* Front End Control 1 Regs */
   FILTER0     : origin = 0x001C0000, length = 0x64     /* Filter 0 Registers       */ 
   DPWM0       : origin = 0x001D0000, length = 0x8C     /* DPWM3 Registers          */
   FE_CTRL0    : origin = 0x001E0000, length = 0x44		/* Front End Control 0 Regs */
   MISC_ANALOG : origin = 0xFFF7F000, length = 0x48     /* Misc Analog Registers    */
   PMBUS       : origin = 0xFFF7F600, length = 0x24     /* PMBus Registers          */
   GIO         : origin = 0xFFF7FA00, length = 0x40     /* General Purpose I/O      */
   TIMER       : origin = 0xFFF7FD00, length = 0x9C     /* Timer                    */
   MMC         : origin = 0xFFFFFD00, length = 0x3C     /* Memory Controller        */
   DEC         : origin = 0xFFFFFE00, length = 0xA0     /* DEC Address Manager      */
   CIM         : origin = 0xFFFFFF20, length = 0x18     /* Centrl Interrupt Module  */
   SYS         : origin = 0xFFFFFFD0, length = 0x30     /* System Module            */
}

 
SECTIONS
{
   ErrlogRegsFile     : > ERRLOG
   LoopMuxRegsFile    : > LOOP_MUX
   FaultMuxRegsFile   : > FAULT_MUX
   I2CRegsFile        : > I2C	
   SPIRegsFile        : > SPI	
   Uart0RegsFile      : > UART0	
   Uart1RegsFile      : > UART1	
   AdcRegsFile        : > ADC
   Dpwm3RegsFile      : > DPWM3
   Filter2RegsFile    : > FILTER2
   Dpwm2RegsFile      : > DPWM2
   FeCtrl2RegsFile    : > FE_CTRL2
   Filter1RegsFile    : > FILTER1
   Dpwm1RegsFile      : > DPWM1
   FeCtrl1RegsFile    : > FE_CTRL1
   Filter0RegsFile    : > FILTER0
   Dpwm0RegsFile      : > DPWM0
   FeCtrl0RegsFile    : > FE_CTRL0
   MiscAnalogRegsFile : > MISC_ANALOG 
   PMBusRegsFile      : > PMBUS
   GioRegsFile        : > GIO	
   TimerRegsFile      : > TIMER
   CimRegsFile        : > CIM
   DecRegsFile        : > DEC
   MmcRegsFile        : > MMC
   SysRegsFile        : > SYS
}


/*
//===========================================================================
// End of file.
//===========================================================================
*/
