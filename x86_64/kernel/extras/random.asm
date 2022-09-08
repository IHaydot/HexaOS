randomGenerated: db 0
GLOBAL randomGenerated

GenerateRandomNum64:
    call CheckForRandomNumSupport
    cmp rax, 0xdead
    je .GenFail
    mov ecx, 100
    .retry:
        rdseed eax
        jc .done
        loop .retry
    .done:
        mov [randomGenerated], eax
        ret
    .GenFail:
        mov rax, 0xdead
        jmp $
CheckForRandomNumSupport:
    mov eax, 7
    mov ecx, 0
    cpuid
    shr ebx, 18
    and ebx, 1
    cmp ebx, 1
    je .CheckNumSuccess
    mov rax, 0xdead
    ret
    .CheckNumSuccess:
        ret
    GLOBAL GenerateRandomNum64 