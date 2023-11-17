/**
 * @file    UartHandler.h
 * @brief   Uart related functions are defined here
 * @author  Adhil
 * @date    14-10-2023
 * @see     UartHandler.c
*/
#ifndef _UART_HANDLER_H
#define _UART_HANDLER_H

/***************************INCLUDES*********************************/
#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/drivers/uart.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

/***************************MACROS**********************************/


/***************************TYPEDEFS********************************/

/***************************FUNCTION DECLARATION*********************/
bool InitUart(void);
// bool ReadLocationData(char *pcLocation);
void SendData(const char *pcData);
bool IsRxComplete(void);
char *GetFlowRate(void);
void SetRxStatus(bool bStatus);
// bool ConvertNMEAtoCoordinates(char *pcLocData, float *pfLat, float *pfLon);
// bool ReadSOGData(float *pfSOG);

#endif

//EOF