format ELF64

section '.text' executable 
extrn environ
extrn strncmp
extrn strlen
public getenv
getenv:

  namelen equ rdx
  envp    equ rcx
  env     equ rsi
  tmp     equ rbx

  push envp
  push env
  push namelen
  push tmp

  call strlen 
  mov namelen, rax

  mov envp, [plt environ]

  .loop:
    mov env, [envp]
    test env, env
    jz .null
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
    pop tmp
    pop namelen
    pop env
    pop envp
    ret
  .null:
    xor rax, rax
    jmp .end
