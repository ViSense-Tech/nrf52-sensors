//###############################################################################
//
// FILE:   cyclone_spi.h
//
// TITLE:  Cyclone SPI  Register Definitions.
//
// NOTES:
//  1) Bitfields have been defined for big-endian only.
//###############################################################################
//
//  Ver  | dd mmm yyyy | Who  | Description of changes
// ======|=============|======|==============================================
//  1.00 | 11 Jan 2012 | JPL  | Initial Revision
//       |             |      | 
//       |             |      |
//
//  Texas Instruments, Inc
//  Copyright Texas Instruments 2009. All rights reserved.
//###############################################################################

#ifndef CYCLONE_SPI_H
#define CYCLONE_SPI_H

#ifdef __cplusplus
extern "C" {
#endif

  //=============================================================================
  // SPI Individual Register Bit Definitions
  //=============================================================================

  //-----------------------------------------------------------------------------
  // Control Register 
  //-----------------------------------------------------------------------------
  struct SPICTRL_BITS {             // bits   description
    Uint32 rsvd0:8;                 // 31:24  Reserved
    Uint32 CLKRATE:3;               // 23:21  Clock rate 
    Uint32 FRMLEN:5;                // 20:16  Frame Length 
    Uint32 RXCNT:5;                 // 15:11  RX Cnt 
    Uint32 TXCNT:4;                 // 10:7   TX Cnt
    Uint32 WRSTORE:1;               // 6      Write Store Sel
    Uint32 WRSTART:1;               // 5      Write Start Sel
    Uint32 POL:1;                   // 4      Polarity
    Uint32 PHA:1;                   // 3      Phase
    Uint32 INTEN:1;                 // 2      Int En 
    Uint32 MODE:1;                  // 1      Mode  
    Uint32 SPIEN:1;                 // 0      SPI Enable
  }; 
  union SPICTRL_REG {
    Uint32                   all;
    struct SPICTRL_BITS     bit;
  };

  //-----------------------------------------------------------------------------
  // Status Register 
  //-----------------------------------------------------------------------------
  struct SPISTAT_BITS {             // bits  description
    Uint32 rsvd0:28;                // 31:8  Reserved
    Uint32 FRMCNT:1;                // 7:3   Frame Count 
    Uint32 WRCOL:1;                 // 2     Write Collision 
    Uint32 BUSY:1;                  // 1     SPI Busy 
    Uint32 SPIF:1;                  // 0     SPI Flag 
  }; 
  union SPISTAT_REG {
    Uint32                   all;
    struct SPISTAT_BITS     bit;
  };

  //-----------------------------------------------------------------------------
  // Pin Function Register 
  //-----------------------------------------------------------------------------
  struct SPIFUNC_BITS {             // bits  description
    Uint32 rsvd0:28;                // 31:4  Reserved
    Uint32 MISO:1;                  // 3     MISO Pin 
    Uint32 MOSI:1;                  // 2     MOSI Pin 
    Uint32 SCS:1;                   // 1     SCS Pin 
    Uint32 SCK:1;                   // 0     SCK 
  }; 
  union SPIFUNC_REG {
    Uint32                 all;
    struct SPIFUNC_BITS    bit;
  };

  //-----------------------------------------------------------------------------
  // Pin Direction Register 
  //-----------------------------------------------------------------------------
  struct SPIDIR_BITS {              // bits  description
    Uint32 rsvd0:28;                // 31:4  Reserved
    Uint32 MISO:1;                  // 3     MISO Pin 
    Uint32 MOSI:1;                  // 2     MOSI Pin 
    Uint32 SCS:1;                   // 1     SCS Pin 
    Uint32 SCK:1;                   // 0     SCK Pin 
  }; 
  union SPIDIR_REG {
    Uint32                 all;
    struct SPIDIR_BITS    bit;
  };

  //-----------------------------------------------------------------------------
  // Pin GPOUT Register 
  //-----------------------------------------------------------------------------
  struct SPIGPOUT_BITS {            // bits  description
    Uint32 rsvd0:28;                // 31:4  Reserved
    Uint32 MISO:1;                  // 3     MISO Pin 
    Uint32 MOSI:1;                  // 2     MOSI Pin 
    Uint32 SCS:1;                   // 1     SCS Pin 
    Uint32 SCK:1;                   // 0     SCK Pin 
  }; 
  union SPIGPOUT_REG {
    Uint32                 all;
    struct SPIGPOUT_BITS    bit;
  };

  //-----------------------------------------------------------------------------
  // Pin GPIN Register 
  //-----------------------------------------------------------------------------
  struct SPIGPIN_BITS {            // bits  description
    Uint32 rsvd0:28;                // 31:4  Reserved
    Uint32 MISO:1;                  // 3     MISO Pin 
    Uint32 MOSI:1;                  // 2     MOSI Pin 
    Uint32 SCS:1;                   // 1     SCS Pin 
    Uint32 SCK:1;                   // 0     SCK Pin 
  }; 
  union SPIGPIN_REG {
    Uint32                 all;
    struct SPIGPIN_BITS    bit;
  };


  //-----------------------------------------------------------------------------
  // TX Register 0
  //-----------------------------------------------------------------------------
  struct SPITX0_BITS {              // bits  description
    Uint32 DATA:32;                 // 31:0  Data  
  }; 
  union SPITX0_REG {
    Uint32                  all;
    struct SPITX0_BITS     bit;
  };

  //-----------------------------------------------------------------------------
  // TX Register10
  //-----------------------------------------------------------------------------
  struct SPITX1_BITS {              // bits  description
    Uint32 DATA:32;                 // 31:0  Data  
  }; 
  union SPITX1_REG {
    Uint32                  all;
    struct SPITX1_BITS     bit;
  };

  //-----------------------------------------------------------------------------
  // RX Register 0
  //-----------------------------------------------------------------------------
  struct SPIRX0_BITS {              // bits  description
    Uint32 DATA:32;                 // 31:0  Data  
  }; 
  union SPIRX0_REG {
    Uint32                  all;
    struct SPIRX0_BITS     bit;
  };

  //-----------------------------------------------------------------------------
  // RX Register 1
  //-----------------------------------------------------------------------------
  struct SPIRX1_BITS {              // bits  description
    Uint32 DATA:32;                 // 31:0  Data  
  }; 
  union SPIRX1_REG {
    Uint32                  all;
    struct SPIRX1_BITS     bit;
  };

  //-----------------------------------------------------------------------------
  // RX Register 2
  //-----------------------------------------------------------------------------
  struct SPIRX2_BITS {              // bits  description
    Uint32 DATA:32;                 // 31:0  Data  
  }; 
  union SPIRX2_REG {
    Uint32                  all;
    struct SPIRX2_BITS     bit;
  };

  //-----------------------------------------------------------------------------
  // RX Register 3
  //-----------------------------------------------------------------------------
  struct SPIRX3_BITS {              // bits  description
    Uint32 DATA:32;                 // 31:0  Data  
  }; 
  union SPIRX3_REG {
    Uint32                  all;
    struct SPIRX3_BITS     bit;
  };


  //=============================================================================
  // SPI Module Register File
  //=============================================================================
  struct SPI_REGS {
    union SPICTRL_REG       SPICTRL;
    union SPISTAT_REG       SPISTAT;
    union SPIFUNC_REG       SPIFUNC;        
    union SPIDIR_REG        SPIDIR;         
    union SPIGPOUT_REG      SPIGPOUT;       
    union SPIGPIN_REG       SPIGPIN;        
    union SPITX0_REG        SPITX0;        
    union SPITX1_REG        SPITX1;        
    union SPIRX0_REG        SPIRX0;        
    union SPIRX1_REG        SPIRX1;        
    union SPIRX2_REG        SPIRX2;        
    union SPIRX3_REG        SPIRX3;        
  };
  //-----------------------------------------------------------------------------
  // SPI Module External References & Function Declarations:
  //-----------------------------------------------------------------------------
  extern volatile struct SPI_REGS SPIRegs;


#ifdef __cplusplus
}       // end of extern "C"
#endif

#endif  // end of CYCLONE_SPI_CTRL_H definition

//===========================================================================
// End of file
//===========================================================================
