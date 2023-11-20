//###########################################################################
//
// FILE:   cyclone_defines.h
//
// TITLE:  Cyclone Constant Definitions.
//
// NOTES:
//  1) This file contains some convenient constant definitions for use with
//     the .byte and .half options of the peripheral register structures.
//
//###########################################################################
//
//  Ver  | dd mmm yyyy | Who  | Description of changes
// ======|=============|======|==============================================
//  1.00 | 14 Jun 2011 | F.W. | Added CIM, Global I/O defines
//
//  Texas Instruments, Inc
//  Copyright Texas Instruments 2011. All rights reserved.
//###########################################################################

#ifndef CYCLONE_DEFINES_H
#define CYCLONE_DEFINES_H

#ifdef __cplusplus
extern "C" {
#endif


//=========================================================================================
// CIM module definitions
//=========================================================================================
// FIRQPR, INTREQ, REQMASK Registers
// interrupts listed highest priority to lowest priority:
#define CIMINT_ALL_SYS_SOFT		(0x80000000)	// 31	System Software Interrupt					
#define CIMINT_ALL_FAULT_PIN	(0x40000000)	// 30	Fault Pin Interrupt		
#define CIMINT_ALL_DPWM0		(0x20000000)	// 29	Every(1-16)DPWM0 switching cycles or CLF flag shutdown Interrupt		
#define CIMINT_ALL_DPWM1		(0x10000000)	// 28	Every(1-16)DPWM1 switching cycles or CLF flag shutdown Interrupt			 						
#define CIMINT_ALL_DPWM2		(0x08000000)	// 27	Every(1-16)DPWM2 switching cycles or CLF flag shutdown Interrupt			 						
#define CIMINT_ALL_DPWM3		(0x04000000)	// 26	Every(1-16)DPWM3 switching cycles or CLF flag shutdown Interrupt		 						
#define CIMINT_ALL_FAULT_MUX	(0x02000000)	// 25	Fault Mux Interrupt			 				
#define CIMINT_ALL_ADC_CONV		(0x01000000)	// 24	ADC-12 End of Conversion Interrupt			 						
#define CIMINT_ALL_CPCC			(0x00800000)	// 23	CPCC Interrupt, Mode switched in CPCC module Flag needs to be read for details			 			
#define CIMINT_ALL_TMR_COMP0	(0x00400000)	// 22	24-bit Timer Compare 0 interrupt			 			
#define CIMINT_ALL_TMR_CAPT0	(0x00200000)	// 21	24-bit Timer Capture 0 interrupt									
#define CIMINT_ALL_TMR_COMP1	(0x00100000)	// 20	24-bit Timer Compare 1 interrupt		
#define CIMINT_ALL_TMR_CAPT1	(0x00080000)	// 19	24-bit Timer Capture 1 interrupt	
#define CIMINT_ALL_TMR_OVFL		(0x00040000)	// 18	24-bit Timer counter overflow interrupt							
#define CIMINT_ALL_PWM0_COMP	(0x00020000)	// 17	16-bit Timer PWM0 counter overflow or Compare interrupt			 					
#define CIMINT_ALL_PWM1_COMP	(0x00010000)	// 16	16-bit Timer PWM1 counter overflow or Compare interrupt			 					
#define CIMINT_ALL_PWM2_COMP	(0x00008000)	// 15	16-bit Timer PWM2 counter overflow or Compare interrupt			 					
#define CIMINT_ALL_PWM3_COMP	(0x00004000)	// 14	16-bit Timer PWM3 counter overflow or Compare interrupt			 					
#define CIMINT_ALL_FRONT_END2	(0x00002000)	// 13	Front End 2 Interrupt			 					
#define CIMINT_ALL_FRONT_END1	(0x00001000)	// 12	Front End 1 Interrupt			 					
#define CIMINT_ALL_FRONT_END0	(0x00000800)	// 11	Front End 0 Interrupt				
#define CIMINT_ALL_DIGI_COMP 	(0x00000400)	// 10	Digital comparator interrupt		
#define CIMINT_ALL_PMBUS		(0x00000200)	// 9	PMBus related interrupt			 				
#define CIMINT_ALL_UART2_TX		(0x00000100)	// 8	UART2 TX buffer empty			 						
#define CIMINT_ALL_UART2_RX		(0x00000080)	// 7	UART2 RX buffer has a byte			 				
#define CIMINT_ALL_UART1_TX		(0x00000040)	// 6	UART1 TX buffer empty			 		
#define CIMINT_ALL_UART1_RX		(0x00000020)	// 5	UART1 RX buffer has a byte 		
#define CIMINT_ALL_UART_ERR		(0x00000010)	// 4	UART or SCI error Interrupt. Frame, parity or Overrun			 	
#define CIMINT_ALL_WTDG_WAKE	(0x00000008)	// 3	Wakeup interrupt when watchdog equals half of set watch time			 	
#define CIMINT_ALL_WTDG_RSET	(0x00000004)	// 2	Interrupt from watchdog exceeded (reset)			 	
#define CIMINT_ALL_EXT_INT	    (0x00000002)	// 1	Interrupt on one or all external input pins			 					
#define CIMINT_ALL_BRWN_OUT		(0x00000001)	// 0	Brown Out Interrupt			 					


//=========================================================================================
// Global I/O definitions
//=========================================================================================
//Bit positions:
#define TMR_PWM2_GLBIO_BIT_POSITION              (31)
#define TMR_PWM3_GLBIO_BIT_POSITION              (30)
#define FAULT3_GLBIO_BIT_POSITION                (29)
#define ADC_EXT_TRIG_GLBIO_BIT_POSITION          (28)
#define TCK_GLBIO_BIT_POSITION                   (27)
#define TDO_GLBIO_BIT_POSITION                   (26)
#define TMS_GLBIO_BIT_POSITION                   (25)
#define TDI_GLBIO_BIT_POSITION                   (24)
#define SCI_TX1_GLBIO_BIT_POSITION               (23)
#define SCI_TX0_GLBIO_BIT_POSITION               (22)
#define SCI_RX1_GLBIO_BIT_POSITION               (21)
#define SCI_RX0_GLBIO_BIT_POSITION               (20)
#define TMR_CAP_GLBIO_BIT_POSITION               (19)
#define TMR_PWM1_GLBIO_BIT_POSITION              (18)
#define TMR_PWM0_GLBIO_BIT_POSITION              (17)
#define PMBUS_CLK_GLBIO_BIT_POSITION             (16)
#define PMBUS_DATA_GLBIO_BIT_POSITION            (15)
#define CONTROL_GLBIO_BIT_POSITION               (14)
#define ALERT_GLBIO_BIT_POSITION                 (13)
#define EXT_INT_GLBIO_BIT_POSITION               (12)
#define FAULT2_GLBIO_BIT_POSITION                (11)
#define FAULT1_GLBIO_BIT_POSITION                (10)
#define FAULT0_GLBIO_BIT_POSITION                 (9)
#define SYNC_GLBIO_BIT_POSITION                   (8)
#define DPWM3B_GLBIO_BIT_POSITION                 (7)
#define DPWM3A_GLBIO_BIT_POSITION                 (6)
#define DPWM2B_GLBIO_BIT_POSITION                 (5)
#define DPWM2A_GLBIO_BIT_POSITION                 (4)
#define DPWM1B_GLBIO_BIT_POSITION                 (3)
#define DPWM1A_GLBIO_BIT_POSITION                 (2)
#define DPWM0B_GLBIO_BIT_POSITION                 (1)
#define DPWM0A_GLBIO_BIT_POSITION                 (0)

//Bit masks:
#define TMR_PWM2_GLBIO_BIT_MASK               (1 << TMR_PWM2_GLBIO_BIT_POSITION)              
#define TMR_PWM3_GLBIO_BIT_MASK               (1 << TMR_PWM3_GLBIO_BIT_POSITION)              
#define FAULT3_GLBIO_BIT_MASK                 (1 << FAULT3_GLBIO_BIT_POSITION) 
#define ADC_EXT_TRIG_GLBIO_BIT_MASK           (1 << ADC_EXT_TRIG_GLBIO_BIT_POSITION)          
#define TCK_GLBIO_BIT_MASK                    (1 << TCK_GLBIO_BIT_POSITION)                   
#define TDO_GLBIO_BIT_MASK                    (1 << TDO_GLBIO_BIT_POSITION)                   
#define TMS_GLBIO_BIT_MASK                    (1 << TMS_GLBIO_BIT_POSITION)                   
#define TDI_GLBIO_BIT_MASK                    (1 << TDI_GLBIO_BIT_POSITION)                   
#define SCI_TX1_GLBIO_BIT_MASK                (1 << SCI_TX1_GLBIO_BIT_POSITION)               
#define SCI_TX0_GLBIO_BIT_MASK                (1 << SCI_TX0_GLBIO_BIT_POSITION)              
#define SCI_RX1_GLBIO_BIT_MASK                (1 << SCI_RX1_GLBIO_BIT_POSITION)               
#define SCI_RX0_GLBIO_BIT_MASK                (1 << SCI_RX0_GLBIO_BIT_POSITION)               
#define TMR_CAP_GLBIO_BIT_MASK                (1 << TMR_CAP_GLBIO_BIT_POSITION)               
#define TMR_PWM1_GLBIO_BIT_MASK               (1 << TMR_PWM1_GLBIO_BIT_POSITION)              
#define TMR_PWM0_GLBIO_BIT_MASK               (1 << TMR_PWM0_GLBIO_BIT_POSITION)              
#define PMBUS_CLK_GLBIO_BIT_MASK              (1 << PMBUS_CLK_GLBIO_BIT_POSITION)             
#define PMBUS_DATA_GLBIO_BIT_MASK             (1 << PMBUS_DATA_GLBIO_BIT_POSITION)            
#define CONTROL_GLBIO_BIT_MASK                (1 << CONTROL_GLBIO_BIT_POSITION)               
#define ALERT_GLBIO_BIT_MASK                  (1 << ALERT_GLBIO_BIT_POSITION)                 
#define EXT_INT_GLBIO_BIT_MASK                (1 << EXT_INT_GLBIO_BIT_POSITION)               
#define FAULT2_GLBIO_BIT_MASK                 (1 << FAULT2_GLBIO_BIT_POSITION)                
#define FAULT1_GLBIO_BIT_MASK                 (1 << FAULT1_GLBIO_BIT_POSITION)                
#define FAULT0_GLBIO_BIT_MASK                 (1 << FAULT0_GLBIO_BIT_POSITION)                
#define SYNC_GLBIO_BIT_MASK                   (1 << SYNC_GLBIO_BIT_POSITION)                   
#define DPWM3B_GLBIO_BIT_MASK                 (1 << DPWM3B_GLBIO_BIT_POSITION)                 
#define DPWM3A_GLBIO_BIT_MASK                 (1 << DPWM3A_GLBIO_BIT_POSITION)                 
#define DPWM2B_GLBIO_BIT_MASK                 (1 << DPWM2B_GLBIO_BIT_POSITION)                 
#define DPWM2A_GLBIO_BIT_MASK                 (1 << DPWM2A_GLBIO_BIT_POSITION)                 
#define DPWM1B_GLBIO_BIT_MASK                 (1 << DPWM1B_GLBIO_BIT_POSITION)                 
#define DPWM1A_GLBIO_BIT_MASK                 (1 << DPWM1A_GLBIO_BIT_POSITION)                 
#define DPWM0B_GLBIO_BIT_MASK                 (1 << DPWM0B_GLBIO_BIT_POSITION)                 
#define DPWM0A_GLBIO_BIT_MASK                 (1 << DPWM0A_GLBIO_BIT_POSITION)   

//=========================================================================================
#ifdef __cplusplus
}       // end of extern "C"
#endif

#endif  // end of CYCLONE_DEFINES_H definition

//=========================================================================================
// End of file
//=========================================================================================
