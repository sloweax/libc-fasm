format ELF64

section '.text' executable
public bcmp
extrn memcmp
bcmp:
  xor rax, rax
  cmp rdi, rsi
  je .return
  call plt memcmp
  .return:
    ret
