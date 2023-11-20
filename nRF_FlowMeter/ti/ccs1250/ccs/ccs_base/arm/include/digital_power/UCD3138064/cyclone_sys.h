//###########################################################################
//
// FILE:   cyclone_sys.h
//
// TITLE:  Cyclone System Module Register Definitions.
//
// NOTES:
//  1) Bitfields have been defined for big-endian only.
//###########################################################################
//
//  Ver  | dd mmm yyyy | Who  | Description of changes
// ======|=============|======|==============================================
//  1.00 | 12 Aug 2009 | CMF  | Started with Spartan_Sys.h.
//       |             |      | Updated for 1.0 Memory map document.
//       |             |      |
//
//  Texas Instruments, Inc
//  Copyright Texas Instruments 2008. All rights reserved.
//###########################################################################

#ifndef CYCLONE_SYS_H
#define CYCLONE_SYS_H

#ifdef __cplusplus
extern "C" {
#endif

//===========================================================================
// System Module Individual Register Bit Definitions
//

//-------------------------------------------------
// Clock Control Register bit definitions
//
struct CLKCNTL_BITS {            // bits   description
  Uint32 rsvd3:22;               // 31:10  reserved
  Uint32 M_DIV_RATIO:2;          // 9:8    MCLK (processor clock) divide ratio
  Uint32 rsvd2:1;                // 7      reserved
  Uint32 CLKSR:2;                // 6:5    CLKOUT pin source
  Uint32 rsvd1:1;                // 4      reserved
  Uint32 CLKDOUT:1;              // 3      CLKOUT pin output data
  Uint32 rsvd0:1;                // 2      Reserved
  Uint32 ARM_MODE:2;             // 1:0    ARM Mode
};
union CLKCNTL_REG {
   Uint32                 all;
   struct CLKCNTL_BITS    bit;
};

//-------------------------------------------------
// System Exception Control Register bit definitions
//
struct SYSECR_BITS {              // bits   description
   Uint32 rsvd1:16;               // 31:16  reserved
   Uint32 RESET:2;                // 15:14  Software reset
   Uint32 rsvd0:11;               // 13:3   reserved
   Uint32 PACCOVR:1;              // 2      Peripheral access violation override
   Uint32 ACCOVR:1;               // 1      Memory access reset override
   Uint32 ILLOVR:1;               // 0      Illegal address reset override
};
union SYSECR_REG {
   Uint32                 all;
   struct SYSECR_BITS     bit;
};

//-------------------------------------------------
// System Exception Status Register bit definitions
//
struct SYSESR_BITS {              // bits   description
   Uint32 rsvd1:16;               // 31:16  reserved
   Uint32 PORRST:1;               // 15     Power-up reset flag
   Uint32 CLKRST:1;               // 14     Clock fail flag
   Uint32 WDRST:1;                // 13     Watchdog reset flag
   Uint32 ILLMODE:1;              // 12     Illegal mode flag
   Uint32 ILLADR:1;               // 11     Illegal address access flag 
   Uint32 ILLACC:1;               // 10     Illegal memory access flag
   Uint32 PILLACC:1;              // 9      Peripheral illegal access flag
   Uint32 ILLMAP:1;               // 8      Illegal address map flag
   Uint32 SWRST:1;                // 7      Software reset flag
   Uint32 rsvd0:7;                // 6:0    reserved
};
union SYSESR_REG {
   Uint32                 all;
   struct SYSESR_BITS     bit;
};

//-------------------------------------------------
// Abort Exception Status Register bit definitions
//
struct ABRTESR_BITS {             // bits   description
   Uint32 rsvd1:16;               // 31:16  reserved
   Uint32 ADRABT:1;               // 15     Illegal address abort
   Uint32 MEMABT:1;               // 14     Memory access abort
   Uint32 PACCVIO:1;              // 13     Peripheral access violation error
   Uint32 rsvd0:13;               // 12:0   reserved      
};
union ABRTESR_REG {
   Uint32                 all;
   struct ABRTESR_BITS    bit;
};

//-------------------------------------------------
// Global Status Register bit definitions
//
struct GLBSTAT_BITS {             // bits   description
   Uint32 rsvd1:24;               // 31:8   reserved
   Uint32 SYSADDR:1;              // 7      System illegal address flag
   Uint32 SYSACC:1;               // 6      System illegal access flag
   Uint32 MPUADDR:1;              // 5      MPU illegal address flag
   Uint32 MPUACC:1;               // 4      MPU illegal access flag
   Uint32 rsvd0:4;                // 3:0    reserved
};
union GLBSTAT_REG {
   Uint32                 all;
   struct GLBSTAT_BITS    bit;
};

//-------------------------------------------------
// Device Identification Register bit definitions
//
struct DEV_BITS {                 // bits   description
   Uint32 rsvd0:16;               // 31:16  reserved
   Uint32 DEV:16;                 // 15:0   Device identification code
};
union DEV_REG {
   Uint32                 all;
   struct DEV_BITS        bit;
};

//-------------------------------------------------
// System Software Interrupt Flag Register bit definitions
//
struct SSIF_BITS {                // bits   description
   Uint32 rsvd0:31;               // 31:1   reserved
   Uint32 SSIFLAG:1;              // 0      System software interrupt flag
};
union SSIF_REG {
   Uint32                 all;
   struct SSIF_BITS       bit;
};

//-------------------------------------------------
// System Software Interrupt Request Register bit definitions
//
struct SSIR_BITS {                // bits   description
   Uint32 rsvd0:16;               // 31:16  reserved
   Uint32 SSKEY:8;                // 15:8   System software interrupt request key
   Uint32 SSDATA:8;               // 7:0    System software interrupt data
};
union SSIR_REG {
   Uint32                 all;
   struct SSIR_BITS       bit;
};


//===========================================================================
// System Module Register File
//
struct SYS_REGS {
   union  CLKCNTL_REG    CLKCNTL;       // Clock Control Register
   Uint32                RSVD[3];       // Reserved (address spacer)
   union  SYSECR_REG     SYSECR;        // System Exception Control Register
   union  SYSESR_REG     SYSESR;        // System Exception Status Register
   union  ABRTESR_REG    ABRTESR;       // Abort Exception Status Register
   union  GLBSTAT_REG    GLBSTAT;       // Global Status Register
   union  DEV_REG        DEV;           // Device Identification Register
   Uint32                RSVD1[1];      // Reserved (address spacer)
   union  SSIF_REG       SSIF;          // System Software Interrupt Flag Register
   union  SSIR_REG       SSIR;          // System Software Interrupt Request Register
};

//---------------------------------------------------------------------------
// System Module External References & Function Declarations:
//
extern volatile struct SYS_REGS SysRegs;

//===========================================================================
#ifdef __cplusplus
}       // end of extern "C"
#endif

#endif  // end of CYCLONE_SYS_H definition

//===========================================================================
// End of file
//===========================================================================
