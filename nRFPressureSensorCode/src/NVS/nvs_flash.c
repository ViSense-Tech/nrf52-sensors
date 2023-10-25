
#include "nvs_flash.h"





int nvs_initialisation( struct nvs_fs *fs)
{
    int rc = 0;

	
	uint32_t counter = 0U, counter_his;
	struct flash_pages_info info;

	/* 
	 *	sector_size equal to the pagesize,
	 *	3 sectors
	 *	starting at NVS_PARTITION_OFFSET
	 */
	fs->flash_device = NVS_PARTITION_DEVICE;
	if (!device_is_ready(fs->flash_device)) {
		printk("Flash device %s is not ready\n", fs->flash_device->name);
		return 0;
	}
	fs->offset = NVS_PARTITION_OFFSET;
	rc = flash_get_page_info_by_offs(fs->flash_device, fs->offset, &info);
	if (rc) {
		printk("Unable to get page info\n");
		return 0;
	}
	fs->sector_size = info.size;
	fs->sector_count = 3U;

	rc = nvs_mount(fs);
	if (rc) {
		printk("Flash Init failed%d\n",rc);
		return 0;
	}
	// return fs;

}  
int writeJsonToFlash(struct nvs_fs *fs, uint16_t data_count,uint16_t count_max, char *data, uint8_t len)
{
	char writebuf[100]; 
	strcpy(writebuf, data);
	int rc= nvs_write(fs, (STRING_ID + data_count), writebuf, len);
	if(rc!=88)
	{
	printk("write_failed:%d\n",rc);
	}
}

int readJsonToFlash(struct nvs_fs *fs, uint16_t data_count,uint16_t count_max, char *buf, uint8_t len)

{
	int rc;
	rc= nvs_read(fs, (STRING_ID + data_count), buf, len);
	printk("read_errorcode:%d\n",rc);
	return rc;
		
}

int deleteFlash(struct nvs_fs *fs, uint16_t data_count,uint16_t count_max)
{
	 for(int i=0;i<count_max; i++)                        // read print and delete 10 values
        {
		  nvs_delete(fs, STRING_ID+i); 
		  printk("Deleting[%d]",i);
		}
	 printk("Deleted all..");

}

int freeSpaceCalc(struct nvs_fs *fs, uint16_t data_count,uint16_t count_max)
{
	int free_space = nvs_calc_free_space(fs);
	printk("\n free space %d ", free_space);
	return free_space;
}

// int nvs_logger(char *cJson, int data_count)
// {

//     char buf[150];
// 	char readbuf[150];
// 	char readbuf2;
//     strcpy(buf, cJson);
//     int rc = 0;

//     int i = 0;
    
//     rc= nvs_write(&fs, (STRING_ID + data_count), &buf, sizeof(buf));   // write to flash
//     rc= nvs_read(&fs, (STRING_ID+data_count), &readbuf, sizeof(readbuf));   // read from flash
            
//     printk("Id: %d, Data: %s\n",STRING_ID + data_count, readbuf);

// 	if(GetCharaStatus()== true)// Mobile device chara read status
// 	{
//     	 printk("Deleting \n");	
// 		 for(int i=0;i<10; i++)                        // read print and delete 10 values
//         {
// 		  nvs_delete(&fs, STRING_ID+i); 
// 		}
// 	}

//     if (data_count == 9)
//     {
//         for(int i=0;i<10; i++)                        // read print and delete 10 values
//         {
//             rc= nvs_read(&fs, (STRING_ID + i), &readbuf, sizeof(readbuf));
            
//             printk("Id: %d, Data: %s\n",STRING_ID+i, readbuf);	 
//             nvs_delete(&fs, STRING_ID+i); 	                                  //delete
//         }
//     }
    


    

// // for(int i=0;i<=10; i++)                        // read print and delete 11 values
// // {
// //   rc= nvs_read(&fs, (STRING_ID+i), &readbuf, sizeof(readbuf));
  
// //   printk("Id: %d, Data: %s\n",STRING_ID+i, readbuf);	 
// //   nvs_delete(&fs, STRING_ID+i);	                                  //delete}
// // }


// //strcpy(buf,"{ADCValue:44, PrevPressure: 0psi}" );


// // for(int i=0;i<=10; i++)
// // {
// //   rc= nvs_write(&fs, (STRING_ID+i), &buf, sizeof(buf));


// // }

// // for(int i=0;i<=10; i++)
// // {
// //   rc= nvs_read(&fs, (STRING_ID+i), &readbuf, sizeof(readbuf));
  
// //   printk("Id: %d, Data: %s\n",STRING_ID+i, readbuf);
	 
  
  
// //   nvs_delete(&fs, STRING_ID+i);	
// // }

// }