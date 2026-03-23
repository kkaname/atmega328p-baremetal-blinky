MEMORY
{
    FLASH (rx) : ORIGIN = 0x0000, LENGTH = 32K
    RAM   (rw) : ORIGIN = 0x800100, LENGTH = 2K
}

SECTIONS
{
    .text :
    {
        KEEP(*(.vectors))     /* interrupt vectors */
        *(.text*)             /* program code */
        *(.rodata*)           /* const data */
        _etext = .;
    } > FLASH

    .data :
    {
        __data_start = .;
        *(.data*)
        __data_end = .;
    } > RAM AT > FLASH
    __data_load_start = LOADADDR(.data);

    .bss :
    {
        __bss_start = .;
        *(.bss*)
        *(COMMON)
        __bss_end = .;
    } > RAM

    __stack = ORIGIN(RAM) + LENGTH(RAM) - 1;
}
