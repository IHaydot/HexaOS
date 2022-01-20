PROGRAM_SPACE equ 0x7e00
disk_init: 
    mov ah, 0x02
    mov bx, PROGRAM_SPACE
    mov al, 32
    mov dl, [BOOT_DRIVE]
    mov ch, 0x00
    mov dh, 0x00
    mov cl, 0x02
    int 0x13
    jc disk_fail_handler
    ret
BOOT_DRIVE: db 0
disk_fail_handler:  
    ;TODO SHELL
    mov bx, disk_fail_message
    call printx16
disk_fail_message: db ' failed to read the disk...', 0
