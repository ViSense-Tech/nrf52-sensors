//###############################################################################
//
// FILE:   cyclone_rtc.h
//
// TITLE:  Cyclone RTC Register Definitions.
//
// NOTES:
//  1) Bitfields have been defined for big-endian only.
//###############################################################################
//
//  Ver  | dd mmm yyyy | Who  | Description of changes
// ======|=============|======|==============================================
//       |             |      |
//
//  Texas Instruments, Inc
//  Copyright Texas Instruments 2009. All rights reserved.
//###############################################################################

#ifndef CYCLONE_RTC_H
#define CYCLONE_RTC_H

#ifdef __cplusplus
extern "C" {
#endif

  //=============================================================================
  // RTC Interface Individual Register Bit Definitions
  //=============================================================================

  //-----------------------------------------------------------------------------
  // RTC Control Register bit definitions
  //-----------------------------------------------------------------------------
  struct RTCCTRL_BITS {             // bits   description
    Uint32 rsvd1:22;                // 31:10  reserved
    Uint32 TESTMODE:1;              // 9      Testmode 
    Uint32 CONFIG_CL:5;             // 8:4    Analog config cl
    Uint32 CONFIG_INCL:2;           // 3:2    Analog config incl 
    Uint32 rsvd0:1;                 // 1      reserved
    Uint32 PRESET_EN:1;             // 0      Preset enable 
  };
  union RTCCTRL_REG {
    Uint32                   all;
    struct RTCCTRL_BITS     bit;
  };
  
  //-----------------------------------------------------------------------------
  // RTC Counter Register bit definitions
  //-----------------------------------------------------------------------------
  struct RTCCOUNT_BITS {            // bits   description
    Uint32 rsvd0:4;                 // 31:28  reserved
    Uint32 DAYS:11;                 // 27:17  Count days
    Uint32 HOURS:5;                 // 16:12  Count hours 
    Uint32 MINS:6;                  // 11:6   Count minutes 
    Uint32 SECS:6;                  // 0:5    Count seconds 
  };
  union RTCCOUNT_REG {
    Uint32                   all;
    struct RTCCOUNT_BITS     bit;
  };

  //-----------------------------------------------------------------------------
  // RTC Preset Register bit definitions
  //-----------------------------------------------------------------------------
  struct RTCPRESET_BITS {            // bits   description
    Uint32 rsvd0:4;                  // 31:28  reserved
    Uint32 DAYS:11;                  // 27:17  Preset days
    Uint32 HOURS:5;                  // 16:12  Preset hours 
    Uint32 MINS:6;                   // 11:6   Preset minutes 
    Uint32 SECS:6;                   // 0:5    Preset seconds 
  };
  union RTCPRESET_REG {
    Uint32                   all;
    struct RTCPRESET_BITS     bit;
  };

  //-----------------------------------------------------------------------------
  // RTC Interrupt Enable Register bit definitions
  //-----------------------------------------------------------------------------
  struct RTCINTEN_BITS {            // bits   description
    Uint32 rsvd0:28;                // 31:4   reserved
    Uint32 SEC60:1;                 // 3      60sec interrupt en
    Uint32 SEC30:1;                 // 2      30sec interrupt en
    Uint32 SEC10:1;                 // 1      10sec interrupt en
    Uint32 SEC:1;                   // 0      1sec interrupt en 
  };
  union RTCINTEN_REG {
    Uint32                   all;
    struct RTCINTEN_BITS     bit;
  };

  //-----------------------------------------------------------------------------
  // RTC Interrupt Status Register bit definitions
  //-----------------------------------------------------------------------------
  struct RTCINTSTAT_BITS {          // bits   description
    Uint32 rsvd0:28;                // 31:4   reserved
    Uint32 SEC60:1;                 // 3      60sec interrupt en
    Uint32 SEC30:1;                 // 2      30sec interrupt en
    Uint32 SEC10:1;                 // 1      10sec interrupt en
    Uint32 SEC:1;                   // 0      1sec interrupt en 
  };
  union RTCINTSTAT_REG {
    Uint32                   all;
    struct RTCINTSTAT_BITS     bit;
  };

  //-----------------------------------------------------------------------------
  // RTC Prescale Register bit definitions
  //-----------------------------------------------------------------------------
  struct RTCPRESCALE_BITS {         // bits   description
    Uint32 rsvd0:22;                // 31:11  reserved
    Uint32 PRESCALE:10;             // 0      Prescaler value 
  };
  union RTCPRESCALE_REG {
    Uint32                   all;
    struct RTCPRESCALE_BITS     bit;
  };
  
  //=============================================================================
  // RTC Interface Register File
  //=============================================================================
  struct RTC_REGS {
    union  RTCCTRL_REG     RTCCTRL;     // RTC Control Register
    union  RTCCOUNT_REG    RTCCOUNT;    // RTC Count Register
    union  RTCPRESET_REG   RTCPRESET;   // RTC Count Preset Register
    union  RTCINTEN_REG    RTCINTEN;    // RTC Interrupt Enable Register
    union  RTCINTSTAT_REG  RTCINTSTAT;  // RTC Interrupt Status Register
    union  RTCPRESCALE_REG RTCPRESCALE; // RTC Prescale Register
  };
  
  //---------------------------------------------------------------------------
  // RTC Interface External References & Function Declarations:
  //
  extern volatile struct RTC_REGS RTCRegs;
  
  //===========================================================================
#ifdef __cplusplus
}       // end of extern "C"
#endif

#endif  // end of CYCLONE_RTC_H definition

//===========================================================================
// End of file
//===========================================================================
