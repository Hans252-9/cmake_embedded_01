ENTRY(Reset_Handler)

MEMORY
{
    FLASH   (rx)  : ORIGIN = 0x08000000, LENGTH = 2048K

    /* Data tightly coupled memory */
    DTCMRAM (rwx) : ORIGIN = 0x20000000, LENGTH = 128K

    /* AXI SRAM, vhodná pro větší data a některé DMA operace */
    RAM_D1  (rwx) : ORIGIN = 0x24000000, LENGTH = 512K

    /* Instruction tightly coupled memory */
    ITCMRAM (rwx) : ORIGIN = 0x00000000, LENGTH = 64K
}

_estack = ORIGIN(DTCMRAM) + LENGTH(DTCMRAM);

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
    } > DTCMRAM AT > FLASH

    .bss (NOLOAD) :
    {
        . = ALIGN(4);
        _sbss = .;

        *(.bss)
        *(.bss*)
        *(COMMON)

        . = ALIGN(4);
        _ebss = .;
    } > DTCMRAM

    /*
     * Volitelná sekce pro velké buffery v AXI SRAM.
     */
    .ram_d1 (NOLOAD) :
    {
        . = ALIGN(32);
        _sram_d1 = .;

        *(.ram_d1)
        *(.ram_d1*)

        . = ALIGN(32);
        _eram_d1 = .;
    } > RAM_D1

    /*
     * Volitelná sekce pro kód kopírovaný do ITCM.
     * Zatím zůstane prázdná.
     */
    .itcm (NOLOAD) :
    {
        . = ALIGN(4);
        _sitcm = .;

        *(.itcm)
        *(.itcm*)

        . = ALIGN(4);
        _eitcm = .;
    } > ITCMRAM

    _end = _ebss;
    end = _ebss;

    /DISCARD/ :
    {
        *(.comment)
        *(.note*)
    }
}
