/*****************************************************INCLUDES*****************************************/
#include <zephyr/drivers/flash.h>
#include <zephyr/storage/flash_map.h>
#include <zephyr/fs/nvs.h>
#include <string.h>
#include <zephyr/sys/reboot.h>
//#include "BleService.h" 
/******************************************************MACROS*****************************************/

#define NVS_PARTITION		storage_partition
#define NVS_PARTITION_DEVICE	FIXED_PARTITION_DEVICE(NVS_PARTITION)
#define NVS_PARTITION_OFFSET	FIXED_PARTITION_OFFSET(NVS_PARTITION)
/* SPI flash region*/
#define SPI_FLASH_REGION_OFFSET 0x24000//0x10000
/* SPI flash sector size*/
#define SPI_FLASH_SECTOR_SIZE        4096

/* file system for storing Config data */
#define CONFIG_DATA_FS 1
/* File system for storing JSON payload */
#define DATA_FS 0
/* Specify number of hours of historical data is required to be stored on external flash. */
#define HOURS_OF_STORAGE 1
/*Number of entries in one min to the flash*/
#define NUMBER_OF_ENTRIES_IN_MINUTE 43
/*write alignment of flash*/
#define WRITE_ALIGNMENT 128
/*Number of minute in hour*/
#define MINUTE_IN_HOUR 60
/* Number of entries to the flash*/
#define NUMBER_OF_ENTRIES  (NUMBER_OF_ENTRIES_IN_MINUTE * MINUTE_IN_HOUR * HOURS_OF_STORAGE)   // calculate accordingly
/*NUmber of sector used for storing JSON*/
#define SECTOR_COUNT ((NUMBER_OF_ENTRIES * WRITE_ALIGNMENT) / 4096)

#define STRING_ID 0

/**
 * @note : Below MACRO is used to enable MX66 flash support but if it is enabled will get a build error
 *         which has tobe fixed by configuring dts file in boards directory. You can do that by commenting out
 *         mx25 flash node in definition qspi node in dts file manually.
*/
//#define MX66FLASH_ENABLED //Uncomment this line to enable MX66 functionality

/*********************************************************TYPEDEFS*****************************************/
typedef struct __attribute__((packed)) __sConfigData
{
    long long lastUpdatedTime;
    uint32_t flashIdx;
    uint32_t sleepTime;
    uint32_t pressureZero;
    uint32_t pressureMax;
    uint16_t pressureMin;
    uint8_t flag;
}_sConfigData;

/**********************************************************FUNCTION DECLARATIONS*******************************/
 int nvs_logger(char* cjson, int data_count);
int nvs_initialisation( struct nvs_fs *fs, uint8_t selector);
int writeJsonToFlash(struct nvs_fs *fs, uint16_t data_count,uint16_t count_max, char *buf, uint8_t len);
int readJsonToFlash(struct nvs_fs *fs, uint16_t data_count,uint16_t count_max, char *buf, uint8_t len);
int deleteFlash(struct nvs_fs *fs, uint16_t data_count,uint16_t count_max);
int freeSpaceCalc(struct nvs_fs *fs, uint16_t data_count,uint16_t count_max);

// external flash support functions
bool writeJsonToExternalFlash(char *pcBuffer, uint32_t flashIdx, int unLength);
bool EraseExternalFlash(uint16_t);
bool readJsonFromExternalFlash(char *pcBuffer, uint32_t flashIdx, int unLength);
