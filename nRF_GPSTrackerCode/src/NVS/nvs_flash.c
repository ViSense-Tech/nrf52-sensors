/*************************************************************INCLUDES*****************************************/
#include "nvs_flash.h"
#include <stdio.h>

/**************************************************************GLOBAL VARIABLES*********************************/
static _sConfigData sConfigData = {0};
#ifdef MX66FLASH_ENABLED
static const struct device *const flash_dev = DEVICE_DT_GET(DT_NODELABEL(mx66l1g));
#else
static const struct device *const flash_dev = DEVICE_DT_GET(DT_ALIAS(spi_flash0));
#endif

/**
 * @brief  Initialise flash
 * @param  fs 	    : File pointer 
 * @param  selector : decides if config or data partition is selected
 * @return return code for flash initialisation
*/
int FlashInit( struct nvs_fs *fs, uint8_t selector)
{
    int rc = 0;
	//uint32_t counter = 0U;
	struct flash_pages_info info;
	fs->flash_device = NVS_PARTITION_DEVICE;

	do
	{
		if (!device_is_ready(fs->flash_device)) 
		{
			printk("Flash device %s is not ready\n", fs->flash_device->name);
			break;
		}

		if (selector == DATA_FS) // data
		{
			fs->offset = NVS_PARTITION_OFFSET + 16384;
			rc = flash_get_page_info_by_offs(fs->flash_device, fs->offset, &info);
			if (rc) 
			{
				printk("Unable to get page info\n");
				break;
			}
			fs->sector_size = info.size;
			fs->sector_count = 2U;
		}
		
		if (selector == CONFIG_DATA_FS) // config data
		{
			fs->offset = NVS_PARTITION_OFFSET;
			rc = flash_get_page_info_by_offs(fs->flash_device, fs->offset, &info);
			if (rc) 
			{
				printk("Unable to get page info\n");
				break;
			}
			fs->sector_size = info.size;
			fs->sector_count = 4U;
		}

		rc = nvs_mount(fs);
		if (rc) 
		{
			printk("Flash Init failed%d\n",rc);
			break;
		}

	} while (0);
	
	return rc;
}  

/**
 * @brief Read Data from flash
 * @param fs         : File pointer
 * @param data_count : number of json entry
 * @param buf		 : buffer to store read data
 * @param len 		 : length of data
 * @return number of bytes read on success
 * 
*/
int ReadJsonFromFlash(struct nvs_fs *fs, uint16_t data_count, char *buf, uint8_t len)
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

/**
 * @brief Delete data from flash
 * @param fs       : File pointer
 * @param selector : decides if config or data partition is selected
 * @return None
*/
void deleteFlash(struct nvs_fs *fs, uint8_t selector)
{
	nvs_clear(fs);
	nvs_initialisation(fs, selector); //deleting data
	printk("Deleted all..");
}

/**
 * @brief Calculate available space in config or data partition
 * @param fs : File pointer
 * @return free space available in config or data partition
*/
int freeSpaceCalc(struct nvs_fs *fs)
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
		rc = flash_write(flash_dev, SPI_FLASH_REGION_OFFSET + flashIdx, pcBuffer, WRITE_ALIGNMENT);
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


_sConfigData *GetConfigData()
{
	return &sConfigData;
}

