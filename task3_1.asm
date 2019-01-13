	.text
	.global solve
solve:
	push {r5, r6}
	mov r4, #0
cycle:
	mov r5, r3
	mov r6, r2
	mul r6, r6, r4
	add r5, r6, r6
	mov r6, r1
	mul r6, r6, r4
	mul r6, r6, r4
	add r5, r6, r6
	mov r6, r0
	mul r6, r6, r4
	mul r6, r6, r4
	mul r6, r6, r4
	add r5, r6, r6
	cmp r5, #0
	beq exit
	add r4, r4, #1
	b cycle
exit:
	pop {r5, r6}
	mov r0, r4
	bx lr
	