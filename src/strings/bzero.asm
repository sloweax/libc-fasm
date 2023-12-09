format ELF64

section '.text' executable
public bzero
extrn memset
bzero:
  mov rdx, rsi
  xor rsi, rsi
  call plt memset
  ret
