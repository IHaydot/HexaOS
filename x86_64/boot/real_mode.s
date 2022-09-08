prot_to_real:
    lgdt [real_gdt_desc]
    sidt [protidt]
    lidt [realidt]
    mov esp, eax
    push eax
    mov ebp, 0x8000
    mov esp, ebp
    mov 
    
real_gdt_desc:
    dw 0x27
    dq real_gdt
real_gdt:
    dw 0
    dw 0
    db 0
    db 0
    db 0 
    db 0
    dw 0xffff
    dw 0
    db 0
    db 0x9a
    db 0xcf 
    db 0x0
    dw 0xffff
    dw 0
    db 0
    db 0x92
    db 0xcf
    db 0
    dw 0xffff
    dw 0
    db 0
    db 0x9e
    db 0 
    db 0
    dw 0xffff
    dw 0
    db 0
    db 0x92
    db 0x0
    db 0x0
realidt:
    dw 0x400
    dq 0
protidt:
    dw 0
    dq 0


