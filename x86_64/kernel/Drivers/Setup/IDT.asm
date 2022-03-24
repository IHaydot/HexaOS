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
    
[extern general_handler_C]

[extern breakpoint_handler_C]
general_handler:
    PUSHAL
    call general_handler_C
    POPAL
    hlt
    GLOBAL general_handler

breakpoint_handler:
    PUSHAL
    call breakpoint_handler_C
    POPAL
    iretq
    GLOBAL breakpoint_handler

[extern division_handler_C]
division_handler:
    PUSHAL
    call division_handler_C
    POPAL
    hlt
    GLOBAL division_handler

[extern overflow_handler_C]
overflow_hanlder:
    mov ebp, 0x400000
    mov esp, ebp
    PUSHAL
    call overflow_handler_C
    POPAL
    hlt
    GLOBAL overflow_hanlder

[extern double_fault_handler_C]
double_fault_handler:
    PUSHAL
    call double_fault_handler_C
    POPAL
    hlt
    GLOBAL double_fault_handler

[extern page_fault_handler_C]
page_fault_handler:
    PUSHAL
    call page_fault_handler_C
    POPAL
    hlt
    GLOBAL page_fault_handler
[extern cmd_handler_C]
cmd_handler:
    PUSHAL
    call cmd_handler_C
    POPAL
    iretq
    GLOBAL cmd_handler
[extern usb_init_handler_C]
usb_init_handler:
    PUSHAL
    call usb_init_handler_C
    POPAL
    iretq
    GLOBAL usb_init_handler