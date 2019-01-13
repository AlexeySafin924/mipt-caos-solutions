         .text
         .global calculate
calculate:
ldrsb    r3, [r0]
ldrsh    r2, [r0, #2]
add      r3, r3, r2
ldr      r1, [r0, #4]
adds     r3, r3, r1
mov      r2, #0
adc      r2, #0
mov      r0, r3
mov      r1, r2
bx       lr
