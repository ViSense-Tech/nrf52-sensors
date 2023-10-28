/**
 * @file main.c
 * @brief Main function
 * @date 2023-21-09
 * @author Jeslin
 * @note  This is a test code for pressure sensor.
*/


/*******************************INCLUDES****************************************/
#include <zephyr/device.h>
#include <zephyr/pm/pm.h>
#include <zephyr/pm/device.h>
#include <zephyr/devicetree.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/kernel.h>
#include <zephyr/sys/printk.h>
#include <zephyr/sys/util.h>
#include <nrfx_example.h>
#include <saadc_examples_common.h>
#include <nrfx_saadc.h>
#include <nrfx_log.h>
#include <stdlib.h>
#include <stdio.h>
#include "BleHandler.h"
#include "BleService.h"
#include "JsonHandler.h"
#include "RtcHandler.h"
#include "nvs_flash.h"


/*******************************MACROS****************************************/
#define INFOLITZ_EDIT //Comment this line to disable our changes
//#define SLEEP_ENABLE  //Uncomment this line to enable sleep functionality
#define ADC_MAX_VALUE 1023
#define PRESSURE_SENSOR 0x01
#define PRESSURE_SAMPLE_COUNT 10

// diagnostics
#define SENSOR_DIAGNOSTICS (1<<0)
#define SENSOR_STATUS_OK    ~(1<<0)
#define TIME_STAMP_ERROR   (1<<1)
#define TIME_STAMP_OK      ~(1<<1)

/*******************************TYPEDEFS****************************************/

/*******************************GLOBAL VARIABLES********************************/

#ifndef INFOLITZ_EDIT
    const int pressureMax = 929; //analog reading of pressure transducer at 100psi
    const int pressureZero = 110; //analog reading of pressure transducer at 0psi
#else
    static uint32_t pressureZero = 119; //analog reading of pressure transducer at 0psi
                              //PressureZero = 0.5/3.3V*1024~150(supply voltage - 3.3v) taken from Arduino code refernce from visense 
    static uint32_t pressureMax = 564; //analog reading of pressure transducer at 100psi
                             //PressureMax = 2.5/3.3V*1024~775  taken from Arduino code refernce from visense       
#endif

const int pressuretransducermaxPSI = 70; //psi value of transducer being used
cJSON *pcData = NULL;
const struct device *pAdc = NULL;
const struct gpio_dt_spec sSleepStatusLED = GPIO_DT_SPEC_GET(DT_ALIAS(led0), gpios);
void setPressureZero(uint32_t ucbuff);
void setPressureMax(uint32_t ucbuff);
bool bPressureZeroSet = false;
bool bPressureMaxSet = false;
uint8_t flag = 0;
typedef struct __attribute__((packed)) __sConfigData
{
    uint64_t ullLastUpdatedTimeStamp;
    uint32_t pressureZero;
    uint32_t pressureMax;
    uint8_t flag;
}_sConfigData;


struct nvs_fs fs;    //file system
/*******************************FUNCTION DEFINITIONS********************************/

/**
 * @brief  This function is to read raw adc value
 * @param  None 
 * @return uint16_t - ADC result
*/
uint16_t AnalogRead(void)
{
    nrfx_err_t status;
    uint32_t sample_value;

    status = nrfx_saadc_buffer_set(&sample_value, 1);
    NRFX_ASSERT(status == NRFX_SUCCESS);
    status = nrfx_saadc_mode_trigger();
    NRFX_ASSERT(status == NRFX_SUCCESS);

    return sample_value;
}
/**
 * @brief Setting pressureZero
 * @param ucbuffer - buffer for setting pressureZero
 * @return void
*/
void SetPressureZero(uint32_t ucbuffer)
{
    pressureZero = ucbuffer;
    bPressureZeroSet = true;
    // writeJsonToFlash(&fs, 82, 0, (char *) &pressureZero, sizeof(pressureZero));
}
/**
 * @brief Setting pressureMax
 * @param ucbuffer - buffer for setting pressureMax
 * @return void
*/
void SetPressureMax(uint32_t ucbuffer)
{
    pressureMax = ucbuffer;
    bPressureMaxSet = true;
    // writeJsonToFlash(&fs, 83, 0, (char *) &pressureMax, sizeof(pressureMax));
}

/*
 * @brief Setting Power management policy
 * @param void
 * @return true or false
*/
static bool SetPMState()
{
    bool bRetVal = false;

    struct pm_state_info info =
    {
        .exit_latency_us  = 0,
        .min_residency_us = 0,
        .state            = PM_STATE_SUSPEND_TO_RAM,
        .substate_id      = 0,
    };

    bRetVal = pm_state_force(0, &info);
    return bRetVal;
}

/**
 * @brief function for entering sleep mode
 * @param nDuration - Duration for sleep
 * @return none
*/
static void EnterSleepMode(int nDuration)
{
    pm_device_action_run(pAdc, PM_DEVICE_ACTION_SUSPEND);
    BleStopAdvertise();
    gpio_pin_set(sSleepStatusLED.port, sSleepStatusLED.pin, 1);
    k_sleep(K_SECONDS(nDuration));
}

/**
 * @brief function for exiting sleep mode
 * @return none
*/
static void ExitSleepMode()
{
    pm_device_action_run(pAdc, PM_DEVICE_ACTION_RESUME);
    gpio_pin_set(sSleepStatusLED.port, sSleepStatusLED.pin, 0);
}

/**
 * @brief function to initialize adc
 * @return void
*/
static void InitADC()
{
    nrfx_err_t status;
    status = nrfx_saadc_init(NRFX_SAADC_DEFAULT_CONFIG_IRQ_PRIORITY);
    NRFX_ASSERT(status == NRFX_SUCCESS);

    nrfx_saadc_channel_t saadc_channel = 
    {
        .channel_config = 
        {
            .resistor_p        = NRF_SAADC_RESISTOR_DISABLED,
            .resistor_n        = NRF_SAADC_RESISTOR_DISABLED,
            .gain              = NRF_SAADC_GAIN1_6,
            .reference         = NRF_SAADC_REFERENCE_VDD4,
            .acq_time          = NRF_SAADC_ACQTIME_10US,
            .mode              = NRF_SAADC_MODE_SINGLE_ENDED,
            .burst             = NRF_SAADC_BURST_DISABLED,
        },
        .pin_p             = NRF_SAADC_INPUT_AIN1,
        .pin_n             = NRF_SAADC_INPUT_DISABLED,
        .channel_index     = 1
    };

    status = nrfx_saadc_channel_config(&saadc_channel);
    NRFX_ASSERT(status == NRFX_SUCCESS);
    
    uint32_t channels_mask = nrfx_saadc_channels_configured_get();
    status = nrfx_saadc_simple_mode_set(channels_mask,
                                        NRF_SAADC_RESOLUTION_10BIT,
                                        NRF_SAADC_OVERSAMPLE_DISABLED,
                                        NULL);
    NRFX_ASSERT(status == NRFX_SUCCESS);
}
bool GetPressureReading(uint16_t *unPressureResult, uint32_t *unPressureRaw)
{
    uint16_t unAdcSample = 0;
    uint16_t unPressureSample = 0;
    uint8_t count = 0;
    *unPressureRaw = 0;
    *unPressureResult = 0;
    
    for (uint8_t i = 0; i < PRESSURE_SAMPLE_COUNT; i++)
    {
        
        unAdcSample = AnalogRead();

        if (unAdcSample > pressureZero && unAdcSample < ADC_MAX_VALUE)
        {
            unPressureSample += ((unAdcSample)-(pressureZero))*(pressuretransducermaxPSI)/(pressureMax-pressureZero);
            count++;
            *unPressureRaw += unAdcSample;   
        }
        k_msleep(100);
    }
    if (count == 0)
    {
        *unPressureRaw = unAdcSample; 
        return false;
    }
    else
    {
        *unPressureRaw = *unPressureRaw/count;
        *unPressureResult = unPressureSample/count;
        return true;
    }
}

/**
 * @brief  Main function
 * @return int
*/
int main(void)
{
    int nError;
    uint16_t unPressureResult =0;
    uint32_t unPressureRaw = 0;
    char cbuffer[50] = {0};
    char *cJsonBuffer= NULL;
    uint8_t *pucAdvertisingdata = NULL;
    cJSON *pMainObject = NULL;
    uint32_t diagnostic_data = 0;
    uint16_t data_count = 1;  // initialise data counter
    uint32_t count_max=50;  // max data to be stored
    char buf[ADV_BUFF_SIZE];
    _sConfigData sConfigData = {0};
    
    //cJSON_Hooks *pJsonHook. = NULL; 
    long long llEpochNow = 0;

    
    SetPMState();
    pucAdvertisingdata = GetAdvertisingBuffer();
    InitADC();
    k_sleep(K_TICKS(100));
    pAdc = device_get_binding("arduino_adc");

    if (!EnableBLE())
    {
        printk("Bluetooth init failed (err %d)\n", nError);
        return 0;
    }

    nError = InitExtendedAdv();
	if (nError) 
    {
		printk("Advertising failed to create (err %d)\n", nError);
		return 0;
	}
     nvs_initialisation(&fs); 
    sprintf(cbuffer,"%dpsi", unPressureResult);
    StartAdvertising();
    gpio_pin_configure_dt(&sSleepStatusLED, GPIO_ACTIVE_LOW);
    //cJSON_InitHooks(pJsonHook);   
    GetFileSystem(&fs);

	fs.offset = NVS_PARTITION_OFFSET;
    k_msleep(100);
    int rc = readJsonToFlash(&fs, 0, 0, (char *)&sConfigData, sizeof(sConfigData)); 
    if((rc==sizeof(sConfigData)) || (sConfigData.flag & (1 << 0)))
    {
        printk("\n\rPressureZero: %d\n", sConfigData.pressureZero);
        printk("\n\rPressureMax: %d\n", sConfigData.pressureMax);
        printk("\n\rFlag: %d\n", sConfigData.flag);
        pressureZero = sConfigData.pressureZero;       
        pressureMax = sConfigData.pressureMax;
    
    }
    else
    {
        printk("\n\rError occured while reading config data: %d\n", rc);
        //return 0;
    }
    
    if(rc == sizeof(sConfigData) || sConfigData.flag & (1<<4))
    {
        diagnostic_data = diagnostic_data & (~(1<<4));   
    }
    else
    {
        diagnostic_data = diagnostic_data | (1<<4);
    }

    fs.offset = NVS_PARTITION_OFFSET + 4096;


    while (1) 
    {
        if (bPressureZeroSet && bPressureMaxSet)
        {
           
            sConfigData.pressureZero = pressureZero;
            sConfigData.pressureMax = pressureMax;
            
            bPressureZeroSet = false;
            bPressureMaxSet = false;
            flag = flag | (1 << 0);
            sConfigData.flag = flag;
            fs.offset = NVS_PARTITION_OFFSET;
            int rc= nvs_write(&fs, 0, (char *)&sConfigData, sizeof(_sConfigData));
            printk("Size of written buf:%d\n",rc);
            k_msleep(1000);
            rc = nvs_read(&fs, 0, (char *)&sConfigData, sizeof(_sConfigData));

            fs.offset = NVS_PARTITION_OFFSET + 4096;
        }
        
        if (GetTimeUpdateStatus())
        {
            InitRtc();
            SetTimeUpdateStatus(false); 
            fs.offset = NVS_PARTITION_OFFSET;
            sConfigData.flag = sConfigData.flag | (1 << 4);
            int rc= nvs_write(&fs, 0, (char *)&sConfigData, sizeof(_sConfigData));
            fs.offset = NVS_PARTITION_OFFSET + 4096;
            diagnostic_data = diagnostic_data & (~(1<<4));
            printk("Time updated\n");
        }
        


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
        AddItemtoJsonObject(&pMainObject, NUMBER, "ADCValue", &unPressureRaw, sizeof(uint16_t));
        AddItemtoJsonObject(&pMainObject, NUMBER, "PressureZero", &pressureZero, sizeof(uint32_t));
        AddItemtoJsonObject(&pMainObject, NUMBER, "PressureMax", &pressureMax, sizeof(uint32_t));
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
        //cJsonBuffer = malloc(150 * sizeof(uint8_t));
        cJsonBuffer = cJSON_Print(pMainObject);
        pucAdvertisingdata[2] = PRESSURE_SENSOR;
        pucAdvertisingdata[3] = (uint8_t)strlen(cJsonBuffer);
        memcpy(&pucAdvertisingdata[4], cJsonBuffer, strlen(cJsonBuffer));
        //printk("JSON:\n%s\n", cJsonBuffer);
        if(!IsConnected())              //save to flash only if Mobile Phone is NOT connected
        {
            fs.offset = NVS_PARTITION_OFFSET + 4096;
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
            fs.offset = NVS_PARTITION_OFFSET;
        } 
        
        printk("JSON:\n%s\n", cJsonBuffer);

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
        
        memset(pucAdvertisingdata, 0, ADV_BUFF_SIZE);

        cJSON_Delete(pMainObject);
        cJSON_free(cJsonBuffer);
        
        //k_sleep(K_MSEC(1000));
        printk("PressureZero: %d\n", pressureZero);
        printk("PressureMax: %d\n", pressureMax);

        #ifdef SLEEP_ENABLE
         k_sleep(K_SECONDS(300));
         EnterSleepMode(3600);
         ExitSleepMode();
        #endif
    }
}