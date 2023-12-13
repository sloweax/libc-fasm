include '../stdio/file.inc'

format ELF64

section '.text' executable
extrn _exit
extrn main
extrn __finit
extrn fflush_unlocked
public _start
_start:
  mov rdi, __stdin
  mov esi, 0
  call plt __finit

  mov rdi, __stdout
  mov esi, 1
  call plt __finit

  mov rdi, __stderr
  mov esi, 2
  call plt __finit

  mov edi, dword [rsp]     ; argc
  lea rsi, qword [rsp + 8] ; argv
  lea rdx, [edi*8+16]
  add rdx, rsp             ; envp
  mov [environ], rdx
  mov rax, [rsi]
  mov [__progname], rax

  push rbx
  call plt main
  mov ebx, eax

  mov rdi, __stdout
  call plt fflush_unlocked

  mov rdi, __stderr
  call plt fflush_unlocked
  pop rbx

  mov edi, ebx
  call plt _exit
  
section '.bss' writeable
public environ
environ rq 1

public __progname
__progname rq 1

public __stdin
__stdin rb file.sizeof

public __stdout
__stdout rb file.sizeof

public __stderr
__stderr rb file.sizeof
