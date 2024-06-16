#include "poly_Rq_mul.h"

void Toep_3x3x3x2x2x8(uint16_t *toep, uint16_t *vec, uint16_t *r);
void Toep_3x3x2x2x8  (uint16_t *toep, uint16_t *vec, uint16_t *r);
void Toep_3x2x2x8    (uint16_t *toep, uint16_t *vec, uint16_t *r);
void Toep_2x2x8      (uint16_t *toep, uint16_t *vec, uint16_t *r);
void Toep_2x8        (uint16_t *toep, uint16_t *vec, uint16_t *r);
void TMVP_8x8_on_8   (uint16_t *toep, uint16_t *vec, uint16_t *r);

void poly_Rq_mul(poly *r, poly *a, poly *b) {
    // Convert coefficients of a into the anti-diagonal of 32x32 Toep matrix:
    // toep_a = {0, ...(43)..., 0, a_821, ..., a_1, a_0, a_821, ..., a_1, a_0, 0, ...(43)..., 0}
    uint16_t toep_a[216*SIZE] = {0}; // initialized to zeros
    // vec_b
    uint16_t vec_b[108*SIZE] = {0};
    for (uint16_t i=0; i < NTRU_N; i++){
        toep_a[108*SIZE - 1          - i] = a->coeffs[i];
        toep_a[108*SIZE - 1 + NTRU_N - i] = a->coeffs[i];
        vec_b[i] = b->coeffs[i];
    }

    // perform the multiplication
    uint16_t result[108*SIZE];
    Toep_3x3x3x2x2x8(toep_a, vec_b, result);

    // modulo 4096
    for (uint16_t i=0; i<108*SIZE; i++){
        result[i] = result[i] & 4095;
    }

    // extract the answer part
    for (uint16_t i=0; i<NTRU_N; i++){
        r->coeffs[i] = result[i];
    }

    return ;
}

void Toep_3x3x3x2x2x8(uint16_t *toep, uint16_t *vec, uint16_t *r){
    // a is the anti-diagonal elements of a 108 SIZE x 108 SIZE toep, consists of 216 SIZE elements. (In fact the last one is of no use)
    // b is the vector to be multiplied with, consists of 108 SIZE elements
    // r is the result vector

    uint16_t toep_m2[72*SIZE];
    uint16_t toep_m1[72*SIZE];
    uint16_t toep_0[72*SIZE];
    uint16_t toep_p1[72*SIZE];
    uint16_t toep_p2[72*SIZE];

    uint16_t toep_0_m1_m2[72*SIZE];
    uint16_t toep_p1_0_m1[72*SIZE];
    uint16_t toep_p2_p1_0[72*SIZE];

    uint16_t vec_0[36*SIZE];
    uint16_t vec_1[36*SIZE];
    uint16_t vec_2[36*SIZE];

    uint16_t vec_0_minus_1[36*SIZE];
    uint16_t vec_1_minus_2[36*SIZE];
    uint16_t vec_2_minus_0[36*SIZE];

    uint16_t intermediate_0[36*SIZE]={0};
    uint16_t intermediate_1[36*SIZE]={0};
    uint16_t intermediate_2[36*SIZE]={0};
    uint16_t intermediate_3[36*SIZE]={0};
    uint16_t intermediate_4[36*SIZE]={0};
    uint16_t intermediate_5[36*SIZE]={0};

    // Block Matrix form of Toeplitz matrix
    for (uint16_t i=0; i<72*SIZE; i++){
        // i=0,1,...,72xSIZE-1
        toep_p2[i]=toep[i          ];
        toep_p1[i]=toep[i + 36*SIZE];
        toep_0[i] =toep[i + 72*SIZE];
        toep_m1[i]=toep[i + 108*SIZE];
        toep_m2[i]=toep[i + 144*SIZE];

        //toep_0_m1_m2[i] = toep_0[i] + toep_m1[i] + toep_m2[i];
        //toep_p1_0_m1[i] = toep_p1[i] + toep_0[i] + toep_m1[i];
        //toep_p2_p1_0[i] = toep_p2[i] + toep_p1[i] + toep_0[i];
    }
    uint16x8_t vtoep_m2, vtoep_m1, vtoep_0, vtoep_p1, vtoep_p2;
    for (uint16_t i=0; i<72; i++){
        vtoep_m2 = vld1q_u16(&toep_m2[i * SIZE]);
        vtoep_m1 = vld1q_u16(&toep_m1[i * SIZE]);
        vtoep_0  = vld1q_u16(&toep_0 [i * SIZE]);
        vtoep_p1 = vld1q_u16(&toep_p1[i * SIZE]);
        vtoep_p2 = vld1q_u16(&toep_p2[i * SIZE]);

        vst1q_u16(&toep_0_m1_m2[i * SIZE], vaddq_u16(vtoep_0 , vaddq_u16(vtoep_m1, vtoep_m2)));
        vst1q_u16(&toep_p1_0_m1[i * SIZE], vaddq_u16(vtoep_p1, vaddq_u16(vtoep_0 , vtoep_m1)));
        vst1q_u16(&toep_p2_p1_0[i * SIZE], vaddq_u16(vtoep_p2, vaddq_u16(vtoep_p1, vtoep_0 )));
    }

    for (uint16_t i=0; i<36*SIZE; i++) {
        vec_0[i] = vec[i         ];
        vec_1[i] = vec[i + 36*SIZE];
        vec_2[i] = vec[i + 72*SIZE];

        vec_0_minus_1[i] = vec_0[i] - vec_1[i];
        vec_1_minus_2[i] = vec_1[i] - vec_2[i];
        vec_2_minus_0[i] = vec_2[i] - vec_0[i];
    }

    Toep_3x3x2x2x8(toep_0_m1_m2,   vec_2,          intermediate_0);
    Toep_3x3x2x2x8(toep_p1_0_m1,   vec_1,          intermediate_1);
    Toep_3x3x2x2x8(toep_p2_p1_0,   vec_0,          intermediate_2);
    Toep_3x3x2x2x8(toep_0,         vec_2_minus_0,  intermediate_3);
    Toep_3x3x2x2x8(toep_p1,        vec_0_minus_1,  intermediate_4);
    Toep_3x3x2x2x8(toep_m1,        vec_1_minus_2,  intermediate_5);

    // Recombination
    for (uint16_t i=0; i<36*SIZE; i++){
        r[i          ] = intermediate_0[i] - intermediate_3[i] + intermediate_5[i];
        r[i + 36*SIZE] = intermediate_1[i] - intermediate_5[i] + intermediate_4[i];
        r[i + 72*SIZE] = intermediate_2[i] - intermediate_4[i] + intermediate_3[i]; 
    }

}

void Toep_3x3x2x2x8(uint16_t *toep, uint16_t *vec, uint16_t *r){
    // a is the anti-diagonal elements of a 36 SIZE x 36 SIZE toep, consists of 72 SIZE elements. (In fact the last one is of no use)
    // b is the vector to be multiplied with, consists of 36 SIZE elements
    // r is the result vector

    uint16_t toep_m2[24*SIZE];
    uint16_t toep_m1[24*SIZE];
    uint16_t toep_0[24*SIZE];
    uint16_t toep_p1[24*SIZE];
    uint16_t toep_p2[24*SIZE];

    uint16_t toep_0_m1_m2[24*SIZE];
    uint16_t toep_p1_0_m1[24*SIZE];
    uint16_t toep_p2_p1_0[24*SIZE];

    uint16_t vec_0[12*SIZE];
    uint16_t vec_1[12*SIZE];
    uint16_t vec_2[12*SIZE];

    uint16_t vec_0_minus_1[12*SIZE];
    uint16_t vec_1_minus_2[12*SIZE];
    uint16_t vec_2_minus_0[12*SIZE];

    uint16_t intermediate_0[12*SIZE]={0};
    uint16_t intermediate_1[12*SIZE]={0};
    uint16_t intermediate_2[12*SIZE]={0};
    uint16_t intermediate_3[12*SIZE]={0};
    uint16_t intermediate_4[12*SIZE]={0};
    uint16_t intermediate_5[12*SIZE]={0};

    // Block Matrix form of Toeplitz matrix
    for (uint16_t i=0; i<24*SIZE; i++){
        // i=0,1,...,8xSIZE-1=63
        toep_p2[i]=toep[i          ];
        toep_p1[i]=toep[i + 12*SIZE];
        toep_0[i] =toep[i + 24*SIZE];
        toep_m1[i]=toep[i + 36*SIZE];
        toep_m2[i]=toep[i + 48*SIZE];

        toep_0_m1_m2[i] = toep_0[i] + toep_m1[i] + toep_m2[i];
        toep_p1_0_m1[i] = toep_p1[i] + toep_0[i] + toep_m1[i];
        toep_p2_p1_0[i] = toep_p2[i] + toep_p1[i] + toep_0[i];

    }

    for (uint16_t i=0; i<12*SIZE; i++) {
        vec_0[i] = vec[i         ];
        vec_1[i] = vec[i + 12*SIZE];
        vec_2[i] = vec[i + 24*SIZE];

        vec_0_minus_1[i] = vec_0[i] - vec_1[i];
        vec_1_minus_2[i] = vec_1[i] - vec_2[i];
        vec_2_minus_0[i] = vec_2[i] - vec_0[i];
    }

    Toep_3x2x2x8(toep_0_m1_m2,   vec_2,          intermediate_0);
    Toep_3x2x2x8(toep_p1_0_m1,   vec_1,          intermediate_1);
    Toep_3x2x2x8(toep_p2_p1_0,   vec_0,          intermediate_2);
    Toep_3x2x2x8(toep_0,         vec_2_minus_0,  intermediate_3);
    Toep_3x2x2x8(toep_p1,        vec_0_minus_1,  intermediate_4);
    Toep_3x2x2x8(toep_m1,        vec_1_minus_2,  intermediate_5);

    // Recombination
    for (uint16_t i=0; i<12*SIZE; i++){
        r[i          ] = intermediate_0[i] - intermediate_3[i] + intermediate_5[i];
        r[i + 12*SIZE] = intermediate_1[i] - intermediate_5[i] + intermediate_4[i];
        r[i + 24*SIZE] = intermediate_2[i] - intermediate_4[i] + intermediate_3[i]; 
    }

}

void Toep_3x2x2x8(uint16_t *toep, uint16_t *vec, uint16_t *r){
    // a is the anti-diagonal elements of a 96x96 toep, consists of 192 elements. (In fact 191 of 192 will be used)
    // b is the vector to be multiplied with, consists of 96 elements
    // r is the result vector

    uint16_t toep_m2[8*SIZE];
    uint16_t toep_m1[8*SIZE];
    uint16_t toep_0[8*SIZE];
    uint16_t toep_p1[8*SIZE];
    uint16_t toep_p2[8*SIZE];

    uint16_t toep_0_m1_m2[8*SIZE];
    uint16_t toep_p1_0_m1[8*SIZE];
    uint16_t toep_p2_p1_0[8*SIZE];

    uint16_t vec_0[4*SIZE];
    uint16_t vec_1[4*SIZE];
    uint16_t vec_2[4*SIZE];

    uint16_t vec_0_minus_1[4*SIZE];
    uint16_t vec_1_minus_2[4*SIZE];
    uint16_t vec_2_minus_0[4*SIZE];

    uint16_t intermediate_0[4*SIZE]={0};
    uint16_t intermediate_1[4*SIZE]={0};
    uint16_t intermediate_2[4*SIZE]={0};
    uint16_t intermediate_3[4*SIZE]={0};
    uint16_t intermediate_4[4*SIZE]={0};
    uint16_t intermediate_5[4*SIZE]={0};

    for (uint16_t i=0; i<8*SIZE; i++){
        // i=0,1,...,8xSIZE-1=63
        toep_p2[i]=toep[i          ];
        toep_p1[i]=toep[i +  4*SIZE];
        toep_0[i] =toep[i +  8*SIZE];
        toep_m1[i]=toep[i + 12*SIZE];
        toep_m2[i]=toep[i + 16*SIZE];

        toep_0_m1_m2[i] = toep_0[i] + toep_m1[i] + toep_m2[i];
        toep_p1_0_m1[i] = toep_p1[i] + toep_0[i] + toep_m1[i];
        toep_p2_p1_0[i] = toep_p2[i] + toep_p1[i] + toep_0[i];

    }

    for (uint16_t i=0; i<4*SIZE; i++) {
        vec_0[i] = vec[i         ];
        vec_1[i] = vec[i + 4*SIZE];
        vec_2[i] = vec[i + 8*SIZE];

        vec_0_minus_1[i] = vec_0[i] - vec_1[i];
        vec_1_minus_2[i] = vec_1[i] - vec_2[i];
        vec_2_minus_0[i] = vec_2[i] - vec_0[i];
    }

    Toep_2x2x8(toep_0_m1_m2,   vec_2,          intermediate_0);
    Toep_2x2x8(toep_p1_0_m1,   vec_1,          intermediate_1);
    Toep_2x2x8(toep_p2_p1_0,   vec_0,          intermediate_2);
    Toep_2x2x8(toep_0,         vec_2_minus_0,  intermediate_3);
    Toep_2x2x8(toep_p1,        vec_0_minus_1,  intermediate_4);
    Toep_2x2x8(toep_m1,        vec_1_minus_2,  intermediate_5);

    // Recombination
    for (uint16_t i=0; i<4*SIZE; i++){
        r[i         ] = intermediate_0[i] - intermediate_3[i] + intermediate_5[i];
        r[i + 4*SIZE] = intermediate_1[i] - intermediate_5[i] + intermediate_4[i];
        r[i + 8*SIZE] = intermediate_2[i] - intermediate_4[i] + intermediate_3[i]; 
    }


}

void Toep_2x2x8(uint16_t *toep, uint16_t *vec, uint16_t *r){
    // a is the anti-diagonal elements of a 32x32 toep, consists of 64 elements. (In fact 63 of 64 will be used)
    // b is the vector to be multiplied with, consists of 32 elements
    // r is the result vector

    // prepare the anti-diagonal elements of a 16x16 toep
    uint16_t toep_m1[ 4*SIZE ];
    uint16_t toep_0 [ 4*SIZE ];
    uint16_t toep_p1[ 4*SIZE ];

    uint16_t toep_0_m1[ 4*SIZE ];
    uint16_t toep_p1_0[ 4*SIZE ];

    uint16_t vec_0[ 2*SIZE ];
    uint16_t vec_1[ 2*SIZE ];
    uint16_t vec_1_minus_0[ 2*SIZE ];

    uint16_t intermdiate_0[ 2*SIZE ];
    uint16_t intermdiate_1[ 2*SIZE ];
    uint16_t intermdiate_2[ 2*SIZE ];

    for (uint16_t i=0; i<4*SIZE; i++){
        // i = 0, 1, ... 4*SIZE-1 = 31
        toep_p1[i] = toep[i         ];  // toep[0 - 31]
        toep_0 [i] = toep[i + 2*SIZE];  // toep[16 - 47]
        toep_m1[i] = toep[i + 4*SIZE];  // toep[32 - 63]

        toep_0_m1[i] = toep_0[i] + toep_m1[i];
        toep_p1_0[i] = toep_p1[i] + toep_0 [i];
    }


    for (uint16_t i=0; i<2*SIZE; i++){
        vec_0[i] = vec[         i];
        vec_1[i] = vec[2*SIZE + i];

        vec_1_minus_0[i] = vec_1[i] - vec_0[i];
    }




    Toep_2x8(toep_0_m1, vec_1,         intermdiate_0);
    Toep_2x8(toep_0,    vec_1_minus_0, intermdiate_1);
    Toep_2x8(toep_p1_0, vec_0,         intermdiate_2);


    // Recombination
    for (uint16_t i=0; i<2*SIZE; i++){
        r[i]        = intermdiate_0[i] - intermdiate_1[i];
        r[2*SIZE+i] = intermdiate_1[i] + intermdiate_2[i];
    }
}

void Toep_2x8(uint16_t *toep, uint16_t *vec, uint16_t *r){
    // a is the anti-diagonal elements of a 16x16 toep, consists of 64 elements. (In fact 31 of 32 will be used)
    // b is the vector to be multiplied with, consists of 16 elements
    // r is the result vector

    // prepare the anti-diagonal elements of a 8x8 toep
    uint16_t toep_m1[ 2*SIZE ];
    uint16_t toep_0 [ 2*SIZE ];
    uint16_t toep_p1[ 2*SIZE ];

    uint16_t toep_0_m1[ 2*SIZE ];
    uint16_t toep_p1_0[ 2*SIZE ];

    uint16_t vec_0[ SIZE ];
    uint16_t vec_1[ SIZE ];
    uint16_t vec_1_minus_0[ SIZE ];

    uint16_t intermdiate_0[ SIZE ];
    uint16_t intermdiate_1[ SIZE ];
    uint16_t intermdiate_2[ SIZE ];

    for (uint16_t i=0; i<2*SIZE; i++){
        // i = 0, 1, ... (2*SIZE)/2-1 = 31
        toep_p1[i] = toep[i         ];  // toep[0 - 31]
        toep_0 [i] = toep[i + 1*SIZE];  // toep[16 - 47]
        toep_m1[i] = toep[i + 2*SIZE];  // toep[32 - 63]

        toep_0_m1[i] = toep_0[i] + toep_m1[i];
        toep_p1_0[i] = toep_p1[i] + toep_0 [i];
    }

    // for (uint16_t i=0; i<2*SIZE; i++){
    //     printf("%d ", toep_m1[i]);
    // }
    // printf("\n");

    for (uint16_t i=0; i<SIZE; i++){
        vec_0[i] = vec[         i];
        vec_1[i] = vec[SIZE + i];

        vec_1_minus_0[i] = vec_1[i] - vec_0[i];
    }


    TMVP_8x8_on_8(toep_0_m1, vec_1,          intermdiate_0);
    TMVP_8x8_on_8(toep_0,    vec_1_minus_0,  intermdiate_1);
    TMVP_8x8_on_8(toep_p1_0, vec_0,          intermdiate_2);

    // Recombination
    for (uint16_t i=0; i<SIZE; i++){
        r[i]      = intermdiate_0[i] - intermdiate_1[i];
        r[SIZE+i] = intermdiate_1[i] + intermdiate_2[i];
    }
}

void TMVP_8x8_on_8   (uint16_t *toep, uint16_t *vec, uint16_t *r){
    uint16x8_t result_vector = vdupq_n_u16(0);
    uint16_t scalar;
    uint16x8_t toep_vector;

    scalar = vec[0];
    toep_vector = vld1q_u16(&toep[0]);
    result_vector = vmlaq_n_u16(result_vector, toep_vector, scalar);
    scalar = vec[1];
    toep_vector = vld1q_u16(&toep[1]);
    result_vector = vmlaq_n_u16(result_vector, toep_vector, scalar);
    scalar = vec[2];
    toep_vector = vld1q_u16(&toep[2]);
    result_vector = vmlaq_n_u16(result_vector, toep_vector, scalar);
    scalar = vec[3];
    toep_vector = vld1q_u16(&toep[3]);
    result_vector = vmlaq_n_u16(result_vector, toep_vector, scalar);
    scalar = vec[4];
    toep_vector = vld1q_u16(&toep[4]);
    result_vector = vmlaq_n_u16(result_vector, toep_vector, scalar);
    scalar = vec[5];
    toep_vector = vld1q_u16(&toep[5]);
    result_vector = vmlaq_n_u16(result_vector, toep_vector, scalar);
    scalar = vec[6];
    toep_vector = vld1q_u16(&toep[6]);
    result_vector = vmlaq_n_u16(result_vector, toep_vector, scalar);
    scalar = vec[7];
    toep_vector = vld1q_u16(&toep[7]);
    result_vector = vmlaq_n_u16(result_vector, toep_vector, scalar);

    uint16_t r_temp[SIZE];

    vst1q_u16(r_temp, result_vector);
    for (uint16_t i=0; i<SIZE; i++){
        r[i] = r_temp[(SIZE - 1) - i];
    }
}
