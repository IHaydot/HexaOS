[bits 16]
[org 0x7c00]
mov [BOOT_DRIVE], dl
mov bp, 0x8000
mov sp, bp
call cls
mov bx, booting1
call printx16
call disk_init
jmp PROGRAM_SPACE

%include "boot/stage1/writerx16.s"
%include "boot/stage1/disk.s"
booting1: db "booting1", 0
times 510-($-$$) db 0
dw 0xaa55