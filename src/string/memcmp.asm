format ELF64

section '.text' executable
public memcmp
memcmp:

  xor eax, eax

  test rdx, rdx
  jz .end

  .loop:
    dec rdx
    jz .return
    mov al, byte [rdi]
    cmp al, byte [rsi]
    jne .return
    inc rdi
    inc rsi
    jmp .loop

  .return:
    movzx eax, byte [rdi]
    movzx edi, byte [rsi]
    sub eax, edi
  .end:
    ret
