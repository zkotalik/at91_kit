    /* Power Management Controller (PMC) */
    .equ    PMC_BASE,           0xFFFFFC00
    .equ    PMC_SCER_OFS,       0x00        /* Sys Clk Enable Reg */
    .equ    PMC_SCDR_OFS,       0x04        /* Sys Clk Disable Reg */
    .equ    PMC_SCSR_OFS,       0x08        /* Sys Clk Status Reg        */
    .equ    PMC_PCER_OFS,       0x10        /* Periph Clk Enable Reg     */
    .equ    PMC_PCDR_OFS,       0x14        /* Periph Clk Disable Reg    */
    .equ    PMC_PCSR_OFS,       0x18        /* Periph Clk Status Reg     */
    .equ    CKGR_MOR_OFS,       0x20        /* Main Oscillator Reg       */
    .equ    CKGR_MCFR_OFS,      0x24        /* Main Clock Freq Reg       */
    .equ    CKGR_PLLAR_OFS,     0x28        /* PLLA Reg                  */
    .equ    CKGR_PLLBR_OFS,     0x2C        /* PLLA Reg                  */
    .equ    PMC_MCKR_OFS,       0x30        /* Master Clock Reg          */
    .equ    PMC_PCK0_OFS,       0x40        /* Programmable Clk 0 Reg    */
    .equ    PMC_PCK1_OFS,       0x44        /* Programmable Clk 1 Reg    */
    .equ    PMC_PCK2_OFS,       0x48        /* Programmable Clk 2 Reg    */
    .equ    PMC_PCK3_OFS,       0x4C        /* Programmable Clk 3 Reg    */
    .equ    PMC_IER_OFS,        0x60        /* Interrupt Enable  Reg     */
    .equ    PMC_IDR_OFS,        0x64        /* Interrupt Disable Reg     */
    .equ    PMC_SR_OFS,         0x68        /* Status Reg                */
    .equ    PMC_IMR_OFS,        0x6C        /* Interrupt Mask Reg        */

    /* bits */
    .equ    PMC_MOSCEN,         (1<<0)      /* Main osc. enable          */
    .equ    PMC_MUL,            (0x7FF<<16) /* PLL Multiplier            */
    .equ    PMC_MOSCS,          (1<<0)      /* Main Oscillator Stable    */
    .equ    PMC_LOCKA,          (1<<1)      /* PLL A Lock Status         */
    .equ    PMC_LOCKB,          (1<<2)      /* PLL A Lock Status         */
    .equ    PMC_MCKRDY,         (1<<3)      /* Master Clock Status       */

    .equ    PMC_SETUP,          1
    .equ    PMC_SCER_Val,       0x00000001
    .equ    PMC_PCER_Val,       0x00000018
    .equ    CKGR_MOR_EN_VAL,    0x000FF001  /* 2ms=0x40 for stable */
    .equ    CKGR_PLLAR_Val,     0x2026BF04  /* MULA=38,O=2,0.5ms stable,DIV=4 */
    .equ    CKGR_PLLBR_Val,     0x10483F0E
    .equ    PMC_MCKR_Val,       0x00000202  /* MCK 3x slower PCK */ 
    .equ    PMC_MCKR_Fil,       0xFFFFFCE0  /* Valid bits filter */
    .equ    PMC_PCK0_Val,       0x00000000
    .equ    PMC_PCK1_Val,       0x00000000
    .equ    PMC_PCK2_Val,       0x00000000
    .equ    PMC_PCK3_Val,       0x00000000

