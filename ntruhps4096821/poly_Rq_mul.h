#ifndef POLY_RQ_MUL
#define POLY_RQ_MUL

#include <stdio.h>
#include <stdint.h>
#include <arm_neon.h>

#include "params.h"

// the size of each block matrix
#define SIZE 8

#define POLY_N 1024
typedef struct {
    uint16_t coeffs[POLY_N];
} poly;

void poly_Rq_mul (poly *r, poly *a, poly *b);

#endif
