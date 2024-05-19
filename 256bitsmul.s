.section .data
values:
    // from the least significant to the most
    .word 0x88888888, 0x77777777, 0x66666666, 0x12345678, 0x44444444, 0x33333333, 0x22222222, 0x11111111
    .word 0x99999999, 0xaaaaaaaa, 0xbbbbbbbb, 0xfedcba98, 0xdddddddd, 0xeeeeeeee, 0xffffffff, 0xffffffff

.align 4
result: .space 256

.section .text

.global _start

_start:
    ldr r0, =values        // Load the address of values into r0
    add r1, r0, #32        // Calculate the address of the second 128-bit value
    ldr r2, =result        // Load the address of result into r2
    bl _256mul             // Call the 256-bit multiplication function
    b _exit                // Exit the program

_256mul:
    // Save registers that will be used
    push {r0-r2, lr}

    // Call _128mul with the first pair of 128-bit values
    bl _128mul

    // Calculate the next addresses for 128-bit multiplication
    add r0, r0, #16
    add r2, r2, #128
    bl _128mul
    
    sub r0, r0, #16
    add r1, r1, #16
    add r2, r2, #64
    bl _128mul
    
    add r0, r0, #16
    sub r2, r2, #128
    bl _128mul

    // Restore registers
    pop {r0-r2, lr}

    // Post processing addition (similar to the 128-bit post-processing)
    add r3, r2, #64
    add r4, r3, #64
    add r5, r4, #64


    // r2, #16
    ldr r8, [r2, #16]
    ldr r9, [r4]
    ldr r10, [r5]
    
    adds r8, r8, r9
    adc r11, r11, #0
    adds r8, r8, r10
    adc r11,r11,#0
    
    str r8, [r2, #16] //carry in r11
	
	// r2, #20
    ldr r8, [r2, #20]
    ldr r9, [r4, #4]
    ldr r10, [r5, #4]
    
	adds r8, r8, r11 //add carry
	mov r11, #0 //clear carry
	adc r11, r11, #0
    adds r8, r8, r9
    adc r11, r11, #0
    adds r8, r8, r10
    adc r11,r11,#0
    
    str r8, [r2, #20]


    // r2, #24
    ldr r8, [r2, #24]
    ldr r9, [r4, #8]
    ldr r10, [r5, #8]
    
	adds r8, r8, r11 //add carry
	mov r11, #0 //clear carry
	adc r11, r11, #0
    adds r8, r8, r9
    adc r11, r11, #0
    adds r8, r8, r10
    adc r11,r11,#0
    
    str r8, [r2, #24]

    // r2, #28
    ldr r8, [r2, #28]
    ldr r9, [r4, #12]
    ldr r10, [r5, #12]
    
	adds r8, r8, r11 //add carry
	mov r11, #0 //clear carry
	adc r11, r11, #0
    adds r8, r8, r9
    adc r11, r11, #0
    adds r8, r8, r10
    adc r11,r11,#0
    
    str r8, [r2, #28]
	
	   
	 
	
	
	
	// r2, #32
    ldr r8, [r3]
    ldr r9, [r4, #16]
    ldr r10, [r5, #16]
    
	adds r8, r8, r11 //add carry
	mov r11, #0 //clear carry
	adc r11, r11, #0
    adds r8, r8, r9
    adc r11, r11, #0
    adds r8, r8, r10
    adc r11,r11,#0
    
    str r8, [r2, #32]





	// r2, #36
    ldr r8, [r3, #4]
    ldr r9, [r4, #20]
    ldr r10, [r5, #20]
    
	adds r8, r8, r11 //add carry
	mov r11, #0 //clear carry
	adc r11, r11, #0
    adds r8, r8, r9
    adc r11, r11, #0
    adds r8, r8, r10
    adc r11,r11,#0
    
    str r8, [r2, #36]




 	// r2, #40
    ldr r8, [r3, #8]
    ldr r9, [r4, #24]
    ldr r10, [r5, #24]
    
	adds r8, r8, r11 //add carry
	mov r11, #0 //clear carry
	adc r11, r11, #0
    adds r8, r8, r9
    adc r11, r11, #0
    adds r8, r8, r10
    adc r11,r11,#0
    
    str r8, [r2, #40]


	// r2, #44
    ldr r8, [r3, #12]
    ldr r9, [r4, #28]
    ldr r10, [r5, #28]
    
	adds r8, r8, r11 //add carry
	mov r11, #0 //clear carry
	adc r11, r11, #0
    adds r8, r8, r9
    adc r11, r11, #0
    adds r8, r8, r10
    adc r11,r11,#0
    
    str r8, [r2, #44]


    // r2, #48
    ldr r8, [r3, #16]
    
    add r8, r8, r11
	mov r11, #0
    
    str r8, [r2, #48]


	// Shifting
	
	ldr r8, [r3, #20]
	str r8, [r2, #52]
	
	ldr r8, [r3, #24]
	str r8, [r2, #56]
	
	ldr r8, [r3, #28]
	str r8, [r2, #60]
	

    bx lr

_128mul:
    // Save registers that will be used
    push {r0-r2, lr}

    // Call _64mul with the first pair of 64-bit values
    bl _64mul


    add r0, r0, #8
	add r2, r2, #32
    bl _64mul
	
	sub r0, r0, #8
	add r1, r1, #8
	add r2, r2, #16
    bl _64mul
	
	
	add r0, r0, #8
    sub r2, r2, #32
	

    // Call _64mul with the second pair of 64-bit values
    bl _64mul


    // Restore registers
    pop {r0-r2, lr}

	// 後處理加法：
	add r3, r2, #16 
	add r4, r3, #16
	add r5, r4, #16



	// r2, #8
	ldr r8, [r2, #8]
	ldr r9, [r4]
	ldr r10, [r5]
	
	adds r8, r8, r9
	adc r11, r11, #0
	adds r8, r8, r10
	adc r11,r11,#0
	
	str r8, [r2, #8] //carry in r11
	
	
	// r2, #12
	ldr r8, [r2, #12]
	ldr r9, [r4, #4]
	ldr r10, [r5, #4]
	
	add r8, r8, r11 //把進位加上去
	mov r11, #0 //進位歸零
	adds r8, r8, r9
	adc r11, r11, #0
	adds r8, r8, r10
	adc r11,r11,#0
	
	str r8, [r2, #12]
	
	
	// r2, #16
	ldr r8, [r3]
	ldr r9, [r4, #8]
	ldr r10, [r5, #8]
	
	add r8, r8, r11 //把進位加上去
	mov r11, #0 //進位歸零
	adds r8, r8, r9
	adc r11, r11, #0
	adds r8, r8, r10
	adc r11,r11,#0
	
	str r8, [r2, #16]
	
	
	
	// r2, #20
	ldr r8, [r3, #4]
	ldr r9, [r4, #12]
	ldr r10, [r5, #12]
	
	add r8, r8, r11 //把進位加上去
	mov r11, #0 //進位歸零
	adds r8, r8, r9
	adc r11, r12, #0
	adds r8, r8, r10
	adc r11,r11,#0
	
	str r8, [r2, #20]
	
	// r2, #24
	ldr r8, [r3, #8]
	
	add r8, r8, r11
	mov r11, #0 //clear carry
	
	str r8, [r2, #24]
	
    bx lr

_64mul:
    // Load the lower and upper parts of the first 64-bit number
    ldr r3, [r0]           // Lower part of the first number
    ldr r4, [r0, #4]       // Upper part of the first number

    // Load the lower and upper parts of the second 64-bit number
    ldr r5, [r1]           // Lower part of the second number
    ldr r6, [r1, #4]       // Upper part of the second number

    // Perform the multiplication
    // r3:r4 * r5:r6 -> (r7:r8:r9:r10)
    // r3 * r5 (lower * lower)
    umull r7, r8, r3, r5

    // r3 * r6 (lower * upper)
    umull r9, r10, r3, r6

    // Add the result to the upper part
    adds r8, r8, r9
    adc r10, r10, #0

    // r4 * r5 (upper * lower)
    umull r9, r3, r4, r5

    // Add the result to the upper part
    adds r8, r8, r9
    adc r10, r10, r3

    // r4 * r6 (upper * upper)
    umull r9, r3, r4, r6

    // Add the result to the upper part
    adds r10, r10, r9
    adc r3, r3, #0

    // Store the result
    str r7, [r2]           // Store lower part
    str r8, [r2, #4]       // Store lower-middle part
    str r10, [r2, #8]      // Store upper-middle part
    str r3, [r2, #12]      // Store upper part

    bx lr                  // Return from subroutine

_exit:
    mov r7, #1             // System call for exit
    mov r0, #0             // Exit status
    svc 0                  // Trigger system call
