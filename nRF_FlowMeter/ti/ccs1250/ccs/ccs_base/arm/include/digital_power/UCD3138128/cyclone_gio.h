//###########################################################################
//
// FILE:   cyclone_gio.h
//
// TITLE:  Cyclone Device Gio Module Register Definitions.
//
// NOTES:
//  1) Bitfields have been defined for big-endian only.
//###########################################################################
//
//  Ver  | dd mmm yyyy | Who  | Description of changes
// ======|=============|======|==============================================
//  1.00 | 12 Aug 2009 | CMF  | Started with Spartan_Gio.h.
//       |             |      | Updated for 1.0 Memory map document.
//       |             |      |
//
//  Texas Instruments, Inc
//  Copyright Texas Instruments 2008. All rights reserved.
//###########################################################################

#ifndef CYCLONE_GIO_H
#define CYCLONE_GIO_H

#ifdef __cplusplus
extern "C" {
#endif

//===============================================================================
// GIO Individual Register Bit Definitions
//===============================================================================

  //-----------------------------------------------------------------------------
  // Fault Port I/O Direction Register bit definitions 
  //-----------------------------------------------------------------------------
  struct FAULTDIR_BITS {            // bits   description
    Uint32 rsvd0:24;                // 31:8   reserved
    Uint32 GIO_D_DIR:1;             // 7      GIO_D Pin Direction in GPIO Mode
    Uint32 GIO_C_DIR:1;             // 6      GIO_C Pin Direction in GPIO Mode
    Uint32 GIO_B_DIR:1;             // 5      GIO_B Pin Direction in GPIO Mode
    Uint32 GIO_A_DIR:1;             // 4      GIO_A Pin Direction in GPIO Mode
    Uint32 FLT3_DIR:1;              // 3      FAULT[3] Pin Direction
    Uint32 FLT2_DIR:1;              // 2      FAULT[2] Pin Direction
    Uint32 FLT1_DIR:1;              // 1      FAULT[1] Pin Direction
    Uint32 FLT0_DIR:1;              // 0      FAULT[0] Pin Direction
  };
  union FAULTDIR_REG {
    Uint32                all;
    struct FAULTDIR_BITS  bit;
  };

  //-----------------------------------------------------------------------------
  // Fault Port In Register bit definitions 
  //-----------------------------------------------------------------------------
  struct FAULTIN_BITS {             // bits   description
    Uint32 rsvd0:24;                // 31:8   reserved
    Uint32 GIO_D_IN:1;              // 7      GIO_D Input Value in GPIO Mode
    Uint32 GIO_C_IN:1;              // 6      GIO_C Input Value in GPIO Mode
    Uint32 GIO_B_IN:1;              // 5      GIO_B Input Value in GPIO Mode
    Uint32 GIO_A_IN:1;              // 4      GIO_A Input Value in GPIO Mode
    Uint32 FLT3_IN:1;               // 3      FAULT[3] Input Value
    Uint32 FLT2_IN:1;               // 2      FAULT[2] Input Value
    Uint32 FLT1_IN:1;               // 1      FAULT[1] Input Value
    Uint32 FLT0_IN:1;               // 0      FAULT[0] Input Value
  };
  union FAULTIN_REG {
    Uint32                all;
    struct FAULTIN_BITS   bit;
  };
  
  //-----------------------------------------------------------------------------
  // Fault Port Output Register bit definitions 
  //-----------------------------------------------------------------------------
  struct FAULTOUT_BITS {            // bits   description
    Uint32 rsvd1:24;                // 31:8   reserved
    Uint32 GIO_D_OUT:1;             // 7      GIO_D pin output data
    Uint32 GIO_C_OUT:1;             // 6      GIO_C pin output data
    Uint32 GIO_B_OUT:1;             // 5      GIO_B pin output data
    Uint32 GIO_A_OUT:1;             // 4      GIO_A pin output data
    Uint32 FLT3_OUT:1;              // 3      FAULT[3] pin output data
    Uint32 FLT2_OUT:1;              // 2      FAULT[2] pin output data
    Uint32 FLT1_OUT:1;              // 1      FAULT[1] pin output data
    Uint32 FLT0_OUT:1;              // 0      FAULT[0] pin output data
  };
  union FAULTOUT_REG {
    Uint32                all;
    struct FAULTOUT_BITS  bit;
  };
  
  //-----------------------------------------------------------------------------
  // Fault Port Interrupt Enable Register bit definitions 
  //-----------------------------------------------------------------------------
  struct FAULTINTENA_BITS {         // bits   description
    Uint32 rsvd0:24;                // 31:8   reserved
    Uint32 GIO_D_INT_EN:1;          // 7      GIO_D pin interrupt enable
    Uint32 GIO_C_INT_EN:1;          // 6      GIO_C pin interrupt enable
    Uint32 GIO_B_INT_EN:1;          // 5      GIO_B pin interrupt enable
    Uint32 GIO_A_INT_EN:1;          // 4      GIO_A pin interrupt enable
    Uint32 FLT3_INT_EN:1;           // 3      FAULT[3] pin interrupt enable
    Uint32 FLT2_INT_EN:1;           // 2      FAULT[2] pin interrupt enable
    Uint32 FLT1_INT_EN:1;           // 1      FAULT[1] pin interrupt enable
    Uint32 FLT0_INT_EN:1;           // 0      FAULT[0] pin interrupt enable
  };
  union FAULTINTENA_REG {
    Uint32                   all;
    struct FAULTINTENA_BITS  bit;
  };
  
  //-----------------------------------------------------------------------------
  // Fault Port Interrupt Polarity Register bit definitions 
  //-----------------------------------------------------------------------------
  struct FAULTINTPOL_BITS {         // bits   description
    Uint32 rsvd0:24;                // 31:8   reserved
    Uint32 GIO_D_INT_POL:1;         // 7      GIO_D pin interrupt polarity
    Uint32 GIO_C_INT_POL:1;         // 6      GIO_C pin interrupt polarity
    Uint32 GIO_B_INT_POL:1;         // 5      GIO_B pin interrupt polarity
    Uint32 GIO_A_INT_POL:1;         // 4      GIO_A pin interrupt polarity
    Uint32 FLT3_INT_POL:1;          // 3      FAULT[3] pin interrupt polarity
    Uint32 FLT2_INT_POL:1;          // 2      FAULT[2] pin interrupt polarity
    Uint32 FLT1_INT_POL:1;          // 1      FAULT[1] pin interrupt polarity
    Uint32 FLT0_INT_POL:1;          // 0      FAULT[0] pin interrupt polarity
  };
  union FAULTINTPOL_REG {
    Uint32                   all;
    struct FAULTINTPOL_BITS  bit;
  };
  
  //-----------------------------------------------------------------------------
  // Fault Port Interrupt Pending Register bit definitions 
  //-----------------------------------------------------------------------------
  struct FAULTINTPEND_BITS {        // bits   description
    Uint32 rsvd0:24;                // 31:8   reserved
    Uint32 GIO_D_INT_PEND:1;        // 7      GIO_D pin interrupt flag
    Uint32 GIO_C_INT_PEND:1;        // 6      GIO_C pin interrupt flag
    Uint32 GIO_B_INT_PEND:1;        // 5      GIO_B pin interrupt flag
    Uint32 GIO_A_INT_PEND:1;        // 4      GIO_A pin interrupt flag
    Uint32 FLT3_INT_PEND:1;         // 3      FAULT[3] pin interrupt flag
    Uint32 FLT2_INT_PEND:1;         // 2      FAULT[2] pin interrupt flag
    Uint32 FLT1_INT_PEND:1;         // 1      FAULT[1] pin interrupt flag
    Uint32 FLT0_INT_PEND:1;         // 0      FAULT[0] pin interrupt flag
  };
  union FAULTINTPEND_REG {
    Uint32                    all;
    struct FAULTINTPEND_BITS  bit;
  };
  
  //-----------------------------------------------------------------------------
  // External Interrupt I/O Direction Register bit definitions 
  //-----------------------------------------------------------------------------
  struct EXTINTDIR_BITS {            // bits   description
    Uint32 rsvd0:31;                 // 31:1   reserved
    Uint32 EXT_INT_DIR:1;            // 0      External Interrupt Pin Direction 
  };
  union EXTINTDIR_REG {
    Uint32                 all;
    struct EXTINTDIR_BITS  bit;
  };

  //-----------------------------------------------------------------------------
  // External Interrupt Input Register bit definitions 
  //-----------------------------------------------------------------------------
  struct EXTINTIN_BITS {             // bits   description
    Uint32 rsvd0:31;                 // 31:1   reserved
    Uint32 EXT_INT_IN:1;             // 0      External Interrupt Pin Input Value
  };
  union EXTINTIN_REG {
    Uint32                 all;
    struct EXTINTIN_BITS   bit;
  };
  
  //-----------------------------------------------------------------------------
  // External Interrupt Output Register bit definitions 
  //-----------------------------------------------------------------------------
  struct EXTINTOUT_BITS {           // bits   description
    Uint32 rsvd0:31;                // 31:1   reserved
    Uint32 EXT_INT_OUT:1;            // 0      External Interrupt pin output data
  };
  union EXTINTOUT_REG {
    Uint32                 all;
    struct EXTINTOUT_BITS  bit;
  };
  
  //-----------------------------------------------------------------------------
  // External Interrupt Enable Register bit definitions 
  //-----------------------------------------------------------------------------
  struct EXTINTENA_BITS {           // bits   description
    Uint32 rsvd0:31;                // 31:1   reserved
    Uint32 EXT_INT_EN:1;            // 0      External Interrupt pin interrupt enable
  };
  union EXTINTENA_REG {
    Uint32                 all;
    struct EXTINTENA_BITS  bit;
  };
  
  //-----------------------------------------------------------------------------
  // External Interrupt Polarity Register bit definitions 
  //-----------------------------------------------------------------------------
  struct EXTINTPOL_BITS {           // bits   description
    Uint32 rsvd0:31;                // 31:1   reserved
    Uint32 EXT_INT_POL:1;           // 0      External Interrupt pin interrupt polarity
  };
  union EXTINTPOL_REG {
    Uint32                 all;
    struct EXTINTPOL_BITS  bit;
  };
  
  //-----------------------------------------------------------------------------
  // External Interrupt Pending Register bit definitions 
  //-----------------------------------------------------------------------------
  struct EXTINTPEND_BITS {          // bits   description
    Uint32 rsvd0:31;                // 31:1   reserved
    Uint32 EXT_INT_PEND:1;          // 0      External Interrupt pin interrupt flag
  };
  union EXTINTPEND_REG {
    Uint32                  all;
    struct EXTINTPEND_BITS  bit;
  };  

  //=============================================================================
  // GIO Module Register File
  //=============================================================================
  struct GIO_REGS {
    union  FAULTDIR_REG      FAULTDIR;      // Fault Port Direction Register
    union  FAULTIN_REG       FAULTIN;       // Fault Port Input Data
    union  FAULTOUT_REG      FAULTOUT;      // Fault Port Output Data
    Uint32                   RSVD_3;        // Reserved
    Uint32                   RSVD_2;        // Reserved
    union  FAULTINTENA_REG   FAULTINTENA;   // Fault Port Interrupt Enable Register
    union  FAULTINTPOL_REG   FAULTINTPOL;   // Fault Port Interrupt Polarity Register
    union  FAULTINTPEND_REG  FAULTINTPEND;  // Fault Port Interrupt Pending Register
    union  EXTINTDIR_REG     EXTINTDIR;     // External Interrupt Direction Register
    union  EXTINTIN_REG      EXTINTIN;      // External Interrupt Input Data
    union  EXTINTOUT_REG     EXTINTOUT;     // External Interrupt Output Data
    Uint32                   RSVD_1;        // Reserved
    Uint32                   RSVD_0;        // Reserved
    union  EXTINTENA_REG     EXTINTENA;     // External Interrupt Enable Register
    union  EXTINTPOL_REG     EXTINTPOL;     // External Interrupt Polarity Register
    union  EXTINTPEND_REG    EXTINTPEND;    // External Interrupt Pending Register
  };

  //---------------------------------------------------------------------------
  // GIO Module External References & Function Declarations:
  //
  extern volatile struct GIO_REGS GioRegs;
  
  //===========================================================================
#ifdef __cplusplus
}       // end of extern "C"
#endif

#endif  // end of CYCLONE_GIO_H definition

//===========================================================================
// End of file
//===========================================================================
