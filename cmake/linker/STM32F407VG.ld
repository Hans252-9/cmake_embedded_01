ENTRY(Reset_Handler)

MEMORY
{
    FLASH (rx)  : ORIGIN = 0x08000000, LENGTH = 1024K

    /* SRAM1 112 KB + SRAM2 16 KB */
    RAM   (rwx) : ORIGIN = 0x20000000, LENGTH = 128K

    /* Core-coupled RAM; není běžně dostupná všem DMA periferiím */
    CCMRAM (rwx) : ORIGIN = 0x10000000, LENGTH = 64K
}

_estack = ORIGIN(RAM) + LENGTH(RAM);

SECTIONS
{
    .isr_vector :
    {
        . = ALIGN(1024);
        KEEP(*(.isr_vector))
        . = ALIGN(4);
    } > FLASH

    .text :
    {
        . = ALIGN(4);

        *(.text)
        *(.text*)
        *(.rodata)
        *(.rodata*)

        KEEP(*(.init))
        KEEP(*(.fini))

        . = ALIGN(4);
        _etext = .;
    } > FLASH

    .ARM.extab :
    {
        *(.ARM.extab*)
    } > FLASH

    .ARM.exidx :
    {
        __exidx_start = .;
        *(.ARM.exidx*)
        __exidx_end = .;
    } > FLASH

    _sidata = LOADADDR(.data);

    .data :
    {
        . = ALIGN(4);
        _sdata = .;

        *(.data)
        *(.data*)

        . = ALIGN(4);
        _edata = .;
    } > RAM AT > FLASH

    .bss (NOLOAD) :
    {
        . = ALIGN(4);
        _sbss = .;

        *(.bss)
        *(.bss*)
        *(COMMON)

        . = ALIGN(4);
        _ebss = .;
    } > RAM

    /*
     * Proměnné lze později explicitně umístit do sekce .ccmram.
     * Například pomocí atributu section(".ccmram").
     */
    .ccmram (NOLOAD) :
    {
        . = ALIGN(4);
        _sccmram = .;

        *(.ccmram)
        *(.ccmram*)

        . = ALIGN(4);
        _eccmram = .;
    } > CCMRAM

    _end = _ebss;
    end = _ebss;

    /DISCARD/ :
    {
        *(.comment)
        *(.note*)
    }
}
