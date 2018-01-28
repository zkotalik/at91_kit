/*************************************************************************
* The startup code must be linked at the start of ROM, which is NOT
* necessarily address zero.
*/

.include "at91rm9200.inc"
.include "at91rm9200_pmc.inc"
.include "at91rm9200_mc.inc"
.include "at91rm9200_pio.inc"

.extern __stack;
.extern __bss_start__
.extern __bss_end__
.extern __init_array_start
.extern __init_array_end
.extern main
.extern interruptHandler
;@.extern __iram_start__
;@.extern __data_start__
;@.extern __data_load__
;@.extern _edata
;@.extern __fastcode_start__
;@.extern __fastcode_load__
;@.extern __fastcode_end__

.equ    MAGIC, 0xDEADBEEF

	.section .text
	.globl _entry

_entry:

    ldr pc,reset_handler_ptr        ;@  Processor Reset handler
    ldr pc,undefined_handler_ptr    ;@  Undefined instruction handler
    ldr pc,swi_handler_ptr          ;@  Software interrupt
    ldr pc,prefetch_handler_ptr     ;@  Prefetch/abort handler.
    ldr pc,data_handler_ptr         ;@  Data abort handler/
    ldr pc,unused_handler_ptr       ;@
    ldr pc, [pc, #-0xF20]           ;@  IRQ handler
    ldr pc,fiq_handler_ptr          ;@  Fast interrupt handler.

    ;@ Set the branch addresses
reset_handler_ptr:      .word reset
undefined_handler_ptr:  .word hang
swi_handler_ptr:        .word vPortYieldProcessor
prefetch_handler_ptr:   .word hang
data_handler_ptr:       .word hang
unused_handler_ptr:     .word MAGIC
fiq_handler_ptr:        .word hang

reset:
    ;@ Disable interrupts
    msr     cpsr_c, #(SYS_MODE | I_BIT | F_BIT)
.ifndef NO_COPY
    ;@ Copy interrupt vector to its place
    ldr r0,=_entry
    ldr r1, =__iram_start__

    ;@  Here we copy the branching instructions
    ldmia r0!,{r2-r9}
    stmia r1!,{r2-r9}

    ;@  Here we copy the branching addresses
    ldmia r0!,{r2-r9}
    stmia r1!,{r2-r9}

    ;@ Remap if MC has not been remapped already
    ldr r0, =0x34
    ldr r1, [r0]
    ldr r2, =MAGIC
    subs r0, r1, r2
    ldrne r0, =MC_BASE
    ldrne r1, =MC_RCB
    strne r1, [r0, #MC_RCR]
.endif
    ;@ PMC setup 
    ldr     r0, =PMC_BASE

.ifndef NO_MO_SETUP
    ;@ Setup Main osc. 
    ldr     r1, =CKGR_MOR_EN_VAL
    str     r1, [r0, #CKGR_MOR_OFS]
1:
    ldr     r1, [r0, #PMC_SR_OFS]
    ands    r1, r1, #PMC_MOSCS
    beq     1b
.endif

.ifndef NO_PLLA_SETUP
    ;@ Setup PLLA - it will be functional only if value 
    ;@ is not the same so first there is a must to 
    ;@ test it
    ldr     r1, =CKGR_PLLAR_Val
    ldr     r2, [r0, #CKGR_PLLAR_OFS]
    cmp    r2, r1
    beq     pllb
    str     r1, [r0, #CKGR_PLLAR_OFS]
1:
    ldr     r1, [r0, #PMC_SR_OFS]
    ands    r1, r1, #PMC_LOCKA
    beq     1b
.endif

pllb:

.ifndef NO_PLLB_SETUP
    ;@ Setup PLLB - it will be functional only if value 
    ;@ is not the same so first there is a must to 
    ;@ test it
    ldr     r1, =CKGR_PLLBR_Val
    ldr     r2, [r0, #CKGR_PLLBR_OFS]
    cmp    r2, r1
    beq     mck
    str     r1, [r0, #CKGR_PLLBR_OFS]
1:
    ldr     r1, [r0, #PMC_SR_OFS]
    ands    r1, r1, #PMC_LOCKB
    beq     1b
.endif

mck:

.ifndef NO_MCK_SETUP
    ;@ Setup master clock and processor clock
    mov     r1, #5
    str     r1, [r0, #PMC_MCKR_OFS]
1:
    ldr     r1, [r0, #PMC_SR_OFS]
    ands    r1, r1, #PMC_MCKRDY
    beq     1b

    mov     r1, #1
    str     r1, [r0, #PMC_MCKR_OFS]
1:
    ldr     r1, [r0, #PMC_SR_OFS]
    ands    r1, r1, #PMC_MCKRDY
    beq     1b

    ldr     r1, =PMC_MCKR_Val
    str     r1, [r0, #PMC_MCKR_OFS]
1:
    ldr     r1, [r0, #PMC_SR_OFS]
    ands    r1, r1, #PMC_MCKRDY
    beq     1b
.endif

    ;@ Memories configuration
    ldr r0, =MC_BASE

.ifndef NO_SMC_SETUP
    ldr r1, =SMC_CSR0_VAL
    str r1, [r0, #(EBI_OFS + SMC_OFS + SMC_CSR0)]
    str r1, [r0, #(EBI_OFS + SMC_OFS + SMC_CSR2)]
.endif
    
    ;@ LCD access setup
    ldr r1, =SMC_CSR3_VAL
    str r1, [r0, #(EBI_OFS + SMC_OFS + SMC_CSR3)]

.ifndef NO_SDRAM_SETUP
    mov r1, #0xFF00
    add r1, #0xFF
    ror r1, #16
    ldr r2, =PIOC_BASE
    str r1, [r2, #PIO_PDR]      ;@ Set high 16 address bits as peripherial
    ldr r1, =EBI_CSA_CS1A
    str r1, [r0, #(EBI_OFS + EBI_CSA)]   ;@ Enable CS1 for SDRAM
    mov r1, #0
    str r1, [r0, #(EBI_OFS + EBI_CFGR)]
    ldr r1, =SDRAM_CR_VAL
    str r1, [r0, #(EBI_OFS + SDRAMC_OFS + SDRAM_CR)]
    ldr r1, =SDRAM_MR_MODE_PRECHARGE
    str r1, [r0, #(EBI_OFS + SDRAMC_OFS + SDRAM_MR)]
    mov r3, #0
    ldr r2, =SDRAMC_ADDRESS
    str r3, [r2]                ;@ Access to SDRAM after precharge
    ldr r1, =SDRAM_MR_MODE_REFRESH
    str r1, [r0, #(EBI_OFS + SDRAMC_OFS + SDRAM_MR)]
.rept 8
    str r3, [r2]
.endr
    ldr r1, =SDRAM_MR_MODE_LOAD
    str r1, [r0, #(EBI_OFS + SDRAMC_OFS + SDRAM_MR)]
    str r3, [r2, #80]
    mov r1, #0x2E
    lsl r1, #4
    str r1, [r0, #(EBI_OFS + SDRAMC_OFS + SDRAM_TR)]
    ldr r1, =SDRAM_MR_MODE_NORMAL
    str r1, [r0, #(EBI_OFS + SDRAMC_OFS + SDRAM_MR)]
    str r3, [r2]
.endif

    /* Relocate .fastcode section (copy from RAM to ROM) */
;@    ldr     r0, =__fastcode_load__
;@    ldr     r1, =__fastcode_start__
;@    ldr     r2, =__fastcode_end__
;@1:
;@    cmp     r1, r2
;@    ldmltia r0!, {r3}
;@    stmltia r1!, {r3}
;@    blt     1b

    /* Relocate .data section (copy from RAM to ROM) */
    ldr     r0, =__data_load__
    ldr     r1, =__data_start__
    ldr     r2, =_edata
1:
    cmp     r1, r2
    ldmltia r0!, {r3}
    stmltia r1!, {r3}
    blt     1b

    /* Clear .bss section (zero init) */
    ldr     r1, =__bss_start__
    ldr     r2, =__bss_end__
    mov     r3, #0
1:
    cmp     r1, r2
    stmltia r1!, {r3}
    blt     1b

    ;@ Set interrupt stacks
    ldr r0,=__stack;
    mov r1,#0x4 ;@ interrupt (4b)

    ;@ UND mode
    msr     cpsr_c, #(UND_MODE | I_BIT | F_BIT)
    mov sp,r0
    sub r0,r0,r1

    ;@ ABT mode
    msr     cpsr_c, #(ABT_MODE | I_BIT | F_BIT)
    mov sp,r0
    sub r0,r0,r1

    mov r1, #0x400 ;@ IRQ and SVC has 1k 
    ;@ FIQ mode
    msr     cpsr_c, #(FIQ_MODE | I_BIT | F_BIT)
    mov sp,r0
    sub r0,r0,r1

    ;@ IRQ mode
    msr     cpsr_c, #(IRQ_MODE | I_BIT | F_BIT)
    mov sp,r0
    sub r0,r0,r1

    ;@ System mode with disabled interrupts
    msr     cpsr_c, #(SVC_MODE | I_BIT | F_BIT)
    mov sp,r0
    sub r0, r0, r1

    ;@ System mode with disabled interrupts
    msr     cpsr_c, #(SYS_MODE | I_BIT | F_BIT)
    mov sp,r0

    ;@ Supervisor mode with disabled interrupts
    msr     cpsr_c, #(SVC_MODE | I_BIT | F_BIT)

;@    ;@ Call constructors for global objects
;@    ldr r0, =__init_array_start
;@    ldr r1, =__init_array_end
;@globals_init:
;@    cmp     r0, r1
;@    ldrlt   r2, [r0], #4
;@    movlt   lr, pc
;@    bxlt    r2
;@    blt     globals_init

    ;@ Enter C/C++ code 
    bl      main
    b       reset

    .section .text

hang:
	b hang

