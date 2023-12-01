/**
 * @file    UartHandler.c
 * @brief   Uart related functions are defined here
 * @author  Adhil
 * @date    14-10-2023
 * @see     UartHandler.h
*/

/***************************INCLUDES*********************************/
#include "UartHandler.h"

/***************************MACROS***********************************/
#define MSG_SIZE 255

/****************************TYPEDEFS********************************/
typedef enum __eRxState
{
 START,
 RCV,
 END
}_eRxState;


/****************************GLoBALS*********************************/
static const struct device *const psUartDev = DEVICE_DT_GET(DT_NODELABEL(uart0));
/* receive buffer used in UART ISR callback */
static char cRxBuffer[MSG_SIZE] = {0};
char cFlowRate[MSG_SIZE] = {0};
static int nRxBuffIdx = 0;
static bool bRxCmplt = false;
static _eRxState RxState = START;
static double dMinGPM = 10.000;

/***************************FUNCTION DECLARATION*********************/

/*****************************FUNCTION DEFINITION***********************/
/**
 * @brief Getting min GPM value
 * @param None
 * @return GPM minimum value;
*/
double GetMinGPM()
{
    return dMinGPM;
}

/**
 * @brief Setting GPM value 
 * @param dGPMVal : GPM min value to set
 * @return None
*/
void SetMinGPM(double dGPMVal)
{
    dMinGPM = dGPMVal;
}
/**
 * @brief  Send data via uart
 * @param  pcData : data to send
 * @return None
*/
void SendData(const char *pcData)
{
    uint8_t ucLength, index = 0;

    if (pcData)
    {
        ucLength = strlen(pcData);

        for (index = 0; index < ucLength; index++)
        {
            uart_poll_out(psUartDev, *(pcData++));
            k_usleep(50);
        }
    }
}

/**
 * @brief Set Rx status
 * @param bStatus : status
 * @return None
*/
void SetRxStatus(bool bStatus)
{
    bRxCmplt = bStatus;
}

/**
 * @brief Read GPS Packet
 * @param ucByte : byte read
 * @return None
*/
static void ReadFlowRate(uint8_t ucByte)
{
    switch(RxState)
    {
        case START: if (ucByte == '$' && bRxCmplt == false)
                    {
                        nRxBuffIdx = 0;
                        memset(cRxBuffer, 0, sizeof(cRxBuffer));
                        RxState = RCV;
                        cRxBuffer[nRxBuffIdx++] = ucByte;
                    }
                    break;

        case RCV:   if (ucByte == '\r' || ucByte =='\n')
                    {
                        cRxBuffer[nRxBuffIdx++] = '\0';
                        bRxCmplt = true;
                        RxState = END;
                    }
                    cRxBuffer[nRxBuffIdx++] = ucByte;
                    break;

        case END:   RxState = START;
                    nRxBuffIdx = 0;
                    break;

        default:    break;            
    }
}
/**
 * @brief  Get Rx Status
 * @param  None
 * @return true for success
*/
bool IsRxComplete(void)
{
    return bRxCmplt;
}

/**
 * @brief  Get flow rate
 * @param  None
 * @return pointer to string
*/
char *GetFlowRate(void)
{
    return cRxBuffer;
}

/**
 * @brief  Recieve byte 
 * @param  None
 * @return true for success
*/
bool ProcessRxdData(void)
{
    uint8_t ucByte = 0;
    bool bRetval = false;
        /* read until FIFO empty */
    if (uart_fifo_read(psUartDev, &ucByte, 1) > 0) 
    {
        ReadFlowRate(ucByte);
        bRetval = true;
    }

    return bRetval;
}

/**
 * @brief Serial reception callback
 * @param psUartDev  : Uart Device handle
 * @param pvUserData : argyment to uart reception callback
 * @return None
*/
void ReceptionCallback(const struct device *psUartDev, void *pvUserData)
{
    if (psUartDev)
    {
        if (!uart_irq_update(psUartDev)) 
        {
            return;
        }

        if (!uart_irq_rx_ready(psUartDev)) 
        {
            return;
        }

        if (!ProcessRxdData())
        {
            printk("Uart reception failed\n\r");
        }
    }
}

/**
 * @brief  Initialising uart 
 * @param  None
 * @return true for success
*/
bool InitUart(void)
{
    int nRetVal = 0;
    bool bRetVal = false;

    do 
    {
        if (!device_is_ready(psUartDev)) 
        {
            printk("UART device not found!");
            break;
        }

        nRetVal = uart_irq_callback_user_data_set(psUartDev, ReceptionCallback, NULL);

        if (nRetVal < 0) 
        {
            if (nRetVal == -ENOTSUP) 
            {
                printk("Interrupt-driven UART API support not enabled\n");
            } 
            else if (nRetVal == -ENOSYS) 
            {
                printk("UART device does not support interrupt-driven API\n");
            } 
            else 
            {
                printk("Error setting UART callback: %d\n", nRetVal);
            }
            break;
        }

        uart_irq_rx_enable(psUartDev);
        bRetVal = true;
    } while(0);

    return bRetVal;
}