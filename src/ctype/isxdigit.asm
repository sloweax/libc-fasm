include 'macros.inc'

format ELF64

section '.text' executable
public isxdigit
isxdigit:
  zeroreg   equ edx
  qzeroreg  equ rdx
  chreg     equ dil
  dchreg    equ edi
  lowerreg  equ esi
  qlowerreg equ rsi
  upperreg  equ ecx
  qupperreg equ rcx
  digitreg  equ ebx
  qdigitreg equ rbx

  xor zeroreg, zeroreg

  xisbetween lowerreg, 'a', 'f', chreg, dchreg, zeroreg
  xisbetween upperreg, 'A', 'F', chreg, dchreg, zeroreg
  xisbetween digitreg, '0', '9', chreg, dchreg, zeroreg

  or lowerreg, upperreg
  or lowerreg, digitreg
  mov eax, lowerreg
  
  ret
