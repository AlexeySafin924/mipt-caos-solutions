#include <asm/unistd_32.h>
	.intel_syntax noprefix
	.text
	.global _start
_start:
	mov eax, __NR_read
	mov ebx, 0
	lea ecx, [esp]
	mov edx, 100
	int 0x80
write:
	mov esi, eax
	mov eax, __NR_write
	mov ebx, 1
	lea ecx, [esp]
	mov edx, esi
	int 0x80

	cmp esi, 100
	je _start
return:
	mov eax, __NR_exit
	mov ebx, 1
	int 0x80