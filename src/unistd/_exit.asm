format ELF64

section '.text' executable
extrn _Exit
public _exit
_exit:
  call plt _Exit
