include '../../sys64.inc'

format ELF64

section '.text' executable
public mmap
mmap:
  mov r10, rcx
  syscall64 sys64_mmap
  ret
