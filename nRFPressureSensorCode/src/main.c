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
static void UpdateConfigParameters();
static bool DoTimedDataNotification(cJSON **pMainObject, char **pcBuffer);
static bool SendHistoryDataToApp(uint16_t uPressureValue, char *pcBuffer, uint16_t unLength);
static bool SendLiveData(cJSON *pMainObject, char **pcBuffer, uint16_t *pusPressureResult);

/*******************************FUNCTION DEFINITIONS********************************/

/**
 * @brief  Main function
 * @return int
*/
int main(void)
{
    char *cJsonBuffer= NULL;
    cJSON *pMainObject = NULL;
    int64_t Timenow = 0;
#ifdef PMIC_ENABLED  
    float fSOC=0.0;
#endif

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
            UpdateConfigParameters();

            pMainObject = cJSON_CreateObject();
            pressureZero = GetPressureZero();
            pressureMax = GetPressureMax();

            if ((sConfigData.flag & (1 << 4))) //check whether config data is read from the flash / updated from mobile
            {
                diagnostic_data = diagnostic_data & CONFIG_WRITE_OK; //added a diagnostic information to the application
            }
            else
            {
                diagnostic_data = diagnostic_data | CONFIG_WRITE_FAILED; //added a diagnostic information to the application
            }

            if (DoTimedDataNotification(&pMainObject, &cJsonBuffer))
            {
                memset(pucAdvertisingdata, 0, ADV_BUFF_SIZE);
                cJSON_Delete(pMainObject);
                cJSON_free(cJsonBuffer);
            }
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
 * @brief Running history and live data notification in timeslots
 * @param pMainObject : Main object
 * @return true for success
*/
static bool DoTimedDataNotification(cJSON **pMainObject, char **pcBuffer)
{
    int64_t  llTimeNow=0;
    uint16_t unPressureResult =0;
    bool bRetVal = false;

    if (!pMainObject || !pcBuffer)
    {
        printk("ERR:Invalid arguments in timed Notification function\n\r");
        return bRetVal;
    }

    llTimeNow = sys_clock_tick_get();

    while(sys_clock_tick_get() - llTimeNow < (LIVEDATA_TIMESLOT))
    {
        if (!SendLiveData(*pMainObject, pcBuffer, &unPressureResult))
        {
            printk("ERR: Sennding live data failed\n\r");
            break;
        }
    }

    llTimeNow = sys_clock_tick_get();

    while(sys_clock_tick_get() - llTimeNow < (HISTORYDATA_TIMESLOT))
    {   
        if (!SendHistoryDataToApp(unPressureResult, *pcBuffer, strlen(*pcBuffer)))
        {
            printk("ERR: Sennding history data failed\n\r");
            break;            
        }
    }

    bRetVal = true;

    return bRetVal;
}

/**
 * @brief Send live data to App
 * @param pMainObject : JSON root object
 * @param pcBuffer    : JSON data buffer
 * @param pusPressurResult : Pressure result
 * @return true for success
*/
static bool SendLiveData(cJSON *pMainObject, char **pcBuffer, uint16_t *pusPressureResult)
{
    bool bRetVal = false;
    long long llEpochNow = 0;
    uint32_t unPressureRaw = 0;
    char cbuffer[50] = {0};

    do
    {

        if (GetPressureReading(pusPressureResult, &unPressureRaw))
        {
            printk("INFO:PressureRaw: %d\n", unPressureRaw);
        }

        if (GetCurrentTime(&llEpochNow))
        {
            printk("CurrentTime=%llu\n\r", llEpochNow);
        }
        
        if (!AddItemtoJsonObject(&pMainObject, NUMBER, "ADCValue", &unPressureRaw, sizeof(uint16_t)))
        {
            printk("ERR: Adding ADC value to JSON\n\r");
            //break;
        }
       
        if (!AddItemtoJsonObject(&pMainObject, NUMBER, "TS", &llEpochNow, sizeof(long long)))
        {
            printk("ERR: Adding timestamp value to JSON\n\r");
            //break;
        }

        if (unPressureRaw > pressureZero && unPressureRaw < ADC_MAX_VALUE)
        {
            memset(cbuffer, '\0',sizeof(cbuffer));
            
            sprintf(cbuffer,"%dpsi", *pusPressureResult);
            printk("Data:%s\n", cbuffer);
            if (!AddItemtoJsonObject(&pMainObject, STRING, "Pressure", (uint8_t*)cbuffer, (uint8_t)strlen(cbuffer)))
            {
                printk("ERR: Adding pressure value to JSON\n\r");
                //break;
            }
            diagnostic_data = diagnostic_data & SENSOR_STATUS_OK;

        }
        else if(unPressureRaw > 100 && unPressureRaw < 1023) //
        {
            memset(cbuffer, '\0',sizeof(cbuffer));
            *pusPressureResult = 0;
            sprintf(cbuffer,"%dpsi", *pusPressureResult);
            if (!AddItemtoJsonObject(&pMainObject, STRING, "Pressure", (uint8_t*)cbuffer, (uint8_t)strlen(cbuffer)))
            {
                printk("ERR: Adding ADC value to JSON\n\r");
                //break;
            }
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

        if (!AddItemtoJsonObject(&pMainObject, NUMBER, "DIAG", &diagnostic_data, sizeof(uint32_t)))
        {
            printk("ERR: Adding ADC value to JSON\n\r");
            //return
        }        
        bRetVal = true;
    } while (0);


        

#ifdef PMIC_ENABLED            
    PMICUpdate(&fSOC);
    memset(cbuffer, '\0', sizeof(cbuffer));
    printk("soc=%f\n\r", fSOC);
    sprintf(cbuffer,"%d%%", (int)fSOC);
    AddItemtoJsonObject(&pMainObject, STRING, "Batt", cbuffer, sizeof(float));
#endif            
    *pcBuffer = cJSON_Print(pMainObject);
    pucAdvertisingdata[2] = PRESSURE_SENSOR;
    pucAdvertisingdata[3] = (uint8_t)strlen(*pcBuffer);
    memcpy(&pucAdvertisingdata[4], *pcBuffer, strlen(*pcBuffer));

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

    // SendHistoryDataToApp(unPressureResult, cJsonBuffer, strlen(cJsonBuffer)); //save to flash only if Mobile Phone is NOT connected
    
    printk("JSON:\n*%s#\n", *pcBuffer);
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
        printk("INFO: In history notification\n\r");
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
static void UpdateConfigParameters()
{
    cJSON *pConfigObject = NULL;
    char *cJsonConfigBuffer = NULL;
    uint8_t *pucConfigBuffer = NULL;
    uint32_t ulSleepTime = 0;
    char cBuffer[30] =  {0};
    uint32_t unPressureMin = 0;

    pConfigObject = cJSON_CreateObject();
    ulSleepTime = GetSleepTime();
    pucConfigBuffer = GetConfigBuffer();
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
       
#ifdef PMIC_ENABLED	       
       PMICInit();
#endif       
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