/**
 * @file   main.c
 * @brief  This is a GPSTracker application
 * @date   15-10-2023
 * @author Adhil
*/

/************************INCLUDES***************************/
#include "GPSHandler.h"
#include "LCDHandler.h"

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
	float fLatitude = 0.00;
	float fLongitude = 0.00;
	float fSOG = 0.00;
	long long TimeNow = 0;
	char cLCDMessage[50] = {0};
	uint8_t ucIdx = 0;

	if (!InitUart())
	{
		printk("Device not initialised\n\r");
		return 0;
	}
	InitLCD();
	//Backlight();

	while(1)
	{
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
				}
			}
			else
			{
				//WriteLCDCmd(0x01); //Clear
				//printk("GPS module Waiting to get fix..\n\r");
				//SetLCDCursor(0,1);
				//strcpy(cLCDMessage, "Waiting for Loc fix..");
				//WriteStringToLCD(cLCDMessage);
				// for (ucIdx = 0; ucIdx < strlen(cLCDMessage)-16; ucIdx++)
				// {
				// 	k_sleep(K_MSEC(300));
				// 	WriteLCDCmd(LCD_SHIFT_LEFT);
				// }
				
			}
		}

		TimeNow = sys_clock_tick_get();

        while(sys_clock_tick_get() - TimeNow < COORD_READ_TIMEOUT)
        {
			if (ReadSOGData(&fSOG))
			{
				fSOG = fSOG*1.151;
				printk("SOG: %f\n\r", fSOG);
				WriteLCDCmd(0x01); //Clear
				SetLCDCursor(0, 1);
				sprintf(cLCDMessage, "SOG:%f", fSOG);
				WriteStringToLCD(cLCDMessage);
				k_sleep(K_MSEC(200));
			}
		}	
	}
	return 0;
}
