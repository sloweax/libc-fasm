format ELF64

section '.text' executable
public strncmp
strncmp:
  push rdi
  push rsi
  push rdx

  xor eax, eax
  test rdx, rdx
  je .null

  .loop:
    dec rdx
    jz .return

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
  .null:
    pop rdx
    pop rsi
    pop rdi
    ret
