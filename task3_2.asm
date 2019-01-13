.text
.global solve

solve:
	push {r4, r5, r6}
	mov r4, #0
loop:
	mov r5, r3
	mov r6, r2
	mul r6, r4, r6
	add r5, r6, r5
	mov r6, r1
	mul r6, r4, r6
	mul r6, r4, r6
	add r5, r6, r5
	mov r6, r0
	mul r6, r4, r6
	mul r6, r4, r6
	mul r6, r4, r6
	add r5, r6, r5
	cmp r5, #0
	beq exit
	add r4, r4, #1
	b loop
exit:	
	mov r0, r4
	pop {r4, r5, r6}
	bx lr