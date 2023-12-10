include '../sys64.inc'

format ELF64

section '.text' executable
public close
close:
  syscall64 sys64_close
  ret
