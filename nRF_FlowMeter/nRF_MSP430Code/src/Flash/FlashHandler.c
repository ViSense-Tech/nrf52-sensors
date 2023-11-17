/**
 * @file    : RtcHandler.h 
 * @brief   : File containing functions for handling RTC 
 * @author  : Rajeev
 * @date    : 01-11-2023
 * @note 
*/
/***************************************INCLUDES*********************************/
#include "FlashHandler.h"

/***************************************FUNCTION DECLARATION********************/
int nvs_initialisation( struct nvs_fs *fs, uint8_t selector)
{
    int rc = 0;
	uint32_t counter = 0U, counter_his;
	struct flash_pages_info info;

	fs->flash_device = NVS_PARTITION_DEVICE;
	if (!device_is_ready(fs->flash_device)) {
		printk("Flash device %s is not ready\n", fs->flash_device->name);
		return 0;
	}

	if (selector == DATA_FS) // data
	{
		fs->offset = NVS_PARTITION_OFFSET + 12288;
		rc = flash_get_page_info_by_offs(fs->flash_device, fs->offset, &info);
		if (rc) 
		{
			printk("Unable to get page info\n");
			return 0;
		}
		fs->sector_size = info.size;
		fs->sector_count = 4U;
	}
	
	if (selector == CONFIG_DATA_FS) // config data
	{
		fs->offset = NVS_PARTITION_OFFSET;
		rc = flash_get_page_info_by_offs(fs->flash_device, fs->offset, &info);
		if (rc) 
		{
			printk("Unable to get page info\n");
			return 0;
		}
		fs->sector_size = info.size;
		fs->sector_count = 3U;
	}

	rc = nvs_mount(fs);
	if (rc) {
		printk("Flash Init failed%d\n",rc);
		return 0;
	}
}  


int writeJsonToFlash(struct nvs_fs *fs, uint16_t data_count,uint16_t count_max, char *data, uint8_t len)
{
	char writebuf[180]; 
	strcpy(writebuf, data);

	int rc= nvs_write(fs, (STRING_ID + data_count), writebuf, len);
	printk("Size of written buf:%d\n",rc);
	if(rc!=len)
	{
		printk("write_failed:%d\n",rc);
	}
}


int readJsonToFlash(struct nvs_fs *fs, uint16_t data_count,uint16_t count_max, char *buf, uint8_t len)
{
	int rc;

	rc= nvs_read(fs, (STRING_ID + data_count), buf, len);
	k_msleep(10);
	printk("Read Count:%d\n",rc);
	if(rc!=len)
	{
		printk("read_failed:%d\n",rc);
	}
	return rc;
		
}


int deleteFlash(struct nvs_fs *fs, uint16_t data_count,uint16_t count_max)
{
	nvs_clear(fs);
	nvs_initialisation(fs, DATA_FS); //deleting data
	printk("Deleted all..");

}


int freeSpaceCalc(struct nvs_fs *fs, uint16_t data_count,uint16_t count_max)
{
	int free_space = nvs_calc_free_space(fs);
	printk("\n free space %d ", free_space);
	return free_space;
}