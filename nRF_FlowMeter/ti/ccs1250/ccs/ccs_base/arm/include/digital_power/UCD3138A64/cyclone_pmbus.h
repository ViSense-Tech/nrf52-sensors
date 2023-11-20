//###############################################################################
//
// FILE:   cyclone_pmbus.h
//
// TITLE:  Cyclone PMBus Interface Register Definitions.
//
// NOTES:
//  1) Bitfields have been defined for big-endian only.
//###############################################################################
//
//  Ver  | dd mmm yyyy | Who  | Description of changes
// ======|=============|======|==============================================
//  1.00 | 19 Aug 2008 | CMF  | Started with Spartan_Pmbus.h.
//       |             |      | Updated for 1.0 Memory map document.
//       |             |      |
//
//  Texas Instruments, Inc
//  Copyright Texas Instruments 2009. All rights reserved.
//###############################################################################

#ifndef CYCLONE_PMBUS_H
#define CYCLONE_PMBUS_H

#ifdef __cplusplus
extern "C" {
#endif

  //=============================================================================
  // PMBus Interface Individual Register Bit Definitions
  //=============================================================================

  //-----------------------------------------------------------------------------
  // PMBus Control Register 1 bit definitions
  //-----------------------------------------------------------------------------
  struct PMBCTRL1_BITS {            // bits   description
    Uint32 rsvd0:11;                // 31:21  reserved
    Uint32 PRC_CALL:1;              // 20     Process call message enable
    Uint32 GRP_CMD:1;               // 19     Group command message enable
    Uint32 PEC_ENA:1;               // 18     PEC byte enable
    Uint32 EXT_CMD:1;               // 17     Extended command enable
    Uint32 CMD_ENA:1;               // 16     Command word enable
    Uint32 BYTE_COUNT:8;            // 15:8   Byte count
    Uint32 SLAVE_ADDR:7;            // 7:1    Slave address
    Uint32 RW:1;                    // 0      Read/write indicator
  };
  union PMBCTRL1_REG {
    Uint32                   all;
    struct PMBCTRL1_BITS     bit;
  };
  
  //-----------------------------------------------------------------------------
  // PMBus Transmit Data Buffer bit definitions
  //
  // No bitfields are defined for PMBTXBUF because writing
  // to any of the four data bytes triggers the PMBus
  // transmission.  Therefore, we force the user to always
  // write to all four bytes at the same time.
  //-----------------------------------------------------------------------------
  struct PMBTXBUF_BITS {            // bits   description
    Uint32 ALL:32;                  // 31:0   All the bits
  };
  union PMBTXBUF_REG {
    Uint32                   all;
    struct PMBTXBUF_BITS     bit;
  };

  //-----------------------------------------------------------------------------
  // PMBus Receive Data Buffer bit definitions
  //-----------------------------------------------------------------------------
  struct PMBRXBUF_BITS {           // bits   description
    Uint32 BYTE3:8;                // 31:24  Byte3
    Uint32 BYTE2:8;                // 16:23  Byte2
    Uint32 BYTE1:8;                // 8:15   Byte1
    Uint32 BYTE0:8;                // 0:7    Byte0
  };
	struct PMBRXBUF_BYTES {              // bits   description
	   Uint8  BYTE3;                  // 31:24  reserved
	   Uint8  BYTE2;                  // 16:23  Byte #2
	   Uint8  BYTE1;                  // 8:15   Byte #1
	   Uint8  BYTE0;                  // 0:7    Byte #0
  };
  union PMBRXBUF_REG {
    Uint32                   all;
    struct PMBRXBUF_BITS     bit;
	struct PMBRXBUF_BYTES	byte;
  };
  
  //-----------------------------------------------------------------------------
  // PMBus Acknowledge Register bit definitions
  //-----------------------------------------------------------------------------
  struct PMBACK_BITS {             // bits   description
    Uint32 rsvd0:31;               // 31:1   reserved
    Uint32 ACK:1;                  // 0      Acknowledge enable
  };
  struct PMBACK_BYTES {              // bits   description
    Uint8  BYTE3;                  // 31:24  reserved
    Uint8  BYTE2;                  // 16:23  Byte #2
    Uint8  BYTE1;                  // 8:15   Byte #1
    Uint8  BYTE0;                  // 0:7    Byte #0
  };
  union PMBACK_REG {
    Uint32                all;
    struct PMBACK_BITS    bit;
	struct PMBACK_BYTES	byte;
  };
  
  //-----------------------------------------------------------------------------
  // PMBus Status Register bit definitions
  //-----------------------------------------------------------------------------
  struct PMBST_BITS {               // bits  Description
    Uint32 rsvd0:10;               // 31:22  reserved
    Uint32 SCL_RAW:1;              // 21     PMBus Clock Status
    Uint32 SDA_RAW:1;              // 20     PMBus Data Status
    Uint32 CONTROL_RAW:1;          // 19     Control Raw Status
    Uint32 ALERT_RAW:1;            // 18     Alert Raw Status
    Uint32 CONTROL_EDGE:1;         // 17     Control Signal Edge Detected
    Uint32 ALERT_EDGE:1;           // 16     Alert signal detected flag
    Uint32 MASTER:1;               // 15     Master/Slave mode flag
    Uint32 LOST_ARB:1;             // 14     Lost arbitration flag
    Uint32 BUS_FREE:1;             // 13     Bus free flag
    Uint32 UNIT_BUSY:1;            // 12     Unit busy flag
    Uint32 RPT_START:1;            // 11     Repeated start condition flag
    Uint32 SLAVE_ADDR_READY:1;     // 10     Slave address ready flag
    Uint32 CLK_HIGH_TIMEOUT:1;     // 9      Clock high timeout flag
    Uint32 CLK_LOW_TIMEOUT:1;      // 8      Clock low timeout flag
    Uint32 PEC_VALID:1;            // 7      PEC valid flag
    Uint32 NACK:1;                 // 6      NACK condition received flag
    Uint32 EOM:1;                  // 5      End of message flag
    Uint32 DATA_REQUEST:1;         // 4      Data request flag
    Uint32 DATA_READY:1;           // 3      Data ready flag
    Uint32 RD_BYTE_COUNT:3;        // 2:0    Read byte count
  };

struct PMBST_BYTES {              // bits   description
   Uint8  rsvd3;                  // 31:24  reserved
   Uint8  BYTE2;                  // 16:23  Byte #2
   Uint8  BYTE1;                  // 8:15   Byte #1
   Uint8  BYTE0;                  // 0:7    Byte #0
};

struct PMBST_HALFS {              // bits   description
   Uint16 HALF1;                  // 31:16  Half #1
   Uint16 HALF0;                  // 15:0   Half #0
};

// Allow access to the bit fields or entire register
union PMBST_REG {
   Uint32                 all;
   struct PMBST_BITS      bit;
   struct PMBST_BYTES     byte;
   struct PMBST_HALFS     half;
};
  //-----------------------------------------------------------------------------
  // PMBus Interrupt Mask Register bit definitions
  //-----------------------------------------------------------------------------
  struct PMBINTM_BITS {             // bits   description
    Uint32 rsvd0:22;                // 31:10  reserved
    Uint32 CLK_HIGH_TIMEOUT:1;      // 9      Clock High Detection Interrupt mask
    Uint32 LOST_ARB:1;              // 8      Lost arbitration interrupt mask
    Uint32 CONTROL:1;               // 7      Remote module control asserted interrupt mask
    Uint32 ALERT:1;                 // 6      Alert signal detected interrupt mask
    Uint32 EOM:1;                   // 5      End of message interrupt mask
    Uint32 SLAVE_ADDR_READY:1;      // 4      Slave address ready interrupt mask
    Uint32 DATA_REQUEST:1;          // 3      Data request interrupt mask
    Uint32 DATA_READY:1;            // 2      Data ready interrupt mask
    Uint32 BUS_LOW_TIMEOUT:1;       // 1      Bus low timeout interrupt mask
    Uint32 BUS_FREE:1;              // 0      Bus free interrupt mask
  };
  union PMBINTM_REG {
    Uint32                  all;
    struct PMBINTM_BITS     bit;
  };

  //-----------------------------------------------------------------------------
  // PMBus Control Register 2 bit definitions
  //-----------------------------------------------------------------------------
  struct PMBCTRL2_BITS {           // bits   description
    Uint32 rsvd0:1;                // 31     reserved
    Uint32 SLAVE_ADDR_2_EN:1;      // 30     Slave address 2 enable
    Uint32 SLAVE_ADDR_2:7;         // 29:23  Slave address 2 value
    Uint32 RX_BYTE_ACK_CNT:2;      // 22:21  Num bytes to auto acknowledge in slave mode.
    Uint32 MAN_CMD:1;              // 20     Manual command acknowledge mode
    Uint32 TX_PEC:1;               // 19     Transmited PEC flag
    Uint32 TX_COUNT:3;             // 18:16  Transmit byte count
    Uint32 PEC_ENA:1;              // 15     Enable PEC processing
    Uint32 SLAVE_MASK:7;           // 14:8   Slave mask
    Uint32 MAN_SLAVE_ACK:1;        // 7      Manual slave acknowledge mode enable
    Uint32 SLAVE_ADDR:7;           // 6:0    Slave address
  };

  struct PMBCTRL2_BYTES {           // bits   description
   Uint8  rsvd3;                  // 31:24  reserved
   Uint8  BYTE2;                  // 16:23  Byte #2
   Uint8  BYTE1;                  // 8:15   Byte #1
   Uint8  BYTE0;                  // 0:7    Byte #0
};

struct PMBCTRL2_HALFS {           // bits   description
   Uint16 HALF1;                  // 31:16  Half #1
   Uint16 HALF0;                  // 15:0   Half #0
};

// Allow access to the bit fields or entire register
union PMBCTRL2_REG {
   Uint32                   all;
   struct PMBCTRL2_BITS     bit;
   struct PMBCTRL2_BYTES    byte;
   struct PMBCTRL2_HALFS    half;
};
  
  //-----------------------------------------------------------------------------
  // PMBus Hold Slave Address Register bit definitions
  //-----------------------------------------------------------------------------
  struct PMBHSA_BITS {             // bits   description
    Uint32 rsvd0:24;               // 31:8   reserved
    Uint32 SLAVE_ADDR:7;           // 7:1    Stored address acknowledged by slave
    Uint32 SLAVE_RW:1;             // 0      Stored R/W bit from slave acknowledge
  };
  union PMBHSA_REG {
    Uint32                 all;
    struct PMBHSA_BITS     bit;
  };
  
  //-----------------------------------------------------------------------------
  // PMBus Miscellaneous Control Register bit definitions
  //-----------------------------------------------------------------------------
  struct PMBCTRL3_BITS {           // bits   description
    Uint32 rsvd0:7;                // 31:25  reserved
    Uint32 I2C_MODE_EN:1;          // 24     I2C Mode Enable 
    Uint32 CLK_HI_DIS:1;           // 23     Clock High Timeout Disable 
    Uint32 MASTER_EN:1;            // 22     Master Mode Enable
    Uint32 SLAVE_EN:1;             // 21     Slave Mode Enable
    Uint32 CLK_LO_DIS:1;           // 20     Clock Low Timeout Disable
    Uint32 IBIAS_B_EN:1;           // 19     IBias B enable
    Uint32 IBIAS_A_EN:1;           // 18     IBias A enable
    Uint32 SCL_DIR:1;              // 17     Clock Pin GPIO Direction
    Uint32 SCL_VALUE:1;            // 16     Clock Pin GPIO Value
    Uint32 SCL_MODE:1;             // 15     Clock Pin GPIO Mode
    Uint32 SDA_DIR:1;              // 14     Clock Pin GPIO Direction
    Uint32 SDA_VALUE:1;            // 13     Clock Pin GPIO Value
    Uint32 SDA_MODE:1;             // 12     Clock Pin GPIO Mode
    Uint32 CNTL_DIR:1;             // 11     Direction of control pins in GPIO mode
    Uint32 CNTL_VALUE:1;           // 10     Output value of control pins in GPIO mode
    Uint32 CNTL_MODE:1;            // 9      Configures mode of control pins
    Uint32 ALERT_DIR:1;            // 8      Alert Pin GPIO Direction
    Uint32 ALERT_VALUE:1;          // 7      Value of Alert pin in GPIO mode
    Uint32 ALERT_MODE:1;           // 6      Configures mode of Alert pin
    Uint32 CNTL_INT_EDGE:1;        // 5      Control interrupt edge select
    Uint32 rsvd1:1;                // 4      reserved
    Uint32 FAST_MODE:1;            // 3      Fast mode enable
    Uint32 BUS_LO_INT_EDGE:1;      // 2      Bus low timeout interrupt edge select
    Uint32 ALERT_EN:1;             // 1      Alert enable
    Uint32 RESET:1;                // 0      PMBus Master reset
  };
  union PMBCTRL3_REG {
    Uint32                 all;
    struct PMBCTRL3_BITS   bit;
  };
  
  //=============================================================================
  // PMBus Interface Register File
  //=============================================================================
  struct PMBUS_REGS {
    union  PMBCTRL1_REG   PMBCTRL1;    // PMBus Control Register 1
    union  PMBTXBUF_REG   PMBTXBUF;    // PMBus Transmit Data Buffer
    union  PMBRXBUF_REG   PMBRXBUF;    // PMBus Receive Data Buffer
    union  PMBACK_REG     PMBACK;      // PMBus Acknowledge Register
    union  PMBST_REG      PMBST;       // PMBus Status Register
    union  PMBINTM_REG    PMBINTM;     // PMBus Interrupt Mask Register
    union  PMBCTRL2_REG   PMBCTRL2;    // PMBus Control Register 2
    union  PMBHSA_REG     PMBHSA;      // PMBus Hold Slave Address Register
    union  PMBCTRL3_REG   PMBCTRL3;    // PMBus Control Register 3
  };
  
  //---------------------------------------------------------------------------
  // PMBus Interface External References & Function Declarations:
  //
  extern volatile struct PMBUS_REGS PMBusRegs;
  extern volatile struct PMBUS_REGS PMBus1Regs;
  
  //===========================================================================
#ifdef __cplusplus
}       // end of extern "C"
#endif

#endif  // end of CYCLONE_PMBUS_H definition

//===========================================================================
// End of file
//===========================================================================
