#include <stdio.h>
#include <arm_neon.h>

uint16_t a[16] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16};
uint16_t b[16] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16};
uint16_t result[16];

void Toep_2x8(uint16_t *a, uint16_t *b, uint16_t *r);
void naiveTMVP(uint16_t *a, uint16_t *b, uint16_t *r);


int main() {
    printf("Hello\n");
    
    Toep_2x8(a, b, result);


    printf("byebye\n");
    return 0;
}

void Toep_2x8(uint16_t *a, uint16_t *b, uint16_t *r){
    // a is the address of length 16 coefficients of a
    // b is the address of length 16 coefficients of b
    // r is the address of length 16 coefficients of result.
    // We convert input a into a Toeplitz matrix representation
    



    uint16_t toep_a_0[15];
    uint16_t toep_a_pm1[15];
    for (uint16_t i=0; i<15; i++){
        toep_a_0[i] = a[(23-i) % 16];
        toep_a_pm1[i] = a[15-i];
    }

    
    // printf("toep_a_pm1 is ");
    // for (uint16_t i=0; i<15; i++){
    //     printf("%d ", toep_a_pm1[i]);
    // }
    // printf("\n");

    
    // (A_-1 - A_0) B_1
    uint16_t toep[15];
    for (uint16_t i=0; i<15; i++){
        toep[i] = toep_a_pm1[i] - toep_a_0[i];
    }
    // uint16_t current_b[8];
    // for (uint16_t i=0; i<8; i++){
    //     current_b[i] = b[8+i];
    // }




    
    uint16_t temp_result_1[8] = {0,0,0,0,0,0,0,0};
    naiveTMVP(toep, &b[8], temp_result_1);


    // A0 (B_0+B_1)

    uint16_t current_b[8];
    for (uint16_t i=0; i<8; i++){
        current_b[i] = b[i] + b[8+i];
    }
    
    uint16_t temp_result_2[8] = {0,0,0,0,0,0,0,0};
    naiveTMVP(toep_a_0, current_b, temp_result_2);


    // (A_1 - A_0) B_0

    for (uint16_t i=0; i<15; i++){
        toep[i] = toep_a_pm1[i] - toep_a_0[i];
    }

    uint16_t temp_result_3[8] = {0,0,0,0,0,0,0,0};
    naiveTMVP(toep, b, temp_result_3);



    // Recombination
    for (uint16_t i=0; i<8; i++){
        result[i] = temp_result_1[i] + temp_result_2[i];
        result[8+i] = temp_result_2[i] + temp_result_3[i];
    }


    for (uint16_t i=0; i<16; i++){
        printf("%d ", result[i]);
    }

}

void naiveTMVP(uint16_t *a, uint16_t *b, uint16_t *r){
    // a is the anti-diagonal elements of a toep, consists of 15 elements.
    // b is the vector to be multiplied with
    // r is the result vector

    uint16x8_t result_vector = vdupq_n_u16(0);
    u_int16_t b_scalar;
    uint16x8_t a_vector;

    for (uint16_t i=0; i<8; i++){

        // Load vectors
        b_scalar = b[i];

        a_vector = vld1q_u16(&a[i]);

        // Perform multiply-accumulate operation
        result_vector = vmlaq_n_u16(result_vector, a_vector, b_scalar);

    }
    
    uint16_t r_temp[8];
    vst1q_u16(r_temp, result_vector);

    // 我怎麼想也不知道 result_vector 要 倒序 才會是我們要的
    for (u_int16_t i=0; i<8; i++){
        r[i] = r_temp[7-i];
    }


}


