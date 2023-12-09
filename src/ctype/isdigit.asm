include 'macros.inc'

format ELF64

section '.text' executable
public isdigit
isdigit:
  isbetween '0', '9'
  ret

