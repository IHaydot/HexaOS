[bits 16]
[org 0x7e00]
mov bx, booting2
mov bx, booting2
call printx16
call cls
jmp EPM
jmp $
booting2: db "booting2", 0
%include "boot/stage1/writerx16.s"

%include "boot/stage2/PMExtra.s"
LandedInPM: db 'S', 0
[bits 32]
BEGIN_PM: 
    mov ebx, LandedInPM
    call print_strx32
    call DetCPUID
    call DetLongMode
    call IdentityPagingInit
    call x86_64GDT
    mov [0xb8000], byte 'D'
    jmp CODE_SEG:MainModeStart
%include "boot/stage2/writerx86.s"
%include "boot/stage2/long_mode/cpuid.s"
%include "boot/stage2/long_mode/bootPaging.s"
[bits 64]
MainModeStart: 
    mov edi, 0xb8000
    mov rax, 0x1f201f201f201f20
    mov ecx, 500
    rep stosq
    jmp $
times 16384-($-$$) db 0