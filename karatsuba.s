	.section	__TEXT,__text,regular,pure_instructions
	.build_version macos, 14, 0	sdk_version 14, 4
	.globl	_add                            ; -- Begin function add
	.p2align	2
_add:                                   ; @add
	.cfi_startproc
; %bb.0:
	sub	sp, sp, #16
	.cfi_def_cfa_offset 16
	str	w0, [sp, #12]
	str	w1, [sp, #8]
	ldr	w8, [sp, #12]
	ldr	w9, [sp, #8]
	add	w0, w8, w9
	add	sp, sp, #16
	ret
	.cfi_endproc
                                        ; -- End function
	.globl	_subtract                       ; -- Begin function subtract
	.p2align	2
_subtract:                              ; @subtract
	.cfi_startproc
; %bb.0:
	sub	sp, sp, #16
	.cfi_def_cfa_offset 16
	str	w0, [sp, #12]
	str	w1, [sp, #8]
	ldr	w8, [sp, #12]
	ldr	w9, [sp, #8]
	subs	w0, w8, w9
	add	sp, sp, #16
	ret
	.cfi_endproc
                                        ; -- End function
	.globl	_karatsuba                      ; -- Begin function karatsuba
	.p2align	2
_karatsuba:                             ; @karatsuba
	.cfi_startproc
; %bb.0:
	sub	sp, sp, #144
	.cfi_def_cfa_offset 144
	stp	x29, x30, [sp, #128]            ; 16-byte Folded Spill
	add	x29, sp, #128
	.cfi_def_cfa w29, 16
	.cfi_offset w30, -8
	.cfi_offset w29, -16
	stur	w0, [x29, #-8]
	stur	w1, [x29, #-12]
	ldur	w8, [x29, #-8]
	subs	w8, w8, #10
	cset	w8, lt
	tbnz	w8, #0, LBB2_2
	b	LBB2_1
LBB2_1:
	ldur	w8, [x29, #-12]
	subs	w8, w8, #10
	cset	w8, ge
	tbnz	w8, #0, LBB2_3
	b	LBB2_2
LBB2_2:
	ldur	w8, [x29, #-8]
	ldur	w9, [x29, #-12]
	mul	w8, w8, w9
	stur	w8, [x29, #-4]
	b	LBB2_4
LBB2_3:
	ldur	s1, [x29, #-8]
                                        ; implicit-def: $d0
	fmov	s0, s1
	sshll.2d	v0, v0, #0
                                        ; kill: def $d0 killed $d0 killed $q0
	scvtf	d0, d0
	bl	_log10
	fmov	d1, #1.00000000
	str	d1, [sp, #8]                    ; 8-byte Folded Spill
	fadd	d0, d0, d1
	str	d0, [sp, #16]                   ; 8-byte Folded Spill
	ldur	s1, [x29, #-12]
                                        ; implicit-def: $d0
	fmov	s0, s1
	sshll.2d	v0, v0, #0
                                        ; kill: def $d0 killed $d0 killed $q0
	scvtf	d0, d0
	bl	_log10
	ldr	d2, [sp, #8]                    ; 8-byte Folded Reload
	fmov	d1, d0
	ldr	d0, [sp, #16]                   ; 8-byte Folded Reload
	fadd	d1, d1, d2
	fmaxnm	d0, d0, d1
	fcvtzs	w8, d0
	stur	w8, [x29, #-16]
	ldur	w8, [x29, #-16]
	mov	w9, #2
	str	w9, [sp, #44]                   ; 4-byte Folded Spill
	sdiv	w8, w8, w9
	stur	w8, [x29, #-20]
	ldur	w8, [x29, #-8]
	str	w8, [sp, #24]                   ; 4-byte Folded Spill
	ldur	s1, [x29, #-20]
                                        ; implicit-def: $d0
	fmov	s0, s1
	sshll.2d	v0, v0, #0
                                        ; kill: def $d0 killed $d0 killed $q0
	scvtf	d1, d0
	fmov	d0, #10.00000000
	str	d0, [sp, #48]                   ; 8-byte Folded Spill
	bl	_pow
	ldr	w8, [sp, #24]                   ; 4-byte Folded Reload
	fmov	d1, d0
	ldr	d0, [sp, #48]                   ; 8-byte Folded Reload
	fcvtzs	w9, d1
	sdiv	w8, w8, w9
	stur	w8, [x29, #-24]
	ldur	w8, [x29, #-8]
	str	w8, [sp, #28]                   ; 4-byte Folded Spill
	ldur	s2, [x29, #-20]
                                        ; implicit-def: $d1
	fmov	s1, s2
	sshll.2d	v1, v1, #0
                                        ; kill: def $d1 killed $d1 killed $q1
	scvtf	d1, d1
	bl	_pow
	ldr	w8, [sp, #28]                   ; 4-byte Folded Reload
	fmov	d1, d0
	ldr	d0, [sp, #48]                   ; 8-byte Folded Reload
	fcvtzs	w10, d1
	sdiv	w9, w8, w10
	mul	w9, w9, w10
	subs	w8, w8, w9
	stur	w8, [x29, #-28]
	ldur	w8, [x29, #-12]
	str	w8, [sp, #32]                   ; 4-byte Folded Spill
	ldur	s2, [x29, #-20]
                                        ; implicit-def: $d1
	fmov	s1, s2
	sshll.2d	v1, v1, #0
                                        ; kill: def $d1 killed $d1 killed $q1
	scvtf	d1, d1
	bl	_pow
	ldr	w8, [sp, #32]                   ; 4-byte Folded Reload
	fmov	d1, d0
	ldr	d0, [sp, #48]                   ; 8-byte Folded Reload
	fcvtzs	w9, d1
	sdiv	w8, w8, w9
	stur	w8, [x29, #-32]
	ldur	w8, [x29, #-12]
	str	w8, [sp, #36]                   ; 4-byte Folded Spill
	ldur	s2, [x29, #-20]
                                        ; implicit-def: $d1
	fmov	s1, s2
	sshll.2d	v1, v1, #0
                                        ; kill: def $d1 killed $d1 killed $q1
	scvtf	d1, d1
	bl	_pow
	ldr	w8, [sp, #36]                   ; 4-byte Folded Reload
	fcvtzs	w10, d0
	sdiv	w9, w8, w10
	mul	w9, w9, w10
	subs	w8, w8, w9
	stur	w8, [x29, #-36]
	ldur	w0, [x29, #-28]
	ldur	w1, [x29, #-36]
	bl	_karatsuba
	stur	w0, [x29, #-40]
	ldur	w0, [x29, #-28]
	ldur	w1, [x29, #-24]
	bl	_add
	str	w0, [sp, #40]                   ; 4-byte Folded Spill
	ldur	w0, [x29, #-36]
	ldur	w1, [x29, #-32]
	bl	_add
	mov	x1, x0
	ldr	w0, [sp, #40]                   ; 4-byte Folded Reload
	bl	_karatsuba
	stur	w0, [x29, #-44]
	ldur	w0, [x29, #-24]
	ldur	w1, [x29, #-32]
	bl	_karatsuba
	ldr	w8, [sp, #44]                   ; 4-byte Folded Reload
	ldr	d0, [sp, #48]                   ; 8-byte Folded Reload
	stur	w0, [x29, #-48]
	ldur	s2, [x29, #-48]
                                        ; implicit-def: $d1
	fmov	s1, s2
	sshll.2d	v1, v1, #0
                                        ; kill: def $d1 killed $d1 killed $q1
	scvtf	d1, d1
	stur	d1, [x29, #-56]                 ; 8-byte Folded Spill
	ldur	w9, [x29, #-20]
	mul	w8, w8, w9
	scvtf	d1, w8
	bl	_pow
	fmov	d1, d0
	ldr	d0, [sp, #48]                   ; 8-byte Folded Reload
	str	d1, [sp, #64]                   ; 8-byte Folded Spill
	ldur	w8, [x29, #-44]
	ldur	w9, [x29, #-48]
	subs	w8, w8, w9
	ldur	w9, [x29, #-40]
	subs	w8, w8, w9
	scvtf	d1, w8
	str	d1, [sp, #56]                   ; 8-byte Folded Spill
	ldur	s2, [x29, #-20]
                                        ; implicit-def: $d1
	fmov	s1, s2
	sshll.2d	v1, v1, #0
                                        ; kill: def $d1 killed $d1 killed $q1
	scvtf	d1, d1
	bl	_pow
	ldr	d2, [sp, #56]                   ; 8-byte Folded Reload
	ldr	d1, [sp, #64]                   ; 8-byte Folded Reload
	fmov	d3, d0
	ldur	d0, [x29, #-56]                 ; 8-byte Folded Reload
	fmul	d2, d2, d3
	fmadd	d0, d0, d1, d2
	ldur	s2, [x29, #-40]
                                        ; implicit-def: $d1
	fmov	s1, s2
	sshll.2d	v1, v1, #0
                                        ; kill: def $d1 killed $d1 killed $q1
	scvtf	d1, d1
	fadd	d0, d0, d1
	fcvtzs	w8, d0
	stur	w8, [x29, #-4]
	b	LBB2_4
LBB2_4:
	ldur	w0, [x29, #-4]
	ldp	x29, x30, [sp, #128]            ; 16-byte Folded Reload
	add	sp, sp, #144
	ret
	.cfi_endproc
                                        ; -- End function
	.globl	_main                           ; -- Begin function main
	.p2align	2
_main:                                  ; @main
	.cfi_startproc
; %bb.0:
	sub	sp, sp, #80
	.cfi_def_cfa_offset 80
	stp	x29, x30, [sp, #64]             ; 16-byte Folded Spill
	add	x29, sp, #64
	.cfi_def_cfa w29, 16
	.cfi_offset w30, -8
	.cfi_offset w29, -16
	mov	w8, #0
	stur	w8, [x29, #-16]                 ; 4-byte Folded Spill
	stur	wzr, [x29, #-4]
	mov	w8, #23422
	stur	w8, [x29, #-8]
	mov	w8, #56782
	stur	w8, [x29, #-12]
	ldur	w9, [x29, #-8]
                                        ; implicit-def: $x8
	mov	x8, x9
	str	x8, [sp, #32]                   ; 8-byte Folded Spill
	ldur	w9, [x29, #-12]
                                        ; implicit-def: $x8
	mov	x8, x9
	stur	x8, [x29, #-24]                 ; 8-byte Folded Spill
	ldur	w0, [x29, #-8]
	ldur	w1, [x29, #-12]
	bl	_karatsuba
	ldr	x10, [sp, #32]                  ; 8-byte Folded Reload
	ldur	x8, [x29, #-24]                 ; 8-byte Folded Reload
	mov	x9, sp
	str	x10, [x9]
	str	x8, [x9, #8]
                                        ; implicit-def: $x8
	mov	x8, x0
	str	x8, [x9, #16]
	adrp	x0, l_.str@PAGE
	add	x0, x0, l_.str@PAGEOFF
	bl	_printf
	ldur	w0, [x29, #-16]                 ; 4-byte Folded Reload
	ldp	x29, x30, [sp, #64]             ; 16-byte Folded Reload
	add	sp, sp, #80
	ret
	.cfi_endproc
                                        ; -- End function
	.section	__TEXT,__cstring,cstring_literals
l_.str:                                 ; @.str
	.asciz	"Karatsuba multiplication of %d and %d is %d\n"

.subsections_via_symbols
