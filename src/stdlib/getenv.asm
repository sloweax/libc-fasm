format ELF64

section '.text' executable 
extrn environ
extrn strncmp
extrn strlen
public getenv
getenv:

  name    equ r12
  namelen equ r13
  envp    equ r15
  env     equ r14
  tmp     equ r11

  push envp
  push env
  push namelen
  push name

  mov name, rdi

  call strlen 
  mov namelen, rax

  mov envp, [plt environ]

  .loop:
    mov env, [envp]
    test env, env
    jz .null
    mov rdi, name
    mov rsi, env
    mov rdx, namelen
    call strncmp
    test rax, rax
    jz .return
  .next:
    add envp, 8
    jmp .loop

  .return:
    lea tmp, [env+namelen]
    mov al, byte [tmp]
    cmp al, '='
    jne .next
    lea rax, [tmp+1]
  .end:
    pop name
    pop namelen
    pop env
    pop envp
    ret
  .null:
    xor rax, rax
    jmp .end
