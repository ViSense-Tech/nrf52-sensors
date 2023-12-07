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


void BleSensorDataNotify(const struct bt_gatt_attr *attr, uint16_t value);
bool IsNotificationenabled();
bool IsConnected();
bool IsConfigLat();
bool IsConfiglon();
void SetConfigChangeLat(bool);
void SetConfigChangeLon(bool);
bool IsFenceConfigured();
void SetFenceConfigStatus(bool bStatus);
void SetFenceCoordCount(uint8_t ucCount);
uint8_t GetCoordCount();