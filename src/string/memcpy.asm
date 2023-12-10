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
    cmp left, 64
    jae .64
    cmp left, 32
    jae .32
    cmp left, 8
    jae .8
    cmp left, 4
    jae .4
  .1:
    mov btmp, byte [current + rsi]
    mov byte [rdi + current], btmp
    inc current
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
  .32:
    movdqu xmm0, dqword [current + rsi]
    movdqu xmm1, dqword [current + rsi + 16]
    movdqu dqword [current + rdi], xmm0
    movdqu dqword [current + rdi + 16], xmm1
    add current, 32
    jmp .loop
  .64:
    movdqu xmm0, dqword [current + rsi]
    movdqu xmm1, dqword [current + rsi + 16]
    movdqu xmm2, dqword [current + rsi + 32]
    movdqu xmm3, dqword [current + rsi + 48]
    movdqu dqword [current + rdi], xmm0
    movdqu dqword [current + rdi + 16], xmm1
    movdqu dqword [current + rdi + 32], xmm2
    movdqu dqword [current + rdi + 48], xmm3
    add current, 64
    jmp .loop

  .return:
    mov rax, rdi
    ret

