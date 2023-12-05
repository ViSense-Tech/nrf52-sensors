/**
 * @file    : Rtchandler.c
 * @brief   : File containing RTc related functions
 * @author  : Adhil
 * @date    : 04-10-2023
 * @note    :
*/

/***************************************INCLUDES*********************************/
#include "FreqGenerator.h"
#include <string.h>

/***************************************MACROS*********************************/
#define CK_GEN_ADDR		0x60

/***************************************GLOBALS*********************************/

static const struct device *i2c_dev = DEVICE_DT_GET(DT_NODELABEL(i2c0));



/***************************************FUNCTION DEFINITIONS********************/

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
	i2c_reg_write_byte(i2c_dev, CK_GEN_ADDR, SI_CLK0_CONTROL, 0x4F | SI_CLK_SRC_PLL_A);
}


// /**
//  * @brief Setting time and date of RTC
//  * @param None
//  * @return true for success
// */
// static bool SetTimeDate()
// {
// 	bool bRetVal = false;
// 	struct tm sTimeDate;
// 	char cTimeBuffer[MAX_TIME_BUFF_SIZE];
// 	uint8_t ucReg = 0x00;

// 	ConvertEpochToTime(llLastUpdatedTime, &sTimeDate, cTimeBuffer);

// 	do
//     {
//         if (i2c_reg_write_byte(i2c_dev, RTC_DEV_ADDR, 
// 								ucReg, ConvertDecimalToBCD(sTimeDate.tm_sec)) != 0)
//         {
//             printk("writing seconds failed\n\r");
//             break;
//         }

//         ucReg++;

//         if (i2c_reg_write_byte(i2c_dev, RTC_DEV_ADDR, 
// 								ucReg, ConvertDecimalToBCD(sTimeDate.tm_min)) != 0)
//         {
//             printk("writing minute failed\n\r");
//             break;
//         }

//         ucReg++;

//         if (i2c_reg_write_byte(i2c_dev, RTC_DEV_ADDR, 
// 								ucReg, ConvertDecimalToBCD(sTimeDate.tm_hour)) != 0)
//         {
//             printk("writing hour failed\n\r");
//             break;
//         }

//         ucReg++;

//         if (i2c_reg_write_byte(i2c_dev, RTC_DEV_ADDR, 
// 									ucReg, ConvertDecimalToBCD(sTimeDate.tm_wday)) != 0)
//         {
//             printk("writing Day failed\n\r");
//             break;
//         }

//         ucReg++;

//         if (i2c_reg_write_byte(i2c_dev, RTC_DEV_ADDR, 
// 									ucReg, ConvertDecimalToBCD(sTimeDate.tm_mday)) != 0)
//         {
//             printk("writing Date failed\n\r");
//             break;
//         }

//         ucReg++;
// 		printk("Month set: %d\n\r", sTimeDate.tm_mon);
// 		k_sleep(K_MSEC(1000));
//         if (i2c_reg_write_byte(i2c_dev, RTC_DEV_ADDR, 
// 									ucReg, ConvertDecimalToBCD(sTimeDate.tm_mon)) != 0)
//         {
//             printk("writing month failed\n\r");
//             break;
//         }

//         ucReg++;

//          if (i2c_reg_write_byte(i2c_dev, RTC_DEV_ADDR, 
// 		 							ucReg, ConvertDecimalToBCD((sTimeDate.tm_year+1900)-2000)) != 0)
//         {
//             printk("writing year failed\n\r");
//             break;
//         }

// 		bRetVal = true;

//     } while (0);

// 	return bRetVal;
// }

// /**
//  * @brief Initialise RTC
//  * @param None
//  * @return true for success
// */
// bool InitRtc()
// {
//     bool bRetVal = false;

//     if (i2c_reg_write_byte(i2c_dev, RTC_DEV_ADDR, RTC_CTRL_REG, 0x00) != 0)
//     {
//         printk("Configuring RTC failed\n\r");
//     }
//     else
//     {
//         printk("Configuring RTC success\n\r");
//         bRetVal = true;
//     }

// 	bRetVal = SetTimeDate();

//     return bRetVal;
// }

// /**
//  * @brief Get time in epoch format
//  * @param pllCurrEpoch : Epoch time 
//  * @return true for success
// */
// bool GetCurrenTimeInEpoch(long long *pllCurrEpoch)
// {
// 	struct tm sTimeStamp = {0};
// 	uint16_t ucData = 0x00;
// 	uint8_t ucReg = 0x00;
// 	char cTimeBuffer[MAX_TIME_BUFF_SIZE] = {0};
// 	bool bRetval = false;
// 	uint8_t ucRetry = 3;

// 	if (pllCurrEpoch)
// 	{
// 		do
// 		{
// 			if (0 != i2c_reg_read_byte(i2c_dev, RTC_DEV_ADDR, ucReg, &ucData))
// 			{
// 				printk("Reading seconds failed\n\r");
// 				break;
// 			}

// 			sTimeStamp.tm_sec = ConvertBCDToDecimal(ucData);
// 			//printk("Seconds: %d\n\r",sTimeStamp.tm_sec);
// 			ucReg++;

// 			if (0 != i2c_reg_read_byte(i2c_dev, RTC_DEV_ADDR, ucReg, &ucData))
// 			{
// 				printk("Reading minutes failed\n\r");
// 				break;
// 			}
			
// 			sTimeStamp.tm_min = ConvertBCDToDecimal(ucData);
// 			//printk("Min: %d\n\r",sTimeStamp.tm_min);
// 			ucReg++;

// 			if (0 != i2c_reg_read_byte(i2c_dev, RTC_DEV_ADDR, ucReg, &ucData))
// 			{
// 				printk("Reading hour failed\n\r");
// 				break;
// 			}
			
// 			sTimeStamp.tm_hour = ConvertBCDToDecimal(ucData);
// 			//printk("Hours: %d\n\r",sTimeStamp.tm_hour);
// 			ucReg++;

// 			if (0 != i2c_reg_read_byte(i2c_dev, RTC_DEV_ADDR, ucReg, &ucData))
// 			{
// 				printk("Reading day failed\n\r");
// 				break;
// 			}
			
// 			sTimeStamp.tm_wday = ConvertBCDToDecimal(ucData);
// 			//printk("Day: %d\n\r",sTimeStamp.tm_wday);
// 			ucReg++;

// 			if (0 != i2c_reg_read_byte(i2c_dev, RTC_DEV_ADDR, ucReg, &ucData))
// 			{
// 				printk("Reading date failed\n\r");
// 				break;
// 			}
			
// 			sTimeStamp.tm_mday = ConvertBCDToDecimal(ucData);
// 			//printk("Date: %d\n\r",sTimeStamp.tm_mday);
// 			ucReg++;	

// 			if (0 != i2c_reg_read_byte(i2c_dev, RTC_DEV_ADDR, ucReg, &ucData))
// 			{
// 				printk("Reading month failed\n\r");
// 				break;
// 			}
			
// 			sTimeStamp.tm_mon = ConvertBCDToDecimal(ucData);
// 			//printk("Month: %d\n\r",sTimeStamp.tm_mon);
// 			ucReg++;		

// 			if (0 != i2c_reg_read_byte(i2c_dev, RTC_DEV_ADDR, ucReg, &ucData))
// 			{
// 				printk("Reading year failed\n\r");
// 				break;
// 			}
			
// 			sTimeStamp.tm_year = ((ConvertBCDToDecimal(ucData)+2000) - 1900);
// 			//printk("Year: %d\n\r",sTimeStamp.tm_year+1900);
// 			strftime(cTimeBuffer, sizeof(cTimeBuffer), "%a %Y-%m-%d %H:%M:%S %Z", &sTimeStamp);
// 			printk("Current Time: %s\n\r", cTimeBuffer);
// 			sTimeStamp.tm_isdst = -1;
// 			*pllCurrEpoch = mktime(&sTimeStamp);

// 			bRetval = true;

// 		} while (0);
		
		
// 	}
// 	return bRetval;
// }