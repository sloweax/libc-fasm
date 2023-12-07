include '../sys64.inc'

format ELF64

section '.text' executable
public open
open:
  syscall64 sys64_open
  ret
