/**
 * @file   main.c
 * @brief  This is a GPSTracker application
 * @date   15-10-2023
 * @author Adhil
*/

/************************INCLUDES***************************/
#include "GPSHandler.h"
#include "LCDHandler.h"
#include "Accelerometer.h"
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
	char pcLocation[100];
	int Ret = 0;
	float fLatitude = 0.00;
	float fLongitude = 0.00;
	float fSOG = 0.00;
	long long TimeNow = 0;
	char cLCDMessage[50] = {0};
	uint8_t ucIdx = 0;
	_sAcclData sAcclData = {0};
	uint8_t *pucAdvBuffer = NULL;
	char *cJsonBuffer = NULL;
    cJSON *pMainObject = NULL;


	if (!InitUart())
	{
		printk("Device not initialised\n\r");
		return 0;
	}

	InitLCD();

	pucAdvBuffer = GetAdvertisingBuffer();
    // Ret = bt_enable(NULL);
	// if (Ret) 
    // {
	// 	printk("Bluetooth init failed (err %d)\n", Ret);
	// 	return 0;
	// }
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
		pMainObject = cJSON_CreateObject();
		TimeNow = sys_clock_tick_get();

        while(sys_clock_tick_get() - TimeNow < COORD_READ_TIMEOUT)
        {
			if (ReadLocationData(pcLocation))
			{
				if (ConvertNMEAtoCoordinates(pcLocation, &fLatitude, &fLongitude))
				{
					WriteLCDCmd(0x01); //Clear
					SetLCDCursor(1, 1);
					printk("Latitude: %fN Longitude: %fE\n\r", fLatitude, fLongitude);
					sprintf(cLCDMessage, "Lat: %f", fLatitude);
					WriteStringToLCD(cLCDMessage);
					k_sleep(K_MSEC(100));
					SetLCDCursor(2,1);
					sprintf(cLCDMessage, "Lon:%f", fLongitude);
					WriteStringToLCD(cLCDMessage);
					k_sleep(K_MSEC(100));
					AddItemtoJsonObject(&pMainObject, NUMBER, "Latitude", &fLatitude, sizeof(float));
                	AddItemtoJsonObject(&pMainObject, NUMBER, "Longitude", &fLongitude, sizeof(float));
				}
			}
			else
			{
				printk("GPS module Waiting to get fix..\n\r");
			}
		}

		TimeNow = sys_clock_tick_get();

        while(sys_clock_tick_get() - TimeNow < COORD_READ_TIMEOUT)
        {
			if (ReadSOGData(&fSOG))
			{
				printk("SOG: %f\n\r", fSOG);
				WriteLCDCmd(0x01); //Clear
				SetLCDCursor(0, 1);
				sprintf(cLCDMessage, "SOG:%f", fSOG);
				WriteStringToLCD(cLCDMessage);
				k_sleep(K_MSEC(200));
				AddItemtoJsonObject(&pMainObject, NUMBER, "SOG", &fSOG, sizeof(float));
			}
		}

		if (!InitAcclerometer())
		{
			printk("Acclmtr not initialised\n\r");		
		}	
		else
		{
			printk("init accelerometer succes\n\r");
		}
		if (ReadFromAccelerometer(&sAcclData))
		{
			printk("AccX: %d\n\r AccY: %d\n\r AccZ:%d\n\r", 
										sAcclData.unAccX,
										sAcclData.unAccY,
										sAcclData.unAccZ);
				WriteLCDCmd(0x01); //Clear
				SetLCDCursor(1, 1);
				sprintf(cLCDMessage, "AccX:%d AccY:%d", 
									sAcclData.unAccX,
									sAcclData.unAccY);
				WriteStringToLCD(cLCDMessage);
				k_sleep(K_MSEC(200));
				SetLCDCursor(2, 1);
				sprintf(cLCDMessage, "AccZ:%d", 
									sAcclData.unAccZ);
				WriteStringToLCD(cLCDMessage);
				AddItemtoJsonObject(&pMainObject, NUMBER, "AccX", &sAcclData.unAccX, sizeof(float));
				AddItemtoJsonObject(&pMainObject, NUMBER, "AccY", &sAcclData.unAccY, sizeof(float));
				AddItemtoJsonObject(&pMainObject, NUMBER, "AccZ", &sAcclData.unAccZ, sizeof(float));
		}	

		    cJsonBuffer = cJSON_Print(pMainObject);

            pucAdvBuffer[2] = 0x03;
            pucAdvBuffer[3] = (uint8_t)strlen(cJsonBuffer);
            memcpy(pucAdvBuffer+4, cJsonBuffer, strlen(cJsonBuffer));

            printk("JSON:\n%s\n", cJsonBuffer);
            cJSON_Delete(pMainObject);
            cJSON_free(cJsonBuffer);

            if(IsNotificationenabled())
            {
                VisenseSensordataNotify(pucAdvBuffer+2, ADV_BUFF_SIZE);
            }
	}
	return 0;
}
