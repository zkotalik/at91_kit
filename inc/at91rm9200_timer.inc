    /* AT91RM9200 timer counter definitions */
    .equ    TC_BASE,        0xFFFA0000
    .equ    TC0_OFS,        0x00000000
    .equ    TC1_OFS,        0x00000040
    .equ    TC2_OFS,        0x00000080
    .equ    TC_BCR,         0x000000C0      /* TC Block Control */
    .equ    TC_BMR,         0x000000C4      /* TC Block Mode */

    .equ    TC_CCR,         0x00000000      /* Channel Control */
    .equ    TC_CMR,         0x00000004      /* Channel Mode */
    .equ    TC_CV,          0x00000010      /* Counter Value */
    .equ    TC_RA,          0x00000014      /* Register A*/
    .equ    TC_RB,          0x00000018      /* Register B*/
    .equ    TC_RC,          0x0000001C      /* Register C*/
    .equ    TC_SR,          0x00000020      /* Status */
    .equ    TC_IER,         0x00000024      /* Interrupt Enable */
    .equ    TC_IDR,         0x00000028      /* Interrupt Disable */
    .equ    TC_IMR,         0x0000002C      /* Interrupt Mask * /

    /* Registers bits definitions */
    .equ    TC_BCR_SYNC,    0x00000001      /* Software trigger */
    .equ    TC_BMR_TC0XC0S_TCLK0,   0x00    
    .equ    TC_BMR_TC0XC0S_TIOA1,   0x02
    .equ    TC_BMR_TC0XC0S_TIOA2,   0x03
    .equ    TC_BMR_TC1XC1S_TCLK1,   0x00    
    .equ    TC_BMR_TC1XC1S_TIOA0,   0x04
    .equ    TC_BMR_TC1XC1S_TIOA2,   0x0C
    .equ    TC_BMR_TC2XC2S_TCLK2,   0x00    
    .equ    TC_BMR_TC2XC2S_TIOA0,   0x20
    .equ    TC_BMR_TC2XC2S_TIOA1,   0x30
    .equ    TC_CCR_CLKEN,           0x01    /* Clock enable */
    .equ    TC_CCR_CLKDIS,          0x02    /* Clock disable */
    .equ    TC_CCR_SWTRG,           0x04    /* Software trigger */
    .equ    TC_CMR_CLKS_MCK_2,      0x00
    .equ    TC_CMR_CLKS_MCK_8,      0x01
    .equ    TC_CMR_CLKS_MCK_32,     0x02
    .equ    TC_CMR_CLKS_MCK_128,    0x03
    .equ    TC_CMR_CLKS_MCK_1024,   0x04
    .equ    TC_CMR_CLKS_MCK_XC0,    0x05
    .equ    TC_CMR_CLKS_MCK_XC1,    0x06
    .equ    TC_CMR_CLKS_MCK_XC2,    0x07
    .equ    TC_CMR_CLKI,            0x80    /* Increment on falling edge */
    .equ    TC_CMR_CPCTRG,          0x4000  /* RC compare resets counter */
    .equ    TC_IER_COVFS,           0x01    /* Counter Overflow Interrupt */
    .equ    TC_IER_LOVRS,           0x02    /* Load Overrun Interrupt */
    .equ    TC_IER_CPAS,            0x04    /* RA Compare Interrupt */
    .equ    TC_IER_CPBS,            0x08    /* RB Compare Interrupt */
    .equ    TC_IER_CPCS,            0x10    /* RC Compare Interrupt */
    .equ    TC_IER_LDRAS,           0x20    /* RA Loading Interrupt */
    .equ    TC_IER_LDRBS,           0x40    /* RB Loading Interrupt */
    .equ    TC_IER_ETRGS,           0x80    /* External Trigger Interrupt */

