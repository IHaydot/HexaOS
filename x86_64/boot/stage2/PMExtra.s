EPM: 
    jmp switch_to_x32
    
    jmp $
EnableA20:
    in al, 0x92
    or al, 2
    out 0x92, al
    ret

[bits 16]
gdt_start:

gdt_null:
    dd 0
    dd 0

gdt_code:
    dw 0xffff
    dw 0x0
    db 0x0
    db 10011010b
    db 11001111b
    db 0x0
gdt_data:
    dw 0xffff
    dw 0x0
    db 0x0
    db 10010010b
    db 11001111b
    db 0x0
gdt_end:

gdt_descriptor:
    dw gdt_end - gdt_start - 1
    dq gdt_start
CODE_SEG equ gdt_code - gdt_start
DATA_SEG equ gdt_data - gdt_start

[bits 16]
switch_to_x32:
    call EnableA20
    cli
    lgdt [gdt_descriptor]
    mov eax, cr0
    or eax, 0x1
    mov cr0, eax
    jmp CODE_SEG:init_x32
[bits 32]
init_x32:
    mov ax, DATA_SEG 
    mov ds, ax 
    mov ss, ax 
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ebp , 0x90000
    mov esp , ebp 
    call BEGIN_PM
[bits 32]
x86_64GDT:
    mov [gdt_code + 6], byte 10101111b
    mov [gdt_data + 6], byte 10101111b
    ret
[bits 16]
