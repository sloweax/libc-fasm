include 'macros.inc'

format ELF64

section '.text' executable
public isalnum
extrn isalpha
extrn isdigit
isalnum:
  isbetween3 'a', 'z', 'A', 'Z', '0', '9'
  ret

