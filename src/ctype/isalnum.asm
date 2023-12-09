include 'macros.inc'

format ELF64

section '.text' executable
public isalnum
extrn isalpha
extrn isdigit
isalnum:
  isboth <plt isalpha>, <plt isdigit>

