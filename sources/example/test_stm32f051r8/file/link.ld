/*
    Mark
*/

MEMORY
{
   FLASH(RX)    : ORIGIN = 0x08000000, LENGTH = 64K
   RAM(RWX)     : ORIGIN = 0x20000000, LENGTH = 8K
}

/*
.text — скомпилированный машинный код;
.rodata — аналог .data для неизменяемых данных;
.data — глобальные и статические переменные;
.bss — глобальные и статические переменные, которые при старте содержат нулевое значение.

.comment — информация о версии компилятора;
.ARM.attributes — ARM-специфичные атрибуты файла.
*/

_Min_Heap_Size =0;      /* required amount of heap  */

SECTIONS
{
    .isr_vector :
    {
        . = ALIGN(4);
        _start_isr_vector = .;
        KEEP(*(.isr_vector))
        _end_isr_vector = .;
        . = ALIGN(4);
        _start_loop = .;
        KEEP(*(.programm_flash))
        . = ALIGN(4);
        _end_loop = .;
    } > FLASH = 0xff

    .text :
    {
        . = ALIGN(4);
        _start_text = .;
        *(.text)
        *(.text*)
        . = ALIGN(4);
        _start_data_flash = .;
        KEEP(*(.data_flash))
        . = ALIGN(8);
        _end_data_flash = .;
        _end_text = .;

    } > FLASH

    .ARM.exidx :
    {
        *(.ARM.exidx* .gnu.linkonce.armexidx.*)

    } > FLASH

    . = ALIGN(8);
    __exidx_end = .;

    .rodata :
    {
        . = ALIGN(4);
        _start_rodata = .;
        *(.rodata)
        *(.rodata*)
        . = ALIGN(4);
        _end_rodata = .;
    } > RAM AT > FLASH

    .data :
    {
        . = ALIGN(4);
        _start_data = .;
        *(.data)
        *(.data*)
        . = ALIGN(4);
        _end_data = .;
    } >  RAM AT > FLASH

    .bss :
    {
        . = ALIGN(4);
        _start_bss = .;
        *(.bss)
        *(.bss*)
        . = ALIGN(4);
        _end_bss = .;
    } > RAM

    .heap :
    {
        . = ALIGN (8);
        end = .;
        _end = end;
        . = ALIGN(8);
        . = . + _Min_Heap_Size;
        . = ALIGN(8);
        _End_Heap_Size = .;
    } > RAM
}

_size_rodata = SIZEOF(.rodata);
_size_data = SIZEOF(.data);
_size_bss = SIZEOF(.bss);

_start_rodata_copi = __exidx_end;
_start_data_copi = __exidx_end + _size_rodata;
_start_bss_copi = __exidx_end + _size_rodata + _size_data;
