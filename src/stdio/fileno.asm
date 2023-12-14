include 'file.inc'

format ELF64

section '.text' executable
public fileno
fileno:
  mov eax, dword [rdi + file.fd]
  ret
