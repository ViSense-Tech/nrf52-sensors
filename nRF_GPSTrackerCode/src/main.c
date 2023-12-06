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
static bool InitBle();
static bool InitAllModules();
static bool GetAccelerometerDataAndUpdateJson(cJSON *pMainObject);
static bool DisplayAcclData(_sAcclData *psAcclData);
static void DisplaySOG(float fSOG);
static void DisplayLocation(double fLatitude, double fLongitude);
static void PrintBanner();
static bool UpdateConfigurations();
static bool SendHistoryDataToFlash(char *pcJsonBuffer);
static void DisplayFenceStatus();


/***************************GLOBAL VARIABLES******************************/
struct nvs_fs sConfigFs;
_sConfigData sConfigData = {0};
uint32_t ulFlashidx = 0; // flash idx init

/*************************FUNTION DEFINITION******************************/
/**
 * @brief  main function
 * @param  None
 * @return 0 on exit
 */
int main(void)
{
	float mSog = 0.00; // max sog limit init
	double fLatitude = 0.00;
	double fLongitude = 0.00;
	float fSOG = 0.00;
	long long TimeNow = 0, sysTime = 0;
	char *cJsonBuffer = NULL;
	char pcLocation[100];
	bool targetStatus = false; // flag to check geoFence
	uint8_t ucIdx = 0;
	uint8_t *pucAdvBuffer = NULL;
	char cFlashReadBuf[128] = {0};
	long long llEpochTime = 0;
	uint32_t *pDiagData = NULL;
	cJSON *pMainObject = NULL;

	PrintBanner();

	if (!InitAllModules())
	{
		printk("ERR: initialising modules failed\n\r");
	}

	if (!CheckForConfigChange())
	{
		printk("ERROR: Config change check failed \n\r");
	}

	pucAdvBuffer = GetAdvertisingBuffer();
	pDiagData = GetDiagnosticData();

	if (!GetTimeFromRTC())
	{
		printk("WARN: Getting time from RTC failed \n\r");
	}

	while (1)
	{

		pMainObject = cJSON_CreateObject();
		UpdateConfigurations();
		TimeNow = sys_clock_tick_get();

#ifdef SLEEP_ENABLE
		sysTime = sys_clock_tick_get();

		while (sys_clock_tick_get() - sysTime < (ALIVE_TIME * TICK_RATE))
		{
#endif
			while (sys_clock_tick_get() - TimeNow < COORD_READ_TIMEOUT)
			{
				if (ReadLocationData(pcLocation))
				{
					*pDiagData = *pDiagData & GPS_LOC_OK;
					if (ConvertNMEAtoCoordinates(pcLocation, &fLatitude, &fLongitude))
					{
						DisplayLocation(fLatitude, fLongitude);
					}
				}
			}
			if (!(*pDiagData & (1 << 4)))
			{
				memset(pcLocation, 0, sizeof(pcLocation));
				sprintf(pcLocation,"%f", fLatitude);
				AddItemtoJsonObject(&pMainObject, STRING, "Latitude", pcLocation, sizeof(pcLocation));
				memset(pcLocation, 0, sizeof(pcLocation));
				sprintf(pcLocation,"%f", fLongitude);				
				AddItemtoJsonObject(&pMainObject, STRING, "Longitude", pcLocation, sizeof(pcLocation));
			}
			

			TimeNow = sys_clock_tick_get();

			while (sys_clock_tick_get() - TimeNow < COORD_READ_TIMEOUT)
			{
				if (ReadSOGData(&fSOG))
				{
					printk("SOG: %f\n\r", fSOG);
					DisplaySOG(fSOG);
					AddItemtoJsonObject(&pMainObject, NUMBER, "SOG", &fSOG, sizeof(float));

					if (targetStatus && fSOG > mSog) // if device inside fence & crossed threshold values
					{
						printk("/n/r________________INSIDE FENCE_____________: %f\n\r", fSOG);
						DisplayFenceStatus();
					}
				}
			}

			if (!GetAccelerometerDataAndUpdateJson(pMainObject))
			{
				printk("ERR: Acceleromtr process failed\n\r");
			}

			WriteConfiguredtimeToRTC();
			if (GetCurrentTime(&llEpochTime))
			{
				AddItemtoJsonObject(&pMainObject, NUMBER, "TS", &llEpochTime, sizeof(long long));
			}
			printk("DIAG data : %d\n\r", *pDiagData);
			AddItemtoJsonObject(&pMainObject, NUMBER, "DIAG", pDiagData, sizeof(uint32_t));
			*pDiagData = *pDiagData | GPS_LOC_FAILED;
			cJsonBuffer = cJSON_Print(pMainObject);

			pucAdvBuffer[2] = 0x03;
			pucAdvBuffer[3] = (uint8_t)strlen(cJsonBuffer);
			memcpy(pucAdvBuffer + 4, cJsonBuffer, strlen(cJsonBuffer));

			SendHistoryDataToFlash(cJsonBuffer);


			if (IsFenceConfigured())
			{
				if (polygonPoint(fLatitude, fLongitude, 4)) // func def in gpshandler.c
				{
					printk("\n\r");
					printk("target inside fence\n\r");
					printk("\n\r");
					targetStatus = true;
				}
			}

			if (IsNotificationenabled())
			{
				VisenseSensordataNotify(pucAdvBuffer + 2, ADV_BUFF_SIZE);
			}
			else if (!IsConnected() && !IsNotificationenabled() && targetStatus)
			{
				writeJsonToExternalFlash(cJsonBuffer, ulFlashidx, WRITE_ALIGNMENT);
				readJsonFromExternalFlash(cFlashReadBuf, ulFlashidx, WRITE_ALIGNMENT);
				printk("\n\rcFlash read%s\n\r", cFlashReadBuf);
				ulFlashidx++;
				printk("flash count: %d\n\r", ulFlashidx);
			}

			if ((sConfigData.flag & (1 << 1))) // check whether config data is read from the flash / updated from mobile at runtime
			{
				*pDiagData = *pDiagData & CONFIG_WRITE_OK; // added a diagnostic information to the application
			}
			else
			{
				*pDiagData = *pDiagData | CONFIG_WRITE_FAILED; // added a diagnostic information to the application
			}
		
			printk("JSON:\n%s\n", cJsonBuffer);
			cJSON_Delete(pMainObject);
			cJSON_free(cJsonBuffer);	
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
	pDiagData = GetDiagnosticData();

	if (GetTimeUpdateStatus())
	{
		if (InitRtc())
		{
			SetTimeUpdateStatus(false);
			sConfigData.flag = sConfigData.flag | (1 << 4); // set flag for timestamp config data update and store it into flash
			RetCode = nvs_write(&sConfigFs, 0, (char *)&sConfigData, sizeof(_sConfigData));
			if (RetCode < 0)
			{
				*pDiagData = *pDiagData | CONFIG_WRITE_FAILED;
			}
			else
			{
				*pDiagData = *pDiagData & CONFIG_WRITE_OK;
				*pDiagData = *pDiagData & TIME_STAMP_OK;
				printk("Time updated\n");
				bRetVal = true;
			}
		}
		else
		{
			*pDiagData = *pDiagData | TIME_STAMP_ERROR;
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

	k_msleep(100);
	ulRetCode = ReadJsonFromFlash(&sConfigFs, 0, (char *)&sConfigData, sizeof(sConfigData)); // read config params from the flash
	if (sConfigData.flag == 0)
	{
		printk("\n\rError occured while reading config data: %d\n", ulRetCode);
		EraseExternalFlash(SECTOR_COUNT);
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
	_sConfigData ConfigData;
	_sFenceData *psFenceData = NULL;

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
			ulRetCode = nvs_read(&sConfigFs, 0, (char *)&ConfigData, sizeof(_sConfigData));

			if (ulRetCode < 0)
			{
				printk("ERROR: Write failed with ret code:%d\n", ulRetCode);
				break;
			}
			bRetVal = true;
		} while (0);
	}
	if (IsConfigLat() && IsConfigLon())
	{
		psFenceData = malloc(sizeof(_sFenceData));
		psFenceData = GetFenceTable();
		memcpy(&sConfigData.FenceData, psFenceData, sizeof(_sFenceData));
		SetConfigChangeLon(false);
		SetConfigChangeLat(false);
		sConfigData.flag = sConfigData.flag | (1 << 1); // set flag for config data update and store it into flash
		do
		{
			ulRetCode = nvs_write(&sConfigFs, 0, (char *)&sConfigData, sizeof(_sConfigData));

			if (ulRetCode <= 0)
			{
				printk("ERR: Write failed\n\r");
				break;
			}
			
			free(psFenceData);
		} while (0);

		bRetVal = true;

		return bRetVal;
	}
}

/**
 * @brief  : Initaialise BLE module
 * @param  : None
 * @return : true for success
 * 
*/
static bool InitBle()
{
	bool bRetVal = false;
	int Ret = 0;

	do
	{
		if (!EnableBLE())
		{
			printk("ERR: Enabling ble failed \n\r");
			break;
		}

		if (StartAdvertising())
		{
			printk("ERR: Advertising failed to start (err %d)\n", Ret);
			break;
		}

		bRetVal = true;
	} while (0);

	return bRetVal;
	
}

/**
 * @brief  : Initialise all modules 
 * @param  : None
 * @return : true for success 
*/
static bool InitAllModules()
{
	bool bRetVal = false;

	do
	{
		InitLCD();
		InitTimer();

		if (!InitBle())
		{
			printk("ERR: Ble initialisation failed\n\r");
			break;
		}
		if (!InitUart())
		{
			printk("ERR: Device not initialised\n\r");
			break;
		}

		if (!InitRtc())
		{
			printk("WARN: RTC init failed\n\r");
			break;
		}

		if (FlashInit(&sConfigFs, CONFIG_DATA_FS) == 0)
		{
			printk("ERR: Flashinit failed\n\r");
			break;
		}

		bRetVal = true;
	} while (0);
	
	return bRetVal;
}

/**
 * @brief : Display Location data in LCD
 * @param : fLatitude  : Latitude coordinate in decimal degrees
 * 			fLongitude : Longitude coordinate in decimal degrees
 * @return : None
*/
static void DisplayLocation(double fLatitude, double fLongitude)
{
	char cLCDMessage[50] = {0};

	WriteLCDCmd(0x01); // Clear
	SetLCDCursor(1, 1);
	k_usleep(10);
	printk("Latitude: %fN Longitude: %fE\n\r", fLatitude, fLongitude);
	memset(cLCDMessage,'\0', sizeof(cLCDMessage));
	sprintf(cLCDMessage, "Lat:%f", fLatitude);
	printk("Msg: %s\n\r", cLCDMessage);
	WriteStringToLCD(cLCDMessage);

	memset(cLCDMessage,'\0', sizeof(cLCDMessage));
	SetLCDCursor(2, 1);
	sprintf(cLCDMessage, "Lon:%f", fLongitude);
	printk("Msg: %s\n\r", cLCDMessage);
	WriteStringToLCD(cLCDMessage);
	k_sleep(K_MSEC(200));
}

/**
 * @brief  Display fence status in LCD
 * @param  None
 * @return None
*/
static void DisplayFenceStatus()
{
	char cLCDMessage[50] = {0};

	WriteLCDCmd(0x01); // Clear
	SetLCDCursor(1, 1);

	strcpy(cLCDMessage, "INSIDE-FENCE");
	WriteStringToLCD(cLCDMessage);
	k_sleep(K_MSEC(500));
}

/**
 * @brief  : Display SOG value in LCD
 * @param  : fSOG : Speed over Ground value
 * @return : None
*/
static void DisplaySOG(float fSOG)
{
	char cLCDMessage[50] = {0};

	WriteLCDCmd(0x01); // Clear
	SetLCDCursor(0, 1);
	k_usleep(10);
	
	memset(cLCDMessage,'\0', sizeof(cLCDMessage));
	sprintf(cLCDMessage, "SOG:%f", fSOG);
	WriteStringToLCD(cLCDMessage);
	k_sleep(K_MSEC(200));
}

/**
 * @brief : Display x, y, z accelerometer data in LCD
 * @param : psAcclData : accelerometer data
 * @return : true for success
*/
static bool DisplayAcclData(_sAcclData *psAcclData)
{
	char cLCDMessage[30] = {0};
	bool bRetVal = false;

	if (psAcclData)
	{
		WriteLCDCmd(0x01);
		SetLCDCursor(1, 1);
		k_usleep(10);
		sprintf(cLCDMessage, "X:%d",
				psAcclData->unAccX);
		WriteStringToLCD(cLCDMessage);
		k_sleep(K_MSEC(300));
		memset(cLCDMessage,'\0', sizeof(cLCDMessage));
		SetLCDCursor(1, 9);
		k_usleep(10);
		sprintf(cLCDMessage, "Y:%d",
		psAcclData->unAccY);
		WriteStringToLCD(cLCDMessage);
			memset(cLCDMessage,'\0', sizeof(cLCDMessage));
		SetLCDCursor(2, 1);
			k_usleep(10);
		sprintf(cLCDMessage, "Z:%d",
				psAcclData->unAccZ);
		WriteStringToLCD(cLCDMessage);
		k_sleep(K_MSEC(300));
		bRetVal = true;
	}

	return bRetVal;
}

/**
 * @brief  : Read from accelerometer and update JSON 
 * @param  : pMainObject : json object
 * @return : true for success 
*/
static bool GetAccelerometerDataAndUpdateJson(cJSON *pMainObject)
{
	bool bRetVal = false;
	_sAcclData sAcclData = {0};

	do
	{
		if (!InitAcclerometer())
		{
			printk("ERR: Acclmtr not initialised\n\r");
			break;
		}

		if (ReadFromAccelerometer(&sAcclData))
		{
			printk("AccX: %d\n\r AccY: %d\n\r AccZ:%d\n\r",
					sAcclData.unAccX,
					sAcclData.unAccY,
					sAcclData.unAccZ);

			if (!DisplayAcclData(&sAcclData))
			{
				printk("ERR: displaying acceleromtr data failed\n\r");
				break;
			}

			if (!AddItemtoJsonObject(&pMainObject, NUMBER, "AccX", &sAcclData.unAccX, sizeof(float)))
			{
				printk("ERR: Adding X value to JSON failed\n\r");
				break;
			}
			
			if (!AddItemtoJsonObject(&pMainObject, NUMBER, "AccY", &sAcclData.unAccY, sizeof(float)))
			{
				printk("ERR: Adding Y value to JSON failed\n\r");
				break;
			}

			if (!AddItemtoJsonObject(&pMainObject, NUMBER, "AccZ", &sAcclData.unAccZ, sizeof(float)))
			{
				printk("ERR: Adding Z value to JSON failed\n\r");
				break;
			}

		}
		else
		{
			printk("ERR: Reading from Acceleromtr failed\n\r");
			break;
		}

		bRetVal = true;
	} while (0);

	return bRetVal;
}

/**
 * @brief History notification function
 * @param pcJsonBuffer : History data to notify
 * @return true for success
*/
static bool SendHistoryDataToFlash(char *pcJsonBuffer)
{
 
    char cBuffer[WRITE_ALIGNMENT];
    bool bRetval = false;
 
 
    if (pcJsonBuffer)
    {
        if(!IsConnected()) // && sConfigData.flag & (1 << 4) can include this condition also if config is mandetory during initial setup
        {
           
            memset(cBuffer, '\0', sizeof(cBuffer));
            memcpy(cBuffer, pcJsonBuffer, strlen(pcJsonBuffer));
            if(writeJsonToExternalFlash(cBuffer, ulFlashidx, WRITE_ALIGNMENT))
            {
                // NO OP
            }
            k_msleep(50);
            if (readJsonFromExternalFlash(cBuffer, ulFlashidx, WRITE_ALIGNMENT))
            {
                printk("\nId: %d, Stored_Data: %s\n",ulFlashidx, cBuffer);
            }
            ulFlashidx++;
            sConfigData.flashIdx = ulFlashidx;
            nvs_write(&sConfigFs, 0, (char *)&sConfigData, sizeof(_sConfigData));
            if(ulFlashidx>= NUMBER_OF_ENTRIES)
            {
                ulFlashidx = 0;
            }
        }
 
 
        if(IshistoryNotificationenabled() && IsConnected())
        {
            printk("In history notif\n\r");
            if (VisenseHistoryDataNotify(ulFlashidx))
            {
                ulFlashidx = 0;
                sConfigData.flashIdx = ulFlashidx;
                nvs_write(&sConfigFs, 0, (char *)&sConfigData, sizeof(_sConfigData));
            }
        }
 
        bRetval = true;
    }
 
    return bRetval;
}

/**
 * @brief  printing visense banner
 * @param  None
 * @return None
*/
static void PrintBanner()
{
    printk("\n\r");
    printk("'##::::'##:'####::'######::'########:'##::: ##::'######::'########:\n\r");
    k_msleep(50);
    printk("##:::: ##:. ##::'##... ##: ##.....:: ###:: ##:'##... ##: ##.....::\n\r");
    k_msleep(50);
    printk("##:::: ##:: ##:: ##:::..:: ##::::::: ####: ##: ##:::..:: ##:::::::\n\r");
    k_msleep(50);
    printk("##:::: ##:: ##::. ######:: ######::: ## ## ##:. ######:: ######:::\n\r");
    k_msleep(50);
    printk(". ##:: ##::: ##:::..... ##: ##...:::: ##. ####::..... ##: ##...::::\n\r");
    k_msleep(50);
    printk(":. ## ##:::: ##::'##::: ##: ##::::::: ##:. ###:'##::: ##: ##:::::::\n\r");
    k_msleep(50);
    printk("::. ###::::'####:. ######:: ########: ##::. ##:. ######:: ########:\n\r");
    k_msleep(50);
    printk(":::...:::::....:::......:::........::..::::..:::......:::........::\n\r");
    k_msleep(50);
    printk("\n\r");
}