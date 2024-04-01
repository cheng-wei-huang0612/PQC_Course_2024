.global _start

_64_bit_unsigned_multiplication:
	// input: r0-r3, two 64-bit unsigned integer
	// output: r4-r7, a 128-bit unsigned integer
	umull r4, r5, r0, r2
	mov r6, #0
	mov r7, #0
	umaal r5, r7, r0, r3 // here r7 holds value for the third word value temporarily
	umaal r5, r6, r1, r2
	umaal r6, r7, r1, r3

_start:
	// 	give function input here
	// 	format: 
	// 		a = r1 + 2^32 + r0
	// 		b = r3 + 2^32 + r2
	// START of value assignment
	//	here my setup for this example is:
	// 	a = 0x1ffffffff = 8589934591
	// 	b = 0x2fffffffe = 12884901886
	mov r0, #4294967295
	mov r1, #1
	mov r2, #4294967294
	mov r3, #2
	// END of value assignment
	
	bl _64_bit_unsigned_multiplication
	// 	the correct answer (calculated using python) should be 0x5fffffff900000002 = 110680464412192538626