/**
 * @file   main.c
 * @brief  This is a GPSTracker application
 * @date   15-10-2023
 * @author Adhil
*/

/************************INCLUDES***************************/
#include "GPSHandler.h"
#include "BleHandler.h"
#include "BleService.h"
#include "JsonHandler.h"

/*************************MACROS****************************/
#define TICK_RATE 32768
#define COORD_READ_TIMEOUT	TICK_RATE * 2 //2 seconds for reading location coordinates 
#define SOG_READ_TIMEOUT	TICK_RATE * 2 //2 seconds for reading SOG in knots.
/*************************TYPEDEFS***************************/

/*************************FUNTION DEFINITION*****************/
/**
 * @brief  main function
 * @param  None
 * @return 0 on exit
*/
int main(void)
{
	int Ret = 0;
	long long TimeNow = 0;
	uint8_t ucIdx = 0;
	uint8_t *pucAdvBuffer = NULL;
	char *cJsonBuffer = NULL;
    cJSON * pMainObject = NULL;


	if (!InitUart())
	{
		printk("Device not initialised\n\r");
		return 0;
	}

	pucAdvBuffer = GetAdvertisingBuffer();

	if (!EnableBLE())
	{
		printk("Enabling ble failed \n\r");
		return 0;
	}

	if (InitExtendedAdv()) 
    {
		printk("Advertising failed to create (err %d)\n", Ret);
		return 0;
	}

    if(	StartAdvertising())
    {
        printk("Advertising failed to start (err %d)\n", Ret);
        return 0;
    }


	while(1)
	{

		pucAdvBuffer[2] = 0x03;

		if (IsRxComplete())
		{
			printk("Rxdata: %s\n\r", GetFlowRate());
			strcpy((char *)pucAdvBuffer+4, GetFlowRate());
			pucAdvBuffer[3] = (uint8_t)strlen((char *)pucAdvBuffer+4);
			SetRxStatus(false);
			
		}

		if(IsNotificationenabled())
		{
			VisenseSensordataNotify(pucAdvBuffer+2, ADV_BUFF_SIZE);
		}
		

	}

	return 0;
}
