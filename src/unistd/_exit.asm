include '../sys64.inc'

format ELF64

section '.text' executable
extrn _Exit
public _exit
_exit:
  call plt _Exit
