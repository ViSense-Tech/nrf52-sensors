/*
//###########################################################################
//
// FILE:	F2800153_ram_lnk.cmd
//
// TITLE:	Linker Command File For F2800153 Device
//
//###########################################################################
*/

MEMORY
{
   BEGIN            : origin = 0x00000000, length = 0x00000002
   BOOT_RSVD        : origin = 0x00000002, length = 0x0000024E

   RAMM0            : origin = 0x00000250, length = 0x000001B0
   RAMM1            : origin = 0x00000400, length = 0x000003F8
   // RAMM1_RSVD       : origin = 0x000007F8, length = 0x00000008 /* Reserve and do not use for code as per the errata advisory "Memory: Prefetching Beyond Valid Memory" */

   RAMLS0           : origin = 0x00008000, length = 0x00002000
   RAMLS1           : origin = 0x0000A000, length = 0x00001FF8
   // RAMLS1_RSVD      : origin = 0x0000BFF8, length = 0x00000008

   RESET            : origin = 0x003FFFC0, length = 0x00000002

    /* Flash sectors */
   /* BANK 0 */
   /* Flash sectors */
   FLASH_BANK0_SEC_0_7     : origin = 0x080002, length = 0x1FFE  /* on-chip Flash */
   FLASH_BANK0_SEC_8_15    : origin = 0x082000, length = 0x2000  /* on-chip Flash */
   FLASH_BANK0_SEC_16_23   : origin = 0x084000, length = 0x2000  /* on-chip Flash */
   FLASH_BANK0_SEC_24      : origin = 0x086000, length = 0x0400  /* on-chip Flash */
   FLASH_BANK0_SEC_25      : origin = 0x086400, length = 0x0400  /* on-chip Flash */
   FLASH_BANK0_SEC_26      : origin = 0x086800, length = 0x0400  /* on-chip Flash */
   FLASH_BANK0_SEC_27      : origin = 0x086C00, length = 0x0400  /* on-chip Flash */
   FLASH_BANK0_SEC_28      : origin = 0x087000, length = 0x0400  /* on-chip Flash */
   FLASH_BANK0_SEC_29      : origin = 0x087400, length = 0x0400  /* on-chip Flash */
   FLASH_BANK0_SEC_30      : origin = 0x087800, length = 0x0400  /* on-chip Flash */
   FLASH_BANK0_SEC_31      : origin = 0x087C00, length = 0x0400  /* on-chip Flash */
   FLASH_BANK0_SEC_32      : origin = 0x088000, length = 0x03F0  /* on-chip Flash */
 
 // FLASH_BANK0_SEC_32_RSVD : origin = 0x0883F0, length = 0x0010  /* Reserve and do not use for code as per the errata advisory "Memory: Prefetching Beyond Valid Memory" */
}


SECTIONS
{
   codestart        : > BEGIN
   .TI.ramfunc      : > RAMM0
   .text            : >> RAMLS0 | RAMLS1
   .cinit           : > RAMM0
   .switch          : > RAMM0
   .reset           : > RESET,                  TYPE = DSECT /* not used, */

   .stack           : > RAMM1

#if defined(__TI_EABI__)
   .bss             : > RAMLS0 | RAMLS1
   .bss:output      : > RAMLS0 | RAMLS1
   .init_array      : > RAMM0
   .const           : > RAMLS0 | RAMLS1
   .data            : > RAMLS0 | RAMLS1
   .sysmem          : > RAMLS0 | RAMLS1
  .bss:cio          : > RAMLS0 | RAMLS1
#else
   .pinit           : > RAMM0
   .ebss            : > RAMLS0 | RAMLS1
   .econst          : > RAMLS0 | RAMLS1
   .esysmem         : > RAMLS0 | RAMLS1
   .cio             : > RAMLS0 | RAMLS1
#endif

    /*  Allocate IQ math areas: */
   IQmath           : > RAMLS0 | RAMLS1
   IQmathTables     : > RAMLS0 | RAMLS1
}
/*
//###########################################################################
// End of file.
//###########################################################################
*/	