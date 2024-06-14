.section .text
.global toep_poly_mul_8

toep_poly_mul_8:
    // Arguments:
    // x0: result r(x)         (uint16_t *) = (r0, ..., r7)
    // x1: toeplitz a(x) (const uint16_t *) = (a7, ..., a0, a7, ... a1)
    // x2: b(x)          (const uint16_t *) = (b0, ..., b7)

    // load b(x) into v2
    ld1     {v2.8h}, [x2]

    // compute r0
    add     x8, x1, #14
    ld1     {v1.8h}, [x8]
    mul     v1.8h, v1.8h, v2.8h
    addv    h3, v1.8h
    mov     v0.8h[0], v3.8h[0]
    // compute r1
    add     x8, x1, #12
    ld1     {v1.8h}, [x8]
    mul     v1.8h, v1.8h, v2.8h
    addv    h3, v1.8h
    mov     v0.8h[1], v3.8h[0]
    // compute r2
    add     x8, x1, #10
    ld1     {v1.8h}, [x8]
    mul     v1.8h, v1.8h, v2.8h
    addv    h3, v1.8h
    mov     v0.8h[2], v3.8h[0]
    // compute r3
    add     x8, x1, #8
    ld1     {v1.8h}, [x8]
    mul     v1.8h, v1.8h, v2.8h
    addv    h3, v1.8h
    mov     v0.8h[3], v3.8h[0]
    // compute r4
    add     x8, x1, #6
    ld1     {v1.8h}, [x8]
    mul     v1.8h, v1.8h, v2.8h
    addv    h3, v1.8h
    mov     v0.8h[4], v3.8h[0]
    // compute r5
    add     x8, x1, #4
    ld1     {v1.8h}, [x8]
    mul     v1.8h, v1.8h, v2.8h
    addv    h3, v1.8h
    mov     v0.8h[5], v3.8h[0]
    // compute r6
    add     x8, x1, #2
    ld1     {v1.8h}, [x8]
    mul     v1.8h, v1.8h, v2.8h
    addv    h3, v1.8h
    mov     v0.8h[6], v3.8h[0]
    // compute r7
    add     x8, x1, #0
    ld1     {v1.8h}, [x8]
    mul     v1.8h, v1.8h, v2.8h
    addv    h3, v1.8h
    mov     v0.8h[7], v3.8h[0]

    // mod 4096
    mov     x8, #4095
    mov     v1.8h[0], w8
    mov     v1.8h[1], w8
    mov     v1.8h[2], w8
    mov     v1.8h[3], w8
    mov     v1.8h[4], w8
    mov     v1.8h[5], w8
    mov     v1.8h[6], w8
    mov     v1.8h[7], w8

    and     v0.16b, v0.16b, v1.16b

    st1     {v0.8h}, [x0]

    ret
