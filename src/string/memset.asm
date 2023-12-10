format ELF64

section '.text' executable
public memset
memset:

  total   equ rdx
  current equ r11
  left    equ rcx
  qtmp    equ rax
  dtmp    equ eax
  wtmp    equ ax
  btmp    equ al
  aux64   equ r10

  movsx aux64, sil
  mov qtmp, 0x0101010101010101
  imul qtmp, aux64
  movq xmm0, qtmp
  punpcklqdq xmm0, xmm0

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
    mov byte [rdi + current], btmp
    inc current
    jmp .loop
  .4: 
    mov dword [rdi + current], dtmp
     add current, 4
    jmp .loop
  .8:
    mov qword [rdi + current], qtmp
    add current, 8
    jmp .loop
  .32:
    movdqu dqword [current + rdi], xmm0
    movdqu dqword [current + rdi + 16], xmm0
    add current, 32
    jmp .loop
  .64:
    movdqu dqword [current + rdi], xmm0
    movdqu dqword [current + rdi + 16], xmm0
    movdqu dqword [current + rdi + 32], xmm0
    movdqu dqword [current + rdi + 48], xmm0
    add current, 64
    jmp .loop

  .return:
    mov rax, rdi
    ret
