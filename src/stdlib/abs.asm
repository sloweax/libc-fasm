format ELF64

section '.text' executable
public abs
abs:
  mov eax, edi
  neg eax
  cmovl eax, edi
  ret
