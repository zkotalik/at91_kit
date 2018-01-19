MEMORY
{
    IRAM(rwx)   : ORIGIN = 0x00200000, LENGTH = 16K   
    IREM(rwx)   : ORIGIN = 0x00000000, LENGTH = 16K
    RAM (rwx)   : ORIGIN = 0x20000000, LENGTH = 32M
    ROM(rw)     : ORIGIN = 0x10000000, LENGTH = 8M
}

REGION_ALIAS("REGION_TEXT", IREM);
REGION_ALIAS("REGION_RODATA", IREM);
REGION_ALIAS("REGION_DATA", IREM);
REGION_ALIAS("REGION_BSS", IREM);

ENTRY(_entry)

SECTIONS {
/*
    .ramvect : {
        __iram_start__ = .;
        . = 0x40;
    } > IRAM
*/
    .text : {
        *startup.o (.text)
        *(.text)
    } > REGION_TEXT

    .data : {
        __data_start__ = .;
        *(.data)
        __data_end__ = .;
    } > REGION_DATA

    .bss : {
        __bss_start__ = .;
        *(.bss)
        __bss_end__ = .;
    } > REGION_BSS

    __stack = ORIGIN(REGION_DATA) + LENGTH(REGION_DATA);

}
