macro isbetween a*, b* {
  xor eax, eax
  cmp dil, a
  cmovge eax, edi
  cmp dil, b
  jg .null
  ret
  .null:
    xor eax, eax
    ret
}

macro isboth a*, b* {
  push rsi
  call a
  mov esi, eax
  call b
  or eax, esi
  pop rsi
  ret
}
