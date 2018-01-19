    /* AIC - Advanced Interrupt Controller */
    .equ    AIC_BASE,           0xFFFFF000
    .equ    AIC_SMR0_OFS,       0x00        /* Source Mode 0 */
    .equ    AIC_SVR0_OFS,       0x80        /* Source Vector */
    .equ    AIC_IVR_OFS,        0x100       /* Interrupt Vector */
    .equ    AIC_FVR_OFS,        0x104       /* Fast Interrupt Vector */
    .equ    AIC_ISR_OFS,        0x108       /* Interrupt Status */
    .equ    AIC_IPR_OFS,        0x10C       /* Interrupt Pending */
    .equ    AIC_IMR_OFS,        0x110       /* Interrupt Mask */
    .equ    AIC_CISR_OFS,       0x140       /* Core Interrupt Status */
    .equ    AIC_IECR_OFS,       0x120       /* Interrupt Enable */
    .equ    AIC_IDCR_OFS,       0x124       /* Interrupt Disable */
    .equ    AIC_ICCR_OFS,       0x128       /* Interrupt Clear */
    .equ    AIC_ISCR_OFS,       0x12C       /* Interrupt Set */
    .equ    AIC_EOICR_OFS,      0x130       /* End of Interrupt Command */
    .equ    AIC_SPU_OFS,        0x134       /* Spurious Interrupt Vector */
    .equ    AIC_DCR_OFS,        0x138       /* Debug Control */

    /* AIC bit control */
    .equ    AIC_SMR_SRC_LLS,    0x00        /* Low Level Sensitive */
    .equ    AIC_SMR_SRC_NET,    0x20        /* Negative-edge Triggered */
    .equ    AIC_SMR_SRC_HLS,    0x40        /* High Level Sensitive */
    .equ    AIC_SMR_SRC_PET,    0x60        /* Positive-edge Triggered */

