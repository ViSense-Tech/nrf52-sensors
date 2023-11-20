//###########################################################################
//
// FILE:   cyclone_adc.h
//
// TITLE:  Cyclone 12-bit Analog-to-Digital Converter Register Definitions.
//
// NOTES:
//  1) Bitfields have been defined for big-endian only.
//###########################################################################
//
//  Ver  | dd mmm yyyy | Who  | Description of changes
// ======|=============|======|==============================================
//  1.00 | 12 Aug 2009 | CMF  | Started with cyclone_adc.h.
//       |             |      | Updated for 1.0 Memory map document.
//       |             |      |
//
//  Texas Instruments, Inc
//  Copyright Texas Instruments 2008. All rights reserved.
//###########################################################################

#ifndef CYCLONE_ADC_H
#define CYCLONE_ADC_H

#ifdef __cplusplus
extern "C" {
#endif

  //===============================================================================
  // 12-bit Analog-to-Digital Converter Individual Register Bit Definitions
  //===============================================================================

  //-----------------------------------------------------------------------------
  // ADC Control Register 1 bit definitions
  //-----------------------------------------------------------------------------
  struct ADCCTRL_BITS {             // bits   description
    Uint32 EXT_TRIG_DLY:8;          // 31:24  External ADC Trigger Delay
    Uint32 EXT_TRIG_GPIO_VAL:1;     // 23     ADC External Trigger GPIO Value
    Uint32 EXT_TRIG_GPIO_DIR:1;     // 22     ADC External Trigger GPIO Direction
    Uint32 EXT_TRIG_GPIO_EN:1;      // 21     ADC External Trigger GPIO Enable
    Uint32 EXT_TRIG_EN:1;           // 20     External ADC Trigger Enable
    Uint32 EXT_TRIG_SEL:4;          // 19:16  External ADC Trigger Select
    Uint32 SAMPLING_SEL:3;          // 15:13  Sampling Select 
    Uint32 ADC_SEL_REF:1;           // 12     ADC Reference Select 
    Uint32 ADC_ROUND:1;             // 11     ADC Rounding Enable
    Uint32 BYPASS_EN:3;             // 10:8   Dual Sample and Hold Bypass
    Uint32 MAX_CONV:4;              // 7:4    Maximum Number of Conversions
    Uint32 SINGLE_SWEEP:1;          // 3      Single Loop Sweep Select
    Uint32 SW_START:1;              // 2      Software start of conversion
    Uint32 ADC_INT_EN:1;            // 1      ADC End of Conversion Interrupt
    Uint32 ADC_EN:1;                // 0      ADC Enable
  }; 
  union ADCCTRL_REG {
    Uint32                  all;
    struct ADCCTRL_BITS     bit;
  };
  
  //-----------------------------------------------------------------------------
  // ADC Status Register
  //-----------------------------------------------------------------------------
  struct ADCSTAT_BITS {            // bits    description
    Uint32 rsvd:25;                // 31:7    Reserved
    Uint32 CURRENT_CH:4;           // 6:3     Current Channel
    Uint32 ADC_EXT_TRIG_VAL:1;     // 2       ADC External Trigger Pin Value
    Uint32 ADC_INT_RAW:1;          // 1       End of Conversion Status, Raw
    Uint32 ADC_INT:1;              // 0       Latched Interrupt Status
  };
  union ADCSTAT_REG {
    Uint32                  all;
    struct ADCSTAT_BITS     bit;
  };

  //-------------------------------------------------------------------------------
  // ADC Test Control Register bit definitions
  // (Reserved for TI use)
  //-------------------------------------------------------------------------------
  struct ADCTSTCTRL_BITS {          // bits   description
    Uint32 rsvd1:30;                // 31:1   reserved
    Uint32 ADC_SH_BUFFER_EN:1;      // 1      ADC Sample/Hold Buffer override  enable
    Uint32 rsvd0:1;                 // 0      Reserved
  };
  union ADCTSTCTRL_REG {
    Uint32                      all;
    struct ADCTSTCTRL_BITS      bit;
  };

  //-----------------------------------------------------------------------------
  // ADC Sequence Select 0 Register bit definitions
  //-----------------------------------------------------------------------------
  struct ADCSEQSEL0_BITS {         // bits   description
    Uint32 rsvd3:3;                // 31:29  reserved
    Uint32 SEQ3_SH:1;              // 28     Dual channel sequence select
    Uint32 SEQ3:4;                 // 27:24  Conversion #3 channel
    Uint32 rsvd2:3;                // 23:21  reserved
    Uint32 SEQ2_SH:1;              // 20     Dual channel sequence select
    Uint32 SEQ2:4;                 // 19:16  Conversion #2 channel
    Uint32 rsvd1:3;                // 15:13  reserved
    Uint32 SEQ1_SH:1;              // 12     Dual channel sequence select
    Uint32 SEQ1:4;                 // 11:8   Conversion #1 channel
    Uint32 rsvd0:3;                // 7:5    reserved
    Uint32 SEQ0_SH:1;              // 4      Dual channel sequence select
    Uint32 SEQ0:4;                 // 3:0    Conversion #0 channel
  };
  union ADCSEQSEL0_REG {
    Uint32                     all;
    struct ADCSEQSEL0_BITS     bit;
  };
  
  //-----------------------------------------------------------------------------
  // ADC Sequence Select 1 Register bit definitions
  //-----------------------------------------------------------------------------
  struct ADCSEQSEL1_BITS {         // bits   description
    Uint32 rsvd3:3;                // 31:29  reserved
    Uint32 SEQ7_SH:1;              // 28     Dual channel sequence select
    Uint32 SEQ7:4;                 // 27:24  Conversion #7 channel
    Uint32 rsvd2:3;                // 23:21  reserved
    Uint32 SEQ6_SH:1;              // 20     Dual channel sequence select
    Uint32 SEQ6:4;                 // 19:16  Conversion #6 channel
    Uint32 rsvd1:3;                // 15:13  reserved
    Uint32 SEQ5_SH:1;              // 12     Dual channel sequence select
    Uint32 SEQ5:4;                 // 11:8   Conversion #5 channel
    Uint32 rsvd0:3;                // 7:5    reserved
    Uint32 SEQ4_SH:1;              // 4      Dual channel sequence select
    Uint32 SEQ4:4;                 // 3:0    Conversion #4 channel
  };
  union ADCSEQSEL1_REG {
    Uint32                     all;
    struct ADCSEQSEL1_BITS     bit;
  };  
  
  //-----------------------------------------------------------------------------
  // ADC Sequence Select 2 Register bit definitions
  //-----------------------------------------------------------------------------
  struct ADCSEQSEL2_BITS {         // bits   description
    Uint32 rsvd3:3;                // 31:29  reserved
    Uint32 SEQ11_SH:1;             // 28     Dual channel sequence select
    Uint32 SEQ11:4;                // 27:24  Conversion #11 channel
    Uint32 rsvd2:3;                // 23:21  reserved
    Uint32 SEQ10_SH:1;             // 20     Dual channel sequence select
    Uint32 SEQ10:4;                // 19:16  Conversion #10 channel
    Uint32 rsvd1:3;                // 15:13  reserved
    Uint32 SEQ9_SH:1;              // 12     Dual channel sequence select
    Uint32 SEQ9:4;                 // 11:8   Conversion #9 channel
    Uint32 rsvd0:3;                // 7:5    reserved
    Uint32 SEQ8_SH:1;              // 4      Dual channel sequence select
    Uint32 SEQ8:4;                 // 3:0    Conversion #8 channel
  };
  union ADCSEQSEL2_REG {
    Uint32                     all;
    struct ADCSEQSEL2_BITS     bit;
  };   
  
  //-----------------------------------------------------------------------------
  // ADC Sequence Select 3 Register bit definitions
  //-----------------------------------------------------------------------------
  struct ADCSEQSEL3_BITS {         // bits   description
    Uint32 rsvd3:3;                // 31:29  reserved
    Uint32 SEQ15_SH:1;             // 28     Dual channel sequence select
    Uint32 SEQ15:4;                // 27:24  Conversion #15 channel
    Uint32 rsvd2:3;                // 23:21  reserved
    Uint32 SEQ14_SH:1;             // 20     Dual channel sequence select
    Uint32 SEQ14:4;                // 19:16  Conversion #14 channel
    Uint32 rsvd1:3;                // 15:13  reserved
    Uint32 SEQ13_SH:1;             // 12     Dual channel sequence select
    Uint32 SEQ13:4;                // 11:8   Conversion #13 channel
    Uint32 rsvd0:3;                // 7:5    reserved
    Uint32 SEQ12_SH:1;             // 4      Dual channel sequence select
    Uint32 SEQ12:4;                // 3:0    Conversion #12 channel
  };
  union ADCSEQSEL3_REG {
    Uint32                     all;
    struct ADCSEQSEL3_BITS     bit;
  };  

  //-----------------------------------------------------------------------------
  // ADC Result Register bit definitions
  //-----------------------------------------------------------------------------
  struct ADCRESULT_BITS {          // bits   description
    Uint32 rsvd0:20;               // 31:12  reserved
    Uint32 RESULT:12;              // 11:0   Conversion result
  };
  union ADCRESULT_REG {
    Uint32                     all;
    struct ADCRESULT_BITS     bit;
  };
  
  //-----------------------------------------------------------------------------
  // ADC Averaged Result Register bit definitions
  //-----------------------------------------------------------------------------
  struct ADCAVGRESULT_BITS {          // bits   description
    Uint32 rsvd0:20;               // 31:12  reserved
    Uint32 RESULT:12;              // 11:0   Conversion result
  };
  union ADCAVGRESULT_REG {
    Uint32                     all;
    struct ADCAVGRESULT_BITS   bit;
  }; 

  //-----------------------------------------------------------------------------
  // ADC Digital Compare Limits x Register bit definitions
  //-----------------------------------------------------------------------------
  struct ADCCOMPLIM_BITS {         // bits   description
    Uint32 rsvd1:4;                // 31:28  reserved
    Uint32 UPPER_LIMIT:12;         // 27:16  Upper limit
    Uint32 rsvd0:4;                // 15:12  reserved
    Uint32 LOWER_LIMIT:12;         // 11:0   Lower limit
  };
  union ADCCOMPLIM_REG {
    Uint32                     all;
    struct ADCCOMPLIM_BITS    bit;
  };
  
  //-----------------------------------------------------------------------------
  // ADC Digital Comparator Enable Register bit definitions
  //-----------------------------------------------------------------------------
  struct ADCCOMPEN_BITS {          // bits   description
    Uint32 rsvd2:4;                // 31:28  reserved
    Uint32 COMP5_UP_INT_EN:1;      // 27     Comparator 5 Upper Interrupt Enable
    Uint32 COMP5_LO_INT_EN:1;      // 26     Comparator 5 Lower Interrupt Enable
    Uint32 COMP4_UP_INT_EN:1;      // 25     Comparator 4 Upper Interrupt Enable
    Uint32 COMP4_LO_INT_EN:1;      // 24     Comparator 4 Lower Interrupt Enable
    Uint32 COMP3_UP_INT_EN:1;      // 23     Comparator 3 Upper Interrupt Enable
    Uint32 COMP3_LO_INT_EN:1;      // 22     Comparator 3 Lower Interrupt Enable
    Uint32 COMP2_UP_INT_EN:1;      // 21     Comparator 2 Upper Interrupt Enable
    Uint32 COMP2_LO_INT_EN:1;      // 20     Comparator 2 Lower Interrupt Enable
    Uint32 COMP1_UP_INT_EN:1;      // 19     Comparator 1 Upper Interrupt Enable
    Uint32 COMP1_LO_INT_EN:1;      // 18     Comparator 1 Lower Interrupt Enable
    Uint32 COMP0_UP_INT_EN:1;      // 17     Comparator 0 Upper Interrupt Enable
    Uint32 COMP0_LO_INT_EN:1;      // 16     Comparator 0 Lower Interrupt Enable
    Uint32 rsvd1:2;                // 15:14  Reserved
    Uint32 COMP5_DATA_SEL:1;       // 13     Comparator 5 Data Select
    Uint32 COMP4_DATA_SEL:1;       // 12     Comparator 4 Data Select
    Uint32 COMP3_DATA_SEL:1;       // 11     Comparator 3 Data Select
    Uint32 COMP2_DATA_SEL:1;       // 10     Comparator 2 Data Select
    Uint32 COMP1_DATA_SEL:1;       // 9      Comparator 1 Data Select
    Uint32 COMP0_DATA_SEL:1;       // 8      Comparator 0 Data Select
    Uint32 rsvd0:2;                // 7:6    reserved
    Uint32 COMP5_EN:1;             // 5      Digital comparator 5 enable
    Uint32 COMP4_EN:1;             // 4      Digital comparator 4 enable
    Uint32 COMP3_EN:1;             // 3      Digital comparator 3 enable
    Uint32 COMP2_EN:1;             // 2      Digital comparator 2 enable
    Uint32 COMP1_EN:1;             // 1      Digital comparator 1 enable
    Uint32 COMP0_EN:1;             // 0      Digital comparator 0 enable
  };
  union ADCCOMPEN_REG {
    Uint32                    all;
    struct ADCCOMPEN_BITS    bit;
  };
  
  //-----------------------------------------------------------------------------
  // ADC Digital Comparator Results Register bit definitions
  //-----------------------------------------------------------------------------
  struct ADCCOMPRESULT_BITS {       // bits   description
    Uint32 rsvd1:4;                 // 31:28  Reserved
    Uint32 DCOMP5_UP_RAW:1;         // 27     Comparator 5 Upper Limit Raw Result
    Uint32 DCOMP5_LO_RAW:1;         // 26     Comparator 5 Lower Limit Raw Result
    Uint32 DCOMP4_UP_RAW:1;         // 25     Comparator 4 Upper Limit Raw Result
    Uint32 DCOMP4_LO_RAW:1;         // 24     Comparator 4 Lower Limit Raw Result
    Uint32 DCOMP3_UP_RAW:1;         // 23     Comparator 3 Upper Limit Raw Result
    Uint32 DCOMP3_LO_RAW:1;         // 22     Comparator 3 Lower Limit Raw Result
    Uint32 DCOMP2_UP_RAW:1;         // 21     Comparator 2 Upper Limit Raw Result
    Uint32 DCOMP2_LO_RAW:1;         // 20     Comparator 2 Lower Limit Raw Result
    Uint32 DCOMP1_UP_RAW:1;         // 19     Comparator 1 Upper Limit Raw Result
    Uint32 DCOMP1_LO_RAW:1;         // 18     Comparator 1 Lower Limit Raw Result
    Uint32 DCOMP0_UP_RAW:1;         // 17     Comparator 0 Upper Limit Raw Result
    Uint32 DCOMP0_LO_RAW:1;         // 16     Comparator 0 Lower Limit Raw Result
    Uint32 rsvd0:4;                 // 15:12  Reserved
    Uint32 DCOMP5_UP_INT:1;         // 11     Comparator 5 Upper Limit Latch Result
    Uint32 DCOMP5_LO_INT:1;         // 10     Comparator 5 Lower Limit Latch Result
    Uint32 DCOMP4_UP_INT:1;         // 9      Comparator 5 Upper Limit Latch Result
    Uint32 DCOMP4_LO_INT:1;         // 8      Comparator 5 Lower Limit Latch Result
    Uint32 DCOMP3_UP_INT:1;         // 7      Comparator 5 Upper Limit Latch Result
    Uint32 DCOMP3_LO_INT:1;         // 6      Comparator 5 Lower Limit Latch Result
    Uint32 DCOMP2_UP_INT:1;         // 5      Comparator 5 Upper Limit Latch Result
    Uint32 DCOMP2_LO_INT:1;         // 4      Comparator 5 Lower Limit Latch Result
    Uint32 DCOMP1_UP_INT:1;         // 3      Comparator 5 Upper Limit Latch Result
    Uint32 DCOMP1_LO_INT:1;         // 2      Comparator 5 Lower Limit Latch Result
    Uint32 DCOMP0_UP_INT:1;         // 1      Comparator 5 Upper Limit Latch Result
    Uint32 DCOMP0_LO_INT:1;         // 0      Comparator 5 Lower Limit Latch Result
  };
  union ADCCOMPRESULT_REG {
    Uint32                        all;
    struct ADCCOMPRESULT_BITS     bit;
  };
  
  //-----------------------------------------------------------------------------
  // ADC Averaging Control Register Bit Definitions
  //-----------------------------------------------------------------------------
  struct ADCAVGCTRL_BITS {          // bits   description
    Uint32 rsvd5:9;                 // 31:23  Reserved
    Uint32 AVG5_CONFIG:2;           // 22:21  Averaging Module 5 Configuration
    Uint32 AVG5_EN:1;               // 20     Averaging Module 5 Enable
    Uint32 rsvd4:1;                 // 19     Reserved
    Uint32 AVG4_CONFIG:2;           // 18:17  Averaging Module 4 Configuration
    Uint32 AVG4_EN:1;               // 16     Averaging Module 4 Enable
    Uint32 rsvd3:1;                 // 15     Reserved
    Uint32 AVG3_CONFIG:2;           // 14:13  Averaging Module 3 Configuration
    Uint32 AVG3_EN:1;               // 12     Averaging Module 3 Enable
    Uint32 rsvd2:1;                 // 11     Reserved
    Uint32 AVG2_CONFIG:2;           // 10:9   Averaging Module 2 Configuration
    Uint32 AVG2_EN:1;               // 8      Averaging Module 2 Enable
    Uint32 rsvd1:1;                 // 7      Reserved
    Uint32 AVG1_CONFIG:2;           // 6:5    Averaging Module 1 Configuration
    Uint32 AVG1_EN:1;               // 4      Averaging Module 1 Enable
    Uint32 rsvd0:1;                 // 3      Reserved
    Uint32 AVG0_CONFIG:2;           // 2:1    Averaging Module 0 Configuration
    Uint32 AVG0_EN:1;               // 0      Averaging Module 0 Enable
  };
  union ADCAVGCTRL_REG {
    Uint32                        all;
    struct ADCAVGCTRL_BITS        bit;
  };

  //===========================================================================
  // ADC Module Register File
  //
  struct ADC_REGS {
    union  ADCCTRL_REG        ADCCTRL;         // ADC Control Register
    union  ADCSTAT_REG        ADCSTAT;         // ADC Status Register
    union  ADCTSTCTRL_REG     ADCTSTCTRL;      // ADC Test Control Register
    union  ADCSEQSEL0_REG     ADCSEQSEL0;      // ADC Sequencer Select Register 0
    union  ADCSEQSEL1_REG     ADCSEQSEL1;      // ADC Sequencer Select Register 1
    union  ADCSEQSEL2_REG     ADCSEQSEL2;      // ADC Sequencer Select Register 2
    union  ADCSEQSEL3_REG     ADCSEQSEL3;      // ADC Sequencer Select Register 3
    union  ADCRESULT_REG      ADCRESULT[16];   // ADC Conversion Result 0:15
    union  ADCAVGRESULT_REG   ADCAVGRESULT[6]; // ADC Averaged Conversion Result 0:5 
    union  ADCCOMPLIM_REG     ADCCOMPLIM[6];   // ADC Digital Compare Limits Register 0:5
    union  ADCCOMPEN_REG      ADCCOMPEN;       // ADC Digital Compare Enable Register
    union  ADCCOMPRESULT_REG  ADCCOMPRESULT;   // ADC Digital Compare Result Register
    union  ADCAVGCTRL_REG     ADCAVGCTRL;      // ADC Averaging Control Register
  };
  
  //-----------------------------------------------------------------------------
  // ADC Module External References & Function Declarations:
  //-----------------------------------------------------------------------------
  extern volatile struct ADC_REGS AdcRegs;

#ifdef __cplusplus
}       // end of extern "C"
#endif

#endif  // end of CYCLONE_ADC_H definition

//===========================================================================
// End of file
//===========================================================================
