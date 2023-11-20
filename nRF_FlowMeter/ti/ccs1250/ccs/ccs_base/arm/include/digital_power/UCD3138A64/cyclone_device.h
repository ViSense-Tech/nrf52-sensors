//###########################################################################
//
// FILE:   Cyclone_Device.h
//
// TITLE:  Cyclone Device Definitions.
//
//###########################################################################
//
//  Ver  | dd mmm yyyy | Who  | Description of changes
// ======|=============|======|==============================================
//  1.00 | 12 Aug 2009 | CMF  | Started with Spartan_Device.h.
//       |             |      | Updated for 1.0 Memory map document.
//       |             |      |
//
//  Texas Instruments, Inc
//  Copyright Texas Instruments 2009. All rights reserved.
//###########################################################################

#ifndef CYCLONE_DEVICE_H
#define CYCLONE_DEVICE_H


#ifdef __cplusplus
extern "C" {
#endif

//===========================================================================
// For Portability, It Is Recommended To Use Following Data Type Definitions
//
#ifndef CYCLONE_DATA_TYPES
#define CYCLONE_DATA_TYPES
	typedef signed char          int8;
	typedef char                 Uint8;
	typedef short                int16;
	typedef unsigned short       Uint16;
	typedef int                  int32;
	typedef unsigned int         Uint32;
	typedef long long            int64;
	typedef unsigned long long   Uint64;

	typedef	Uint16	PM11;  	// PMBus literal format.  Top 5 bits are exponent, 
			      	// bottom 11 bits are signed integer
#endif

#include "cyclone_constants.h"

//===========================================================================
// Include All Peripheral Structure Definitions:
//
#include "cyclone_adc.h"         // ADC Registers
#include "cyclone_cim.h"         // CIM Registers
#include "cyclone_dec.h"         // DEC Registers
#include "cyclone_dpwm.h"        // DPWM Registers
#include "cyclone_fault_mux.h"   // Fault Mux Registers
#include "cyclone_fe_ctrl.h"     // Front End Control Registers
#include "cyclone_filter.h"      // FLTR Registers
#include "cyclone_gio.h"         // GIO Registers
#include "cyclone_rtc.h"         // RTC Registers
#include "cyclone_loop_mux.h"    // Loop Mux Registers
#include "cyclone_misc_analog.h" // Misc Analog Registers
#include "cyclone_mmc.h"         // MMC Registers
#include "cyclone_pmbus.h"       // PMBus Registers
#include "cyclone_sys.h"         // SYS Registers
#include "cyclone_spi.h"         // SPI Registers
#include "cyclone_timer.h"       // SYS Registers
#include "cyclone_uart.h"        // UART Registers

#include "cyclone_defines.h"     // Constant Definitions


//===========================================================================
#ifdef __cplusplus
}       // end of extern "C"
#endif

#endif  // end of CYCLONE_DEVICE_H definition


//===========================================================================
// End of file
//===========================================================================
