/**
 * @file BleHandler.h
 * @author 
 * @brief
 * @date 27-09-2023
 * @see BleHandler.c
*/
#ifndef _BLE_HANDLER_H
#define _BLE_HANDLER_H

/**************************************INCLUDES******************************/
#include <stdbool.h>
#include <zephyr/bluetooth/bluetooth.h>
#include <zephyr/bluetooth/hci.h>
#include <zephyr/bluetooth/conn.h>
#include <zephyr/bluetooth/uuid.h>
#include <zephyr/bluetooth/gatt.h>

/***************************************MACROS*******************************/
#define ADV_BUFF_SIZE           (180)
// #define EXTENDED_ADV
/**************************************TYPEDEFS******************************/
#define BT_UUID_CUSTOM_SERVICE_VAL \
	BT_UUID_128_ENCODE(0xe076567e, 0x5d3b, 0x11ee, 0x8c99, 0x0242ac120002)

/*************************************FUNCTION DECLARATION*******************/
bool EnableBLE();
uint8_t *GetAdvertisingBuffer();
int InitExtendedAdv(void);
int StartAdvertising(void);
int UpdateAdvertiseData(void);
bool BleStopAdvertise();

#endif