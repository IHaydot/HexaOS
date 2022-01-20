DetCPUID:
    pushfd
    pop eax
    mov ecx, eax
    xor eax, 1 << 21
    push eax
    popfd
    pushfd
    pop eax
    push ecx
    popfd
    xor eax, ecx
    jz NoCPUID
    ret
DetLongMode: 
    mov eax, 0x80000001
    cpuid
    test edx, 1 << 29
    jz NoLongMode
    
    ret
NoLongMode:
    mov ebx, NoLongModestr
    call print_strx32
    hlt
NoLongModestr: db 'NLONGMODE', 0
NoCPUID:
    mov ebx, NoCPUIDStr
    call print_strx32
    hlt
NoCPUIDStr: db 'NCPUID', 0