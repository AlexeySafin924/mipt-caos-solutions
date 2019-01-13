	.intel_syntax noprefix
	.global my_sin
	.text
my_sin:
	push ebp
	mov ebp, esp
	push eax
	movsd xmm0, [ebp + 8]
	subsd xmm0, xmm0
	movsd xmm1, [ebp + 8]
	movsd xmm2, [ebp + 8]
	mov eax, 1
	subsd xmm5, xmm5
	mov ebx, 100000
	cvtsi2sd xmm6, ebx
	divsd xmm5, xmm6
	mulsd xmm5, xmm5
	mulsd xmm5, xmm5
	mulsd xmm5, xmm5
	mulsd xmm5, xmm5
loop:
	subsd xmm0, xmm1
	mulsd xmm0, xmm0
	comisd xmm0, xmm5
	jbe exit
	movsd xmm0, xmm1
	movsd xmm3, [ebp + 8]
	mulsd xmm2, xmm3
	mulsd xmm2, xmm3
	add eax, 1
	cvtsi2sd xmm4, eax
	divsd xmm2, xmm4
	add eax, 1
	cvtsi2sd xmm4, eax
	divsd xmm2, xmm4
	mov ebx, -1
	cvtsi2sd xmm4, ebx
	mulsd xmm2, xmm4
	addsd xmm1, xmm2
	jmp loop
exit:
	movsd [ebp + 8], xmm1
	fld qword ptr [ebp + 8]
	pop eax
	pop ebp
	ret
