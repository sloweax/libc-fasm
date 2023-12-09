include 'macros.inc'

format ELF64

section '.text' executable
public isxdigit
isxdigit:
  isbetween3 'a', 'f', 'A', 'F', '0', '9'
  ret
