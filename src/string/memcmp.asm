format ELF64

section '.text' executable
public memcmp
memcmp:
  push rdi
  push rsi
  push rdx

  xor eax, eax

  test rdx, rdx
  je .end

  .loop:
    dec rdx
    test rdx, rdx
    je .return
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
    pop rdx
    pop rsi
    pop rdi
    ret
