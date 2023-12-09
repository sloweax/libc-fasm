format ELF64

section '.text' executable
public isascii
isascii:
  test edi, edi
  jz .zero
  xor eax, eax
  cmp edi, 127
  cmovle eax, edi
  ret
  .zero:
    inc eax
    ret
