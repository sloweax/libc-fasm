include 'file.inc'

format ELF64

section '.text' executable
extrn fflush_unlocked
extrn memcpy
public fwrite_unlocked
fwrite_unlocked:
  nmemb equ rbx
  size  equ r12
  total equ r13

  push total
  push nmemb
  push size

  xor nmemb, nmemb
  mov size, rsi
  test size, size
  cmovnz nmemb, rdx

  mov rsi, nmemb
  mov rax, size
  mul rsi

  mov total, rax

  mov rsi, total
  mov rdx, rcx
  call fwritex

  cmp total, rax
  cmove rax, nmemb
  je .return

  div size

  .return:
    pop size
    pop nmemb
    pop total
    ret

; size_t fwritex(void *p, size_t, FILE*);
fwritex:
  src   equ r12
  size  equ r13
  total equ r14
  file  equ rbx

  push total
  push src
  push size
  push file

  xor total, total

  mov src, rdi
  mov size, rsi
  mov file, rdx

  .loop:
    test size, size
    jz .return

    cmp qword [file + file.pos], file.bufsize
    jne .memcpy

    mov rdi, file
    call fflush_unlocked
    cmp eax, EOF
    je .return

    .memcpy:
      mov rdx, file.bufsize
      sub rdx, qword [file + file.pos]
      cmp size, rdx
      cmovb rdx, size
      add total, rdx
      sub size, rdx
      mov rdi, qword [file + file.pos]
      add qword [file + file.pos], rdx
      lea rdi, [file + file.buf + rdi]
      mov rsi, src
      add src, rdx
      call plt memcpy
      jmp .loop


  .return:
    mov rax, total
    pop file
    pop size
    pop src
    pop total
    ret
