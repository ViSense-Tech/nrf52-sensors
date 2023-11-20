//###############################################################################
//
// FILE:   cyclone_dpwm.h
//
// TITLE:  Cyclone Digital PWM Module Register Definitions.
//
// NOTES:
//  1) Bitfields have been defined for big-endian only.
//###############################################################################
//
//  Ver  | dd mmm yyyy | Who  | Description of changes
// ======|=============|======|==============================================
//  1.00 | 07 Oct 2009 | CMF  | Started with Spartan_Dpwm.h.
//       |             |      | Updated for 1.0 Memory map document.
//       |             |      |
//
//  Texas Instruments, Inc
//  Copyright Texas Instruments 2009. All rights reserved.
//###############################################################################

#ifndef CYCLONE_DPWM_H
#define CYCLONE_DPWM_H

#ifdef __cplusplus
extern "C" {
#endif

  //=============================================================================
  // DPWM Individual Register Bit Definitions
  //=============================================================================
  
  //-----------------------------------------------------------------------------
  // DPWM Control Register 0 bit definitions
  //-----------------------------------------------------------------------------
  struct DPWMCTRL0_BITS {                // bits   Description
    Uint32 PWM_B_INTRA_MUX:4;            // 31:28  PWM B Intramux Configuration
    Uint32 PWM_A_INTRA_MUX:4;            // 27:24  PWM A Intramux Configuration
    Uint32 CBC_PWM_C_EN:1;               // 23     Cycle-by-Cycle PWM C Enable
    Uint32 rsvd0:2;                      // 22:21  Reserved
    Uint32 CBC_PWM_AB_EN:1;              // 20     Cycle-by-Cycle Current Limit Mode
    Uint32 CBC_ADV_CNT_EN:1;             // 19     Cycle-by-Cycle Current Limit Enable
    Uint32 MIN_DUTY_MODE:2;              // 18:17  Minimum Duty Cycle Clamp Select
    Uint32 rsvd1:1;                      // 16     Reserved
    Uint32 MSYNC_SLAVE_EN:1;             // 15     Internal sync enable
    Uint32 D_ENABLE:1;                   // 14     1-D Enable
    Uint32 rsvd2:1;                      // 13     Reserved
    Uint32 RESON_MODE_FIXED_DUTY_EN:1;   // 12     Controls Pulse Width in Resonance Mode 
    Uint32 PWM_B_FLT_POL:1;              // 11     PWM B Fault Polarity
    Uint32 PWM_A_FLT_POL:1;              // 10     PWM A Fault Polarity        
    Uint32 BLANK_B_EN:1;                 // 9      PWM B Comparator Blanking Enable
    Uint32 BLANK_A_EN:1;                 // 8      PWM A Comparator Blanking Enable
    Uint32 PWM_MODE:4;                   // 7:4    Configures DPWM mode of operation
    Uint32 PWM_B_INV:1;                  // 3      PWM B polarity inversion
    Uint32 PWM_A_INV:1;                  // 2      PWM A polarity inversion
    Uint32 CLA_EN:1;                     // 1      PWM input selection - enable CLA input
    Uint32 PWM_EN:1;                     // 0      PWM enable
  };
  union DPWMCTRL0_REG {
    Uint32                 all;
    struct DPWMCTRL0_BITS  bit;
  };

  //-----------------------------------------------------------------------------
  // DPWM Control Register 1 bit definitions
  //-----------------------------------------------------------------------------
  struct DPWMCTRL1_BITS {            // bits   description
    Uint32 PRESET_EN:1;              // 31     Preset Counter Enable
    Uint32 SYNC_FET_EN:1;            // 30     SyncFET Mode Enable
    Uint32 BURST_EN:1;               // 29     Burst (Light Load) Mode enable
    Uint32 CLA_DUTY_ADJ_EN:1;        // 28     Current/Flux Balancing Adjustment Enable
    Uint32 SYNC_OUT_DIV_SEL:4;       // 27:24  Sync out divider select
    Uint32 CLA_SCALE:3;              // 23:21  CLA scaling select
    Uint32 EXT_SYNC_EN:1;	         // 20     Slave DPWM to external sync
    Uint32 CBC_BSIDE_ACTIVE_EN:1;    // 19     Cycle-by-Cycle B Side Active Enable
    Uint32 AUTO_MODE_SEL:1;          // 18     Auto Mode Switching Select
    Uint32 rsvd0:1;                  // 17     Reserved
    Uint32 EVENT_UP_SEL:1;           // 16     PWM Update mode
    Uint32 CHECK_OVERRIDE:1;         // 15     Override PWM checks for invalid config
    Uint32 GLOBAL_PERIOD_EN:1;       // 14     PWM Global Period Enable
    Uint32 PWM_B_OE:1;               // 13     PWM B output enable
    Uint32 PWM_A_OE:1;               // 12     PWM A output enable
    Uint32 GPIO_B_VAL:1;             // 11     PWM B output in GPIO mode
    Uint32 GPIO_B_EN:1;              // 10     PWM B output enable in GPIO mode
    Uint32 GPIO_A_VAL:1;             // 9      PWM A output in GPIO mode
    Uint32 GPIO_A_EN:1;              // 8      PWM A output enable in GPIO mode
    Uint32 PWM_HR_MULTI_OUT_EN:1;    // 7      PWM High Res Multi-Mode Output Enable
    Uint32 SFRAME_EN:1;              // 6      PWM single frame mode select
    Uint32 PWM_B_PROT_DIS:1;         // 5      PWM B async protection disable
    Uint32 PWM_A_PROT_DIS:1;         // 4      PWM A async protection disable
    Uint32 HIRES_SCALE:2;            // 3:2    Hi-resolution scale select
    Uint32 rsvd1:1;                  // 1      Reserved
    Uint32 HIRES_DIS:1;              // 0      Hi-resolution disable
  };
  union DPWMCTRL1_REG {
    Uint32                 all;
    struct DPWMCTRL1_BITS  bit;
  };
  
  //-----------------------------------------------------------------------------
  // DPWM Control Register 2 Bit Definitions
  //-----------------------------------------------------------------------------
  struct DPWMCTRL2_BITS {              // bits   description
    Uint32 rsvd0:15;                   // 31:17  Reserved
    Uint32 BLANK_PCM_EN:1;             // 16     Blanking Mask PCM Enable 
    Uint32 SYNC_IN_DIV_RATIO:4;        // 15:12  External Sync In Divide Ratio
    Uint32 rsvd1:2;                    // 11:10     Reserved
    Uint32 FILTER_DUTY_SEL:2;          // 9:8   Selects DPWM Duty for Mode Switching
    Uint32 IDE_DUTY_B_EN:1;            // 7      IDE Duty Cycle Side B Enable
    Uint32 IDE_DETECT_EN:1;            // 6      IDE Detect Enable
    Uint32 SAMPLE_TRIG1_OVERSAMPLE:2; // 5:4    Configures Oversampling function
    Uint32 SAMPLE_TRIG1_MODE:2;       // 3:2    Sample Trigger Configuration
    Uint32 SAMPLE_TRIG_2_EN:1;         // 1      Sample Trigger 2 Enable
    Uint32 SAMPLE_TRIG_1_EN:1;         // 0      Sample Trigger 1 Enable
  };
  union DPWMCTRL2_REG {
    Uint32                 all;
    struct DPWMCTRL2_BITS  bit;
  };

  //-----------------------------------------------------------------------------
  // DPWM Period Register bit definitions
  //-----------------------------------------------------------------------------
  struct DPWMPRD_BITS {              // bits   description
    Uint32 rsvd1:14;                 // 31:18  reserved
    Uint32 PRD:14;                   // 17:4   PWM Period - clock periods + 1
    Uint32 rsvd0:4;                  // 3:0    Reserved
  };
  union DPWMPRD_REG {
    Uint32                 all;
    struct DPWMPRD_BITS    bit;
  };
  
  //-----------------------------------------------------------------------------
  // DPWM Event 1 Register bit definitions
  //-----------------------------------------------------------------------------
  struct DPWMEV1_BITS {              // bits   description
    Uint32 rsvd1:14;                 // 31:18  reserved
    Uint32 EVENT1:14;                // 17:4   Event 1 configuration
    Uint32 rsvd0:4;                  // 3:0    Reserved
  };
  union DPWMEV1_REG {
    Uint32                 all;
    struct DPWMEV1_BITS    bit;
  };

  //-----------------------------------------------------------------------------
  // DPWM Event 2 Register bit definitions
  //-----------------------------------------------------------------------------
  struct DPWMEV2_BITS {              // bits   description
    Uint32 rsvd0:14;                 // 31:18  reserved
    Uint32 EVENT2:18;                // 17:0   Event 2 configuration
  };
  union DPWMEV2_REG {
    Uint32                 all;
    struct DPWMEV2_BITS    bit;
  };
  
  //-----------------------------------------------------------------------------
  // DPWM Event 3 Register bit definitions
  //-----------------------------------------------------------------------------
  struct DPWMEV3_BITS {              // bits   description
    Uint32 rsvd0:14;                 // 31:18  reserved
    Uint32 EVENT3:18;                // 17:0   Event 3 configuration
  };
  union DPWMEV3_REG {
    Uint32                 all;
    struct DPWMEV3_BITS    bit;
  };
  
  //-----------------------------------------------------------------------------
  // DPWM Event 4 Register bit definitions
  //-----------------------------------------------------------------------------
  struct DPWMEV4_BITS {              // bits   description
    Uint32 rsvd0:14;                 // 31:18  reserved
    Uint32 EVENT4:18;                // 17:0   Event 4 configuration
  };
  union DPWMEV4_REG {
    Uint32                 all;
    struct DPWMEV4_BITS    bit;
  };

  //-----------------------------------------------------------------------------
  // DPWM Sample Trigger 1 Register bit definitions
  //-----------------------------------------------------------------------------
  struct DPWMSAMPTRIG1_BITS {        // bits   description
    Uint32 rsvd1:14;                 // 31:12  reserved
    Uint32 SAMPLE_TRIGGER:12;        // 17:6   Sample trigger configuration
    Uint32 rsvd0:6;                  // 5:0    reserved
  };
  union DPWMSAMPTRIG1_REG {
    Uint32                       all;
    struct DPWMSAMPTRIG1_BITS    bit;
  };

  //-----------------------------------------------------------------------------
  // DPWM Sample Trigger 2 Register bit definitions
  //-----------------------------------------------------------------------------
  struct DPWMSAMPTRIG2_BITS {        // bits   description
    Uint32 rsvd1:14;                 // 31:12  reserved
    Uint32 SAMPLE_TRIGGER:12;        // 17:6   Sample trigger configuration
    Uint32 rsvd0:6;                  // 5:0    reserved
  };
  union DPWMSAMPTRIG2_REG {
    Uint32                       all;
    struct DPWMSAMPTRIG2_BITS    bit;
  };  

  //-----------------------------------------------------------------------------
  // DPWM Phase Trigger Register bit definitions
  //-----------------------------------------------------------------------------
  struct DPWMPHASETRIG_BITS {        // bits   description
    Uint32 rsvd1:14;                 // 31:14  reserved
    Uint32 PHASE_TRIGGER:14;         // 17:4   Phase trigger configuration
    Uint32 rsvd0:4;                  // 3:0    Reserved
  };
  union DPWMPHASETRIG_REG {
    Uint32                       all;
    struct DPWMPHASETRIG_BITS    bit;
  };

  //-----------------------------------------------------------------------------
  // DPWM Cycle Adjust A Register bit definitions
  //-----------------------------------------------------------------------------
  struct DPWMCYCADJA_BITS {          // bits   description
    Uint32 rsvd0:16;                 // 31:16  Reserved
    int32 CYCLE_ADJUST_A:16;        // 15:0   Cycle Adjust A
  };
  union DPWMCYCADJA_REG {
    int32                    all;
    struct DPWMCYCADJA_BITS   bit;
  };

  //-----------------------------------------------------------------------------
  // DPWM Cycle Adjust B Register bit definitions
  //-----------------------------------------------------------------------------
  struct DPWMCYCADJB_BITS {          // bits   description
    Uint32 rsvd0:16;                 // 31:16  Reserved
    int32 CYCLE_ADJUST_B:16;        // 15:0   Cycle Adjust B
  };
  union DPWMCYCADJB_REG {
    int32                    all;
    struct DPWMCYCADJB_BITS   bit;
  };

  //-----------------------------------------------------------------------------
  // DPWM Resonant Duty Register bit definitions
  //-----------------------------------------------------------------------------
  struct DPWMRESDUTY_BITS {          // bits   description
    Uint32 rsvd0:18;                // 31:14  Reserved
    Uint32 RESONANT_DUTY:14;        // 13:0   Resonant Duty Adjust 
  };
  union DPWMRESDUTY_REG {
    Uint32                   all;
    struct DPWMRESDUTY_BITS   bit;
  };  

  //-----------------------------------------------------------------------------
  // DPWM Fault Control Register bit definitions
  //-----------------------------------------------------------------------------
  struct DPWMFLTCTRL_BITS {          // bits   description
    Uint32 rsvd0:1;                  // 31     Reserved
    Uint32 ALL_FAULT_EN:1;           // 30     Fault Module Enable
    Uint32 CBC_FAULT_EN:1;           // 29     CBC Fault Module Enable
    Uint32 CBC_FAULT_MODE:1;         // 28     CBC Fault Mode Select 
    Uint32 CBC_MAX_COUNT:7;          // 27:21  Cycle-by-Cycle Max Count
    Uint32 AB_MAX_COUNT:7;           // 20:14  Fault AB Cycle Max Count
    Uint32 B_MAX_COUNT:7;            // 13:7   Fault B Cycle Max Count
    Uint32 A_MAX_COUNT:7;            // 6:0    Fault A Cycle Max Count
  };
  union DPWMFLTCTRL_REG {
    Uint32                    all;
    struct DPWMFLTCTRL_BITS   bit;
  };

  //-----------------------------------------------------------------------------
  // DPWM Overflow Register
  //-----------------------------------------------------------------------------
  struct DPWMOVERFLOW_BITS {         // bits   description
    Uint32 rsvd0:24;                 // 31:8   Reserved
    Uint32 PWM_B_CHECK:1;            // 7      Value of PWM B Internal Check
    Uint32 PWM_A_CHECK:1;            // 6      Value of PWM A Internal Check
    Uint32 GPIO_B_IN:1;              // 5      Input value of PWM B 
    Uint32 GPIO_A_IN:1;              // 4      Input value of PWM A
    Uint32 OVERFLOW:4;               // 3:0    DPWM Overflow status
  };
  union DPWMOVERFLOW_REG {
    Uint32                   all;
    struct DPWMOVERFLOW_BITS bit;
  };

  //-----------------------------------------------------------------------------
  // DPWM Interrupt Register
  //-----------------------------------------------------------------------------
  struct DPWMINT_BITS {              // bits   description
    Uint32 rsvd0:9;                  // 31:23  Reserved
    Uint32 MODE_SWITCH:1;            // 22     Mode Switching Flag
    Uint32 FLT_A:1;                  // 21     Fault A Flag
    Uint32 FLT_B:1;                  // 20     Fault B Flag
    Uint32 FLT_AB:1;                 // 19     Fault AB Flag
    Uint32 FLT_CBC:1;                // 18     Fault CBC Flag 
    Uint32 PRD:1;                    // 17     PWM Period Interrupt Flag
    Uint32 INT:1;                    // 16     Interrupt Status
    Uint32 rsvd1:4;                  // 15:12  Reserved
    Uint32 MODE_SWITCH_FLAG_CLR:1;   // 11     Mode Switching Flag Clear
    Uint32 MODE_SWITCH_FLAG_EN:1;    // 10     Mode Switching Flag Enable
    Uint32 MODE_SWITCH_INT_EN:1;     // 9      Mode Switching Interrupt Enable
    Uint32 FLT_A_INT_EN:1;           // 8      Fault A Interrupt Enable
    Uint32 FLT_B_INT_EN:1;           // 7      Fault B Interrupt Enable
    Uint32 FLT_AB_INT_EN:1;          // 6      Fault AB Interrupt Enable
    Uint32 FLT_CBC_INT_EN:1;         // 5      Fault CBC Interrupt Enable
    Uint32 PRD_INT_EN:1;             // 4      End-of-Period Interrupt Enable
    Uint32 PRD_INT_SCALE:4;          // 3:0    End-of-Period Interrupt Scale
  };
  union DPWMINT_REG {
    Uint32                   all;
    struct DPWMINT_BITS      bit;
  };

  //-----------------------------------------------------------------------------
  // DPWM Counter Preset Register
  //-----------------------------------------------------------------------------
  struct DPWMCNTPRE_BITS {          // bits     Description
    Uint32 rsvd1:14;                // 31:14    Reserved
    Uint32 PRESET:14;               // 17:4     Preset DPWM Counter value
    Uint32 rsvd0:4;                 // 3:0      Reserved
  };
  union DPWMCNTPRE_REG {
    Uint32                  all;
    struct DPWMCNTPRE_BITS  bit;
  };

  //-----------------------------------------------------------------------------
  // DPWM Blanking A Begin Register
  //-----------------------------------------------------------------------------
  struct DPWMBLKABEG_BITS {          // bits     Description
    Uint32 rsvd1:14;                 // 31:18    Reserved
    Uint32 BLANK_A_BEGIN:14;         // 17:4     Start of PWM A Comparator Blanking
    Uint32 rsvd0:4;                  // 3:0      Reserved
  };
  union DPWMBLKABEG_REG {
    Uint32                  all;
    struct DPWMBLKABEG_BITS bit;
  };

  //-----------------------------------------------------------------------------
  // DPWM Blanking A End Register
  //-----------------------------------------------------------------------------
  struct DPWMBLKAEND_BITS {          // bits     Description
    Uint32 rsvd1:14;                 // 31:18    Reserved
    Uint32 BLANK_A_END:14;           // 17:4     End of PWM A Comparator Blanking
    Uint32 rsvd0:4;                  // 3:0      Reserved
  };
  union DPWMBLKAEND_REG {
    Uint32                  all;
    struct DPWMBLKAEND_BITS bit;
  };

  //-----------------------------------------------------------------------------
  // DPWM Blanking B Begin Register
  //-----------------------------------------------------------------------------
  struct DPWMBLKBBEG_BITS {          // bits     Description
    Uint32 rsvd1:14;                 // 31:18    Reserved
    Uint32 BLANK_B_BEGIN:14;         // 17:4     Start of PWM B Comparator Blanking
    Uint32 rsvd0:4;                  // 3:0      Reserved
  };
  union DPWMBLKBBEG_REG {
    Uint32                  all;
    struct DPWMBLKBBEG_BITS bit;
  };

  //-----------------------------------------------------------------------------
  // DPWM Blanking B End Register
  //-----------------------------------------------------------------------------
  struct DPWMBLKBEND_BITS {          // bits     Description
    Uint32 rsvd1:14;                 // 31:18    Reserved
    Uint32 BLANK_B_END:14;           // 17:4     End of PWM B Comparator Blanking
    Uint32 rsvd0:4;                  // 3:0      Reserved
  };
  union DPWMBLKBEND_REG {
    Uint32                  all;
    struct DPWMBLKBEND_BITS bit;
  };

  //-----------------------------------------------------------------------------
  // DPWM Minimum Duty Cycle High Register
  //-----------------------------------------------------------------------------
  struct DPWMMINDUTYHI_BITS {       // bits     Description
    Uint32 rsvd1:14;                // 31:18    Reserved
    Uint32 MIN_DUTY_HIGH:14;        // 17:4     Minimum Duty High Threshold
    Uint32 rsvd0:4;                 // 3:0      Reserved
  };
  union DPWMMINDUTYHI_REG {
    Uint32                    all;
    struct DPWMMINDUTYHI_BITS bit;
  };

  //-----------------------------------------------------------------------------
  // DPWM Minimum Duty Cycle Low Register
  //-----------------------------------------------------------------------------
  struct DPWMMINDUTYLO_BITS {       // bits     Description
    Uint32 rsvd1:14;                // 31:18    Reserved
    Uint32 MIN_DUTY_LOW:14;         // 17:4     Minimum Duty Low Threshold
    Uint32 rsvd0:4;                 // 3:0      Reserved
  };
  union DPWMMINDUTYLO_REG {
    Uint32                    all;
    struct DPWMMINDUTYLO_BITS bit;
  };

  //-----------------------------------------------------------------------------
  // DPWM Adaptive Sample Register
  //-----------------------------------------------------------------------------
  struct DPWMADAPTIVE_BITS {        // bits    Description
    Uint32 rsvd0:20;                // 31:12   Reserved
    int32 ADAPT_SAMP:12;           // 11:0    Adaptive Sample Adjust
  };
  union DPWMADAPTIVE_REG {
    Uint32                   all;
    struct DPWMADAPTIVE_BITS bit;
  }; 
  
  //-----------------------------------------------------------------------------
  // DPWM Fault Status Register
  //-----------------------------------------------------------------------------
  struct DPWMFLTSTAT_BITS {         // bits    Description
    Uint32 rsvd0:26;                // 31:6    Reserved
    Uint32 BURST:1;                 // 5       Burst Mode
    Uint32 IDE_DETECT:1;            // 4       IDE Detect Indication
    Uint32 FLT_A:1;                 // 3       Fault A Detection
    Uint32 FLT_B:1;                 // 2       Fault B Detection
    Uint32 FLT_AB:1;                // 1       Fault AB Detection
    Uint32 FLT_CBC:1;               // 0       Current Limit Detection
  };
  union DPWMFLTSTAT_REG {
    Uint32                   all;
    struct DPWMFLTSTAT_BITS  bit;
  };   

  //-----------------------------------------------------------------------------
  // DPWM Auto Switch High Upper Thresh Register
  //-----------------------------------------------------------------------------
  struct DPWMAUTOSWHIUPTHRESH_BITS {  // bits    Description
    Uint32 rsvd1:14;                  // 31:18   Reserved
    Uint32 AUTO_SWITCH_HIGH_UPPER:14; // 17:4    Auto Switch High Threshold
    Uint32 rsvd0:4;                   // 3:0     Reserved
  };
  union DPWMAUTOSWHIUPTHRESH_REG {
    Uint32                           all;
    struct DPWMAUTOSWHIUPTHRESH_BITS bit;
  };
  
  //-----------------------------------------------------------------------------
  // DPWM Auto Switch High Lower Thresh Register
  //-----------------------------------------------------------------------------
  struct DPWMAUTOSWHILOWTHRESH_BITS { // bits    Description
    Uint32 rsvd1:14;                  // 31:18   Reserved
    Uint32 AUTO_SWITCH_HIGH_LOWER:14; // 17:4    Auto Switch High Threshold
    Uint32 rsvd0:4;                   // 3:0     Reserved
  };
  union DPWMAUTOSWHILOWTHRESH_REG {
    Uint32                            all;
    struct DPWMAUTOSWHILOWTHRESH_BITS bit;
  };  

  //-----------------------------------------------------------------------------
  // DPWM Auto Switch Low Upper Thresh Register
  //-----------------------------------------------------------------------------
  struct DPWMAUTOSWLOUPTHRESH_BITS{   // bits    Description
    Uint32 rsvd1:14;                  // 31:18   Reserved
    Uint32 AUTO_SWITCH_LOW_UPPER:14;  // 17:4    Auto Switch Low Threshold
    Uint32 rsvd0:4;                   // 3:0     Reserved
  };
  union DPWMAUTOSWLOUPTHRESH_REG {
    Uint32                           all;
    struct DPWMAUTOSWLOUPTHRESH_BITS bit;
  };  

  //-----------------------------------------------------------------------------
  // DPWM Auto Switch Low Lower Thresh Register
  //-----------------------------------------------------------------------------
  struct DPWMAUTOSWLOLOWTHRESH_BITS{  // bits    Description
    Uint32 rsvd1:14;                  // 31:18   Reserved
    Uint32 AUTO_SWITCH_LOW_LOWER:14;  // 17:4    Auto Switch Low Threshold
    Uint32 rsvd0:4;                   // 3:0     Reserved
  };
  union DPWMAUTOSWLOLOWTHRESH_REG {
    Uint32                            all;
    struct DPWMAUTOSWLOLOWTHRESH_BITS bit;
  };  

  //-----------------------------------------------------------------------------
  // DPWM Auto Config Max Register
  //-----------------------------------------------------------------------------
  struct DPWMAUTOMAX_BITS {              // bits    Description
    Uint32 PWM_B_INTRA_MUX:4;            // 31:28   PWM B Intramux Configuration
    Uint32 PWM_A_INTRA_MUX:4;            // 27:24   PWM A Intramux Configuration
    Uint32 CBC_PWM_C_EN:1;               // 23      Cycle-by-Cycle PWM C Enable
    Uint32 rsvd0:2;                      // 22:21   Reserved
    Uint32 CBC_PWM_AB_EN:1;              // 20      Cycle-by-Cycle Current Limit Mode
    Uint32 CBC_ADV_CNT_EN:1;             // 19      Cycle-by-Cycle Current Limit Enable
    Uint32 rsvd1:6;                      // 18:13   Reserved
    Uint32 RESON_MODE_FIXED_DUTY_EN:1;   // 12      Controls Pulse Width in Resonance Mode
    Uint32 rsvd2:4;                      // 11:8     Reserved
    Uint32 PWM_MODE:4;                   // 7:4     Configures DPWM mode of operation
    Uint32 rsvd3:2;                      // 3:2     Reserved
    Uint32 CLA_EN:1;                     // 1       PWM input selection - enable CLA input
    Uint32 rsvd4:1;                      // 0       Reserved
  };
  union DPWMAUTOMAX_REG {
    Uint32                  all;
    struct DPWMAUTOMAX_BITS bit;
  };

  //-----------------------------------------------------------------------------
  // DPWM Auto Config Mid Register
  //-----------------------------------------------------------------------------
  struct DPWMAUTOMID_BITS {              // bits    Description
    Uint32 PWM_B_INTRA_MUX:4;            // 31:28   PWM B Intramux Configuration
    Uint32 PWM_A_INTRA_MUX:4;            // 27:24   PWM A Intramux Configuration
    Uint32 CBC_PWM_C_EN:1;               // 23      Cycle-by-Cycle PWM C Enable
    Uint32 rsvd0:2;                      // 22:21   Reserved
    Uint32 CBC_PWM_AB_EN:1;              // 20      Cycle-by-Cycle Current Limit Mode
    Uint32 CBC_ADV_CNT_EN:1;             // 19      Cycle-by-Cycle Current Limit Enable
    Uint32 rsvd1:6;                      // 18:13   Reserved
    Uint32 RESON_MODE_FIXED_DUTY_EN:1;   // 12      Controls Pulse Width in Resonance Mode
    Uint32 rsvd2:4;                      // 11:8     Reserved
    Uint32 PWM_MODE:4;                   // 7:4     Configures DPWM mode of operation
    Uint32 rsvd3:2;                      // 3:2     Reserved
    Uint32 CLA_EN:1;                     // 1       PWM input selection - enable CLA input
    Uint32 rsvd4:1;                      // 0       Reserved
  };
  union DPWMAUTOMID_REG {
    Uint32                  all;
    struct DPWMAUTOMID_BITS bit;
  };  

  //-----------------------------------------------------------------------------
  // DPWM Edge PWM Generation Control Register
  //-----------------------------------------------------------------------------
  struct DPWMEDGEGEN_BITS {              // bits    Description
    Uint32 rsvd0:15;                     // 31:17   Reserved
    Uint32 EDGE_EN:1;                    // 16      Enables Edge Generate Module
    Uint32 rsvd1:1;                      // 15      Reserved
    Uint32 A_ON_EDGE:3;                  // 14:12   A On Edge Trigger Select
    Uint32 rsvd2:1;                      // 11      Reserved
    Uint32 A_OFF_EDGE:3;                 // 10:8    A Off Edge Trigger Select
    Uint32 rsvd3:1;                      // 7       Reserved
    Uint32 B_ON_EDGE:3;                  // 6:4     B On Edge Trigger Select
    Uint32 rsvd4:1;                      // 3       Reserved
    Uint32 B_OFF_EDGE:3;                 // 2:0     B Off Edge Trigger Select
  };
  union DPWMEDGEGEN_REG {
    Uint32                  all;
    struct DPWMEDGEGEN_BITS bit;
  };

  //-----------------------------------------------------------------------------
  // DPWM Filter Duty Read Register
  //-----------------------------------------------------------------------------
  struct DPWMFILTERDUTYREAD_BITS {       // bits    Description
    Uint32 rsvd0:14;                     // 31:18   Reserved
    Uint32 FILTER_DUTY:18;               // 17:0    Filter Duty
  };
  union DPWMFILTERDUTYREAD_REG {
    Uint32                         all;
    struct DPWMFILTERDUTYREAD_BITS bit;
  };  

  //-----------------------------------------------------------------------------
  // DPWM CBC Location Register
  //-----------------------------------------------------------------------------
  struct DPWMCBCLOCATION_BITS {         // bits     Description
    Uint32 rsvd0:18;                    // 31:14    Reserved
    Uint32 CBC_LOCATION:14;             // 13:0     CBC Location 
  };
  union DPWMCBCLOCATION_REG {
    Uint32                         all;
    struct DPWMCBCLOCATION_BITS    bit;
  };

  //-----------------------------------------------------------------------------
  // DPWM BIST Status Register
  //-----------------------------------------------------------------------------
  struct DPWMBISTSTAT_BITS {            // bits     Description
    Uint32 rsvd0:17;                    // 31:15    Reserved
    Uint32 BIST_CNT:15;                 // 14:0     BIST Count
  };
  union DPWMBISTSTAT_REG {
    Uint32                         all;
    struct DPWMBISTSTAT_BITS       bit;
  };

  //=============================================================================
  // DPWM Module Register File
  //=============================================================================
  struct DPWM_REGS {
    union DPWMCTRL0_REG               DPWMCTRL0;
    union DPWMCTRL1_REG               DPWMCTRL1;
    union DPWMCTRL2_REG               DPWMCTRL2;
    union DPWMPRD_REG	              DPWMPRD;
    union DPWMEV1_REG	              DPWMEV1;
    union DPWMEV2_REG	              DPWMEV2;
    union DPWMEV3_REG	              DPWMEV3;
    union DPWMEV4_REG	              DPWMEV4;
    union DPWMSAMPTRIG1_REG           DPWMSAMPTRIG1;
    union DPWMSAMPTRIG2_REG           DPWMSAMPTRIG2;
    union DPWMPHASETRIG_REG           DPWMPHASETRIG;
    union DPWMCYCADJA_REG             DPWMCYCADJA;
    union DPWMCYCADJB_REG             DPWMCYCADJB;
    union DPWMRESDUTY_REG             DPWMRESDUTY;
    union DPWMFLTCTRL_REG             DPWMFLTCTRL;
    union DPWMOVERFLOW_REG            DPWMOVERFLOW;
    union DPWMINT_REG                 DPWMINT;
    union DPWMCNTPRE_REG              DPWMCNTPRE;
    union DPWMBLKABEG_REG             DPWMBLKABEG;
    union DPWMBLKAEND_REG             DPWMBLKAEND;
    union DPWMBLKBBEG_REG             DPWMBLKBBEG;
    union DPWMBLKBEND_REG             DPWMBLKBEND;
    union DPWMMINDUTYHI_REG           DPWMMINDUTYHI;
    union DPWMMINDUTYLO_REG           DPWMMINDUTYLO;
    union DPWMADAPTIVE_REG            DPWMADAPTIVE;
    union DPWMFLTSTAT_REG             DPWMFLTSTAT;
    union DPWMAUTOSWHIUPTHRESH_REG    DPWMAUTOSWHIUPTHRESH;
    union DPWMAUTOSWHILOWTHRESH_REG   DPWMAUTOSWHILOWTHRESH;
    union DPWMAUTOSWLOUPTHRESH_REG    DPWMAUTOSWLOUPTHRESH;
    union DPWMAUTOSWLOLOWTHRESH_REG   DPWMAUTOSWLOLOWTHRESH;
    union DPWMAUTOMAX_REG             DPWMAUTOMAX;
    union DPWMAUTOMID_REG             DPWMAUTOMID;
    union DPWMEDGEGEN_REG             DPWMEDGEGEN;
    union DPWMFILTERDUTYREAD_REG      DPWMFILTERDUTYREAD;
    union DPWMCBCLOCATION_REG         DPWMCBCLOCATION;
    union DPWMBISTSTAT_REG            DPWMBISTSTAT;
  };

  //-----------------------------------------------------------------------------
  // DPWM Module External References & Function Declarations:
  //-----------------------------------------------------------------------------
  extern volatile struct DPWM_REGS Dpwm0Regs;
  extern volatile struct DPWM_REGS Dpwm1Regs;
  extern volatile struct DPWM_REGS Dpwm2Regs;
  extern volatile struct DPWM_REGS Dpwm3Regs;

//===========================================================================
#ifdef __cplusplus
}       // end of extern "C"
#endif

#endif  // end of CYCLONE_DPWM_H definition

//===========================================================================
// End of file
//===========================================================================
