format ELF64

section '.text' executable
public labs
labs:
  mov rax, rdi
  neg rax
  cmovl rax, rdi
  ret
