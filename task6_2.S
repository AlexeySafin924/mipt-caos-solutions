	.intel_syntax noprefix
	.text
	.globl	mergesort
//At first we push registers and add memory to store variables
mergesort:
	push	ebp
	mov	ebp, esp
	push	ebx
	sub	esp, 52
	mov	eax, [ebp+16]
	mov	[ebp-44], eax
	mov	eax, [ebp+20]
	mov	[ebp-48], eax
	mov	eax, esp
	mov	ebx, eax
	mov	eax,  [ebp+12]
	sub	eax,  [ebp+8]
	//now if array is 1 element size we just put it into output
	cmp	eax, 1
	jg	not_one_element
	mov	eax, [ebp+8]
	lea	edx, [0+eax*4]
	mov	eax, [ebp-48]
	add	edx, eax
	mov	eax, [ebp+8]
	lea	ecx, [0+eax*4]
	mov	eax, [ebp-44]
	add	eax, ecx
	mov	eax,  [eax]
	mov	 [edx], eax
	mov	eax, 0
	jmp	exit
not_one_element:
	//caluclate m = from + (to - from) / 2 (cetner to sort)
	mov	eax, [ebp+12]
	sub	eax, [ebp+8]
	mov	edx, eax
	shr	edx, 31
	add	eax, edx
	sar	eax
	mov	edx, eax
	mov	eax, [ebp+8]
	add	eax, edx
	mov	 [ebp-24], eax
	//call mergesort two times for left and right half of array
	push	[ebp-48]
	push	 [ebp-44]
	push	 [ebp-24]
	push	 [ebp+8]
	call	mergesort
	add	esp, 16
	push	 [ebp-48]
	push	 [ebp-44]
	push	 [ebp+12]
	push	 [ebp-24]
	call	mergesort
	add	esp, 16
	//now we allocate from - to place on stack
	mov	eax, [ebp+12]
	sub	eax, [ebp+8]
	lea	edx, [eax-1]
	mov	 [ebp-20], edx
	sal	eax, 2
	lea	edx, [eax+3]
	mov	eax, 16
	sub	eax, 1
	add	eax, edx
	mov	ecx, 16
	mov	edx, 0
	div	ecx
	imul	eax, eax, 16
	sub	esp, eax
	mov	eax, esp
	add	eax, 3
	shr	eax, 2
	sal	eax, 2
	mov	[ebp-16], eax
	//add 3 variables for cycle through array 
	mov	DWORD PTR [ebp-40], 0
	mov	eax, [ebp+8]
	mov	 [ebp-36], eax
	mov	eax, [ebp-24]
	mov	 [ebp-32], eax
	jmp	first_merge_cycle
in_while_comparator:
	mov	eax, [ebp-36]
	lea	edx, [0+eax*4]
	mov	eax,  [ebp-48]
	add	eax, edx
	mov	edx,  [eax]
	mov	eax,  [ebp-32]
	lea	ecx, [0+eax*4]
	mov	eax,  [ebp-48]
	add	eax, ecx
	mov	eax,  [eax]
	cmp	edx, eax
	jge	put_in_tmp_elem_from_one_half
	mov	eax,  [ebp-36]
	lea	edx, [0+eax*4]
	mov	eax,  [ebp-48]
	add	eax, edx
	mov	ecx,  [eax]
	mov	eax,  [ebp-16]
	mov	edx,  [ebp-40]
	mov	 [eax+edx*4], ecx
	add	DWORD PTR [ebp-36], 1
	jmp	put_in_tmp_elem_from_other_half
put_in_tmp_elem_from_one_half:
	mov	eax, [ebp-32]
	lea	edx, [0+eax*4]
	mov	eax, [ebp-48]
	add	eax, edx
	mov	ecx,  [eax]
	mov	eax,  [ebp-16]
	mov	edx,  [ebp-40]
	mov	 [eax+edx*4], ecx
	add	DWORD PTR [ebp-32], 1
put_in_tmp_elem_from_other_half:
	add	DWORD PTR [ebp-40], 1
first_merge_cycle:
	//we should go through 2 arrays while them both in range
	mov	eax, [ebp-36]
	cmp	eax, [ebp-24]
	//if them not in range we go to adding rest of arrays to end of allocated
	jge	add_to_tmp_rest_of_first_half
	mov	eax, [ebp-32]
	cmp	eax,  [ebp+12]
	jl	in_while_comparator
	jmp	add_to_tmp_rest_of_first_half
first_half_adding:
	//adding elements from first half to end of array
	mov	eax, [ebp-36]
	lea	edx, [0+eax*4]
	mov	eax, [ebp-48]
	add	eax, edx
	mov	ecx, [eax]
	mov	eax,  [ebp-16]
	mov	edx,  [ebp-40]
	mov	 [eax+edx*4], ecx
	add	DWORD PTR [ebp-40], 1
	add	DWORD PTR [ebp-36], 1
add_to_tmp_rest_of_first_half:
	//again, add elements while we could
	mov	eax,  [ebp-36]
	cmp	eax,  [ebp-24]
	jl	first_half_adding
	jmp	add_to_tmp_rest_of_second_half
adding_second_half:
	//adding elements from end of second half of array
	mov	eax, [ebp-32]
	lea	edx, [0+eax*4]
	mov	eax, [ebp-48]
	add	eax, edx
	mov	ecx, [eax]
	mov	eax, [ebp-16]
	mov	edx,  [ebp-40]
	mov 	[eax+edx*4], ecx
	add	DWORD PTR [ebp-40], 1
	add	DWORD PTR [ebp-32], 1
add_to_tmp_rest_of_second_half:
	//add elements from second half while we could
	mov	eax, [ebp-32]
	cmp	eax, [ebp+12]
	jl	adding_second_half
	mov	eax, [ebp+8]
	mov	[ebp-28], eax
	jmp	copy_tmp_to_out
tmp_to_out_copy:
	//copy our tmp array to out array
	mov	eax, [ebp-28]
	lea	edx, [0+eax*4]
	mov	eax, [ebp-48]
	lea	ecx, [edx+eax]
	mov	eax, [ebp-28]
	sub	eax,  [ebp+8]
	mov	edx, eax
	mov	eax, [ebp-16]
	mov	eax, [eax+edx*4]
	mov 	[ecx], eax
	add	DWORD PTR [ebp-28], 1
copy_tmp_to_out:
	//copy while we could
	mov	eax, [ebp-28]
	cmp	eax,  [ebp+12]
	jl	tmp_to_out_copy
	mov	eax, 1
exit:
	//just return
	leave
	ret
