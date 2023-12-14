/**
 * @file    : Rtchandler.c
 * @brief   : File containing RTc related functions
 * @author  : Adhil
 * @date    : 04-10-2023
 * @note    :
*/

/***************************************INCLUDES*********************************/
#include "FreqGenerator.h"
#include <zephyr/kernel.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/devicetree.h>
#include <string.h>

/***************************************MACROS*********************************/
#define CK_GEN_ADDR		0x60

/***************************************GLOBALS*********************************/

static const struct device *i2c_dev = DEVICE_DT_GET(DT_NODELABEL(i2c0));
const struct gpio_dt_spec sMuxInput1 = GPIO_DT_SPEC_GET(DT_ALIAS(muxinputa), gpios);
const struct gpio_dt_spec sMuxInput2 = GPIO_DT_SPEC_GET(DT_ALIAS(muxinputb), gpios);


/***************************************FUNCTION DEFINITIONS********************/

void SelectMuxChannel(uint8_t ucChannel)
{
    switch(ucChannel)
    {   
        /*State of pin is inverted in nRF52840 DK need to investigate*/
        case 0: gpio_pin_set(sMuxInput1.port, sMuxInput1.pin , 1);
                gpio_pin_set(sMuxInput2.port, sMuxInput2.pin , 1);
                break;

        case 1: gpio_pin_set(sMuxInput1.port, sMuxInput1.pin , 0);
                gpio_pin_set(sMuxInput2.port, sMuxInput2.pin , 1);
                break;

        case 2: gpio_pin_set(sMuxInput1.port, sMuxInput1.pin , 1);
                gpio_pin_set(sMuxInput2.port, sMuxInput2.pin , 0);
                break;

        case 3: gpio_pin_set(sMuxInput1.port, sMuxInput1.pin , 0);
                gpio_pin_set(sMuxInput2.port, sMuxInput2.pin , 0);
                break;   

        default:
                 break;                     
            
    }
   
}

/**
 * @brief Initialize the GPIO pins for exciting the irrometer sensor
 * @param None
 * @return None
*/
void InitMuxInputPins(void)
{
    gpio_pin_configure_dt(&sMuxInput1, GPIO_OUTPUT_LOW);
    gpio_pin_configure_dt(&sMuxInput2, GPIO_OUTPUT_LOW);       
}

//
// Set up specified PLL with mult, num and denom
// mult is 15..90
// num is 0..1,048,575 (0xFFFFF)
// denom is 0..1,048,575 (0xFFFFF)
//
static void setupPLL(uint8_t pll, uint8_t mult, uint32_t num, uint32_t denom)
{
	uint32_t P1;					// PLL config register P1
	uint32_t P2;					// PLL config register P2
	uint32_t P3;					// PLL config register P3

	P1 = (uint32_t)(128 * ((float)num / (float)denom));
	P1 = (uint32_t)(128 * (uint32_t)(mult) + P1 - 512);
	P2 = (uint32_t)(128 * ((float)num / (float)denom));
	P2 = (uint32_t)(128 * num - denom * P2);
	P3 = denom;

	i2c_reg_write_byte(i2c_dev, CK_GEN_ADDR, pll + 0, (P3 & 0x0000FF00) >> 8);
	i2c_reg_write_byte(i2c_dev, CK_GEN_ADDR, pll + 1, (P3 & 0x000000FF));
	i2c_reg_write_byte(i2c_dev, CK_GEN_ADDR, pll + 2, (P1 & 0x00030000) >> 16);
	i2c_reg_write_byte(i2c_dev, CK_GEN_ADDR, pll + 3, (P1 & 0x0000FF00) >> 8);
	i2c_reg_write_byte(i2c_dev, CK_GEN_ADDR, pll + 4, (P1 & 0x000000FF));
	i2c_reg_write_byte(i2c_dev, CK_GEN_ADDR, pll + 5, ((P3 & 0x000F0000) >> 12) | ((P2 & 0x000F0000) >> 16));
	i2c_reg_write_byte(i2c_dev, CK_GEN_ADDR, pll + 6, (P2 & 0x0000FF00) >> 8);
	i2c_reg_write_byte(i2c_dev, CK_GEN_ADDR, pll + 7, (P2 & 0x000000FF));
}

//
// Set up MultiSynth with integer divider and R divider
// R divider is the bit value which is OR'ed onto the appropriate register, it is a #define in si5351a.h
//
static void setupMultisynth(uint8_t synth, uint32_t divider, uint8_t rDiv)
{
	uint32_t P1;					// Synth config register P1
	uint32_t P2;					// Synth config register P2
	uint32_t P3;					// Synth config register P3

	P1 = 128 * divider - 512;
	P2 = 0;							// P2 = 0, P3 = 1 forces an integer value for the divider
	P3 = 1;

	i2c_reg_write_byte(i2c_dev, CK_GEN_ADDR, synth + 0,   (P3 & 0x0000FF00) >> 8);
	i2c_reg_write_byte(i2c_dev, CK_GEN_ADDR, synth + 1,   (P3 & 0x000000FF));
	i2c_reg_write_byte(i2c_dev, CK_GEN_ADDR, synth + 2,   ((P1 & 0x00030000) >> 16) | rDiv);
	i2c_reg_write_byte(i2c_dev, CK_GEN_ADDR, synth + 3,   (P1 & 0x0000FF00) >> 8);
	i2c_reg_write_byte(i2c_dev, CK_GEN_ADDR, synth + 4,   (P1 & 0x000000FF));
	i2c_reg_write_byte(i2c_dev, CK_GEN_ADDR, synth + 5,   ((P3 & 0x000F0000) >> 12) | ((P2 & 0x000F0000) >> 16));
	i2c_reg_write_byte(i2c_dev, CK_GEN_ADDR, synth + 6,   (P2 & 0x0000FF00) >> 8);
	i2c_reg_write_byte(i2c_dev, CK_GEN_ADDR, synth + 7,   (P2 & 0x000000FF));
}

// 
// Set CLK0 output ON and to the specified frequency
// Frequency is in the range 1MHz to 150MHz
// Example: si5351aSetFrequency(10000000);
// will set output CLK0 to 10MHz
//
// This example sets up PLL A
// and MultiSynth 0
// and produces the output on CLK0
//
void si5351aSetFrequency(uint32_t frequency)
{
	uint32_t pllFreq;
	uint32_t xtalFreq = XTAL_FREQ;
	uint32_t l;
	float f;
	uint8_t mult;
	uint32_t num;
	uint32_t denom;
	uint32_t divider;

	divider = 900000000 / frequency;// Calculate the division ratio. 900,000,000 is the maximum internal 
									// PLL frequency: 900MHz
	if (divider % 2) divider--;		// Ensure an even integer division ratio

	pllFreq = divider * frequency;	// Calculate the pllFrequency: the divider * desired output frequency

	mult = pllFreq / xtalFreq;		// Determine the multiplier to get to the required pllFrequency
	l = pllFreq % xtalFreq;			// It has three parts:
	f = l;							// mult is an integer that must be in the range 15..90
	f *= 1048575;					// num and denom are the fractional parts, the numerator and denominator
	f /= xtalFreq;					// each is 20 bits (range 0..1048575)
	num = f;						// the actual multiplier is  mult + num / denom
	denom = 1048575;				// For simplicity we set the denominator to the maximum 1048575

									// Set up PLL A with the calculated multiplication ratio
	setupPLL(SI_SYNTH_PLL_A, mult, num, denom);

									// Set up MultiSynth divider 0, with the calculated divider. 
									// The final R division stage can divide by a power of two, from 1..128. 
									// reprented by constants SI_R_DIV1 to SI_R_DIV128 (see si5351a.h header file)
									// If you want to output frequencies below 1MHz, you have to use the 
									// final R division stage
	setupMultisynth(SI_SYNTH_MS_0, divider, SI_R_DIV_1);
									// Reset the PLL. This causes a glitch in the output. For small changes to 
									// the parameters, you don't need to reset the PLL, and there is no glitch
	i2c_reg_write_byte(i2c_dev, CK_GEN_ADDR, SI_PLL_RESET, 0xA0);	
									// Finally switch on the CLK0 output (0x4F)
									// and set the MultiSynth0 input to be PLL A
	i2c_reg_write_byte(i2c_dev, CK_GEN_ADDR, SI_CLK0_CONTROL /*| SI_CLK1_CONTROL | SI_CLK2_CONTROL*/,
														 0x4F | SI_CLK_SRC_PLL_A);
	setupPLL(SI_SYNTH_PLL_B, mult, num, denom);													 

	setupMultisynth(SI_SYNTH_MS_1, divider, SI_R_DIV_1);

	i2c_reg_write_byte(i2c_dev, CK_GEN_ADDR, SI_CLK1_CONTROL, 0x4F | SI_CLK_SRC_PLL_B);

	setupMultisynth(SI_SYNTH_MS_2, divider, SI_R_DIV_1);

	i2c_reg_write_byte(i2c_dev, CK_GEN_ADDR, SI_CLK2_CONTROL, 0x4F | SI_CLK_SRC_PLL_B);


}