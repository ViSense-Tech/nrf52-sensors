//###########################################################################
//
// FILE:   cyclone_mmc.h
//
// TITLE:  Cyclone Memory Controller Module Register Definitions.
//
// NOTES:
//  1) Bitfields have been defined for big-endian only.
//###########################################################################
//
//  Ver  | dd mmm yyyy | Who  | Description of changes
// ======|=============|======|==============================================
//  1.00 | 12 Aug 2009 | CMF  | Started with Spartan_Mmc.h.
//       |             |      | Updated for 1.0 Memory map document.
//       |             |      |
//
//  Texas Instruments, Inc
//  Copyright Texas Instruments 2008. All rights reserved.
//###########################################################################

#ifndef CYCLONE_MMC_H
#define CYCLONE_MMC_H

#ifdef __cplusplus
extern "C" {
#endif

//===========================================================================
// Memory Controller Module Individual Register Bit Definitions
//

//-------------------------------------------------
// Static Memory Control Register bit definitions
//
struct SMCTRL_BITS {              // bits   description
   Uint32 rsvd2:18;               // 31:14  reserved
   Uint32 LEAD:2;                 // 13:12  Address setup time cycles (write)
   Uint32 TRAIL:3;                // 11:9   Trailing wait states (read/write)
   Uint32 rsvd1:1;                // 8      reserved
   Uint32 ACTIVE:4;               // 7:4    Wait states (read/write)
   Uint32 ENDIAN:1;               // 3      Endian mode
   Uint32 rsvd0:1;                // 2      reserved
   Uint32 WIDTH:2;                // 1:0    Data width
};
union SMCTRL_REG {
   Uint32                 all;
   struct SMCTRL_BITS     bit;
};

//-------------------------------------------------
// Write Control Register bit definitions
//
struct WCTRL_BITS {               // bits   description
   Uint32 rsvd0:30;               // 31:2   reserved
   Uint32 TRAIL_OVR:1;            // 1      Write trailing wait state override
   Uint32 WBUF_ENA:1;             // 0      Write buffer enable
};
union WCTRL_REG {
   Uint32              all;
   struct WCTRL_BITS   bit;
};

//-------------------------------------------------
// Peripheral Control Register bit definitions
//
struct PCTRL_BITS {               // bits   description
   Uint32 rsvd0:31;               // 31:1   reserved
   Uint32 PBUF_ENA:1;             // 0      Peripheral enable
};
union PCTRL_REG {
   Uint32                all;
   struct PCTRL_BITS     bit;
};

//-------------------------------------------------
// Peripheral Location Register bit definitions
//
struct PLOC_BITS {                // bits   description
   Uint32 rsvd0:16;               // 31:16  reserved
   Uint32 LOC15:1;                // 15     Peripheral 15 location
   Uint32 LOC14:1;                // 14     Peripheral 14 location
   Uint32 LOC13:1;                // 13     Peripheral 13 location
   Uint32 LOC12:1;                // 12     Peripheral 12 location
   Uint32 LOC11:1;                // 11     Peripheral 11 location
   Uint32 LOC10:1;                // 10     Peripheral 10 location
   Uint32 LOC9:1;                 // 9      Peripheral 9 location
   Uint32 LOC8:1;                 // 8      Peripheral 8 location
   Uint32 LOC7:1;                 // 7      Peripheral 7 location
   Uint32 LOC6:1;                 // 6      Peripheral 6 location
   Uint32 LOC5:1;                 // 5      Peripheral 5 location
   Uint32 LOC4:1;                 // 4      Peripheral 4 location
   Uint32 LOC3:1;                 // 3      Peripheral 3 location
   Uint32 LOC2:1;                 // 2      Peripheral 2 location
   Uint32 LOC1:1;                 // 1      Peripheral 1 location
   Uint32 LOC0:1;                 // 0      Peripheral 0 location
};
union PLOC_REG {
   Uint32                all;
   struct PLOC_BITS      bit;
};

//-------------------------------------------------
// Peripheral Protection Register bit definitions
//
struct PPROT_BITS {               // bits   description
   Uint32 rsvd0:16;               // 31:16  reserved
   Uint32 PROT15:1;               // 15     Peripheral 15 protection
   Uint32 PROT14:1;               // 14     Peripheral 14 protection
   Uint32 PROT13:1;               // 13     Peripheral 13 protection
   Uint32 PROT12:1;               // 12     Peripheral 12 protection
   Uint32 PROT11:1;               // 11     Peripheral 11 protection
   Uint32 PROT10:1;               // 10     Peripheral 10 protection
   Uint32 PROT9:1;                // 9      Peripheral 9 protection
   Uint32 PROT8:1;                // 8      Peripheral 8 protection
   Uint32 PROT7:1;                // 7      Peripheral 7 protection
   Uint32 PROT6:1;                // 6      Peripheral 6 protection
   Uint32 PROT5:1;                // 5      Peripheral 5 protection
   Uint32 PROT4:1;                // 4      Peripheral 4 protection
   Uint32 PROT3:1;                // 3      Peripheral 3 protection
   Uint32 PROT2:1;                // 2      Peripheral 2 protection
   Uint32 PROT1:1;                // 1      Peripheral 1 protection
   Uint32 PROT0:1;                // 0      Peripheral 0 protection
};
union PPROT_REG {
   Uint32               all;
   struct PPROT_BITS    bit;
};

//===========================================================================
// Memory Controller Module Register File
//
struct MMC_REGS {
   union  SMCTRL_REG     SMCTRL;      // Static Memory Control Register
   Uint32                RSVD[0xA];   // Reserved (address spacer)
   union  WCTRL_REG      WCTRL;       // Write Control Register
   union  PCTRL_REG      PCTRL;       // Peripheral Control Register
   union  PLOC_REG       PLOC;        // Peripheral Location Register
   union  PPROT_REG      PPROT;       // Peripheral Protection Register
};

//---------------------------------------------------------------------------
// Memory Controller Module External References & Function Declarations:
//
extern volatile struct MMC_REGS MmcRegs;

//===========================================================================
#ifdef __cplusplus
}       // end of extern "C"
#endif

#endif  // end of CYCLONE_MMC_H definition

//===========================================================================
// End of file
//===========================================================================
