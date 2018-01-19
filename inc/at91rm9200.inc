	/* Standard definitions of Mode bits and Interrupt (I & F)
         * flags in PSRs 
         */
	.equ	USR_MODE, 0x10
	.equ	FIQ_MODE, 0x11
	.equ	IRQ_MODE, 0x12
	.equ	SVC_MODE, 0x13
	.equ	ABT_MODE, 0x17
	.equ	UND_MODE, 0x1B
	.equ	SYS_MODE, 0x1F

	.equ	I_BIT, 0x80            /* when I bit is set, IRQ is disabled */
	.equ	F_BIT, 0x40            /* when F bit is set, FIQ is disabled */


    
    /* Peripherials Identifiers */
    .equ    ID_AIC,             0x00        /* FIQ */
    .equ    ID_SYSIRQ,          0x01        /* System peripherials */
    .equ    ID_PIOA,            0x02
    .equ    ID_PIOB,            0x03
    .equ    ID_PIOC,            0x04
    .equ    ID_PIOD,            0x05
    .equ    ID_US0,             0x06
    .equ    ID_US1,             0x07
    .equ    ID_US2,             0x08
    .equ    ID_US3,             0x09
    .equ    ID_MCI,             0x0A
    .equ    ID_UDP,             0x0B
    .equ    ID_TWI,             0x0C
    .equ    ID_SPI,             0x0D
    .equ    ID_SSC0,            0x0E
    .equ    ID_SSC1,            0x0F
    .equ    ID_SSC2,            0x10
    .equ    ID_TC0,             0x11
    .equ    ID_TC1,             0x12
    .equ    ID_TC2,             0x13
    .equ    ID_TC3,             0x14
    .equ    ID_TC4,             0x15
    .equ    ID_TC5,             0x16
    .equ    ID_UHP,             0x17
    .equ    ID_EMAC,            0x18


