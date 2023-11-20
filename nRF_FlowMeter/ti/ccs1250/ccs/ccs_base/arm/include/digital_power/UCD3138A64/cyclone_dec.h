//###########################################################################
//
// FILE:   cyclone_dec.h
//
// TITLE:  Cyclone Address Manager Register Definitions.
//
// NOTES:
//  1) Bitfields have been defined for big-endian only.
//###########################################################################
//
//  Ver  | dd mmm yyyy | Who  | Description of changes
// ======|=============|======|==============================================
//  1.00 | 12 Aug 2009 | CMF  | Started with Spartan_Dec.h.
//       |             |      | Updated for 1.0 Memory map document.
//       |             |      |
//
//  Texas Instruments, Inc
//  Copyright Texas Instruments 2008. All rights reserved.
//###########################################################################

#ifndef CYCLONE_DEC_H
#define CYCLONE_DEC_H

#ifdef __cplusplus
extern "C" {
#endif

//===========================================================================
// Address Manager Module Individual Register Bit Definitions
//

  //-----------------------------------------------------------------------------
  // Memory Fine Base Address High Register 0 bit definitions
  //-----------------------------------------------------------------------------
  struct MFBAHR0_BITS {            // bits   description
    Uint32 rsvd0:16;               // 31:16  reserved
    Uint32 ADDRESS:16;             // 15:0   Address[31:16]
  };
  union MFBAHR0_REG {
    Uint32                 all;
    struct MFBAHR0_BITS    bit;
  };

  //-----------------------------------------------------------------------------
  // Memory Fine Base Address Low Register 0 bit definitions
  //-----------------------------------------------------------------------------
  struct MFBALR0_BITS {            // bits   description
    Uint32 rsvd2:16;               // 31:16  reserved
    Uint32 ADDRESS:6;              // 15:10  Address[15:10]
    Uint32 rsvd1:1;                // 9      reserved
    Uint32 MS:1;                   // 8      Memory map select
    Uint32 BLOCK_SIZE:4;           // 7:4    Block size
    Uint32 rsvd0:2;                // 3:2    reserved
    Uint32 RONLY:1;                // 1      Read-only protection
    Uint32 PRIV:1;                 // 0      Privilege mode protection
  };
  union MFBALR0_REG {
    Uint32                 all;
    struct MFBALR0_BITS    bit;
  };
  
  //-----------------------------------------------------------------------------
  // Memory Fine Base Address High Registers 1-19 bit definitions
  //-----------------------------------------------------------------------------
  struct MFBAHRX_BITS {            // bits   description
    Uint32 rsvd0:16;               // 31:16  reserved
    Uint32 ADDRESS:16;             // 15:0   Address[31:16]
  };
  union MFBAHRX_REG {
    Uint32                 all;
    struct MFBAHRX_BITS    bit;
  };
  
  //-----------------------------------------------------------------------------
  // Memory Fine Base Address Low Registers 1-3,17-19 bit definitions
  //-----------------------------------------------------------------------------
  struct MFBALRX_BITS {            // bits   description
    Uint32 rsvd2:16;               // 31:16  reserved
    Uint32 ADDRESS:6;              // 15:10  Address[15:10]
    Uint32 AW:1;                   // 9      Auto-wait-on-write
    Uint32 rsvd1:1;                // 8      reserved
    Uint32 BLOCK_SIZE:4;           // 7:4    Block size
    Uint32 rsvd0:2;                // 3:2    reserved
    Uint32 RONLY:1;                // 1      Read-only protection
    Uint32 PRIV:1;                 // 0      Privilege mode protection
  };
  union MFBALRX_REG {
    Uint32                 all;
    struct MFBALRX_BITS    bit;
  };
  
  //-----------------------------------------------------------------------------
  // Memory Fine Base Address Low Registers 4-16 bit definitions
  //-----------------------------------------------------------------------------
  struct MFBALRY_BITS {            // bits   description
    Uint32 rsvd1:16;               // 31:16  reserved
    Uint32 ADDRESS:6;              // 15:10  Address[15:10]
    Uint32 AW:1;                   // 9      Auto-wait-on-write
    Uint32 rsvd0:7;                // 8:2    reserved
    Uint32 RONLY:1;                // 1      Read-only protection
    Uint32 PRIV:1;                 // 0      Privilege mode protection
  };
  union MFBALRY_REG {
    Uint32                 all;
    struct MFBALRY_BITS    bit;
  }; 

  //-----------------------------------------------------------------------------
  // Program Flash Control Registers 0-3 bit definitions
  //-----------------------------------------------------------------------------
  struct PFLASHCTRL_X_BITS {         // bits   description
    Uint32 rsvd2:20;               // 31:12  reserved
    Uint32 BUSY:1;                 // 11     Flash busy
    Uint32 rsvd1:1;                // 10     leave as 0
    Uint32 PAGE_ERASE:1;           // 9      Page erase enable
    Uint32 MASS_ERASE:1;           // 8      Mass erase enable
    Uint32 rsvd0:3;                // 7:5    reserved
    Uint32 PAGE_SEL:5;             // 4:0    Page selection
  };
  union PFLASHCTRL_X_REG {
    Uint32                     all;
    struct PFLASHCTRL_X_BITS     bit;
  };
  
  //-----------------------------------------------------------------------------
  // Data Flash Control Register bit definitions
  //-----------------------------------------------------------------------------
  struct DFLASHCTRL_BITS {         // bits   description
    Uint32 rsvd2:20;               // 31:12  reserved
    Uint32 BUSY:1;                 // 11     Flash busy
    Uint32 rsvd1:1;                // 10     leave as 0
    Uint32 PAGE_ERASE:1;           // 9      Page erase enable
    Uint32 MASS_ERASE:1;           // 8      Mass erase enable
    Uint32 rsvd0:2;                // 7:6    reserved
    Uint32 PAGE_SEL:6;             // 5:0    Page selection
  };
  union DFLASHCTRL_REG {
    Uint32                     all;
    struct DFLASHCTRL_BITS     bit;
  };

  //-----------------------------------------------------------------------------
  // Flash Interlock Register bit definitions
  //-----------------------------------------------------------------------------
  struct FLASHILOCK_BITS {        // bits   description
    Uint32 INTERLOCK_KEY:32;      // 31:0   Interlock Key
  };
  union FLASHILOCK_REG {
    Uint32                     all;
    struct FLASHILOCK_BITS     bit;
  };

  //=============================================================================
  // Address Manager Module Register File
  //=============================================================================
  struct DEC_REGS {
    union  MFBAHR0_REG        MFBAHR0;        // Memory Fine Base Address High Register 0
    union  MFBALR0_REG        MFBALR0;        // Memory Fine Base Address Low Register 0
    union  MFBAHRX_REG        MFBAHR1;        // Memory Fine Base Address High Register 1
    union  MFBALRX_REG        MFBALR1;        // Memory Fine Base Address Low Register 1
    union  MFBAHRX_REG        MFBAHR2;        // Memory Fine Base Address High Register 2
    union  MFBALRX_REG        MFBALR2;        // Memory Fine Base Address Low Register 2
    union  MFBAHRX_REG        MFBAHR3;        // Memory Fine Base Address High Register 3
    union  MFBALRX_REG        MFBALR3;        // Memory Fine Base Address Low Register 3
    union  MFBAHRX_REG        MFBAHR4;        // Memory Fine Base Address High Register 4
    union  MFBALRY_REG        MFBALR4;        // Memory Fine Base Address Low Register 4
    union  MFBAHRX_REG        MFBAHR5;        // Memory Fine Base Address High Register 5
    union  MFBALRY_REG        MFBALR5;        // Memory Fine Base Address Low Register 5
    union  MFBAHRX_REG        MFBAHR6;        // Memory Fine Base Address High Register 6
    union  MFBALRY_REG        MFBALR6;        // Memory Fine Base Address Low Register 6
    union  MFBAHRX_REG        MFBAHR7;        // Memory Fine Base Address High Register 7
    union  MFBALRY_REG        MFBALR7;        // Memory Fine Base Address Low Register 7
    union  MFBAHRX_REG        MFBAHR8;        // Memory Fine Base Address High Register 8
    union  MFBALRY_REG        MFBALR8;        // Memory Fine Base Address Low Register 8
    union  MFBAHRX_REG        MFBAHR9;        // Memory Fine Base Address High Register 9
    union  MFBALRY_REG        MFBALR9;        // Memory Fine Base Address Low Register 9
    union  MFBAHRX_REG        MFBAHR10;       // Memory Fine Base Address High Register 10
    union  MFBALRY_REG        MFBALR10;       // Memory Fine Base Address Low Register 10
    union  MFBAHRX_REG        MFBAHR11;       // Memory Fine Base Address High Register 11
    union  MFBALRY_REG        MFBALR11;       // Memory Fine Base Address Low Register 11
    union  MFBAHRX_REG        MFBAHR12;       // Memory Fine Base Address High Register 12
    union  MFBALRY_REG        MFBALR12;       // Memory Fine Base Address Low Register 12
    union  MFBAHRX_REG        MFBAHR13;       // Memory Fine Base Address High Register 13
    union  MFBALRY_REG        MFBALR13;       // Memory Fine Base Address Low Register 13
    union  MFBAHRX_REG        MFBAHR14;       // Memory Fine Base Address High Register 14
    union  MFBALRY_REG        MFBALR14;       // Memory Fine Base Address Low Register 14
    union  MFBAHRX_REG        MFBAHR15;       // Memory Fine Base Address High Register 15
    union  MFBALRY_REG        MFBALR15;       // Memory Fine Base Address Low Register 15
    union  MFBAHRX_REG        MFBAHR16;       // Memory Fine Base Address High Register 16
    union  MFBALRY_REG        MFBALR16;       // Memory Fine Base Address Low Register 16
    union  MFBAHRX_REG        MFBAHR17;       // Memory Fine Base Address High Register 17
    union  MFBALRX_REG        MFBALR17;       // Memory Fine Base Address Low Register 17
    union  PFLASHCTRL_X_REG   PFLASHCTRL_0;   // Program Flash Control Register 0
    union  DFLASHCTRL_REG     DFLASHCTRL;     // Data Flash Control Register
    union  FLASHILOCK_REG     FLASHILOCK;     // Program Flash Interlock Register
    union  PFLASHCTRL_X_REG   PFLASHCTRL_1;   // Program Flash Control Register 1
  };
  
  //---------------------------------------------------------------------------
  // Address Manager Module External References & Function Declarations:
  //
  extern volatile struct DEC_REGS DecRegs;
  
//===========================================================================
#ifdef __cplusplus
}       // end of extern "C"
#endif

#endif  // end of CYCLONE_DEC_H definition

//===========================================================================
// End of file
//===========================================================================
