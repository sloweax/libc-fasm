include '../sys64.inc'

format ELF64

section '.text' executable 
extrn environ
extrn strncmp
extrn strlen
public getenv
getenv:
  push rbp
  mov rbp, rsp
  sub rsp, 16

  push rdi
  push rsi
  push rdx
  push rbx

  namelen equ qword [rbp - 8]
  envp    equ qword [rbp - 16]

  call strlen 
  mov rdx, rax
  mov namelen, rax

  mov rax, [plt environ]
  mov envp, rax

  .loop:
    mov rax, envp
    mov rsi, [rax]
    test rsi, rsi
    je .null
    call strncmp
    test rax, rax
    je .return
  .next:
    add envp, 8
    jmp .loop

  .return:
    mov rbx, rsi
    add rbx, namelen
    mov al, byte [rbx]
    cmp al, '='
    jne .next
    mov rax, rbx
    inc rax
  .end:
    pop rbx
    pop rdx
    pop rsi
    pop rdi
    leave
    ret
  .null:
    mov rax, 0
    jmp .end
