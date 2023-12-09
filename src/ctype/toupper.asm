include 'macros.inc'

format ELF64

section '.text' executable
extrn islower
public toupper
toupper:
  tox <plt islower>, sub, 'a' - 'A'
