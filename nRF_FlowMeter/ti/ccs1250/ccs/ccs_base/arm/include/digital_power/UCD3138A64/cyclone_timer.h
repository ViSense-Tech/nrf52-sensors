//###############################################################################
//
// FILE:   cyclone_timer.h
//
// TITLE:  Cyclone Timer Module Register Definitions.
//
// NOTES:
//  1) Bitfields have been defined for big-endian only.
//###############################################################################
//
//  Ver  | dd mmm yyyy | Who  | Description of changes
// ======|=============|======|==============================================
//  1.00 | 19 Aug 2009 | CMF  | Started with Spartan_Timer.h.
//       |             |      | Updated for 1.0 Memory map document.
//       |             |      |
//
//  Texas Instruments, Inc
//  Copyright Texas Instruments 2009. All rights reserved.
//###############################################################################

#ifndef CYCLONE_TIMER_H
#define CYCLONE_TIMER_H

#ifdef __cplusplus
extern "C" {
#endif

  //=============================================================================
  // TIMER Individual Register Bit Definitions
  //=============================================================================

  //-----------------------------------------------------------------------------
  // T24 Counter Data Register bit definitions
  //-----------------------------------------------------------------------------
  struct T24CNTDAT_BITS {          // bits   description
    Uint32 rsvd0:8;                // 31:24  reserved
    Uint32 CNT_DAT:24;             // 23:0   Counter data
  };
  union T24CNTDAT_REG {
    Uint32                 all;
    struct T24CNTDAT_BITS  bit;
  };

  //-----------------------------------------------------------------------------
  // T24 Counter Control/Status Register bit definitions
  //-----------------------------------------------------------------------------
  struct T24CNTCTRL_BITS {         // bits   description
    Uint32 rsvd1:16;               // 31:16  reserved
    Uint32 PRESCALE:8;             // 15:8   Prescale value
    Uint32 rsvd0:5;                // 7:3    reserved
    Uint32 EXT_CLK_SEL:1;          // 2      External clock select
    Uint32 OV_INT_ENA:1;           // 1      Overflow interrupt enable
    Uint32 OV_FLAG:1;              // 0      Overflow event flag
  };
  union T24CNTCTRL_REG {
    Uint32                   all;
    struct T24CNTCTRL_BITS   bit;
  };

  //-----------------------------------------------------------------------------
  // T24 Capture Data Register bit definitions
  //-----------------------------------------------------------------------------
  struct T24CAPDAT_BITS {          // bits   description
    Uint32 rsvd0:8;                // 31:24  reserved
    Uint32 CAP_DAT:24;             // 23:0   Counter data
  };
  union T24CAPDAT_REG {
    Uint32                  all;
    struct T24CAPDAT_BITS   bit;
  };

  //-----------------------------------------------------------------------------
  // T24 Capture Control Register bit definitions
  //-----------------------------------------------------------------------------
  struct T24CAPCTRL_BITS {         // bits   description
    Uint32 rsvd0:26;               // 31:6   reserved
    Uint32 CAP_SEL:2;              // 4:3    Capture Pin Select
    Uint32 EDGE:2;                 // 3:2    Edge select
    Uint32 CAP_INT_ENA:1;          // 1      Capture interrupt enable
    Uint32 CAP_INT_FLAG:1;         // 0      Capture event flag
  };
  union T24CAPCTRL_REG {
    Uint32                   all;
    struct T24CAPCTRL_BITS   bit;
  };
  
  //-----------------------------------------------------------------------------
  // T24 I/O Control and Data Register bit definitions
  //-----------------------------------------------------------------------------
  struct T24CAPIO_BITS {           // bits   description
    Uint32 rsvd0:26;               // 31:6   reserved
    Uint32 TCAP_1_IN:1;            // 5      TCAP1 pin input data
    Uint32 TCAP_1_OUT:1;           // 4      TCAP1 pin output data
    Uint32 TCAP_1_DIR:1;           // 3      TCAP1 pin direction
    Uint32 TCAP_0_IN:1;            // 2      TCAP0 pin input data
    Uint32 TCAP_0_OUT:1;           // 1      TCAP0 pin output data
    Uint32 TCAP_0_DIR:1;           // 0      TCAP0 pin direction
  };
  union T24CAPIO_REG {
    Uint32                 all;
    struct T24CAPIO_BITS   bit;
  };

  //-----------------------------------------------------------------------------
  // T24 Compare Data Register bit definitions
  //-----------------------------------------------------------------------------
  struct T24CMPDAT_BITS {          // bits   description
    Uint32 rsvd0:8;                // 31:24  reserved
    Uint32 CMP_DAT:24;             // 23:0   Compare data
  };
  union T24CMPDAT_REG {
    Uint32                  all;
    struct T24CMPDAT_BITS   bit;
  };

  //-----------------------------------------------------------------------------
  // T24 Compare Control Register bit definitions
  // T24 bits [7:2] only available for T24CMPCTRL1
  //-----------------------------------------------------------------------------
  struct T24CMPCTRL_BITS {          // bits   description
    Uint32 rsvd0:30;                // 31:2   reserved
    Uint32 CMP_INT_ENA:1;           // 1      Compare interrupt enable
    Uint32 CMP_INT_FLAG:1;          // 0      Compare event flag
  };
  union T24CMPCTRL_REG {
    Uint32                   all;
    struct T24CMPCTRL_BITS   bit;
  };

  //-----------------------------------------------------------------------------
  // PWMx Counter Data Register bit definitions
  //-----------------------------------------------------------------------------
  struct T16PWMXCNTDAT_BITS {      // bits   description
    Uint32 rsvd0:16;               // 31:16  reserved
    Uint32 CNT_DAT:16;             // 15:0   Counter data
  };
  union T16PWMXCNTDAT_REG {
    Uint32                     all;
    struct T16PWMXCNTDAT_BITS  bit;
  };

  //-----------------------------------------------------------------------------
  // PWMx Counter Control Register bit definitions
  //-----------------------------------------------------------------------------
  struct T16PWMXCNTCTRL_BITS {     // bits   description
    Uint32 rsvd1:16;               // 31:16  reserved
    Uint32 PRESCALE:8;             // 15:8   Prescale value
    Uint32 rsvd0:1;                // 7      Reserved
    Uint32 SYNC_SEL:2;             // 6:5    Counter Sync Select
    Uint32 SYNC_EN:1;              // 4      Counter Sync Enable
    Uint32 SW_RESET:1;             // 3      Software reset
    Uint32 CMP_RESET_ENA:1;        // 2      Counter reset from compare action enable
    Uint32 OV_INT_ENA:1;           // 1      Overflow interrupt enable
    Uint32 OV_INT_FLAG:1;          // 0      Overflow interrupt flag
  };
  union T16PWMXCNTCTRL_REG {
    Uint32                       all;
    struct T16PWMXCNTCTRL_BITS   bit;
  };

  //-----------------------------------------------------------------------------
  // PWMx Compare y Data Register bit definitions
  //-----------------------------------------------------------------------------
  struct T16PWMXCMPYDAT_BITS {     // bits   description
    Uint32 rsvd0:16;               // 31:16  reserved
    Uint32 CMP_DAT:16;             // 15:0   Compare data
  };
  union T16PWMXCMPYDAT_REG {
    Uint32                      all;
    struct T16PWMXCMPYDAT_BITS  bit;
  };
  
  //-----------------------------------------------------------------------------
  // PWMx Compare Control Register bit definitions
  //-----------------------------------------------------------------------------
  struct T16PWMXCMPCTRL_BITS {     // bits   description
    Uint32 rsvd1:19;               // 31:13  reserved
    Uint32 SHADOW:1;               // 12     PWM update control
    Uint32 PWM_IN:1;               // 11     TPWMx pin state
    Uint32 PWM_OUT:1;              // 10     TPWMx pin output data
    Uint32 PWM_OUT_ENA:1;          // 9      TPWMx pin output enable
    Uint32 PWM_OUT_DRV:1;          // 8      TPMWx pin output control
    Uint32 PWM_OUT_ACTION1:2;      // 7:6    TPWMx pin output action on T16CMP1DR match
    Uint32 PWM_OUT_ACTION0:2;      // 5:4    TPWMx pin output action on T16CMP0DR match
    Uint32 CMP1_INT_ENA:1;         // 3      Compare 1 interrupt enable
    Uint32 CMP1_INT_FLAG:1;        // 2      Compare 1 interrupt flag
    Uint32 CMP0_INT_ENA:1;         // 1      Compare 0 interrupt enable
    Uint32 CMP0_INT_FLAG:1;        // 0      Compare 0 interrupt flag
  };
  union T16PWMXCMPCTRL_REG {
    Uint32                       all;
    struct T16PWMXCMPCTRL_BITS   bit;
  };
  
  //-----------------------------------------------------------------------------
  // Watchdog Status Register bit definitions
  //-----------------------------------------------------------------------------
  struct WDST_BITS {              // bits   description
    Uint32 rsvd0:28;              // 31:4   reserved
    Uint32 WAKE_EV_RAW:1;         // 3      Watchdog Wake Event Raw Status
    Uint32 WD_EV_RAW:1;           // 2      Watchdog Event Raw Status
    Uint32 WAKE_EV_INT:1;         // 1      Watchdog Wake Event Interrupt Status
    Uint32 WD_EV_INT:1;          // 0      Watchdog Event Interrupt Status
  };
  union WDST_REG {
    Uint32                 all;
    struct WDST_BITS       bit;
  };

  //-----------------------------------------------------------------------------
  // Watchdog Control Register bit definitions
  //-----------------------------------------------------------------------------
  struct WDCTRL_BITS {              // bits   description
    Uint32 rsvd1:17;               // 31:15  reserved
    Uint32 WD_PERIOD:7;               // 14:8   WD period - changed from period to avoid problems with #define PERIOD
    Uint32 rsvd0:1;                // 7      reserved
    Uint32 PROTECT:1;              // 6      Watchdog protect bit - active low.
    Uint32 CPU_RESET_EN:1;         // 5      WD reset of CPU enable
    Uint32 WDRST_INT_EN:1;         // 4      WD reset event interrupt enable
    Uint32 WKEV_INT_EN:1;          // 3      WD wake event interrupt enable
    Uint32 WKEV_EN:1;              // 2      WD wake event enable
    Uint32 WDRST_EN:1;             // 1      WD reset event enable
    Uint32 CNT_RESET:1;            // 0      WD reset
  };
  union WDCTRL_REG {
    Uint32                 all;
    struct WDCTRL_BITS     bit;
  };

  //=============================================================================
  // Timer Module Register File
  //=============================================================================
  struct TIMER_REGS {
    union  T24CNTDAT_REG       T24CNTDAT;        // T24 Counter Data Register
    union  T24CNTCTRL_REG      T24CNTCTRL;       // T24 Counter Control/Status Register
    union  T24CAPDAT_REG       T24CAPDAT0;       // T24 Capture Data 0 Register
    union  T24CAPDAT_REG       T24CAPDAT1;       // T24 Capture Data 1 Register
    Uint32                     RSVD[1];          // Reserved (address spacer)
    union  T24CAPCTRL_REG      T24CAPCTRL0;      // T24 Capture Control 0 Register
    union  T24CAPCTRL_REG      T24CAPCTRL1;      // T24 Capture Control 1 Register
    Uint32                     RSVD1[1];         // Reserved (address spacer)
    union  T24CAPIO_REG        T24CAPIO;         // T24 I/O Control and Data Register
    union  T24CMPDAT_REG       T24CMPDAT0;       // T24 Compare Data Register
    union  T24CMPDAT_REG       T24CMPDAT1;       // T24 Compare Data Register
    union  T24CMPCTRL_REG      T24CMPCTRL0;      // T24 Compare Control Register
    union  T24CMPCTRL_REG      T24CMPCTRL1;      // T24 Compare Control Register
    union  T16PWMXCNTDAT_REG   T16PWM0CNTDAT;    // PWM0 Counter Data Register
    union  T16PWMXCNTCTRL_REG  T16PWM0CNTCTRL;   // PWM0 Counter Control Register
    union  T16PWMXCMPYDAT_REG  T16PWM0CMP0DAT;   // PWM0 Compare Channel 0 Data Register
    union  T16PWMXCMPYDAT_REG  T16PWM0CMP1DAT;   // PWM0 Compare Channel 1 Data Register
    union  T16PWMXCMPCTRL_REG  T16PWM0CMPCTRL;   // PWM0 Compare Control Register
    Uint32                     RSVD4[4];         // Reserved (address spacer)
    union  T16PWMXCNTDAT_REG   T16PWM1CNTDAT;    // PWM1 Counter Data Register
    union  T16PWMXCNTCTRL_REG  T16PWM1CNTCTRL;   // PWM1 Counter Control Register
    union  T16PWMXCMPYDAT_REG  T16PWM1CMP0DAT;   // PWM1 Compare Channel 0 Data Register
    union  T16PWMXCMPYDAT_REG  T16PWM1CMP1DAT;   // PWM1 Compare Channel 1 Data Register
    union  T16PWMXCMPCTRL_REG  T16PWM1CMPCTRL;   // PWM1 Compare Control Register
    union  T16PWMXCNTDAT_REG   T16PWM2CNTDAT;    // PWM2 Counter Data Register
    union  T16PWMXCNTCTRL_REG  T16PWM2CNTCTRL;   // PWM2 Counter Control Register
    union  T16PWMXCMPYDAT_REG  T16PWM2CMP0DAT;   // PWM2 Compare Channel 0 Data Register
    union  T16PWMXCMPYDAT_REG  T16PWM2CMP1DAT;   // PWM2 Compare Channel 1 Data Register
    union  T16PWMXCMPCTRL_REG  T16PWM2CMPCTRL;   // PWM2 Compare Control Register
    union  T16PWMXCNTDAT_REG   T16PWM3CNTDAT;    // PWM3 Counter Data Register
    union  T16PWMXCNTCTRL_REG  T16PWM3CNTCTRL;   // PWM3 Counter Control Register
    union  T16PWMXCMPYDAT_REG  T16PWM3CMP0DAT;   // PWM3 Compare Channel 0 Data Register
    union  T16PWMXCMPYDAT_REG  T16PWM3CMP1DAT;   // PWM3 Compare Channel 1 Data Register
    union  T16PWMXCMPCTRL_REG  T16PWM3CMPCTRL;   // PWM3 Compare Control Register
    union  WDST_REG            WDST;             // Watchdog Status Register
    union  WDCTRL_REG          WDCTRL;           // Watchdog Control Register
  };


  //-----------------------------------------------------------------------------
  // Timer Module External References & Function Declarations:
  //-----------------------------------------------------------------------------
  extern volatile struct TIMER_REGS TimerRegs;

  //===========================================================================
#ifdef __cplusplus
}       // end of extern "C"
#endif

#endif  // end of CYCLONE_TIMER_H definition

//===========================================================================
// End of file
//===========================================================================
