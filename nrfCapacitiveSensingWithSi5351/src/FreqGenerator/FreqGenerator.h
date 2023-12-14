/**
 * @file    : RtcHandler.h 
 * @brief   : File containing functions for handling RTC 
 * @author  : Adhil
 * @date    : 04-10-2023
 * @note 
*/

#ifndef _FREQ_GENERATOR_H
#define _FREQ_GENERATOR_H

/***************************************INCLUDES*********************************/
#include <time.h>
#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/drivers/i2c.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/devicetree.h>

/***************************************MACROS**********************************/
#define SI_CLK0_CONTROL	16			// Register definitions
#define SI_CLK1_CONTROL	17
#define SI_CLK2_CONTROL	18
#define SI_SYNTH_PLL_A	26
#define SI_SYNTH_PLL_B	34
#define SI_SYNTH_MS_0		42
#define SI_SYNTH_MS_1		50
#define SI_SYNTH_MS_2		58
#define SI_PLL_RESET		177

#define SI_R_DIV_1		0b00000000			// R-division ratio definitions
#define SI_R_DIV_2		0b00010000
#define SI_R_DIV_4		0b00100000
#define SI_R_DIV_8		0b00110000
#define SI_R_DIV_16		0b01000000
#define SI_R_DIV_32		0b01010000
#define SI_R_DIV_64		0b01100000
#define SI_R_DIV_128		0b01110000

#define SI_CLK_SRC_PLL_A	0b00000000
#define SI_CLK_SRC_PLL_B	0b00100000

#define XTAL_FREQ	27000000			// Crystal frequency


/***************************************TYPEDEFS*********************************/


/***************************************FUNCTION DECLARTAION*********************/
void si5351aSetFrequency(uint32_t frequency);
void InitMuxInputPins(void);
void SelectMuxChannel(uint8_t ucChannel);
#endif
