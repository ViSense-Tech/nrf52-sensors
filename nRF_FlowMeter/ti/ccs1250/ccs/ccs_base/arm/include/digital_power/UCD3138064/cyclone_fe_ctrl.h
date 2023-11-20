//###############################################################################
//
// FILE:   cyclone_fe_ctrl.h
//
// TITLE:  Cyclone Front End Control Register Definitions.
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

#ifndef CYCLONE_FE_CTRL_H
#define CYCLONE_FE_CTRL_H

#ifdef __cplusplus
extern "C" {
#endif

  //=============================================================================
  // Front End Control Individual Register Bit Definitions
  //=============================================================================

  //-----------------------------------------------------------------------------
  // Ramp Control Register
  //-----------------------------------------------------------------------------
  struct RAMPCTRL_BITS {            // bits   description
    Uint32 rsvd1:2;                 // 31:30  Reserved
    Uint32 SYNC_FET_RAMP_START:14;  // 29:16  SyncFET Ramp Start Value
    Uint32 rsvd0:2;                 // 15:14  Reserved
    Uint32 ANALOG_PCM_INT_EN:1;     // 13     Analog Peak Current Interrupt Enable
    Uint32 RAMP_SAT_EN:1;           // 12     Ramp Saturation Enable
    Uint32 RAMP_COMP_INT_EN:1;      // 11     Ramp Complete Interrupt Enable
    Uint32 RAMP_DLY_INT_EN:1;       // 10     Ramp Delay Complete Interrupt Enable
    Uint32 PREBIAS_INT_EN:1;        // 9      Pre-Bias Complete Interrupt Enable
    Uint32 PCM_START_SEL:1;         // 8      Peak Current Mode Start Select
    Uint32 SYNC_FET_EN:1;           // 7      Enable use of Ramp for SyncFET
    Uint32 MASTER_SEL:2;            // 6:5    Master Ramp I/F Select
    Uint32 SLAVE_COMP_EN:1;         // 4      Sync ramp to Master Complete
    Uint32 SLAVE_DELAY_EN:1;        // 3      Sync ramp to Master Delay Complete
    Uint32 CONTROL_EN:1;            // 2      Sync ramp to Control assertion
    Uint32 FIRMWARE_START:1;        // 1      Start ramp with firmware
    Uint32 RAMP_EN:1;               // 0      Ramp Enable
  }; 
  union RAMPCTRL_REG {
    Uint32                   all;
    struct RAMPCTRL_BITS     bit;
  };
  
  //-----------------------------------------------------------------------------
  // Ramp Status Register
  //-----------------------------------------------------------------------------
  struct RAMPSTAT_BITS {            // bits   description
    Uint32 rsvd0:19;                // 31:13  Reserved
    Uint32 EADC_DONE_RAW:1;         // 12     EADC Conversion Raw Status
    Uint32 ANALOG_PCM_INT_STATUS:1; // 11     Analog Peak Current Latched Status
    Uint32 RAMP_COMP_INT_STATUS:1;  // 10     Ramp Complete Latched Status
    Uint32 RAMP_DLY_INT_STATUS:1;   // 9      Ramp Delay Complete Latched Status
    Uint32 PREBIAS_INT_STATUS:1;    // 8      Prebias Complete Latched Status
    Uint32 EADC_SAT_HIGH:1;         // 7      EADC Saturation High
    Uint32 EADC_SAT_LOW:1;          // 6      EADC Saturation Low
    Uint32 EADC_EOC:1;              // 5      EADC End of Conversion 
    Uint32 PREBIAS_BUSY:1;          // 4      Prebias Busy Indication
    Uint32 RAMP_BUSY:1;             // 3      Ramp Busy Indication
    Uint32 RAMP_COMP_STATUS:1;      // 2      Ramp Complete Indication
    Uint32 RAMP_DLY_STATUS:1;       // 1      Ramp Delay Indication
    Uint32 PREBIAS_STATUS:1;        // 0      Prebias Indication
  };
  union RAMPSTAT_REG {
    Uint32                   all;
    struct RAMPSTAT_BITS     bit;
  };
  
  //-----------------------------------------------------------------------------
  // Ramp Cycle Register
  //-----------------------------------------------------------------------------
  struct RAMPCYCLE_BITS {           // bits   Description
    Uint32 rsvd1:8;                 // 31:24  Reserved
    Uint32 DELAY_CYCLES:16;         // 23:8   Number of Delay Cycles before ramp
    Uint32 rsvd0:1;                 // 7      Reserved
    Uint32 SWITCH_CYC_PER_STEP:7;   // 6:0    Number of switching cycles per step
  };
  union RAMPCYCLE_REG {
    Uint32                   all;
    struct RAMPCYCLE_BITS    bit;
  };

  //-----------------------------------------------------------------------------
  // EADC DAC Value Register
  //-----------------------------------------------------------------------------
  struct EADCDAC_BITS {             // Bits   Description
    Uint32 rsvd1:16;                // 31:16  Reserved
    Uint32 DAC_DITHER_EN:1;         // 15     DAC Dithering Enable
    Uint32 rsvd0:1;                 // 14     Reserved
    Uint32 DAC_VALUE:14;            // 13:0   DAC Value
  };
  union EADCDAC_REG {
    Uint32                  all;
    struct EADCDAC_BITS     bit;
  };

  //-----------------------------------------------------------------------------
  // Ramp DAC Ending Value Register
  //-----------------------------------------------------------------------------
  struct RAMPDACEND_BITS {          // Bits   Description
    Uint32 rsvd1:18;                // 31:14  Reserved
    Uint32 RAMP_DAC_VALUE:14;       // 13:0   Ramp Ending DAC Value
  };
  union RAMPDACEND_REG {
    Uint32                  all;
    struct RAMPDACEND_BITS  bit;
  };
  
  //-----------------------------------------------------------------------------
  // DAC Step Register
  //-----------------------------------------------------------------------------
  struct DACSTEP_BITS {            // Bits   Description
    Uint32 rsvd0:14;               // 31:18  Reserved
    Uint32 DAC_STEP:18;            // 17:0   DAC Step
  };
  union DACSTEP_REG {
    Uint32               all;
    struct DACSTEP_BITS  bit;
  };
  
  //-----------------------------------------------------------------------------
  // DAC Saturation Step Register 
  //-----------------------------------------------------------------------------
  struct DACSATSTEP_BITS {         // Bits   Description 
    Uint32 rsvd0:18;               // 31:14  Reserved
    Uint32 DAC_SAT_STEP:14;        // 13:0   DAC SaturationStep
  };
  union DACSATSTEP_REG {
    Uint32                  all;
    struct DACSATSTEP_BITS  bit;
  };

  //-----------------------------------------------------------------------------
  // EADC Trim Register
  //-----------------------------------------------------------------------------
  struct EADCTRIM_BITS {          // Bits   Description 
    Uint32 rsvd3:2;               // 31:30  Reserved
    Uint32 GAIN3_TRIM:6;          // 29:24  Gain3 Trim
    Uint32 rsvd2:2;               // 23:22  Reserved
    Uint32 GAIN2_TRIM:6;          // 21:16  Gain2 Trim
    Uint32 rsvd1:2;               // 15:14  Reserved
    Uint32 GAIN1_TRIM:6;          // 13:8   Gain1 Trim
    Uint32 rsvd0:2;               // 7:6    Reserved
    Uint32 GAIN0_TRIM:6;          // 5:0    Gain0 Trim
  };
  union EADCTRIM_REG {
    Uint32                  all;
    struct EADCTRIM_BITS    bit;
  };

  //-----------------------------------------------------------------------------
  // EADC Control Register 
  //-----------------------------------------------------------------------------
  struct EADCCTRL_BITS {           // Bits   Description 
    Uint32 rsvd0:3;                // 31:29  Reserved
    Uint32 D2S_COMP_EN:1;          // 28     Analog Front End Ramp Comparator Enable
    Uint32 EN_HYST_HIGH:1;         // 27     Increase comparator trip point
    Uint32 EN_HYST_LOW:1;          // 26     Decrease comparator trip point
    Uint32 SAMP_TRIG_SCALE:4;      // 25:22  Sample Trigger Scale
    Uint32 FRAME_SYNC_EN:1;        // 21     Frame Sync Enable
    Uint32 SCFE_CNT_RST:1;         // 20     Switched Cap Front End Counter Reset
    Uint32 SCFE_CNT_INIT:4;        // 19:16  Initial Value for Switched Cap Front End Counter
    Uint32 EADC_INV:1;             // 15     Invert EADC Data
    Uint32 AUTO_GAIN_SHIFT_MODE:1; // 14     Auto Gain Shifting Mode Select
    Uint32 AUTO_GAIN_SHIFT_EN:1;   // 13     Auto Gain Shifting Enable
    Uint32 AVG_WEIGHT_EN:1;        // 12     Averaging Weight Enable
    Uint32 AVG_SPATIAL_EN:1;       // 11     Averaging Spatial Enable
    Uint32 AVG_MODE_SEL:2;         // 10:9   Averaging Mode Select
    Uint32 EADC_MODE:3;            // 8:6    EADC Mode Select
    Uint32 AFE_GAIN:2;             // 5:4    AFE Gain Setting
    Uint32 SCFE_GAIN_FILTER_SEL:1; // 3      SCFE Gain Filter Enable
    Uint32 SCFE_CLK_DIV_2:1;       // 2      Front End sampling select
    Uint32 SCFE_ENA:1;             // 1      SCFE Enable
    Uint32 EADC_ENA:1;             // 0      EADC Enable
  };
  union EADCCTRL_REG {
    Uint32                 all;
    struct EADCCTRL_BITS   bit;
  };
    
  //-----------------------------------------------------------------------------
  // Analog Control Register
  //-----------------------------------------------------------------------------
  struct ACTRL_BITS {              // Bits   Description 
    Uint32 rsvd1:16;               // 31:16  Reserved
    Uint32 EADC_REF_TRIM:6;        // 15:10  EADC Reference Trim
    Uint32 EADC_REF_RESET:1;       // 9      EADC Reference Reset
    Uint32 EADC_REF_EN:1;          // 8      EADC Reference Enable
    Uint32 rsvd0:3;                // 7:5    Reserved
    Uint32 EADC_GAIN_CAL:1;        // 4      EADC Gain Calibration
    Uint32 EADC_OFFSET_CAL:1;      // 3      EADC Offset Calibration
    Uint32 INT_REF_SEL:1;          // 2      Internal Reference Select
    Uint32 EXT_V_SE_SEL:1;         // 1      Selects V_SE
    Uint32 ANALOG_ENA:1;           // 0      Analog Front Enable
  };
  union ACTRL_REG {
    Uint32                all;
    struct ACTRL_BITS     bit;
  };

  //-----------------------------------------------------------------------------
  // Pre-Bias Control Register 0 
  //-----------------------------------------------------------------------------
  struct PREBIASCTRL0_BITS {       // Bits   Description 
    Uint32 rsvd0:14;               // 31:18  Reserved
    Uint32 PRE_BIAS_POL:1;         // 17     Prebias polarity
    Uint32 PRE_BIAS_EN:1;          // 16     Prebias Enable
    Uint32 PRE_BIAS_RANGE:8;       // 15:8   Prebias Range
    Uint32 PRE_BIAS_LIMIT:8;       // 7:0    Prebias Limit
  };
  union PREBIASCTRL0_REG {
    Uint32                    all;
    struct PREBIASCTRL0_BITS  bit;
  };

  //-----------------------------------------------------------------------------
  // Pre-Bias Control Register 1 
  //-----------------------------------------------------------------------------
  struct PREBIASCTRL1_BITS {       // Bits   Description 
    Uint32 rsvd1:8;                // 31:24  Reserved
    Uint32 SAMPLES_PER_ADJ:8;      // 23:16  Samples per adjustment
    Uint32 rsvd0:2;                // 15:14  Reserved
    Uint32 MAX_DAC_ADJ:14;         // 13:0   Maximum DAC Adjustment
  };
  union PREBIASCTRL1_REG {
    Uint32                    all;
    struct PREBIASCTRL1_BITS  bit;
  };

  //-----------------------------------------------------------------------------
  // SAR Control Register
  //-----------------------------------------------------------------------------
  struct SARCTRL_BITS {              // Bits   Description 
    Uint32 EADC_WINDOW_2:8;          // 31:24  EADC Window 2 Setting
    Uint32 EADC_WINDOW_1:8;          // 23:16  EADC Window 1 Setting
    Uint32 SAR_RANGE:8;              // 15:8   SAR Range Setting
    Uint32 rsvd0:6;                  // 7:2    Reserved
    Uint32 SAR_RESOLUTION:2;         // 1:0    SAR Final Resolution
  };
  union SARCTRL_REG {
    Uint32                    all;
    struct SARCTRL_BITS       bit;
  };
  
  //-----------------------------------------------------------------------------
  // SAR Timing Register
  //-----------------------------------------------------------------------------
  struct SARTIMING_BITS {           // Bits   Description
    Uint32 rsvd2:21;                // 31:11  Reserved
    Uint32 SAR_TIMING_UPPER:3;      // 10:8   SAR Timing setting for upper bits
    Uint32 rsvd1:1;                 // 7      Reserved
    Uint32 SAR_TIMING_MID:3;        // 6:4    SAR Timing setting for mid bits
    Uint32 rsvd0:1;                 // 3      Reserved
    Uint32 SAR_TIMING_LOWER:3;      // 2:0    SAR Timing setting for lower bits
  };
  union SARTIMING_REG {
    Uint32                   all;
    struct SARTIMING_BITS    bit;
  };

  //-----------------------------------------------------------------------------
  // EADC Value Register
  //-----------------------------------------------------------------------------
  struct EADCVALUE_BITS {           // Bits   Description 
    Uint32 rsvd1:6;                 // 31:26  Reserved
    Uint32 ABS_VALUE:10;            // 25:16  Absolute Value
	Uint32 EADC_SAT_HIGH:1;          // 15     Saturation High Indicator
	Uint32 EADC_SAT_LOW:1;           // 14     Saturation Low Indicator
    Uint32 rsvd0:5;                 // 13:9   Reserved
    int32 ERROR_VALUE:9;           // 8:0    Error Value
  };
  union EADCVALUE_REG {
    Uint32                  all;
    struct EADCVALUE_BITS   bit;
  };

  //-----------------------------------------------------------------------------
  // EADC Raw Value Register
  //-----------------------------------------------------------------------------
  struct EADCRAWVALUE_BITS {        // Bits   Description
    Uint32 rsvd0:23;                // 31:9   Reserved
    int32 RAW_ERROR_VALUE:9;       // 8:0    Raw Error Value
  };
  union EADCRAWVALUE_REG {
    Uint32                    all;
    struct EADCRAWVALUE_BITS  bit;
  };

  //-----------------------------------------------------------------------------
  // DAC Status Register 
  //-----------------------------------------------------------------------------
  struct DACSTAT_BITS {             // Bits   Description 
    Uint32 rsvd0:22;                // 31:10  Reserved
    Uint32 DAC_VALUE:10;            // 9:0    Current DAC Value
  };
  union DACSTAT_REG {
    Uint32                all;
    struct DACSTAT_BITS   bit;
  };

  //=============================================================================
  // Front End Control Module Register File
  //=============================================================================
  struct FE_CTRL_REGS {
    union RAMPCTRL_REG        RAMPCTRL;         // Ramp Control Register
    union RAMPSTAT_REG        RAMPSTAT;         // Ramp Status Register
    union RAMPCYCLE_REG       RAMPCYCLE;        // Ramp Cycle Register
    union EADCDAC_REG         EADCDAC;          // EADC DAC Value Register
    union RAMPDACEND_REG      RAMPDACEND;       // Ramp DAC Ending Value Register
    union DACSTEP_REG         DACSTEP;          // DAC Step Register
    union DACSATSTEP_REG      DACSATSTEP;       // DAC Saturation Step Register
    union EADCTRIM_REG        EADCTRIM;         // EADC Trim Register
    union EADCCTRL_REG        EADCCTRL;         // EADC Control Register
    union ACTRL_REG           ACTRL;            // Analog Control Register
    union PREBIASCTRL0_REG    PREBIASCTRL0;     // Pre-bias Control Register 0
    union PREBIASCTRL1_REG    PREBIASCTRL1;     // Pre-bias Control Register 1
    union SARCTRL_REG         SARCTRL;          // SAR Control Register
    union SARTIMING_REG       SARTIMING;        // SAR Timing Register
    union EADCVALUE_REG       EADCVALUE;        // EADC Value Register
    union EADCRAWVALUE_REG    EADCRAWVALUE;     // EADC Raw Value Register
    union DACSTAT_REG         DACSTAT;          // Current DAC Value Register
  };
  
  //-----------------------------------------------------------------------------
  // ADC Module External References & Function Declarations:
  //-----------------------------------------------------------------------------
  extern volatile struct FE_CTRL_REGS FeCtrl0Regs;
  extern volatile struct FE_CTRL_REGS FeCtrl1Regs;
  extern volatile struct FE_CTRL_REGS FeCtrl2Regs;


#ifdef __cplusplus
}       // end of extern "C"
#endif

#endif  // end of CYCLONE_FE_CTRL_H definition

//===========================================================================
// End of file
//===========================================================================
