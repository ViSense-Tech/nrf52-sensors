/**
 * @file    Accelerometer.h
 * @brief   Accelerometer related functions are handled here
 * @author  Adhil
 * @date    17-10-2023
 * @see     Accelerometer.c
*/

/***************************INCLUDES*********************************/
#include "LCDHandler.h"
#include "Accelerometer.h"

/***************************MACROS**********************************/

/***************************TYPEDEFS********************************/

/***************************GLOBALS*********************************/


/***************************FUNCTION DECLARATION*********************/

/***************************FUNCTION DEFINITION**********************/

/**
 * @brief initialize accelerometer
 * @param None
 * @return true for success
*/
bool InitAcclerometer() 
{
    bool bRetVal = false;
    struct device *psI2CDevice = NULL;

    do
    {
        psI2CDevice = GetI2CDevice();

        if (psI2CDevice == NULL)
        {
            printk("Getting i2c handle failed\n\r");
           break;
        }
        if (0 != i2c_reg_write_byte(psI2CDevice, ACCLMTR_DEV_ADDR, ACCLMTR_POWER_CTL_REG, 0x00))
        {
            printk("writing power ctl register failed\n\r");
            break;
        }
        if (0 != i2c_reg_write_byte(psI2CDevice, ACCLMTR_DEV_ADDR, ACCLMTR_POWER_CTL_REG, 0x08))
        {
            printk("writing power ctl register failed\n\r");
            break;
        }
        if (0 != i2c_reg_write_byte(psI2CDevice, ACCLMTR_DEV_ADDR, ACCLMTR_DATA_FORMAT_REG, 0x01))
        {
            printk("writing data foramt reg failed\n\r");
            break;
        }

        bRetVal = true;
    } while (0);

    return bRetVal;
}

/**
 * @brief Read sensor data from accelerometer
 * @param psAcclData : buffer to store accelerometer data
 * @return true for success
*/
bool ReadFromAccelerometer(_sAcclData *psAcclData)
{
    bool bRetVal = false;
    struct device *psI2CDevice = NULL;
    uint8_t ucAcclbuffer[9] = {0};
    uint8_t ucbyte;

    psI2CDevice = GetI2CDevice();
     if (psI2CDevice && psAcclData)
    {
        
       if (0 == i2c_burst_read(psI2CDevice, ACCLMTR_DEV_ADDR, ACCLMTR_DATAX0_REG, ucAcclbuffer, 6))
        {
            printk("i2c read success\n\r");
            psAcclData->unAccX = ucAcclbuffer[0] | ucAcclbuffer[1] << 8;
            psAcclData->unAccY = ucAcclbuffer[2] | ucAcclbuffer[3] << 8;
            psAcclData->unAccZ = ucAcclbuffer[4] | ucAcclbuffer[5] << 8;
            bRetVal = true;
        }
        else
        {
            printk("read failed\n\r");
        }
    }

    return bRetVal;
}
