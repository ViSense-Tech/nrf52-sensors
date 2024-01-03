/**
 * @file main.c
 * @brief Main function
 * @date 2023-09-27
 * @author Jeslin
 * @note  This is a test code for Irrometer.
*/


/*******************************INCLUDES****************************************/
#include "Json/cJSON.h"
#include "BleHandler.h"
#include "BleService.h"
#include "JsonHandler.h"
#include "RtcHandler.h"
#include "nvs_flash.h"
#include "SystemHandler.h"
#include "AdcHandler.h"
#include "Timerhandler.h"
#include "TempSensor.h"
#ifdef PMIC_ENABLED
#include "PMIC/PMICHandler.h"
#endif

/*******************************MACROS****************************************/
#define SLEEP_ENABLE  //Uncomment this line to enable sleep functionality
#define TIME_STAMP_ERROR   (1<<1)
#define TIME_STAMP_OK      ~(1<<1)


/*******************************GLOBAL VARIABLES********************************/
uint8_t *pucAdvBuffer = NULL;
struct nvs_fs fs; 
_sConfigData sConfigData = {0};
struct nvs_fs fs;    //file system
struct nvs_fs sConfigFs;
uint32_t uFlashIdx = 0;  // initialise data counter
char *cJsonBuffer = NULL;

/*******************************FUNCTION DECLARATION********************************/
static void PrintBanner();
static bool InitAllModules();
static void InitDataPartition();
static bool InitBle();
static bool InitPowerManager();
static bool CheckForConfigChange();
static bool GetTimeFromRTC();
static bool UpdateConfigurations();
static bool WriteConfiguredtimeToRTC(void);
static void UpdateConfigParameters();
static bool SendHistoryDataToApp(char *pcBuffer, uint16_t unLength);
static bool AddSensorDataToPayload(uint8_t ucChannel, cJSON *pMainObject);
static bool UpdateDiagInfoForSensors(uint8_t ucChannel, int *pnCBValue);
static bool AppendSensorDataToMainObject(cJSON *pMainObject, int *pnCBValue, uint8_t ucChannel);
static bool GetAllSensorData(cJSON *pMainObject);
static bool DoTimedDataNotification(cJSON *pMainObject);
static bool SendLiveDataToApp(cJSON *pMainObject);
#ifdef PMIC_ENABLED
static bool GetBatLvlStatusAndUpdateJSON(cJSON *pMainObject);
#endif


/*******************************FUNCTION DEFINITIONS********************************/

/**
 * @brief Main function
*/
int main(void)
{
    cJSON *pMainObject = NULL;
    int64_t Timenow =0;

    PrintBanner();
    printk("VISENSE_IRROMETER_FIRMWARE_VERSION: %s\n\r", VISENSE_IRROMETER_FIRMWARE_VERSION);
    k_msleep(1000);
    printk("FEATURES: %s", VISENSE_IRROMETER_FEATURES);
    k_msleep(1000);
    printk("\n\r");

    if (!InitAllModules())
    {
            printk("ERROR: Initialising all modules failed \n\r");
    }

    if (!CheckForConfigChange())
    {
        printk("ERROR: Config check failed\n\r");
    }    

    if (!GetTimeFromRTC())
    {
        printk("WARN: Getting time from RTC failed\n\r");
    }

    while (1) 
    {
        #ifdef SLEEP_ENABLE
        Timenow = sys_clock_tick_get();

        while(sys_clock_tick_get() - Timenow < (ALIVE_TIME * TICK_RATE))
        {
        #endif    

            if (UpdateConfigurations())
            {
                printk("INFO: Updating config \n\r");           
            }

            WriteConfiguredtimeToRTC();
            UpdateConfigParameters();
            pMainObject = cJSON_CreateObject();
            DoTimedDataNotification(pMainObject);
            memset(pucAdvBuffer, 0, ADV_BUFF_SIZE);
            cJSON_Delete(pMainObject);
            cJSON_free(cJsonBuffer);
            
            #ifndef SLEEP_ENABLE 
            k_msleep(500);
            #endif
        #ifdef SLEEP_ENABLE
        }
        #endif

        #ifdef SLEEP_ENABLE
         k_msleep(1000);
         EnterSleepMode(GetSleepTime());
         ExitSleepMode();
        #endif
    }
}

/**
 * @brief Running history and live data notification in timeslots
 * @param pMainObject : Main object
 * @return true for success
*/
static bool DoTimedDataNotification(cJSON *pMainObject)
{
    int64_t  llTimeNow=0;

    bool bRetVal = false;

    if (!pMainObject)
    {
        return bRetVal;
    }

    llTimeNow = sys_clock_tick_get();

    while(sys_clock_tick_get() - llTimeNow < (LIVEDATA_TIMESLOT))
    {
        if (!SendLiveDataToApp(pMainObject))
        {
            printk("ERR: Sennding live data failed\n\r");
            break;
        }
    }

    llTimeNow = sys_clock_tick_get();

    while(sys_clock_tick_get() - llTimeNow < (HISTORYDATA_TIMESLOT))
    {   
        if (!SendHistoryDataToApp(cJsonBuffer, strlen(cJsonBuffer)))
        {
            printk("ERR: Sennding history data failed\n\r");
            break;            
        }
    }

    bRetVal = true;

    return bRetVal;
}


#ifdef PMIC_ENABLED  
/**
 * @brief Get battery percentage and update it to JSON
 * @param pMainObject : Main object
 * @return true for success
*/
static bool GetBatLvlStatusAndUpdateJSON(cJSON *pMainObject)
{      
    float fSOC=0.0;
    char cBuffer[30] = {0};

    PMICUpdate(&fSOC);
    memset(cBuffer, '\0', sizeof(cBuffer));
    printk("soc=%f\n\r", fSOC);
    sprintf(cBuffer,"%d%%", (int)fSOC);
    AddItemtoJsonObject(&pMainObject, STRING, "Batt", cBuffer, sizeof(float));          
}
#endif

/**
 * @brief Get data from all irrometrs
 * @param pMainObject : Main object
 * @return true for success
*/
static bool GetAllSensorData(cJSON *pMainObject)
{
    bool bRetVal = false;

    if (!pMainObject)
    {
        return bRetVal;
    }

    do
    {
        if (!AddSensorDataToPayload(CHANNEL_0, pMainObject))
        {
            printk("ERR: Adding sensor 1 data to JSON failed");
            break;
        }

        if (!AddSensorDataToPayload(CHANNEL_1, pMainObject))
        {
            printk("ERR: Adding sensor 2 data to JSON failed"); 
            break;               
        }

        if (!AddSensorDataToPayload(CHANNEL_2, pMainObject))
        {
            printk("ERR: Adding sensor 3 data to JSON failed");
            break;
        }

        bRetVal = true;
    } while (0);

    return bRetVal;
}

/**
 * @brief Sending Live data to Application
 * @param pMainObject : Main object
 * @return true for success
*/
static bool SendLiveDataToApp(cJSON *pMainObject)
{
    bool bRetVal = false;
    long long llEpochNow = 0;
    double dTemperature = 0.0;
    uint32_t *pDiagData = NULL;
    
    pDiagData = GetDiagData();
     
    if (!pMainObject && !pDiagData)
    {
        return bRetVal;
    }

    do
    {
        if (!GetAllSensorData(pMainObject))    
        {
            printk("ERR: Getting All sensor data failed\n\r");
            break;
        } 
        if (GetCurrentTime(&llEpochNow))
        {
            printk("CurrentEpoch=%llu\n\r", llEpochNow);
        }
        printCurrentTime();
        
        if (ReadTemperatureFromDS18b20(&dTemperature))
        {
            if (!AddItemtoJsonObject(&pMainObject, NUMBER_FLOAT, "Temp", &dTemperature, sizeof(double)))
            {
                printk("ERR: Adding sensor 3 data to JSON failed");  
                break;              
            }
        }

    #ifdef PMIC_ENABLED
            GetBatLvlStatusAndUpdateJSON(pMainObject);
    #endif

        if (!AddItemtoJsonObject(&pMainObject, NUMBER_INT, "TS", &llEpochNow, sizeof(long long)))
        {
            printk("ERR: Adding timestamp to JSON failed\n\r");
            break;
        }
        
        if (!AddItemtoJsonObject(&pMainObject, NUMBER_INT, "DIAG", pDiagData, sizeof(uint32_t)))
        {
            printk("ERR: Adding diag to JSON failed\n\r");   
            break;     
        }

        cJsonBuffer = cJSON_Print(pMainObject);

        pucAdvBuffer[2] = 0x02;
        pucAdvBuffer[3] = (uint8_t)strlen(cJsonBuffer);
        memcpy(pucAdvBuffer+4, cJsonBuffer, strlen(cJsonBuffer));
        printk("JSON:\n*%s#\n", cJsonBuffer);
        
        if(IsNotificationenabled() && IsConnected())
        {
            VisenseSensordataNotify(pucAdvBuffer+2, ADV_BUFF_SIZE);
        }
        else if (!IsConnected())
        {
            #ifdef EXT_ADV
                UpdateAdvData();
                StartAdv();
            #endif
        }

      bRetVal = true;
    } while (0);


    return bRetVal;
}

/**
 * @brief Append sensor data to root JSON object
 * @param pMainObject : Main object 
 * @param pnCBValue : CB value
 * @return true for success
*/
static bool AppendSensorDataToMainObject(cJSON *pMainObject, int *pnCBValue, uint8_t ucChannel)
{
    cJSON *pSensorObj = NULL;
    bool bRetVal = false;
    char cBuffer[50] = {0};
    int ADCReading1 = 0;
    int ADCReading2 = 0;

    if (pnCBValue)
    {
        do
        {
            memset(cBuffer, '\0', sizeof(cBuffer));
            sprintf(cBuffer,"CB=%d", abs(*pnCBValue));
            printk("Data:%s\n", cBuffer);

            ADCReading1 = GetADCReadingInForwardBias();
            ADCReading2 = GetADCReadingInReverseBias();

            switch (ucChannel)
            {
                case 0: pSensorObj=cJSON_AddObjectToObject(pMainObject, "S1");
                        break;
                case 1: pSensorObj=cJSON_AddObjectToObject(pMainObject, "S2");
                        break;
                case 2: pSensorObj=cJSON_AddObjectToObject(pMainObject, "S3");
                        break;
                default:
                        break;        
            }

            if (!AddItemtoJsonObject(&pSensorObj, NUMBER_INT, "ADC1", &ADCReading1, sizeof(uint16_t)))
            {
                printk("ERR: Adding ADC reading 1 failed\n\r");
                break;
            }
            if (!AddItemtoJsonObject(&pSensorObj, NUMBER_INT, "ADC2", &ADCReading2, sizeof(uint16_t)))
            {
                printk("ERR: Adding ADC reading 2 failed\n\r");
                break;
            }
            
            if (!AddItemtoJsonObject(&pSensorObj, STRING, "CB", (uint8_t*)cBuffer, (uint8_t)strlen(cBuffer)))
            {
                printk("ERR: Adding CB value failed\n\r");
                break;
            }

            bRetVal = true;
        } while (0);
    }   

    return bRetVal; 
}

/**
 * @brief Update Diagnostic data for sesors
 * @param ucChannel : channel of the sensor
 * @param pnCBValue : CB value
 * @return true for success
*/
static bool UpdateDiagInfoForSensors(uint8_t ucChannel, int *pnCBValue)
{
    uint32_t *pDiagData = NULL;
    bool bRetVal = false;

    pDiagData = GetDiagData();

    if (!pnCBValue || !pDiagData)
    {
        return bRetVal;
    }

    switch (ucChannel)
    {
        case 0: if(*pnCBValue >= 255)
                {
                    *pDiagData = *pDiagData | IRROMETER_1_ERROR;
                }
                else
                {
                    *pDiagData = *pDiagData & IRROMETER_1_OK;
                }

                bRetVal = true;

                break;

        case 1: if(*pnCBValue >= 255)
                {
                    *pDiagData = *pDiagData | IRROMETER_2_ERROR;
                }
                else
                {
                    *pDiagData = *pDiagData & IRROMETER_2_OK;
                }

                bRetVal = true;                
                
                break;

        case 2: if(*pnCBValue >= 255)
                {
                    *pDiagData = *pDiagData | IRROMETER_3_ERROR;
                }
                else
                {
                    *pDiagData = *pDiagData & IRROMETER_3_OK;
                }

                bRetVal = true;                

                break;    
        
        default:
                break;
    }

    return bRetVal;
}

/**
 * @brief Read the sensor data and append to JSON payload
 * @param ucChannel : ADC channel 
 * @param pMainObject : Json main object
 * @return true for success
*/
static bool AddSensorDataToPayload(uint8_t ucChannel, cJSON *pMainObject)
{
    int nCBValue = 0;
    bool bRetVal = false;

    do
    {
        if (!ReadFromADC(ucChannel, &nCBValue))
        {
            printk("ERR: Read from ADC channel\n\r");
            break;
        }

        if (!AppendSensorDataToMainObject(pMainObject, &nCBValue, ucChannel))
        {
            printk("ERR: Append data to JSON failed\n\r");
            break;          
        }

        if (!UpdateDiagInfoForSensors(ucChannel, &nCBValue))
        {
            printk("ERR: Update Diagnostic failed\n\r");
            break;
        }

        bRetVal = true;
    } while (0);

    return bRetVal;
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
 * @brief Sending history data over ble
 * @param pcBuffer : data to send
 * @param unLength : Length of data
 * @return None
*/
static bool SendHistoryDataToApp(char *pcBuffer, uint16_t unLength)
{

    char cBuffer[ADV_BUFF_SIZE];
    bool bRetval = false;


    if (pcBuffer)
    {
        if(!IsConnected()) // && sConfigData.flag & (1 << 4) can include this condition also if config is mandetory during initial setup
        {
            
            memset(cBuffer, '\0', sizeof(cBuffer));
            memcpy(cBuffer, pcBuffer, unLength);
            if(writeJsonToExternalFlash(cBuffer, uFlashIdx,WRITE_ALIGNMENT))
            {
                // NO OP
            }
            k_msleep(50);
            if (readJsonFromExternalFlash(cBuffer, uFlashIdx, WRITE_ALIGNMENT))
            {
                printk("\nId: %d, Stored_Data: %s\n",uFlashIdx, pcBuffer);
            }
            uFlashIdx++;
            sConfigData.flashIdx = uFlashIdx;
            nvs_write(&sConfigFs, 0, (char *)&sConfigData, sizeof(_sConfigData));
            if(uFlashIdx>= NUMBER_OF_ENTRIES)
            {
                uFlashIdx = 0;   
            }
        }
 

        if(IshistoryNotificationenabled() && IsConnected())
        {
            if(VisenseHistoryDataNotify(uFlashIdx))
            {
                uFlashIdx = 0; 
                sConfigData.flashIdx = uFlashIdx;
                nvs_write(&sConfigFs, 0, (char *)&sConfigData, sizeof(_sConfigData));
            }
            
        }

        bRetval = true;
    }

    return bRetval;
}

/**
 * @brief send config data to application over ble
 * @param None
 * @return None
*/
static void UpdateConfigParameters()
{
    cJSON *pConfigObject = NULL;
    char *cJsonConfigBuffer = NULL;
    uint8_t *pucConfigBuffer = NULL;
    uint32_t ulSleepTime = 0;
    char cBuffer[30] =  {0};

    pConfigObject = cJSON_CreateObject();
    ulSleepTime = GetSleepTime();
    strcpy(cBuffer, VISENSE_IRROMETER_FIRMWARE_VERSION);
    AddItemtoJsonObject(&pConfigObject, STRING, "VERSION", cBuffer, strlen(cBuffer));
    memset(cBuffer, 0, sizeof(cBuffer));
    sprintf(cBuffer, "%ds", ulSleepTime);
    AddItemtoJsonObject(&pConfigObject, STRING, "Sleep", cBuffer, strlen(cBuffer));
    cJsonConfigBuffer = cJSON_Print(pConfigObject);
    printk("ConfigJSON:\n%s\n", cJsonConfigBuffer);

    pucConfigBuffer = GetConfigBuffer();
    memcpy(pucConfigBuffer, cJsonConfigBuffer, strlen(cJsonConfigBuffer));

    cJSON_free(cJsonConfigBuffer);
    cJSON_Delete(pConfigObject);
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

    pDiagData = GetDiagData();

    if (GetTimeUpdateStatus())
    {
        if (InitRtc())
        {
            SetTimeUpdateStatus(false); 
            sConfigData.flag = sConfigData.flag | (1 << 4); //set flag for timestamp config data update and store it into flash
            RetCode = nvs_write(&sConfigFs, 0, (char *)&sConfigData, sizeof(_sConfigData));
            if(RetCode < 0)
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
            printk("WARN: Check RTC is connected\n\r");
            SetTimeUpdateStatus(false); 
            *pDiagData = *pDiagData | TIME_STAMP_ERROR;
        }
    }

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

    pucAdvBuffer = GetAdvBuffer();

    do
    {
        if (pucAdvBuffer == NULL)
        {
            break;
        }

        if (!EnableBLE())
        {
            printk("Bluetooth init failed (err %d)\n", nError);
            break;
        }

#ifdef EXT_ADV
        nError = InitExtAdv();
        
        if (nError) 
        {
            printk("Advertising failed to create (err %d)\n", nError);
            break;
        }
#endif        

        StartAdv();
        bRetVal = true;
    } while (0);
    
    return bRetVal;
}

/**
 * @brief initialise data partitions
 * @param None
 * @return None
*/
static void InitDataPartition()
{
    nvs_initialisation(&fs, DATA_FS); 
    SetFileSystem(&fs);
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

        InitIrroMtrExcitingPins();
        InitAdc(NRF_SAADC_INPUT_AIN1, 1);
       
#ifdef PMIC_ENABLED	       
       PMICInit();
#endif

       InitTimer();
       k_sleep(K_TICKS(100));

       InitDataPartition();

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
 * @brief Check for config change and update value from flash
 * @param None
 * @return true for success
*/
static bool CheckForConfigChange()
{
    uint32_t ulRetCode = 0;
    bool bRetVal = false;
    uint32_t *pDiagData = NULL;

    pDiagData = GetDiagData();

    nvs_initialisation(&sConfigFs, CONFIG_DATA_FS); 
    k_msleep(100);
    ulRetCode = readJsonToFlash(&sConfigFs, 0, 0, (char *)&sConfigData, sizeof(sConfigData)); // read config params from the flash
    if(sConfigData.flag == 0) 
    {
        printk("\n\rError occured while reading config data: %d\n", ulRetCode);
        EraseExternalFlash(SECTOR_COUNT);   
        *pDiagData = *pDiagData | CONFIG_WRITE_FAILED; // flag will shows error while reading config data from flash and added to the application
    }
    else
    {
        SetSleepTime(sConfigData.sleepTime);
        uFlashIdx = sConfigData.flashIdx;
        printk("sConfigFlag %d ,flashIdx = %d\n",
                                     sConfigData.flag,
                                     sConfigData.flashIdx); //get all the config params from the flash if a reboot occures

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
 * @brief Getting time from RTC
 * @param None
 * @return true for success
*/
static bool GetTimeFromRTC()
{
    long long llEpochNow = 0;
    bool bRetVal = false;
    uint32_t *pDiagData = NULL;

    pDiagData = GetDiagData();

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
