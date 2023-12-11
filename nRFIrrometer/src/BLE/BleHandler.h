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
#define ADV_BUFF_SIZE           (247)
#define BT_UUID_CUSTOM_SERVICE_VAL \
	BT_UUID_128_ENCODE(0xb484afa8, 0x5dee, 0x11ee, 0x8c99, 0x0242ac120002)
//#define EXT_ADV               /*Uncomment this line to enable extended advertising*/

/**************************************TYPEDEFS******************************/

/*************************************FUNCTION DECLARATION*******************/
bool EnableBLE();
uint8_t *GetAdvBuffer();
int InitExtAdv(void);
int StartAdv(void);
int UpdateAdvData(void);
bool BleStopAdv();


#endif