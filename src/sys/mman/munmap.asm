include '../../sys64.inc'

format ELF64

section '.text' executable
public munmap
munmap:
  syscall64 sys64_munmap
  ret
