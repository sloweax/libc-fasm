include 'macros.inc'

format ELF64

section '.text' executable
public isxdigit
isxdigit:
  zeroreg   equ edx
  chreg     equ dil
  dchreg    equ edi
  lowerreg  equ esi
  upperreg  equ ecx
  digitreg  equ eax

  xor zeroreg, zeroreg

  xisbetween lowerreg, 'a', 'f', chreg, dchreg, zeroreg
  xisbetween upperreg, 'A', 'F', chreg, dchreg, zeroreg
  xisbetween digitreg, '0', '9', chreg, dchreg, zeroreg

  or lowerreg, upperreg
  or digitreg, lowerreg
  
  ret
