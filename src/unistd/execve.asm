include '../sys64.inc'

format ELF64

section '.text' executable
public execve
execve:
  syscall64 sys64_execve
  ret
