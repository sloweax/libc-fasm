format ELF64

section '.text' executable
public bzero
extrn memset
bzero:
  push rax
  mov rdx, rsi
  mov rsi, 0
  call plt memset
  pop rax
  ret
