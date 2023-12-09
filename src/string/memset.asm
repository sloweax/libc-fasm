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
    mov byte [rdi + current], btmp
    inc current
    jmp .loop
  .2:
    mov word [rdi + current], wtmp 
    add current, 2
    jmp .loop
  .4: 
    mov dword [rdi + current], dtmp
     add current, 4
    jmp .loop
  .8:
    mov qword [rdi + current], qtmp
    add current, 8
    jmp .loop

  .return:
    mov rax, rdi
    ret
