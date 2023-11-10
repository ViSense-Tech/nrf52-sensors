/**
 * @file    : main.c
 * @brief   : Application entry
 * @author  : Adhil
 * @date    : 09-11-2023
 * @note 
*/

/***************************************INCLUDES*********************************/
#include "Common.h"
#include "CapSense/Capsense.h"
/***************************************MACROS**********************************/

/***************************************TYPEDEFS*********************************/

/***************************************GLOBALS*********************************/

/***************************************FUNCTION DECLARTAION*********************/

//void CapSenseEvt(_eCapSenseEvt eCapSenseEvt);

/***************************************FUNCTION DEFINITIONS*********************/
#if 0 /*Not used this for now will be adding the event handler for cap sense later*/
/**
 * @brief Cap sense event handler
*/
void CapSenseEvt(_eCapSenseEvt eCapSenseEvt)
{
	printk("\n\rTouch occured\n\r");
	return;
}
#endif

void main(void)
{
	_sCapSenseConfig sCapSenseConfig = 
	{
		.ulInput = 2,
		.ulOutput = 11
	};

	if (!CapSenseInit(&sCapSenseConfig))
	{
		printk("ERR: Cap sense init failed\n\r");
	}

	/*Cap sense event handler registering*/
	//CapSenseCallback(CapSenseEvt);

	while(1)
	{
		CapsenseSample();
		k_msleep(10);
		if (GetTouchSenseStatus())
		{
			printk("INFO: Touch occured\n\r");
			SetTouchSense(false);
		}
	}
}
