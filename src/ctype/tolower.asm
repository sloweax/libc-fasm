include 'macros.inc'

format ELF64

section '.text' executable
extrn isupper
public tolower
tolower:
  tox <plt isupper>, add, 'a' - 'A'
