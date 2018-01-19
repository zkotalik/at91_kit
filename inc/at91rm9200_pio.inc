    /* Parallel Input/Output - PIO */
    .equ    PIOA_BASE,          0xFFFFF400
    .equ    PIOB_BASE,          0xFFFFF600
    .equ    PIOC_BASE,          0xFFFFF800

    .equ    PIO_PER,            0x00        /* Enable */
    .equ    PIO_PDR,            0x04        /* Disable */
    .equ    PIO_PSR,            0x08        /* Status*/
    .equ    PIO_OER,            0x10        /* Output enable */
    .equ    PIO_ODR,            0x14        /* Output disable */
    .equ    PIO_OSR,            0x18        /* Output status */
    .equ    PIO_IFER,           0x20        /* Glitch input filter enable*/
    .equ    PIO_IFDR,           0x24        /* Glitch input filter dis */
    .equ    PIO_IFSR,           0x28        /* Glitch input status */
    .equ    PIO_SODR,           0x30        /* set output data */
    .equ    PIO_CODR,           0x34        /* clear output data */
    .equ    PIO_ODSR,           0x38        /* output data status */
    .equ    PIO_PDSR,           0x3C        /* pin data status */
    .equ    PIO_IER,            0x40        /* interrupt enable */
    .equ    PIO_IDR,            0x44        /* interrupt disable */
    .equ    PIO_IMR,            0x48        /* interrupt mask */
    .equ    PIO_ISR,            0x4C        /* interrupt status */
    .equ    PIO_MDER,           0x50        /* multi-driver enable */
    .equ    PIO_MDDR,           0x54        /* multi-driver disable */
    .equ    PIO_MDSR,           0x58        /* multi-driver status */
    .equ    PIO_PUER,           0x60        /* pull-up enable */
    .equ    PIO_PUDR,           0x64        /* pull-up disable */
    .equ    PIO_PUSR,           0x68        /* pull-up status */
    .equ    PIO_ASR,            0x70        /* peripheral A select */
    .equ    PIO_BSR,            0x74        /* peripheral B select */
    .equ    PIO_ABSR,           0x78        /* peripheral status */
    .equ    PIO_OWER,           0xA0        /* output write enable */
    .equ    PIO_OWDR,           0xA4        /* output write disable */
    .equ    PIO_OWSR,           0xA8        /* output write status */

