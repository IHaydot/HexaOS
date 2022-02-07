MemoryRegionCount:
    db 0
    GLOBAL MemoryRegionCount
DetectMemory:
    mov ax, 0
    mov es, ax
    mov di, 0xdead
    mov edx, 0x534d4150
    xor ebx, ebx
    .repmem:
        mov eax, 0xe820
        mov ecx, 24
        int 0x15
        cmp ebx, 0
        je .finmem
        mov di, 4 
        inc byte [MemoryRegionCount]
        jmp .repmem
    .finmem:

    ret 