include '../sys64.inc'

format ELF64

section '.text' executable
public getpid
getpid:
  syscall64 sys64_getpid
  ret
