/*----------------------------------------------------------------------------*/
/* TMS570LS202x6SFlashLnk.cmd                                                 */
/*                                                                            */
/* (c) Texas Instruments 2009, All rights reserved.                           */
/*                                                                            */

/* USER CODE BEGIN (0) */
/* USER CODE END */


/*----------------------------------------------------------------------------*/
/* Linker Settings                                                            */
--retain="*(.intvecs)"

/*----------------------------------------------------------------------------*/
/* Memory Map                                                                 */
MEMORY{
    VECTORS (X)  : origin=0x00000000 length=0x00000020
    FLASH0  (RX) : origin=0x00000020 length=0x0007FFE0
    FLASH1  (RX) : origin=0x00080000 length=0x00080000
    FLASH2  (RX) : origin=0x00100000 length=0x00080000
    FLASH3  (RX) : origin=0x00180000 length=0x00080000
    STACKS  (RW) : origin=0x08000000 length=0x00001300
    RAM     (RW) : origin=0x08001300 length=0x00026D00
}

/*----------------------------------------------------------------------------*/
/* Section Configuration                                                      */
SECTIONS{
    .intvecs : {} > VECTORS
    .text    : {} > FLASH0 | FLASH1 | FLASH2 | FLASH3
    .const   : {} > FLASH0 | FLASH1 | FLASH2 | FLASH3
    .cinit   : {} > FLASH0 | FLASH1 | FLASH2 | FLASH3
    .pinit   : {} > FLASH0 | FLASH1 | FLASH2 | FLASH3
    .bss     : {} > RAM
    .data    : {} > RAM
}
/*----------------------------------------------------------------------------*/

