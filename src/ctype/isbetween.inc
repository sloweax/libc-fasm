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
