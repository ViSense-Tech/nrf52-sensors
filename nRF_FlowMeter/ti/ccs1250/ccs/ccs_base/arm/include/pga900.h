/* ============================================================================ */
/* Copyright (c) 2017, Texas Instruments Incorporated                           */
/*  All rights reserved.                                                        */
/*                                                                              */
/*  Redistribution and use in source and binary forms, with or without          */
/*  modification, are permitted provided that the following conditions          */
/*  are met:                                                                    */
/*                                                                              */
/*  *  Redistributions of source code must retain the above copyright           */
/*     notice, this list of conditions and the following disclaimer.            */
/*                                                                              */
/*  *  Redistributions in binary form must reproduce the above copyright        */
/*     notice, this list of conditions and the following disclaimer in the      */
/*     documentation and/or other materials provided with the distribution.     */
/*                                                                              */
/*  *  Neither the name of Texas Instruments Incorporated nor the names of      */
/*     its contributors may be used to endorse or promote products derived      */
/*     from this software without specific prior written permission.            */
/*                                                                              */
/*  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" */
/*  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,       */
/*  THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR      */
/*  PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR            */
/*  CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,       */
/*  EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,         */
/*  PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; */
/*  OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,    */
/*  WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR     */
/*  OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,              */
/*  EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.                          */
/* ============================================================================ */
/********************************************************************
*
* This File contains PGA900 Register Definitions
*
* Rev. 1.0, Initial Release for CCS
*
********************************************************************/

#ifndef PGA900_TYPES_H
#define PGA900_TYPES_H

#ifdef __cplusplus
extern "C" {
#endif

typedef volatile signed char    VSC;
typedef volatile unsigned char  VUC;
typedef volatile signed short   VS2;
typedef volatile unsigned short VUS;
typedef volatile signed long    VSL;
typedef volatile unsigned long  VUL;
typedef volatile signed int     VSI;
typedef volatile unsigned int   VUI;
typedef volatile float          VFLOAT;

typedef signed char             SC;
typedef unsigned char           UC;
typedef signed short            S2;
typedef unsigned short          US;
typedef signed long             SL;
typedef unsigned long           UL;
typedef signed int              SI;
typedef unsigned int            UI;
typedef float                   FLOAT;

#ifdef __cplusplus
}
#endif

#endif /* PGA900_TYPES_H */

#ifndef PGA900_H
#define PGA900_H

#ifdef __cplusplus
extern "C" {
#endif

#define RAMBIST_CONTROL            (*((VUC *)0x40000502))
#define RAMBIST_STATUS             (*((VUC *)0x40000503))
#define CLK_CTRL_STATUS            (*((VUC *)0x40000504))
#define DIG_IF_CTRL                (*((VUC *)0x40000506))
#define OWI_ERROR_STATUS_LO        (*((VUC *)0x40000508))
#define OWI_ERROR_STATUS_HI        (*((VUC *)0x40000509))
#define OWI_ERROR_STATUS           (*((VUS *)0x40000508))
#define OWI_INTERRUPT              (*((VUC *)0x4000050A))
#define OWI_INTERRUPT_ENABLE       (*((VUC *)0x4000050B))
#define OTP_PROG_DATA1             (*((VUC *)0x40000510))
#define OTP_PROG_DATA2             (*((VUC *)0x40000511))
#define OTP_PROG_DATA3             (*((VUC *)0x40000512))
#define OTP_PROG_DATA4             (*((VUC *)0x40000513))
#define OTP_PROG_DATA              (*((VUL *)0x40000510))
#define OTP_PROG_ADDR1             (*((VUC *)0x40000514))
#define OTP_PROG_ADDR2             (*((VUC *)0x40000515))
#define OTP_PROG_ADDR              (*((VUS *)0x40000514))
#define OTP_PROG_CTRL_STAT         (*((VUC *)0x40000516))
#define OTP_PAGE_ADDR              (*((VUC *)0x40000518))
#define DATARAM_PAGE_ADDR          (*((VUC *)0x40000519))
#define DEVRAM_PAGE_ADDR           (*((VUC *)0x4000051A))
#define WDOG_CTRL_STAT             (*((VUC *)0x4000051C))
#define WDOG_TRIG                  (*((VUC *)0x4000051D))
#define PIN_MUX                    (*((VUC *)0x4000051E))
#define PADC_DATA1                 (*((VUC *)0x40000520))
#define PADC_DATA2                 (*((VUC *)0x40000521))
#define PADC_DATA3                 (*((VUC *)0x40000522))
#define PADC_DATA                  (*((VS2 *)0x40000520))
#define PADC_DATA_24BIT            (*((VSL *)0x40000520))
#define PADC_CONFIG                (*((VUC *)0x40000523))
#define TADC_DATA1                 (*((VUC *)0x40000524))
#define TADC_DATA2                 (*((VUC *)0x40000525))
#define TADC_DATA3                 (*((VUC *)0x40000526))
#define TADC_DATA                  (*((VS2 *)0x40000524))
#define TADC_DATA_24BIT            (*((VSL *)0x40000524))
#define TADC_CONFIG                (*((VUC *)0x40000527))
#define ADC_CFG_1                  (*((VUC *)0x40000529))
#define DAC_REG0_1                 (*((VUC *)0x40000530))
#define DAC_REG0_2                 (*((VUC *)0x40000531))
#define DAC_REG0                   (*((VUS *)0x40000530))
#define DAC_REG1_1                 (*((VUC *)0x40000532))
#define DAC_REG1_2                 (*((VUC *)0x40000533))
#define DAC_REG1                   (*((VUS *)0x40000532))
#define DAC_CTRL_STATUS            (*((VUC *)0x40000538))
#define DAC_CONFIG                 (*((VUC *)0x40000539))
#define DAC_LPBK_CTRL              (*((VUC *)0x4000053A))
#define OP_STAGE_CTRL              (*((VUC *)0x4000053B))
#define AFE_CFG                    (*((VUC *)0x400004F4))
#define AFEDIAG_CFG                (*((VUC *)0x40000545))
#define BRDG_CTRL                  (*((VUC *)0x40000546))
#define P_GAIN_SELECT              (*((VUC *)0x40000547))
#define T_GAIN_SELECT              (*((VUC *)0x40000548))
#define TEMP_CTRL                  (*((VUC *)0x4000054C))
#define ALPWR                      (*((VUC *)0x40000550))
#define DLPWR                      (*((VUC *)0x40000554))
#define PSMON1                     (*((VUC *)0x40000558))
#define PSMON2                     (*((VUC *)0x40000559))
#define PSMON                      (*((VUS *)0x40000558))
#define AFEDIAG                    (*((VUC *)0x4000055A))
#define TOPDIG_MUX_SEL             (*((VUC *)0x40000560))
#define TONDIG_MUX_SEL             (*((VUC *)0x40000561))
#define AMUX_ACT                   (*((VUC *)0x40000564))
#define AMUX_TIN_MUX_CTRL          (*((VUC *)0x40000565))
#define AMUX_TOUT_MUX_CTRL         (*((VUC *)0x40000566))
#define AMUX_CTRL                  (*((VUC *)0x40000567))
#define TRACE_FIFO_CTRL_STAT       (*((VUC *)0x40000570))
#define REVISION_ID1               (*((VUC *)0x40000400))
#define REVISION_ID2               (*((VUC *)0x40000401))
#define REVISION_ID                (*((VUS *)0x40000400))
#define COM_MCU_TO_DIF_B1          (*((VUC *)0x40000404))
#define COM_MCU_TO_DIF_B2          (*((VUC *)0x40000405))
#define COM_MCU_TO_DIF_B           (*((VUS *)0x40000404))
#define COM_TX_STATUS              (*((VUC *)0x40000406))
#define COM_DIF_TO_MCU_B1          (*((VUC *)0x40000408))
#define COM_DIF_TO_MCU_B2          (*((VUC *)0x40000409))
#define COM_DIF_TO_MCU_B           (*((VUS *)0x40000408))
#define COM_RX_STATUS              (*((VUC *)0x4000040A))
#define COM_RX_INT_ENABLE          (*((VUC *)0x4000040B))
#define MICRO_INTERFACE_CONTROL    (*((VUC *)0x4000040C))
#define SECLOCK                    (*((VUC *)0x4000040D))
#define UART_CONFIG                (*((VUC *)0x40000200))
#define UART_EN                    (*((VUC *)0x40000201))
#define BAUD_RATE_LO               (*((VUC *)0x40000202))
#define BAUD_RATE_HI               (*((VUC *)0x40000203))
#define BAUD_RATE                  (*((VUS *)0x40000202))
#define UART_LINE_STATUS           (*((VUC *)0x40000204))
#define UART_INTERRUPT_STATUS      (*((VUC *)0x40000208))
#define UART_INTERRUPT_ENABLE      (*((VUC *)0x4000020A))
#define UART_RX_BUF                (*((VUC *)0x4000020C))
#define UART_TX_BUF                (*((VUC *)0x4000020E))
#define PWM_ON_TIME1               (*((VUC *)0x40000210))
#define PWM_ON_TIME2               (*((VUC *)0x40000211))
#define PWM_ON_TIME                (*((VUS *)0x40000210))
#define PWM_OFF_TIME1              (*((VUC *)0x40000212))
#define PWM_OFF_TIME2              (*((VUC *)0x40000213))
#define PWM_OFF_TIME               (*((VUS *)0x40000212))
#define PWM_EN                     (*((VUC *)0x40000214))
#define GPIO_INPUT                 (*((VUC *)0x40000218))
#define GPIO_OUTPUT                (*((VUC *)0x40000219))
#define GPIO_DIR                   (*((VUC *)0x4000021A))
#define REMAP                      (*((VUC *)0x40000220))
#define EEPROMARRAY                (0x40000000)
#define EEPROM_CACHE               (0x40000080)
#define EEPROM_PAGE_ADDRESS        (*((VUC *)0x40000088))
#define EEPROM_CTRL                (*((VUC *)0x40000089))
#define EEPROM_CRC                 (*((VUC *)0x4000008A))
#define EEPROM_STATUS              (*((VUC *)0x4000008B))
#define EEPROM_CRC_STATUS          (*((VUC *)0x4000008C))
#define EEPROM_CRC_VALUE           (*((VUC *)0x4000008D))
	
/* Bit definition of RAMBIST_STATUS register */
#define DATARAM_MBIST_DONE   (1 << 0)
#define DATARAM_MBIST_FAIL   (1 << 1)
#define DEVRAM_MBIST_DONE    (1 << 4)
#define DEVRAM_MBIST_FAIL    (1 << 5)
#define DATARAM_MBIST_NOTDONE (0 << 0)
#define DATARAM_MBIST_NOTFAIL (0 << 1)
#define DEVRAM_MBIST_NOTDONE  (0 << 4)
#define DEVRAM_MBIST_NOTFAIL  (0 << 5)

/* Bit definition of CLK_CTRL */
#define CLK_CTRL             ((1 << 0) | (1 << 1))
#define CLK_STATUS           ((1 << 4) | (1 << 5))
#define CLK_1MHZ             0x00
#define CLK_2MHZ             0x01
#define CLK_4MHZ             0x02
#define CLK_500KHZ           0x03

/* Bit definition of DIG_IF_CTRL register */
#define SPI_ENABLE               (1 << 0)
#define I2C_ENABLE               (1 << 1)
#define OWI_ENABLE               (1 << 2)
#define OWI_TRANSCEIVER_ENABLE   (1 << 3)
#define OWI_DEGLITCH_FILTER_10MS (1 << 4)
#define I2C_RATE_800_KBPS        (1 << 5)
#define I2C_DEGLITCH_EN          (1 << 6)
#define SPI_DISABLE              (0 << 0)
#define I2C_DISABLE              (0 << 1)
#define OWI_DISABLE              (0 << 2)
#define OWI_XCVR_DISABLE         (0 << 3)
#define OWI_DEGLITCH_FILTER_1MS  (0 << 4)
#define I2C_RATE_100_400_KBPS    (0 << 5)
#define I2C_DEGLITCH_DISABLE     (0 << 6)

/* Bit definition of OWI_ERROR_STATUS_LO register */
#define SYNC_FIELD_BIT_RATE_LT_320BPS      (1 << 0)
#define SYNC_FIELD_BIT_RATE_GT_19200BPS    (1 << 1)
#define SYNC_FIELD_STOP_BIT_SHORT          (1 << 2)
#define CMD_FIELD_INCORRECT_STOP_BIT       (1 << 3)
#define CMD_FIELD_STOP_BIT_SHORT           (1 << 4)
#define DATA_FIELD_INCORRECT_STOP_BIT      (1 << 5)
#define DATA_FIELD_STOP_BIT_SHORT          (1 << 6)
#define DATA_FIELD_SLAVE_TX_OVERDRIVEN     (1 << 7)

/* Bit definition of OWI_ERROR_STATUS_HI register */
#define SYNC_FIELD_BITS_DIFFERENT          (1 << 0)
#define INVALID_CMD_SENT                   (1 << 1)
#define CLEAR_OWI_ERROR_STATUS             (1 << 7)

/* Bit definition of OWI_INTERRUPT register */
#define OWI_INTERRUPT_ACTIVE               (1 << 0)

/* Bit definition of OWI_INTERRUPT_ENABLE register */
#define OWI_INT_ENABLE                     (1 << 0)

/* Bit definition of OTP_PROG_ADDR2 */
#define OTP_PROG             (1 << 7)

/* Bit definition of OTP_PROG_CTRL_STAT */
#define OTP_PROGTIMER_DIS    (1 << 0)
#define OTP_PROGTIMER_ENA    (0 << 0)
#define OTP_PROG_IN_PROGRESS (1 << 1)

/* Bit definition of WDOG_CTRL_STAT */
#define WATCH_DOG_TIMER_ENABLE  (1 << 0)
#define WATCH_DOG_TIMER_RESET   (1 << 7)

/* Bit definition of PIN_MUX register */
#define	UART_SELECT                           0x01

/* Bit definition of PADC_CONFIG or TADC_CONFIG register */
#define	ADC_ENABLE                  (1 << 0)
#define	ADC_ENABLE_24BIT            (1 << 1)
#define ADC_DECI_RATE_128US         (1 << 2)
#define ADC_INT_RATE_EVERY_4_SAMPLE (1 << 3)
#define	ADC_DISABLE                 (0 << 0)
#define	ADC_ENABLE_16BIT            (0 << 1)
#define ADC_DECI_RATE_64US          (0 << 2)
#define ADC_INT_RATE_EVERY_SAMPLE   (0 << 3)

/* Bit definition of ADC_CFG_1 register */
#define RESET_MOD                   (1 << 0)
#define RESET_CLK                   (1 << 1)
#define ADC_EN                      (1 << 4)

/* DAC_CTRL_STATUS DAC control status register definitions */
#define	DAC_ENABLE                    (1 << 0)
#define	DAC_DISABLE                   (0 << 0)

/* DAC_CONFIG - DAC configuration register definitions */
#define DAC_RATIOMETRIC_MODE_ENABLE   (1 << 0)
#define DAC_RATIOMETRIC_MODE_DISABLE  (0 << 0)

/* DAC_LPBK_CTRL - DAC loop-back control register definitions */
#define DAC_LOOPBACK_CONNECT          0x01
#define DAC_LOOPBACK_DISCONNECT       0x00
#define DAC_LOOPBACK_AMPLIFIER_ENABLE 0x02
#define DAC_LOOPBACK_AMPLIFIER_DISABLE 0x00
#define DAC_LOOPBACK_ENABLE           0x04
#define DAC_LOOPBACK_DISABLE          0x00

/* OP_STAGE_CTRL register bit definitions */
#define DAC_GAIN                      ((1 << 2) | (0 << 1) | (1 << 0))
#define B_4_20MA_EN                   (1 << 3)
#define DACCAP_EN                     (1 << 4)
#define PULLUP_EN                     (1 << 5)

/* DAC_GAIN configuration */
#define DAC_VOLTAGE_MODE_DIS          ((0 << 2) | (0 << 1) | (0 << 0))
#define DAC_GAIN_10V                  ((0 << 2) | (0 << 1) | (1 << 0))
#define DAC_GAIN_4V                   ((0 << 2) | (1 << 1) | (0 << 0))
#define DAC_GAIN_2V                   ((1 << 2) | (0 << 1) | (0 << 0))
#define DAC_GAIN_6_67V                ((1 << 2) | (1 << 1) | (0 << 0))
#define B_4_20MA_DISABLE              (0 << 3)
#define DACCAP_DISABLE                (0 << 4)
#define PULLUP_DISABLE                (0 << 5)

/* Bit definitions of AFE_CFG register */
#define PGAIN_OPEN    (0 << 5)
#define PGAIN_CLOSE   (1 << 5)

/* Bit definition of AFEDIAG_CFG register */
#define DIS_R1M       (1 << 0)
#define DIS_R2M       (1 << 1)
#define FAULT_THRS    ((1 << 4) | (1 << 3) | (1 << 2))
#define DIS_R_SD      (1 << 5)
#define DIS_R_TEMP    (1 << 6)
/* DIS_R2M , DIS_R1M bits definition */
#define PULL_DOWN_4M  ((0 << 1) | (0 << 0))
#define PULL_DOWN_3M  ((1 << 1) | (0 << 0))
#define PULL_DOWN_2M  ((0 << 1) | (1 << 0))
#define PULL_DOWN_1M  ((1 << 1) | (1 << 0))
/* FAULT_THRS bits definition */
#define PGAIN_UV_5_OV_95      ((0 << 4) | (0 << 3) | (0 << 2))
#define PGAIN_UV_7_5_OV_92_5  ((0 << 4) | (0 << 3) | (1 << 2))
#define PGAIN_UV_10_OV_90     ((0 << 4) | (1 << 3) | (0 << 2))
#define PGAIN_UV_12_5_OV_87_5 ((0 << 4) | (1 << 3) | (1 << 2))
#define PGAIN_UV_15_OV_85     ((1 << 4) | (0 << 3) | (0 << 2))
#define PGAIN_UV_20_OV_80     ((1 << 4) | (0 << 3) | (1 << 2))
#define PGAIN_UV_25_OV_75     ((1 << 4) | (1 << 3) | (0 << 2))
#define PGAIN_UV_30_OV_70     ((1 << 4) | (1 << 3) | (1 << 2))

/* Bit definition of BRDG_CTRL */
#define BRDG_EN           (1 << 0)
#define VBRDG_CTRL        ((1 << 2) | (1 << 1))
#define BRDG_DISABLE      (0 << 0)
#define VBRDG_CTRL_2_5V   ((0 << 2) | (0 << 1))
#define VBRDG_CTRL_2_0V   ((0 << 2) | (1 << 1))
#define VBRDG_CTRL_1_2V   ((1 << 2) | (0 << 1))


/* Bit definition of P_GAIN_SELECT register */
#define P_GAIN0                     (0 << 0)
#define P_GAIN1                     (0 << 1)
#define P_GAIN2                     (0 << 2)
#define P_GAIN3                     (0 << 3)
#define P_GAIN4                     (0 << 4)
#define P_INV                       (0 << 7)

#define P_GAIN_5_00_V_V             ((0 << 4) | (0 << 3) | (0 << 2) | (0 << 1) | (0 << 0))
#define P_GAIN_5_48_V_V             ((0 << 4) | (0 << 3) | (0 << 2) | (0 << 1) | (1 << 0))
#define P_GAIN_5_97_V_V             ((0 << 4) | (0 << 3) | (0 << 2) | (1 << 1) | (0 << 0))
#define P_GAIN_6_56_V_V             ((0 << 4) | (0 << 3) | (0 << 2) | (1 << 1) | (1 << 0))
#define P_GAIN_7_02_V_V             ((0 << 4) | (0 << 3) | (1 << 2) | (0 << 1) | (0 << 0))
#define P_GAIN_8_00_V_V             ((0 << 4) | (0 << 3) | (1 << 2) | (0 << 1) | (1 << 0))
#define P_GAIN_9_09_V_V             ((0 << 4) | (0 << 3) | (1 << 2) | (1 << 1) | (0 << 0))
#define P_GAIN_10_00_V_V            ((0 << 4) | (0 << 3) | (1 << 2) | (1 << 1) | (1 << 0))
#define P_GAIN_10_53_V_V            ((0 << 4) | (1 << 3) | (0 << 2) | (0 << 1) | (0 << 0))
#define P_GAIN_11_11_V_V            ((0 << 4) | (1 << 3) | (0 << 2) | (0 << 1) | (1 << 0))
#define P_GAIN_12_50_V_V            ((0 << 4) | (1 << 3) | (0 << 2) | (1 << 1) | (0 << 0))
#define P_GAIN_13_33_V_V            ((0 << 4) | (1 << 3) | (0 << 2) | (1 << 1) | (1 << 0))
#define P_GAIN_14_29_V_V            ((0 << 4) | (1 << 3) | (1 << 2) | (0 << 1) | (0 << 0))
#define P_GAIN_16_00_V_V            ((0 << 4) | (1 << 3) | (1 << 2) | (0 << 1) | (1 << 0))
#define P_GAIN_17_39_V_V            ((0 << 4) | (1 << 3) | (1 << 2) | (1 << 1) | (0 << 0))
#define P_GAIN_18_18_V_V            ((0 << 4) | (1 << 3) | (1 << 2) | (1 << 1) | (1 << 0))
#define P_GAIN_19_05_V_V            ((1 << 4) | (0 << 3) | (0 << 2) | (0 << 1) | (0 << 0))
#define P_GAIN_20_00_V_V            ((1 << 4) | (0 << 3) | (0 << 2) | (0 << 1) | (1 << 0))
#define P_GAIN_22_22_V_V            ((1 << 4) | (0 << 3) | (0 << 2) | (1 << 1) | (0 << 0))
#define P_GAIN_25_00_V_V            ((1 << 4) | (0 << 3) | (0 << 2) | (1 << 1) | (1 << 0))
#define P_GAIN_30_77_V_V            ((1 << 4) | (0 << 3) | (1 << 2) | (0 << 1) | (0 << 0))
#define P_GAIN_36_36_V_V            ((1 << 4) | (0 << 3) | (1 << 2) | (0 << 1) | (1 << 0))
#define P_GAIN_40_00_V_V            ((1 << 4) | (0 << 3) | (1 << 2) | (1 << 1) | (0 << 0))
#define P_GAIN_44_44_V_V            ((1 << 4) | (0 << 3) | (1 << 2) | (1 << 1) | (1 << 0))
#define P_GAIN_50_00_V_V            ((1 << 4) | (1 << 3) | (0 << 2) | (0 << 1) | (0 << 0))
#define P_GAIN_57_14_V_V            ((1 << 4) | (1 << 3) | (0 << 2) | (0 << 1) | (1 << 0))
#define P_GAIN_66_67_V_V            ((1 << 4) | (1 << 3) | (0 << 2) | (1 << 1) | (0 << 0))
#define P_GAIN_80_00_V_V            ((1 << 4) | (1 << 3) | (0 << 2) | (1 << 1) | (1 << 0))
#define P_GAIN_100_00_V_V           ((1 << 4) | (1 << 3) | (1 << 2) | (0 << 1) | (0 << 0))
#define P_GAIN_133_33_V_V           ((1 << 4) | (1 << 3) | (1 << 2) | (0 << 1) | (1 << 0))
#define P_GAIN_200_00_V_V           ((1 << 4) | (1 << 3) | (1 << 2) | (1 << 1) | (0 << 0))
#define P_GAIN_400_00_V_V           ((1 << 4) | (1 << 3) | (1 << 2) | (1 << 1) | (1 << 0))

/* Bit definition of T_GAIN_SELECT register */
#define T_GAIN0                     (0 << 0)
#define T_GAIN1                     (0 << 1)
#define T_INV                       (1 << 7)
#define T_GAIN_1_33_V_V             ((0 << 1) | (0 << 0))
#define T_GAIN_2_V_V                ((0 << 1) | (1 << 0))
#define T_GAIN_5_V_V                ((1 << 1) | (0 << 0))
#define T_GAIN_20_V_V               ((1 << 1) | (1 << 0))

/* Bit definition of TEMP_CTRL register */
#define TEMP_MUX_CTRL               ((0 << 3) | (0 << 2) | (0 << 1) | (0 << 0))
/* TEMP_MUX_CTRL  configuration */
#define VINTP_VINTN                 ((0 << 3) | (0 << 2) | (0 << 1) | (0 << 0))
#define VEXTP_VEXTN                 ((0 << 3) | (0 << 2) | (0 << 1) | (1 << 0))
#define VTEMP_INT                   ((0 << 3) | (0 << 2) | (1 << 1) | (1 << 0))
#define ITEMP_CTRL                  ((1 << 6) | (0 << 5) | (0 << 4))
/* ITEMP_CTRL configuration */
#define ITEMP_CTRL_25UA             ((0 << 6) | (0 << 5) | (0 << 4))
#define ITEMP_CTRL_50UA             ((0 << 6) | (0 << 5) | (1 << 4))
#define ITEMP_CTRL_100UA            ((0 << 6) | (1 << 5) | (0 << 4))
#define ITEMP_CTRL_500UA            ((0 << 6) | (1 << 5) | (1 << 4))
#define ITEMP_CTRL_OFF              ((1 << 6) | (0 << 5) | (0 << 4))

/* Bit definition of ALPWR register */
#define SHUT_DOWN                   (1 << 0)
#define ADC_EN_VREF                 (1 << 2)
#define GATE_CTRL_SD_DISABLE        (1 << 4)
#define POWER_UP_PT_PGA_FD          (0 << 0)
#define ADC_DIS_VREF                (0 << 2)
#define GATE_CTRL_SD_ENABLE         (0 << 4)

/* Bit definition of DLPWR register */
#define OWI_CLK_EN                         (1 << 0)

/* Bit definition of PSMON1 register */
#define VBRG_OV       (1 << 0)
#define VBRG_UV       (1 << 1)
#define REF_OV        (1 << 2)
#define REF_UV        (1 << 3)
#define AVDD_OV       (1 << 4)
#define AVDD_UV       (1 << 5)
#define OSC_VDD_OV    (1 << 6)
#define OSC_VDD_UV    (1 << 7)

/* Bit definition of PSMON2 register */
#define DVDD_OV       (1 << 0)
#define DVDD_UV       (1 << 1)

/* Resistive Bridge Sensor Connectivity Diagnostics */
/* Bit definition of AFEDIAG register */
#define VINP_OV       (1 << 0)
#define VINP_UV       (1 << 1)
#define VINT_OV       (1 << 2)
#define PGAIN_OV      (1 << 4)
#define PGAIN_UV      (1 << 5)
#define TGAIN_OV      (1 << 6)
#define TGAIN_UV      (1 << 7)

/* Digital multiplexer selection */
#define DIG_MUX_SEL_VBRDG_OV               0x01
#define DIG_MUX_SEL_VBRDG_UV               0x02
#define DIG_MUX_SEL_REF_OV                 0x03
#define DIG_MUX_SEL_REF_UV                 0x04
#define DIG_MUX_SEL_AVDD_OV                0x05
#define DIG_MUX_SEL_AVDD_UV                0x06
#define DIG_MUX_SEL_OSC_VDD_OV             0x07
#define DIG_MUX_SEL_OSC_VDD_UV             0x08
#define DIG_MUX_SEL_BRDG_OV                0x09
#define DIG_MUX_SEL_BRDG_UV                0x0a
#define DIG_MUX_SEL_TEMP_OV                0x0b
#define DIG_MUX_SEL_TEMP_UV                0x0c
#define DIG_MUX_SEL_PGAIN_OV               0x0d
#define DIG_MUX_SEL_PGAIN_UV               0x0e
#define DIG_MUX_SEL_TGAIN_OV               0x0f
#define DIG_MUX_SEL_TGAIN_UV               0x10
#define DIG_MUX_SEL_OWI_ERROR_STATUS_LO_0  0x11
#define DIG_MUX_SEL_OWI_ERROR_STATUS_LO_1  0x12
#define DIG_MUX_SEL_OWI_ERROR_STATUS_LO_2  0x13
#define DIG_MUX_SEL_OWI_ERROR_STATUS_LO_3  0x14
#define DIG_MUX_SEL_OWI_ERROR_STATUS_LO_4  0x15
#define DIG_MUX_SEL_OWI_ERROR_STATUS_LO_5  0x16
#define DIG_MUX_SEL_OWI_ERROR_STATUS_LO_6  0x17
#define DIG_MUX_SEL_OWI_ERROR_STATUS_LO_7  0x18
#define DIG_MUX_SEL_OWI_ERROR_STATUS_HI_0  0x19
#define DIG_MUX_SEL_OWI_ERROR_STATUS_HI_1  0x1a
#define DIG_MUX_SEL_OWI_RECEIVE_DATA       0x1b
#define DIG_MUX_SEL_OWI_TRANSMIT_DATA      0x1e
#define DIG_MUX_SEL_PWM                    0x1f
#define DIG_MUX_SEL_OWI_ACT_INTERRUPT      0x22
#define DIG_MUX_SEL_OWI_COMBUF_INTERRUPT   0x23
#define DIG_MUX_SEL_UART_INTERRUPT         0x24
#define DIG_MUX_SEL_PADC_INTERRUPT         0x27
#define DIG_MUX_SEL_TADC_INTERRUPT         0x28
#define DIG_MUX_SEL_OSC4MHz                0x29
#define DIG_MUX_SEL_CORTEX_M0_CLOCK        0x2a
#define DIG_MUX_SEL_ADC_CLOCK              0x2b
#define DIG_MUX_SEL_PADC_DECI_CLOCK        0x2c
#define DIG_MUX_SEL_TADC_DECI_CLOCK        0x2d
#define DIG_MUX_SEL_DATASRAM_MBIST_DONE    0x2f
#define DIG_MUX_SEL_DATASRAM_MBIST_FAIL    0x30
#define DIG_MUX_SEL_DEVSRAM_MBIST_DONE     0x31
#define DIG_MUX_SEL_DEVSRAM_MBIST_FAIL     0x32
#define DIG_MUX_SEL_DVDD_OV                0x33
#define DIG_MUX_SEL_DVDD_UV                0x34

/* Bit definition of AMUX_ACT register */
#define TIN_MUX_EN                  (1 << 0) 
#define TOUT_MUX_EN                 (1 << 1) 

/*
 * Analog multiplexer signal selection for TIP and TIN signal
 * AMUX_TIN_MUX_CTRL
 */
#define TIP_DAC_BUF_RATIOMETRIC_OUTPUT 0x00
#define TIP_ADC_OTA_COMMON_MODE_BUFFER 0x01
#define TIP_OUTPUT_BUFFER              0x02
#define TIP_TEST_MUX_OSCILLATOR        0x03
#define TIP_LOOP_BACK_AMPLIFIER        0x04
#define TIP_PRESSURE_ADC_INPUT_1       0x05
#define TIP_BRIDGE_BUFFER              0x06
#define TIP_T_ADC_INPUT_1              0x07
#define TIN_EXTERNAL_TEST_CLOCK        0x00
#define TIN_ACD_REF_COMMON_MODE_BUFFER 0x01
#define TIN_PRESSURE_ADC_INPUT_2       0x05
#define TIN_ADC_REF_BUFFER             0x06
#define TIN_T_ADC_INPUT_2              0x07

/*
 * Analog multiplexer signal selection for TOP and TON signal
 * AMUX_TOUT_MUX_CTRL
 */
#define TOP_BRIDGE_VOLTAGE             0x00
#define TOP_TPGA_OUTPUT_1              0x01
#define TOP_SPARE                      0x02
#define TOP_HIGH_VOLTAGE_REF           0x03
#define TOP_DAC_BUF_RATIOMETRIC_OUTPUT 0x04
#define TOP_DAC_OUTPUT                 0x05
#define TOP_REF_CURRENT_TRIM_V_I       0x06
#define TOP_AVSS                       0x07
#define TOP_ADC_OTA_COM_MODE           0x08
#define TOP_LOOP_BACK_OUTPUT_P         0x09
#define TOP_PPGA_OUTPUT_1              0x0A
#define TOP_AVDD                       0x0C
#define TOP_TIP                        0x0D
#define TOP_P_PGA_VCM                  0x0E
#define TON_ADC_REF                    0x00
#define TON_TPGA_OUTPUT_2              0x01
#define TON_OSCILLATOR                 0x02
#define TON_AVSS                       0x03
#define TON_2_5V_REF                   0x04
#define TON_REF_GROUND                 0x05
#define TON_ACD_REF_COM_MODE           0x08
#define TON_LOOP_BACK_OUTPUT_N         0x09
#define TON_PPGA_OUTPUT_2              0x0A
#define TON_OSCILLATOR_VDD             0x0C
#define TON_TIN                        0x0D
#define TON_T_PGA_VCM                  0x0E

/* Bit definition of AMUX_CTRL register */
#define TEST_MUX_DAC_EN             (1 << 0) 
#define TEST_MUX_P_EN               (1 << 1) 
#define TEST_MUX_T_EN               (1 << 2) 
#define TSEM_N                      (1 << 3) 

/* Bit definition of COM_TX_STATUS register */
#define COMBUF_TXRDY             (1 << 0)
/* Bit definition of COM_RX_STATUS register */
#define COMBUF_RXRDY             (1 << 0)
/* Enable COMBUF Receive interrupt */
#define COMBUF_RXRDY_INT_ENABLE  (1 << 0)

/* Bit definition of MICRO_INTERFACE_CONTROL register */
#define IF_SEL               (1 << 0)
#define MICRO_RESET          (1 << 1)
#define DEBUG_LOCK           (1 << 2)
#define MICRO_IF_SELECT      (0 << 0) /* M0 accesses PGA900 resources */
#define DIGITAL_IF_SELECT    (1 << 0) /* Digital IF accesses PGA900 resources */
#define DEBUG_UNLOCK         (0 << 2) /* Debug access PGA900 resource,IF_SEL=0*/

/* Bit definition of SECLOCK register */
#define SECURITY_LOCK_EN  (1 << 0) /* Enable when 0xAA is written to SECLOCK */
#define SECURITY_LOCK_DS  (0 << 0) /* Disable when 0x00 is written to SECLOCK */


/* Bit definition of UART_CONFIG register */
#define PARITY_ENABLE                         (1 << 0)
#define PARITY_EVEN                           (1 << 1)
#define TWO_STOP_BITS                         (1 << 2)
#define PARITY_DISABLE                        (0 << 0)
#define PARITY_ODD                            (0 << 1)
#define ONE_STOP_BIT                          (0 << 2)

/* Bit definition of UART_EN register */
#define	UART_ENABLE_BIT                       0x01

/*
 * Formula for Baud rate calculation are as below
 * Baud Rate Divider = round(250000 / (Desired baud rate)) - 1
 */
#define BAUD_RATE_DIVIDER_1200    207
#define BAUD_RATE_DIVIDER_2400    103
#define BAUD_RATE_DIVIDER_4800    51
#define BAUD_RATE_DIVIDER_9600    25
#define BAUD_RATE_DIVIDER_19200   12

/* Bit definition of UART_LINE_STATUS register */
#define	OVERRUN_ERROR                         (1 << 0)
#define	PARITY_ERROR                          (1 << 1)
#define	FRAMING_ERROR                         (1 << 2)
#define	RX_READY                              (1 << 3)
#define	TX_COMPLETE                           (1 << 4)

/* Bit definition of UART_INTERRUPT_STATUS register */
#define	UART_RXRDY_I                          (1 << 0)
#define	UART_TXCOMPLETE_I                     (1 << 1)

/* Bit definition of UART_INTERRUPT_ENABLE register */
#define	UART_RXRDY_INT_EN                     (1 << 0)
#define	UART_TXCOMPLETE_INT_EN                (1 << 1)

/* Bit definition of PWM_EN register */
#define PWM_BLOCK_EN  (1 << 0)
#define PWM_BLOCK_DIS (0 << 0)

/* Bit definition of GPIO_DIR register */
#define	GPIO1_DIR               (1 << 0)
#define GPIO2_DIR               (1 << 1)
#define GPIO1_CFG               (1 << 2)
#define GPIO2_CFG               (1 << 3)
#define	GPIO1_DIR_OUTPUT        (0 << 0)
#define	GPIO1_DIR_INPUT         (1 << 0)
#define	GPIO2_DIR_OUTPUT        (0 << 1)
#define	GPIO2_DIR_INPUT         (1 << 1)
#define	GPIO1_PUSH_PULL         (0 << 2)
#define	GPIO1_OPEN_DRAIN        (1 << 2)
#define	GPIO2_PUSH_PULL         (0 << 3)
#define	GPIO2_OPEN_DRAIN        (1 << 3)
#define	GPIO1_OUTPUT_OPEN_DRAIN (GPIO1_DIR_OUTPUT | GPIO1_OPEN_DRAIN)
#define	GPIO1_OUTPUT_PUSH_PULL  (GPIO1_DIR_OUTPUT | GPIO1_PUSH_PULL)
#define	GPIO2_OUTPUT_OPEN_DRAIN (GPIO2_DIR_OUTPUT | GPIO2_OPEN_DRAIN)
#define	GPIO2_OUTPUT_PUSH_PULL  (GPIO2_DIR_OUTPUT | GPIO2_PUSH_PULL)

/* Bit definition of REMAP register */
#define CODE_EXECUTE_OUT_OF_OTP    (0 << 0)
#define CODE_EXECUTE_OUT_OF_DEVRAM (1 << 0)

/* Bit definition of EEPROM control register */
#define EEPROM_PROGRAM                    (1 << 0)
#define EEPROM_ERASE                      (1 << 1)
#define EEPROM_ERASE_PROGRAM              (1 << 2)
#define EEPROM_FIX_ERASE_PROGRAM_TIME_8MS (1 << 3)

/* Bit definition of EEPROM_CRC register */
#define EEPROM_CALCULATE_CRC              (1 << 0)

/* Bit definition of EEPROM status register */
#define EEPROM_READ_IN_PROGRESS           (1 << 0)
#define EEPROM_ERASE_IN_PROGRESS          (1 << 1)
#define EEPROM_PROGRAM_IN_PROGRESS        (1 << 2)

/* Bit definition of EEPROM CRC status register */
#define EEPROM_CRC_CHECK_IN_PROGRESS      (1 << 0)
#define EEPROM_CRC_GOOD                   (1 << 1)

#ifdef __cplusplus
}
#endif

#endif /* PGA900_H */
