	.intel_syntax noprefix
	.text
	.global dot_product
dot_product:
	mov eax, [esp + 8]
cycle:
	cmp eax, 4
	jb add_last
	sub eax, 4
	mov ebx, [esp + 8]
	movups xmm1, [ebx + 4  * eax]
	mov ebx, [esp + 12]
	movups xmm2, [ebx + 4 * eax]
	mulps xmm1, xmm2
	haddps xmm1, xmm1
	haddps xmm1, xmm1
	addss xmm0, xmm1
	jmp cycle
add_last:
	cmp eax, 0
	je exit
	sub eax, 1
	mov ebx, [esp + 8]
	movss xmm1, [ebx + 4 * eax]
	mov ebx, [esp + 12]
	movss xmm2, [ebx + 4 * eax]
	mulss xmm1, xmm2
	addss xmm0, xmm1
	jmp add_last
exit:
	sub esp, 4
	movss [esp], xmm0
	fld dword ptr [esp]
	add esp, 4
	ret
