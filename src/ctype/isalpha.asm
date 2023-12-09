include 'macros.inc'

format ELF64

section '.text' executable
public isalpha
extrn islower
extrn isupper
isalpha:
  isboth <plt islower>, <plt isupper>
  ret

