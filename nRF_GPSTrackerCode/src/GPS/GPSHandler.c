/**
 * @file    GPSHandler.c
 * @brief   GPS related functions are handled here
 * @author  Adhil
 * @date    14-10-2023
 * @see     GSPHandler.h
*/

/***************************INCLUDES*********************************/
#include "GPSHandler.h"

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
static int nRxBuffIdx = 0;
static bool bRxCmplt = false;
static _eRxState RxState = START;

/***************************FUNCTION DECLARATION*********************/
static void ReadGPSPacket(uint8_t ucByte);

/*****************************FUNCTION DEFINITION***********************/
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
 * @brief Convert NMEA format of degrees minutes to coordinates
 * @param pcLocData : Location data
 * @param pfLat     : Latitude coordinate
 * @param pfLon     : Longitude coordinate
 * @return true for success
*/
bool ConvertNMEAtoCoordinates(char *pcLocData, float *pfLat, float *pfLon)
{
    char *cSubstr = NULL;
    bool bRetVal = false;
    float fDegrees = 0.00;
    float fMinutes = 0;

    if (pcLocData && pfLat && pfLon)
    {
        cSubstr = strtok(pcLocData, ",");

        if (cSubstr == NULL)
        {
            return bRetVal;
        }
        
        *pfLat = atof(cSubstr);
        fDegrees = *pfLat;
        fMinutes = (int)fDegrees%100;
        *pfLat = ((int)fDegrees/100) + (fMinutes/60);
        cSubstr = strtok(NULL, ",");

        if (cSubstr == NULL)
        {
            return bRetVal;
        } 

        cSubstr = strtok(NULL, ",");

        if (cSubstr == NULL)
        {
            return bRetVal;
        }

        if (strlen(cSubstr) > 2)
        {
            *pfLon = atof(cSubstr);
            fDegrees = *pfLon;
            fMinutes = (int)fDegrees%100;
            *pfLon = ((int)fDegrees/100) + (fMinutes/60);
            bRetVal = true;
        }
    }

    return bRetVal;
}

/**
 * @brief Read GPS Packet
 * @param ucByte : byte read
 * @return None
*/
static void ReadGPSPacket(uint8_t ucByte)
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
                    break;

        default:    break;            
    }
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
        ReadGPSPacket(ucByte);
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
 * @brief Read Location data
 * @param None
 * @return true for success
*/
bool ReadLocationData(char *pcLocation)
{
    bool bRetVal = false;
    char *cSubString = NULL;
    uint8_t ucIdx = 0;

    if (bRxCmplt)
    {
        cSubString = strstr(cRxBuffer, "$GNGGA");
        if (cSubString != NULL)
        {
            memcpy(pcLocation, cSubString, strlen(cSubString));
            for (ucIdx = 0; pcLocation[ucIdx] != ','; ucIdx++);
            ucIdx++;
            memcpy(pcLocation, pcLocation+ucIdx, strlen(pcLocation+ucIdx));
            for (ucIdx = 0; pcLocation[ucIdx] != ','; ucIdx++);
            ucIdx++;
            memcpy(pcLocation, pcLocation+ucIdx, strlen(pcLocation+ucIdx));

            if (strchr(pcLocation, 'E') != NULL && strchr(pcLocation, 'N') != NULL)
            {
                for (ucIdx = 0; pcLocation[ucIdx] != 'E'; ucIdx++);
                ucIdx++;
                memset(pcLocation+ucIdx, '\0', strlen(pcLocation+ucIdx));
            }
            else
            {
                //strcpy(pcLocation, "xxxxxxxxx,N,xxxxxxxxxx,E");
            }
        }
        bRxCmplt = false;
        bRetVal = true;
    }

    return bRetVal;
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

bool ReadSOGData(float *pfSOG)
{
    bool bRetVal = false;
    char *pcSubString = NULL;
    char *pcSOGData = NULL;
    char cSOG[50] = {0};
    uint8_t ucIdx = 0;

    if (bRxCmplt)
    {
        //printk(cRxBuffer);
        //printk("\n\r");
        pcSubString = strstr(cRxBuffer, "$GNRMC");

        if (pcSubString != NULL)
        {
            pcSOGData = strchr(pcSubString, 'E');

            if (pcSOGData != NULL)
            {
                pcSOGData++;
                memcpy(cSOG, pcSOGData, strlen(pcSOGData));

                if (cSOG[0] == ',' && cSOG[1] != ',')
                {
                    for (ucIdx = 1; cSOG[ucIdx] != ','; ucIdx++);
                    ucIdx++;
                    memset(cSOG+ucIdx, '\0', strlen(cSOG+ucIdx));
                    *pfSOG = atof(cSOG);
                    printk("SOG %f\n\r", *pfSOG);
                    bRetVal = true;
                }
                else
                {
                    *pfSOG = 0.00;
                }
            }
        }

        bRxCmplt = false;
    }

    return bRetVal;
}