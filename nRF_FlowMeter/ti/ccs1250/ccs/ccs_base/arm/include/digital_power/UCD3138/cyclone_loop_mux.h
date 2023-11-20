//###############################################################################
//
// FILE:   cyclone_loop_mux.h
//
// TITLE:  Cyclone Loop Mux Register Definitions.
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

#ifndef CYCLONE_LOOP_MUX_H
#define CYCLONE_LOOP_MUX_H

#ifdef __cplusplus
extern "C" {
#endif

  //=============================================================================
  // Loop Mux Individual Register Bit Definitions
  //=============================================================================

  //-----------------------------------------------------------------------------
  // Front End Control 0 Mux Register
  //-----------------------------------------------------------------------------
  struct FECTRL0MUX_BITS {          // bits   description
    Uint32 rsvd0:18;                // 31:14  Reserved
    Uint32 NL_SEL:2;                // 13:12  Front End NL Limit Select
    Uint32 DPWM3_FRAME_SYNC_EN:1;   // 11     Front End DPWM3 Frame Sync Enable
    Uint32 DPWM2_FRAME_SYNC_EN:1;   // 10     Front End DPWM3 Frame Sync Enable
    Uint32 DPWM1_FRAME_SYNC_EN:1;   // 9      Front End DPWM3 Frame Sync Enable
    Uint32 DPWM0_FRAME_SYNC_EN:1;   // 8      Front End DPWM3 Frame Sync Enable
    Uint32 DPWM3_B_TRIG_EN:1;       // 7      Front End DPWM3 PWM-B Trig Enable
    Uint32 DPWM2_B_TRIG_EN:1;       // 6      Front End DPWM2 PWM-B Trig Enable
    Uint32 DPWM1_B_TRIG_EN:1;       // 5      Front End DPWM1 PWM-B Trig Enable
    Uint32 DPWM0_B_TRIG_EN:1;       // 4      Front End DPWM0 PWM-B Trig Enable
    Uint32 DPWM3_A_TRIG_EN:1;       // 3      Front End DPWM3 PWM-A Trig Enable
    Uint32 DPWM2_A_TRIG_EN:1;       // 2      Front End DPWM2 PWM-A Trig Enable
    Uint32 DPWM1_A_TRIG_EN:1;       // 1      Front End DPWM1 PWM-A Trig Enable
    Uint32 DPWM0_A_TRIG_EN:1;       // 0      Front End DPWM0 PWM-A Trig Enable
  }; 
  union FECTRL0MUX_REG {
    Uint32                    all;
    struct FECTRL0MUX_BITS     bit;
  };

  //-----------------------------------------------------------------------------
  // Front End Control 1 Mux Register
  //-----------------------------------------------------------------------------
  struct FECTRL1MUX_BITS {          // bits   description
    Uint32 rsvd0:18;                // 31:14  Reserved
    Uint32 NL_SEL:2;                // 13:12  Front End NL Limit Select
    Uint32 DPWM3_FRAME_SYNC_EN:1;   // 11     Front End DPWM3 Frame Sync Enable
    Uint32 DPWM2_FRAME_SYNC_EN:1;   // 10     Front End DPWM3 Frame Sync Enable
    Uint32 DPWM1_FRAME_SYNC_EN:1;   // 9      Front End DPWM3 Frame Sync Enable
    Uint32 DPWM0_FRAME_SYNC_EN:1;   // 8      Front End DPWM3 Frame Sync Enable
    Uint32 DPWM3_B_TRIG_EN:1;       // 7      Front End DPWM3 PWM-B Trig Enable
    Uint32 DPWM2_B_TRIG_EN:1;       // 6      Front End DPWM2 PWM-B Trig Enable
    Uint32 DPWM1_B_TRIG_EN:1;       // 5      Front End DPWM1 PWM-B Trig Enable
    Uint32 DPWM0_B_TRIG_EN:1;       // 4      Front End DPWM0 PWM-B Trig Enable
    Uint32 DPWM3_A_TRIG_EN:1;       // 3      Front End DPWM3 PWM-A Trig Enable
    Uint32 DPWM2_A_TRIG_EN:1;       // 2      Front End DPWM2 PWM-A Trig Enable
    Uint32 DPWM1_A_TRIG_EN:1;       // 1      Front End DPWM1 PWM-A Trig Enable
    Uint32 DPWM0_A_TRIG_EN:1;       // 0      Front End DPWM0 PWM-A Trig Enable
  }; 
  union FECTRL1MUX_REG {
    Uint32                    all;
    struct FECTRL1MUX_BITS    bit;
  };

  //-----------------------------------------------------------------------------
  // Front End Control 2 Mux Register
  //-----------------------------------------------------------------------------
  struct FECTRL2MUX_BITS {          // bits   description
    Uint32 rsvd0:18;                // 31:14  Reserved
    Uint32 NL_SEL:2;                // 13:12  Front End NL Limit Select
    Uint32 DPWM3_FRAME_SYNC_EN:1;   // 11     Front End DPWM3 Frame Sync Enable
    Uint32 DPWM2_FRAME_SYNC_EN:1;   // 10     Front End DPWM3 Frame Sync Enable
    Uint32 DPWM1_FRAME_SYNC_EN:1;   // 9      Front End DPWM3 Frame Sync Enable
    Uint32 DPWM0_FRAME_SYNC_EN:1;   // 8      Front End DPWM3 Frame Sync Enable
    Uint32 DPWM3_B_TRIG_EN:1;       // 7      Front End DPWM3 PWM-B Trig Enable
    Uint32 DPWM2_B_TRIG_EN:1;       // 6      Front End DPWM2 PWM-B Trig Enable
    Uint32 DPWM1_B_TRIG_EN:1;       // 5      Front End DPWM1 PWM-B Trig Enable
    Uint32 DPWM0_B_TRIG_EN:1;       // 4      Front End DPWM0 PWM-B Trig Enable
    Uint32 DPWM3_A_TRIG_EN:1;       // 3      Front End DPWM3 PWM-A Trig Enable
    Uint32 DPWM2_A_TRIG_EN:1;       // 2      Front End DPWM2 PWM-A Trig Enable
    Uint32 DPWM1_A_TRIG_EN:1;       // 1      Front End DPWM1 PWM-A Trig Enable
    Uint32 DPWM0_A_TRIG_EN:1;       // 0      Front End DPWM0 PWM-A Trig Enable
  }; 
  union FECTRL2MUX_REG {
    Uint32                    all;
    struct FECTRL2MUX_BITS    bit;
  };
  
  //-----------------------------------------------------------------------------
  // Sample Trigger Control Register
  //-----------------------------------------------------------------------------
  struct SAMPTRIGCTRL_BITS {       // bits   description
    Uint32 rsvd0:20;               // 31:12  Reserved
    Uint32 FE2_TRIG_DPWM3_EN:1;    // 11     Front End 2 DPWM 3 Trig Enable
    Uint32 FE2_TRIG_DPWM2_EN:1;    // 10     Front End 2 DPWM 2 Trig Enable
    Uint32 FE2_TRIG_DPWM1_EN:1;    // 9      Front End 2 DPWM 1 Trig Enable
    Uint32 FE2_TRIG_DPWM0_EN:1;    // 8      Front End 2 DPWM 1 Trig Enable
    Uint32 FE1_TRIG_DPWM3_EN:1;    // 7      Front End 1 DPWM 3 Trig Enable
    Uint32 FE1_TRIG_DPWM2_EN:1;    // 6      Front End 1 DPWM 2 Trig Enable
    Uint32 FE1_TRIG_DPWM1_EN:1;    // 5      Front End 1 DPWM 1 Trig Enable
    Uint32 FE1_TRIG_DPWM0_EN:1;    // 4      Front End 1 DPWM 1 Trig Enable
    Uint32 FE0_TRIG_DPWM3_EN:1;    // 3      Front End 0 DPWM 3 Trig Enable
    Uint32 FE0_TRIG_DPWM2_EN:1;    // 2      Front End 0 DPWM 2 Trig Enable
    Uint32 FE0_TRIG_DPWM1_EN:1;    // 1      Front End 0 DPWM 1 Trig Enable
    Uint32 FE0_TRIG_DPWM0_EN:1;    // 0      Front End 0 DPWM 1 Trig Enable
  };
  union SAMPTRIGCTRL_REG {
    Uint32                    all;
    struct SAMPTRIGCTRL_BITS  bit;
  };

  //-----------------------------------------------------------------------------
  // External DAC Control Register
  //-----------------------------------------------------------------------------
  struct EXTDACCTRL_BITS {         // Bits   Description
    Uint32 rsvd3:5;                // 31:27  Reserved
    Uint32 DAC2_SEL:3;             // 26:24  DAC 2 Select
    Uint32 rsvd2:5;                // 23:19  Reserved
    Uint32 DAC1_SEL:3;             // 18:16  DAC 1 Select
    Uint32 rsvd1:5;                // 15:11  Reserved
    Uint32 DAC0_SEL:3;             // 10:8   DAC 0 Select
    Uint32 rsvd0:5;                // 7:3    Reserved
    Uint32 EXT_DAC2_EN:1;          // 2      External DAC 2 Enable
    Uint32 EXT_DAC1_EN:1;          // 1      External DAC 1 Enable
    Uint32 EXT_DAC0_EN:1;          // 0      External DAC 0 Enable
  };
  union EXTDACCTRL_REG {
    Uint32                   all;
    struct EXTDACCTRL_BITS   bit;
  };

  //-----------------------------------------------------------------------------
  // Filter Mux Register 
  //-----------------------------------------------------------------------------
  struct FILTERMUX_BITS {         // Bits   Description 
    Uint32 rsvd3:2;               // 31:30  Reserved
    Uint32 FILTER2_KCOMP_SEL:2;   // 29:28  Filter 2 KComp Select
    Uint32 FILTER1_KCOMP_SEL:2;   // 27:26  Filter 1 KComp Select
    Uint32 FILTER0_KCOMP_SEL:2;   // 25:24  Filter 0 KComp Select
    Uint32 rsvd2:5;               // 23:19  Reserved
    Uint32 FILTER2_FFWD_SEL:1;    // 18     Filter 2 Feedforward Select
    Uint32 FILTER1_FFWD_SEL:1;    // 17     Filter 1 Feedforward Select
    Uint32 FILTER0_FFWD_SEL:1;    // 16     Filter 0 Feedforward Select
    Uint32 rsvd1:2;               // 15:14  Reserved  
    Uint32 FILTER2_PER_SEL:2;     // 13:12  Filter 2 Switching Period Select
    Uint32 FILTER1_PER_SEL:2;     // 11:10  Filter 1 Switching Period Select
    Uint32 FILTER0_PER_SEL:2;     // 9:8    Filter 0 Switching Period Select
    Uint32 rsvd0:2;               // 7:6    Reserved  
    Uint32 FILTER2_FE_SEL:2;      // 5:4    Filter 2 Front End Select
    Uint32 FILTER1_FE_SEL:2;      // 3:2    Filter 1 Front End Select
    Uint32 FILTER0_FE_SEL:2;      // 1:0    Filter 0 Front End Select
  };
  union FILTERMUX_REG {
    Uint32                    all;
    struct FILTERMUX_BITS     bit;
  };
  
  //-----------------------------------------------------------------------------
  // Filter KComp A Register
  //-----------------------------------------------------------------------------
  struct FILTERKCOMPA_BITS {     // Bits    Description
    Uint32 rsvd1:2;              // 31:30   Reserved
    Uint32 KCOMP1:14;            // 29:16   KCOMP1 Value
    Uint32 rsvd0:2;              // 15:14   Reserved
    Uint32 KCOMP0:14;            // 13:0    KCOMP0 Value
  };
  union FILTERKCOMPA_REG {
    Uint32                    all;
    struct FILTERKCOMPA_BITS  bit;
  };

  //-----------------------------------------------------------------------------
  // Filter KComp B Register
  //-----------------------------------------------------------------------------
  struct FILTERKCOMPB_BITS {     // Bits    Description
    Uint32 rsvd1:18;             // 31:14   Reserved
    Uint32 KCOMP2:14;            // 13:0    KCOMP2 Value
  };
  union FILTERKCOMPB_REG {
    Uint32                    all;
    struct FILTERKCOMPB_BITS  bit;
  };    

  //-----------------------------------------------------------------------------
  // DPWM Mux Register 
  //-----------------------------------------------------------------------------
  struct DPWMMUX_BITS {           // Bits    Description
    Uint32 DPWM3_SYNC_FET_SEL:2;  // 31:30   DPWM3 Sync Fet Ramp Select
    Uint32 DPWM2_SYNC_FET_SEL:2;  // 29:28   DPWM2 Sync Fet Ramp Select
    Uint32 DPWM1_SYNC_FET_SEL:2;  // 27:26   DPWM1 Sync Fet Ramp Select
    Uint32 DPWM0_SYNC_FET_SEL:2;  // 25:24   DPWM0 Sync Fet Ramp Select
    Uint32 rsvd0:4;               // 23:20   Reserved
    Uint32 DPWM3_SYNC_SEL:2;      // 19:18   DPWM3 Sync Select
    Uint32 DPWM2_SYNC_SEL:2;      // 17:16   DPWM2 Sync Select
    Uint32 DPWM1_SYNC_SEL:2;      // 15:14   DPWM1 Sync Select
    Uint32 DPWM0_SYNC_SEL:2;      // 13:12   DPWM0 Sync Select
    Uint32 DPWM3_FILTER_SEL:3;    // 11:9    DPWM3 Filter Select
    Uint32 DPWM2_FILTER_SEL:3;    // 8:6     DPWM2 Filter Select
    Uint32 DPWM1_FILTER_SEL:3;    // 5:3     DPWM1 Filter Select
    Uint32 DPWM0_FILTER_SEL:3;    // 2:0     DPWM0 Filter Select
  };
  union DPWMMUX_REG {
    Uint32                    all;
    struct DPWMMUX_BITS       bit;
  };

  //-----------------------------------------------------------------------------
  // Constant Power Control Register (CPCTRL)
  //-----------------------------------------------------------------------------
  struct CPCTRL_BITS {          // Bits    Description
    Uint32 rsvd1:16;            // 31:16   Reserved
    Uint32 DAC_COMP_EN:1;       // 15      Enables DAC Setpoint comparison
    Uint32 FW_DIVISOR_EN:1;     // 14      Enable Firwmare Divisor for Constant Power Calculation
    Uint32 LOWER_COMP_EN:1;     // 13      Enable comparison of duty cycle in loop switching
    Uint32 VLOOP_FREEZE_EN:1;   // 12      Enables freeze of Voltage Loop Integration in CC Mode
    Uint32 VLOOP_SEL:2;         // 11:10   Select Voltage Loop for Loop Switching
    Uint32 CLOOP_SEL:2;         // 9:8     Select Current Loop for Loop Switching
    Uint32 THRESH_SEL:3;        // 7:5     Select Input Threshold for CPCC
    Uint32 DIVISOR_SEL:2;       // 4:3     Select Divisor Value
    Uint32 CPCC_INT_EN:1;       // 2       Constant Power/Current Interrupt Enable
    Uint32 CPCC_CONFIG:1;       // 1       Constant Power/Current Configuration
    Uint32 CPCC_EN:1;           // 0       Constant Power Constant Current Enable
  };
  union CPCTRL_REG {
    Uint32                    all;
    struct CPCTRL_BITS        bit;
  };

  //-----------------------------------------------------------------------------
  // Constant Power Nominal Threshold Register (CPNOM)
  //-----------------------------------------------------------------------------
  struct CPNOM_BITS {              // Bits    Description
    Uint32 rsvd1:6;                // 31:26   Reserved
    Uint32 NOM_CURRENT_UPPER:10;   // 25:16   Nominal Current Upper Threshold
    Uint32 rsvd0:6;                // 15:10   Reserved
    Uint32 NOM_CURRENT_LOWER:10;   // 9:0     Nominal Current Lower Threshold
  };
  union CPNOM_REG {
    Uint32                    all;
    struct CPNOM_BITS         bit;
  };

  //-----------------------------------------------------------------------------
  // Constant Power Max Threshold Register (CPMAX)
  //-----------------------------------------------------------------------------
  struct CPMAX_BITS {             // Bits    Description
    Uint32 rsvd1:6;               // 31:26   Reserved
    Uint32 MAX_CURRENT_UPPER:10;  // 25:16   Maximum Current Upper Threshold
    Uint32 rsvd0:6;               // 15:10   Reserved
    Uint32 MAX_CURRENT_LOWER:10;  // 9:0     Maximum Current Lower Threshold
  };
  union CPMAX_REG {
    Uint32                   all;
    struct CPMAX_BITS        bit;
  };

  //-----------------------------------------------------------------------------
  // Constant Power Configuration Register (CPCONFIG)
  //-----------------------------------------------------------------------------
  struct CPCONFIG_BITS {          // Bits    Description
    Uint32 rsvd1:6;               // 31:26   Reserved
    Uint32 MAX_CURRENT:10;        // 25:16   Maximum Current 
    Uint32 rsvd0:6;               // 15:10   Reserved
    Uint32 NOM_VOLTAGE:10;        // 9:0     Nominal Voltage
  };
  union CPCONFIG_REG {
    Uint32                   all;
    struct CPCONFIG_BITS     bit;
  }; 
  
  //-----------------------------------------------------------------------------
  // Constant Power Max Power Register (CPMAXPWR)
  //-----------------------------------------------------------------------------
  struct CPMAXPWR_BITS {          // Bits    Description
    Uint32 rsvd0:12;              // 31:20   Reserved
    Uint32 MAX_POWER:20;          // 19:0    Maximum Power
  };
  union CPMAXPWR_REG {
    Uint32                   all;
    struct CPMAXPWR_BITS     bit;
  };

  //-----------------------------------------------------------------------------
  // Constant Power Integrator Threshold Register (CPINTTHRESH)
  //-----------------------------------------------------------------------------
  struct CPINTTHRESH_BITS {      // Bits     Description
    Uint32 rsvd0:8;              // 31:24    Reserved
    Uint32 INT_THRESH:24;        // 23:0     Signed Integrator Threshold
  };
  union CPINTTHRESH_REG {
    Uint32                   all;
    struct CPINTTHRESH_BITS  bit;
  };

  //-----------------------------------------------------------------------------
  // Constant Power Firmware Divisor Register (CPFWDIVISOR)
  //-----------------------------------------------------------------------------
  struct CPFWDIVISOR_BITS {      // Bits     Description
    Uint32 rsvd0:22;             // 31:10    Reserved
    Uint32 FW_DIVISOR:10;        // 9:0      Firmware configurable divisor
  };
  union CPFWDIVISOR_REG {
    Uint32                   all;
    struct CPFWDIVISOR_BITS  bit;
  };

  //-----------------------------------------------------------------------------
  // Constant Power Status Register (CPSTAT)
  //-----------------------------------------------------------------------------
  struct CPSTAT_BITS {           // Bits     Description
    Uint32 rsvd0:23;             // 31:9     Reserved
    Uint32 CONSTANT_CUR:1;       // 8        Constant Current Mode Indication
    Uint32 CONSTANT_PWR:1;       // 7        Constant Power Mode Indication
    Uint32 CONSTANT_VOLT:1;      // 6        Constant Voltage Mode Indication
    Uint32 CC_TO_CV_INT:1;       // 5        Constant Current to Voltage Interrupt
    Uint32 CV_TO_CC_INT:1;       // 4        Constant Voltage to Current Interrupt
    Uint32 CC_TO_CP_INT:1;       // 3        Constant Current to Power Interrupt
    Uint32 CP_TO_CC_INT:1;       // 2        Constant Power to Current Interrupt
    Uint32 CP_TO_CV_INT:1;       // 1        Constant Power to Voltage Interrupt
    Uint32 CV_TO_CP_INT:1;       // 0        Constant Voltage to Power Interrupt
  };
  union CPSTAT_REG {
    Uint32                   all;
    struct CPSTAT_BITS       bit;
  };

  //-----------------------------------------------------------------------------
  // Cycle Adjustment Control Register
  //-----------------------------------------------------------------------------
  struct CYCADJCTRL_BITS {      // Bits    Description
    Uint32 rsvd0:22;            // 31:10   Reserved
    Uint32 CYC_ADJ_GAIN:3;      // 9:7     Cycle Adjustment Gain
    Uint32 CYC_ADJ_SYNC:2;      // 6:5     Cycle Adjustment Sync
    Uint32 SECOND_SAMPLE_SEL:2; // 4:3     Second Cycle Adjustment Select
    Uint32 FIRST_SAMPLE_SEL:2;  // 2:1     First Cycle Adjustment Select
    Uint32 CYC_ADJ_EN:1;        // 0       Cycle Adjustment Enable
  };
  union CYCADJCTRL_REG {
    Uint32                    all;
    struct CYCADJCTRL_BITS    bit;
  };
  
  //-----------------------------------------------------------------------------
  // Cycle Adjustment Limit Register
  //-----------------------------------------------------------------------------
  struct CYCADJLIM_BITS {          // Bits    Description
    Uint32 rsvd1:3;                // 31:29   Reserved
    Uint32 CYC_ADJ_UPPER_LIMIT:13; // 28:16   Cycle Adjustment Upper Limit
    Uint32 rsvd0:3;                // 15:13   Reserved
    Uint32 CYC_ADJ_LOWER_LIMIT:13; // 12:0    Cycle Adjustment Lower Limit
  };
  union CYCADJLIM_REG {
    Uint32                    all;
    struct CYCADJLIM_BITS     bit;
  };

  //-----------------------------------------------------------------------------
  // Cycle Adjustment Status Register
  //-----------------------------------------------------------------------------
  struct CYCADJSTAT_BITS {      // Bits    Description
    Uint32 rsvd1:3;             // 31:29   Reserved
    Uint32 CYC_ADJ_CAL:13;      // 28:16   Cycle Adjustment Calculation
    Uint32 rsvd0:6;             // 15:10   Reserved
    Uint32 CYC_ADJ_ERROR:10;    // 9:0     Cycle Adjustment Error
  };
  union CYCADJSTAT_REG {
    Uint32                    all;
    struct CYCADJSTAT_BITS    bit;
  };

  //-----------------------------------------------------------------------------
  // Global Enable Register
  //-----------------------------------------------------------------------------
  struct GLBEN_BITS {           // Bits    Description
    Uint32 rsvd1:21;            // 31:11   Reserved
    Uint32 FE_CTRL2_EN:1;       // 10      Global Enable for Front End Control 2
    Uint32 FE_CTRL1_EN:1;       // 9       Global Enable for Front End Control 1
    Uint32 FE_CTRL0_EN:1;       // 8       Global Enable for Front End Control 0
    Uint32 rsvd0:4;             // 7:4     Reserved
    Uint32 DPWM3_EN:1;          // 3       Global Enable for DPWM Module 3
    Uint32 DPWM2_EN:1;          // 2       Global Enable for DPWM Module 2
    Uint32 DPWM1_EN:1;          // 1       Global Enable for DPWM Module 1
    Uint32 DPWM0_EN:1;          // 0       Global Enable for DPWM Module 0
  };
  union GLBEN_REG {
    Uint32                 all;
    struct GLBEN_BITS      bit;
  };

  //-----------------------------------------------------------------------------
  // PWM Global Period Register
  //-----------------------------------------------------------------------------
  struct PWMGLBPER_BITS {       // Bits    Description
    Uint32 rsvd1:14;            // 31:18   Reserved
    Uint32 PRD:14;              // 17:4    Global DPWM Period Value
    Uint32 rsvd0:4;             // 3:0     Reserved
  };
  union PWMGLBPER_REG {
    Uint32                    all;
    struct PWMGLBPER_BITS     bit;
  };

  //-----------------------------------------------------------------------------
  // Sync Control Register
  //-----------------------------------------------------------------------------
  struct SYNCCTRL_BITS {        // Bits    Description
    Uint32 rsvd0:26;            // 31:6    Reserved
    Uint32 SYNC_IN:1;           // 5       Sync pin value
    Uint32 SYNC_MUX_SEL:3;      // 4:2     Sync Select
    Uint32 SYNC_OUT:1;          // 1       Sync GPIO Value
    Uint32 SYNC_DIR:1;          // 0       Sync Pin Direction
  };
  union SYNCCTRL_REG {
    Uint32                    all;
    struct SYNCCTRL_BITS      bit;
  };

  //-----------------------------------------------------------------------------
  // Light Load Control Register
  //-----------------------------------------------------------------------------
  struct LLCTRL_BITS {         // Bits     Description
    Uint32 rsvd1:6;            // 31:26    Reserved
    Uint32 DPWM_ON_TIME:18;    // 25:8     DPWM On Time during Light Load Mode
    Uint32 rsvd0:4;            // 7:4      Reserved
    Uint32 CYCLE_CNT_EN:1;     // 3        Cycle Counter Enable
    Uint32 LL_FILTER_SEL:2;    // 2:1      Light Load Filter Select
    Uint32 LL_EN:1;            // 0        Light Load Enable
  };
  union LLCTRL_REG {
    Uint32                    all;
    struct LLCTRL_BITS        bit;
  };
  
  //-----------------------------------------------------------------------------
  // Light Load Enable Threshold Register
  //-----------------------------------------------------------------------------
  struct LLENTHRESH_BITS {       // Bits     Description
    Uint32 CYCLE_CNT_THRESH:8;   // 31:24    Switching Cycle Counter Threshold for turning on burst mode
    Uint32 rsvd0:6;              // 23:18    Reserved
    Uint32 TURN_ON_THRESH:18;    // 17:0     Filter Data Threshold to turn on burst mode
  };
  union LLENTHRESH_REG {
    Uint32                    all;
    struct LLENTHRESH_BITS    bit;
  };

  //-----------------------------------------------------------------------------
  // Light Load Disable Threshold Register
  //-----------------------------------------------------------------------------
  struct LLDISTHRESH_BITS {       // Bits     Description
    Uint32 rsvd0:14;              // 31:18    Reserved
    Uint32 TURN_OFF_THRESH:18;    // 17:0     Filter Data Threshold to turn off burst mode
  };
  union LLDISTHRESH_REG {
    Uint32                    all;
    struct LLDISTHRESH_BITS    bit;
  };  

  //-----------------------------------------------------------------------------
  // Digital Peak Current Mode Control Register
  //-----------------------------------------------------------------------------
  struct PCMCTRL_BITS {         // Bits      Description
    Uint32 rsvd1:26;             // 31:6         Reserved
    Uint32 PCM_FILTER_SEL:2;     // 5:4       Peak Current Mode Filter Select
    Uint32 rsvd0:4;             // 3:0        Reserved
  };
  union PCMCTRL_REG {
    Uint32                   all;
    struct PCMCTRL_BITS      bit;
  };

  //-----------------------------------------------------------------------------
  // Analog Peak Current Mode Control Register
  //-----------------------------------------------------------------------------
  struct APCMCTRL_BITS {         // Bits     Description
    Uint32 rsvd0:28;             // 31:4     Reserved
    Uint32 PCM_LATCH_EN:1;       // 3        PCM Latch Enable
    Uint32 PCM_FE_SEL:2;         // 2:1      Analog Peak Current Front End Select
    Uint32 PCM_EN:1;             // 0        Analog Peak Current Mode Enable
  };
  union APCMCTRL_REG {
    Uint32                   all;
    struct APCMCTRL_BITS     bit;
  }; 

  //-----------------------------------------------------------------------------
  // Loop Mux Test Register
  //-----------------------------------------------------------------------------
  struct LOOPMUXTEST_BITS {      // Bits     Description
    Uint32 rsvd0:13;             // 31:19    Reserved
    Uint32 BIST_COMP:1;          // 18       BIST Complete Flag
    Uint32 BIST_EN:1;            // 17       BIST Enable
    Uint32 BIST_TRIM_TEST_EN:1;  // 16       BIST Trim Test Enable
    Uint32 EADC_REF_TRIM:6;      // 15:10    EADC Ref Trim
    Uint32 EADC_REF_RESET:1;     // 9        EADC Reference Reset
    Uint32 EADC_REF_EN:1;        // 8        EADC Reference Enable
    Uint32 GAIN_TRIM:6;          // 7:2      EADC Gain Trim
    Uint32 AFE_GAIN:2;           // 1:0      AFE Gain
  };
  union LOOPMUXTEST_REG {
    Uint32                  all;
    struct LOOPMUXTEST_BITS bit;
  };

  //=============================================================================
  // Loop Mux Module Register File
  //=============================================================================
  struct LOOP_MUX_REGS {
    union FECTRL0MUX_REG       FECTRL0MUX;        // Front End Control 0 Mux Register
    union FECTRL1MUX_REG       FECTRL1MUX;        // Front End Control 1 Mux Register
    union FECTRL2MUX_REG       FECTRL2MUX;        // Front End Control 2 Mux Register
    union SAMPTRIGCTRL_REG     SAMPTRIGCTRL;      // Sample Trigger Control Register
    union EXTDACCTRL_REG       EXTDACCTRL;        // External DAC Control Register
    union FILTERMUX_REG        FILTERMUX;         // Filter Mux Register
    union FILTERKCOMPA_REG     FILTERKCOMPA;      // Filter KCOMP A Register
    union FILTERKCOMPB_REG     FILTERKCOMPB;      // Filter KCOMP B Register
    union DPWMMUX_REG          DPWMMUX;           // DPWM Mux Register
    union CPCTRL_REG           CPCTRL;            // Constant Power Control Register
    union CPNOM_REG            CPNOM;             // Constant Power Nominal Threshold Register
    union CPMAX_REG            CPMAX;             // Constant Power Maximum Threshold Register
    union CPCONFIG_REG         CPCONFIG;          // Constant Power Configuration Register
    union CPMAXPWR_REG         CPMAXPWR;          // Constant Power Maximum Power Register
    union CPINTTHRESH_REG      CPINTTHRESH;       // Constant Power Integrator Threshold Register
    union CPFWDIVISOR_REG      CPFWDIVISOR;       // Constant Power Firmware Divisor Register
    union CPSTAT_REG           CPSTAT;            // Constant Power Status Register
    union CYCADJCTRL_REG       CYCADJCTRL;        // Cycle Adjustment Control
    union CYCADJLIM_REG        CYCADJLIM;         // Cycle Adjustment Limit Register
    union CYCADJSTAT_REG       CYCADJSTAT;        // Cycle Adjustment Status Register
    union GLBEN_REG            GLBEN;             // Global Enable Register
    union PWMGLBPER_REG        PWMGLBPER;         // PWM Global Period Register
    union SYNCCTRL_REG         SYNCCTRL;          // Sync Control Register
    union LLCTRL_REG           LLCTRL;            // Light Load Control Register
    union LLENTHRESH_REG       LLENTHRESH;        // Light Load Enable Threshold Register
    union LLDISTHRESH_REG      LLDISTHRESH;       // Light Load Disable Threshold Register
    union PCMCTRL_REG          PCMCTRL;          // Digital Peak Current Mode Control Register
    Uint32                     RESERVED;         //Reserved
    union APCMCTRL_REG         APCMCTRL;          // Analog Peak Current Mode Control Register
    union LOOPMUXTEST_REG      LOOPMUXTEST;       // Loop Mux Test Register
  };
  
  //-----------------------------------------------------------------------------
  // Loop Mux Module External References & Function Declarations:
  //-----------------------------------------------------------------------------
  extern volatile struct LOOP_MUX_REGS LoopMuxRegs;


#ifdef __cplusplus
}       // end of extern "C"
#endif

#endif  // end of CYCLONE_LOOP_MUX_H definition

//===========================================================================
// End of file
//===========================================================================
