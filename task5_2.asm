	.text
	.global main
main:
	push {lr}
loop:
	ldr r0, .Lstdin
	ldr r0, [r0]
	bl fgetc
	cmp r0, #-1
	beq exit
	cmp r0, #48
	blo loop
	cmp r0, #57
	bhi loop
	ldr r1, .Lstdout
	ldr r1, [r1]
	bl fputc
	b loop
exit:
	pop {lr}
	bx lr
.Lstdin:
	.word stdin
.Lstdout:
	.word stdout