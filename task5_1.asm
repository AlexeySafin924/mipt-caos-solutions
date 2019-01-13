	.text
	.global main
main:
	push {r4, r5, r6, r7, r8, r9, lr}
	ldr r8, scanf_p
	ldr r9, printf_p
	sub sp, #8

	mov r0, r8
	mov r1, sp
	mov r2, sp
	add r2, r2, #4
	bl scanf
	ldr r4, [sp]
	ldr r5, [sp, #4]
	add r4, r4, r5
	mov r1, r4
	mov r0, r9
	bl printf
	add sp, sp, #8
	pop {r4, r5, r6, r7, r8, r9,lr}	
	bx lr
scanf_p:
	.word format_scanf
printf_p:
	.word format_printf	

	.data
format_printf:
	.ascii "%d\0"
format_scanf:
	.ascii "%d%d\0"