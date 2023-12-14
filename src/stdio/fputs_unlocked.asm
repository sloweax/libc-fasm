include  'file.inc'

format ELF64

section '.text' executable
extrn strlen
extrn fwrite_unlocked
extrn fputc_unlocked
public fputs_unlocked
fputs_unlocked:
  str equ rbx
  file equ r12
  len equ r13

  push file
  push str
  push len

  mov str, rdi
  mov file, rsi

  mov rdi, str
  call plt strlen
  mov len, rax

  mov rdi, str
  mov rsi, 1
  mov rdx, len
  mov rcx, file
  call plt fwrite_unlocked
  cmp rax, len
  jne .eof

  .return:
    pop len
    pop str
    pop file
    ret
  .eof:
    mov rax, EOF
    jmp .return
