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
#include "RtcHandler.h"
#include "nvs_flash.h"
#include "SystemHandler.h"
#include "TimerHandler.h"

/*************************MACROS****************************/
#define TICK_RATE 32768
#define COORD_READ_TIMEOUT TICK_RATE * 2 // 2 seconds for reading location coordinates
#define SOG_READ_TIMEOUT TICK_RATE * 2	 // 2 seconds for reading SOG in knots.
#define TIME_STAMP_ERROR (1 << 1)
#define TIME_STAMP_OK ~(1 << 1)
/*************************TYPEDEFS***************************/

/***************************FUNCTION DECLARATION******************************/
static bool GetTimeFromRTC();
static bool WriteConfiguredtimeToRTC(void);
static bool CheckForConfigChange(void);

/***************************GLOBAL VARIABLES******************************/
struct nvs_fs sConfigFs;
_sConfigData sConfigData = {0};

uint32_t ulFlashidx = 0; // flash idx init

/*************************FUNTION DEFINITION*****************/
/**
 * @brief  main function
 * @param  None
 * @return 0 on exit
 */

/*******************************************************************IN_DEVELOPMENT********************************************************************************************************/
int main(void)
{

	int Ret = 0;
	float mSog = 0.00; // max sog limit init
	double fLatitude = 0.00;
	double fLongitude = 0.00;
	float fSOG = 0.00;
	long long TimeNow = 0, sysTime = 0;
	char cLCDMessage[50] = {0};
	char cLCDWarning[50] = {0};
	char *cJsonBuffer = NULL;
	char pcLocation[100];
	bool targetStatus = false; // flag to check geoFence
	uint8_t ucIdx = 0;
	_sAcclData sAcclData = {0};
	uint8_t *pucAdvBuffer = NULL;
	char cFlashReadBuf[128] = {0};
	long long llEpochTime = 0;
	uint32_t *pDiagData = NULL;

	cJSON *pMainObject = NULL;
	_sFenceData *psFenceLatLon = NULL; // stuct pointer of fence data structure

	if (!CheckForConfigChange())
	{
		printk("ERROR: Config change check failed \n\r");
		// return 0;
	}
	if (!InitRtc())
	{
		printk("RTC init failed\n\r");
		/// return 0;
	}

	if (!InitUart())
	{
		printk("Device not initialised\n\r");
		// return 0;
	}

	InitLCD();
	InitTimer();

	pucAdvBuffer = GetAdvertisingBuffer();
	pDiagData = GetDiagnosticData();
	// Ret = bt_enable(NULL);
	// if (Ret)
	// {
	// 	printk("Bluetooth init failed (err %d)\n", Ret);
	// 	return 0;
	// }
	if (!EnableBLE())
	{
		printk("Enabling ble failed \n\r");
		// return 0;
	}

	// if (InitExtendedAdv())
	// {
	// 	printk("Advertising failed to create (err %d)\n", Ret);
	// 	return 0;
	// }

	if (StartAdvertising())
	{
		printk("Advertising failed to start (err %d)\n", Ret);
		// return 0;
	}

	EraseExternalFlash(SECTOR_COUNT);

	if (!GetTimeFromRTC())
	{
		printk("WARN: Getting time from RTC failed \n\r");
	}

	while (1)
	{

		pMainObject = cJSON_CreateObject();
		TimeNow = sys_clock_tick_get();
#ifdef SLEEP_ENABLE
		sysTime = sys_clock_tick_get();

		while (sys_clock_tick_get() - sysTime < (ALIVE_TIME * TICK_RATE))
		{
#endif
			// #if 0
			while (sys_clock_tick_get() - TimeNow < COORD_READ_TIMEOUT)
			{
				// printk("In here timed wait location");
				if (ReadLocationData(pcLocation))
				{
					// printk("Loc: %s\n\r", pcLocation);
					*pDiagData = *pDiagData & GPS_FIX_OK;
					if (ConvertNMEAtoCoordinates(pcLocation, &fLatitude, &fLongitude))
					{
						WriteLCDCmd(0x01); // Clear
						SetLCDCursor(1, 1);
						k_usleep(10);
						printk("Latitude: %fN Longitude: %fE\n\r", fLatitude, fLongitude);
						memset(cLCDMessage,'\0', sizeof(cLCDMessage));
						sprintf(cLCDMessage, "Lat:%f", fLatitude);
						printk("Msg: %s\n\r", cLCDMessage);
						WriteStringToLCD(cLCDMessage);
						//k_sleep(K_MSEC(100));
						memset(cLCDMessage,'\0', sizeof(cLCDMessage));
						SetLCDCursor(2, 1);
						sprintf(cLCDMessage, "Lon:%f", fLongitude);
						printk("Msg: %s\n\r", cLCDMessage);
						WriteStringToLCD(cLCDMessage);
						k_sleep(K_MSEC(200));
						// AddItemtoJsonObject(&pMainObject, NUMBER, "Latitude", &fLatitude, sizeof(float));
						// AddItemtoJsonObject(&pMainObject, NUMBER, "Longitude", &fLongitude, sizeof(float));
						
					}
				}
				else
				{
					// *pDiagData = *pDiagData | GPS_FIX_FAILED;
					// printk("GPS module Waiting to get fix...\n\r");
				}
			}
			if (!(*pDiagData & (1 << 4)))
			{
				AddItemtoJsonObject(&pMainObject, FLOAT, "Latitude", &fLatitude, sizeof(float));
				AddItemtoJsonObject(&pMainObject, FLOAT, "Longitude", &fLongitude, sizeof(float));

			}
			

			TimeNow = sys_clock_tick_get();

			while (sys_clock_tick_get() - TimeNow < COORD_READ_TIMEOUT)
			{
				if (ReadSOGData(&fSOG))
				{
					printk("SOG: %f\n\r", fSOG);
					WriteLCDCmd(0x01); // Clear
					SetLCDCursor(0, 1);
					k_usleep(10);
					
					memset(cLCDMessage,'\0', sizeof(cLCDMessage));
					sprintf(cLCDMessage, "SOG:%f", fSOG);
					WriteStringToLCD(cLCDMessage);
					k_sleep(K_MSEC(200));
					AddItemtoJsonObject(&pMainObject, NUMBER, "SOG", &fSOG, sizeof(float));
					// mSog = GetSogMax();	//speed max value from config chara
					//  if (fSOG>mSog && targetStatus)           // if device inside fence & crossed threshold values
					//  {
					//  	printk("WARNING-SOG: %f\n\r", fSOG);
					//  	WriteLCDCmd(0x01); //Clear
					//  	SetLCDCursor(0, 1);
					//  	sprintf(cLCDWarning, "SOG:%f", fSOG);
					//  	WriteStringToLCD(cLCDWarning);
					//  	k_sleep(K_MSEC(200));
					//  }

					if (targetStatus == 1 && fSOG > mSog) // if device inside fence & crossed threshold values
					{
						printk("/n/r________________INSIDE FENCE_____________: %f\n\r", fSOG);
						WriteLCDCmd(0x01); // Clear
						SetLCDCursor(0, 1);
						sprintf(cLCDWarning, "INSIDE-FENCE%f", fSOG);
						WriteStringToLCD(cLCDWarning);
						k_sleep(K_MSEC(200));
					}

					// elif  not in target status
					//(print warning on LCD -outside geofence)
					// if (targetstatus)
					// store to flash

					// rec /store/adv -data only inside fence
					//  rec only when fsog>0 moving
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
				WriteLCDCmd(0x01); // Clear
				SetLCDCursor(1, 1);
				k_usleep(10);
				sprintf(cLCDMessage, "X:%d",
						sAcclData.unAccX);
				WriteStringToLCD(cLCDMessage);
				// k_sleep(K_MSEC(300));
				memset(cLCDMessage,'\0', sizeof(cLCDMessage));
				// WriteLCDCmd(0x01); // Clear
				SetLCDCursor(1, 9);
				k_usleep(10);
				sprintf(cLCDMessage, "Y:%d",
				sAcclData.unAccY);
				WriteStringToLCD(cLCDMessage);
				// k_sleep(K_MSEC(500));
				 memset(cLCDMessage,'\0', sizeof(cLCDMessage));
				// WriteLCDCmd(0x01); // Clear
				// k_usleep(10);
				SetLCDCursor(2, 1);
				 k_usleep(10);
				sprintf(cLCDMessage, "Z:%d",
						sAcclData.unAccZ);
				WriteStringToLCD(cLCDMessage);
				k_sleep(K_MSEC(200));
				//memset(cLCDMessage,'\0', sizeof(cLCDMessage));
				
				AddItemtoJsonObject(&pMainObject, NUMBER, "AccX", &sAcclData.unAccX, sizeof(float));
				AddItemtoJsonObject(&pMainObject, NUMBER, "AccY", &sAcclData.unAccY, sizeof(float));
				AddItemtoJsonObject(&pMainObject, NUMBER, "AccZ", &sAcclData.unAccZ, sizeof(float));
			}
			WriteConfiguredtimeToRTC();
			if (GetCurrentTime(&llEpochTime))
			{
				AddItemtoJsonObject(&pMainObject, NUMBER, "TS", &llEpochTime, sizeof(long long));
			}
			printk("DIAG data : %d\n\r", *pDiagData);
			AddItemtoJsonObject(&pMainObject, NUMBER, "DIAG", pDiagData, sizeof(uint32_t));
			*pDiagData = *pDiagData | GPS_FIX_FAILED;
			cJsonBuffer = cJSON_Print(pMainObject);
			//  if(targetStatus==1)
			{
				writeJsonToExternalFlash(cJsonBuffer, ulFlashidx, WRITE_ALIGNMENT);
				readJsonFromExternalFlash(cFlashReadBuf, ulFlashidx, WRITE_ALIGNMENT);
				printk("\n\rcFlash read%s\n\r", cFlashReadBuf);
				ulFlashidx++;
				printk("flash count: %d\n\r", ulFlashidx);
			}
			pucAdvBuffer[2] = 0x03;
			pucAdvBuffer[3] = (uint8_t)strlen(cJsonBuffer);
			memcpy(pucAdvBuffer + 4, cJsonBuffer, strlen(cJsonBuffer));
			if (IshistoryNotificationenabled() && IsConnected())
			{
				if (VisenseHistoryDataNotify(ulFlashidx))
				{
					ulFlashidx = 0;
				}
			}

			printk("JSON:\n%s\n", cJsonBuffer);
			cJSON_Delete(pMainObject);
			cJSON_free(cJsonBuffer);

			// #endif
			if (IsConfigLat() && IsConfigLon())
			{

				// if (polygonPoint(fLatitude, fLongitude, 4)) // func def in gpshandler.c
				// {
				// 	printk("\n\r");
				// 	printk("target inside fence\n\r");
				// 	printk("\n\r");
				// 	targetStatus = true;
				// }
			}

			if (IsNotificationenabled())
			{

				VisenseSensordataNotify(pucAdvBuffer + 2, ADV_BUFF_SIZE);
			}
			else if (!IsConnected() && !IsNotificationenabled())
			{
				// UpdateAdvertiseData();
				// StartAdvertising();
			}
			if ((sConfigData.flag & (1 << 4))) // check whether config data is read from the flash / updated from mobile at runtime
			{
				*pDiagData = *pDiagData & CONFIG_WRITE_OK; // added a diagnostic information to the application
			}
			else
			{
				*pDiagData = *pDiagData | CONFIG_WRITE_FAILED; // added a diagnostic information to the application
			}
#ifdef SLEEP_ENABLE
		}
		EnterSleepMode(GetSleepTime());
		ExitSleepMode();
		// printk("INFO: Syncing time with RTC\n\r");
		if (!GetTimeFromRTC())
		{
			printk("WARN: Getting time from RTC failed\n\r");
		}
#else
		k_msleep(100);
#endif
	}
	return 0;
}
/**
 * @brief Getting time from RTC
 * @param None
 * @return true for success
 */
static bool GetTimeFromRTC()
{
	long long llEpochNow = 0;
	bool bRetVal = false;
	uint32_t *pDiagData = NULL;
	pDiagData = GetDiagnosticData();

	if (GetCurrenTimeInEpoch(&llEpochNow))
	{
		printk("CurrentTime=%llu\n\r", llEpochNow);
		SetCurrentTime(llEpochNow);
		*pDiagData = *pDiagData & TIME_STAMP_OK;
		bRetVal = true;
	}
	else
	{
		*pDiagData = *pDiagData | TIME_STAMP_ERROR;
	}

	return bRetVal;
}
/**
 * @brief Write the configured time from BLE to RTC
 * @param None
 * @return true for success
 */
static bool WriteConfiguredtimeToRTC(void)
{
	bool bRetVal = false;
	int RetCode = 0;
	uint32_t *pDiagData = NULL;
	//pDiagData = GetDiagnosticData();

	if (GetTimeUpdateStatus())
	{
		if (InitRtc())
		{
			SetTimeUpdateStatus(false);
			sConfigData.flag = sConfigData.flag | (1 << 4); // set flag for timestamp config data update and store it into flash
			RetCode = nvs_write(&sConfigFs, 0, (char *)&sConfigData, sizeof(_sConfigData));
			if (RetCode < 0)
			{
				//*pDiagData = *pDiagData | CONFIG_WRITE_FAILED;
			}
			else
			{
				//*pDiagData = *pDiagData & CONFIG_WRITE_OK;
				//*pDiagData = *pDiagData & TIME_STAMP_OK;
				printk("Time updated\n");
				bRetVal = true;
			}
		}
		else
		{
			//*pDiagData = *pDiagData | TIME_STAMP_ERROR;
		}
	}

	return bRetVal;
}
/**
 * @brief Check for config change and update value from flash
 * @param None
 * @return true for success
 */
static bool CheckForConfigChange() // check for config change and update value from flash
{
	uint32_t ulRetCode = 0;
	bool bRetVal = false;
	uint32_t *pDiagData = NULL;
	pDiagData = GetDiagnosticData();

	nvs_initialisation(&sConfigFs, CONFIG_DATA_FS);
	k_msleep(100);
	ulRetCode = readJsonToFlash(&sConfigFs, 0, 0, (char *)&sConfigData, sizeof(sConfigData)); // read config params from the flash
	if (sConfigData.flag == 0)
	{
		printk("\n\rError occured while reading config data: %d\n", ulRetCode);
		*pDiagData = *pDiagData | CONFIG_WRITE_FAILED; // flag will shows error while reading config data from flash and added to the application
	}
	else
	{
		SetSleepTime(sConfigData.sleepTime);
		ulFlashidx = sConfigData.flashIdx;
		printk("sConfigFlag %d ,flashIdx = %d\n",
			   sConfigData.flag,
			   sConfigData.flashIdx);		   // get all the config params from the flash if a reboot occures
		SetFenceTable(&sConfigData.FenceData); // get coordinates from the flash if a reboot occures
		bRetVal = true;
	}

	return bRetVal;
}
/**
 * @brief Update Configurations if any config value is written via Ble
 * @param None
 * @return true for success
 */
static bool UpdateConfigurations()
{
	uint32_t ulRetCode = 0;
	bool bRetVal = false;

	if (IsSleepTimeSet())
	{
		sConfigData.sleepTime = GetSleepTime();
		SetSleepTimeSetStataus(false);
		sConfigData.flag = sConfigData.flag | (1 << 0); // set flag for config data update and store it into flash

		do
		{
			ulRetCode = nvs_write(&sConfigFs, 0, (char *)&sConfigData, sizeof(_sConfigData));

			if (ulRetCode < 0)
			{
				printk("ERROR: Write failed with ret code:%d\n", ulRetCode);
				break;
			}

			k_msleep(100);
			ulRetCode = nvs_read(&sConfigFs, 0, (char *)&sConfigData, sizeof(_sConfigData));

			if (ulRetCode < 0)
			{
				printk("ERROR: Write failed with ret code:%d\n", ulRetCode);
				break;
			}
			bRetVal = true;
		} while (0);
	}
	if (IsConfigLat() && IsConfiglon())
	{

		memcpy(&sConfigData.FenceData, GetFenceTable(), sizeof(GetFenceTable()));
		SetConfigLat(false);
		SetConfigLon(false);
		sConfigData.flag = sConfigData.flag | (1 << 1); // set flag for config data update and store it into flash
		do
		{
			ulRetCode = nvs_write(&sConfigFs, 0, (char *)&sConfigData, sizeof(_sConfigData));
		} while (0);
		bRetVal = true;

		return bRetVal;
	}
}