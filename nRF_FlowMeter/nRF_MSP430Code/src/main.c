/**
 * @file   main.c
 * @brief  This is a GPSTracker application
 * @date   15-10-2023
 * @author Adhil
*/

/************************INCLUDES***************************/
#include "UartHandler.h"
#include "BleHandler.h"
#include "BleService.h"
#include "JsonHandler.h"
#include "TimerHandler.h"
#include "FlashHandler.h"
#include "SystemHandler.h"
#include "PMIC/PMICHandler.h"
#include "Common.h"
#include "MeshHandler.h"

/*************************MACROS****************************/
//#define SLEEP_ENABLE  //Uncomment this line to enable sleep functionality
#define TIME_STAMP_ERROR   (1<<1)
#define TIME_STAMP_OK      ~(1<<1)
/*************************TYPEDEFS***************************/

/*************************GLOBALS***************************/
cJSON *pcData = NULL;
uint8_t ucNotifyBuffer[210];
int32_t lDiagnosticdata = 0; 
_sConfigData sConfigData = {0};
struct nvs_fs fs;    //file system
struct nvs_fs sConfigFs;
uint32_t ulFlashIdx = 0;  // initialise data counter

/*************************FUNTION DECLARATION*****************/
static bool InitPowerManager();
static void InitDataPartition();
static bool InitBle();
static void PrintBanner();
static bool InitAllModules();
static bool WriteConfiguredtimeToRTC(void);
static bool GetTimeFromRTC();
static bool UpdateConfigurations();
static bool CheckForConfigChange();
static void SendConfigDataToApp();
static bool SendHistoryDataToApp(char *pcBuffer, uint16_t unLength);

/*************************FUNTION DEFINITION*****************/
/**
 * @brief  main function
 * @param  None
 * @return 0 on exit
*/
int main(void)
{
	int Ret = 0;
	long long TimeNow = 0, llEpochNow;
	uint8_t ucIdx = 0;
	uint8_t *pucAdvBuffer = NULL;
	char *cJsonBuffer = NULL;
    char cFlashReadBuf[350];
	char cBuffer[30];
#ifdef PMIC_ENABLED    
    float fSOC = 0.0;
#endif    
    char *pcEnd = NULL;
	double dFlowRate = 0.0;
    cJSON * pMainObject = NULL;

	PrintBanner();
    printk("VISENSE_FLOWMTR_FIRMWARE_VERSION: %s\n\r", VISENSE_FLOWMTR_FIRMWARE_VERSION);
    k_msleep(1000);
    printk("FEATURES: %s", VISENSE_FLOWMTR_FEATURES);
    k_msleep(1000);
    printk("\n\r");

	if (!InitAllModules())
    {
        printk("ERROR: Initialising all modules failed \n\r");
    }

    // if (!CheckForConfigChange())
    // {
    //     printk("ERROR: Config check failed\n\r");
    // }    

    if (!GetTimeFromRTC())
    {
        printk("WARN: Getting time from RTC failed\n\r");
    }

	while(1)
	{
	#ifdef SLEEP_ENABLE	
		TimeNow = sys_clock_tick_get();

		while(sys_clock_tick_get() - TimeNow < (ALIVE_TIME * TICK_RATE))
		{
	#endif		
            if (UpdateConfigurations())
            {
                printk("INFO: Updating config \n\r");           
            }

            WriteConfiguredtimeToRTC();
            SendConfigDataToApp();

			pMainObject = cJSON_CreateObject();
			memset(ucNotifyBuffer, 0, ADV_BUFF_SIZE);
			ucNotifyBuffer[0] = FLOW_METER;

			if (IsRxComplete())
			{
				strcpy(cBuffer, GetFlowRate());
                printk("flowrate test %s\n\r", cBuffer);
                //dFlowRate = strtod(cBuffer, pcEnd);
                //sscanf( cBuffer, "$Flowrate: %f", &dFlowRate);
                pcEnd = strchr(cBuffer, ':');
                pcEnd = pcEnd+2;
                strcpy(cBuffer, pcEnd);
                
                //printk("double value: %s\n\r",cBuffer);
				dFlowRate = atof(cBuffer);
                printk("flow: %f\n\r",dFlowRate);
                if (dFlowRate <= GetMinGPM())
                {
                    printk("WARN: flowrate is below minGPM\n\r");
                }
				memset(cBuffer, 0, sizeof(cBuffer));
				sprintf(cBuffer, "%f", dFlowRate);
                
				AddItemtoJsonObject(&pMainObject, NUMBER_FLOAT, "FlowRate", &dFlowRate, sizeof(float));
				SetRxStatus(false);
			}
            else
            {
                printk("Not ecieved data from msp\n\r");
            }

			if (GetCurrentTime(&llEpochNow))
			{
				AddItemtoJsonObject(&pMainObject, NUMBER_INT, "TS", &llEpochNow, sizeof(long long));
			}
#ifdef PMIC_ENABLED            
			PMICUpdate(&fSOC);
            memset(cBuffer, '\0', sizeof(cBuffer));
            printk("soc=%f\n\r", fSOC);
            sprintf(cBuffer,"%d%%", (int)fSOC);
            AddItemtoJsonObject(&pMainObject, STRING, "Batt", cBuffer, sizeof(float));
#endif            
			cJsonBuffer = cJSON_Print(pMainObject);
            SendHistoryDataToApp(cJsonBuffer, strlen(cJsonBuffer));

			strcpy((char *)ucNotifyBuffer+2, cJsonBuffer);
			ucNotifyBuffer[1] = (uint8_t)strlen((char *)ucNotifyBuffer+2);
			printk("packet:%s\n\r", (char *)ucNotifyBuffer);

			if(IsNotificationenabled())
			{
				VisenseSensordataNotify(ucNotifyBuffer, ADV_BUFF_SIZE);
			}
            else if (!IsConnected() && !IsNotificationenabled() && !IsSupervisorLiveNotifyEnable())
			{
				writeJsonToExternalFlash(cJsonBuffer, ulFlashIdx, WRITE_ALIGNMENT);
				readJsonFromExternalFlash(cFlashReadBuf, ulFlashIdx, WRITE_ALIGNMENT);
				printk("\n\rcFlash read%s\n\r", cFlashReadBuf);
				ulFlashIdx++;
				printk("flash count: %d\n\r", ulFlashIdx);
			}
            if (IsSupervisorLiveNotifyEnable())
            {
                if (SendLiveDataToSupervisor(cJsonBuffer, strlen(cJsonBuffer)))
                {
                    printk("INFO: LiveData sent to Supervisor\n\r");
                }
                
            }

			cJSON_Delete(pMainObject);
			cJSON_free(cJsonBuffer);
			k_msleep(200);
		#ifdef SLEEP_ENABLE	
		}
		EnterSleepMode(GetSleepTime());
        ExitSleepMode();
        //printk("INFO: Syncing time with RTC\n\r");
        if (!GetTimeFromRTC())
        {
            printk("WARN: Getting time from RTC failed\n\r");
        }
		#else
			k_msleep(1000);
		#endif
	}

	return 0;
}

/**
 * @brief initialise data partitions
 * @param None
 * @return None
*/
static void InitDataPartition()
{
    // nvs_initialisation(&fs, DATA_FS); 
    SetFileSystem(&fs);
}

/**
 * @brief Initialise power manager module
 * @param None
 * @return true for success
*/
static bool InitPowerManager()
{
    bool bRetVal = false;

    bRetVal = SetPMState();

    return bRetVal;
}

/**
 * @brief Initialise BLE functions
 * @param None
 * @return true for success
*/
static bool InitBle()
{
    bool bRetVal = false;
    int nError = 0;

    do
    {

        if (!EnableBLE())
        {
            printk("Bluetooth init failed (err %d)\n", nError);
            break;
        }
        // nError = StartAdvertising();
        if (nError)
        {
            printk("Advertising failed to create (err %d)\n", nError);
            break;
        }
        bRetVal = true;
    } while (0);
    
    return bRetVal;
}

/**
 * @brief Init all modules RTC, BLE,.. etc
 * @param None
 * @return true for success
*/
static bool InitAllModules()
{
    bool bRetVal = false;

    do
    {
		if(!InitPowerManager()) 
		{
			printk("ERROR: Init PM failed\n\r");
			break;
		}
#ifdef PMIC_ENABLED        
        PMICInit();
#endif        
		InitTimer();
		k_sleep(K_TICKS(100));

		// InitDataPartition();

		if (!InitUart())
		{
			printk("Device not initialised\n\r");
			break;
		}

		if (!InitBle())
		{
			printk("ERROR: Init BLE failed\n\r");
			break;       
		}
		bRetVal = true;
    } while (0);
    
    return bRetVal;
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

    if (GetCurrenTimeInEpoch(&llEpochNow))
    {
        printk("CurrentTime=%llu\n\r", llEpochNow);
        SetCurrentTime(llEpochNow);
		/*Need to add the diagnostics here*/
        // lDiagnosticdata = lDiagnosticdata & TIME_STAMP_OK;
        bRetVal = true;
    }
    else
    {
        //lDiagnosticdata = lDiagnosticdata | TIME_STAMP_ERROR;
    }

    return bRetVal;
}

/**
 * @brief Check for config change and update value from flash
 * @param None
 * @return true for success
*/
static bool CheckForConfigChange()
{
    uint32_t ulRetCode = 0;
    bool bRetVal = false;
    uint32_t *uFlashIdx = NULL;

    uFlashIdx = GetFlashCounter();
    nvs_initialisation(&sConfigFs, CONFIG_DATA_FS); 
    k_msleep(100);
    ulRetCode = readJsonToFlash(&sConfigFs, 0, 0, (char *)&sConfigData, sizeof(sConfigData)); // read config params from the flash
    if(sConfigData.flag == 0) 
    {
        printk("\n\rError occured while reading config data: %d\n", ulRetCode);
        EraseExternalFlash(SECTOR_COUNT);
       // lDiagnosticdata = lDiagnosticdata | (1<<4); // flag will shows error while reading config data from flash and added to the application
    }
    else
    {
        SetSleepTime(sConfigData.sleepTime);
        *uFlashIdx = sConfigData.flashIdx;
        printk("sConfigFlag %d ,flashIdx = %d\n",
                                     sConfigData.flag,
                                     sConfigData.flashIdx); //get all the config params from the flash if a reboot occures

        bRetVal = true;
    }

    return bRetVal;
}

/**
 * @brief Sending history data over ble
 * @param pcBuffer : data to send
 * @param unLength : Length of data
 * @return None
*/
static bool SendHistoryDataToApp(char *pcBuffer, uint16_t unLength)
{

    char cBuffer[ADV_BUFF_SIZE];
    bool bRetval = false;
    uint32_t *uFlashIdx = NULL;

    uFlashIdx = GetFlashCounter();


    if (pcBuffer)
    {
        if(!IsConnected()) // && sConfigData.flag & (1 << 4) can include this condition also if config is mandetory during initial setup
        {
            
            memset(cBuffer, '\0', sizeof(cBuffer));
            memcpy(cBuffer, pcBuffer, unLength);
            if(writeJsonToExternalFlash(cBuffer, *uFlashIdx,WRITE_ALIGNMENT))
            {
                // NO OP
            }
            k_msleep(50);
            if (readJsonFromExternalFlash(cBuffer, *uFlashIdx, WRITE_ALIGNMENT))
            {
                printk("\nId: %d, Stored_Data: %s\n",*uFlashIdx, cBuffer);
            }
            *uFlashIdx = *uFlashIdx + 1;
            sConfigData.flashIdx = *uFlashIdx;
            nvs_write(&sConfigFs, 0, (char *)&sConfigData, sizeof(_sConfigData));
            if(*uFlashIdx>= NUMBER_OF_ENTRIES)
            {
                *uFlashIdx = 0;
            }
        }
 

        // if(IshistoryNotificationenabled() && IsConnected())
        // {
        //     VisenseHistoryDataNotify();
        //     *uFlashIdx = 0; 
        // }

        bRetval = true;
    }

    return bRetval;
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

    if (GetTimeUpdateStatus())
    {
        if (InitRtc())
        {
            SetTimeUpdateStatus(false); 
            sConfigData.flag = sConfigData.flag | (1 << 4); //set flag for timestamp config data update and store it into flash
            RetCode = nvs_write(&sConfigFs, 0, (char *)&sConfigData, sizeof(_sConfigData));
            if(RetCode < 0)
            {
                lDiagnosticdata = lDiagnosticdata | (1<<4);
            }
            else
            {
                lDiagnosticdata = lDiagnosticdata & (~(1<<4));
                lDiagnosticdata = lDiagnosticdata & TIME_STAMP_OK;
                printk("Time updated\n");
                bRetVal = true;
            }
        }
        else
        {
            printk("WARN: Check RTC is connected\n\r");
            SetTimeUpdateStatus(false); 
            lDiagnosticdata = lDiagnosticdata | TIME_STAMP_ERROR;
        }
    }

    return bRetVal;
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
    uint32_t ulSleepTime = 0;
    double dGPM=0.00;
    char cBuffer[30] =  {0};

    pConfigObject = cJSON_CreateObject();
    ulSleepTime = GetSleepTime();
    dGPM = GetMinGPM();
    strcpy(cBuffer, VISENSE_FLOWMTR_FIRMWARE_VERSION);
    AddItemtoJsonObject(&pConfigObject, STRING, "VERSION", cBuffer, strlen(cBuffer));
    memset(cBuffer, 0, sizeof(cBuffer));
    sprintf(cBuffer, "%ds", ulSleepTime);
    AddItemtoJsonObject(&pConfigObject, STRING, "Sleep", cBuffer, strlen(cBuffer));
    memset(cBuffer, 0, sizeof(cBuffer));
    sprintf(cBuffer, "%fGPM", dGPM);
    AddItemtoJsonObject(&pConfigObject, STRING, "GPM", cBuffer, strlen(cBuffer));
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
        sConfigData.flag = sConfigData.flag | (1 << 0); //set flag for config data update and store it into flash

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

    return bRetVal;
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

