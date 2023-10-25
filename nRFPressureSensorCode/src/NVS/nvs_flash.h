#include <zephyr/drivers/flash.h>
#include <zephyr/storage/flash_map.h>
#include <zephyr/fs/nvs.h>
#include <string.h>
//#include "BleService.h" 

#define NVS_PARTITION		storage_partition
#define NVS_PARTITION_DEVICE	FIXED_PARTITION_DEVICE(NVS_PARTITION)
#define NVS_PARTITION_OFFSET	FIXED_PARTITION_OFFSET(NVS_PARTITION)

/* 1000 msec = 1 sec */
#define SLEEP_TIME      100
/* maximum reboot counts, make high enough to trigger sector change (buffer */
/* rotation). */


#define STRING_ID 1
// static struct nvs_fs fs;


 int nvs_logger(char* cjson, int data_count);
int nvs_initialisation( struct nvs_fs *fs);
int writeJsonToFlash(struct nvs_fs *fs, uint16_t data_count,uint16_t count_max, char *buf, uint8_t len);
int readJsonToFlash(struct nvs_fs *fs, uint16_t data_count,uint16_t count_max, char *buf, uint8_t len);
int deleteFlash(struct nvs_fs *fs, uint16_t data_count,uint16_t count_max);
int freeSpaceCalc(struct nvs_fs *fs, uint16_t data_count,uint16_t count_max);