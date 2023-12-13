include '../sys/mman.inc'

file.fd equ 0
file.pos equ 4
file.buf equ 12
file.bufsize equ PAGE_SIZE - file.buf
file.sizeof equ PAGE_SIZE

O_RDONLY equ 00o
O_WRONLY equ 01o
O_RDWR equ 02o
O_CREAT equ 100o
O_TRUNC equ 1000o
O_APPEND equ 2000o

EOF equ -1
