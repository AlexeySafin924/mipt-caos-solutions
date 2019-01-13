	.global summ
	.intel_syntax noprefix
	.text
summ:
	push ebp
	mov ebp, esp
	mov ecx, [ebp + 8]
	push ebx
.Loop:
	mov ebx, ecx
	dec ebx
	mov edx, [ebp + 12]
	mov eax, [edx + 4 * ebx]
	mov edx, [ebp + 16]
	add eax, [edx + 4 * ebx]
	mov edx, [ebp + 20]
	mov [edx + 4 * ebx], eax
	loop .Loop
	pop ebx
	pop ebp
	ret
