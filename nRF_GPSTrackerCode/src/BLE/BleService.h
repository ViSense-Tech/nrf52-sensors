/**
 * @file BleService.h
 * @brief File containing Visense service related handling
 * @author
 * @see BleService.c
 * @date 27-09-2023
*/

/**************************************INCLUDES******************************/
#include "BleHandler.h"
#include "JsonHandler.h"

/***************************************MACROS*******************************/
#define CONFIG_WRITE_OK  ~(1 << 0)
#define CONFIG_WRITE_FAILED  (1 << 0)
/**************************************TYPEDEFS******************************/

/*************************************FUNCTION DECLARATION*******************/
int VisenseSensordataNotify(uint8_t *pucSensorData, uint16_t unLen);
bool VisenseHistoryDataNotify(uint32_t ulWritePos);
void BleSensorDataNotify(const struct bt_gatt_attr *attr, uint16_t value);
int VisenseConfigDataNotify(uint8_t *pucCongigData, uint16_t unLen);
bool IsNotificationenabled();
bool IsConfigNotifyEnabled();
bool IshistoryNotificationenabled();
bool IsConnected();
bool IsConfigLat();
bool IsConfigLon();
void SetConfigChangeLat(bool);
void SetConfigChangeLon(bool);
bool IsFenceConfigured();
void SetFenceConfigStatus(bool bStatus);
void SetFenceCoordCount(int ucCount);
int GetCoordCount();
void ParseRcvdData();
void SetConfigStatus(bool bStatus);
bool GetConfigStatus();
void ParseFenceData();
void SendServerHistoryDataToApp(uint8_t *pucSensorData, uint16_t unLen);
