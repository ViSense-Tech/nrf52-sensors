//###############################################################################
//
// FILE:   cyclone_fault_mux.h
//
// TITLE:  Cyclone Fault Mux Register Definitions.
//
// NOTES:
//  1) Bitfields have been defined for big-endian only.
//###############################################################################
//
//  Ver  | dd mmm yyyy | Who  | Description of changes
// ======|=============|======|==============================================
//  1.00 | 20 Aug 2009 | CMF  | Initial Revision
//       |             |      | 
//       |             |      |
//
//  Texas Instruments, Inc
//  Copyright Texas Instruments 2009. All rights reserved.
//###############################################################################

#ifndef CYCLONE_FAULT_MUX_H
#define CYCLONE_FAULT_MUX_H

#ifdef __cplusplus
extern "C" {
#endif

  //=============================================================================
  // Fault Mux Individual Register Bit Definitions
  //=============================================================================

  //-----------------------------------------------------------------------------
  // Analog Comparator Control 0 Register
  //-----------------------------------------------------------------------------
  struct ACOMPCTRL0_BITS {          // bits   description
    Uint32 rsvd3:1;                 // 31     Reserved
    Uint32 ACOMP_B_THRESH:7;        // 30:24  Analog Comparator B Threshold
    Uint32 rsvd2:2;                 // 23:22  Reserved
    Uint32 ACOMP_B_SEL:3;           // 21:19  Analog Comparator B Select
    Uint32 ACOMP_B_POL:1;           // 18     Analog Comparator B Polarity
    Uint32 ACOMP_B_INT_EN:1;        // 17     Analog Comparator B Interrupt Enable
    Uint32 rsvd1:2;                 // 16:15  Reserved
    Uint32 ACOMP_A_THRESH:7;        // 14:8   Analog Comparator A Threshold
    Uint32 rsvd0:2;                 // 7:6    Reserved
    Uint32 ACOMP_A_SEL:3;           // 5:3    Analog Comparator A Select
    Uint32 ACOMP_A_POL:1;           // 2      Analog Comparator A Polarity
    Uint32 ACOMP_A_INT_EN:1;        // 1      Analog Comparator A Interrupt Enable
    Uint32 ACOMP_EN:1;              // 0      Analog Comparator A Enable
  }; 
  union ACOMPCTRL0_REG {
    Uint32                    all;
    struct ACOMPCTRL0_BITS    bit;
  };
  
  //-----------------------------------------------------------------------------
  // Analog Comparator Control 1 Register
  //-----------------------------------------------------------------------------
  struct ACOMPCTRL1_BITS {          // bits   description
    Uint32 rsvd4:1;                 // 31     Reserved
    Uint32 ACOMP_D_THRESH:7;        // 30:24  Analog Comparator D Threshold
    Uint32 rsvd3:2;                 // 23:22  Reserved
    Uint32 ACOMP_D_SEL:3;           // 21:19  Analog Comparator D Select
    Uint32 ACOMP_D_POL:1;           // 18     Analog Comparator D Polarity
    Uint32 ACOMP_D_INT_EN:1;        // 17     Analog Comparator D Interrupt Enable
    Uint32 ACOMP_D_OUT_EN:1;        // 16     Analog Comparator D DAC Output Enable
    Uint32 rsvd2:1;                 // 15     Reserved
    Uint32 ACOMP_C_THRESH:7;        // 14:8   Analog Comparator C Threshold
    Uint32 rsvd1:2;                 // 7:6    Reserved
    Uint32 ACOMP_C_SEL:3;           // 5:3    Analog Comparator C Select
    Uint32 ACOMP_C_POL:1;           // 2      Analog Comparator C Polarity
    Uint32 ACOMP_C_INT_EN:1;        // 1      Analog Comparator C Interrupt Enable
    Uint32 rsvd0:1;                 // 0      Reserved
  }; 
  union ACOMPCTRL1_REG {
    Uint32                    all;
    struct ACOMPCTRL1_BITS    bit;
  };
  
  //-----------------------------------------------------------------------------
  // Analog Comparator Control 2 Register
  //-----------------------------------------------------------------------------
  struct ACOMPCTRL2_BITS {          // bits   description
    Uint32 rsvd4:1;                 // 31     Reserved
    Uint32 ACOMP_F_THRESH:7;        // 30:24  Analog Comparator F Threshold
    Uint32 rsvd3:1;                 // 23     Reserved
    Uint32 ACOMP_F_REF_SEL:1;       // 22     Analog Comparator F Ref Select
    Uint32 ACOMP_F_SEL:3;           // 21:19  Analog Comparator F Select
    Uint32 ACOMP_F_POL:1;           // 18     Analog Comparator F Polarity
    Uint32 ACOMP_F_INT_EN:1;        // 17     Analog Comparator F Interrupt Enable
    Uint32 ACOMP_F_OUT_EN:1;        // 16     Analog Comparator F DAC Output Enable
    Uint32 rsvd2:1;                 // 15     Reserved
    Uint32 ACOMP_E_THRESH:7;        // 14:8   Analog Comparator E Threshold
    Uint32 rsvd1:2;                 // 7:6    Reserved
    Uint32 ACOMP_E_SEL:3;           // 5:3    Analog Comparator E Select
    Uint32 ACOMP_E_POL:1;           // 2      Analog Comparator E Polarity
    Uint32 ACOMP_E_INT_EN:1;        // 1      Analog Comparator E Interrupt Enable
    Uint32 ACOMP_E_OUT_EN:1;        // 0      Analog Comparator E DAC Output Enable
  }; 
  union ACOMPCTRL2_REG {
    Uint32                    all;
    struct ACOMPCTRL2_BITS    bit;
  };

  //-----------------------------------------------------------------------------
  // Analog Comparator Control 3 Register
  //-----------------------------------------------------------------------------
  struct ACOMPCTRL3_BITS {          // bits   description
    Uint32 rsvd2:17;                // 31:15  Reserved
    Uint32 ACOMP_G_THRESH:7;        // 14:8   Analog Comparator G Threshold
    Uint32 rsvd1:2;                 // 7:6    Reserved
    Uint32 ACOMP_G_SEL:3;           // 5:3    Analog Comparator G Select
    Uint32 ACOMP_G_POL:1;           // 2      Analog Comparator G Polarity
    Uint32 ACOMP_G_INT_EN:1;        // 1      Analog Comparator G Interrupt Enable
    Uint32 ACOMP_G_OUT_EN:1;        // 0      Analog Comparator G DAC Output Enable
  }; 
  union ACOMPCTRL3_REG {
    Uint32                    all;
    struct ACOMPCTRL3_BITS    bit;
  };

  //-----------------------------------------------------------------------------
  // External Fault Control Register
  //-----------------------------------------------------------------------------
  struct EXTFAULTCTRL_BITS {       // Bits   Description
    Uint32 rsvd0:20;               // 31:12  Reserved
    Uint32 FAULT3_POL:1;           // 11     External FAULT[3] Polarity
    Uint32 FAULT2_POL:1;           // 10     External FAULT[2] Polarity
    Uint32 FAULT1_POL:1;           // 9      External FAULT[1] Polarity
    Uint32 FAULT0_POL:1;           // 8      External FAULT[0] Polarity
    Uint32 FAULT3_INT_EN:1;        // 7      External FAULT[3] Interrupt Enable
    Uint32 FAULT2_INT_EN:1;        // 6      External FAULT[2] Interrupt Enable
    Uint32 FAULT1_INT_EN:1;        // 5      External FAULT[1] Interrupt Enable
    Uint32 FAULT0_INT_EN:1;        // 4      External FAULT[0] Interrupt Enable
    Uint32 FAULT3_DET_EN:1;        // 3      External FAULT[3] Detection Enable
    Uint32 FAULT2_DET_EN:1;        // 2      External FAULT[2] Detection Enable
    Uint32 FAULT1_DET_EN:1;        // 1      External FAULT[1] Detection Enable
    Uint32 FAULT0_DET_EN:1;        // 0      External FAULT[0] Detection Enable
  };
  union EXTFAULTCTRL_REG {
    Uint32                    all;
    struct EXTFAULTCTRL_BITS  bit;
  };

  //-----------------------------------------------------------------------------
  // Fault Mux Interrupt Status Register
  //-----------------------------------------------------------------------------
  struct FAULTMUXINTSTAT_BITS {     // bits   description
    Uint32 rsvd0:15;                // 31:17  Reserved
    Uint32 DCOMP3:1;                // 16     Digital Comparator 3 Interrupt Status
    Uint32 DCOMP2:1;                // 15     Digital Comparator 2 Interrupt Status
    Uint32 DCOMP1:1;                // 14     Digital Comparator 1 Interrupt Status
    Uint32 DCOMP0:1;                // 13     Digital Comparator 0 Interrupt Status
    Uint32 LFO_FAIL:1;              // 12     Low Frequency Oscillator Failure
    Uint32 FAULT3:1;                // 11     External FAULT[3] Detect Interrupt Status
    Uint32 FAULT2:1;                // 10     External FAULT[2] Detect Interrupt Status
    Uint32 FAULT1:1;                // 9      External FAULT[1] Detect Interrupt Status
    Uint32 FAULT0:1;                // 8      External FAULT[0] Detect Interrupt Status
    Uint32 DCM_DETECT:1;            // 7      Discontinuous Conduction Mode
    Uint32 ACOMP_G:1;               // 6      Analog Comparator G Interrupt Status
    Uint32 ACOMP_F:1;               // 5      Analog Comparator F Interrupt Status
    Uint32 ACOMP_E:1;               // 4      Analog Comparator E Interrupt Status
    Uint32 ACOMP_D:1;               // 3      Analog Comparator D Interrupt Status
    Uint32 ACOMP_C:1;               // 2      Analog Comparator C Interrupt Status
    Uint32 ACOMP_B:1;               // 1      Analog Comparator B Interrupt Status
    Uint32 ACOMP_A:1;               // 0      Analog Comparator A Interrupt Status
  };
  union FAULTMUXINTSTAT_REG {
    Uint32                        all;
    struct FAULTMUXINTSTAT_BITS   bit;
  };

  //-----------------------------------------------------------------------------
  // Fault Mux Raw Status Register
  //-----------------------------------------------------------------------------
  struct FAULTMUXRAWSTAT_BITS {     // bits   description
    Uint32 rsvd0:15;                // 31:17  Reserved
    Uint32 DCOMP3:1;                // 16     Digital Comparator 3 Raw Status
    Uint32 DCOMP2:1;                // 15     Digital Comparator 2 Raw Status
    Uint32 DCOMP1:1;                // 14     Digital Comparator 1 Raw Status
    Uint32 DCOMP0:1;                // 13     Digital Comparator 0 Raw Status
    Uint32 LFO_FAIL:1;              // 12     Low Frequency Oscillator Failure
    Uint32 FAULT3:1;                // 11     External FAULT[2] Detect Raw Status
    Uint32 FAULT2:1;                // 10     External FAULT[2] Detect Raw Status
    Uint32 FAULT1:1;                // 9      External FAULT[1] Detect Raw Status
    Uint32 FAULT0:1;                // 8      External FAULT[0] Detect Raw Status
    Uint32 DCM_DETECT:1;            // 7      Discontinuous Conduction Mode
    Uint32 ACOMP_G:1;               // 6      Analog Comparator G Raw Status
    Uint32 ACOMP_F:1;               // 5      Analog Comparator F Raw Status
    Uint32 ACOMP_E:1;               // 4      Analog Comparator E Raw Status
    Uint32 ACOMP_D:1;               // 3      Analog Comparator D Raw Status
    Uint32 ACOMP_C:1;               // 2      Analog Comparator C Raw Status
    Uint32 ACOMP_B:1;               // 1      Analog Comparator B Raw Status
    Uint32 ACOMP_A:1;               // 0      Analog Comparator A Raw Status
  };
  union FAULTMUXRAWSTAT_REG {
    Uint32                        all;
    struct FAULTMUXRAWSTAT_BITS   bit;
  };

  //-----------------------------------------------------------------------------
  // Comparator Ramp Control 0 Register
  //-----------------------------------------------------------------------------
  struct COMPRAMP0_BITS {           // Bits   Description
    Uint32 START_VALUE_SEL:4;       // 31:28  Selects Ramp Start Value
    Uint32 STEP_SIZE:18;            // 27:10  Comparator Ramp Step Size
    Uint32 CLKS_PER_STEP:5;         // 9:5    Clocks per Ramp Step
    Uint32 DPWM3_TRIG_EN:1;         // 4      DPWM3 Trigger Enable
    Uint32 DPWM2_TRIG_EN:1;         // 3      DPWM2 Trigger Enable
    Uint32 DPWM1_TRIG_EN:1;         // 2      DPWM1 Trigger Enable
    Uint32 DPWM0_TRIG_EN:1;         // 1      DPWM0 Trigger Enable
    Uint32 RAMP_EN:1;               // 0      Ramp Enable
  };
  union COMPRAMP0_REG {
    Uint32                   all;
    struct COMPRAMP0_BITS    bit;
  };

  //-----------------------------------------------------------------------------
  // Digital Comparator Control 0 Register 
  //-----------------------------------------------------------------------------
  struct DCOMPCTRL0_BITS {          // Bits   Description
    Uint32 CNT_THRESH:8;            // 31:24  Digital Comparator Counter Threshold
    Uint32 rsvd0:5;                 // 23:19  Reserved
    Uint32 COMP_POL:1;              // 18     Digital Comparator Polarity Select
    Uint32 FE_SEL:3;                // 17:15  Digital Comparator Front End Select
    Uint32 CNT_CLR:1;               // 14     Digital Comparator Counter Clear
    Uint32 CNT_CONFIG:1;            // 13     Digital Comparator Counter Configuration
    Uint32 INT_EN:1;                // 12     Digital Comparator Interrupt Enable
    Uint32 COMP_EN:1;               // 11     Digital Comparator Enable
    int32 THRESH:11;               // 10:0   Digital Comparator Threshold
  };
  union DCOMPCTRL0_REG {         
    Uint32                    all;
    struct DCOMPCTRL0_BITS    bit;
  };

  //-----------------------------------------------------------------------------
  // Digital Comparator Control 1 Register 
  //-----------------------------------------------------------------------------
  struct DCOMPCTRL1_BITS {          // Bits   Description
    Uint32 CNT_THRESH:8;            // 31:24  Digital Comparator Counter Threshold
    Uint32 rsvd0:5;                 // 23:19  Reserved
    Uint32 COMP_POL:1;              // 18     Digital Comparator Polarity Select
    Uint32 FE_SEL:3;                // 17:15  Digital Comparator Front End Select
    Uint32 CNT_CLR:1;               // 14     Digital Comparator Counter Clear
    Uint32 CNT_CONFIG:1;            // 13     Digital Comparator Counter Configuration
    Uint32 INT_EN:1;                // 12     Digital Comparator Interrupt Enable
    Uint32 COMP_EN:1;               // 11     Digital Comparator Enable
    int32 THRESH:11;               // 10:0   Digital Comparator Threshold
  };
  union DCOMPCTRL1_REG {         
    Uint32                    all;
    struct DCOMPCTRL1_BITS    bit;
  };

  //-----------------------------------------------------------------------------
  // Digital Comparator Control 2 Register 
  //-----------------------------------------------------------------------------
  struct DCOMPCTRL2_BITS {          // Bits   Description
    Uint32 CNT_THRESH:8;            // 31:24  Digital Comparator Counter Threshold
    Uint32 rsvd0:5;                 // 23:19  Reserved
    Uint32 COMP_POL:1;              // 18     Digital Comparator Polarity Select
    Uint32 FE_SEL:3;                // 17:15  Digital Comparator Front End Select
    Uint32 CNT_CLR:1;               // 14     Digital Comparator Counter Clear
    Uint32 CNT_CONFIG:1;            // 13     Digital Comparator Counter Configuration
    Uint32 INT_EN:1;                // 12     Digital Comparator Interrupt Enable
    Uint32 COMP_EN:1;               // 11     Digital Comparator Enable
    int32 THRESH:11;               // 10:0   Digital Comparator Threshold
  };
  union DCOMPCTRL2_REG {         
    Uint32                    all;
    struct DCOMPCTRL2_BITS    bit;
  };

  //-----------------------------------------------------------------------------
  // Digital Comparator Control 3 Register 
  //-----------------------------------------------------------------------------
  struct DCOMPCTRL3_BITS {          // Bits   Description
    Uint32 CNT_THRESH:8;            // 31:24  Digital Comparator Counter Threshold
    Uint32 rsvd0:5;                 // 23:19  Reserved
    Uint32 COMP_POL:1;              // 18     Digital Comparator Polarity Select
    Uint32 FE_SEL:3;                // 17:15  Digital Comparator Front End Select
    Uint32 CNT_CLR:1;               // 14     Digital Comparator Counter Clear
    Uint32 CNT_CONFIG:1;            // 13     Digital Comparator Counter Configuration
    Uint32 INT_EN:1;                // 12     Digital Comparator Interrupt Enable
    Uint32 COMP_EN:1;               // 11     Digital Comparator Enable
    int32 THRESH:11;               // 10:0   Digital Comparator Threshold
  };
  union DCOMPCTRL3_REG {         
    Uint32                    all;
    struct DCOMPCTRL3_BITS    bit;
  };

  //-----------------------------------------------------------------------------
  // Digital Comparator Counter Status Register
  //-----------------------------------------------------------------------------
  struct DCOMPCNTSTAT_BITS {        // Bits    Description
    Uint32 DCOMP3_CNT:8;            // 31:24   Digital Comparator 3 Counter
    Uint32 DCOMP2_CNT:8;            // 23:16   Digital Comparator 2 Counter
    Uint32 DCOMP1_CNT:8;            // 31:24   Digital Comparator 3 Counter
    Uint32 DCOMP0_CNT:8;            // 23:16   Digital Comparator 2 Counter
  };
  union DCOMPCNTSTAT_REG {
    Uint32                    all;
    struct DCOMPCNTSTAT_BITS  bit;
  };

  //-----------------------------------------------------------------------------
  // DPWM 0 Current Limit Control Register
  //-----------------------------------------------------------------------------
  struct DPWM0CLIM_BITS {            // Bits   Description
    Uint32 rsvd0:15;                 // 31:17  Reserved
    Uint32 ANALOG_PCM_EN:1;          // 16     Analog Peak Current Detection Enable
    Uint32 DCOMP3_EN:1;              // 15     Digital Comparator 3 Enable
    Uint32 DCOMP2_EN:1;              // 14     Digital Comparator 2 Enable
    Uint32 DCOMP1_EN:1;              // 13     Digital Comparator 1 Enable
    Uint32 DCOMP0_EN:1;              // 12     Digital Comparator 0 Enable
    Uint32 rsvd1:1;                  // 11     Reserved - leave as zero
    Uint32 FAULT3_EN:1;              // 10     External FAULT[3] Current Limit Enable
    Uint32 FAULT2_EN:1;              // 9      External FAULT[2] Current Limit Enable
    Uint32 FAULT1_EN:1;              // 8      External FAULT[1] Current Limit Enable
    Uint32 FAULT0_EN:1;              // 7      External FAULT[0] Current Limit Enable
    Uint32 ACOMP_G_EN:1;             // 6      Analog Comparator G Enable
    Uint32 ACOMP_F_EN:1;             // 5      Analog Comparator F Enable
    Uint32 ACOMP_E_EN:1;             // 4      Analog Comparator E Enable
    Uint32 ACOMP_D_EN:1;             // 3      Analog Comparator D Enable
    Uint32 ACOMP_C_EN:1;             // 2      Analog Comparator C Enable
    Uint32 ACOMP_B_EN:1;             // 1      Analog Comparator B Enable
    Uint32 ACOMP_A_EN:1;             // 0      Analog Comparator A Enable
  };
  union DPWM0CLIM_REG {
    Uint32                    all;
    struct DPWM0CLIM_BITS     bit;
  };
  
  //-----------------------------------------------------------------------------
  // DPWM 0 Fault AB Detction Register
  //-----------------------------------------------------------------------------
  struct DPWM0FLTABDET_BITS {        // Bits   Description
    Uint32 rsvd0:17;                 // 31:15  Reserved
    Uint32 DCOMP3_EN:1;              // 14     Digital Comparator 3 Enable
    Uint32 DCOMP2_EN:1;              // 13     Digital Comparator 2 Enable
    Uint32 DCOMP1_EN:1;              // 12     Digital Comparator 1 Enable
    Uint32 DCOMP0_EN:1;              // 11     Digital Comparator 0 Enable
    Uint32 FAULT3_EN:1;              // 10     External FAULT[2] Enable
    Uint32 FAULT2_EN:1;              // 9      External FAULT[2] Enable
    Uint32 FAULT1_EN:1;              // 8      External FAULT[1] Enable
    Uint32 FAULT0_EN:1;              // 7      External FAULT[0] Enable
    Uint32 ACOMP_G_EN:1;             // 6      Analog Comparator G Enable
    Uint32 ACOMP_F_EN:1;             // 5      Analog Comparator F Enable
    Uint32 ACOMP_E_EN:1;             // 4      Analog Comparator E Enable
    Uint32 ACOMP_D_EN:1;             // 3      Analog Comparator D Enable
    Uint32 ACOMP_C_EN:1;             // 2      Analog Comparator C Enable
    Uint32 ACOMP_B_EN:1;             // 1      Analog Comparator B Enable
    Uint32 ACOMP_A_EN:1;             // 0      Analog Comparator A Enable
  };
  union DPWM0FLTABDET_REG {
    Uint32                      all;
    struct DPWM0FLTABDET_BITS   bit;
  };
  
  //-----------------------------------------------------------------------------
  // DPWM 0 Fault Detection Register
  //-----------------------------------------------------------------------------
  struct DPWM0FAULTDET_BITS {        // Bits   Description
    Uint32 rsvd1:1;                  // 31     Reserved
    Uint32 PWMB_DCOMP3_EN:1;         // 30     PWM B Digital Comparator 3 Enable
    Uint32 PWMB_DCOMP2_EN:1;         // 29     PWM B Digital Comparator 2 Enable
    Uint32 PWMB_DCOMP1_EN:1;         // 28     PWM B Digital Comparator 1 Enable
    Uint32 PWMB_DCOMP0_EN:1;         // 27     PWM B Digital Comparator 0 Enable
    Uint32 PWMB_FAULT3_EN:1;         // 26     PWM B Fault[3] Enable
    Uint32 PWMB_FAULT2_EN:1;         // 25     PWM B Fault[2] Enable
    Uint32 PWMB_FAULT1_EN:1;         // 24     PWM B Fault[1] Enable
    Uint32 PWMB_FAULT0_EN:1;         // 23     PWM B Fault[0] Enable
    Uint32 PWMB_ACOMP_G_EN:1;        // 22     PWM B Analog Comparator G Enable
    Uint32 PWMB_ACOMP_F_EN:1;        // 21     PWM B Analog Comparator F Enable
    Uint32 PWMB_ACOMP_E_EN:1;        // 20     PWM B Analog Comparator E Enable
    Uint32 PWMB_ACOMP_D_EN:1;        // 19     PWM B Analog Comparator D Enable
    Uint32 PWMB_ACOMP_C_EN:1;        // 18     PWM B Analog Comparator C Enable
    Uint32 PWMB_ACOMP_B_EN:1;        // 17     PWM B Analog Comparator B Enable
    Uint32 PWMB_ACOMP_A_EN:1;        // 16     PWM B Analog Comparator A Enable
    Uint32 rsvd0:1;                  // 15     Reserved
    Uint32 PWMA_DCOMP3_EN:1;         // 14     PWM B Digital Comparator 3 Enable
    Uint32 PWMA_DCOMP2_EN:1;         // 13     PWM B Digital Comparator 2 Enable
    Uint32 PWMA_DCOMP1_EN:1;         // 12     PWM B Digital Comparator 1 Enable
    Uint32 PWMA_DCOMP0_EN:1;         // 11     PWM B Digital Comparator 0 Enable
    Uint32 PWMA_FAULT3_EN:1;         // 10     PWM A Fault[2] Enable    
    Uint32 PWMA_FAULT2_EN:1;         // 9      PWM A Fault[2] Enable
    Uint32 PWMA_FAULT1_EN:1;         // 8      PWM A Fault[1] Enable
    Uint32 PWMA_FAULT0_EN:1;         // 7      PWM A Fault[0] Enable
    Uint32 PWMA_ACOMP_G_EN:1;        // 6      PWM A Analog Comparator G Enable
    Uint32 PWMA_ACOMP_F_EN:1;        // 5      PWM A Analog Comparator F Enable
    Uint32 PWMA_ACOMP_E_EN:1;        // 4      PWM A Analog Comparator E Enable
    Uint32 PWMA_ACOMP_D_EN:1;        // 3      PWM A Analog Comparator D Enable
    Uint32 PWMA_ACOMP_C_EN:1;        // 2      PWM A Analog Comparator C Enable
    Uint32 PWMA_ACOMP_B_EN:1;        // 1      PWM A Analog Comparator B Enable
    Uint32 PWMA_ACOMP_A_EN:1;        // 0      PWM A Analog Comparator A Enable    
  };
  union DPWM0FAULTDET_REG {
    Uint32                   all;
    struct DPWM0FAULTDET_BITS  bit;
  };
  
  //-----------------------------------------------------------------------------
  // DPWM 1 Current Limit Control Register
  //-----------------------------------------------------------------------------
  struct DPWM1CLIM_BITS {            // Bits   Description
    Uint32 rsvd0:15;                 // 31:17  Reserved
    Uint32 ANALOG_PCM_EN:1;          // 16     Analog Peak Current Detection Enable
    Uint32 DCOMP3_EN:1;              // 15     Digital Comparator 3 Enable
    Uint32 DCOMP2_EN:1;              // 14     Digital Comparator 2 Enable
    Uint32 DCOMP1_EN:1;              // 13     Digital Comparator 1 Enable
    Uint32 DCOMP0_EN:1;              // 12     Digital Comparator 0 Enable
    Uint32 rsvd1:1;                  // 11     Reserved - leave as zero
    Uint32 FAULT3_EN:1;              // 10     External FAULT[3] Current Limit Enable
    Uint32 FAULT2_EN:1;              // 9      External FAULT[2] Current Limit Enable
    Uint32 FAULT1_EN:1;              // 8      External FAULT[1] Current Limit Enable
    Uint32 FAULT0_EN:1;              // 7      External FAULT[0] Current Limit Enable
    Uint32 ACOMP_G_EN:1;             // 6      Analog Comparator G Enable
    Uint32 ACOMP_F_EN:1;             // 5      Analog Comparator F Enable
    Uint32 ACOMP_E_EN:1;             // 4      Analog Comparator E Enable
    Uint32 ACOMP_D_EN:1;             // 3      Analog Comparator D Enable
    Uint32 ACOMP_C_EN:1;             // 2      Analog Comparator C Enable
    Uint32 ACOMP_B_EN:1;             // 1      Analog Comparator B Enable
    Uint32 ACOMP_A_EN:1;             // 0      Analog Comparator A Enable    
  };
  union DPWM1CLIM_REG {
    Uint32                    all;
    struct DPWM1CLIM_BITS     bit;
  };
  
  //-----------------------------------------------------------------------------
  // DPWM 1 Fault AB Detction Register
  //-----------------------------------------------------------------------------
  struct DPWM1FLTABDET_BITS {        // Bits   Description
    Uint32 rsvd0:17;                 // 31:15  Reserved
    Uint32 DCOMP3_EN:1;              // 14     Digital Comparator 3 Enable
    Uint32 DCOMP2_EN:1;              // 13     Digital Comparator 2 Enable
    Uint32 DCOMP1_EN:1;              // 12     Digital Comparator 1 Enable
    Uint32 DCOMP0_EN:1;              // 11     Digital Comparator 0 Enable
    Uint32 FAULT3_EN:1;              // 10     External FAULT[3] Enable
    Uint32 FAULT2_EN:1;              // 9      External FAULT[2] Enable
    Uint32 FAULT1_EN:1;              // 8      External FAULT[1] Enable
    Uint32 FAULT0_EN:1;              // 7      External FAULT[0] Enable
    Uint32 ACOMP_G_EN:1;             // 6      Analog Comparator G Enable
    Uint32 ACOMP_F_EN:1;             // 5      Analog Comparator F Enable
    Uint32 ACOMP_E_EN:1;             // 4      Analog Comparator E Enable
    Uint32 ACOMP_D_EN:1;             // 3      Analog Comparator D Enable
    Uint32 ACOMP_C_EN:1;             // 2      Analog Comparator C Enable
    Uint32 ACOMP_B_EN:1;             // 1      Analog Comparator B Enable
    Uint32 ACOMP_A_EN:1;             // 0      Analog Comparator A Enable
  };
  union DPWM1FLTABDET_REG {
    Uint32                      all;
    struct DPWM1FLTABDET_BITS   bit;
  };
  
  //-----------------------------------------------------------------------------
  // DPWM 1 Fault Detection Register
  //-----------------------------------------------------------------------------
  struct DPWM1FAULTDET_BITS {        // Bits   Description
    Uint32 rsvd1:1;                  // 31     Reserved
    Uint32 PWMB_DCOMP3_EN:1;         // 30     PWM B Digital Comparator 3 Enable
    Uint32 PWMB_DCOMP2_EN:1;         // 29     PWM B Digital Comparator 2 Enable
    Uint32 PWMB_DCOMP1_EN:1;         // 28     PWM B Digital Comparator 1 Enable
    Uint32 PWMB_DCOMP0_EN:1;         // 27     PWM B Digital Comparator 0 Enable
    Uint32 PWMB_FAULT3_EN:1;         // 26     PWM B Fault[3] Enable
    Uint32 PWMB_FAULT2_EN:1;         // 25     PWM B Fault[2] Enable
    Uint32 PWMB_FAULT1_EN:1;         // 24     PWM B Fault[1] Enable
    Uint32 PWMB_FAULT0_EN:1;         // 23     PWM B Fault[0] Enable
    Uint32 PWMB_ACOMP_G_EN:1;        // 22     PWM B Analog Comparator G Enable
    Uint32 PWMB_ACOMP_F_EN:1;        // 21     PWM B Analog Comparator F Enable
    Uint32 PWMB_ACOMP_E_EN:1;        // 20     PWM B Analog Comparator E Enable
    Uint32 PWMB_ACOMP_D_EN:1;        // 19     PWM B Analog Comparator D Enable
    Uint32 PWMB_ACOMP_C_EN:1;        // 18     PWM B Analog Comparator C Enable
    Uint32 PWMB_ACOMP_B_EN:1;        // 17     PWM B Analog Comparator B Enable
    Uint32 PWMB_ACOMP_A_EN:1;        // 16     PWM B Analog Comparator A Enable
    Uint32 rsvd0:1;                  // 15     Reserved
    Uint32 PWMA_DCOMP3_EN:1;         // 14     PWM B Digital Comparator 3 Enable
    Uint32 PWMA_DCOMP2_EN:1;         // 13     PWM B Digital Comparator 2 Enable
    Uint32 PWMA_DCOMP1_EN:1;         // 12     PWM B Digital Comparator 1 Enable
    Uint32 PWMA_DCOMP0_EN:1;         // 11     PWM B Digital Comparator 0 Enable
    Uint32 PWMA_FAULT3_EN:1;         // 10     PWM A Fault[3] Enable    
    Uint32 PWMA_FAULT2_EN:1;         // 9      PWM A Fault[2] Enable
    Uint32 PWMA_FAULT1_EN:1;         // 8      PWM A Fault[1] Enable
    Uint32 PWMA_FAULT0_EN:1;         // 7      PWM A Fault[0] Enable
    Uint32 PWMA_ACOMP_G_EN:1;        // 6      PWM A Analog Comparator G Enable
    Uint32 PWMA_ACOMP_F_EN:1;        // 5      PWM A Analog Comparator F Enable
    Uint32 PWMA_ACOMP_E_EN:1;        // 4      PWM A Analog Comparator E Enable
    Uint32 PWMA_ACOMP_D_EN:1;        // 3      PWM A Analog Comparator D Enable
    Uint32 PWMA_ACOMP_C_EN:1;        // 2      PWM A Analog Comparator C Enable
    Uint32 PWMA_ACOMP_B_EN:1;        // 1      PWM A Analog Comparator B Enable
    Uint32 PWMA_ACOMP_A_EN:1;        // 0      PWM A Analog Comparator A Enable   
  };
  union DPWM1FAULTDET_REG {
    Uint32                   all;
    struct DPWM1FAULTDET_BITS  bit;
  };

  //-----------------------------------------------------------------------------
  // DPWM 2 Current Limit Control Register
  //-----------------------------------------------------------------------------
  struct DPWM2CLIM_BITS {            // Bits   Description
    Uint32 rsvd0:15;                 // 31:17  Reserved
    Uint32 ANALOG_PCM_EN:1;          // 16     Analog Peak Current Detection Enable
    Uint32 DCOMP3_EN:1;              // 15     Digital Comparator 3 Enable
    Uint32 DCOMP2_EN:1;              // 14     Digital Comparator 2 Enable
    Uint32 DCOMP1_EN:1;              // 13     Digital Comparator 1 Enable
    Uint32 DCOMP0_EN:1;              // 12     Digital Comparator 0 Enable
    Uint32 rsvd1:1;                  // 11     Reserved - leave as zero
    Uint32 FAULT3_EN:1;              // 10     External FAULT[3] Current Limit Enable
    Uint32 FAULT2_EN:1;              // 9      External FAULT[2] Current Limit Enable
    Uint32 FAULT1_EN:1;              // 8      External FAULT[1] Current Limit Enable
    Uint32 FAULT0_EN:1;              // 7      External FAULT[0] Current Limit Enable
    Uint32 ACOMP_G_EN:1;             // 6      Analog Comparator G Enable
    Uint32 ACOMP_F_EN:1;             // 5      Analog Comparator F Enable
    Uint32 ACOMP_E_EN:1;             // 4      Analog Comparator E Enable
    Uint32 ACOMP_D_EN:1;             // 3      Analog Comparator D Enable
    Uint32 ACOMP_C_EN:1;             // 2      Analog Comparator C Enable
    Uint32 ACOMP_B_EN:1;             // 1      Analog Comparator B Enable
    Uint32 ACOMP_A_EN:1;             // 0      Analog Comparator A Enable  
  };
  union DPWM2CLIM_REG {
    Uint32                    all;
    struct DPWM2CLIM_BITS     bit;
  };

  //-----------------------------------------------------------------------------
  // DPWM 2 Fault AB Detction Register
  //-----------------------------------------------------------------------------
  struct DPWM2FLTABDET_BITS {        // Bits   Description
    Uint32 rsvd0:17;                 // 31:15  Reserved
    Uint32 DCOMP3_EN:1;              // 14     Digital Comparator 3 Enable
    Uint32 DCOMP2_EN:1;              // 13     Digital Comparator 2 Enable
    Uint32 DCOMP1_EN:1;              // 12     Digital Comparator 1 Enable
    Uint32 DCOMP0_EN:1;              // 11     Digital Comparator 0 Enable
    Uint32 FAULT3_EN:1;              // 10     External FAULT[3] Enable
    Uint32 FAULT2_EN:1;              // 9      External FAULT[2] Enable
    Uint32 FAULT1_EN:1;              // 8      External FAULT[1] Enable
    Uint32 FAULT0_EN:1;              // 7      External FAULT[0] Enable
    Uint32 ACOMP_G_EN:1;             // 6      Analog Comparator G Enable
    Uint32 ACOMP_F_EN:1;             // 5      Analog Comparator F Enable
    Uint32 ACOMP_E_EN:1;             // 4      Analog Comparator E Enable
    Uint32 ACOMP_D_EN:1;             // 3      Analog Comparator D Enable
    Uint32 ACOMP_C_EN:1;             // 2      Analog Comparator C Enable
    Uint32 ACOMP_B_EN:1;             // 1      Analog Comparator B Enable
    Uint32 ACOMP_A_EN:1;             // 0      Analog Comparator A Enable
  };
  union DPWM2FLTABDET_REG {
    Uint32                      all;
    struct DPWM2FLTABDET_BITS   bit;
  };
  
  //-----------------------------------------------------------------------------
  // DPWM 2 Fault Detection Register
  //-----------------------------------------------------------------------------
  struct DPWM2FAULTDET_BITS {        // Bits   Description
    Uint32 rsvd1:1;                  // 31     Reserved
    Uint32 PWMB_DCOMP3_EN:1;         // 30     PWM B Digital Comparator 3 Enable
    Uint32 PWMB_DCOMP2_EN:1;         // 29     PWM B Digital Comparator 2 Enable
    Uint32 PWMB_DCOMP1_EN:1;         // 28     PWM B Digital Comparator 1 Enable
    Uint32 PWMB_DCOMP0_EN:1;         // 27     PWM B Digital Comparator 0 Enable
    Uint32 PWMB_FAULT3_EN:1;         // 25     PWM B Fault[3] Enable
    Uint32 PWMB_FAULT2_EN:1;         // 25     PWM B Fault[2] Enable
    Uint32 PWMB_FAULT1_EN:1;         // 24     PWM B Fault[1] Enable
    Uint32 PWMB_FAULT0_EN:1;         // 23     PWM B Fault[0] Enable
    Uint32 PWMB_ACOMP_G_EN:1;        // 22     PWM B Analog Comparator G Enable
    Uint32 PWMB_ACOMP_F_EN:1;        // 21     PWM B Analog Comparator F Enable
    Uint32 PWMB_ACOMP_E_EN:1;        // 20     PWM B Analog Comparator E Enable
    Uint32 PWMB_ACOMP_D_EN:1;        // 19     PWM B Analog Comparator D Enable
    Uint32 PWMB_ACOMP_C_EN:1;        // 18     PWM B Analog Comparator C Enable
    Uint32 PWMB_ACOMP_B_EN:1;        // 17     PWM B Analog Comparator B Enable
    Uint32 PWMB_ACOMP_A_EN:1;        // 16     PWM B Analog Comparator A Enable
    Uint32 rsvd0:1;                  // 15     Reserved
    Uint32 PWMA_DCOMP3_EN:1;         // 14     PWM B Digital Comparator 3 Enable
    Uint32 PWMA_DCOMP2_EN:1;         // 13     PWM B Digital Comparator 2 Enable
    Uint32 PWMA_DCOMP1_EN:1;         // 12     PWM B Digital Comparator 1 Enable
    Uint32 PWMA_DCOMP0_EN:1;         // 11     PWM B Digital Comparator 0 Enable    
    Uint32 PWMA_FAULT3_EN:1;         // 10     PWM A Fault[3] Enable
    Uint32 PWMA_FAULT2_EN:1;         // 9      PWM A Fault[2] Enable
    Uint32 PWMA_FAULT1_EN:1;         // 8      PWM A Fault[1] Enable
    Uint32 PWMA_FAULT0_EN:1;         // 7      PWM A Fault[0] Enable
    Uint32 PWMA_ACOMP_G_EN:1;        // 6      PWM A Analog Comparator G Enable
    Uint32 PWMA_ACOMP_F_EN:1;        // 5      PWM A Analog Comparator F Enable
    Uint32 PWMA_ACOMP_E_EN:1;        // 4      PWM A Analog Comparator E Enable
    Uint32 PWMA_ACOMP_D_EN:1;        // 3      PWM A Analog Comparator D Enable
    Uint32 PWMA_ACOMP_C_EN:1;        // 2      PWM A Analog Comparator C Enable
    Uint32 PWMA_ACOMP_B_EN:1;        // 1      PWM A Analog Comparator B Enable
    Uint32 PWMA_ACOMP_A_EN:1;        // 0      PWM A Analog Comparator A Enable   
  };
  union DPWM2FAULTDET_REG {
    Uint32                   all;
    struct DPWM2FAULTDET_BITS  bit;
  };

  //-----------------------------------------------------------------------------
  // DPWM 3 Current Limit Control Register
  //-----------------------------------------------------------------------------
  struct DPWM3CLIM_BITS {            // Bits   Description
    Uint32 rsvd0:15;                 // 31:17  Reserved
    Uint32 ANALOG_PCM_EN:1;          // 16     Analog Peak Current Detection Enable
    Uint32 DCOMP3_EN:1;              // 15     Digital Comparator 3 Enable
    Uint32 DCOMP2_EN:1;              // 14     Digital Comparator 2 Enable
    Uint32 DCOMP1_EN:1;              // 13     Digital Comparator 1 Enable
    Uint32 DCOMP0_EN:1;              // 12     Digital Comparator 0 Enable
    Uint32 rsvd1:1;                  // 11     Reserved - leave as zero
    Uint32 FAULT3_EN:1;              // 10     External FAULT[3] Current Limit Enable
    Uint32 FAULT2_EN:1;              // 9      External FAULT[2] Current Limit Enable
    Uint32 FAULT1_EN:1;              // 8      External FAULT[1] Current Limit Enable
    Uint32 FAULT0_EN:1;              // 7      External FAULT[0] Current Limit Enable
    Uint32 ACOMP_G_EN:1;             // 6      Analog Comparator G Enable
    Uint32 ACOMP_F_EN:1;             // 5      Analog Comparator F Enable
    Uint32 ACOMP_E_EN:1;             // 4      Analog Comparator E Enable
    Uint32 ACOMP_D_EN:1;             // 3      Analog Comparator D Enable
    Uint32 ACOMP_C_EN:1;             // 2      Analog Comparator C Enable
    Uint32 ACOMP_B_EN:1;             // 1      Analog Comparator B Enable
    Uint32 ACOMP_A_EN:1;             // 0      Analog Comparator A Enable  
  };
  union DPWM3CLIM_REG {
    Uint32                    all;
    struct DPWM3CLIM_BITS     bit;
  };

  //-----------------------------------------------------------------------------
  // DPWM 3 Fault AB Detction Register
  //-----------------------------------------------------------------------------
  struct DPWM3FLTABDET_BITS {        // Bits   Description
    Uint32 rsvd0:17;                 // 31:15  Reserved
    Uint32 DCOMP3_EN:1;              // 14     Digital Comparator 3 Enable
    Uint32 DCOMP2_EN:1;              // 13     Digital Comparator 2 Enable
    Uint32 DCOMP1_EN:1;              // 12     Digital Comparator 1 Enable
    Uint32 DCOMP0_EN:1;              // 11     Digital Comparator 0 Enable
    Uint32 FAULT3_EN:1;              // 10     External FAULT[3] Enable
    Uint32 FAULT2_EN:1;              // 9      External FAULT[2] Enable
    Uint32 FAULT1_EN:1;              // 8      External FAULT[1] Enable
    Uint32 FAULT0_EN:1;              // 7      External FAULT[0] Enable
    Uint32 ACOMP_G_EN:1;             // 6      Analog Comparator G Enable
    Uint32 ACOMP_F_EN:1;             // 5      Analog Comparator F Enable
    Uint32 ACOMP_E_EN:1;             // 4      Analog Comparator E Enable
    Uint32 ACOMP_D_EN:1;             // 3      Analog Comparator D Enable
    Uint32 ACOMP_C_EN:1;             // 2      Analog Comparator C Enable
    Uint32 ACOMP_B_EN:1;             // 1      Analog Comparator B Enable
    Uint32 ACOMP_A_EN:1;             // 0      Analog Comparator A Enable
  };
  union DPWM3FLTABDET_REG {
    Uint32                      all;
    struct DPWM3FLTABDET_BITS   bit;
  };
  
  //-----------------------------------------------------------------------------
  // DPWM 3 Fault Detection Register
  //-----------------------------------------------------------------------------
  struct DPWM3FAULTDET_BITS {        // Bits   Description
    Uint32 rsvd1:1;                  // 31     Reserved
    Uint32 PWMB_DCOMP3_EN:1;         // 30     PWM B Digital Comparator 3 Enable
    Uint32 PWMB_DCOMP2_EN:1;         // 29     PWM B Digital Comparator 2 Enable
    Uint32 PWMB_DCOMP1_EN:1;         // 28     PWM B Digital Comparator 1 Enable
    Uint32 PWMB_DCOMP0_EN:1;         // 27     PWM B Digital Comparator 0 Enable
    Uint32 PWMB_FAULT3_EN:1;         // 26     PWM B Fault[3] Enable
    Uint32 PWMB_FAULT2_EN:1;         // 25     PWM B Fault[2] Enable
    Uint32 PWMB_FAULT1_EN:1;         // 24     PWM B Fault[1] Enable
    Uint32 PWMB_FAULT0_EN:1;         // 23     PWM B Fault[0] Enable
    Uint32 PWMB_ACOMP_G_EN:1;        // 22     PWM B Analog Comparator G Enable
    Uint32 PWMB_ACOMP_F_EN:1;        // 21     PWM B Analog Comparator F Enable
    Uint32 PWMB_ACOMP_E_EN:1;        // 20     PWM B Analog Comparator E Enable
    Uint32 PWMB_ACOMP_D_EN:1;        // 19     PWM B Analog Comparator D Enable
    Uint32 PWMB_ACOMP_C_EN:1;        // 18     PWM B Analog Comparator C Enable
    Uint32 PWMB_ACOMP_B_EN:1;        // 17     PWM B Analog Comparator B Enable
    Uint32 PWMB_ACOMP_A_EN:1;        // 16     PWM B Analog Comparator A Enable
    Uint32 rsvd0:1;                  // 15     Reserved
    Uint32 PWMA_DCOMP3_EN:1;         // 14     PWM B Digital Comparator 3 Enable
    Uint32 PWMA_DCOMP2_EN:1;         // 13     PWM B Digital Comparator 2 Enable
    Uint32 PWMA_DCOMP1_EN:1;         // 12     PWM B Digital Comparator 1 Enable
    Uint32 PWMA_DCOMP0_EN:1;         // 11     PWM B Digital Comparator 0 Enable
    Uint32 PWMA_FAULT3_EN:1;         // 10     PWM A Fault[3] Enable
    Uint32 PWMA_FAULT2_EN:1;         // 9      PWM A Fault[2] Enable
    Uint32 PWMA_FAULT1_EN:1;         // 8      PWM A Fault[1] Enable
    Uint32 PWMA_FAULT0_EN:1;         // 7      PWM A Fault[0] Enable
    Uint32 PWMA_ACOMP_G_EN:1;        // 6      PWM A Analog Comparator G Enable
    Uint32 PWMA_ACOMP_F_EN:1;        // 5      PWM A Analog Comparator F Enable
    Uint32 PWMA_ACOMP_E_EN:1;        // 4      PWM A Analog Comparator E Enable
    Uint32 PWMA_ACOMP_D_EN:1;        // 3      PWM A Analog Comparator D Enable
    Uint32 PWMA_ACOMP_C_EN:1;        // 2      PWM A Analog Comparator C Enable
    Uint32 PWMA_ACOMP_B_EN:1;        // 1      PWM A Analog Comparator B Enable
    Uint32 PWMA_ACOMP_A_EN:1;        // 0      PWM A Analog Comparator A Enable    
  };
  union DPWM3FAULTDET_REG {
    Uint32                     all;
    struct DPWM3FAULTDET_BITS  bit;
  };

  //-----------------------------------------------------------------------------
  // HFO Fail Detect Register
  //-----------------------------------------------------------------------------
  struct HFOFAILDET_BITS {           // Bits   Description
    Uint32 rsvd0:14;                 // 31:18  Reserved
    Uint32 HFO_FAIL_THRESH:17;       // 17:1   High Frequency Oscillator Fail Threshold
    Uint32 HFO_DETECT_EN:1;          // 0      High Frequency Oscillator Fail Detect Enable
  };
  union HFOFAILDET_REG {
    Uint32                   all;
    struct HFOFAILDET_BITS   bit;
  };

  //-----------------------------------------------------------------------------
  // LFO Fail Detect Register
  //-----------------------------------------------------------------------------
  struct LFOFAILDET_BITS {           // Bits   Description
    Uint32 rsvd0:25;                 // 31:6   Reserved
    Uint32 LFO_FAIL_THRESH:5;        // 6:2    Low Frequency Oscillator Fail Threshold
    Uint32 LFO_FAIL_INT_EN:1;        // 1      Low Frequency Oscillator Fail Interrupt Enable
    Uint32 LFO_DETECT_EN:1;          // 0      Low Frequency Oscillator Fail Detect Enable
  };
  union LFOFAILDET_REG {
    Uint32                   all;
    struct LFOFAILDET_BITS   bit;
  };

  //-----------------------------------------------------------------------------
  // IDE Control Register
  //-----------------------------------------------------------------------------
  struct IDECTRL_BITS {              // Bits   Description
    Uint32 DCM_LIMIT_H:8;            // 31:24  DCM Upper Hysteresis
    Uint32 DCM_LIMIT_L:8;            // 23:16  DCM Lower Hysteresis
    Uint32 rsvd0:2;                  // 15:14  Reserved
    Uint32 DCM_INT_EN:1;             // 13     DCM Interrupt Enable
    Uint32 IDE_KD:13;                // 12:0   IDE KD Factor used to calculate Db
  };
  union IDECTRL_REG {
    Uint32                   all;
    struct IDECTRL_BITS      bit;
  };

  //=============================================================================
  // Fault Mux Module Register File
  //=============================================================================
  struct FAULT_MUX_REGS {
    union ACOMPCTRL0_REG        ACOMPCTRL0;       // Analog Comparator Control 0 Register
    union ACOMPCTRL1_REG        ACOMPCTRL1;       // Analog Comparator Control 1 Register
    union ACOMPCTRL2_REG        ACOMPCTRL2;       // Analog Comparator Control 2 Register
    union ACOMPCTRL3_REG        ACOMPCTRL3;       // Analog Comparator Control 3 Register
    union EXTFAULTCTRL_REG      EXTFAULTCTRL;     // External Fault Control Register
    union FAULTMUXINTSTAT_REG   FAULTMUXINTSTAT;  // Fault Mux Interrupt Status Register
    union FAULTMUXRAWSTAT_REG   FAULTMUXRAWSTAT;  // Fault Mux Raw Status Register
    union COMPRAMP0_REG         COMPRAMP0;        // Comparator Ramp Control 0 Register
    union DCOMPCTRL0_REG        DCOMPCTRL0;       // Digital Comparator Control 0 Register
    union DCOMPCTRL1_REG        DCOMPCTRL1;       // Digital Comparator Control 1 Register
    union DCOMPCTRL2_REG        DCOMPCTRL2;       // Digital Comparator Control 2 Register
    union DCOMPCTRL3_REG        DCOMPCTRL3;       // Digital Comparator Control 3 Register
    union DCOMPCNTSTAT_REG      DCOMPCNTSTAT;     // Digital Comparator Counter Status Register
    union DPWM0CLIM_REG         DPWM0CLIM;        // DPWM 0 Current Limit Control Register
    union DPWM0FLTABDET_REG     DPWM0FLTABDET;    // DPWM 0 Fault AB Detection Register
    union DPWM0FAULTDET_REG     DPWM0FAULTDET;    // DPWM 0 Fault Detection Register
    Uint32                      RESERVED0;        // Reserved
    union DPWM1CLIM_REG         DPWM1CLIM;        // DPWM 1 Current Limit Control Register
    union DPWM1FLTABDET_REG     DPWM1FLTABDET;    // DPWM 1 Fault AB Detection Register
    union DPWM1FAULTDET_REG     DPWM1FAULTDET;    // DPWM 1 Fault Detection Register
    Uint32                      RESERVED1;        // Reserved
    union DPWM2CLIM_REG         DPWM2CLIM;        // DPWM 2 Current Limit Control Register
    union DPWM2FLTABDET_REG     DPWM2FLTABDET;    // DPWM 2 Fault AB Detection Register
    union DPWM2FAULTDET_REG     DPWM2FAULTDET;    // DPWM 2 Fault Detection Register
    Uint32                      RESERVED2;        // Reserved
    union DPWM3CLIM_REG         DPWM3CLIM;        // DPWM 3 Current Limit Control Register
    union DPWM3FLTABDET_REG     DPWM3FLTABDET;    // DPWM 3 Fault AB Detection Register
    union DPWM3FAULTDET_REG     DPWM3FAULTDET;    // DPWM 3 Fault Detection Register
    Uint32                      RESERVED3;        // Reserved
    union HFOFAILDET_REG        HFOFAILDET;       // High Frequency Oscillator Fail Detect Register
    union LFOFAILDET_REG        LFOFAILDET;       // Low Frequency Oscillator Fail Detect Register
    union IDECTRL_REG           IDECTRL;          // IDE Control Register
  };
  
  //-----------------------------------------------------------------------------
  // Fault Mux Module External References & Function Declarations:
  //-----------------------------------------------------------------------------
  extern volatile struct FAULT_MUX_REGS FaultMuxRegs;


#ifdef __cplusplus
}       // end of extern "C"
#endif

#endif  // end of CYCLONE_LOOP_MUX_H definition

//===========================================================================
// End of file
//===========================================================================
