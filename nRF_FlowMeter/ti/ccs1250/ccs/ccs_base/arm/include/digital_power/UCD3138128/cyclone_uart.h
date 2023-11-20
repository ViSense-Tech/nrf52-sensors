//###############################################################################
//
// FILE:   cyclone_uart.h
//
// TITLE:  Cyclone Uart Register Definitions.
//
// NOTES:
//  1) Bitfields have been defined for big-endian only.
//###############################################################################
//
//  Ver  | dd mmm yyyy | Who  | Description of changes
// ======|=============|======|==============================================
//  1.00 | 19 Aug 2009 | CMF  | Started with Spartan_Uart.h.
//       |             |      | Updated for 1.0 Memory map document.
//       |             |      |
//
//  Texas Instruments, Inc
//  Copyright Texas Instruments 2009. All rights reserved.
//###############################################################################

#ifndef CYCLONE_UART_H
#define CYCLONE_UART_H

#ifdef __cplusplus
extern "C" {
#endif

  //=============================================================================
  // UART Individual Register Bit Definitions
  //=============================================================================

  //-----------------------------------------------------------------------------
  // UART Control Register 0 bit definitions
  //-----------------------------------------------------------------------------
  struct UARTCTRL0_BITS {          // bits   description
    Uint32 rsvd0:24;               // 31:8   reserved  
    Uint32 STOP:1;                 // 7      Prescaler for clock
    Uint32 PARITY:1;               // 6      Parity selection
    Uint32 PARITY_ENA:1;           // 5      Parity enable
    Uint32 SYNC_MODE:1;            // 4      Sync mode selection
    Uint32 ADDR_MODE:1;            // 3      Address mode selection
    Uint32 DATA_SIZE:3;            // 2:0    TX and RX data size
  };
  union UARTCTRL0_REG {
    Uint32                 all;
    struct UARTCTRL0_BITS  bit;
  };

  //-----------------------------------------------------------------------------
  // UART Receive Status Register bit definitions
  //-----------------------------------------------------------------------------
  struct UARTRXST_BITS {           // bits   description
    Uint32 rsvd0:27;               // 31:5   reserved
    Uint32 RX_IDLE:1;              // 4      RX idle status 
    Uint32 SLEEP:1;                // 3      Sleep
    Uint32 RX_RDY:1;               // 2      RX ready status
    Uint32 RX_WAKE:1;              // 1      RX wake status
    Uint32 RX_ENA:1;               // 0      RX enable
  };
  union UARTRXST_REG {
    Uint32                 all;
    struct UARTRXST_BITS   bit;
  };

  //-----------------------------------------------------------------------------
  // UART Transmit Status Register bit definitions
  //-----------------------------------------------------------------------------
  struct UARTTXST_BITS {           // bits   description
    Uint32 rsvd1:24;               // 31:8   reserved
    Uint32 CONTINUE:1;             // 7      Continue
    Uint32 LOOPBACK:1;             // 6      Loopback enable
    Uint32 rsvd0:2;                // 5:4    reserved
    Uint32 TX_EMPTY:1;             // 3      TX empty
    Uint32 TX_RDY:1;               // 2      TX ready status
    Uint32 TX_WAKE:1;              // 1      TX wake status
    Uint32 TX_ENA:1;               // 0      TX enable
  };
  union UARTTXST_REG {
    Uint32                 all;
    struct UARTTXST_BITS   bit;
  };

  //-----------------------------------------------------------------------------
  // UART Control Register 3 bit definitions
  //-----------------------------------------------------------------------------
  struct UARTCTRL3_BITS {          // bits   description
    Uint32 rsvd0:24;               // 31:8   reserved
    Uint32 SW_RESET:1;             // 7      Software reset
    Uint32 POWERDOWN:1;            // 6      Power down
    Uint32 CLOCK:1;                // 5      Clock select
    Uint32 RX_INT_ENA:1;           // 4      RX interrupt enable
    Uint32 TX_INT_ENA:1;           // 3      TX interrupt enable
    Uint32 WAKEUP_INT_ENA:1;       // 2      Wakeup interrupt enable
    Uint32 BRKDT_INT_ENA:1;        // 1      Break detect interrupt enable
    Uint32 ERR_INT_ENA:1;          // 0      RX error interrupt enable
  };
  union UARTCTRL3_REG {
    Uint32                 all;
    struct UARTCTRL3_BITS  bit;
  }; 

  //-----------------------------------------------------------------------------
  // UART Interrupt Status Register bit definitions
  //-----------------------------------------------------------------------------
  struct UARTINTST_BITS {          // bits   description
    Uint32 rsvd1:24;               // 31:8   reserved
    Uint32 BUS_BUSY:1;             // 7      RX bus busy flag
    Uint32 rsvd0:1;                // 6      reserved
    Uint32 FRAME_ERR:1;            // 5      RX framing error flag
    Uint32 OVERRUN_ERR:1;          // 4      RX overrun error flag
    Uint32 PARITY_ERR:1;           // 3      RX parity error flag
    Uint32 WAKEUP_INT:1;           // 2      Wakeup interrupt flag
    Uint32 BRKDT_INT:1;            // 1      Break detect interrupt flag
    Uint32 RX_ERR:1;               // 0      RX error flag
  };
  union UARTINTST_REG {
    Uint32                 all;
    struct UARTINTST_BITS  bit;
  }; 

  //-----------------------------------------------------------------------------
  // UART Baud Divisor High Byte Register bit definitions
  //-----------------------------------------------------------------------------
  struct UARTHBAUD_BITS {          // bits   description
    Uint32 rsvd0:24;               // 31:8   reserved
    Uint32 BAUD_DIV_H:8;           // 7:0    High byte of baud divisor
  };
  union UARTHBAUD_REG {
    Uint32                 all;
    struct UARTHBAUD_BITS  bit;
  };
  
  //-----------------------------------------------------------------------------
  // UART Baud Divisor Middle Byte Register bit definitions
  //-----------------------------------------------------------------------------
  struct UARTMBAUD_BITS {          // bits   description
    Uint32 rsvd0:24;               // 31:8   reserved
    Uint32 BAUD_DIV_M:8;           // 7:0    Middle byte of baud divisor
  };
  union UARTMBAUD_REG {
    Uint32                 all;
    struct UARTMBAUD_BITS  bit;
  };
  
  //-----------------------------------------------------------------------------
  // UART Baud Divisor Low Byte Register bit definitions
  //-----------------------------------------------------------------------------
  struct UARTLBAUD_BITS {          // bits   description
    Uint32 rsvd0:24;               // 31:8   reserved
    Uint32 BAUD_DIV_L:8;           // 7:0    Low byte of baud divisor
  };
  union UARTLBAUD_REG {
    Uint32                 all;
    struct UARTLBAUD_BITS  bit;
  };

  //-----------------------------------------------------------------------------
  // UART Receive Buffer bit definitions
  //-----------------------------------------------------------------------------
  struct UARTRXBUF_BITS {          // bits   description
    Uint32 rsvd0:24;               // 31:8   reserved
    Uint32 RXDAT:8;                // 7:0    Receive data
  };
  union UARTRXBUF_REG {
    Uint32                 all;
    struct UARTRXBUF_BITS  bit;
  };
  
  //-----------------------------------------------------------------------------
  // UART Transmit Buffer bit definitions
  //-----------------------------------------------------------------------------
  struct UARTTXBUF_BITS {          // bits   description
    Uint32 rsvd0:24;               // 31:8   reserved
    Uint32 TXDAT:8;                // 7:0    Transmit data
  };
  union UARTTXBUF_REG {
    Uint32                 all;
    struct UARTTXBUF_BITS  bit;
  };

  //-----------------------------------------------------------------------------
  // UART Pin Control Register 1 bit definitions
  //-----------------------------------------------------------------------------
  struct UARTIOCTRL_BITS {         // bits   description
    Uint32 rsvd0:28;               // 31:4   reserved
    Uint32 DATA_IN:1;              // 3      Input data from pin
    Uint32 DATA_OUT:1;             // 2      Output data to pin
    Uint32 IO_FUNC:1;              // 1      Pin function
    Uint32 IO_DIR:1;               // 0      Pin direction
  };
  union UARTIOCTRL_REG {
    Uint32                  all;
    struct UARTIOCTRL_BITS  bit;
  };
  
  //=============================================================================
  // UART Module Register File
  //=============================================================================
  struct  UART_REGS { 
    union  UARTCTRL0_REG  UARTCTRL0;       // UART Control Register 0
    union  UARTRXST_REG   UARTRXST;        // UART Receive Status Register
    union  UARTTXST_REG   UARTTXST;        // UART Transmit Status Register
    union  UARTCTRL3_REG  UARTCTRL3;       // UART Control Register 3
    union  UARTINTST_REG  UARTINTST;       // UART Interrupt Status Register
    union  UARTHBAUD_REG  UARTHBAUD;       // UART Baud Divisor High Byte Register
    union  UARTMBAUD_REG  UARTMBAUD;       // UART Baud Divisor Middle Byte Register
    union  UARTLBAUD_REG  UARTLBAUD;       // UART Baud Divisor Low Byte Register
    Uint32                RSVD[1];         // Reserved (address spacer)
    union  UARTRXBUF_REG  UARTRXBUF;       // UART Receive Buffer
    union  UARTTXBUF_REG  UARTTXBUF;       // UART Transmit Buffer
    union  UARTIOCTRL_REG UARTIOCTRLSCLK;  // UART SCLK Pin Control Register
    union  UARTIOCTRL_REG UARTIOCTRLRX;    // UART RX Pin Control Register
    union  UARTIOCTRL_REG UARTIOCTRLTX;    // UART TX Pin Control Register
  };
  
  
  //-----------------------------------------------------------------------------
  // UART Module External References & Function Declarations:
  //-----------------------------------------------------------------------------
  extern volatile struct UART_REGS Uart0Regs;
  extern volatile struct UART_REGS Uart1Regs;
  
  //=============================================================================
#ifdef __cplusplus
}       // end of extern "C"
#endif

#endif  // end of CYCLONE_UART_H definition

//===========================================================================
// End of file
//===========================================================================
