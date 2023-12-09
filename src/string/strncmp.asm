format ELF64

section '.text' executable
public strncmp
strncmp:

  xor eax, eax
  test rdx, rdx
  jz .null

  .loop:
    dec rdx
    jz .return

    mov al, byte [rdi]
    cmp al, byte [rsi]
    jne .return

    test al, al
    jz .return

    mov al, byte [rsi]
    test al, al
    jz .return

    inc rdi
    inc rsi

    jmp .loop

  .return:
    movzx eax, byte [rdi]
    movzx edi, byte [rsi]
    sub eax, edi
  .null:
    ret
