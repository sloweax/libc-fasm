include 'file.inc'

format ELF64

section '.text' executable
public __ffree
extrn munmap
; void __ffree(void *);
__ffree:
  mov rsi, file.sizeof
  call munmap
  ret
