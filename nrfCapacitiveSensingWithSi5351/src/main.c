/**
 * @file   main.c
 * @brief  This is a GPSTracker application
 * @date   15-10-2023
 * @author Adhil
 */

/************************INCLUDES***************************/
#include "FreqGenerator/FreqGenerator.h"
#include "ADC/AdcHandler.h"
#include <zephyr/kernel.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/devicetree.h>
#include <zephyr/device.h>
#include <zephyr/sys/printk.h>
#include <zephyr/sys/util.h>
#include <stdlib.h>
#include <stdio.h>
#include <zephyr/sys/reboot.h>

/*************************MACROS****************************/

/*************************TYPEDEFS***************************/

/***************************FUNCTION DECLARATION******************************/


/***************************GLOBAL VARIABLES******************************/

/*************************FUNTION DEFINITION******************************/
/**
 * @brief  main function
 * @param  None
 * @return 0 on exit
 */
int main(void)
{
	uint16_t usADCResult = 0;
	si5351aSetFrequency(8000000);
	InitADC();

	while (1)
	{
		usADCResult = AnalogRead();
		printk("ADC Reading = %d\n\r", usADCResult);
		k_msleep(500);
	}
}


// /**
//  * @brief  printing visense banner
//  * @param  None
//  * @return None
// */
// static void PrintBanner()
// {
//     printk("\n\r");
//     printk("'##::::'##:'####::'######::'########:'##::: ##::'######::'########:\n\r");
//     k_msleep(50);
//     printk("##:::: ##:. ##::'##... ##: ##.....:: ###:: ##:'##... ##: ##.....::\n\r");
//     k_msleep(50);
//     printk("##:::: ##:: ##:: ##:::..:: ##::::::: ####: ##: ##:::..:: ##:::::::\n\r");
//     k_msleep(50);
//     printk("##:::: ##:: ##::. ######:: ######::: ## ## ##:. ######:: ######:::\n\r");
//     k_msleep(50);
//     printk(". ##:: ##::: ##:::..... ##: ##...:::: ##. ####::..... ##: ##...::::\n\r");
//     k_msleep(50);
//     printk(":. ## ##:::: ##::'##::: ##: ##::::::: ##:. ###:'##::: ##: ##:::::::\n\r");
//     k_msleep(50);
//     printk("::. ###::::'####:. ######:: ########: ##::. ##:. ######:: ########:\n\r");
//     k_msleep(50);
//     printk(":::...:::::....:::......:::........::..::::..:::......:::........::\n\r");
//     k_msleep(50);
//     printk("\n\r");
// }