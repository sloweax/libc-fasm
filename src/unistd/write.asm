include '../sys64.inc'

format ELF64

section '.text' executable
public write
write:
  syscall64 sys64_write
  ret
