include 'file.inc'

format ELF64

section '.text' executable
public fclose
extrn __ffree
extrn fileno
extrn fflush_unlocked
extrn close
fclose:
  push rbx
  mov rbx, rdi

  call plt fflush_unlocked
  cmp eax, EOF
  je .return

  mov rdi, rbx
  call plt fileno
  mov edi, eax
  call plt close
  cmp eax, -1
  je .return
  
  mov rdi, rbx
  call __ffree

  .return:
    pop rbx
    ret
