[extern _idt]
IDTdescriptor:
    dw 4095
    dq _idt

%macro PUSHAL 0
    push rax
    push rcx
    push rdx
    push r8
    push r9
    push r10
    push r11
%endmacro

%macro POPAL 0
    pop rax
    pop rcx
    pop rdx
    pop r8
    pop r9
    pop r10
    pop r11
%endmacro

[extern isr1_handler]
isr1:
    PUSHAL
    call isr1_handler
    POPAL
    iretq
    GLOBAL isr1
    
InitIDTASM:
    lidt[IDTdescriptor]
    sti
    ret
    GLOBAL InitIDTASM
