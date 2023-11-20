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
/* AWR2944 C66xx DEVICE LINKER COMMAND FILE  */
/* This is the stack that is used by code running within main()
 * In case of NORTOS,
 * - This means all the code outside of ISR uses this stack
 * In case of FreeRTOS
 * - This means all the code until vTaskStartScheduler() is called in main()
 *   uses this stack.
 * - After vTaskStartScheduler() each task created in FreeRTOS has its own stack
 */
--stack_size=16384
/* This is the heap size for malloc() API in NORTOS and FreeRTOS
 * This is also the heap used by pvPortMalloc in FreeRTOS
 */
--heap_size=32768
--retain=_vectors

SECTIONS
{
    /* hard addresses forces vecs to be allocated there */
    .text:vectors: {. = align(1024); } > 0x00800000
    .text:      {} > DSS_L2
    .const:     {} > DSS_L2
    .cinit:     {} > DSS_L2
    .data:      {} > DSS_L2
    .stack:     {} > DSS_L2
    .switch:    {} > DSS_L2
    .cio:       {} > DSS_L2
    .sysmem:    {} > DSS_L2
    .fardata:   {} > DSS_L2
    .far:       {} > DSS_L2

    /* These should be grouped together to avoid STATIC_BASE relative relocation linker error */
    GROUP {
        .rodata:    {}
        .bss:       {}
        .neardata:  {}
    } > DSS_L2

    /* Sections needed for C++ projects */
    GROUP {
        .c6xabi.exidx:  {} palign(8)   /* Needed for C++ exception handling */
        .init_array:    {} palign(8)   /* Contains function pointers called before main */
        .fini_array:    {} palign(8)   /* Contains function pointers called after main */
    } > DSS_L2

    /* any data buffer needed to be put in L3 can be assigned this section name */
    .bss.dss_l3 {} > DSS_L3

    /* General purpose user shared memory, used in some examples */
    .bss.user_shared_mem (NOLOAD) : {} > USER_SHM_MEM
    /* this is used when Debug log's to shared memory are enabled, else this is not used */
    .bss.log_shared_mem  (NOLOAD) : {} > LOG_SHM_MEM
    /* this is used only when IPC RPMessage is enabled, else this is not used */
    .bss.ipc_vring_mem   (NOLOAD) : {} > RTOS_NORTOS_IPC_SHM_MEM
}

MEMORY
{
    DSS_L2:   ORIGIN = 0x800000, LENGTH = 0x60000
    DSS_L3:   ORIGIN = 0x88000000, LENGTH = 0x00240000

    /* shared memories that are used by RTOS/NORTOS cores */
    /* On C66,
     * - make sure these are which mapped as non-cache in MAR bits
     */
    USER_SHM_MEM            : ORIGIN = 0xC02E8000, LENGTH = 0x00004000
    LOG_SHM_MEM             : ORIGIN = 0xC02EC000, LENGTH = 0x00004000
    /* MSS mailbox memory is used as shared memory, we dont use bottom 32*6 bytes, since its used as SW queue by ipc_notify */
    RTOS_NORTOS_IPC_SHM_MEM : ORIGIN = 0xC5000000, LENGTH = 0x1F40
}
