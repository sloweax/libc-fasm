include 'file.inc'

format ELF64

section '.text' executable
extrn open
extrn strlen
extrn __fcreate
public fopen
fopen:
  push rbp
  mov rbp, rsp
  sub rsp, 3

  filteredmode equ rbp - 3
  filepath equ r15
  mode equ r14

  push filepath
  push mode

  mov filepath, rdi
  mov mode, rsi

  mov rdi, mode
  call isvalidmode
  test rax, rax
  jz .error

  lea rdi, [filteredmode]
  mov rsi, mode
  call filtermode

  lea rdi, [filteredmode]
  call modeflags

  mov esi, eax
  mov rdi, filepath
  mov rdx, 666o
  call open
  cmp eax, -1
  jle .error

  mov edi, eax
  call __fcreate

  .return:
    pop mode
    pop filepath
    leave
    ret
  .error:
    xor rax, rax
    jmp .return

; check if mode contains valid chars "rwa+b"
isvalidmode:
  push rbx
  mov rbx, rdi

  mov rdi, rbx
  call strlen
  cmp rax, 3
  ja .error

  cmp byte [rbx], 0
  je .error
  cmp byte [rbx], 'r'
  je .start
  cmp byte [rbx], 'w'
  je .start
  cmp byte [rbx], 'a'
  je .start
  jmp .error

  .start:
    lea rdi, [rbx+1]
  .loop:
    mov cl, byte [rdi]
    cmp cl, 0
    je .return
    cmp cl, '+'
    je .next
    cmp cl, 'b'
    je .next
    jmp .error
    .next:
      inc rdi
      jmp .loop

  mov rax, 1

  .return:
    pop rbx
    ret
  .error:
    xor rax, rax
    jmp .return

; remove b from mode and place into dst
; void filtermode(char *dst, char *mode)
filtermode:
  .loop:
    mov al, byte [rsi]
    test al, al
    jz .return
    cmp al, 'b'
    je .next
    mov byte [rdi], al
    inc rdi
    .next:
      inc rsi
      jmp .loop

  .return:
    mov byte [rdi], al
    ret

; int modeflags(const char* mode);
modeflags:
  push rbx
  push r12
  mov r12, rdi

  call strlen
  cmp rax, 2
  jb .1
  jae .2

  .1:
    mov ebx, O_RDONLY
    cmp byte [r12], 'r'
    je .return
    mov ebx, O_WRONLY or O_TRUNC
    cmp byte [r12], 'w'
    je .return
    mov ebx, O_WRONLY or O_APPEND
    jmp .return
  .2:
    mov ebx, O_RDWR
    cmp word [r12], 'r+'
    je .return
    mov ebx, O_WRONLY or O_TRUNC or O_CREAT
    cmp word [r12], 'w+'
    je .return
    mov ebx, O_WRONLY or O_APPEND or O_CREAT

  .return:
    mov eax, ebx
    pop r12
    pop rbx
    ret
