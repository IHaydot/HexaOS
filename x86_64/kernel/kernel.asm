[bits 64]
assembly_kernel:
    
    cmp ebx, 0xe9d
    je interrupts_handler
interrupts_handler_return_point:
    ret

    GLOBAL assembly_kernel

interrupts_handler:
    cmp rax, 0x157
    je int157

    jmp interrupts_handler_return_point
int157:
    int 157
    jmp interrupts_handler_return_point
