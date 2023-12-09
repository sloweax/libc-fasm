format ELF64

section '.text' executable
public isascii
isascii:
  xor eax, eax
  cmp edi, 127
  setbe al
  ret
