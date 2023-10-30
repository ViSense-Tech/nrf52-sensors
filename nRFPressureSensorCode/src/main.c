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
//#define SLEEP_ENABLE  //Uncomment this line to enable sleep functionality
#define PRESSURE_SENSOR         0x01
// diagnostics
#define SENSOR_DIAGNOSTICS       (1<<0)
#define SENSOR_STATUS_OK        ~(1<<0)
#define TIME_STAMP_ERROR         (1<<1)
#define TIME_STAMP_OK           ~(1<<1)

/*******************************TYPEDEFS****************************************/

/*******************************GLOBAL VARIABLES********************************/
uint8_t flag = 0;
_sConfigData sConfigData = {0};
struct nvs_fs fs;    //file system
struct nvs_fs sConfigFs;
uint8_t *pucAdvertisingdata = NULL;
uint32_t diagnostic_data = 0;

/*******************************FUNCTION DEFINITIONS********************************/
static bool UpdateConfigurations();
static bool InitPowerManager();
static bool InitBle();
static void InitDataPartition();
static bool CheckForConfigChange();
static bool InitAllModules();

/*******************************FUNCTION DEFINITIONS********************************/

/**
 * @brief  Main function
 * @return int
*/
int main(void)
{
    int nError;
    int ReturnCode;
    uint16_t unPressureResult =0;
    uint32_t unPressureRaw = 0;
    char cbuffer[50] = {0};
    char *cJsonBuffer= NULL;
    char *cJsonConfigBuffer = NULL;
    cJSON *pMainObject = NULL;
    cJSON *pConfigObject = NULL;
    uint16_t data_count = 1;  // initialise data counter
    uint32_t count_max=50;  // max data to be stored
    uint32_t ulSleepTime = 0;
    char buf[ADV_BUFF_SIZE];
    long long llEpochNow = 0;
    uint32_t pressureMax = 929; //analog reading of pressure transducer at 100psi
    uint32_t pressureZero = 110; //analog reading of pressure transducer at 0psi

   if (!InitAllModules())
   {
        printk("ERROR: Initialising all modules failed \n\r");
   }

    if (!CheckForConfigChange())
    {
        printk("ERROR: Initialising all modules failed \n\r");
    }

    while (1) 
    {
        #ifdef SLEEP_ENABLE
        Timenow = sys_clock_tick_get();

        while(sys_clock_tick_get() - Timenow < (ALIVE_TIME * TICK_RATE))
        {
        #endif    
        if (!UpdateConfigurations())
        {
            printk("ERROR: Updating config failed\n\r");           
        }

        if (GetTimeUpdateStatus())
        {
            InitRtc();
            SetTimeUpdateStatus(false); 
            sConfigData.flag = sConfigData.flag | (1 << 4);
            int RetCode = nvs_write(&sConfigFs, 0, (char *)&sConfigData, sizeof(_sConfigData));
            diagnostic_data = diagnostic_data & (~(1<<4));
            printk("Time updated\n");
        }

        pConfigObject = cJSON_CreateObject();
        ulSleepTime = GetSleepTime();
        AddItemtoJsonObject(&pConfigObject, NUMBER, "PressureZero", &pressureZero, sizeof(uint32_t));
        AddItemtoJsonObject(&pConfigObject, NUMBER, "PressureMax", &pressureMax, sizeof(uint32_t));
        AddItemtoJsonObject(&pConfigObject, NUMBER, "sleeptime", &ulSleepTime, sizeof(uint32_t));
        cJsonConfigBuffer = cJSON_Print(pConfigObject);
        printk("ConfigJSON:\n%s\n", cJsonConfigBuffer);

        if (GetCurrenTimeInEpoch(&llEpochNow))
        {
           printk("CurrentTime=%llu\n\r", llEpochNow);
           diagnostic_data = diagnostic_data & TIME_STAMP_OK;
        }
        else
        {
            diagnostic_data = diagnostic_data | TIME_STAMP_ERROR;
        }

        if (GetPressureReading(&unPressureResult, &unPressureRaw))
        {
            printk("PressureRaw: %d\n", unPressureRaw);
        }

        pMainObject = cJSON_CreateObject();
        pressureZero = GetPressureZero();
        pressureMax = GetPressureMax();

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

        if(!IsConnected())              //save to flash only if Mobile Phone is NOT connected
        {
            memset(buf, '\0', sizeof(buf));
            writeJsonToFlash(&fs, data_count, count_max, cJsonBuffer, strlen(cJsonBuffer));
            k_msleep(50);
            if (readJsonToFlash(&fs, data_count, count_max, buf, strlen(cJsonBuffer)))
            {
                printk("\nId: %d, Stored_Data: %s\n",STRING_ID + data_count, buf);

            }
            data_count++; 

            if(data_count>= count_max || GetCharaStatus() == true ) 
            {

                deleteFlash(&fs,data_count,count_max);    
                k_msleep(10);
                data_count=0;
            }
        } 
        
        printk("JSON:\n%s\n", cJsonBuffer);

        if (IsConfigNotifyEnabled())
        {

            VisenseConfigDataNotify(cJsonConfigBuffer, (uint16_t)strlen(cJsonConfigBuffer));
        }
        
        if(IshistoryNotificationenabled())
        {
            VisenseHistoryDataNotify((uint16_t)strlen(cJsonBuffer));
            data_count = 0; 
        }

        if(IsNotificationenabled())
        {
           VisenseSensordataNotify(pucAdvertisingdata+2, ADV_BUFF_SIZE);
        }
        else if (!IsNotificationenabled() && !IsConnected())
        {
            UpdateAdvertiseData();
            StartAdvertising();
        }
        else
        {
            //NO OP
        }
        if (sConfigData.flag & (1 << 4))
        {
            //printk("\n\rError occured while reading config data: %d\n", rc);
            diagnostic_data = diagnostic_data | (1<<4);
            //k_sleep(K_SECONDS(30));
        }
        
        memset(pucAdvertisingdata, 0, ADV_BUFF_SIZE);
        cJSON_Delete(pMainObject);
        cJSON_Delete(pConfigObject);
        cJSON_free(cJsonBuffer);

        printk("PressureZero: %d\n", pressureZero);
        printk("PressureMax: %d\n", pressureMax);

            #ifndef SLEEP_ENABLE 
            k_sleep(K_MSEC(100));
            #endif
        #ifdef SLEEP_ENABLE
        }
        k_sleep(K_SECONDS(300));
        EnterSleepMode(uSleepTime);
        ExitSleepMode();
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

    if (IsPressureZeroSet() && IsPressureMaxSet() && IsSleepTimeSet())
    {
        // sConfigData.sleepTime = uSleepTime;
        sConfigData.sleepTime = GetSleepTime();
        sConfigData.pressureZero = GetPressureZero();
        sConfigData.pressureMax = GetPressureMax();
        SetPressureZeroSetStatus(false);
        SetPressureMaxSetStatus(false);
        
        //bSleepTimeSet = false;
        SetSleepTimeSetStataus(false);
        flag = flag | (1 << 0);
        sConfigData.flag = flag;

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

        nError = InitExtendedAdv();
        
        if (nError) 
        {
            printk("Advertising failed to create (err %d)\n", nError);
            break;
        }

        StartAdvertising();
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
    ulRetCode = readJsonToFlash(&sConfigFs, 0, 0, (char *)&sConfigData, sizeof(sConfigData)); 
    if(ulRetCode != sizeof(sConfigData))
    {
        printk("\n\rError occured while reading config data: %d\n", ulRetCode);
        diagnostic_data = diagnostic_data | (1<<4);
    }
    else
    {
        SetPressureZero(sConfigData.pressureZero);       
        SetPressureMax(sConfigData.pressureMax);
        SetSleepTime(sConfigData.sleepTime);
        printk("PressureZero = %d, PressureMax = %d\n",
                                     sConfigData.pressureZero, 
                                     sConfigData.pressureMax);
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