printx16:
    pusha
char_loopx16:
    mov al, [bx]
    cmp al, 0
    jne print_charx16
    popa
    ret
print_charx16:
    mov ah, 0x0e
    int 0x10
    add bx, 1
    jmp char_loopx16
cls:
    pusha
    mov ah, 0x00
    mov al, 0x03
    int 0x10
    popa
    ret