/**
 * @file    : RtcHandler.h 
 * @brief   : File containing functions for handling RTC 
 * @author  : Rajeev
 * @date    : 01-11-2023
 * @note 
*/

#ifndef _NVS_FLASH_H
#define _NVS_FLASH_H

/***************************************INCLUDES*********************************/
#include <zephyr/drivers/flash.h>
#include <zephyr/storage/flash_map.h>
#include <zephyr/fs/nvs.h>
#include <string.h>
#include <zephyr/sys/reboot.h>

/***************************************MACROS**********************************/
#define NVS_PARTITION		storage_partition
#define NVS_PARTITION_DEVICE	FIXED_PARTITION_DEVICE(NVS_PARTITION)
#define NVS_PARTITION_OFFSET	FIXED_PARTITION_OFFSET(NVS_PARTITION)
/* file system for storing Config data */
#define CONFIG_DATA_FS 1
/* File system for storing JSON payload */
#define DATA_FS 0
/* Number of entries to the flash*/
#define NUMBER_OF_ENTRIES 5

#define STRING_ID 0

/***************************************TYPEDEFS**********************************/
typedef struct __attribute__((packed)) __sConfigData
{
    long long lastUpdatedTime;
     uint32_t flashIdx;
    uint32_t sleepTime;
    uint8_t flag;
}_sConfigData;

/***************************************FUNCTION DECLARATION**********************/
int nvs_logger(char* cjson, int data_count);
int nvs_initialisation( struct nvs_fs *fs, uint8_t selector);
int writeJsonToFlash(struct nvs_fs *fs, uint16_t data_count,uint16_t count_max, char *buf, uint8_t len);
int readJsonToFlash(struct nvs_fs *fs, uint16_t data_count,uint16_t count_max, char *buf, uint8_t len);
int deleteFlash(struct nvs_fs *fs, uint16_t data_count,uint16_t count_max);
int freeSpaceCalc(struct nvs_fs *fs, uint16_t data_count,uint16_t count_max);

#endif

