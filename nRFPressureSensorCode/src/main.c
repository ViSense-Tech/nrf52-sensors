/**
 * @file main.c
 * @brief Main function
 * @date 2023-21-09
 * @author Jeslin
 * @note  This is a test code for pressure sensor.
*/


/*******************************INCLUDES****************************************/
#include "Common.h"
#include "BleHandler.h"
#include "AdcHandler.h"
#include "BleService.h"
#include "JsonHandler.h"
#include "RtcHandler.h"
#include "SystemHandler.h"
#include "nvs_flash.h"
#include "TimerHandler.h"


/*******************************MACROS****************************************/
// #define SLEEP_ENABLE  //Uncomment this line to enable sleep functionality
#define PRESSURE_SENSOR         0x01
// diagnostics
#define SENSOR_DIAGNOSTICS       (1<<2)
#define SENSOR_STATUS_OK        ~(1<<2)
#define TIME_STAMP_ERROR         (1<<1)
#define TIME_STAMP_OK           ~(1<<1)

/*******************************TYPEDEFS****************************************/

/*******************************GLOBAL VARIABLES********************************/
_sConfigData sConfigData = {0};
struct nvs_fs fs;    //file system
struct nvs_fs sConfigFs;
uint8_t *pucAdvertisingdata = NULL;
uint32_t diagnostic_data = 0;
uint32_t pressureMax = 929; //analog reading of pressure transducer at 100psi
uint32_t pressureZero = 110; //analog reading of pressure transducer at 0psi
uint32_t uFlashIdx = 0;  // initialise data counter

/*******************************FUNCTION DECLARATIONS********************************/
extern void SetFileSystem(struct nvs_fs *fs);
static bool UpdateConfigurations();
static bool InitPowerManager();
static bool InitBle();
static void InitDataPartition();
static bool CheckForConfigChange();
static bool InitAllModules();
static void PrintBanner();
static bool GetTimeFromRTC();
static bool WriteConfiguredtimeToRTC(void);
static void SendConfigDataToApp();
static bool SendHistoryDataToApp(uint16_t uPressureValue, char *pcBuffer, uint16_t unLength);

/*******************************FUNCTION DEFINITIONS********************************/

/**
 * @brief  Main function
 * @return int
*/
int main(void)
{
    uint16_t unPressureResult =0;
    uint32_t unPressureRaw = 0;
    char cbuffer[50] = {0};
    char *cJsonBuffer= NULL;
    cJSON *pMainObject = NULL;
    long long llEpochNow = 0;
    int64_t Timenow = 0;

    PrintBanner();
    printk("VISENSE_PRESSURE_FIRMWARE_VERSION: %s\n\r", VISENSE_PRESSURE_SENSOR_FIRMWARE_VERSION);
    k_msleep(1000);
    printk("FEATURES: %s", VISENSE_PRESSURE_SENSOR_FEATURES);
    k_msleep(1000);
    printk("\n\r");

   if (!InitAllModules())
   {
        printk("ERROR: Initialising all modules failed \n\r");
   }

    if (!CheckForConfigChange())
    {
        printk("ERROR: Config Check failed \n\r");
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
            SendConfigDataToApp();

            if (GetPressureReading(&unPressureResult, &unPressureRaw))
            {
                printk("PressureRaw: %d\n", unPressureRaw);
            }

            pMainObject = cJSON_CreateObject();
            pressureZero = GetPressureZero();
            pressureMax = GetPressureMax();

            if (GetCurrentTime(&llEpochNow))
            {
                printk("CurrentTime=%llu\n\r", llEpochNow);
            }
            AddItemtoJsonObject(&pMainObject, NUMBER, "ADCValue", &unPressureRaw, sizeof(uint16_t));
            AddItemtoJsonObject(&pMainObject, NUMBER, "TS", &llEpochNow, sizeof(long long));

            if (unPressureRaw > pressureZero && unPressureRaw < ADC_MAX_VALUE)
            {
                memset(cbuffer, '\0',sizeof(cbuffer));
                
                sprintf(cbuffer,"%dpsi", unPressureResult);
                printk("Data:%s\n", cbuffer);
                AddItemtoJsonObject(&pMainObject, STRING, "Pressure", (uint8_t*)cbuffer, (uint8_t)strlen(cbuffer));
                diagnostic_data = diagnostic_data & SENSOR_STATUS_OK;

            }
            else if(unPressureRaw > 100 && unPressureRaw < 1023) //
            {
                memset(cbuffer, '\0',sizeof(cbuffer));
                unPressureResult = 0;
                sprintf(cbuffer,"%dpsi", unPressureResult);
                AddItemtoJsonObject(&pMainObject, STRING, "Pressure", (uint8_t*)cbuffer, (uint8_t)strlen(cbuffer));
                diagnostic_data = diagnostic_data & SENSOR_STATUS_OK;  
            }
            else if(unPressureRaw < 100 || unPressureRaw > 1023)
            {
                diagnostic_data = diagnostic_data | SENSOR_DIAGNOSTICS;
            }
            else
            {
                // NO OP
            }
        
            AddItemtoJsonObject(&pMainObject, NUMBER, "DIAG", &diagnostic_data, sizeof(uint32_t));
            cJsonBuffer = cJSON_Print(pMainObject);
            pucAdvertisingdata[2] = PRESSURE_SENSOR;
            pucAdvertisingdata[3] = (uint8_t)strlen(cJsonBuffer);
            memcpy(&pucAdvertisingdata[4], cJsonBuffer, strlen(cJsonBuffer));

                
            SendHistoryDataToApp(unPressureResult, cJsonBuffer, strlen(cJsonBuffer)); //save to flash only if Mobile Phone is NOT connected
            
            printk("JSON:\n%s\n", cJsonBuffer);

            if(IsNotificationenabled())
            {
                VisenseSensordataNotify(pucAdvertisingdata+2, ADV_BUFF_SIZE);
            }
#ifdef EXTENDED_ADV
            else if (!IsNotificationenabled() && !IsConnected())
            {
                UpdateAdvertiseData();
                StartAdvertising();
            }
#endif
            else
            {
                //NO OP
            }
            
            if ((sConfigData.flag & (1 << 4))) //check whether config data is read from the flash / updated from mobile
            {
                diagnostic_data = diagnostic_data & CONFIG_WRITE_OK; //added a diagnostic information to the application
            }
            else
            {
                diagnostic_data = diagnostic_data | CONFIG_WRITE_FAILED; //added a diagnostic information to the application
            }
            
            memset(pucAdvertisingdata, 0, ADV_BUFF_SIZE);
            cJSON_Delete(pMainObject);
            cJSON_free(cJsonBuffer);

        #ifndef SLEEP_ENABLE 
            k_sleep(K_MSEC(100));
        #endif
        #ifdef SLEEP_ENABLE
        }
        EnterSleepMode(GetSleepTime());
        ExitSleepMode();
        printk("INFO: Syncing time with RTC\n\r");
        if (!GetTimeFromRTC())
        {
            printk("WARN: Getting time from RTC failed\n\r");
        }
        #endif
    }
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

    if (IsPressureZeroSet() || IsPressureMaxSet() || IsSleepTimeSet() || IsPressureMinSet())
    {
        if (IsPressureZeroSet() && IsPressureMaxSet())
        {
            sConfigData.pressureZero = GetPressureZero();
            sConfigData.pressureMax = GetPressureMax();
            SetPressureZeroSetStatus(false);
            SetPressureMaxSetStatus(false);
        }
        if (IsSleepTimeSet())
        {
            sConfigData.sleepTime = GetSleepTime();
            SetSleepTimeSetStataus(false);
        }
        if (IsPressureMinSet())
        {
            sConfigData.pressureMin = GetPressureMin();
            SetPressureMinSetStatus(false);
        }

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
 * @brief Sending history data over ble
 * @param pcBuffer : data to send
 * @param unLength : Length of data
 * @return None
*/
static bool SendHistoryDataToApp(uint16_t uPressureValue, char *pcBuffer, uint16_t unLength)
{

    char cBuffer[ADV_BUFF_SIZE];
    bool bRetval = false;


    if (pcBuffer)
    {
        if(!IsConnected() && (uPressureValue >= GetPressureMin())) // && sConfigData.flag & (1 << 4) can include this condition also if config is mandetory during initial setup
        {
            
            memset(cBuffer, '\0', sizeof(cBuffer));
            memcpy(cBuffer, pcBuffer, unLength);
            if(writeJsonToExternalFlash(cBuffer, uFlashIdx, WRITE_ALIGNMENT))
            {
                // NO OP
            }
            k_msleep(50);
            if (readJsonFromExternalFlash(cBuffer, uFlashIdx, WRITE_ALIGNMENT))
            {
                printk("\nId: %d, Stored_Data: %s\n",uFlashIdx, cBuffer);
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
            printk("In history notif\n\r");
            if (VisenseHistoryDataNotify(uFlashIdx))
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
    uint32_t unPressureMin = 0;

    pConfigObject = cJSON_CreateObject();
    ulSleepTime = GetSleepTime();
    unPressureMin = (uint32_t)GetPressureMin();
    strcpy(cBuffer, VISENSE_PRESSURE_SENSOR_FIRMWARE_VERSION);
    AddItemtoJsonObject(&pConfigObject, NUMBER, "PressureZero", &pressureZero, sizeof(uint32_t));
    AddItemtoJsonObject(&pConfigObject, NUMBER, "PressureMax", &pressureMax, sizeof(uint32_t));
    AddItemtoJsonObject(&pConfigObject, STRING, "VERSION", cBuffer, strlen(cBuffer));
    AddItemtoJsonObject(&pConfigObject, NUMBER, "PressureMin", &unPressureMin, sizeof(uint32_t));
    memset(cBuffer, 0, sizeof(cBuffer));
    sprintf(cBuffer, "%ds", ulSleepTime);
    AddItemtoJsonObject(&pConfigObject, STRING, "SLEEP", cBuffer, strlen(cBuffer));
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

    if (GetTimeUpdateStatus())
    {
        if (InitRtc())
        {
            SetTimeUpdateStatus(false); 
            sConfigData.flag = sConfigData.flag | (1 << 4); //set flag for timestamp config data update and store it into flash
            RetCode = nvs_write(&sConfigFs, 0, (char *)&sConfigData, sizeof(_sConfigData));
            if(RetCode < 0)
            {
                diagnostic_data = diagnostic_data | CONFIG_WRITE_FAILED;
            }
            else
            {
                diagnostic_data = diagnostic_data & CONFIG_WRITE_OK;
                diagnostic_data = diagnostic_data & TIME_STAMP_OK;
                printk("Time updated\n");
                bRetVal = true;
            }
        }
        else
        {
            diagnostic_data = diagnostic_data | TIME_STAMP_ERROR;
        }
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

    if (GetCurrenTimeInEpoch(&llEpochNow))
    {
        printk("CurrentTime=%llu\n\r", llEpochNow);
        SetCurrentTime(llEpochNow);
        diagnostic_data = diagnostic_data & TIME_STAMP_OK;
        bRetVal = true;
    }
    else
    {
        diagnostic_data = diagnostic_data | TIME_STAMP_ERROR;
    }

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
 * @brief Initialise BLE functions
 * @param None
 * @return true for success
*/
static bool InitBle()
{
    bool bRetVal = false;
    int nError = 0;

    pucAdvertisingdata = GetAdvertisingBuffer();

    do
    {
        if (pucAdvertisingdata == NULL)
        {
            break;
        }

        if (!EnableBLE())
        {
            printk("Bluetooth init failed (err %d)\n", nError);
            break;
        }
#ifdef EXTENDED_ADV
        nError = InitExtendedAdv();
        
        if (nError) 
        {
            printk("Advertising failed to create (err %d)\n", nError);
            break;
        }
        StartAdvertising();
#else
        nError = StartAdvertising();
        if (nError)
        {
            printk("Advertising failed to create (err %d)\n", nError);
            break;
        }
#endif
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
 * @brief Check for config change and update value from flash
 * @param None
 * @return true for success
*/
static bool CheckForConfigChange()
{
    uint32_t ulRetCode = 0;
    bool bRetVal = false;

    nvs_initialisation(&sConfigFs, CONFIG_DATA_FS); 
    k_msleep(100);
    ulRetCode = readJsonToFlash(&sConfigFs, 0, 0, (char *)&sConfigData, sizeof(sConfigData)); // read config params from the flash
    if(sConfigData.flag == 0) 
    {
        printk("\n\rError occured while reading config data: %d\n", ulRetCode);
        diagnostic_data = diagnostic_data | CONFIG_WRITE_FAILED; // flag will shows error while reading config data from flash and added to the application
        EraseExternalFlash(SECTOR_COUNT);
    }
    else
    {
        SetPressureZero(sConfigData.pressureZero);       
        SetPressureMax(sConfigData.pressureMax);
        SetSleepTime(sConfigData.sleepTime);
        uFlashIdx = sConfigData.flashIdx;
        SetPressureMin(sConfigData.pressureMin);
        printk("PressureZero = %d, PressureMax = %d, sConfigFlag %d ,flashIdx = %d\n",
                                     sConfigData.pressureZero, 
                                     sConfigData.pressureMax,
                                     sConfigData.flag,
                                     sConfigData.flashIdx); //get all the config params from the flash if a reboot occures
        diagnostic_data = diagnostic_data & CONFIG_WRITE_OK;

        bRetVal = true;
    }

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
       InitTimer();
       InitADC();
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