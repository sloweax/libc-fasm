format ELF64

section '.text' executable
public memset
memset:

  total   equ rdx
  current equ rbx
  left    equ rcx
  tmp64   equ rax
  tmp32   equ eax
  tmp16   equ ax
  tmp8    equ al
  aux64   equ r10

  push current
  push left
  push aux64

  movsx aux64, sil
  mov tmp64, 0x0101010101010101
  imul tmp64, aux64

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
    mov byte [rdi + current], tmp8
    inc current
    jmp .loop
  .2:
    mov word [rdi + current], tmp16
    add current, 2
    jmp .loop
  .4:
    mov dword [rdi + current], tmp32
    add current, 4
    jmp .loop
  .8:
    mov qword [rdi + current], tmp64
    add current, 8
    jmp .loop

  .return:
    pop aux64
    pop left
    pop current
    mov rax, rdi
    ret
