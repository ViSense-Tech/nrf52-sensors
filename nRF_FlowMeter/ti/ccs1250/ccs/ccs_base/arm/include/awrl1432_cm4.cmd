/*
 * Copyright (c) 2021, Texas Instruments Incorporated
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

-heap 2048
--retain="*(.intvecs)"
--entry_point=_sysResetEntry_
--retain="__TI_zero_init"
--retain="__TI_decompress_rle24"
--retain="__TI_decompress_none"

MEMORY
{
    P_VEC       : ORIGIN = 0x00000000  LENGTH = 0x00400  /* PROGRAM MEMORY TCMA   */
    SRAM_CODE   : ORIGIN = 0x00000400  LENGTH = 0x7FC00
}

 SECTIONS
 {
     .intvecs : {*(.intvecs)                     } >P_VEC   /* INTERRUPT VECTORS      */
     .code    : {*(.text)                        } >SRAM_CODE   ALIGN(8)
     .cinit   : {                                } >SRAM_CODE   ALIGN(8)
     .pinit   : {                                } >SRAM_CODE   ALIGN(8)

     .ramvecs :
     {          _ramVecTableStart_  = . ;
                _ramVecTableEnd_    = . ;

     } > P_VEC
     .data      : {                                   } >SRAM_CODE
     .bss       : {                                   } >SRAM_CODE
     .stack     : { . += 0x400; _process_sp_   = .;   } >SRAM_CODE
     .mainStack : { . += 0x400; _main_sp_      = .;   } >SRAM_CODE
 }

