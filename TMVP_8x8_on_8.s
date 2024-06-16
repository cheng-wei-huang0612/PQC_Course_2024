.section .text
.global TMVP_8x8_on_8

TMVP_8x8_on_8:
    // Arguments:
    // x0: toeplitz a(x) (const uint16_t *) = (a_-7, ..., a_0, a_1, ... a_8)
    // x1: b(x)          (const uint16_t *) = (b_0, ..., b_7)
    // x2: result r(x)         (uint16_t *) = (r_0, ..., r_7)

    // load b(x) into v2
    ld1     {v2.8h}, [x1]

    // compute r0
    add     x8, x0, #14
    ld1     {v1.8h}, [x8]
    mul     v1.8h, v1.8h, v2.8h
    addv    h3, v1.8h
    mov     v0.8h[0], v3.8h[0]
    // compute r1
    add     x8, x0, #12
    ld1     {v1.8h}, [x8]
    mul     v1.8h, v1.8h, v2.8h
    addv    h3, v1.8h
    mov     v0.8h[1], v3.8h[0]
    // compute r2
    add     x8, x0, #10
    ld1     {v1.8h}, [x8]
    mul     v1.8h, v1.8h, v2.8h
    addv    h3, v1.8h
    mov     v0.8h[2], v3.8h[0]
    // compute r3
    add     x8, x0, #8
    ld1     {v1.8h}, [x8]
    mul     v1.8h, v1.8h, v2.8h
    addv    h3, v1.8h
    mov     v0.8h[3], v3.8h[0]
    // compute r4
    add     x8, x0, #6
    ld1     {v1.8h}, [x8]
    mul     v1.8h, v1.8h, v2.8h
    addv    h3, v1.8h
    mov     v0.8h[4], v3.8h[0]
    // compute r5
    add     x8, x0, #4
    ld1     {v1.8h}, [x8]
    mul     v1.8h, v1.8h, v2.8h
    addv    h3, v1.8h
    mov     v0.8h[5], v3.8h[0]
    // compute r6
    add     x8, x0, #2
    ld1     {v1.8h}, [x8]
    mul     v1.8h, v1.8h, v2.8h
    addv    h3, v1.8h
    mov     v0.8h[6], v3.8h[0]
    // compute r7
    add     x8, x0, #0
    ld1     {v1.8h}, [x8]
    mul     v1.8h, v1.8h, v2.8h
    addv    h3, v1.8h
    mov     v0.8h[7], v3.8h[0]

    st1     {v0.8h}, [x2]

    ret