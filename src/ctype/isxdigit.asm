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

  push qzeroreg
  push qlowerreg
  push qupperreg
  push qdigitreg
  xor zeroreg, zeroreg

  xisbetween lowerreg, 'a', 'f', chreg, dchreg, zeroreg
  xisbetween upperreg, 'A', 'F', chreg, dchreg, zeroreg
  xisbetween digitreg, '0', '9', chreg, dchreg, zeroreg

  xor eax, eax
  or lowerreg, upperreg
  or lowerreg, digitreg
  mov eax, lowerreg
  
  pop qdigitreg
  pop qupperreg
  pop qlowerreg
  pop qzeroreg
  ret
