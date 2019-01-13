	.text
	.global classify

classify:
			push {r5, r6, r7, r8}
			
			mov		r7, #0x7F000000
			orr		r7, r7, #0x00F00000
			mov		r8, #0x000FF000
			orr		r8, r8, #0x00000FF0
			orr		r8, r8, #0x0000000F
			
			ldr 		r1, [r0]
			ldr 		r2, [r0, #4]
			
			
			and		r3, r1, #0x80000000
			and		r4, r1, r7
			and		r5, r1, r8
			and		r6, r1, #0x00080000
			cmp		r4, #0
			beq		zeroExp
			cmp		r4, r7
			beq		onesExp
			cmp		r3, #0
			beq		plusReg
			mov		r0, #0x11
			b endOfProg
			
			
plusReg:
			mov		r0, #0x10
			b endOfProg
			
zeroExp:
			cmp		r2, #0
			bne		denormal
			cmp		r5, #0
			bne		denormal
			cmp		r3, #0
			beq		plusZero
			mov		r0, #0x01
			b endOfProg
			
plusZero:
			mov		r0, #0x00
			b endOfProg
			
denormal:
			cmp		r3, #0
			beq		plusDenormal
			mov		r0, #0x21
			b endOfProg
			
plusDenormal:
			mov		r0, #0x20
			b endOfProg
			
onesExp:
			cmp		r2, #0
			bne		nan
			cmp		r5, #0
			bne		nan
			cmp		r3, #0
			beq		plusInf
			mov		r0, #0xF1
			b endOfProg
			
plusInf:
			mov		r0, #0xF0
			end
			
nan:
			cmp		r6, #0
			beq		sigNaN
			mov		r0, #0x31
			b endOfProg
			
sigNaN:
			mov		r0, #0x30
			b endOfProg

endOfProg:
	pop {r5,r6,r7,r8}
	bx ls