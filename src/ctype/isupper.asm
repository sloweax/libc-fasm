include 'macros.inc'

format ELF64

section '.text' executable
public isupper
isupper:
  isbetween 'A', 'Z'
  ret

