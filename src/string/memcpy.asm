format ELF64

section '.text' executable
public memcpy
memcpy:

  total   equ rdx
  current equ rbx
  left    equ rcx
  tmp64   equ rax
  tmp32   equ eax
  tmp16   equ ax
  tmp8    equ al

  push current
  push left
  push tmp64

  xor current, current

  .loop:
    cmp current, total
    je .return
    mov left, total
    sub left, current
    cmp left, 8
    jge .8
    cmp left, 4
    jge .4
    cmp left, 2
    jge .2
  .1:
    mov tmp8, byte [current + rsi]
    mov byte [rdi + current], tmp8
    inc current
    jmp .loop
  .2:
    mov tmp16, word [current + rsi]
    mov word [rdi + current], tmp16
    add current, 2
    jmp .loop
  .4:
    mov tmp32, dword [current + rsi]
    mov dword [rdi + current], tmp32
    add current, 4
    jmp .loop
  .8:
    mov tmp64, qword [current + rsi]
    mov qword [rdi + current], tmp64
    add current, 8
    jmp .loop

  .return:
    pop tmp64
    pop left
    pop current
    ret

