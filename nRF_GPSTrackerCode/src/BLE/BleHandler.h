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
#define ADV_BUFF_SIZE           (300)
#define BT_UUID_CUSTOM_SERVICE_VAL \
	BT_UUID_128_ENCODE(0x1f1e5906, 0x98ad, 0x11ee, 0xb9d1, 0x0242ac120002)

/**************************************TYPEDEFS******************************/

/*************************************FUNCTION DECLARATION*******************/
// bool EnableBLE();
uint8_t *GetAdvertisingBuffer();
int InitExtendedAdv(void);
int StartAdvertising(void);
int UpdateAdvertiseData(void);
bool BleStopAdvertise();

#endif