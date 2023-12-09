format ELF64

section '.text' executable
public memcpy
memcpy:

  total   equ rdx
  current equ r10
  left    equ rcx
  qtmp    equ rax
  dtmp    equ eax
  wtmp    equ ax
  btmp    equ al

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
    mov btmp, byte [current + rsi]
    mov byte [rdi + current], btmp
    inc current
    jmp .loop
  .2:
    mov wtmp , word [current + rsi]
    mov word [rdi + current], wtmp 
    add current, 2
    jmp .loop
  .4:
    mov dtmp , dword [current + rsi]
    mov dword [rdi + current], dtmp 
    add current, 4
    jmp .loop
  .8:
    mov qtmp, qword [current + rsi]
    mov qword [rdi + current], qtmp
    add current, 8
    jmp .loop

  .return:
    mov rax, rdi
    ret

