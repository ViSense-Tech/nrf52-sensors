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
#include "PMIC/PMICHandler.h"

/*******************************MACROS****************************************/
#define SLEEP_ENABLE  //Uncomment this line to enable sleep functionality
#define TIME_STAMP_ERROR   (1<<1)
#define TIME_STAMP_OK      ~(1<<1)


/*******************************GLOBAL VARIABLES********************************/
cJSON *pcData = NULL;
uint8_t *pucAdvBuffer = NULL;
struct nvs_fs fs; 
_sConfigData sConfigData = {0};
struct nvs_fs fs;    //file system
struct nvs_fs sConfigFs;
uint32_t uFlashIdx = 0;  // initialise data counter

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
static void SendConfigDataToApp();
static bool SendHistoryDataToApp(char *pcBuffer, uint16_t unLength);
/*This function is declared here for now. But prototype is in SystemHandler
will remove this from here later now did this for completing the functionality*/
uint32_t *GetDiagData();


/*******************************FUNCTION DEFINITIONS********************************/

/**
 * @brief Main function
*/
int main(void)
{
    int Ret;
    char cbuffer[50] = {0};
    char *cJsonBuffer = NULL;
    cJSON *pMainObject = NULL;
    int nCBValue = 0;
    uint32_t ulsleepTime = 0;
    cJSON *pSensorObj = NULL;
    long long llEpochNow = 0;
    double dTemperature = 0.0;
#ifdef PMIC_ENABLED    
    float fSOC=0.0;
#endif    
    int64_t Timenow =0;
    int ADCReading1;
    int ADCReading2;
    uint32_t *pDiagData = NULL;

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

    InitIrroMtrExcitingPins();
    InitAdc(NRF_SAADC_INPUT_AIN1, 1);
    pDiagData = GetDiagData();
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
            SendConfigDataToApp();

            pMainObject = cJSON_CreateObject();
           
           if (ReadFromADC(0,  &nCBValue))
            {
                if(nCBValue >= 255)
                {
                    *pDiagData = *pDiagData | IRROMETER_1_ERROR;
                }
                else
                {
                    *pDiagData = *pDiagData & IRROMETER_1_OK;
                }
                memset(cbuffer, '\0', sizeof(cbuffer));
                sprintf(cbuffer,"CB=%d", abs(nCBValue));
                printk("Data:%s\n", cbuffer);
                pSensorObj=cJSON_AddObjectToObject(pMainObject, "S1");
                ADCReading1 = GetADCReadingInForwardBias();
                ADCReading2 = GetADCReadingInReverseBias();
                AddItemtoJsonObject(&pSensorObj, NUMBER_INT, "ADC1", &ADCReading1, sizeof(uint16_t));
                AddItemtoJsonObject(&pSensorObj, NUMBER_INT, "ADC2", &ADCReading2, sizeof(uint16_t));
                AddItemtoJsonObject(&pSensorObj, STRING, "CB", (uint8_t*)cbuffer, (uint8_t)strlen(cbuffer)); 
            }

            if (ReadFromADC(1,  &nCBValue))
            {
                if(nCBValue >= 255)
                {
                    *pDiagData = *pDiagData | IRROMETER_2_ERROR;
                }
                else
                {
                    *pDiagData = *pDiagData & IRROMETER_2_OK;
                }
                memset(cbuffer, '\0', sizeof(cbuffer));
                sprintf(cbuffer,"CB=%d", abs(nCBValue));
                printk("Data:%s\n", cbuffer);
                pSensorObj=cJSON_AddObjectToObject(pMainObject, "S2");
                ADCReading1 = GetADCReadingInForwardBias();
                ADCReading2 = GetADCReadingInReverseBias();
                AddItemtoJsonObject(&pSensorObj, NUMBER_INT, "ADC1", &ADCReading1, sizeof(uint16_t));
                AddItemtoJsonObject(&pSensorObj, NUMBER_INT, "ADC2", &ADCReading2, sizeof(uint16_t));
                AddItemtoJsonObject(&pSensorObj, STRING, "CB", (uint8_t*)cbuffer, (uint8_t)strlen(cbuffer));        
            }

            if (ReadFromADC(2, &nCBValue))
            {
                if(nCBValue >= 255)
                {
                    *pDiagData = *pDiagData | IRROMETER_3_ERROR;
                }
                else
                {
                    *pDiagData = *pDiagData & IRROMETER_3_OK;
                }
                memset(cbuffer, '\0', sizeof(cbuffer));
                sprintf(cbuffer,"CB=%d", abs(nCBValue));
                printk("Data:%s\n", cbuffer);
                pSensorObj=cJSON_AddObjectToObject(pMainObject, "S3");
                ADCReading1 = GetADCReadingInForwardBias();
                ADCReading2 = GetADCReadingInReverseBias();
                AddItemtoJsonObject(&pSensorObj, NUMBER_INT, "ADC1", &ADCReading1, sizeof(uint16_t));
                AddItemtoJsonObject(&pSensorObj, NUMBER_INT, "ADC2", &ADCReading2, sizeof(uint16_t));
                AddItemtoJsonObject(&pSensorObj, STRING, "CB", (uint8_t*)cbuffer, (uint8_t)strlen(cbuffer));
            }


            if (GetCurrentTime(&llEpochNow))
            {
                printk("CurrentTime=%llu\n\r", llEpochNow);
            }
            printCurrentTime();
            
            if (ReadTemperatureFromDS18b20(&dTemperature))
            {
                AddItemtoJsonObject(&pMainObject, NUMBER_FLOAT, "Temp", &dTemperature, sizeof(double));
            }

            AddItemtoJsonObject(&pMainObject, NUMBER_INT, "TS", &llEpochNow, sizeof(long long));
            AddItemtoJsonObject(&pMainObject, NUMBER_INT, "DIAG", pDiagData, sizeof(uint32_t));

#ifdef PMIC_ENABLED            
            PMICUpdate(&fSOC);
            memset(cbuffer, '\0', sizeof(cbuffer));
            printk("soc=%f\n\r", fSOC);
            sprintf(cbuffer,"%d%%", (int)fSOC);
            AddItemtoJsonObject(&pMainObject, STRING, "Batt", cbuffer, sizeof(float));
#endif            
            cJsonBuffer = cJSON_Print(pMainObject);

            pucAdvBuffer[2] = 0x02;
            pucAdvBuffer[3] = (uint8_t)strlen(cJsonBuffer);
            memcpy(pucAdvBuffer+4, cJsonBuffer, strlen(cJsonBuffer));
            printk("JSON:\n*%s#\n", cJsonBuffer);

            SendHistoryDataToApp(cJsonBuffer, strlen(cJsonBuffer));

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
            else
            {
                //No Op
            }
        
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
static void SendConfigDataToApp()
{
    cJSON *pConfigObject = NULL;
    char *cJsonConfigBuffer = NULL;
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

    if (IsConfigNotifyEnabled())
    {
        VisenseConfigDataNotify(cJsonConfigBuffer, (uint16_t)strlen(cJsonConfigBuffer));
    }

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
       
#ifdef PMIC_ENABLED	       
       PMICInit();
#endif

      // InitTimer();
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
