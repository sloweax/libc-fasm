macro pushaq {
  push rax
  push rbx
  push rcx
  push rdx
  push rbp
  push rdi
  push rsi
  push r8 
  push r9 
  push r10
  push r11
  push r12
  push r13
  push r14
  push r15
}

macro popaq {
  push r15
  push r14
  push r13
  push r12
  push r11
  push r10
  push r9 
  push r8 
  push rsi
  push rdi
  push rbp
  push rdx
  push rcx
  push rbx
  push rax
}
