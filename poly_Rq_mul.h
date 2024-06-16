#ifndef POLY_RQ_MUL
#define POLY_RQ_MUL

#include <stdio.h>
#include <stdint.h>
#include <arm_neon.h>

#include "param.h"

// the size of each block matrix
#define SIZE 8

void poly_Rq_mul (uint16_t *r, uint16_t *a, uint16_t *b);

#endif