include 'file.inc'

format ELF64

section '.text' executable
extrn mmap
extrn __finit
public __fcreate
; void *__fcreate(int fd);  
__fcreate:
  file equ r12
  qfd equ rbx
  fd equ ebx

  push file
  push qfd

  mov fd, edi

  mov rdi, 0
  mov rsi, file.sizeof
  mov rdx, PROT_READ or PROT_WRITE
  mov rcx, MAP_ANONYMOUS or MAP_PRIVATE
  mov r8, -1
  mov r9, 0
  call mmap
  test rax, rax
  jz .return

  mov file, rax

  mov rdi, file
  mov esi, fd
  call plt __finit

  .return:
    pop qfd
    pop file
    ret
