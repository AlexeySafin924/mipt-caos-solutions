#include <asm/unistd_32.h>

    .intel_syntax noprefix
    .text
    .global _start

_start:
	//get(in edi) pointer to our heap
    mov esi, 0
    mov eax, __NR_brk
    mov ebx, 0
    int 0x80
    mov edi, eax
	push edi
read_loop:
	//if we still have place, continue to read
    cmp esi, 0
    jg read
	//else increase buffer
    mov esi, 4096
    add edi, esi
    mov eax, __NR_brk
    mov ebx, edi
    int 0x80
    sub edi, esi
read:
	//reading, as much as possible
    mov eax, __NR_read
    mov ebx, 0
    mov ecx, edi
    mov edx, esi
    int 0x80
    //if we readed nothing go to write
    cmp eax, 0
    je write
	//else, continue to read, and change place to store
    sub esi, eax
    add edi, eax
    jmp read_loop
write:
	//needed end of line
    mov al, '\n'
    mov [edi], al
write_loop:
	//we have to start loocup from last adding point
    mov esi, edi    
loop_iter:
	//if we get to the end of edi we exit
    cmp edi, [esp]
    je end
    dec edi
	//if we found a line we write it
    mov al, '\n'
    cmp [edi], al
    je write_line
    jmp loop_iter
write_line:
    mov eax, __NR_write
    mov ebx, 1
    mov ecx, edi
    inc ecx
    mov edx, esi
    sub edx, edi
    int 0x80
    jmp write_loop
end:
	//write last line(from begin to first \n)
    mov eax, __NR_write
    mov ebx, 1
    mov ecx, edi
    mov edx, esi
    sub edx, edi
    inc edx
    int 0x80
	pop edi
    mov eax, __NR_exit
    mov ebx, 0
    int 0x80