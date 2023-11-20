//###############################################################################
//
// FILE:   cyclone_filter.h
//
// TITLE:  Cyclone Filter Register Definitions.
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

#ifndef CYCLONE_FILTER_H
#define CYCLONE_FILTER_H

#ifdef __cplusplus
extern "C" {
#endif

  //=============================================================================
  // Filter Individual Register Bit Definitions
  //=============================================================================

  //-----------------------------------------------------------------------------
  // Filter Status Register
  //-----------------------------------------------------------------------------
  struct FILTERSTATUS_BITS {        // bits   description
    Uint32 rsvd0:27;                // 31:5   Reserved
    Uint32 FILTER_BUSY:1;           // 4      Filter Busy Indication
    Uint32 YN_LOW_CLAMP:1;          // 3      Output Clamp Low Indication
    Uint32 YN_HIGH_CLAMP:1;         // 2      Output Clamp High Indication
    Uint32 KI_YN_LOW_CLAMP:1;       // 1      KI Feedback Clamp Low Indication
    Uint32 KI_YN_HIGH_CLAMP:1;      // 0      KI Feedback Clamp High Indication
  }; 
  union FILTERSTATUS_REG {
    struct FILTERSTATUS_BITS     bit;
    Uint32                       all; 
  };
  
  //-----------------------------------------------------------------------------
  // Filter Control Register
  //-----------------------------------------------------------------------------
  struct FILTERCTRL_BITS {          // bits   description
    Uint32 rsvd0:16;                // 31:16  Reserved
	Uint32 KI_ADDER_MODE:1;         // 15     KI Adder Mode Select
    Uint32 PERIOD_MULT_SEL:1;       // 14     Period Multiplier Select
    Uint32 OUTPUT_MULT_SEL:2;       // 13:12  Output Multiplicand Select
    int32 OUTPUT_SCALE:3;          // 11:9    Output Scaling
    Uint32 NL_MODE:1;               // 8      Selects Non-linear Mode
    Uint32 KD_STALL:1;              // 7      Stalls KD Branch
    Uint32 KI_STALL:1;              // 6      Stalls KI Branch
    Uint32 KP_OFF:1;                // 5      Turns off KP Branch
    Uint32 KD_OFF:1;                // 4      Turns off KD Branch
    Uint32 KI_OFF:1;                // 3      Turns off KI Branch
    Uint32 FORCE_START:1;           // 2      Software Filter Calculation
    Uint32 USE_CPU_SAMPLE:1;        // 1      Use CPU Sample
    Uint32 FILTER_EN:1;             // 0      Filter Enable
  };
  union FILTERCTRL_REG {
    struct FILTERCTRL_BITS     bit;
    Uint32                     all;
  };
  
  //-----------------------------------------------------------------------------
  // CPU XN Register 
  //-----------------------------------------------------------------------------
  struct CPUXN_BITS {               // bits   description
    Uint32 rsvd0:23;                // 31:9   Reserved
    int32 CPU_SAMPLE:9;            // 8:0    CPU Sample
  };
  union CPUXN_REG {
    struct CPUXN_BITS       bit;
    Uint32                  all;
  };

  //-----------------------------------------------------------------------------
  // Filter XN Read Register
  //-----------------------------------------------------------------------------
  struct FILTERXNREAD_BITS {           // bits   description
    Uint32 rsvd1:7;                 // 31:25  Reserved
    int32 XN_M1:9;                 // 24:16  XN_M1 Value
    Uint32 rsvd0:7;                 // 15:9   Reserved
    int32 XN:9;                    // 8:0    XN Value
  };
  union FILTERXNREAD_REG {
    struct FILTERXNREAD_BITS bit;
    Uint32                   all;
  };
  
  //-----------------------------------------------------------------------------
  // Filter KI_YN Read Register
  //-----------------------------------------------------------------------------
  struct FILTERKIYNREAD_BITS {         // bits   description
    Uint32 rsvd0:8;                 // 31:24  Reserved
    int32 KI_YN:24;                // 23:0   KI_YN Value
  };
  union FILTERKIYNREAD_REG {
    struct FILTERKIYNREAD_BITS bit;
    Uint32                     all;   
  };    
    
  //-----------------------------------------------------------------------------
  // Filter KD_YN Read Register
  //-----------------------------------------------------------------------------
  struct FILTERKDYNREAD_BITS {         // bits   description
    Uint32 rsvd0:8;                    // 31:24  Reserved
    int32 KD_YN:24;                   // 23:0   KD_YN Value
  };
  union FILTERKDYNREAD_REG {
    struct FILTERKDYNREAD_BITS bit;
    Uint32                     all; 
  };    

  //-----------------------------------------------------------------------------
  // Filter YN Read Register
  //-----------------------------------------------------------------------------
  struct FILTERYNREAD_BITS {           // bits   description
    Uint32 rsvd0:8;                    // 31:24  Reserved
    int32 YN:24;                      // 23:0   YN Value
  };
  union FILTERYNREAD_REG {
    struct FILTERYNREAD_BITS   bit;
    Uint32                     all;  
  };  

  //-----------------------------------------------------------------------------
  // Coefficient Configuration Register
  //-----------------------------------------------------------------------------
  struct COEFCONFIG_BITS {         // bits   description
    Uint32 rsvd0:4;                // 31:28  Reserved
    Uint32 BIN6_ALPHA:1;           // 27     Bin6 Alpha Configuration
    Uint32 BIN6_CONFIG:3;          // 26:24  Bin6 Configuration
    Uint32 BIN5_ALPHA:1;           // 23     Bin5 Alpha Configuration
    Uint32 BIN5_CONFIG:3;          // 22:20  Bin5 Configuration
    Uint32 BIN4_ALPHA:1;           // 19     Bin4 Alpha Configuration
    Uint32 BIN4_CONFIG:3;          // 18:16  Bin4 Configuration
    Uint32 BIN3_ALPHA:1;           // 15     Bin3 Alpha Configuration
    Uint32 BIN3_CONFIG:3;          // 14:12  Bin3 Configuration
    Uint32 BIN2_ALPHA:1;           // 11     Bin2 Alpha Configuration
    Uint32 BIN2_CONFIG:3;          // 10:8   Bin2 Configuration
    Uint32 BIN1_ALPHA:1;           // 7      Bin1 Alpha Configuration
    Uint32 BIN1_CONFIG:3;          // 6:4    Bin1 Configuration
    Uint32 BIN0_ALPHA:1;           // 3      Bin0 Alpha Configuration
    Uint32 BIN0_CONFIG:3;          // 2:0    Bin0 Configuration
  };
  union COEFCONFIG_REG {
    struct COEFCONFIG_BITS bit;
    Uint32                 all;  
  };
  
  //-----------------------------------------------------------------------------
  // Filter KP Coefficient 0 Register
  //-----------------------------------------------------------------------------
  struct FILTERKPCOEF0_BITS {        // bits   description
    int32 KP_COEF_1:16;             // 31:16  KP Coefficient 1
    int32 KP_COEF_0:16;             // 15:0   KP Coefficient 0
  };
  union FILTERKPCOEF0_REG {
    struct FILTERKPCOEF0_BITS bit;
    Uint32                    all; 
  };
  
  //-----------------------------------------------------------------------------
  // Filter KP Coefficient 1 Register
  //-----------------------------------------------------------------------------
  struct FILTERKPCOEF1_BITS {        // bits   description
    int32 rsvd0:16;                 // 31:16  Reserved
    int32 KP_COEF_2:16;             // 15:0   KP Coefficient 2
  };
  union FILTERKPCOEF1_REG {
    struct FILTERKPCOEF1_BITS bit;
    Uint32                    all;
  };
  
  //-----------------------------------------------------------------------------
  // Filter KI Coefficient 0 Register
  //-----------------------------------------------------------------------------
  struct FILTERKICOEF0_BITS {        // bits   description
    int32 KI_COEF_1:16;             // 31:16  KI Coefficient 1
    int32 KI_COEF_0:16;             // 15:0   KI Coefficient 0
  };
  union FILTERKICOEF0_REG {   
    struct FILTERKICOEF0_BITS bit;
	Uint32                    all;
  };
  
  //-----------------------------------------------------------------------------
  // Filter KI Coefficient 1 Register
  //-----------------------------------------------------------------------------
  struct FILTERKICOEF1_BITS {        // bits   description
    int32 KI_COEF_3:16;             // 31:16  KI Coefficient 3
    int32 KI_COEF_2:16;             // 15:0   KI Coefficient 2
  };
  union FILTERKICOEF1_REG {
    struct FILTERKICOEF1_BITS bit;
    Uint32                    all;
  };  

  //-----------------------------------------------------------------------------
  // Filter KD Coefficient 0 Register
  //-----------------------------------------------------------------------------
  struct FILTERKDCOEF0_BITS {        // bits   description
    int32 KD_COEF_1:16;             // 31:16  KD Coefficient 1
    int32 KD_COEF_0:16;             // 15:0   KD Coefficient 0
  };
  union FILTERKDCOEF0_REG {
    struct FILTERKDCOEF0_BITS bit;
    Uint32                    all;
  }; 

  //-----------------------------------------------------------------------------
  // Filter KD Coefficient 1 Register
  //-----------------------------------------------------------------------------
  struct FILTERKDCOEF1_BITS {     // bits   description
    Uint32 rsvd0:16;              // 31:16  Reserved
    int32 KD_COEF_2:16;          // 15:0   KD Coefficient 2
  };
  union FILTERKDCOEF1_REG {
    struct FILTERKDCOEF1_BITS bit;
    Uint32                    all; 
  };  
  
  //-----------------------------------------------------------------------------
  // Filter KD Alpha Register
  //-----------------------------------------------------------------------------
  struct FILTERKDALPHA_BITS {     // bits   description 
    Uint32 rsvd1:7;               // 31:25  Reserved
    int32 KD_ALPHA_1:9;          // 24:16  KD Alpha 1 Value
    Uint32 rsvd0:7;               // 15:9   Reserved
    int32 KD_ALPHA_0:9;          // 8:0    KD Alpha 0 Value
  };
  union FILTERKDALPHA_REG {
    struct FILTERKDALPHA_BITS bit;
    Uint32                    all;   
  };
  
  //-----------------------------------------------------------------------------
  // Filter Non-Linear Limit Register 0
  //-----------------------------------------------------------------------------
  struct FILTERNL0_BITS {         // bits   description 
    Uint32 rsvd1:7;               // 31:25  Reserved
    int32 LIMIT1:9;              // 24:16  Non-Linear Limit 1 Value
    Uint32 rsvd0:7;               // 15:9   Reserved
    int32 LIMIT0:9;              // 8:0    Non-Linear Limit 0 Value
  };
  union FILTERNL0_REG {
    struct FILTERNL0_BITS     bit;
    Uint32                    all; 
  }; 

  //-----------------------------------------------------------------------------
  // Filter Non-Linear Limit Register 1
  //-----------------------------------------------------------------------------
  struct FILTERNL1_BITS {         // bits   description 
    Uint32 rsvd1:7;               // 31:25  Reserved
    int32 LIMIT3:9;              // 24:16  Non-Linear Limit 3 Value
    Uint32 rsvd0:7;               // 15:9   Reserved
    int32 LIMIT2:9;              // 8:0    Non-Linear Limit 2 Value
  };
  union FILTERNL1_REG {
    struct FILTERNL1_BITS  bit;
    Uint32                 all;  
  };   

  //-----------------------------------------------------------------------------
  // Filter Non-Linear Limit Register 2
  //-----------------------------------------------------------------------------
  struct FILTERNL2_BITS {         // bits   description 
    Uint32 rsvd1:7;               // 31:25  Reserved
    int32 LIMIT5:9;              // 24:16  Non-Linear Limit 5 Value
    Uint32 rsvd0:7;               // 15:9   Reserved
    int32 LIMIT4:9;              // 8:0    Non-Linear Limit 4 Value
  };
  union FILTERNL2_REG {
    struct FILTERNL2_BITS  bit;
    Uint32                 all;
  };       

  //-----------------------------------------------------------------------------
  // Filter KI Feedback Clamp High Register
  //-----------------------------------------------------------------------------
  struct FILTERKICLPHI_BITS {        // bits   description 
    Uint32 rsvd0:8;                  // 31:24  Reserved
    int32 KI_CLAMP_HIGH:24;          // 23:0   KI Clamp High
  };
  union FILTERKICLPHI_REG {
    struct FILTERKICLPHI_BITS bit;
    Uint32                    all;
  };

  //-----------------------------------------------------------------------------
  // Filter KI Feedback Clamp Low Register
  //-----------------------------------------------------------------------------
  struct FILTERKICLPLO_BITS {     // bits   description 
    Uint32 rsvd0:8;               // 31:24  Reserved
    int32 KI_CLAMP_LOW:24;        // 23:0   KI Clamp Low
  };
  union FILTERKICLPLO_REG {
    struct FILTERKICLPLO_BITS bit;
    Uint32                    all;
  };

  //-----------------------------------------------------------------------------
  // Filter YN Clamp High Register
  //-----------------------------------------------------------------------------
  struct FILTERYNCLPHI_BITS {     // Bits   Description
    Uint32 rsvd0:8;               // 31:24  Reserved
    int32  YN_CLAMP_HIGH:24;      // 23:0   YN Clamp High
  };
  union FILTERYNCLPHI_REG {
    struct FILTERYNCLPHI_BITS bit;
    int32                     all; 
  };

  //-----------------------------------------------------------------------------
  // Filter YN Clamp Low Register
  //-----------------------------------------------------------------------------
  struct FILTERYNCLPLO_BITS {     // Bits   Description
    Uint32 rsvd0:8;               // 31:24  Reserved
    int32  YN_CLAMP_LOW:24;       // 23:0   YN Clamp High
  };
  union FILTERYNCLPLO_REG {
    struct FILTERYNCLPLO_BITS bit;
    int32                     all;
  };

  //-----------------------------------------------------------------------------
  // Filter Output Clamp High Register
  //-----------------------------------------------------------------------------
  struct FILTEROCLPHI_BITS {         // Bits   description
    Uint32 rsvd0:14;                 // 31:18  Reserved
    Uint32 OUTPUT_CLAMP_HIGH:18;     // 17:0   Output Clamp High
  };
  union FILTEROCLPHI_REG {
    struct FILTEROCLPHI_BITS  bit;
    Uint32                    all;
  };
    
  //-----------------------------------------------------------------------------
  // Filter Output Clamp Low Register
  //-----------------------------------------------------------------------------
  struct FILTEROCLPLO_BITS {         // Bits   description
    Uint32 rsvd0:14;                 // 31:18  Reserved
    Uint32 OUTPUT_CLAMP_LOW:18;      // 17:0   Output Clamp Low
  };
  union FILTEROCLPLO_REG {
    struct FILTEROCLPLO_BITS  bit;
    Uint32                    all;
  };

  //-----------------------------------------------------------------------------
  // Filter Preset Register
  //-----------------------------------------------------------------------------
  struct FILTERPRESET_BITS {       // Bits   Description
    Uint32 rsvd0:4;                // 31:28  Reserved
    Uint32 PRESET_EN:1;            // 27     Filter Preset Enable
    Uint32 PRESET_REG_SEL:3;       // 26:24  Filter Preset Select
    int32  PRESET_VALUE:24;        // 23:0   Filter Preset Value
  };
  union FILTERPRESET_REG {
    struct FILTERPRESET_BITS  bit;
    Uint32                    all;
  };

  //=============================================================================
  // Filter Module Register File
  //=============================================================================
  struct FILTER_REGS {
    union FILTERSTATUS_REG      FILTERSTATUS;       // Filter Status Register
    union FILTERCTRL_REG        FILTERCTRL;         // Filter Control Register
    union CPUXN_REG             CPUXN;              // CPU XN Register
    union FILTERXNREAD_REG      FILTERXNREAD;       // Filter XN Read Register
    union FILTERKIYNREAD_REG    FILTERKIYNREAD;     // Filter KI YN Read Register
    union FILTERKDYNREAD_REG    FILTERKDYNREAD;     // Filter KD YN Read Register
    union FILTERYNREAD_REG      FILTERYNREAD;       // Filter YN Read Register    
    union COEFCONFIG_REG        COEFCONFIG;         // Coefficient Configuration Register
    union FILTERKPCOEF0_REG     FILTERKPCOEF0;      // Filter KP Coefficient 0 Register
    union FILTERKPCOEF1_REG     FILTERKPCOEF1;      // Filter KP Coefficient 1 Register
    union FILTERKICOEF0_REG     FILTERKICOEF0;      // Filter KI Coefficient 0 Register
    union FILTERKICOEF1_REG     FILTERKICOEF1;      // Filter KI Coefficient 1 Register
    union FILTERKDCOEF0_REG     FILTERKDCOEF0;      // Filter KD Coefficient 0 Register
    union FILTERKDCOEF1_REG     FILTERKDCOEF1;      // Filter KD Coefficient 1 Register
    union FILTERKDALPHA_REG     FILTERKDALPHA;      // Filter KD Alpha Register
    union FILTERNL0_REG         FILTERNL0;          // Filter Non-Linear Limit 0 Register
    union FILTERNL1_REG         FILTERNL1;          // Filter Non-Linear Limit 1 Register
    union FILTERNL2_REG         FILTERNL2;          // Filter Non-Linear Limit 2 Register
    union FILTERKICLPHI_REG     FILTERKICLPHI;      // Filter KI Feedback Clamp High Register
    union FILTERKICLPLO_REG     FILTERKICLPLO;      // Filter KI Feedback Clamp Low Register
    union FILTERYNCLPHI_REG     FILTERYNCLPHI;      // Filter Yn Clamp High Register
    union FILTERYNCLPLO_REG     FILTERYNCLPLO;      // Filter Yn Clamp Low Register
    union FILTEROCLPHI_REG      FILTEROCLPHI;       // Filter Output Clamp High Register
    union FILTEROCLPLO_REG      FILTEROCLPLO;       // Filter Output Clamp Low Register
    union FILTERPRESET_REG      FILTERPRESET;       // Filter Preset Register
  };
  
  //-----------------------------------------------------------------------------
  // ADC Module External References & Function Declarations:
  //-----------------------------------------------------------------------------
  extern volatile struct FILTER_REGS Filter0Regs;
  extern volatile struct FILTER_REGS Filter1Regs;
  extern volatile struct FILTER_REGS Filter2Regs;


#ifdef __cplusplus
}       // end of extern "C"
#endif

#endif  // end of CYCLONE_FILTER_H definition

//===========================================================================
// End of file
//===========================================================================
