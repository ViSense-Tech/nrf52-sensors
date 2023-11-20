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
* This File contains PGA970 Register Definitions
*
* Rev. 1.0, Initial Release for CCS
*
********************************************************************/

#ifndef PGA970_TYPES_H
#define PGA970_TYPES_H

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

#endif /* PGA970_TYPES_H */

#ifndef PGA970_H
#define PGA970_H

#ifdef __cplusplus
extern "C" {
#endif

#define RAM_MBIST_CONTROL          (*((VUC *)0x40000502))
#define RAM_MBIST_STATUS           (*((VUC *)0x40000503))
#define CLK_CTRL_STATUS            (*((VUC *)0x40000504))
#define FRAM_STATUS                (*((VUC *)0x40000505))
#define DIG_IF_CTRL                (*((VUC *)0x40000506))

#define OWI_ERROR_STATUS_LO        (*((VUC *)0x40000508))
#define OWI_ERROR_STATUS_HI        (*((VUC *)0x40000509))
#define OWI_ERROR_STATUS           (*((VUS *)0x40000508))
#define OWI_INTERRUPT              (*((VUC *)0x4000050A))
#define OWI_INTERRUPT_ENABLE       (*((VUC *)0x4000050B))

#define FRAM_PAGE_ADDR             (*((VUC *)0x40000518))
#define DATA_WAVE_PAGE_ADDR        (*((VUC *)0x40000519))
#define DEVRAM_PAGE_ADDR           (*((VUC *)0x4000051A))

#define WDOG_CTRL_STAT             (*((VUC *)0x4000051C))
#define WDOG_TRIG_HIGH             (*((VUC *)0x4000051D))
#define WDOG_TRIG_LOW              (*((VUC *)0x4000051E))

#define DEMOD1_CONFIG              (*((VUC *)0x40000520))
#define DEMOD2_CONFIG              (*((VUC *)0x40000521))
#define ADC3_CONFIG                (*((VUC *)0x40000522))
#define S1_S2_DEMOD_CFG_1          (*((VUC *)0x40000524))
#define S3_ADC_CFG_1               (*((VUC *)0x40000526))
#define S1_CFG                     (*((VUC *)0x40000527)) 
#define S2_CFG                     (*((VUC *)0x40000528))
#define S1_S2_CFG                  (*((VUC *)0x40000529))  
#define S3_CFG                     (*((VUC *)0x4000052A))
#define S3_CFG_1                   (*((VUC *)0x4000052B))     

#define DAC_REG0_1                 (*((VUC *)0x40000530))
#define DAC_REG0_2                 (*((VUC *)0x40000531))
#define DAC_REG0                   (*((VUS *)0x40000530))
#define DAC_CTRL_STATUS            (*((VUC *)0x40000538))
#define DAC_CONFIG                 (*((VUC *)0x40000539))
#define DAC_LPBK_CTRL              (*((VUC *)0x4000053A))
#define OP_STAGE_CTRL              (*((VUC *)0x4000053B))

#define LVDT_OP_CTRL               (*((VUC *)0x4000053C))
#define LVDT_LPBK_CTRL             (*((VUC *)0x4000053D))

#define CCS_CTRL                   (*((VUC *)0x4000053E))

#define AFEDIAG_CFG                (*((VUC *)0x40000545))
#define ALPWR                      (*((VUC *)0x40000550))
#define DLPWR                      (*((VUC *)0x40000554))
#define PSMON1                     (*((VUC *)0x40000558))
#define PSMON2                     (*((VUC *)0x40000559))
#define PSMON                      (*((VUS *)0x40000558))
#define AFEDIAG                    (*((VUC *)0x4000055B))
#define AFEDIAG1                   (*((VUC *)0x4000055C))
#define AFEDIAG3                   (*((VUC *)0x4000055E))
#define AFEDIAG4                   (*((VUC *)0x4000055F))

#define TOPDIG_MUX_SEL             (*((VUC *)0x40000560))

#define AMUX_ACT                   (*((VUC *)0x40000564))
#define AMUX_TIN_MUX_CTRL          (*((VUC *)0x40000565))
#define AMUX_TOUT_MUX_CTRL         (*((VUC *)0x40000566))
#define AMUX_CTRL                  (*((VUC *)0x40000567))

#define TRACE_FIFO_CTRL_STAT       (*((VUC *)0x40000570))

#define WAVEFORM_GEN_CTRL          (*((VUC *)0x40000578))
#define WAVEFORM_TABLE_LEN         (*((VUC *)0x4000057A))
#define WAVEFORM_DAC_OFFSET_0      (*((VUC *)0x4000057C))
#define WAVEFORM_DAC_OFFSET_1      (*((VUC *)0x4000057D))
#define WAVEFORM_DAC_OFFSET        (*((VUS *)0x4000057C))

#define FAST_DIV_NUMERATOR         (*((VSL *)0x40000580))
#define FAST_DIV_DENOMINATOR       (*((VSL *)0x40000584))
#define FAST_DIV_CTRL              (*((VUC *)0x40000588))
#define FAST_DIV_STAT              (*((VUC *)0x4000058A))
#define FAST_DIV_QUOTIENT          (*((VSL *)0x4000058C))
#define FAST_DIV_REMAINDER         (*((VSL *)0x40000590))

#define DEMOD1_BPF_B1              (*((VUL *)0x40000598))
#define DEMOD1_BPF_A2              (*((VUL *)0x4000059C))
#define DEMOD1_BPF_A3              (*((VUL *)0x400005A0))
#define DEMOD1_LPF_B1              (*((VS2 *)0x400005A4))
#define DEMOD1_LPF_A2              (*((VS2 *)0x400005A8))

#define DEMOD2_BPF_B1              (*((VUL *)0x400005B4))
#define DEMOD2_BPF_A2              (*((VUL *)0x400005B8))
#define DEMOD2_BPF_A3              (*((VUL *)0x400005BC))
#define DEMOD2_LPF_B1              (*((VS2 *)0x400005C0))
#define DEMOD2_LPF_A2              (*((VS2 *)0x400005C4))

#define ADC3_AIN1_LPF_B1           (*((VS2 *)0x400005CC))
#define ADC3_AIN1_LPF_A2           (*((VS2 *)0x400005CE))
#define ADC3_PTAT_LPF_B1           (*((VS2 *)0x400005E0))
#define ADC3_PTAT_LPF_A2           (*((VS2 *)0x400005E2))

#define DAC_SIN_NDS1               (*((VUS *)0x400005E4))
#define DAC_SIN_NDS2               (*((VUS *)0x400005E6))

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

#define DEMOD1_DATA                (*((VSL *)0x40000410))
#define DEMOD2_DATA                (*((VSL *)0x40000414))
#define ADC3_AIN1_DATA             (*((VSL *)0x4000041C))
#define ADC3_PTAT_DATA             (*((VSL *)0x40000428))
#define DEMOD1_PH1_DATA            (*((VSL *)0x4000042C))
#define DEMOD1_PH2_DATA            (*((VSL *)0x40000430))
#define DEMOD2_PH1_DATA            (*((VSL *)0x40000434))
#define DEMOD2_PH2_DATA            (*((VSL *)0x40000438))
#define ADC3_COIL3_DATA            (*((VSL *)0x4000043C))

#define REMAP                      (*((VUC *)0x40000220))

#define GPIO_INPUT                 (*((VUC *)0x40000230))
#define GPIO_OUTPUT                (*((VUC *)0x40000231))
#define GPIO_DIR                   (*((VUC *)0x40000232))
#define GPIO_OPTYPE                (*((VUC *)0x40000233))

#define PIN_MUX                    (*((VUC *)0x40000240))

/*FRAM TEXT area*/
#define FRAM_TEXT_START_ADDRESS    (0x00000000)
#define FRAM_TEXT_END_ADDRESS      (0x000017FF)
#define FRAM_TEXT_AREA_SIZE        (0x1800)

/*FRAM DATA area*/
#define FRAM_DATA_START_ADDRESS    (0x00001800)
#define FRAM_DATA_END_ADDRESS      (0x00001FFF)

/*Development Ram start address*/
#define DEVRAM_START_ADDRESS       (0x21000000)

/* Bit definition of CLK_CTRL */
#define CLK_CTRL             ((0 << 1) | (1 << 0))
#define CLK_1MHZ             ((0 << 1) | (0 << 0))
#define CLK_2MHZ             ((0 << 1) | (1 << 0))
#define CLK_4MHZ             ((1 << 1) | (0 << 0))
#define CLK_8MHZ             ((1 << 1) | (1 << 0))

/* Bit definition of DIG_IF_CTRL register */
#define SPI_ENABLE               (1 << 0)
#define OWI_ENABLE               (1 << 2)
#define OWI_TRANSCEIVER_ENABLE   (1 << 3)
#define OWI_DEGLITCH_FILTER_10MS (1 << 4)

#define SPI_DISABLE              (0 << 0)
#define OWI_DISABLE              (0 << 2)
#define OWI_XCVR_DISABLE         (0 << 3)
#define OWI_DEGLITCH_FILTER_1MS  (0 << 4)

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
#define OWI_INT_DISABLE                    (0 << 0)

/* Bit definition of WDOG_CTRL_STAT */
#define WATCH_DOG_TIMER_ENABLE  (1 << 0)
#define WATCH_DOG_RESET_STS     (1 << 6)
#define WATCH_DOG_TIMER_RESET   (1 << 7)

/* Bit definition of DEMOD1_CONFIG register */
#define	DEMOD1_EN                 (1 << 0)
#define DEMOD1_DECI_RATE_128      (0 << 2)
#define DEMOD1_DECI_RATE_256      (1 << 2)
#define	DISABLE_DEMOD1_EN         (0 << 0)

/* Bit definition of DEMOD2_CONFIG register */
#define	DEMOD2_EN                 (1 << 0)
#define DEMOD2_DECI_RATE_128      (0 << 2)
#define DEMOD2_DECI_RATE_256      (1 << 2)
#define	DISABLE_DEMOD2_EN         (0 << 0)

/* Bit definition of ADC3_CONFIG register */
#define	ADC3_EN                   (1 << 0)
#define	DISABLE_ADC3_EN           (0 << 0)

/* Bit definition of S1_S2_DEMOD_CFG_1 register */
#define	S1_S2_RESET_MOD           (1 << 0)
#define	S1_S2_RESET_CLK           (1 << 1)
#define S1_S2_DEMOD_EN            (1 << 3)
#define NO_S1_S2_RESET_MOD        (0 << 0)
#define NO_S1_S2_RESET_CLK        (0 << 1)
#define DISABLE_S1_S2_DEMOD_EN    (0 << 3)

/* Bit definition of S3_ADC_CFG_1 register */
#define	S3_RESET_MOD            (1 << 0)
#define	S3_RESET_CLK            (1 << 1)
#define	S3_ADC_EN               (1 << 3)

#define NO_S3_RESET_MOD         (0 << 0)
#define NO_S3_RESET_CLK         (0 << 1)
#define	S3_ADC_DISABLE          (0 << 3)

/* Bit definition of S1_CFG register */
#define	S1_GAIN_1_00_V_V            ((0 << 1) | (0 << 0))
#define	S1_GAIN_1_33_V_V            ((0 << 1) | (1 << 0))
#define	S1_GAIN_1_67_V_V            ((1 << 1) | (0 << 0))
#define	S1_GAIN_2_00_V_V            ((1 << 1) | (1 << 0))
#define	S1_GAIN_SINGLE_END          (1 << 6)
#define	S1_GAIN_DIFFERENTIAL        (0 << 6)
#define	S1_INV                      (1 << 7)
#define NO_S1_INV                   (0 << 7)

/* Bit definition of S2_CFG register */
#define	S2_GAIN_1_00_V_V            ((0 << 1) | (0 << 0))
#define	S2_GAIN_1_33_V_V            ((0 << 1) | (1 << 0))
#define	S2_GAIN_1_67_V_V            ((1 << 1) | (0 << 0))
#define	S2_GAIN_2_00_V_V            ((1 << 1) | (1 << 0))
#define	S2_GAIN_SINGLE_END          (1 << 6)
#define	S2_GAIN_DIFFERENTIAL        (0 << 6)
#define	S2_INV                      (1 << 7)
#define NO_S2_INV                   (0 << 7)

/* Bit definition of S1_S2_CFG register */
#define	BIAS_VCM_CTRL_0_0       ((0 << 1) | (0 << 0))
#define	BIAS_VCM_CTRL_0_1       ((0 << 1) | (1 << 0))
#define	BIAS_VCM_CTRL_1_0       ((1 << 1) | (0 << 0))
#define	BIAS_VCM_CTRL_1_1       ((1 << 1) | (1 << 0))
#define	VCM_ENABLE              (1 << 2)
#define	VCM_DISABLE             (0 << 2)

/* Bit definition of S3_CFG register */
#define	AIN1_GAIN_1_V_V           ((0 << 7) | (0 << 6))
#define	AIN1_GAIN_1_33_V_V        ((0 << 7) | (1 << 6))
#define	AIN1_GAIN_2_V_V           ((1 << 7) | (0 << 6))
#define	AIN1_GAIN_5_V_V           ((1 << 7) | (1 << 6))

/* Bit definition of S3_CFG_1 register */
#define	PTAT_GAIN_1_V_V         ((0 << 1) | (0 << 0))
#define	PTAT_GAIN_1_33_V_V      ((0 << 1) | (1 << 0))
#define	PTAT_GAIN_2_V_V         ((1 << 1) | (0 << 0))
#define	PTAT_GAIN_5_V_V         ((1 << 1) | (1 << 0))
#define	S3_OUTPUT_INV           (1 << 7)
#define NO_S3_OUTPUT_INV        (0 << 7)

/* DAC_CTRL_STATUS DAC control status register definitions */
#define	DAC_ENABLE                    (1 << 0)
#define	DAC_DISABLE                   (0 << 0)

/* DAC_CONFIG - DAC configuration register definitions */
#define DAC_RATIOMETRIC_MODE_ENABLE   (1 << 0)
#define DAC_ABSOLUTE_MODE_ENABLE      (0 << 0)

/* DAC_LPBK_CTRL - DAC loop-back control register definitions */
#define DAC_LOOPBACK_CONNECT          (1 << 0)
#define DAC_LOOPBACK_DISCONNECT       (0 << 0)

#define DAC_LOOPBACK_AMPLIFIER_ENABLE  (1 << 1)
#define DAC_LOOPBACK_AMPLIFIER_DISABLE (0 << 1)

#define DAC_LOOPBACK_ENABLE           (1 << 2)
#define DAC_LOOPBACK_DISABLE          (0 << 2)

/* OP_STAGE_CTRL register bit definitions */
#define DAC_VOLTAGE_MODE_DIS          ((0 << 2) | (0 << 1) | (0 << 0))

/* DAC GAIN configuration is for Absolute mode*/
#define DAC_GAIN_10_V_V               ((0 << 2) | (0 << 1) | (1 << 0))
#define DAC_GAIN_4_V_V                ((0 << 2) | (1 << 1) | (0 << 0))
#define DAC_GAIN_2_V_V                ((1 << 2) | (0 << 1) | (0 << 0))
#define DAC_GAIN_6_67_V_V             ((1 << 2) | (1 << 1) | (0 << 0))

/* DAC GAIN configuration is for Ratiometric mode*/
#define DAC_GAIN_RATIOMETRIC_4_V_V    ((0 << 2) | (1 << 1) | (0 << 0))

#define CL_4_20MA_ENABLE              (1 << 3)
#define CL_4_20MA_DISABLE             (0 << 3)

#define DACCAP_ENABLE                 (1 << 4)
#define DACCAP_DISABLE                (0 << 4)

#define PULLUP_ENABLE                 (1 << 5)
#define PULLUP_DISABLE                (0 << 5)

#define GATE_3P3_CTRL_VDD_14_V        (1 << 7)
#define GATE_3P3_CTRL_VDD_3_5_V       (0 << 7)

/* LVDT_OP_CTRL register bit definitions */
#define DACVCM_CTRL_0_82_V            ((0 << 1) | (0 << 0))
#define DACVCM_CTRL_0_84_V            ((0 << 1) | (1 << 0))
#define DACVCM_CTRL_0_86_V            ((1 << 1) | (0 << 0))
#define DACVCM_CTRL_0_88_V            ((1 << 1) | (1 << 0))

#define DIFF_VOCM_CTRL_0_75_V         ((0 << 3) | (0 << 2))
#define DIFF_VOCM_CTRL_1_00_V         ((0 << 3) | (1 << 2))
#define DIFF_VOCM_CTRL_1_25_V         ((1 << 3) | (0 << 2))
#define DIFF_VOCM_CTRL_1_50_V         ((1 << 3) | (1 << 2))

#define LVDT_GAIN_CTRL_1_00_V_V       ((0 << 5) | (0 << 4))
#define LVDT_GAIN_CTRL_1_18_V_V       ((0 << 5) | (1 << 4))
#define LVDT_GAIN_CTRL_1_40_V_V       ((1 << 5) | (0 << 4))
#define LVDT_GAIN_CTRL_1_67_V_V       ((1 << 5) | (1 << 4))

#define SKIP_FILTER_ENABLE            (1 << 6)
#define SKIP_FILTER_DISABLE           (0 << 6)

#define LVDT_SINGLE_ENDED_MODE        (0 << 7)
#define LVDT_SINGLE_DIFFERENTIAL_MODE (1 << 7)

/* LVDT_LPBK_CTRL - DAC loop-back control register definitions */
#define LVDT_LOOPBACK_CONNECT          (1 << 0)
#define LVDT_LOOPBACK_DISCONNECT       (0 << 0)

/* CCS_CTRL CCS control status register definitions */
#define	CONST_VDD_CURRENT_ENABLE      (1 << 4)
#define ADJ_CCS_10_1_MA               ((0 << 3) | (0 << 2) | (0 << 1) | (0 << 0))
#define ADJ_CCS_11_1_MA               ((0 << 3) | (0 << 2) | (0 << 1) | (1 << 0))
#define ADJ_CCS_12_1_MA               ((0 << 3) | (0 << 2) | (1 << 1) | (0 << 0))
#define ADJ_CCS_13_1_MA               ((0 << 3) | (0 << 2) | (1 << 1) | (1 << 0))
#define ADJ_CCS_14_2_MA               ((0 << 3) | (1 << 2) | (0 << 1) | (0 << 0))
#define ADJ_CCS_15_2_MA               ((0 << 3) | (1 << 2) | (0 << 1) | (1 << 0))
#define ADJ_CCS_16_2_MA               ((0 << 3) | (1 << 2) | (1 << 1) | (0 << 0))
#define ADJ_CCS_17_3_MA               ((0 << 3) | (1 << 2) | (1 << 1) | (1 << 0))
#define ADJ_CCS_18_3_MA               ((1 << 3) | (0 << 2) | (0 << 1) | (0 << 0))
#define ADJ_CCS_19_3_MA               ((1 << 3) | (0 << 2) | (0 << 1) | (1 << 0))
#define ADJ_CCS_20_3_MA               ((1 << 3) | (0 << 2) | (1 << 1) | (0 << 0))
#define ADJ_CCS_21_3_MA               ((1 << 3) | (0 << 2) | (1 << 1) | (1 << 0))
#define ADJ_CCS_22_3_MA               ((1 << 3) | (1 << 2) | (0 << 1) | (0 << 0))
#define ADJ_CCS_23_3_MA               ((1 << 3) | (1 << 2) | (0 << 1) | (1 << 0))
#define ADJ_CCS_24_3_MA               ((1 << 3) | (1 << 2) | (1 << 1) | (0 << 0))
#define ADJ_CCS_25_3_MA               ((1 << 3) | (1 << 2) | (1 << 1) | (1 << 0))
#define	CONST_VDD_CURRENT_DISABLE     (0 << 4)

/* Bit definition of AFEDIAG_CFG register */
#define S1_PULL_UP_ENABLE       (0 << 0)
#define S1_PULL_UP_DISABLE      (1 << 0)
#define S2_PULL_UP_ENABLE       (0 << 1)
#define S2_PULL_UP_DISABLE      (1 << 1)
#define S3_PULL_UP_ENABLE       (0 << 2)
#define S3_PULL_UP_DISABLE      (1 << 2)
#define PE_PULL_UP_ENABLE       (0 << 3)
#define PE_PULL_UP_DISABLE      (1 << 3)

/* Bit definition of ALPWR register */
#define SHUT_DOWN                   (1 << 0)
#define POWER_UP_PT_PGA_FD          (0 << 0)
#define ADC_EN_VREF                 (1 << 2)
#define ADC_DIS_VREF                (0 << 2)
#define GATE_CTRL_SD_DISABLE        (1 << 4)
#define GATE_CTRL_SD_ENABLE         (0 << 4)

/* Bit definition of DLPWR register */
#define OWI_CLK_EN                  (1 << 0)

/* Power Supply Diagnostics */
/* Bit definition of PSMON1 register */
#define REF_OV                  (1 << 2)
#define REF_UV                  (1 << 3)
#define AVDD_OV                 (1 << 4)
#define AVDD_UV                 (1 << 5)
#define LVDT_AVDD_OV            (1 << 6)
#define LVDT_AVDD_UV            (1 << 7)

/* Bit definition of PSMON2 register */
#define DVDD_OV                 (1 << 0)
#define OSC_BAD                 (1 << 4)
#define OSC_GOOD_CHECK_ENABLE   (1 << 6)
#define OSC_GOOD_CHECK_DISABLE  (0 << 6)

/* Bit definition of AFEDIAG register */
#define P1_OV                   (1 << 0)
#define P1_UV                   (1 << 1)
#define P1_OC                   (1 << 2)
#define P2_OV                   (1 << 3)
#define P2_UV                   (1 << 4)
#define P2_OC                   (1 << 5)
#define PE_OV                   (1 << 6)

/* Bit definition of AFEDIAG1 register */
#define S1_FAULT_OV             (1 << 0)
#define S1_GAIN_OV              (1 << 1)
#define S2_FAULT_OV             (1 << 4)
#define S2_GAIN_OV              (1 << 5)

/* Bit definition of AFEDIAG3 register */
#define AIN1_FAULT_OV           (1 << 4)
#define AIN1_GAIN_OV            (1 << 5)

/* Bit definition of AFEDIAG4 register */
#define PTAT_FAULT_OV           (1 << 0)
#define PTAT_GAIN_OV            (1 << 1)

/*Bit definitions for  AMUX_ACT register */
#define TIN_MUX_ENABLE          (1 << 0)
#define TOUT_MUX_ENABLE         (1 << 1)
#define TIN_MUX_DISABLE         (0 << 0)
#define TOUT_MUX_DISABLE        (0 << 1)

/*
 * Analog multiplexer signal selection for AIN2 and AIN1 signal
 * AMUX_TIN_MUX_CTRL
 */
#define TIP_REF_2P5_DAC                0x00
#define TIP_VREFCM                     0x01
#define TIP_VDT_DRIVE                  0x02
#define TIP_ADCS2P                     0x03
#define TIP_DIG_OSC                    0x04
#define TIP_ADCS1P                     0x05
#define TIP_REF_2P5                    0x06
#define TIP_ADCS3P                     0x07

#define TIN_ACD_REF_COMMON_MODE_BUFFER 0x01
#define TIN_DAC_OUTPUT_STAGE           0x02
#define TIN_ADCS2N                     0x03
#define TIN_LOOP_BACK_AMPLIFIER        0x04
#define TIN_ADCS1N                     0x05
#define TIN_S3_MOD_CLK                 0x06
#define TIN_ADCS3N                     0x07

/*
 * Analog multiplexer signal selection for TOP signal
 * AMUX_TOUT_MUX_CTRL
 */
#define TOP_AVDD_LVDT                  0x00
#define TOP_VCM                        0x02
#define TOP_HIGH_VOLTAGE_REF           0x03
#define TOP_REF2P5_DAC                 0x04
#define TOP_DAC_OUTPUT                 0x05
#define TOP_REF_CURRENT_TRIM_V_I       0x06
#define TOP_S1_TOUT1                   0x07
#define TOP_VOTACM_ADC_1_2             0x08
#define TOP_LOOP_BACK_OUTPUT_P         0x09
#define TOP_S1_VCM_OUT                 0x0A
#define TOP_S3_TOUT1                   0x0B
#define TOP_REG_AVDD                   0x0C
#define TOP_S2_TOUT1                   0x0F

/*
 * Analog multiplexer signal selection for TON signal
 * AMUX_TOUT_MUX_CTRL
 */
#define TON_ADC_REF                    0x00
#define TON_S2_VCM_OUT                 0x01
#define TON_OSCILLATOR                 0x02
#define TON_2_5V_REF                   0x04
#define TON_REF_GROUND                 0x05
#define TON_WAVEFORM_DAC_OUTPUT        0x06
#define TON_S1_TOUT2                   0x07
#define TON_VREFCM_ADC_1_2             0x08
#define TON_S3_TOUT2                   0x0B
#define TON_OSC_BG_1P2                 0x0C
#define TON_S2_TOUT2                   0x0F

/* Digital multiplexer selection
 * TOPDIAG_MUX_SEL or TONDIAG_MUX_SEL*/
#define DIG_MUX_SEL_REF_OV                 0x02
#define DIG_MUX_SEL_AVDD_OV                0x03
#define DIG_MUX_SEL_LVDT_VDD_OV            0x04
#define DIG_MUX_SEL_DVDD_OV                0x05
#define DIG_MUX_SEL_OSC_REF_OV             0x06
#define DIG_MUX_SEL_REF_UV                 0x08
#define DIG_MUX_SEL_AVDD_UV                0x09
#define DIG_MUX_SEL_LVDT_VDD_UV            0x0A
#define DIG_MUX_SEL_DVDD_UV                0x0B
#define DIG_MUX_SEL_OSC_REF_UV             0x0C
#define DIG_MUX_SEL_P1_OV                  0x0D
#define DIG_MUX_SEL_P1_UV                  0x0E
#define DIG_MUX_SEL_P1_OC                  0x0F
#define DIG_MUX_SEL_P2_OV                  0x10
#define DIG_MUX_SEL_P2_UV                  0x11
#define DIG_MUX_SEL_P2_OC                  0x12
#define DIG_MUX_SEL_PE_OV                  0x13
#define DIG_MUX_SEL_S1_FAULT_OV            0x14
#define DIG_MUX_SEL_S1_GAIN_OV             0x15
#define DIG_MUX_SEL_S2_FAULT_OV            0x17
#define DIG_MUX_SEL_S2_GAIN_OV             0x18
#define DIG_MUX_SEL_S3_FAULT_OV            0x1A
#define DIG_MUX_SEL_S3_GAIN_OV             0x1B
#define DIG_MUX_SEL_OWI_ERROR_STATUS_LO_0  0x1D
#define DIG_MUX_SEL_OWI_ERROR_STATUS_LO_1  0x1E
#define DIG_MUX_SEL_OWI_ERROR_STATUS_LO_2  0x1F
#define DIG_MUX_SEL_OWI_ERROR_STATUS_LO_3  0x20
#define DIG_MUX_SEL_OWI_ERROR_STATUS_LO_4  0x21
#define DIG_MUX_SEL_OWI_ERROR_STATUS_LO_5  0x22
#define DIG_MUX_SEL_OWI_ERROR_STATUS_LO_6  0x23
#define DIG_MUX_SEL_OWI_ERROR_STATUS_LO_7  0x24
#define DIG_MUX_SEL_OWI_ERROR_STATUS_HI_0  0x25
#define DIG_MUX_SEL_OWI_ERROR_STATUS_HI_1  0x26
#define DIG_MUX_SEL_OWI_RECEIVE_DATA       0x27
#define DIG_MUX_SEL_OWI_TRANSMIT_DATA      0x2A
#define DIG_MUX_SEL_ADC1_INTERRUPT         0x2D
#define DIG_MUX_SEL_OWI_ACT_INTERRUPT      0x2F
#define DIG_MUX_SEL_OWI_COMBUF_INTERRUPT   0x30
#define DIG_MUX_SEL_OSC_8MHZ               0x3D
#define DIG_MUX_SEL_M0_CLK                 0x3E
#define DIG_MUX_SEL_S1_S2_ADC_CLK          0x3F
#define DIG_MUX_SEL_ADC3_CLK               0x40
#define DIG_MUX_SEL_DEMOD1_DECI_CLK        0x44
#define DIG_MUX_SEL_DEMOD2_DECI_CLK        0x45
#define DIG_MUX_SEL_ADC3_DECI_CLK          0x46
#define DIG_MUX_SEL_WSRAM_MBIST_DONE       0x4A
#define DIG_MUX_SEL_WSRAM_MBIST_FAIL       0x4B
#define DIG_MUX_SEL_RAM_MBIST_DONE         0x4D
#define DIG_MUX_SEL_RAM_MBIST_FAIL         0x4E
#define DIG_MUX_SEL_ADC_CONVERSION_START   0x59

/*Bit definitions for  AMUX_CTRL register */
#define DAC_OP_TO_DAC_GAIN          (1 << 0)
#define DAC_OP_TO_TOP_TON           (0 << 0)
#define S1_OP_TO_ADC1               (1 << 1)
#define S1_OP_TO_TOP_TON            (0 << 1)
#define S2_OP_TO_ADC2               (1 << 2)
#define S2_OP_TO_TOP_TON            (0 << 2)
#define S3_OP_TO_ADC3               (1 << 3)
#define S3_OP_TO_TOP_TON            (0 << 3)
#define WAVEFORM_DAC_OP_TO_WAVEFORM_GAIN ((1 << 4)|(1 << 5)|(1 << 6)|(1 << 7))
#define WAVEFORM_DAC_OP_TO_TOP_TON  ((0 << 4)|(0 << 5)|(0 << 6)| (0 << 7))

/* Bit definition of TRACE_FIFO_CTRL_STAT register */
#define TRACE_FIFO_ENABLE           (1 << 0)
#define TRACE_SOURCE_DEMOD1         (0 << 1)
#define TRACE_SOURCE_DEMOD2         (1 << 1)
#define TRACE_SOURCE_ADC3_AIN1      (5 << 1)
#define TRACE_SOURCE_ADC3_PTAT      (6 << 1)
#define TRACE_FIFO_EMPTY            (1 << 4)
#define TRACE_FIFO_HALF_FULL        (1 << 5)
#define TRACE_FIFO_FULL             (1 << 6)
#define TRACE_FIFO_DISABLE          (0 << 0)

/* Bit definition of WAVEFORM_GEN_CTRL register */
#define WAVEFORM_GEN_ENABLE         (1 << 0)
#define WAVEFORM_GEN_DISABLE        (0 << 0)

/* Bit definition of FAST_DIV_CTRL register */
#define FAST_DIV_CTRL_DIV_START     (1 << 0)

/* Bit definition of FAST_DIV_STAT register */
#define FAST_DIV_STAT_DIV_COMPLETE  (1 << 0)
#define FAST_DIV_STAT_DEN_ZERO      (1 << 1)

/*ADC1/ADC2 BPF register configuration*/
#define ADC12_BPF_CF1KHZ_B20HZ_B1     0x41E
#define ADC12_BPF_CF1KHZ_B20HZ_A2     0xFFFA97
#define ADC12_BPF_CF1KHZ_B20HZ_A3     0xFFF7C4

#define ADC12_BPF_CF1KHZ_B100HZ_B1    0x1495
#define ADC12_BPF_CF1KHZ_B100HZ_A2    0xFFEA21
#define ADC12_BPF_CF1KHZ_B100HZ_A3    0xFFD6D6

#define ADC12_BPF_CF1KHZ_B250HZ_B1    0x336E
#define ADC12_BPF_CF1KHZ_B250HZ_A2    0xFFCB4C
#define ADC12_BPF_CF1KHZ_B250HZ_A3    0xFF9923

#define ADC12_BPF_CF2KHZ_B20HZ_B1     0x41E
#define ADC12_BPF_CF2KHZ_B20HZ_A2     0xFFF6B5
#define ADC12_BPF_CF2KHZ_B20HZ_A3     0xFFF7C4

#define ADC12_BPF_CF2KHZ_B100HZ_B1    0x1495
#define ADC12_BPF_CF2KHZ_B100HZ_A2    0xFFE640
#define ADC12_BPF_CF2KHZ_B100HZ_A3    0xFFD6D6

#define ADC12_BPF_CF2KHZ_B250HZ_B1    0x336E
#define ADC12_BPF_CF2KHZ_B250HZ_A2    0xFFC76B
#define ADC12_BPF_CF2KHZ_B250HZ_A3    0xFF9923

#define ADC12_BPF_CF3KHZ_B20HZ_B1     0x41E
#define ADC12_BPF_CF3KHZ_B20HZ_A2     0xFFF03E
#define ADC12_BPF_CF3KHZ_B20HZ_A3     0xFFF7C4

#define ADC12_BPF_CF3KHZ_B100HZ_B1    0x1495
#define ADC12_BPF_CF3KHZ_B100HZ_A2    0xFFDFC8
#define ADC12_BPF_CF3KHZ_B100HZ_A3    0xFFD6D6

#define ADC12_BPF_CF3KHZ_B250HZ_B1    0x336E
#define ADC12_BPF_CF3KHZ_B250HZ_A2    0xFFC0F5
#define ADC12_BPF_CF3KHZ_B250HZ_A3    0xFF9923

#define ADC12_BPF_CF4KHZ_B20HZ_B1     0x41E
#define ADC12_BPF_CF4KHZ_B20HZ_A2     0xFFE730
#define ADC12_BPF_CF4KHZ_B20HZ_A3     0xFFF7C4

#define ADC12_BPF_CF4KHZ_B100HZ_B1    0x1495
#define ADC12_BPF_CF4KHZ_B100HZ_A2    0xFFD6BB
#define ADC12_BPF_CF4KHZ_B100HZ_A3    0xFFD6D6

#define ADC12_BPF_CF4KHZ_B250HZ_B1    0x336E
#define ADC12_BPF_CF4KHZ_B250HZ_A2    0xFFB7E8
#define ADC12_BPF_CF4KHZ_B250HZ_A3    0xFF9923

#define ADC12_BPF_CF5KHZ_B20HZ_B1     0x41E
#define ADC12_BPF_CF5KHZ_B20HZ_A2     0xFFDB8C
#define ADC12_BPF_CF5KHZ_B20HZ_A3     0xFFF7CF

#define ADC12_BPF_CF5KHZ_B100HZ_B1    0x1495
#define ADC12_BPF_CF5KHZ_B100HZ_A2    0xFFCB18
#define ADC12_BPF_CF5KHZ_B100HZ_A3    0xFFD6D6

#define ADC12_BPF_CF5KHZ_B250HZ_B1    0x336E
#define ADC12_BPF_CF5KHZ_B250HZ_A2    0xFFAC47
#define ADC12_BPF_CF5KHZ_B250HZ_A3    0xFF9923

#define ADC12_BPF_CF6KHZ_B20HZ_B1     0x41E
#define ADC12_BPF_CF6KHZ_B20HZ_A2     0xFFCD52
#define ADC12_BPF_CF6KHZ_B20HZ_A3     0xFFF7C4

#define ADC12_BPF_CF6KHZ_B100HZ_B1    0x1495
#define ADC12_BPF_CF6KHZ_B100HZ_A2    0xFFBCDF
#define ADC12_BPF_CF6KHZ_B100HZ_A3    0xFFD6D6

#define ADC12_BPF_CF6KHZ_B250HZ_B1    0x336E
#define ADC12_BPF_CF6KHZ_B250HZ_A2    0xFF9E0F
#define ADC12_BPF_CF6KHZ_B250HZ_A3    0xFF9923

#define ADC12_BPF_CF7KHZ_B20HZ_B1     0x41E
#define ADC12_BPF_CF7KHZ_B20HZ_A2     0xFFBC82
#define ADC12_BPF_CF7KHZ_B20HZ_A3     0xFFF7C4

#define ADC12_BPF_CF7KHZ_B100HZ_B1    0x1495
#define ADC12_BPF_CF7KHZ_B100HZ_A2    0xFFAC10
#define ADC12_BPF_CF7KHZ_B100HZ_A3    0xFFD6D6

#define ADC12_BPF_CF7KHZ_B250HZ_B1    0x336E
#define ADC12_BPF_CF7KHZ_B250HZ_A2    0xFF8D43
#define ADC12_BPF_CF7KHZ_B250HZ_A3    0xFF9923

#define ADC12_BPF_CF8KHZ_B20HZ_B1     0x41E
#define ADC12_BPF_CF8KHZ_B20HZ_A2     0xFFA91D
#define ADC12_BPF_CF8KHZ_B20HZ_A3     0xFFF7C4

#define ADC12_BPF_CF8KHZ_B100HZ_B1    0x1495
#define ADC12_BPF_CF8KHZ_B100HZ_A2    0xFF98AC
#define ADC12_BPF_CF8KHZ_B100HZ_A3    0xFFD6D6

#define ADC12_BPF_CF8KHZ_B250HZ_B1    0x336E
#define ADC12_BPF_CF8KHZ_B250HZ_A2    0xFF79E1
#define ADC12_BPF_CF8KHZ_B250HZ_A3    0xFF9923

#define ADC12_BPF_CF9KHZ_B20HZ_B1     0x41E
#define ADC12_BPF_CF9KHZ_B20HZ_A2     0xFF9322
#define ADC12_BPF_CF9KHZ_B20HZ_A3     0xFFF7C4

#define ADC12_BPF_CF9KHZ_B100HZ_B1    0x1495
#define ADC12_BPF_CF9KHZ_B100HZ_A2    0xFF82B3
#define ADC12_BPF_CF9KHZ_B100HZ_A3    0xFFD6D6

#define ADC12_BPF_CF9KHZ_B250HZ_B1    0x336E
#define ADC12_BPF_CF9KHZ_B250HZ_A2    0xFF63EA
#define ADC12_BPF_CF9KHZ_B250HZ_A3    0xFF9923

#define ADC12_BPF_CF10KHZ_B20HZ_B1    0x41E
#define ADC12_BPF_CF10KHZ_B20HZ_A2    0xFF7A92
#define ADC12_BPF_CF10KHZ_B20HZ_A3    0xFFF7C4

#define ADC12_BPF_CF10KHZ_B100HZ_B1   0x1495
#define ADC12_BPF_CF10KHZ_B100HZ_A2   0xFF6A24
#define ADC12_BPF_CF10KHZ_B100HZ_A3   0xFFD6D6

#define ADC12_BPF_CF10KHZ_B250HZ_B1   0x336E
#define ADC12_BPF_CF10KHZ_B250HZ_A2   0xFF4B5F
#define ADC12_BPF_CF10KHZ_B250HZ_A3   0xFF9923

#define ADC12_BPF_CF11KHZ_B20HZ_B1    0x41E
#define ADC12_BPF_CF11KHZ_B20HZ_A2    0xFF5F6D
#define ADC12_BPF_CF11KHZ_B20HZ_A3    0xFFF7C4

#define ADC12_BPF_CF11KHZ_B100HZ_B1   0x1495
#define ADC12_BPF_CF11KHZ_B100HZ_A2   0xFF4F01
#define ADC12_BPF_CF11KHZ_B100HZ_A3   0xFFD6D6

#define ADC12_BPF_CF11KHZ_B250HZ_B1   0x336E
#define ADC12_BPF_CF11KHZ_B250HZ_A2   0xFF303F
#define ADC12_BPF_CF11KHZ_B250HZ_A3   0xFF9923

#define ADC12_BPF_CF12KHZ_B20HZ_B1    0x41E
#define ADC12_BPF_CF12KHZ_B20HZ_A2    0xFF41B3
#define ADC12_BPF_CF12KHZ_B20HZ_A3    0xFFF7C4

#define ADC12_BPF_CF12KHZ_B100HZ_B1   0x1495
#define ADC12_BPF_CF12KHZ_B100HZ_A2   0xFF3149
#define ADC12_BPF_CF12KHZ_B100HZ_A3   0xFFD6D6

#define ADC12_BPF_CF12KHZ_B250HZ_B1   0x336E
#define ADC12_BPF_CF12KHZ_B250HZ_A2   0xFF128A
#define ADC12_BPF_CF12KHZ_B250HZ_A3   0xFF9933

#define ADC12_BPF_CF13KHZ_B20HZ_B1    0x41E
#define ADC12_BPF_CF13KHZ_B20HZ_A2    0xFF2165
#define ADC12_BPF_CF13KHZ_B20HZ_A3    0xFFF7C4

#define ADC12_BPF_CF13KHZ_B100HZ_B1   0x1495
#define ADC12_BPF_CF13KHZ_B100HZ_A2   0xFF10FD
#define ADC12_BPF_CF13KHZ_B100HZ_A3   0xFFD6D6

#define ADC12_BPF_CF13KHZ_B250HZ_B1   0x336E
#define ADC12_BPF_CF13KHZ_B250HZ_A2   0xFEF242
#define ADC12_BPF_CF13KHZ_B250HZ_A3   0xFF9923

#define ADC12_BPF_CF14KHZ_B20HZ_B1    0x41E
#define ADC12_BPF_CF14KHZ_B20HZ_A2    0xFEFE83
#define ADC12_BPF_CF14KHZ_B20HZ_A3    0xFFF7C4

#define ADC12_BPF_CF14KHZ_B100HZ_B1   0x1495
#define ADC12_BPF_CF14KHZ_B100HZ_A2   0xFEEE1D
#define ADC12_BPF_CF14KHZ_B100HZ_A3   0xFFD6D6

#define ADC12_BPF_CF14KHZ_B250HZ_B1   0x336E
#define ADC12_BPF_CF14KHZ_B250HZ_A2   0xFECF66
#define ADC12_BPF_CF14KHZ_B250HZ_A3   0xFF9923

#define ADC12_BPF_CF15KHZ_B20HZ_B1    0x41E
#define ADC12_BPF_CF15KHZ_B20HZ_A2    0xFED90D
#define ADC12_BPF_CF15KHZ_B20HZ_A3    0xFFF7C4

#define ADC12_BPF_CF15KHZ_B100HZ_B1   0x1495
#define ADC12_BPF_CF15KHZ_B100HZ_A2   0xFEC8A9
#define ADC12_BPF_CF15KHZ_B100HZ_A3   0xFFD6D6

#define ADC12_BPF_CF15KHZ_B250HZ_B1   0x336E
#define ADC12_BPF_CF15KHZ_B250HZ_A2   0xFEA9F7
#define ADC12_BPF_CF15KHZ_B250HZ_A3   0xFF9923

#define ADC12_BPF_CF16KHZ_B20HZ_B1    0x41E
#define ADC12_BPF_CF16KHZ_B20HZ_A2    0xFEB103
#define ADC12_BPF_CF16KHZ_B20HZ_A3    0xFFF7C4

#define ADC12_BPF_CF16KHZ_B100HZ_B1   0x1495
#define ADC12_BPF_CF16KHZ_B100HZ_A2   0xFEA0A2
#define ADC12_BPF_CF16KHZ_B100HZ_A3   0xFFD6D6

#define ADC12_BPF_CF16KHZ_B250HZ_B1   0x336E
#define ADC12_BPF_CF16KHZ_B250HZ_A2   0xFE81F5
#define ADC12_BPF_CF16KHZ_B250HZ_A3   0xFF9923

#define ADC12_BPF_CF17KHZ_B20HZ_B1    0x41E
#define ADC12_BPF_CF17KHZ_B20HZ_A2    0xFE8667
#define ADC12_BPF_CF17KHZ_B20HZ_A3    0xFFF7C4

#define ADC12_BPF_CF17KHZ_B100HZ_B1   0x1495
#define ADC12_BPF_CF17KHZ_B100HZ_A2   0xFE7609
#define ADC12_BPF_CF17KHZ_B100HZ_A3   0xFFD6D6

#define ADC12_BPF_CF17KHZ_B250HZ_B1   0x336E
#define ADC12_BPF_CF17KHZ_B250HZ_A2   0xFE5761
#define ADC12_BPF_CF17KHZ_B250HZ_A3   0xFF9923

#define ADC12_BPF_CF18KHZ_B20HZ_B1    0x41E
#define ADC12_BPF_CF18KHZ_B20HZ_A2    0xFE5938
#define ADC12_BPF_CF18KHZ_B20HZ_A3    0xFFF7C4

#define ADC12_BPF_CF18KHZ_B100HZ_B1   0x1495
#define ADC12_BPF_CF18KHZ_B100HZ_A2   0xFE48DD
#define ADC12_BPF_CF18KHZ_B100HZ_A3   0xFFD6D6

#define ADC12_BPF_CF18KHZ_B250HZ_B1   0x336E
#define ADC12_BPF_CF18KHZ_B250HZ_A2   0xFE2A3A
#define ADC12_BPF_CF18KHZ_B250HZ_A3   0xFF9923

#define ADC12_BPF_CF19KHZ_B20HZ_B1    0x41E
#define ADC12_BPF_CF19KHZ_B20HZ_A2    0xFE2977
#define ADC12_BPF_CF19KHZ_B20HZ_A3    0xFFF7C4

#define ADC12_BPF_CF19KHZ_B100HZ_B1   0x1495
#define ADC12_BPF_CF19KHZ_B100HZ_A2   0xFE191F
#define ADC12_BPF_CF19KHZ_B100HZ_A3   0xFFD6D6

#define ADC12_BPF_CF19KHZ_B250HZ_B1   0x336E
#define ADC12_BPF_CF19KHZ_B250HZ_A2   0xFDFA82
#define ADC12_BPF_CF19KHZ_B250HZ_A3   0xFF9923

#define ADC12_BPF_CF20KHZ_B20HZ_B1    0x41E
#define ADC12_BPF_CF20KHZ_B20HZ_A2    0xFDF725
#define ADC12_BPF_CF20KHZ_B20HZ_A3    0xFFF7C4

#define ADC12_BPF_CF20KHZ_B100HZ_B1   0x1495
#define ADC12_BPF_CF20KHZ_B100HZ_A2   0xFDE6D0
#define ADC12_BPF_CF20KHZ_B100HZ_A3   0xFFD6D6

#define ADC12_BPF_CF20KHZ_B250HZ_B1   0x336E
#define ADC12_BPF_CF20KHZ_B250HZ_A2   0xFDC839
#define ADC12_BPF_CF20KHZ_B250HZ_A3   0xFF9923

/*ADC1/ADC2 LPF register configuration*/
#define ADC12_LPF_CF20HZ_OP128US_B1    0x105
#define ADC12_LPF_CF20HZ_OP128US_A2    0x7DF5

#define ADC12_LPF_CF20HZ_OP256US_B1    0x207
#define ADC12_LPF_CF20HZ_OP256US_A2    0x7BF2

#define ADC12_LPF_CF100HZ_OP128US_B1   0x4F3
#define ADC12_LPF_CF100HZ_OP128US_A2   0x7619

#define ADC12_LPF_CF100HZ_OP256US_B1   0x98C
#define ADC12_LPF_CF100HZ_OP256US_A2   0x6CE8

#define ADC12_LPF_CF250HZ_OP128US_B1   0xBBA
#define ADC12_LPF_CF250HZ_OP128US_A2   0x688B

#define ADC12_LPF_CF250HZ_OP256US_B1   0x15AC
#define ADC12_LPF_CF250HZ_OP256US_A2   0x54A8

/*ADC3 LPF register configuration*/
#define ADC3_LPF_CF20HZ_B1             0x187
#define ADC3_LPF_CF20HZ_A2             0x7CF3

#define ADC3_LPF_CF100HZ_B1            0x74A
#define ADC3_LPF_CF100HZ_A2            0x716C

#define ADC3_LPF_CF250HZ_B1            0x10E2
#define ADC3_LPF_CF250HZ_A2            0x5E3B

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
#define MICRO_IF_SELECT      (0 << 0) /* M0 accesses PGA970 resources */
#define DIGITAL_IF_SELECT    (1 << 0) /* Digital IF accesses PGA970 resources */
#define MICRO_NORESET        (0 << 1)
#define DEBUG_UNLOCK         (0 << 2) /* Debug access PGA970 resource,IF_SEL=0*/

/* Bit definition of SECLOCK register */
#define SECURITY_LOCK_EN  (1 << 0) /* Enable when 0xAA is written to SECLOCK */
#define SECURITY_LOCK_DS  (0 << 0) /* Disable when 0x00 is written to SECLOCK */

/* Bit definition of REMAP register */
#define REMAP_ENABLE          0x01
#define REMAP_DISABLE         0x00

/* Bit definition of GPIO_OUTPUT */
#define GPIO1_OUTPUT            (1 << 0)
#define GPIO2_OUTPUT            (1 << 1)

/* Bit definition of GPIO_DIR register */
#define	GPIO1_DIR_INPUT         (1 << 0)
#define	GPIO2_DIR_INPUT         (1 << 1)

#define	GPIO1_DIR_OUTPUT        (0 << 0)
#define	GPIO2_DIR_OUTPUT        (0 << 1)

/* Bit definition of GPIO_OPTYPE register */
#define	GPIO1_PUSH_PULL         (0 << 0)
#define	GPIO1_OPEN_DRAIN        (1 << 0)
#define	GPIO2_PUSH_PULL         (0 << 1)
#define	GPIO2_OPEN_DRAIN        (1 << 1)

/*Bit definition of PIN_MUX*/
#define TOPDIG_GPIO_2_PIN_ENABLE      (1 << 1)
#define GPIO_OP_GPIO_2_PIN_ENABLE     (0 << 1)

#ifdef __cplusplus
}
#endif

#endif /* PGA970_H */
