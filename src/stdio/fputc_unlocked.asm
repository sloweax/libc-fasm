include 'file.inc'

format ELF64

section '.text' executable
extrn fflush_unlocked
public fputc_unlocked
fputc_unlocked:
  file equ rbx

  push file

  mov file, rsi

  mov rsi, qword [file + file.pos]
  cmp rsi, file.bufsize
  jb .add_char

  push rdi
  mov rdi, file
  call plt fflush_unlocked
  pop rdi
  cmp eax, EOF
  je .return

  mov rsi, file
  call fputc_unlocked
  jmp .return

  .add_char:
    mov byte [file + file.buf + rsi], dil
    inc rsi
    mov qword [file + file.pos], rsi
    movzx eax, dil
    jmp .return

  .return:
    pop file
    ret
