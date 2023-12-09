macro isbetween a*, b*, dchar=edi, dout=eax, bout=al {
  xor dout, dout
  sub dchar, a
  cmp dchar, b - a
  setbe bout
}

macro isbetween2 a*, b*, x*, y* {
  mov esi, edi
  isbetween a, b, edi, eax, al
  isbetween x, y, esi, edx, dl
  or al, dl
}

macro isbetween3 a*, b*, x*, y*, i*, j* {
  mov esi, edi
  isbetween a, b, edi, eax, al
  mov edi, esi
  isbetween x, y, esi, edx, dl
  or al, dl
  isbetween i, j, edi, ecx, cl
  or al, cl
}

macro tox proc*, op*, val* {
  push rbx
  mov ebx, edi
  call proc
  test eax, eax
  mov eax, ebx
  jz .return
  op eax, val
  .return:
    pop rbx
    ret
}
