/**
 * @file BleService.h
 * @brief File containing Visense service related handling
 * @author
 * @see BleService.c
 * @date 27-09-2023
*/

/**************************************INCLUDES******************************/
#include "BleHandler.h"

/***************************************MACROS*******************************/
#define NOTIFY_BUFFER_SIZE        247
#define CONFIG_WRITE_FAILED       (1 << 0)
#define CONFIG_WRITE_OK        ~(1 << 0)
/**************************************TYPEDEFS******************************/

/*************************************FUNCTION DECLARATION*******************/
int VisenseSensordataNotify(uint8_t *pucSensorData, uint16_t unLen);
void BleSensorDataNotify(const struct bt_gatt_attr *attr, uint16_t value);
bool IsNotificationenabled();
bool IsConnected();
bool IsConfigNotifyEnabled();
int VisenseConfigDataNotify(uint8_t *pucConfigData, uint16_t unLen);
bool IshistoryNotificationenabled();
bool VisenseHistoryDataNotify(uint32_t);
