include '../sys64.inc'

format ELF64

section '.text' executable 
public _Exit
_Exit:
  syscall64 sys64_exit_group 
  .loop:
    syscall64 sys64_exit 
    jmp .loop
