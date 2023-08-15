.data

.text

.global main

main:

mov $1, %eax
xorl %ebx, %ebx
int 0x80
