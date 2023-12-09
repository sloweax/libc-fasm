macro xisbetween dreg*, a*, b*, bchreg*, dchreg*, dzeroreg* {
  xor dreg, dreg
  cmp bchreg, a
  cmovge dreg, dchreg
  cmp bchreg, b
  cmovg dreg, dzeroreg
}

macro isbetween a*, b* {
  xor esi, esi
  xisbetween eax, a, b, dil, edi, esi
}

macro isboth a*, b* {
  push rbx
  call a
  mov ebx, eax
  call b
  or eax, ebx
  pop rbx
}
