include '../sys64.inc'

format ELF64

section '.text' executable
public read
read:
  syscall64 sys64_read
  ret
