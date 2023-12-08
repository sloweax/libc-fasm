format ELF64

section '.text' executable
public strchr
strchr:
  mov rax, rdi

  .loop:
    cmp byte [rax], 0
    je .null
    cmp byte [rax], sil
    je .return
    inc rax
    jmp .loop

  .return:
    ret

  .null:
    xor rax, rax
    jmp .return
  
