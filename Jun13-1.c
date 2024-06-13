// We implement three-way Toeplitz matrix decomposition and multiplication algorithm
#include <stdio.h>
#include <arm_neon.h>

// Define the size of the arrays
#define SIZE 24
#define STANDARD_SIZE 8

uint16_t a[SIZE] = {159, 29, 43, 155, 152, 71, 188, 7, 167, 68, 191, 63, 186, 148, 30, 90, 74, 193, 37, 54, 143, 90, 5, 185};
uint16_t b[SIZE] = {30, 123, 92, 177, 58, 113, 151, 200, 151, 25, 62, 27, 8, 165, 29, 26, 53, 71, 199, 1, 136, 50, 48, 46};
uint16_t result[SIZE] = {0};

void Toep_3x8(uint16_t *a, uint16_t *b, uint16_t *r);
void naiveTMVP(uint16_t *a, uint16_t *b, uint16_t *r);

int main() {
    printf("Hello\n\n");
    
    // Perform the main function
    Toep_3x8(a, b, result);

    // print the result
    for (uint16_t i=0; i<SIZE; i++){
        printf("%d ", result[i]);
    }

    printf("\n\nbyebye");
    return 0;
}



void Toep_3x8(uint16_t *a, uint16_t *b, uint16_t *r){

    uint16_t toep_a_m2[15];
    uint16_t toep_a_m1[15];
    uint16_t toep_a_0[15];
    uint16_t toep_a_p1[15];
    uint16_t toep_a_p2[15];
    uint16_t toep_a_0_m1_m2[15];
    uint16_t toep_a_p1_0_m1[15];
    uint16_t toep_a_p2_p1_0[15];

    uint16_t b_p0[8];
    uint16_t b_p1[8];
    uint16_t b_p2[8];

    uint16_t b_p2_minus_p0[8];
    uint16_t b_p0_minus_p1[8];
    uint16_t b_p1_minus_p2[8];

    for (uint16_t i=0; i<(2 * STANDARD_SIZE - 1); i++){
        // i from 0, 1, 2, ...,  14
        toep_a_m2[i] = a[(15-i)];
        toep_a_m1[i] = a[(23 - i) % 24];
        toep_a_0[i] = a[(24 + 7 - i) % 24];
        toep_a_p1[i] = a[(15-i)];
        toep_a_p2[i] = a[(23 - i) % 24];

        toep_a_0_m1_m2[i] = toep_a_0[i] + toep_a_m1[i] + toep_a_m2[i];
        toep_a_p1_0_m1[i] = toep_a_p1[i] + toep_a_0[i] + toep_a_m1[i];
        toep_a_p2_p1_0[i] = toep_a_p2[i] + toep_a_p1[i] + toep_a_0[i];
    }

    for (uint16_t i=0; i<STANDARD_SIZE; i++){
        b_p0[i] = b[i];
        b_p1[i] = b[STANDARD_SIZE + i];
        b_p2[i] = b[2 * STANDARD_SIZE + i];

        b_p2_minus_p0[i] = b_p2[i] - b_p0[i];
        b_p0_minus_p1[i] = b_p0[i] - b_p1[i];
        b_p1_minus_p2[i] = b_p1[i] - b_p2[i];
    }

    uint16_t temp_result_1[STANDARD_SIZE] = {0};
    uint16_t temp_result_2[STANDARD_SIZE] = {0};
    uint16_t temp_result_3[STANDARD_SIZE] = {0};
    uint16_t temp_result_4[STANDARD_SIZE] = {0};
    uint16_t temp_result_5[STANDARD_SIZE] = {0};
    uint16_t temp_result_6[STANDARD_SIZE] = {0};

    naiveTMVP(toep_a_0_m1_m2,   b_p2,           temp_result_1);
    naiveTMVP(toep_a_p1_0_m1,   b_p1,           temp_result_2);
    naiveTMVP(toep_a_p2_p1_0,   b_p0,           temp_result_3);
    naiveTMVP(toep_a_0,         b_p2_minus_p0,  temp_result_4);
    naiveTMVP(toep_a_p1,        b_p0_minus_p1,  temp_result_5);
    naiveTMVP(toep_a_m1,        b_p1_minus_p2,  temp_result_6);

    // Recombination
    for (uint16_t i=0; i<STANDARD_SIZE; i++){
        r[i] += temp_result_1[i] - temp_result_4[i] + temp_result_6[i];
        r[STANDARD_SIZE+i] += temp_result_2[i] + temp_result_5[i] - temp_result_6[i];
        r[2*STANDARD_SIZE+i] += temp_result_3[i] - temp_result_5[i] + temp_result_4[i];
    }

    for (uint16_t i=0; i<SIZE; i++){
        r[i] = r[i] % 4096;
    }


}










void naiveTMVP(uint16_t *a, uint16_t *b, uint16_t *r){
    // a is the anti-diagonal elements of a toep, consists of 15 elements.
    // b is the vector to be multiplied with
    // r is the result vector

    uint16x8_t result_vector = vdupq_n_u16(0);
    u_int16_t b_scalar;
    uint16x8_t a_vector;

    for (uint16_t i=0; i<STANDARD_SIZE; i++){

        // Load vectors
        b_scalar = b[i];

        a_vector = vld1q_u16(&a[i]);

        // Perform multiply-accumulate operation
        result_vector = vmlaq_n_u16(result_vector, a_vector, b_scalar);

    }
    
    uint16_t r_temp[STANDARD_SIZE];
    vst1q_u16(r_temp, result_vector);

    // 我怎麼想也不知道 result_vector 要 倒序 才會是我們要的
    for (u_int16_t i=0; i<STANDARD_SIZE; i++){
        r[i] = r_temp[(STANDARD_SIZE - 1) - i];
    }


}