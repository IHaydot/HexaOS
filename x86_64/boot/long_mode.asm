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
    mov edi, 0xb8000
    mov rax, 0x8f208f208f208f20
    mov ecx, 500
    rep stosq
    call _start
    hlt