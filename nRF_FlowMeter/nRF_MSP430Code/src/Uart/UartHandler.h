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
void SendData(const char *pcData);
bool IsRxComplete(void);
char *GetFlowRate(void);
void SetRxStatus(bool bStatus);
double GetMinGPM();
void SetMinGPM(double dGPMVal);

#endif

//EOF