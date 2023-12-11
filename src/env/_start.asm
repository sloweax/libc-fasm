format ELF64

section '.text' executable
extrn _exit
extrn main
public _start
_start:
  mov edi, dword [rsp]     ; argc
  lea rsi, qword [rsp + 8] ; argv
  lea rdx, [edi*8+16]
  add rdx, rsp             ; envp
  mov [environ], rdx
  mov rax, [rsi]
  mov [__progname], rax

  call plt main

  mov edi, eax
  call plt _exit
  
section '.bss' writeable
public environ
environ rq 1

public __progname
__progname rq 1
