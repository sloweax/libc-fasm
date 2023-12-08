format ELF64

section '.text' executable
public strcmp
strcmp:
  push rdi
  push rsi

  .loop:
    mov al, byte [rdi]
    cmp al, byte [rsi]
    jne .return

    test al, al
    je .return

    mov al, byte [rsi]
    test al, al
    je .return

    inc rdi
    inc rsi
    jmp .loop

  .return:
    movzx eax, byte [rdi]
    movzx edi, byte [rsi]
    sub eax, edi
    pop rsi
    pop rdi
    ret
