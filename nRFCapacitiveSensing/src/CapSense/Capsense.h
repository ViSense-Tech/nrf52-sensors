/**
 * @file    : Capsense.h
 * @brief   : File containing functions related to capacitive sensing
 * @author  : Adhil
 * @date    : 09-11-2023
 * @note 
*/

/***************************************INCLUDES*********************************/
#include "../Common.h"
/***************************************MACROS**********************************/

// This factor determines how quickly the rolling average will change based on the sampled input.
// A high value makes the average more stable, but means it takes longer to detect changes in the capacitance.
// If the value is too low it could make the average change too quickly, which is an issue when holding a button
// down for a long time.
#define ROLLING_AVG_FACTOR          2048

// This factor determines how many samples are needed for the capsense library to start to provide output.
#define INITIAL_CALIBRATION_TIME    50

// These factors decide how many successive high samples are needed for a capacitive button to be considered pressed. 
// A high value increases button stability, but also increases the latency of button presses. 
#define DEBOUNCE_ITERATIONS         3
#define DEBOUNCE_ITER_MASK          0x07

// This factor determines how much offset from the average it takes to consider a button pressed.
// A high value means the button must be pressed harder (reduced sensitivity), but reduces the chance of false button 
// presses caused by noise. 
#define HIGH_AVG_THRESHOLD          8

/***************************************TYPEDEFS*********************************/
typedef enum __eCapSenseEvt
{
    CAPSENSE_BUTTON_PRESSED,
    CAPSENSE_CALIBRATED
}_eCapSenseEvt;

typedef void (*CapSenseCallback)(_eCapSenseEvt eCapSenseEvt);

typedef struct __sCapSenseChannel
{
    uint32_t    ulInputPin;
    uint32_t    ulOutputPin;
    uint32_t    ulRollingAvg;
    uint32_t    ulAvg;
    uint32_t    ulAvgcounter;
    uint32_t    ulAvgInt;
    uint32_t    ulValue;
    uint32_t    ulValMax;
    uint32_t    ulValMin;
    uint32_t    ulValDebounceMsk; 
    bool        bPressed;
    uint32_t    ulChannelNum;
}_sCapSenseChannel;

typedef struct __sCapSenseConfig
{
    uint32_t ulInput;
    uint32_t ulOutput;
}_sCapSenseConfig;

/***************************************GLOBALS*********************************/

/***************************************FUNCTION DECLARTAION*********************/

/***************************************FUNCTION DEFINITIONS*********************/
// Function to initialize the capsense library.
bool CapSenseInit(_sCapSenseConfig *psCapSenseConfig);

// Function to set the callback which is triggered when one of the capsense channels registers a change.
bool CapSenseSetCallback(CapSenseCallback Callback);

// Function to initiate sampling of all the registered capsense channels. 
// Once sampling of all channels is complete the callback will be called if any change was registered. 
bool CapsenseSample(void);
void FinalizeSampling(uint32_t ulTimerCount, _sCapSenseChannel *psCapSenseChannel);
_sCapSenseChannel *GetCapSenseChannel();
void SetTouchSense(bool bStatus);
bool GetTouchSenseStatus();
