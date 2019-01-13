	.global summ
	.intel_syntax noprefix
	.text
summ:
	push ebx
	mov ecx, N
.Loop:
	mov ebx, ecx
	dec ebx
	mov edx, A
	mov eax, [edx + 4 * ebx]
	mov edx, B
	add eax, [edx + 4 * ebx]
	mov edx, R
	mov [edx + 4*ebx], eax
	loop .Loop
	pop ebx
	ret

	.global everyday795
everyday795:
	push ebp
	mov ebp, esp
	push ebx
	sub esp, 12
	mov eax, esp
	add eax, 8
	mov [esp + 4], eax
	mov ecx, offset scanf_format_string
	mov [esp+0], ecx
	call scanf
	mov ebx, [esp + 8]
	imul ebx, [ebp + 8]
	add ebx, [ebp + 12]
	mov ecx, offset printf_format_string
	mov [esp + 0], ecx
	mov [esp + 4], ebx
	call printf
	add esp, 12
	pop ebx
	pop ebp
	ret
scanf_format_string:
	.string "%d"
printf_format_string:
	.string "%d\n"