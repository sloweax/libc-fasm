include 'file.inc'

format ELF64

section '.text' executable
public __finit
; void __finit(void *, int fd);
__finit:
  mov qword [rdi + file.pos], 0
  mov dword [rdi + file.fd], esi
  ret
