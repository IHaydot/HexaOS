global LMBegin
extern _start
section .text
bits 64
LMBegin:
    mov ax, 0
    mov ss, ax
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov rax, 0x2f592f412f4b2f4f
    mov qword [0xb8000], rax
    call _start
    hlt