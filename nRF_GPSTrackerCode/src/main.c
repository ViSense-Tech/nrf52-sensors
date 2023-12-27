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
#ifdef PMIC_ENABLED
#include "PMIC/PMICHandler.h"
#endif

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
static void SendConfigDataToApp();
static void ReadAndProcessLocationData(void);
static void ReadAndProcessSOGData(void);
static void SendLiveDataToApp();
static void UpdateTimeAndDiagData();


/***************************GLOBAL VARIABLES******************************/
static struct nvs_fs sConfigFs;
static uint32_t ulFlashidx = 0; // flash idx init
static cJSON *pMainObject = NULL;
static char *cJsonBuffer = NULL;


/*************************FUNTION DEFINITION******************************/
/**
 * @brief  main function
 * @param  None
 * @return 0 on exit
 */
int main(void)
{

#ifdef 	SLEEP_ENABLE
	long long sysTime;
#endif
	uint8_t *pucAdvBuffer = NULL;
	int *pDiagData = NULL;

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

#ifdef SLEEP_ENABLE
		sysTime = sys_clock_tick_get();

		while (sys_clock_tick_get() - sysTime < (ALIVE_TIME * TICK_RATE))
		{
#endif
			pMainObject = cJSON_CreateObject();
			UpdateConfigurations();
			WriteConfiguredtimeToRTC();
			ReadAndProcessLocationData();
			ReadAndProcessSOGData();

			if (!GetAccelerometerDataAndUpdateJson(pMainObject))
			{
				printk("ERR: Acceleromtr process failed\n\r");
			}

			SendConfigDataToApp();
			UpdateTimeAndDiagData();
			SendHistoryDataToFlash(cJsonBuffer);
			SendLiveDataToApp();

			if(GetConfigStatus())
			{
				ParseFenceData();	
				ParseRcvdData();
				SetConfigStatus(false);
			}

#ifdef SLEEP_ENABLE
		}
		 EnterSleepMode(GetSleepTime());
		 ExitSleepMode();

		printk("INFO: Syncing time with RTC\n\r");
		if (!GetTimeFromRTC())
		{
			printk("WARN: Getting time from RTC failed\n\r");
		}
		k_msleep(100);
#else
		k_msleep(100);
#endif
	}
	return 0;
}

static void UpdateTimeAndDiagData()
{
	uint8_t *pucAdvBuffer = NULL;
	long long llEpochTime = 0;
#ifdef PMIC_ENABLED	
	float fSOC = 0.0;
#endif	
	int *pDiagData = NULL;
#ifdef PMIC_ENABLED	
	char cBuffer[30];
#endif
	pucAdvBuffer = GetAdvertisingBuffer();
	pDiagData = GetDiagnosticData();

	if (GetCurrentTime(&llEpochTime))
	{
		AddItemtoJsonObject(&pMainObject, NUMBER, "TS", &llEpochTime, sizeof(long long));
	}
	printk("DIAG data : %d\n\r", *pDiagData);
	AddItemtoJsonObject(&pMainObject, NUMBER, "DIAG", pDiagData, sizeof(uint32_t));
	*pDiagData = *pDiagData | GPS_LOC_FAILED;
	cJsonBuffer = cJSON_Print(pMainObject);

#ifdef PMIC_ENABLED	
	PMICUpdate(&fSOC);
	memset(cBuffer, '\0', sizeof(cBuffer));
	printk("soc=%f\n\r", fSOC);
	sprintf(cBuffer,"%d%%", (int)fSOC);
	AddItemtoJsonObject(&pMainObject, STRING, "Batt", cBuffer, sizeof(float));
#endif	

	pucAdvBuffer[2] = 0x03;
	pucAdvBuffer[3] = (uint8_t)strlen(cJsonBuffer);
	memcpy(pucAdvBuffer + 4, cJsonBuffer, strlen(cJsonBuffer));
}

/**
 * @brief Send Live data to application
 * @param None
 * @return None
*/
static void SendLiveDataToApp()
{
	//char cFlashReadBuf[128] = {0};
	uint8_t *pucAdvBuffer = NULL;
	int *pDiagData = NULL;
	_sConfigData *psConfigData = NULL;

	psConfigData = GetConfigData();
	pucAdvBuffer = GetAdvertisingBuffer();
	pDiagData = GetDiagnosticData();

	if (IsNotificationenabled())
	{
		VisenseSensordataNotify(pucAdvBuffer + 2, ADV_BUFF_SIZE);
	}
	else if (!IsConnected() && !IsNotificationenabled() && IsDeviceInsideofFence())
	{
		writeJsonToExternalFlash(cJsonBuffer, ulFlashidx, WRITE_ALIGNMENT);
		// readJsonFromExternalFlash(cFlashReadBuf, ulFlashidx, WRITE_ALIGNMENT);
		// printk("\n\rcFlash read%s\n\r", cFlashReadBuf);
		// ulFlashidx++;
		// printk("flash count: %d\n\r", ulFlashidx);
	}

	if ((psConfigData->flag & (1 << 1))) // check whether config data is read from the flash / updated from mobile at runtime
	{
		*pDiagData = *pDiagData & CONFIG_WRITE_OK; // added a diagnostic information to the application
	}
	else
	{
		*pDiagData = *pDiagData | CONFIG_WRITE_FAILED; // added a diagnostic information to the application
	}

	printk("JSON:\n%s\n", cJsonBuffer);
	cJSON_free(cJsonBuffer);
	cJSON_Delete(pMainObject);
	memset(pucAdvBuffer, 0, 300);
}

/**
 * @brief Read and process SOG data
 * @param None
 * @return None
*/
static void ReadAndProcessSOGData(void)
{
	float mSog = 0.00; // max sog limit init
	float fSOG = 0.00;
	long long TimeNow = 0;
	int *pDiagData = NULL;

	pDiagData = GetDiagnosticData();
	TimeNow = sys_clock_tick_get();

	while (sys_clock_tick_get() - TimeNow < SOG_READ_TIMEOUT)
	{
		if (ReadSOGData(&fSOG))
		{
			fSOG = fSOG * 1.51; /*knots to mph calculation*/
			printk("SOG: %f\n\r", fSOG);
			DisplaySOG(fSOG);
			AddItemtoJsonObject(&pMainObject, FLOAT, "SOG", &fSOG, sizeof(fSOG));

			if (IsDeviceInsideofFence() && fSOG > mSog) // if device inside fence & crossed threshold values
			{
				printk("/n/r________________INSIDE FENCE_____________: %f\n\r", fSOG);
				DisplayFenceStatus();
			}
			break;
		}
	}
}

/**
 * @brief Read and process Location data
 * @param None
 * @return None
*/
static void ReadAndProcessLocationData(void)
{
	long long TimeNow = 0;
	double fLatitude = 0.00;
	double fLongitude = 0.00;
	char pcLocation[50];
	int *pDiagData = NULL;

	pDiagData = GetDiagnosticData();
	TimeNow = sys_clock_tick_get();

	while (sys_clock_tick_get() - TimeNow < COORD_READ_TIMEOUT)
	{
		if (ReadLocationData(pcLocation))
		{
			*pDiagData = *pDiagData & GPS_LOC_OK;
			if (ConvertNMEAtoCoordinates(pcLocation, &fLatitude, &fLongitude))
			{
				DisplayLocation(fLatitude, fLongitude);
			}
			break;
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

	if (IsFenceConfigured())
	{
		if (polygonPoint(fLatitude, fLongitude, 4)) // func def in gpshandler.c
		{
			printk("\n\r");
			printk("target inside fence\n\r");
			printk("\n\r");
		}
	}
}

/**
 * @brief send config data to application over ble
 * @param None
 * @return None
*/
static void SendConfigDataToApp()
{
    cJSON *pConfigObject = NULL;
    char *cJsonConfigBuffer = NULL;
	_sFenceData *psFenceData = NULL;
    uint32_t ulSleepTime = 0;
	int ucCoordCount = 0;
	uint8_t ucIdx = 0;
    char cBuffer[30] =  {0};
	uint8_t cKeyBuff[10] = {0};

    pConfigObject = cJSON_CreateObject();
    ulSleepTime = GetSleepTime();
    sprintf(cBuffer, "%ds", ulSleepTime);
    AddItemtoJsonObject(&pConfigObject, STRING, "Sleep", cBuffer, strlen(cBuffer));
	ucCoordCount = GetCoordCount();
	AddItemtoJsonObject(&pConfigObject, NUMBER, "cc", &ucCoordCount, sizeof(ucCoordCount));
   	psFenceData = GetFenceTable();
	for (ucIdx=0; ucIdx < ucCoordCount; ucIdx++)
	{
		sprintf(cKeyBuff, "Lat%d", ucIdx+1);
		sprintf(cBuffer, "%f", psFenceData->dLatitude);
		AddItemtoJsonObject(&pConfigObject, STRING, cKeyBuff, cBuffer, strlen(cBuffer));
		memset(cKeyBuff, 0, sizeof(cKeyBuff));
		memset(cBuffer, 0, sizeof(cBuffer));
		sprintf(cKeyBuff, "Lon%d", ucIdx+1);
		sprintf(cBuffer, "%f", psFenceData->dLongitude);
		AddItemtoJsonObject(&pConfigObject, STRING, cKeyBuff, cBuffer, strlen(cBuffer));		
	}

	cJsonConfigBuffer = cJSON_Print(pConfigObject);
    printk("ConfigJSON:\n%s\n", cJsonConfigBuffer);

    if (IsConfigNotifyEnabled())
    {
        VisenseConfigDataNotify(cJsonConfigBuffer, (uint16_t)strlen(cJsonConfigBuffer));
    }

    cJSON_free(cJsonConfigBuffer);
    cJSON_Delete(pConfigObject);
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
	_sConfigData *psConfigData = NULL;

	psConfigData = GetConfigData();
	pDiagData = GetDiagnosticData();

	if (GetTimeUpdateStatus())
	{
		if (InitRtc())
		{
			SetTimeUpdateStatus(false);
			psConfigData->flag = psConfigData->flag | (1 << 4); // set flag for timestamp config data update and store it into flash
			RetCode = nvs_write(&sConfigFs, 0, (char *)psConfigData, sizeof(_sConfigData));
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
	uint8_t ucIdx = 0;
	bool bRetVal = false;
	uint32_t *pDiagData = NULL;
	_sConfigData *psConfigData = NULL;

	psConfigData = GetConfigData();
	pDiagData = GetDiagnosticData();

	k_msleep(100);
	ulRetCode = ReadJsonFromFlash(&sConfigFs, 0, (char *)psConfigData, sizeof(_sConfigData)); // read config params from the flash
	if (psConfigData->flag == 0)
	{
		printk("\n\rError occured while reading config data: %d\n", ulRetCode);
		EraseExternalFlash(SECTOR_COUNT);
		*pDiagData = *pDiagData | CONFIG_WRITE_FAILED; // flag will shows error while reading config data from flash and added to the application
	}
	else
	{
		SetCurrentTime(psConfigData->lastUpdatedTime);
		SetSleepTime(psConfigData->sleepTime);
		ulFlashidx = psConfigData->flashIdx;
		printk("sConfigFlag %d ,flashIdx = %d\n CC=%d",
			   psConfigData->flag,
			   psConfigData->flashIdx,
			   psConfigData->ucCoordCount);		   // get all the config params from the flash if a reboot occures
		SetFenceTable(&psConfigData->FenceData[0]); // get coordinates from the flash if a reboot occures
		for (ucIdx = 0; psConfigData->ucCoordCount > ucIdx ; ucIdx++)
		{
			printk("Lat: %f Lon: %f\n\r", 
			psConfigData->FenceData[ucIdx].dLatitude, psConfigData->FenceData[ucIdx].dLongitude);
		}
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
	int32_t ulRetCode = 0;
	bool bRetVal = false;
	_sFenceData *psFenceData = NULL;
	_sConfigData *psConfigData = NULL;

	psConfigData = GetConfigData();
	if (IsSleepTimeSet())
	{
		psConfigData->sleepTime = GetSleepTime();
		SetSleepTimeSetStataus(false);
		psConfigData->flag = psConfigData->flag | (1 << 0); // set flag for config data update and store it into flash

		do
		{
			ulRetCode = nvs_write(&sConfigFs, 0, (char *)psConfigData, sizeof(_sConfigData));

			if (ulRetCode < 0)
			{
				printk("ERROR: Write failed with ret code:%d\n", ulRetCode);
				break;
			}

			k_msleep(100);
			ulRetCode = nvs_read(&sConfigFs, 0, (char *)psConfigData, sizeof(_sConfigData));

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
		psFenceData = GetFenceTable();
		psConfigData->ucCoordCount = GetCoordCount();
		memcpy(psConfigData->FenceData, psFenceData, sizeof(_sFenceData) * psConfigData->ucCoordCount);
		//free(psFenceData);
		// for (uint8_t ucIdx = 0; psConfigData->ucCoordCount > ucIdx ; ucIdx++)
		// {
		// 	printk("\n\rUCLat: %f UCLon: %f\n\r", 
		// 	psConfigData->FenceData[ucIdx].dLatitude, psConfigData->FenceData[ucIdx].dLongitude);
		// 	//psFenceData++;
		// }	
		SetConfigChangeLon(false);
		SetConfigChangeLat(false);
		
		psConfigData->flag = psConfigData->flag | (1 << 1); // set flag for config data update and store it into flash
		
		do
		{		

			ulRetCode = nvs_write(&sConfigFs, 0, (char *)psConfigData, sizeof(_sConfigData));

			if (ulRetCode <= 0)
			{
				printk("ERR: Write failed\n\r");
				break;
			}

			bRetVal = true;

		} while (0);
	}

	
	return bRetVal;
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
#ifdef PMIC_ENABLED		
		PMICInit();
#endif		

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

		if (FlashInit(&sConfigFs, CONFIG_DATA_FS) != 0)
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
	_sConfigData *psConfigData = NULL;
 
 	psConfigData = GetConfigData();

    if (pcJsonBuffer)
    {
        if(!IsConnected()) // && psConfigData->flag & (1 << 4) can include this condition also if config is mandetory during initial setup
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
            psConfigData->flashIdx = ulFlashidx;
            nvs_write(&sConfigFs, 0, (char *)psConfigData, sizeof(_sConfigData));
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
                psConfigData->flashIdx = ulFlashidx;
                nvs_write(&sConfigFs, 0, (char *)psConfigData, sizeof(_sConfigData));
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