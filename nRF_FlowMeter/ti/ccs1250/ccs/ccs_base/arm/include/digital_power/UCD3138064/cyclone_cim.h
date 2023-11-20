//###########################################################################
//
// FILE:   cyclone_cim.h
//
// TITLE:  Cyclone Central Interrupt Module Register Definitions.
//
// NOTES:
//  1) Bitfields have been defined for big-endian only.
//###########################################################################
//
//  Ver  | dd mmm yyyy | Who  | Description of changes
// ======|=============|======|==============================================
//  1.00 | 12 Aug 2009 | CMF  | Started with Spartan_Cim.h.
//       |             |      | Updated for 1.0 Memory map document.
//  2.00 | 13 Jun 2011 | FW   | Updated for 2p0 Memory map document; 
//                            | Added Interrupt names.
//
//  Texas Instruments, Inc
//  Copyright Texas Instruments 2008. All rights reserved.
//###########################################################################

#ifndef CYCLONE_CIM_H
#define CYCLONE_CIM_H

#ifdef __cplusplus
extern "C" {
#endif


//===========================================================================
// Central Interrupt Module Individual Register Bit Definitions
//

//-------------------------------------------------
// IRQ Index Offset Vector Register bit definitions
//
struct IRQIVEC_BITS {             // bits   description
   Uint32 rsvd0:24;               // 31:8   reserved
   Uint32 IRQIVEC:8;              // 7:0    Index vector
};
union IRQIVEC_REG {
   Uint32                 all;
   struct IRQIVEC_BITS    bit;
};

//-------------------------------------------------
// FIQ Index Offset Vector Register bit definitions
//
struct FIQIVEC_BITS {             // bits   description
   Uint32 rsvd0:24;               // 31:8   reserved
   Uint32 FIQIVEC:8;              // 7:0    Index vector
};
union FIQIVEC_REG {
   Uint32                 all;
   struct FIQIVEC_BITS    bit;
};

//-------------------------------------------------
// FIQ/IRQ Program Control Register bit definitions
//
struct FIRQPR_BITS {                   // bits   description
   Uint32 FIRQ_SYS_SOFT:1;             // 31     Interrupt 31, System Software Interrupt
   Uint32 FIRQ_FAULT_PIN:1;            // 30     Interrupt 30, Fault Pin Interrupt
   Uint32 FIRQ_DPWM0:1;                // 29     Interrupt 29, Every(1-16)DPWM0 switching cycles or CLF flag shutdown Interrupt
   Uint32 FIRQ_DPWM1:1;                // 28     Interrupt 28, Every(1-16)DPWM1 switching cycles or CLF flag shutdown Interrupt
   Uint32 FIRQ_DPWM2:1;                // 27     Interrupt 27, Every(1-16)DPWM2 switching cycles or CLF flag shutdown Interrupt
   Uint32 FIRQ_DPWM3:1;                // 26     Interrupt 26, Every(1-16)DPWM3 switching cycles or CLF flag shutdown Interrupt
   Uint32 FIRQ_FAULT_MUX:1;            // 25     Interrupt 25, Fault Mux Interrupt
   Uint32 FIRQ_ADC_CONV:1;             // 24     Interrupt 24, ADC-12 End of Conversion Interrupt
   Uint32 FIRQ_CPCC:1;                 // 23     Interrupt 23, CPCC Interrupt, Mode switched in CPCC module Flag needs to be read for details
   Uint32 FIRQ_TMR_COMP0:1;            // 22     Interrupt 22, 24-bit Timer Compare 0 interrupt
   Uint32 FIRQ_TMR_CAPT0:1;            // 21     Interrupt 21, 24-bit Timer Capture 0 interrupt
   Uint32 FIRQ_TMR_COMP1:1;            // 20     Interrupt 20, 24-bit Timer Compare 1 interrupt
   Uint32 FIRQ_TMR_CAPT1:1;            // 19     Interrupt 19, 24-bit Timer Capture 1 interrupt
   Uint32 FIRQ_TMR_OVFL:1;             // 18     Interrupt 18, 24-bit Timer counter overflow interrupt
   Uint32 FIRQ_PWM0_COMP:1;            // 17     Interrupt 17, 16-bit Timer PWM0 counter overflow or Compare interrupt
   Uint32 FIRQ_PWM1_COMP:1;            // 16     Interrupt 16, 16-bit Timer PWM1 counter overflow or Compare interrupt
   Uint32 FIRQ_PWM2_COMP:1;            // 15     Interrupt 15, 16-bit Timer PWM2 counter overflow or Compare interrupt
   Uint32 FIRQ_PWM3_COMP:1;            // 14     Interrupt 14, 16-bit Timer PWM3 counter overflow or Compare interrupt
   Uint32 FIRQ_FRONT_END2:1;           // 13     Interrupt 13, Front End 2 Interrupt
   Uint32 FIRQ_FRONT_END1:1;           // 12     Interrupt 12, Front End 1 Interrupt
   Uint32 FIRQ_FRONT_END0:1;           // 11     Interrupt 11, Front End 0 Interrupt
   Uint32 FIRQ_DIGI_COMP:1;            // 10     Interrupt 10, Digital comparator interrupt
   Uint32 FIRQ_PMBUS:1;                // 9      Interrupt 9, PMBus related interrupt
   Uint32 FIRQ_UART2_TX:1;             // 8      Interrupt 8, UART2 TX buffer empty
   Uint32 FIRQ_UART2_RX:1;             // 7      Interrupt 7, UART2 RX buffer has a byte
   Uint32 FIRQ_UART1_TX:1;             // 6      Interrupt 6, UART1 TX buffer empty
   Uint32 FIRQ_UART1_RX:1;             // 5      Interrupt 5, UART1 RX buffer has a byte
   Uint32 FIRQ_UART_ERR:1;             // 4      Interrupt 4, UART or SCI error Interrupt. Frame, parity or Overrun
   Uint32 FIRQ_WTDG_WAKE:1;            // 3      Interrupt 3, Wakeup interrupt when watchdog equals half of set watch time
   Uint32 FIRQ_WTDG_RSET:1;            // 2      Interrupt 2, Interrupt from watchdog exceeded (reset)
   Uint32 FIRQ_EXT_INT:1;              // 1      Interrupt 1, Interrupt on one or all external input pins
   Uint32 FIRQ_BRWN_OUT:1;             // 0      Interrupt 0, Brownout interrupt
};
union FIRQPR_REG {
   Uint32                 all;
   struct FIRQPR_BITS     bit;
};

//-------------------------------------------------
// Pending Interrupt Read Location Register bit definitions
//
struct INTREQ_BITS {                     // bits   description
   Uint32 INTREQ_SYS_SOFT:1;             // 31     Interrupt 31, System Software Interrupt
   Uint32 INTREQ_FAULT_PIN:1;            // 30     Interrupt 30, Fault Pin Interrupt
   Uint32 INTREQ_DPWM0:1;                // 29     Interrupt 29, Every(1-16)DPWM0 switching cycles or CLF flag shutdown Interrupt
   Uint32 INTREQ_DPWM1:1;                // 28     Interrupt 28, Every(1-16)DPWM1 switching cycles or CLF flag shutdown Interrupt
   Uint32 INTREQ_DPWM2:1;                // 27     Interrupt 27, Every(1-16)DPWM2 switching cycles or CLF flag shutdown Interrupt
   Uint32 INTREQ_DPWM3:1;                // 26     Interrupt 26, Every(1-16)DPWM3 switching cycles or CLF flag shutdown Interrupt
   Uint32 INTREQ_FAULT_MUX:1;            // 25     Interrupt 25, Fault Mux Interrupt
   Uint32 INTREQ_ADC_CONV:1;             // 24     Interrupt 24, ADC-12 End of Conversion Interrupt
   Uint32 INTREQ_CPCC:1;                 // 23     Interrupt 23, CPCC Interrupt, Mode switched in CPCC module Flag needs to be read for details
   Uint32 INTREQ_TMR_COMP0:1;            // 22     Interrupt 22, 24-bit Timer Compare 0 interrupt
   Uint32 INTREQ_TMR_CAPT0:1;            // 21     Interrupt 21, 24-bit Timer Capture 0 interrupt
   Uint32 INTREQ_TMR_COMP1:1;            // 20     Interrupt 20, 24-bit Timer Compare 1 interrupt
   Uint32 INTREQ_TMR_CAPT1:1;            // 19     Interrupt 19, 24-bit Timer Capture 1 interrupt
   Uint32 INTREQ_TMR_OVFL:1;             // 18     Interrupt 18, 24-bit Timer counter overflow interrupt
   Uint32 INTREQ_PWM0_COMP:1;            // 17     Interrupt 17, 16-bit Timer PWM0 counter overflow or Compare interrupt
   Uint32 INTREQ_PWM1_COMP:1;            // 16     Interrupt 16, 16-bit Timer PWM1 counter overflow or Compare interrupt
   Uint32 INTREQ_PWM2_COMP:1;            // 15     Interrupt 15, 16-bit Timer PWM2 counter overflow or Compare interrupt
   Uint32 INTREQ_PWM3_COMP:1;            // 14     Interrupt 14, 16-bit Timer PWM3 counter overflow or Compare interrupt
   Uint32 INTREQ_FRONT_END2:1;           // 13     Interrupt 13, Front End 2 Interrupt
   Uint32 INTREQ_FRONT_END1:1;           // 12     Interrupt 12, Front End 1 Interrupt
   Uint32 INTREQ_FRONT_END0:1;           // 11     Interrupt 11, Front End 0 Interrupt
   Uint32 INTREQ_DIGI_COMP:1;            // 10     Interrupt 10, Digital comparator interrupt
   Uint32 INTREQ_PMBUS:1;                // 9      Interrupt 9, PMBus related interrupt
   Uint32 INTREQ_UART2_TX:1;             // 8      Interrupt 8, UART2 TX buffer empty
   Uint32 INTREQ_UART2_RX:1;             // 7      Interrupt 7, UART2 RX buffer has a byte
   Uint32 INTREQ_UART1_TX:1;             // 6      Interrupt 6, UART1 TX buffer empty
   Uint32 INTREQ_UART1_RX:1;             // 5      Interrupt 5, UART1 RX buffer has a byte
   Uint32 INTREQ_UART_ERR:1;             // 4      Interrupt 4, UART or SCI error Interrupt. Frame, parity or Overrun
   Uint32 INTREQ_WTDG_WAKE:1;            // 3      Interrupt 3, Wakeup interrupt when watchdog equals half of set watch time
   Uint32 INTREQ_WTDG_RSET:1;            // 2      Interrupt 2, Interrupt from watchdog exceeded (reset)
   Uint32 INTREQ_EXT_INT:1;              // 1      Interrupt 1, Interrupt on one or all external input pins
   Uint32 INTREQ_BRWN_OUT:1;             // 0      Interrupt 0, Brownout interrupt
};
union INTREQ_REG {
   Uint32                 all;
   struct INTREQ_BITS     bit;
};

//-------------------------------------------------
// Interrupt Request Mask Register bit definitions
//
struct REQMASK_BITS {             // bits   description
   Uint32 REQMASK_SYS_SOFT:1;             // 31     Interrupt 31, System Software Interrupt
   Uint32 REQMASK_FAULT_PIN:1;            // 30     Interrupt 30, Fault Pin Interrupt
   Uint32 REQMASK_DPWM0:1;                // 29     Interrupt 29, Every(1-16)DPWM0 switching cycles or CLF flag shutdown Interrupt
   Uint32 REQMASK_DPWM1:1;                // 28     Interrupt 28, Every(1-16)DPWM1 switching cycles or CLF flag shutdown Interrupt
   Uint32 REQMASK_DPWM2:1;                // 27     Interrupt 27, Every(1-16)DPWM2 switching cycles or CLF flag shutdown Interrupt
   Uint32 REQMASK_DPWM3:1;                // 26     Interrupt 26, Every(1-16)DPWM3 switching cycles or CLF flag shutdown Interrupt
   Uint32 REQMASK_FAULT_MUX:1;            // 25     Interrupt 25, Fault Mux Interrupt
   Uint32 REQMASK_ADC_CONV:1;             // 24     Interrupt 24, ADC-12 End of Conversion Interrupt
   Uint32 REQMASK_CPCC:1;                 // 23     Interrupt 23, CPCC Interrupt, Mode switched in CPCC module Flag needs to be read for details
   Uint32 REQMASK_TMR_COMP0:1;            // 22     Interrupt 22, 24-bit Timer Compare 0 interrupt
   Uint32 REQMASK_TMR_CAPT0:1;            // 21     Interrupt 21, 24-bit Timer Capture 0 interrupt
   Uint32 REQMASK_TMR_COMP1:1;            // 20     Interrupt 20, 24-bit Timer Compare 1 interrupt
   Uint32 REQMASK_TMR_CAPT1:1;            // 19     Interrupt 19, 24-bit Timer Capture 1 interrupt
   Uint32 REQMASK_TMR_OVFL:1;             // 18     Interrupt 18, 24-bit Timer counter overflow interrupt
   Uint32 REQMASK_PWM0_COMP:1;            // 17     Interrupt 17, 16-bit Timer PWM0 counter overflow or Compare interrupt
   Uint32 REQMASK_PWM1_COMP:1;            // 16     Interrupt 16, 16-bit Timer PWM1 counter overflow or Compare interrupt
   Uint32 REQMASK_PWM2_COMP:1;            // 15     Interrupt 15, 16-bit Timer PWM2 counter overflow or Compare interrupt
   Uint32 REQMASK_PWM3_COMP:1;            // 14     Interrupt 14, 16-bit Timer PWM3 counter overflow or Compare interrupt
   Uint32 REQMASK_FRONT_END2:1;           // 13     Interrupt 13, Front End 2 Interrupt
   Uint32 REQMASK_FRONT_END1:1;           // 12     Interrupt 12, Front End 1 Interrupt
   Uint32 REQMASK_FRONT_END0:1;           // 11     Interrupt 11, Front End 0 Interrupt
   Uint32 REQMASK_DIGI_COMP:1;            // 10     Interrupt 10, Digital comparator interrupt
   Uint32 REQMASK_PMBUS:1;                // 9      Interrupt 9, PMBus related interrupt
   Uint32 REQMASK_UART2_TX:1;             // 8      Interrupt 8, UART2 TX buffer empty
   Uint32 REQMASK_UART2_RX:1;             // 7      Interrupt 7, UART2 RX buffer has a byte
   Uint32 REQMASK_UART1_TX:1;             // 6      Interrupt 6, UART1 TX buffer empty
   Uint32 REQMASK_UART1_RX:1;             // 5      Interrupt 5, UART1 RX buffer has a byte
   Uint32 REQMASK_UART_ERR:1;             // 4      Interrupt 4, UART or SCI error Interrupt. Frame, parity or Overrun
   Uint32 REQMASK_WTDG_WAKE:1;            // 3      Interrupt 3, Wakeup interrupt when watchdog equals half of set watch time
   Uint32 REQMASK_WTDG_RSET:1;            // 2      Interrupt 2, Interrupt from watchdog exceeded (reset)
   Uint32 REQMASK_EXT_INT:1;              // 1      Interrupt 1, Interrupt on one or all external input pins
   Uint32 REQMASK_BRWN_OUT:1;             // 0      Interrupt 0, Brownout interrupt
};
union REQMASK_REG {
   Uint32                 all;
   struct REQMASK_BITS    bit;
};


//===========================================================================
// Central Interrupt Manager Module Register File
//
struct CIM_REGS {
   union  IRQIVEC_REG    IRQIVEC;     // IRQ Index Offset Vector Register
   union  FIQIVEC_REG    FIQIVEC;     // FIQ Index Offset Vector Register                        
   Uint32                RSVD;        // Reserved (address spacer)
   union  FIRQPR_REG     FIRQPR;      // FIQ/IRQ Program Control Register
   union  INTREQ_REG     INTREQ;      // Pending Interrupt Read Location
   union  REQMASK_REG    REQMASK;     // Interrupt Mask Register
};

//---------------------------------------------------------------------------
// Central Interrupt Manager Module External References & Function Declarations:
//
extern volatile struct CIM_REGS CimRegs;

//===========================================================================
#ifdef __cplusplus
}       // end of extern "C"
#endif

#endif  // end of CYCLONE_CIM_H definition

//===========================================================================
// End of file
//===========================================================================
