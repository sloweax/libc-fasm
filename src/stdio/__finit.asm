include 'file.inc'

format ELF64

section '.text' executable
extrn memset
public __finit
; void *__finit(void *, int fd);  
__finit:
  file equ r12
  qfd equ rbx
  fd equ ebx

  push file
  push qfd

  mov file, rdi
  mov fd, esi

  mov esi, 0
  mov rdx, 12
  call memset ; zero file.fd + file.pos

  mov dword [file + file.fd], fd

  mov rax, file

  pop qfd
  pop file
  ret
