ENTRY(start)

SECTIONS
{
    . = 1M;
    .idt BLOCK(0x1000) : ALIGN(0x1000)
    {
        _idt = .;
        . = . + 0x1000;
    }

    .boot :
    {
        *(.multiboot_header)
    }
    .text :
    {
        *(.text)
    }
}