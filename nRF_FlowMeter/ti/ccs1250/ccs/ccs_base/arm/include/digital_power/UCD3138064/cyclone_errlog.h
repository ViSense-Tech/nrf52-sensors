//###########################################################################
//
// FILE:   cyclone_errlog.h
//
// TITLE:  Cyclone Errlog Register Definitions.
//
// NOTES:
//  1) Bitfields have been defined for big-endian only.
//###########################################################################
//
//  Ver  | dd mmm yyyy | Who  | Description of changes
// ======|=============|======|==============================================
//  1.00 | 18 Aug 2009 | CMF  | Updated for 1.0 Memory map document.
//       |             |      |
//
//  Texas Instruments, Inc
//  Copyright Texas Instruments 2009. All rights reserved.
//###########################################################################

#ifndef CYCLONE_ERRLOG_H
#define CYCLONE_ERRLOG_H

#ifdef __cplusplus
extern "C" {
#endif

//===========================================================================
// Errlog Individual Register Bit Definitions
//

//-------------------------------------------------
// Memory Fine Base Address High Register 0 bit definitions
//
struct ERRLOG_BITS {            // bits   description
  Uint32 ERRLOG_BUSY:1;         // 31     Errlog Busy Bit
  Uint32 ERRLOG_STATUS:31;      // 30:0   Errlog Status Bits
};
union ERRLOG_REG {
   Uint32                all;
   struct ERRLOG_BITS    bit;
};

//===========================================================================
// Address Manager Module Register File
//
struct ERRLOG_REGS {
   union  ERRLOG_REG        ERRLOG;        // Memory Fine Base Address High Register 0
};

//---------------------------------------------------------------------------
// Address Manager Module External References & Function Declarations:
//
extern volatile struct ERRLOG_REGS ErrlogRegs;

//===========================================================================
#ifdef __cplusplus
}       // end of extern "C"
#endif

#endif  // end of CYCLONE_ERRLOG_H definition

//===========================================================================
// End of file
//===========================================================================
