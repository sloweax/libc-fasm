format ELF64

section '.text' executable
public isdigit
isdigit:
  xor eax, eax
  cmp dil, '0'
  cmovge eax, edi
  cmp dil, '9'
  jg .null
  ret
  .null:
    xor eax, eax
    ret

