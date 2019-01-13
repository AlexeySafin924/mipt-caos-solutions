	.text
	.global sort_by_age
sort_by_age:
	push {r4, r5, r6, r7, r8}
	cmp r0, #1
	bls exit
	mov r3, r1
	mov r7, #0
	mov r2, #1
loop:
	ldrb r4, [r3, #4]
	ldrb r5, [r3, #52]
	cmp r4, r5
	bls continue
	mov r8, r3
	add r8, r8, #44
swap:
	ldr r4, [r8, #48]
	ldr r5, [r8]
	str r5, [r8, #48]
	str r4, [r8]
	cmp r8, r3
	beq continue
	sub r8, r8, #4
	b swap
continue:
	add r2, r2, #1
	cmp r0, r2
	bls next_test
	add r3, r3, #48
	b loop
next_test:
	cmp r0, r7
	bls exit
	add r7, r7, #1
	mov r3, r1
	mov r2, #1
	b loop
exit:
	pop {r4, r5, r6, r7, r8}
	bx lr