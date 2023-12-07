include '../sys64.inc'

format ELF64

section '.text' executable
extrn execve
extrn environ
public execv
execv:
  mov rdx, [plt environ]
  call plt execve
  ret
