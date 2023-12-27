/**
 * @file    GPSHandler.c
 * @brief   GPS related functions are handled here
 * @author  Adhil
 * @date    14-10-2023
 * @see     GSPHandler.h
*/

/***************************INCLUDES*********************************/
#include "GPSHandler.h"
#include<math.h>
#include "JsonHandler.h"
#include "BleService.h"

/***************************MACROS***********************************/
#define MSG_SIZE 255

/****************************TYPEDEFS********************************/
typedef enum __eRxState
{
 START,
 RCV,
 END
}_eRxState;

#ifdef HAVERSINE
/*haversine function takes in a location and sets a geofence as a circle or raduis dDistance*/
 double hardcodedLat = 10.055555555555557;  
 double hardcodedLon = -76.35472222222222;
 double dDistance=0;
 #define EARTH_RADIUS 6371000.0
#endif
#define M_PI		3.14159265358979323846
#define SCALING_FACTOR 100000000000000.0


/****************************GLoBALS*********************************/
static const struct device *const psUartDev = DEVICE_DT_GET(DT_NODELABEL(uart0));
/* receive buffer used in UART ISR callback */
static char cRxBuffer[MSG_SIZE] = {0};
static int nRxBuffIdx = 0;
static bool bRxCmplt = false;
static _eRxState RxState = START;
static float fSOG = 0.0;


double latitude;
double longitude;

int fence;
char cumulativeAngle[12];
int targetStatus;

/***************************FUNCTION DECLARATION*********************/
static void ReadGPSPacket(uint8_t ucByte);

/*****************************FUNCTION DEFINITION***********************/
/**
 * @brief Check if device is inside of fence
 * @param None
 * @return status of device inside of fence
*/
int IsDeviceInsideofFence()
{
    return targetStatus;
}

/**
 * @brief Set SOG value
 * @param fVal : SOG value
 * @return None
*/
void SetSogMax(float fVal)
{
    fSOG = fVal;
}

/**
 * @brief Get SOG value
 * @param None
 * @return SOG value
*/
float GetSogMax()
{
    return fSOG;
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
 * @brief Convert NMEA format of degrees minutes to coordinates
 * @param pcLocData : Location data
 * @param pfLat     : Latitude coordinate
 * @param pfLon     : Longitude coordinate
 * @return true for success
*/
bool ConvertNMEAtoCoordinates(char *pcLocData, double *pfLat, double *pfLon)
{
    char *cSubstr = NULL;
    bool bRetVal = false;
    double fDegrees = 0.00;
    double fMinutes = 0;
    int temp = 0;


    if (pcLocData && pfLat && pfLon)
    {
        cSubstr = strtok(pcLocData, ",");

        if (cSubstr == NULL)
        {
            return bRetVal;
        }
        
        *pfLat = atof(cSubstr);
        printk("Latitude %f\n\r", *pfLat);
        fDegrees = *pfLat;
        temp = fDegrees/100;
        fMinutes = fDegrees/ 100;
        fMinutes = fMinutes - temp;
        fMinutes = fMinutes * 100;
        //printk("min: %f", fMinutes);
        *pfLat = temp + (fMinutes/60);
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
            printk("Longtude %f\n\r", *pfLon);
            fDegrees = *pfLon;
            temp = fDegrees/100;
            fMinutes = fDegrees/ 100;
            fMinutes = fMinutes - temp;
            fMinutes = fMinutes * 100;
          //  printk("min: %f", fMinutes);
            *pfLon = temp + (fMinutes/60);
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
       // printk("%c", (char)ucByte);
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

        if (cSubString == NULL)
        {
            cSubString = strstr(cRxBuffer, "$GPGGA");
        }

        if (cSubString != NULL)
        {
            memcpy(pcLocation, cSubString, strlen(cSubString));
            for (ucIdx = 0; pcLocation[ucIdx] != ','; ucIdx++);
            ucIdx++;
            memcpy(pcLocation, pcLocation+ucIdx, strlen(pcLocation+ucIdx));
            for (ucIdx = 0; pcLocation[ucIdx] != ','; ucIdx++);
            ucIdx++;
            memcpy(pcLocation, pcLocation+ucIdx, strlen(pcLocation+ucIdx));

            if (strchr(pcLocation, 'E') != NULL || strchr(pcLocation, 'W') != NULL && strchr(pcLocation, 'N') != NULL)
            {
                for (ucIdx = 0; (pcLocation[ucIdx] != 'E') && (pcLocation[ucIdx] != 'W'); ucIdx++);
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
        pcSubString = strstr(cRxBuffer, "$GNRMC");

        if (pcSubString == NULL)
        {
            pcSubString = strstr(cRxBuffer, "$GPRMC");
        }

        if (pcSubString != NULL)
        {
            pcSOGData = strchr(pcSubString, 'E');

            if (pcSOGData == NULL)
            {
                pcSOGData = strchr(pcSubString, 'W');
            }

            if (pcSOGData != NULL)
            {
                pcSOGData++;
                memcpy(cSOG, pcSOGData, strlen(pcSOGData));
                
                if (cSOG[0] == ',' && cSOG[1] != ',')
                {
                    for (ucIdx = 1; cSOG[ucIdx] != ','; ucIdx++);
                    ucIdx++;
                    memcpy(cSOG, cSOG+1, strlen(cSOG+1));
                  //  printk("SOG str: %s\n\r", cSOG);
                    memset(cSOG+ucIdx, '\0', strlen(cSOG+ucIdx));
                    *pfSOG = atof(cSOG);
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

#ifdef HAVERSINE 
/**
 * @brief  haversine Distance calculation to find if the device is inside the fence or not
 * @param  None
 * @return 0 on exit
*/
double haversineDistance(double lat1, double lon1, double lat2, double lon2) {                                     
    double dLat = deg2rad(lat2 - lat1);
    double dLon = deg2rad(lon2 - lon1);
    
    double a = sin(dLat / 2) * sin(dLat / 2) + cos(deg2rad(lat1)) * cos(deg2rad(lat2)) * sin(dLon / 2) * sin(dLon / 2);
    double c = 2 * atan2(sqrt(a), sqrt(1 - a));
    
    double distance = EARTH_RADIUS * c;
    return distance;
}
#endif

/**
 * @brief  Point-in-polygon algorithm
 * @param  None
 * @return 0 on exit
*/
bool polygonPoint(double latitude, double longitude, int fenceSize) 
{
    double vectors[fenceSize][2];
	_sFenceData *psFenceData = NULL;
    double angle = 0;
    double num, den;

    psFenceData = GetFenceTable();
    for(int i = 0; i < fenceSize; i++) 
    {
        vectors[i][0] = (psFenceData->dLatitude)- latitude;
        vectors[i][1] = (psFenceData->dLongitude) - longitude;         
        psFenceData++;
    }
    
    for(int i = 0; i < fenceSize; i++) 
    {
        num = (vectors[i % fenceSize][0]) * (vectors[(i + 1) % fenceSize][0]) + (vectors[i % fenceSize][1]) * (vectors[(i + 1) % fenceSize][1]);
        den = (sqrt(pow(vectors[i % fenceSize][0], 2) + pow(vectors[i % fenceSize][1], 2))) * 
              (sqrt(pow(vectors[(i + 1) % fenceSize][0], 2) + pow(vectors[(i + 1) % fenceSize][1], 2)));

        angle = angle + (180 * acos(num / den) / M_PI);
    }

    if (angle > 355 && angle < 365) { 
        targetStatus = 1;
    } else {
        targetStatus = 0;
    }

    printk("Target: %d\n\r",targetStatus);
    printk("Angle: %lf\n\r",angle);
    return targetStatus;
}
