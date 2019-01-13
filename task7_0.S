.intel_syntax noprefix
	.text
	.global calc
calc:
	push ebp
	mov ebp, esp
	fld qword ptr [ebp + 16]
	fadd qword ptr [ebp + 8]
	fild dword ptr [ebp + 32]
	fadd qword ptr [ebp + 24]
	pop ebp
	fdivp st(1), st
	ret

	.global vector_sum
vector_sum:
	push ebp
	push esi
	push edi
	push ebx
	mov ebp, esp
	mov ecx, [ebp + 20]
	mov esi, [ebp + 24]
	mov edi, [ebp + 28]
	mov ebx, [ebp + 32]
	mov eax, 0
Loop:
	movaps xmm0, [esi + eax * 4]
	movaps xmm1, [edi + eax * 4]
	addps xmm0, xmm1
	movaps [ebx + eax * 4], xmm0
	add eax, 4
	cmp eax, ecx
	jl Loop
	pop ebx
	pop edi
	pop esi
	pop ebp
	ret
