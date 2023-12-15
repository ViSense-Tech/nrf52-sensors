/*************************************************************INCLUDES*****************************************/
#include "nvs_flash.h"


/**************************************************************GLOBAL VARIABLES*********************************/
const struct device *flash_dev = DEVICE_DT_GET(DT_ALIAS(spi_flash0));
uint32_t uFlashIdx = 0;  // initialise data counter

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
		fs->offset = NVS_PARTITION_OFFSET + 8192;
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
		fs->offset = NVS_PARTITION_OFFSET + 8192;
		rc = flash_get_page_info_by_offs(fs->flash_device, fs->offset, &info);
		if (rc) 
		{
			printk("Unable to get page info\n");
			return 0;
		}
		fs->sector_size = info.size;
		fs->sector_count = 2U;
	}

	rc = nvs_mount(fs);
	if (rc) {
		printk("Flash Init failed%d\n",rc);
		return 0;
	}
	// return fs;

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
/**
 * @brief  Write data to external flash
 * @param pcBuffer : data to send
 * @param unLength : Length of data
 * @return True for success
*/
bool writeJsonToExternalFlash(char *pcBuffer, uint32_t flashIdx, int unLength) // &flashIdx
{
	bool bRetval = false;
	int rc = 0;
	flashIdx = (flashIdx * WRITE_ALIGNMENT);


	do
	{
		if (!device_is_ready(flash_dev)) 
		{
			printk("%s: device not ready.\n", flash_dev->name);
			break;
		}
		rc = flash_write(flash_dev, SPI_FLASH_REGION_OFFSET + flashIdx, pcBuffer, unLength);
		if (rc != 0)
		{
			printf("Flash write failed! %d\n", rc);
			break;
		}
		printk("offset:%d\n",flashIdx);
		
		k_sleep(K_MSEC(10));
		bRetval = true;


		
	} while (0);

	return bRetval;

}
/**
 * @brief  Read data from external flash
 * @param pcBuffer : data buffer to store
 * @param unLength : Length of data
 * @return True for success
*/
bool readJsonFromExternalFlash(char *pcBuffer, uint32_t flashIdx, int unLength)
{
	bool bRetval = false;
	int rc = 0;

	flashIdx = flashIdx * WRITE_ALIGNMENT;
	

	do
	{
		rc = flash_read(flash_dev,SPI_FLASH_REGION_OFFSET + flashIdx, pcBuffer, WRITE_ALIGNMENT);
		if (rc != 0)
		{
			printf("Flash read failed! %d\n", rc);
			break;
		}
		printk("offset:%d\n",flashIdx);
		bRetval = true;
		
	}while(0);

	return bRetval;

}
/**
 * @brief  Erase external flash
 * @param None
 * @return True for success
*/
bool EraseExternalFlash(uint16_t uSectorIdx)
{
	bool bRetval = false;
	int rc = 0;

	do
	{
		rc = flash_erase(flash_dev, SPI_FLASH_REGION_OFFSET,
				SPI_FLASH_SECTOR_SIZE * uSectorIdx);
		if (rc != 0) 
		{
			printf("Flash erase failed! %d\n", rc);
			break;
		} else 
		{
			printf("Flash erase succeeded!\n");
		}
		bRetval = true;
	} while (0);

	return bRetval;
}

uint32_t *GetFlashCounter()
{
	return &uFlashIdx;
}



