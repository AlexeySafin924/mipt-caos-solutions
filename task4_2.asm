	.text
	.global check_int
check_int:
	cmp r0, #0
	beq return_true
shift_loop:
	mov r1, #1
	and r1, r0, r1
	cmp r1, #1
	beq check
	lsr r0, #1
	b shift_loop
check:
	mov r1, #0x00FF0000
	orr r1, r1, #0x0000FF00
	orr r1, r1, #0x000000FF
	cmp r0, r1
	bls return_true
	mov r0, #0
	bx lr
return_true:
	mov r0, #1
	bx lr