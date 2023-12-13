include 'file.inc'

format ELF64

section '.text' executable
public fflush_unlocked
extrn write
extrn memcpy
fflush_unlocked:
  file equ rbx
  towrite equ r12

  push file
  push towrite

  xor rax, rax

  mov file, rdi
  mov rdx, qword [file + file.pos]
  test rdx, rdx
  jz .return

  mov towrite, rdx
  mov edi, dword [file + file.fd]
  lea rsi, [file + file.buf]
  call write

  cmp rax, towrite
  je .zero_pos

  lea rdi, [file + file.buf]
  lea rsi, [file + file.buf + rax]
  mov rdx, towrite
  sub rdx, rax
  call memcpy

  mov qword [file + file.pos], rdx
  mov rax, EOF
  jmp .return

  .zero_pos:
    mov qword [file + file.pos], 0
    xor rax, rax
    jmp .return

  .return:
    pop towrite
    pop file
    ret
