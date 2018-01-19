;@ Memory management Controller (MC)

.equ    MC_BASE,    0xFFFFFF00

.equ    MC_RCR,     0x00            ;@ Remap Control
.equ    MC_ASR,     0x04            ;@ Abort Status
.equ    MC_AASR,    0x08            ;@ Abort Address Status
.equ    MC_MPR,     0x0C            ;@ Master Priority 

.equ    EBI_OFS,    0x60            ;@ EBI Configurations Registers
.equ    EBI_CSA,    0x00            ;@ Chip Select Assignement 
.equ    EBI_CFGR,   0x04            ;@ Configuration 

.equ    SMC_OFS,    0x10            ;@ SMC User Interface
.equ    SDRAMC_OFS, 0x30            ;@ SDRAMC User Interface

;@ SMC regs
.equ    SMC_CSR0,   0x00            ;@ Chip select register 0
.equ    SMC_CSR1,   0x04            ;@ Chip select register 1
.equ    SMC_CSR2,   0x08            ;@ Chip select register 2
.equ    SMC_CSR3,   0x0C            ;@ Chip select register 3
.equ    SMC_CSR4,   0x10            ;@ Chip select register 4
.equ    SMC_CSR5,   0x14            ;@ Chip select register 5
.equ    SMC_CSR6,   0x18            ;@ Chip select register 6
.equ    SMC_CSR7,   0x1C            ;@ Chip select register 7

;@ SDRAM regs
.equ    SDRAM_MR,   0x00            ;@ 0x00 SDRAMC Mode Register
.equ    SDRAM_TR,   0x04            ;@ 0x04 SDRAMC Refresh Timer Register
.equ    SDRAM_CR,   0x08            ;@ 0x08 SDRAMC Configuration Register
.equ    SDRAM_SSR,  0x0C            ;@ 0x0C SDRAMC Self Refresh Register
.equ    SDRAM_LPR,  0x10            ;@ 0x10 SDRAMC Low Power Register
.equ    SDRAM_IER,  0x14            ;@ 0x14 SDRAMC Interrupt Enable Register
.equ    SDRAM_IDR,  0x18            ;@ 0x18 SDRAMC Interrupt Disable Register
.equ    SDRAM_IMR,  0x1C            ;@ 0x1C SDRAMC Interrupt Mask Register
.equ    SDRAM_ICR,  0x20            ;@ 0x20 SDRAMC Interrupt Status Register

;@ Bits Assignement
.equ    MC_RCB,     0x01            ;@ Toggle remapping

.equ    EBI_CSA_CS0A,	    0x0001
.equ    EBI_CSA_CS1A,	    0x0002
.equ    EBI_CSA_CS3A,	    0x0008
.equ    EBI_CSA_CS4A,	    0x0010

.equ    SMC_CSR_RWHOLD,		    28
.equ    SMC_CSR_RWSETUP,		24
.equ    SMC_CSR_ACSS_STANDARD,	0x00000000
.equ    SMC_CSR_ACSS_1CYCLE,	0x00010000
.equ    SMC_CSR_ACSS_2CYCLE,	0x00020000
.equ    SMC_CSR_ACSS_3CYCLE,	0x00030000
.equ    SMC_CSR_DRP,		    0x00008000
.equ    SMC_CSR_DBW_8,		    0x00004000
.equ    SMC_CSR_DBW_16,		    0x00002000
.equ    SMC_CSR_BAT_8,		    0x00000000
.equ    SMC_CSR_BAT_16,		    0x00001000
.equ    SMC_CSR_TDF,		    8
.equ    SMC_CSR_WSEN,		    0x00000080
.equ    SMC_CSR_NWS,		    0x7F

.equ    SDRAM_MR_MODE_NORMAL,    0
.equ    SDRAM_MR_MODE_NOP,       1
.equ    SDRAM_MR_MODE_PRECHARGE, 2
.equ    SDRAM_MR_MODE_LOAD,      3
.equ    SDRAM_MR_MODE_REFRESH,   4
.equ    SDRAM_MR_DBW_32,         0
.equ    SDRAM_MR_DBW_16,         (1<<4)

.equ    SDRAM_CR_NC_8,           0
.equ    SDRAM_CR_NC_9,           1
.equ    SDRAM_CR_NC_10,          2
.equ    SDRAM_CR_NC_11,          3
.equ    SDRAM_CR_NR_11,          0
.equ    SDRAM_CR_NR_12,          (1<<2)
.equ    SDRAM_CR_NR_13,          (2<<2)
.equ    SDRAM_CR_NB_2,           0
.equ    SDRAM_CR_NB_4,           (1<<4)
.equ    SDRAM_CR_CAS,            (2<<5)
.equ    SDRAM_TWR,              7
.equ    SDRAM_TRC,              11
.equ    SDRAM_TRP,              15
.equ    SDRAM_TRCD,             19
.equ    SDRAM_TRAS,             23
.equ    SDRAM_TXSR,             27

;@ Values for application
.equ    NWS,            4
.equ    TDF,            2
.equ    RWSETUP,        0
.equ    RWHOLD,         0

.equ    TWR,            2
.equ    TRC,            8
.equ    TRP,            1
.equ    TRCD,           1
.equ    TRAS,           3
.equ    TXSR,           4

.equ    LCD_NWS,        10
.equ    LCD_RWSETUP,    1
.equ    LCD_RWHOLD,     4
.equ    LCD_TDF,        3

.equ    SMC_CSR0_VAL, (NWS | SMC_CSR_WSEN | (TDF << SMC_CSR_TDF) | SMC_CSR_BAT_16 | SMC_CSR_DBW_16 | SMC_CSR_ACSS_STANDARD | (RWSETUP << SMC_CSR_RWSETUP) | (RWHOLD << SMC_CSR_RWHOLD))
.equ    SDRAM_CR_VAL, (SDRAM_CR_NC_9 | SDRAM_CR_NR_12 | SDRAM_CR_NB_4 | SDRAM_CR_CAS | (TWR << SDRAM_TWR) | (TRC << SDRAM_TRC) | (TRP << SDRAM_TRP) | (TRCD << SDRAM_TRCD) | (TRAS << SDRAM_TRAS) | (TXSR << SDRAM_TXSR))

.equ SMC_CSR3_VAL, (LCD_NWS | SMC_CSR_WSEN | SMC_CSR_DBW_8 | SMC_CSR_ACSS_2CYCLE) ;@ | (LCD_RWSETUP << SMC_CSR_RWSETUP) | (LCD_RWHOLD << SMC_CSR_RWHOLD))

.equ   SDRAMC_ADDRESS,  0x20000000


