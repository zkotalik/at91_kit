/*******************************************************
 * Some usefull macros
 */
    .include "at91rm9200.inc"

    .equ    I_BIT,      0x80        /* Interrupt bit in CPSR */

    /* IRQ entry code */
    .macro IRQ_ENTRY regs:vararg

    /* Adjust and save lr_irq on stack */
    sub     r14, r14, #4
    stmfd   sp!, {r14}
    /* Write in IVR to support protect mode */
    /* No effect in normal mode */
    /* De-assert NIRQ and clear sources in protect mode */
    ldr     r14, =AIC_BASE
    str     r14, [r14, #AIC_IVR_OFS]
    /* Save R0 and SPRS in IRQ stack */
    mrs     r14, spsr
    stmfd   sp!, {r0, r14}
    /* Enable Interrupt and switch in SYS mode */
    mrs     r0, cpsr
    bic     r0, r0, #(I_BIT | SYS_MODE)
    orr     r0, r0, #SYS_MODE
    msr     cpsr_c, r0
    /* Save scratch/used regs and lr in user stack */
    .ifb \regs
    stmfd   sp!, {r1-r3, r12, r14}
    .else
    stmfd   sp!, {r1-r3, \regs, r12, r14}
    .endif
    .endm

    /* IRQ exit code */
    .macro IRQ_EXIT regs:vararg

    /* Restore scratch/used regs and lr from user stack */
    .ifb \regs
    ldmia   sp!, {r1-r3, r12, r14}
    .else
    ldmia   sp!, {r1-r3, \regs, r12, r14}
    .endif
    /* Disable interrupt and switch back to IRQ_MODE */
    mrs     r0, cpsr
    bic     r0, #SYS_MODE
    orr     r0, #(I_BIT | IRQ_MODE)
    msr     cpsr_c, r0
    /* Mark end of interrupt on AIC */
    ldr     r0, =AIC_BASE
    str     r0, [r0, #AIC_EOICR_OFS]
    /* Restore spsr and r0 from IRQ stack */
    ldmia   sp!, {r0, r14}
    msr     spsr, r14
    /* Restore adjusted lr_irq from IRQ stack directly in pc */
    ldmia   sp!, {pc}^
    .endm

