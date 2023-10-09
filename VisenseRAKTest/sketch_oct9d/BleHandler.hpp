/**
* @file   BleHandler.h
* @brief  Ble related functions handled here
* @author Adhil
* @date   09-10-2023
* @note
*/

/**************************************INCLUDES**************************************/
#include <bluefruit.h>

/************************************MACROS*****************************************/


/************************************GLOBALS****************************************/


/***********************************FUNCTION DECLARATION****************************/
void SetupViseneService(void);
//void ble_start_advertisement(void);
bool BleEnable();
bool SetupScan();
void BleStartAdvertising(void);
bool IsBleConnected();
bool IsCentalConnected();
bool BleSensorNotifydata(uint8_t *pucBuffer, uint16_t unLength);
