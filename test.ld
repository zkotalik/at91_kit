MEMORY
{
    IRAM(rwx)   : ORIGIN = 0x00200000, LENGTH = 16K   
    RAM (rwx)   : ORIGIN = 0x20000000, LENGTH = 32M
    ROM(rw)     : ORIGIN = 0x10000000, LENGTH = 8M
}

REGION_ALIAS("REGION_TEXT", RAM);
REGION_ALIAS("REGION_RODATA", RAM );
REGION_ALIAS("REGION_DATA", RAM);
REGION_ALIAS("REGION_BSS", RAM);

ENTRY(_entry)

SECTIONS {

    .ramvect : {
        __iram_start__ = .;
        . = 0x40;
    } > IRAM

    .text : {
        *startup.o (.text)
        *(.text)
		*(.rodata)
		*(.rodata*)
		*(.glue_7)
		*(.glue_7t)
    } > REGION_TEXT

    .data : {
        __data_start__ = .;
        *(.data)
        __data_end__ = .;
    } > REGION_DATA

    .bss : {
        __bss_start__ = .;
        *(.bss)
    } > REGION_BSS

	. = ALIGN(4);
	.eh_frame :
	{
		 KEEP (*(.eh_frame))
	} > RAM
	
	/* Align here to ensure that the .bss section occupies space up to
	_end.  Align after .bss to ensure correct alignment even if the
	.bss section disappears because there are no input sections.  */
	. = ALIGN(32 / 8);

}
	. = ALIGN(32 / 8);
	_end = .;
	_bss_end__ = . ; __bss_end__ = . ; __end__ = . ;
	PROVIDE (end = .);

    __stack = ORIGIN(REGION_DATA) + LENGTH(REGION_DATA);
