format ELF64

section '.text' executable
public strncmp
strncmp:
  push rdi
  push rsi
  push rdx

  xor eax, eax

  .loop:
    cmp rdx, 0
    je .end
    mov al, byte [rdi]
    cmp al, byte [rsi]
    jz .cmp
    jne .cmp
    inc rdi
    inc rsi
    dec rdx
    jmp .loop

  .cmp:
    movsx eax, byte [rdi]
    movsx edi, byte [rsi]
    sub eax, edi
  .end:
    pop rdx
    pop rsi
    pop rdi
    ret
