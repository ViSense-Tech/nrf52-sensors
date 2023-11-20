/*----------------------------------------------------------------------------*/
/* sys_link.cmd                                                               */
/*                                                                            */
/* (c) Texas Instruments 2009, All rights reserved.                           */
/*                                                                            */

/* USER CODE BEGIN (0) */
/* USER CODE END */


/*----------------------------------------------------------------------------*/
/* Linker Settings                                                            */

-l rtsv7M3_T_be_eabi.lib

--retain="*(.intvecs)"
--retain="*(.vim_table)"


/* USER CODE BEGIN (1) */
/* USER CODE END */

/*----------------------------------------------------------------------------*/
/* Memory Map                                                                 */

MEMORY
{
    VECTORS (X)  : origin=0x00000000 length=0x00000040
    VIM_TABLE (X): origin=0x00000040 length=0x000000C0
    STACKS  (RW) : origin=0x08000000 length=0x00000800
    FLASH0  (RX) : origin=0x00000100 length=0x0007FEFF
    FLASH1  (RX) : origin=0x00080000 length=0x0001FFFF
    RAM     (RW) : origin=0x08000800 length=0x0000F7FF

/* USER CODE BEGIN (2) */
/* USER CODE END */
}

/* USER CODE BEGIN (3) */
/* USER CODE END */


/*----------------------------------------------------------------------------*/
/* Section Configuration                                                      */

SECTIONS
{
    .intvecs : {} > VECTORS
    .vim_table : {} > VIM_TABLE
    .text    : {} > FLASH0 | FLASH1
    .const   : {} > FLASH0 | FLASH1
    .cinit   : {} > FLASH0 | FLASH1
    .pinit   : {} > FLASH0 | FLASH1
    .bss     : {} > RAM 
    .data    : {} > RAM 


   .stack   :                            /* SOFTWARE SYSTEM STACK                 */
   {                                                   /* initial stack pointer values          */
    . += 0x00000400;  _Stack_Table_Pointer  = .;
    . += 0x00000400;  _Stack_Handler_Pointer  = .;
   } > STACKS


/* USER CODE BEGIN (4) */
/* USER CODE END */
}

/* USER CODE BEGIN (5) */
/* USER CODE END */


/*----------------------------------------------------------------------------*/
/* Misc                                                                       */

/* USER CODE BEGIN (6) */
/* USER CODE END */


/*----------------------------------------------------------------------------*/

