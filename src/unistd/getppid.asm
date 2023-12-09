include '../sys64.inc'

format ELF64

section '.text' executable
public getppid
getppid:
  syscall64 sys64_getppid
  ret
