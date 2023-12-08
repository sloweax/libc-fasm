format ELF64

section '.text' executable
public bzero
extrn memset
bzero:
  push rax
  mov rdx, rsi
  xor rsi, rsi
  call plt memset
  pop rax
  ret
