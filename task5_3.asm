	.text
	.global main
main:
	push {r4, r5, r7, lr}
	mov r0, #0
	mov r1, #100
	bl realloc
	mov r7, #100
	mov r4, r0
	mov r5, #0
loop:
	ldr r0, =stdin
	ldr r0, [r0]
	bl fgetc
	cmp r0, #-1
	beq reverse_order
	cmp r0, #32
	blo loop
	strb r0, [r4, r5]
	add r5, r5, #1
	cmp r5, r7
	blo loop
	mov r0, #2
	mul r1, r0, r7
	mov r7, r1
	mov r0, r4
	bl realloc
	mov r4, r0	
	b loop
reverse_order:
	cmp r5, #0
	beq end
	sub r5, r5, #1
	ldr r1, =stdout
	ldr r1, [r1]
	ldrb r0, [r4, r5]
	bl fputc
	b reverse_order
end:
	mov r0, r4
	bl free
	pop {r4, r5, r7, lr}
	bx lr