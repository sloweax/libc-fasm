format ELF64

section '.text' executable
public llabs
llabs:
  mov rax, rdi
  neg rax
  cmovl rax, rdi
  ret
