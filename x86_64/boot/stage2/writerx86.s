VIDEO_MEMORY equ 0xb8000
COLOR equ 0xf0
print_strx32:
    pusha
    mov edx, VIDEO_MEMORY
char_loopx32:
    mov al, [ebx]
    mov ah, COLOR
    cmp al, 0
    je done_print
    mov [edx], ax
    add ebx, 1
    add edx, 2
    jmp char_loopx32
done_print:
    popa
    ret