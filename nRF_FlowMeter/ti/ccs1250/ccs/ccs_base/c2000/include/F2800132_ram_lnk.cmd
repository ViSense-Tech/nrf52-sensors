/*
//###########################################################################
//
// FILE:	F2800132_ram_lnk.cmd
//
// TITLE:	Linker Command File For F2800132 Device
//
//###########################################################################
*/

MEMORY
{
   BEGIN            : origin = 0x00000000, length = 0x00000002
   BOOT_RSVD        : origin = 0x00000002, length = 0x00000126

   RAMM0            : origin = 0x00000128, length = 0x000002D8
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
   FLASH_BANK0_SEC_24      : origin = 0x086000, length = 0x0380  /* on-chip Flash */
   FLASH_BANK0_SEC_25      : origin = 0x086400, length = 0x0380  /* on-chip Flash */
   FLASH_BANK0_SEC_26      : origin = 0x086800, length = 0x0380  /* on-chip Flash */
   FLASH_BANK0_SEC_27      : origin = 0x086C00, length = 0x0380  /* on-chip Flash */
   FLASH_BANK0_SEC_28      : origin = 0x087000, length = 0x0380  /* on-chip Flash */
   FLASH_BANK0_SEC_29      : origin = 0x087400, length = 0x0380  /* on-chip Flash */
   FLASH_BANK0_SEC_30      : origin = 0x087800, length = 0x0380  /* on-chip Flash */
   FLASH_BANK0_SEC_31      : origin = 0x087C00, length = 0x0380  /* on-chip Flash */
   FLASH_BANK0_SEC_32      : origin = 0x088080, length = 0x0380  /* on-chip Flash */
   FLASH_BANK0_SEC_33      : origin = 0x088480, length = 0x0380  /* on-chip Flash */
   FLASH_BANK0_SEC_34      : origin = 0x088880, length = 0x0380  /* on-chip Flash */
   FLASH_BANK0_SEC_35      : origin = 0x088C80, length = 0x0380  /* on-chip Flash */
   FLASH_BANK0_SEC_36      : origin = 0x089080, length = 0x0380  /* on-chip Flash */
   FLASH_BANK0_SEC_37      : origin = 0x089480, length = 0x0380  /* on-chip Flash */
   FLASH_BANK0_SEC_38      : origin = 0x089880, length = 0x0380  /* on-chip Flash */
   FLASH_BANK0_SEC_39      : origin = 0x089C80, length = 0x0380  /* on-chip Flash */
   FLASH_BANK0_SEC_40_47   : origin = 0x08A000, length = 0x2000  /* on-chip Flash */
   FLASH_BANK0_SEC_48_55   : origin = 0x08C000, length = 0x2000  /* on-chip Flash */
   FLASH_BANK0_SEC_56_63   : origin = 0x08E000, length = 0x1FF0  /* on-chip Flash */
 
 // FLASH_BANK0_SEC_63_RSVD : origin = 0x08FFF0, length = 0x0010  /* Reserve and do not use for code as per the errata advisory "Memory: Prefetching Beyond Valid Memory" */
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