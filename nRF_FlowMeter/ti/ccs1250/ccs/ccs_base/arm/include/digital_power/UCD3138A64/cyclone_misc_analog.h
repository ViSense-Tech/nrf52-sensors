//###############################################################################
//
// FILE:   cyclone_misc_analog.h
//
// TITLE:  Cyclone Miscellaneous Analog Register Definitions.
//
// NOTES:
//  1) Bitfields have been defined for big-endian only.
//###############################################################################
//
//  Ver  | dd mmm yyyy | Who  | Description of changes
// ======|=============|======|==============================================
//  1.00 | 19 Aug 2009 | CMF  | Initial Revision
//       |             |      | 
//       |             |      |
//
//  Texas Instruments, Inc
//  Copyright Texas Instruments 2009. All rights reserved.
//###############################################################################

#ifndef CYCLONE_MISC_ANALOG_H
#define CYCLONE_MISC_ANALOG_H

#ifdef __cplusplus
extern "C" {
#endif

  //=============================================================================
  // Miscellaneous Analog Individual Register Bit Definitions
  //=============================================================================

 

 //-----------------------------------------------------------------------------
  // Clock Trim Register
  //-----------------------------------------------------------------------------
  struct CLKTRIM_BITS {             // bits   description
    Uint32 rsvd0:15;                // 31:17  Reserved
    Uint32 RESET_DISABLE:1;         // 16     RESET Pin Disable bit
    Uint32 HFO_FINE_TRIM:4;         // 15:12  HFO Fine Trim
    Uint32 HFO_COARSE_TRIM:4;       // 11:8   HFO Coarse Trim
    Uint32 reserved:8;              // 7:0    reserved for TI use
  }; 
  union CLKTRIM_REG {
    Uint32                  all;
    struct CLKTRIM_BITS     bit;
  };

  //-----------------------------------------------------------------------------
  // Package ID Register
  //-----------------------------------------------------------------------------
  struct PKGID_BITS {             // bits   description 
    Uint32 rsvd0:30;              // 31:1   Reserved
    Uint32 PKG_ID:2;              // 1:0    Package ID
  };
  union PKGID_REG {
    Uint32                  all;
    struct PKGID_BITS       bit;
  };

  //-----------------------------------------------------------------------------
  // Brownout Register
  //-----------------------------------------------------------------------------
  struct BROWNOUT_BITS {         // bits   description 
    Uint32 rsvd0:29;             // 31:3   Reserved
    Uint32 INT:1;                // 2      Brownout Interrupt Latched Status
    Uint32 INT_EN:1;             // 1      Brownout Interrupt Enable
    Uint32 COMP_EN:1;            // 0      Brownout Enable
  };
  union BROWNOUT_REG {
    Uint32                  all;
    struct BROWNOUT_BITS    bit;
  };
  
    //-----------------------------------------------------------------------------
  // Global I/O Enable Register
  //-----------------------------------------------------------------------------
  struct GLBIOEN_BITS {         // bits   description 
    Uint32 TMR_PWM2_IO_EN:1;          // bit 31
    Uint32 TMR_PWM3_IO_EN:1;          // bit 30
	Uint32 FAULT3_IO_EN:1;            // bit 29
	Uint32 ADC_EXT_TRIG_IO_EN:1;      // bit 28
	Uint32 TCK_IO_EN:1;               // bit 27
    Uint32 TDO_IO_EN:1;               // bit 26
	Uint32 TMS_IO_EN:1;               // bit 25
	Uint32 TDI_IO_EN:1;               // bit 24
	Uint32 SCI_TX1_IO_EN:1;           // bit 23
    Uint32 SCI_TX0_IO_EN:1;           // bit 22
	Uint32 SCI_RX1_IO_EN:1;           // bit 21
	Uint32 SCI_RX0_IO_EN:1;           // bit 20
	Uint32 TMR_CAP0_IO_EN:1;           // bit 19
    Uint32 TMR_PWM1_IO_EN:1;          // bit 18
	Uint32 TMR_PWM0_IO_EN:1;          // bit 17
	Uint32 TMR_CAP1_IO_EN:1;         // bit 16
	Uint32 I2C_DATA_IO_EN:1;        // bit 15
    Uint32 CONTROL_IO_EN:1;           // bit 14
	Uint32 ALERT_IO_EN:1;             // bit 13
	Uint32 EXT_INT_IO_EN:1;           // bit 12
	Uint32 FAULT2_IO_EN:1;            // bit 11
    Uint32 FAULT1_IO_EN:1;            // bit 10
	Uint32 FAULT0_IO_EN:1;            // bit  9
	Uint32 SYNC_IO_EN:1;              // bit  8
	Uint32 DPWM3B_IO_EN:1;            // bit  7
    Uint32 DPWM3A_IO_EN:1;            // bit  6
	Uint32 DPWM2B_IO_EN:1;            // bit  5
	Uint32 DPWM2A_IO_EN:1;            // bit  4
	Uint32 DPWM1B_IO_EN:1;            // bit  3
    Uint32 DPWM1A_IO_EN:1;            // bit  2
	Uint32 DPWM0B_IO_EN:1;            // bit  1
	Uint32 DPWM0A_IO_EN:1;            // bit  0
  };
  union GLBIOEN_REG {
    Uint32                  all;
    struct GLBIOEN_BITS     bit;
  };

  //-----------------------------------------------------------------------------
  // Global I/O Output Enable Register
  //-----------------------------------------------------------------------------
  struct GLBIOOE_BITS {         // bits   description 
    Uint32 TMR_PWM2_IO_OE:1;          // bit 31
    Uint32 TMR_PWM3_IO_OE:1;          // bit 30
	Uint32 FAULT3_IO_OE:1;            // bit 29
	Uint32 ADC_EXT_TRIG_IO_OE:1;      // bit 28
	Uint32 TCK_IO_OE:1;               // bit 27
    Uint32 TDO_IO_OE:1;               // bit 26
	Uint32 TMS_IO_OE:1;               // bit 25
	Uint32 TDI_IO_OE:1;               // bit 24
	Uint32 SCI_TX1_IO_OE:1;           // bit 23
    Uint32 SCI_TX0_IO_OE:1;           // bit 22
	Uint32 SCI_RX1_IO_OE:1;           // bit 21
	Uint32 SCI_RX0_IO_OE:1;           // bit 20
	Uint32 TMR_CAP0_IO_OE:1;           // bit 19
    Uint32 TMR_PWM1_IO_OE:1;          // bit 18
	Uint32 TMR_PWM0_IO_OE:1;          // bit 17
	Uint32 TMR_CAP1_IO_OE:1;         // bit 16
	Uint32 I2C_DATA_IO_OE:1;        // bit 15
    Uint32 CONTROL_IO_OE:1;           // bit 14
	Uint32 ALERT_IO_OE:1;             // bit 13
	Uint32 EXT_INT_IO_OE:1;           // bit 12
	Uint32 FAULT2_IO_OE:1;            // bit 11
    Uint32 FAULT1_IO_OE:1;            // bit 10
	Uint32 FAULT0_IO_OE:1;            // bit  9
	Uint32 SYNC_IO_OE:1;              // bit  8
	Uint32 DPWM3B_IO_OE:1;            // bit  7
    Uint32 DPWM3A_IO_OE:1;            // bit  6
	Uint32 DPWM2B_IO_OE:1;            // bit  5
	Uint32 DPWM2A_IO_OE:1;            // bit  4
	Uint32 DPWM1B_IO_OE:1;            // bit  3
    Uint32 DPWM1A_IO_OE:1;            // bit  2
	Uint32 DPWM0B_IO_OE:1;            // bit  1
	Uint32 DPWM0A_IO_OE:1;            // bit  0
  };
  union GLBIOOE_REG {
    Uint32                  all;
    struct GLBIOOE_BITS     bit;
  };

  //-----------------------------------------------------------------------------
  // Global I/O Open Drain Enable Register
  //-----------------------------------------------------------------------------
  struct GLBIOOD_BITS {         // bits   description 
    Uint32 TMR_PWM2_IO_OD:1;          // bit 31
	Uint32 TMR_PWM3_IO_OD:1;          // bit 30
    Uint32 FAULT3_IO_OD:1;            // bit 29
	Uint32 ADC_EXT_TRIG_IO_OD:1;      // bit 28
	Uint32 TCK_IO_OD:1;               // bit 27
    Uint32 TDO_IO_OD:1;               // bit 26
	Uint32 TMS_IO_OD:1;               // bit 25
	Uint32 TDI_IO_OD:1;               // bit 24
	Uint32 SCI_TX1_IO_OD:1;           // bit 23
    Uint32 SCI_TX0_IO_OD:1;           // bit 22
	Uint32 SCI_RX1_IO_OD:1;           // bit 21
	Uint32 SCI_RX0_IO_OD:1;           // bit 20
	Uint32 TMR_CAP0_IO_OD:1;           // bit 19
    Uint32 TMR_PWM1_IO_OD:1;          // bit 18
	Uint32 TMR_PWM0_IO_OD:1;          // bit 17
	Uint32 TMR_CAP1_IO_OD:1;         // bit 16
	Uint32 I2C_DATA_IO_OD:1;        // bit 15
    Uint32 CONTROL_IO_OD:1;           // bit 14
	Uint32 ALERT_IO_OD:1;             // bit 13
	Uint32 EXT_INT_IO_OD:1;           // bit 12
	Uint32 FAULT2_IO_OD:1;            // bit 11
    Uint32 FAULT1_IO_OD:1;            // bit 10
	Uint32 FAULT0_IO_OD:1;            // bit  9
	Uint32 SYNC_IO_OD:1;              // bit  8
	Uint32 DPWM3B_IO_OD:1;            // bit  7
    Uint32 DPWM3A_IO_OD:1;            // bit  6
	Uint32 DPWM2B_IO_OD:1;            // bit  5
	Uint32 DPWM2A_IO_OD:1;            // bit  4
	Uint32 DPWM1B_IO_OD:1;            // bit  3
    Uint32 DPWM1A_IO_OD:1;            // bit  2
	Uint32 DPWM0B_IO_OD:1;            // bit  1
	Uint32 DPWM0A_IO_OD:1;            // bit  0 
  };
  union GLBIOOD_REG {
    Uint32                  all;
    struct GLBIOOD_BITS     bit;
  };

  //-----------------------------------------------------------------------------
  // Global I/O Value Register
  //-----------------------------------------------------------------------------
  struct GLBIOVAL_BITS {        // bits   description 
    Uint32 TMR_PWM2_IO_VALUE:1;          // bit 31
	Uint32 TMR_PWM3_IO_VALUE:1;          // bit 30
	Uint32 FAULT3_IO_VALUE:1;            // bit 29
	Uint32 ADC_EXT_TRIG_IO_VALUE:1;      // bit 28
	Uint32 TCK_IO_VALUE:1;               // bit 27
    Uint32 TDO_IO_VALUE:1;               // bit 26
	Uint32 TMS_IO_VALUE:1;               // bit 25
	Uint32 TDI_IO_VALUE:1;               // bit 24
	Uint32 SCI_TX1_IO_VALUE:1;           // bit 23
    Uint32 SCI_TX0_IO_VALUE:1;           // bit 22
	Uint32 SCI_RX1_IO_VALUE:1;           // bit 21
	Uint32 SCI_RX0_IO_VALUE:1;           // bit 20
	Uint32 TMR_CAP0_IO_VALUE:1;           // bit 19
    Uint32 TMR_PWM1_IO_VALUE:1;          // bit 18
	Uint32 TMR_PWM0_IO_VALUE:1;          // bit 17
	Uint32 TMR_CAP1_IO_VALUE:1;         // bit 16
	Uint32 I2C_DATA_IO_VALUE:1;        // bit 15
    Uint32 CONTROL_IO_VALUE:1;           // bit 14
	Uint32 ALERT_IO_VALUE:1;             // bit 13
	Uint32 EXT_INT_IO_VALUE:1;           // bit 12
	Uint32 FAULT2_IO_VALUE:1;            // bit 11
    Uint32 FAULT1_IO_VALUE:1;            // bit 10
	Uint32 FAULT0_IO_VALUE:1;            // bit  9
	Uint32 SYNC_IO_VALUE:1;              // bit  8
	Uint32 DPWM3B_IO_VALUE:1;            // bit  7
    Uint32 DPWM3A_IO_VALUE:1;            // bit  6
	Uint32 DPWM2B_IO_VALUE:1;            // bit  5
	Uint32 DPWM2A_IO_VALUE:1;            // bit  4
	Uint32 DPWM1B_IO_VALUE:1;            // bit  3
    Uint32 DPWM1A_IO_VALUE:1;            // bit  2
	Uint32 DPWM0B_IO_VALUE:1;            // bit  1
	Uint32 DPWM0A_IO_VALUE:1;            // bit  0
  };
  union GLBIOVAL_REG {
    Uint32                   all;
    struct GLBIOVAL_BITS     bit;
  };  

  //-----------------------------------------------------------------------------
  // Global I/O Read Value Register
  //-----------------------------------------------------------------------------
  struct GLBIOREAD_BITS {        // bits   description 
    Uint32 TMR_PWM2_IO_READ:1;          // bit 31
	Uint32 TMR_PWM3_IO_READ:1;          // bit 30
	Uint32 FAULT3_IO_READ:1;            // bit 29
	Uint32 ADC_EXT_TRIG_IO_READ:1;      // bit 28
	Uint32 TCK_IO_READ:1;               // bit 27
    Uint32 TDO_IO_READ:1;               // bit 26
	Uint32 TMS_IO_READ:1;               // bit 25
	Uint32 TDI_IO_READ:1;               // bit 24
	Uint32 SCI_TX1_IO_READ:1;           // bit 23
    Uint32 SCI_TX0_IO_READ:1;           // bit 22
	Uint32 SCI_RX1_IO_READ:1;           // bit 21
	Uint32 SCI_RX0_IO_READ:1;           // bit 20
	Uint32 TMR_CAP0_IO_READ:1;           // bit 19
    Uint32 TMR_PWM1_IO_READ:1;          // bit 18
	Uint32 TMR_PWM0_IO_READ:1;          // bit 17
	Uint32 TMR_CAP1_IO_READ:1;         // bit 16
	Uint32 I2C_DATA_IO_READ:1;        // bit 15
    Uint32 CONTROL_IO_READ:1;           // bit 14
	Uint32 ALERT_IO_READ:1;             // bit 13
	Uint32 EXT_INT_IO_READ:1;           // bit 12
	Uint32 FAULT2_IO_READ:1;            // bit 11
    Uint32 FAULT1_IO_READ:1;            // bit 10
	Uint32 FAULT0_IO_READ:1;            // bit  9
	Uint32 SYNC_IO_READ:1;              // bit  8
	Uint32 DPWM3B_IO_READ:1;            // bit  7
    Uint32 DPWM3A_IO_READ:1;            // bit  6
	Uint32 DPWM2B_IO_READ:1;            // bit  5
	Uint32 DPWM2A_IO_READ:1;            // bit  4
	Uint32 DPWM1B_IO_READ:1;            // bit  3
    Uint32 DPWM1A_IO_READ:1;            // bit  2
	Uint32 DPWM0B_IO_READ:1;            // bit  1
	Uint32 DPWM0A_IO_READ:1;            // bit  0
  };
  union GLBIOREAD_REG {
    Uint32                   all;
    struct GLBIOREAD_BITS    bit;
  };  


  //-----------------------------------------------------------------------------
  // I/O Mux Control Register
  //-----------------------------------------------------------------------------
  struct IOMUX_BITS {          // bits   description
    Uint32 rsvd0:24;           // 31:8   Reserved
    Uint32 TCAP1_MUX_SEL:2;    // 7:6    TCAP1 Pins Mux Control
    Uint32 TCAP0_MUX_SEL:2;    // 5:4    TCAP0 Data Pins Mux Control
    Uint32 rsvd1:2;         // 3:2    Reserved 
    Uint32 RTC_CLK_IN_SEL:1;   // 1      RTC clock in mux select      
    Uint32 RTC_CLK_OUT_SEL:1;  // 0      RTC clock out mux select      
  };
  union IOMUX_REG {
    Uint32                   all;
    struct IOMUX_BITS        bit;
  };


  //-----------------------------------------------------------------------------
  // Current Sharing Control Register
  //-----------------------------------------------------------------------------
  struct CSCTRL_BITS {               // bits    Description
    Uint32 rsvd1:8;                  // 31:24   Reserved
    Uint32 DPWM_DUTY:8;              // 23:16   DPWM Duty/Pulse Width for Cur Share
    Uint32 DPWM_PERIOD:8;            // 15:8    DPWM Period for Current Share
    Uint32 rsvd0:4;                  // 7:4     Reserved
    Uint32 TEST_MODE:4;              // 3:0     Current Sharing Test Mode
  };
  union CSCTRL_REG {
    Uint32                   all;
    struct CSCTRL_BITS       bit;
  };

  //-----------------------------------------------------------------------------
  // Temperature Reference Register
  //-----------------------------------------------------------------------------
  struct TEMPREF_BITS {        // bits    Description
    Uint32 rsvd0:20;           // 31:12   Reserved
    Uint32 TEMP_REF:12;        // 11:0    Temperature Reference 
  };
  union TEMPREF_REG {
    Uint32                   all;
    struct TEMPREF_BITS      bit;
  };

  //-----------------------------------------------------------------------------
  // Clock Gating Control Register (CLKGATECTRL)
  //-----------------------------------------------------------------------------
  struct CLKGATECTRL_BITS {   // bits    Description
    Uint32 rsvd0:11;          // 31:21   Reserved
    Uint32 RTC_CLK_EN:1;      // 20      RTC Clock Enable 
    Uint32 PMBUS1_CLK_EN:1;   // 19      PMBus 1 I/F Clock Enable
    Uint32 SPI_CLK_EN:1;      // 18      SPI I/F Clock Enable
    Uint32 PCM_CLK_EN:1;      // 17      Peak Current Mode Clock Enable
    Uint32 CPCC_CLK_EN:1;     // 16      Constant Power/Constant Current Clock Enable
    Uint32 FILTER2_CLK_EN:1;  // 15      Filter 2 Clock Enable
    Uint32 FILTER1_CLK_EN:1;  // 14      Filter 1 Clock Enable
    Uint32 FILTER0_CLK_EN:1;  // 13      Filter 0 Clock Enable
    Uint32 FE_CTRL2_CLK_EN:1; // 12      Front End Control 2 Clock Enable
    Uint32 FE_CTRL1_CLK_EN:1; // 11      Front End Control 2 Clock Enable
    Uint32 FE_CTRL0_CLK_EN:1; // 10      Front End Control 2 Clock Enable
    Uint32 DPWM3_CLK_EN:1;    // 9       DPWM4 Clock Enable
    Uint32 DPWM2_CLK_EN:1;    // 8       DPWM4 Clock Enable
    Uint32 DPWM1_CLK_EN:1;    // 7       DPWM4 Clock Enable
    Uint32 DPWM0_CLK_EN:1;    // 6       DPWM4 Clock Enable
    Uint32 SCI1_CLK_EN:1;     // 5       SCI1 Clock Enable
    Uint32 SCI0_CLK_EN:1;     // 4       SCI0 Clock Enable
    Uint32 ADC12_CLK_EN:1;    // 3       ADC12 Control Clock Enable
    Uint32 PMBUS0_CLK_EN:1;   // 2       PMBus I/F Clock Enable
    Uint32 GIO_CLK_EN:1;      // 1       GIO Clock Enable
    Uint32 TIMER_CLK_EN:1;    // 0       Timer Clock Enable
  };
  union CLKGATECTRL_REG {
    Uint32                  all;
    struct CLKGATECTRL_BITS bit;
  };

  //=============================================================================
  // Miscellaneous Analog  Module Register File
  //=============================================================================
  struct MISC_ANALOG_REGS {
    union CLKTRIM_REG       CLKTRIM;
    int32 RESERVED1; //reserved for TI use
    int32 RESERVED2; //reserved for TI use
    int32 RESERVED3; //reserved for TI use
    union PKGID_REG         PKGID;
    union BROWNOUT_REG      BROWNOUT;
    union GLBIOEN_REG       GLBIOEN;
    union GLBIOOE_REG       GLBIOOE;
    union GLBIOOD_REG       GLBIOOD;
    union GLBIOVAL_REG      GLBIOVAL;
    union GLBIOREAD_REG     GLBIOREAD;
    int32 RESERVED4; //reserved for TI use
    union IOMUX_REG         IOMUX;
    int32 RESERVED5; //reserved for TI use
    union CSCTRL_REG        CSCTRL;
    union TEMPREF_REG       TEMPREF;
    union CLKGATECTRL_REG   CLKGATECTRL;
    int32 RESERVED6; //reserved for TI use
  };

  //-----------------------------------------------------------------------------
  // ADC Module External References & Function Declarations:
  //-----------------------------------------------------------------------------
  extern volatile struct MISC_ANALOG_REGS MiscAnalogRegs;


#ifdef __cplusplus
}       // end of extern "C"
#endif

#endif  // end of CYCLONE_FE_CTRL_H definition

//===========================================================================
// End of file
//===========================================================================
