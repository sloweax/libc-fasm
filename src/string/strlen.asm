format ELF64

section '.text' executable
public strlen
strlen:
  mov rax, rdi

  .loop:
    cmp byte [rax], 0
    je .return
    inc rax
    jmp .loop

  .return:
    sub rax, rdi
    ret
