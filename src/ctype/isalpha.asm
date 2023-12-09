include 'macros.inc'

format ELF64

section '.text' executable
public isalpha
extrn islower
extrn isupper
isalpha:
  isbetween2 'a', 'z', 'A', 'Z'
  ret

