include 'macros.inc'

format ELF64

section '.text' executable
public islower
islower:
  isbetween 'a', 'z'
  ret

