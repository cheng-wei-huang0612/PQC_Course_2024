#include "poly_Rq_mul.h"

void Toep_3x3x3x2x2x8(uint16x8_t *toep, uint16x8_t *vec, uint16x8_t *r);
void Toep_3x3x2x2x8  (uint16x8_t *toep, uint16x8_t *vec, uint16x8_t *r);
void Toep_3x2x2x8    (uint16x8_t *toep, uint16x8_t *vec, uint16x8_t *r);
void Toep_2x2x8      (uint16x8_t *toep, uint16x8_t *vec, uint16x8_t *r);
void Toep_2x8        (uint16x8_t *toep, uint16x8_t *vec, uint16x8_t *r);
void TMVP_8x8_on_8   (uint16x8_t *toep, uint16x8_t *vec, uint16x8_t *r);

void poly_Rq_mul(poly *r, poly *a, poly *b) {
    uint16_t toep_a[216*SIZE] = {0};
    uint16_t vec_b [108*SIZE] = {0};
    uint16_t result[108*SIZE];

    // Convert coefficients of a into the anti-diagonal of 32x32 Toep matrix:
    // toep_a = {0, ...(43)..., 0, a_820, ..., a_1, a_0, a_820, ..., a_1, a_0, 0, ...(43)..., 0}
    // vec_b = (b_0, ..., b_820, 0, ...(43)..., 0)
    for (uint16_t i=0; i < NTRU_N; i++){
        toep_a[108*SIZE - 1          - i] = a->coeffs[i];
        toep_a[108*SIZE - 1 + NTRU_N - i] = a->coeffs[i];
        vec_b[i] = b->coeffs[i];
    }

    uint16x8_t xtoep_a[216];
    uint16x8_t xvec_b [108];
    uint16x8_t xresult[108];
    // Convert into uint16x8_t for neon intrinsics optimization
    for (uint16_t i=0; i < 108; i++){
        xtoep_a[i      ] = vld1q_u16(&toep_a[i * SIZE             ]);
        xtoep_a[i + 108] = vld1q_u16(&toep_a[i * SIZE + 108 * SIZE]);
        xvec_b[i] = vld1q_u16(&vec_b[i * SIZE]);
    }

    // perform the multiplication
    Toep_3x3x3x2x2x8(xtoep_a, xvec_b, xresult);

    // Convert back to uint16_t coefficients
    for (uint16_t i=0; i < 108; i++){
        vst1q_u16(&result[i * SIZE], xresult[i]);
    }

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

void Toep_3x3x3x2x2x8(uint16x8_t *toep, uint16x8_t *vec, uint16x8_t *r){
    // a is the anti-diagonal elements of a 108 SIZE x 108 SIZE toep, consists of 216 SIZE elements. (In fact the last one is of no use)
    // b is the vector to be multiplied with, consists of 108 SIZE elements
    // r is the result vector

    uint16x8_t toep_m2[72];
    uint16x8_t toep_m1[72];
    uint16x8_t toep_0 [72];
    uint16x8_t toep_p1[72];
    uint16x8_t toep_p2[72];

    uint16x8_t toep_0_m1_m2[72];
    uint16x8_t toep_p1_0_m1[72];
    uint16x8_t toep_p2_p1_0[72];

    uint16x8_t vec_0[36];
    uint16x8_t vec_1[36];
    uint16x8_t vec_2[36];

    uint16x8_t vec_0_minus_1[36];
    uint16x8_t vec_1_minus_2[36];
    uint16x8_t vec_2_minus_0[36];

    uint16x8_t intermediate_0[36]={0};
    uint16x8_t intermediate_1[36]={0};
    uint16x8_t intermediate_2[36]={0};
    uint16x8_t intermediate_3[36]={0};
    uint16x8_t intermediate_4[36]={0};
    uint16x8_t intermediate_5[36]={0};

    // Block Matrix form of Toeplitz matrix
    for (uint16_t i=0; i<72; i++){
        // i=0,1,...,72xSIZE-1
        toep_p2[i] = toep[i     ];
        toep_p1[i] = toep[i + 36];
        toep_0 [i] = toep[i + 72];
        toep_m1[i] = toep[i + 108];
        toep_m2[i] = toep[i + 144];

        toep_0_m1_m2[i] = vaddq_u16(toep_0 [i], vaddq_u16(toep_m1[i], toep_m2[i]));
        toep_p1_0_m1[i] = vaddq_u16(toep_p1[i], vaddq_u16(toep_0 [i], toep_m1[i]));
        toep_p2_p1_0[i] = vaddq_u16(toep_p2[i], vaddq_u16(toep_p1[i], toep_0 [i]));
    }

    for (uint16_t i=0; i<36; i++) {
        vec_0[i] = vec[i     ];
        vec_1[i] = vec[i + 36];
        vec_2[i] = vec[i + 72];

        vec_0_minus_1[i] = vsubq_u16(vec_0[i], vec_1[i]);
        vec_1_minus_2[i] = vsubq_u16(vec_1[i], vec_2[i]);
        vec_2_minus_0[i] = vsubq_u16(vec_2[i], vec_0[i]);
    }

    Toep_3x3x2x2x8(toep_0_m1_m2,   vec_2,          intermediate_0);
    Toep_3x3x2x2x8(toep_p1_0_m1,   vec_1,          intermediate_1);
    Toep_3x3x2x2x8(toep_p2_p1_0,   vec_0,          intermediate_2);
    Toep_3x3x2x2x8(toep_0,         vec_2_minus_0,  intermediate_3);
    Toep_3x3x2x2x8(toep_p1,        vec_0_minus_1,  intermediate_4);
    Toep_3x3x2x2x8(toep_m1,        vec_1_minus_2,  intermediate_5);

    // Recombination
    for (uint16_t i=0; i<36; i++){
        r[i     ] = vsubq_u16(intermediate_0[i], vsubq_u16(intermediate_3[i], intermediate_5[i])); 
        r[i + 36] = vsubq_u16(intermediate_1[i], vsubq_u16(intermediate_5[i], intermediate_4[i])); 
        r[i + 72] = vsubq_u16(intermediate_2[i], vsubq_u16(intermediate_4[i], intermediate_3[i])); 
    }
}

void Toep_3x3x2x2x8(uint16x8_t *toep, uint16x8_t *vec, uint16x8_t *r){
    // a is the anti-diagonal elements of a 36 SIZE x 36 SIZE toep, consists of 72 SIZE elements. (In fact the last one is of no use)
    // b is the vector to be multiplied with, consists of 36 SIZE elements
    // r is the result vector

    uint16x8_t toep_m2[24];
    uint16x8_t toep_m1[24];
    uint16x8_t toep_0 [24];
    uint16x8_t toep_p1[24];
    uint16x8_t toep_p2[24];

    uint16x8_t toep_0_m1_m2[24];
    uint16x8_t toep_p1_0_m1[24];
    uint16x8_t toep_p2_p1_0[24];

    uint16x8_t vec_0[12];
    uint16x8_t vec_1[12];
    uint16x8_t vec_2[12];

    uint16x8_t vec_0_minus_1[12];
    uint16x8_t vec_1_minus_2[12];
    uint16x8_t vec_2_minus_0[12];

    uint16x8_t intermediate_0[12]={0};
    uint16x8_t intermediate_1[12]={0};
    uint16x8_t intermediate_2[12]={0};
    uint16x8_t intermediate_3[12]={0};
    uint16x8_t intermediate_4[12]={0};
    uint16x8_t intermediate_5[12]={0};

    // Block Matrix form of Toeplitz matrix
    for (uint16_t i=0; i<24; i++){
        // i=0,1,...,72xSIZE-1
        toep_p2[i] = toep[i     ];
        toep_p1[i] = toep[i + 12];
        toep_0 [i] = toep[i + 24];
        toep_m1[i] = toep[i + 36];
        toep_m2[i] = toep[i + 48];

        toep_0_m1_m2[i] = vaddq_u16(toep_0 [i], vaddq_u16(toep_m1[i], toep_m2[i]));
        toep_p1_0_m1[i] = vaddq_u16(toep_p1[i], vaddq_u16(toep_0 [i], toep_m1[i]));
        toep_p2_p1_0[i] = vaddq_u16(toep_p2[i], vaddq_u16(toep_p1[i], toep_0 [i]));
    }

    for (uint16_t i=0; i<12; i++) {
        vec_0[i] = vec[i     ];
        vec_1[i] = vec[i + 12];
        vec_2[i] = vec[i + 24];

        vec_0_minus_1[i] = vsubq_u16(vec_0[i], vec_1[i]);
        vec_1_minus_2[i] = vsubq_u16(vec_1[i], vec_2[i]);
        vec_2_minus_0[i] = vsubq_u16(vec_2[i], vec_0[i]);
    }

    Toep_3x2x2x8(toep_0_m1_m2,   vec_2,          intermediate_0);
    Toep_3x2x2x8(toep_p1_0_m1,   vec_1,          intermediate_1);
    Toep_3x2x2x8(toep_p2_p1_0,   vec_0,          intermediate_2);
    Toep_3x2x2x8(toep_0,         vec_2_minus_0,  intermediate_3);
    Toep_3x2x2x8(toep_p1,        vec_0_minus_1,  intermediate_4);
    Toep_3x2x2x8(toep_m1,        vec_1_minus_2,  intermediate_5);

    // Recombination
    for (uint16_t i=0; i<12; i++){
        r[i     ] = vsubq_u16(intermediate_0[i], vsubq_u16(intermediate_3[i], intermediate_5[i])); 
        r[i + 12] = vsubq_u16(intermediate_1[i], vsubq_u16(intermediate_5[i], intermediate_4[i])); 
        r[i + 24] = vsubq_u16(intermediate_2[i], vsubq_u16(intermediate_4[i], intermediate_3[i])); 
    }
}

void Toep_3x2x2x8(uint16x8_t *toep, uint16x8_t *vec, uint16x8_t *r){
    // a is the anti-diagonal elements of a 96x96 toep, consists of 192 elements. (In fact 191 of 192 will be used)
    // b is the vector to be multiplied with, consists of 96 elements
    // r is the result vector

    uint16x8_t toep_m2[8];
    uint16x8_t toep_m1[8];
    uint16x8_t toep_0 [8];
    uint16x8_t toep_p1[8];
    uint16x8_t toep_p2[8];

    uint16x8_t toep_0_m1_m2[8];
    uint16x8_t toep_p1_0_m1[8];
    uint16x8_t toep_p2_p1_0[8];

    uint16x8_t vec_0[4];
    uint16x8_t vec_1[4];
    uint16x8_t vec_2[4];

    uint16x8_t vec_0_minus_1[4];
    uint16x8_t vec_1_minus_2[4];
    uint16x8_t vec_2_minus_0[4];

    uint16x8_t intermediate_0[4]={0};
    uint16x8_t intermediate_1[4]={0};
    uint16x8_t intermediate_2[4]={0};
    uint16x8_t intermediate_3[4]={0};
    uint16x8_t intermediate_4[4]={0};
    uint16x8_t intermediate_5[4]={0};

    // Block Matrix form of Toeplitz matrix
    for (uint16_t i=0; i<8; i++){
        // i=0,1,...,72xSIZE-1
        toep_p2[i] = toep[i     ];
        toep_p1[i] = toep[i +  4];
        toep_0 [i] = toep[i +  8];
        toep_m1[i] = toep[i + 12];
        toep_m2[i] = toep[i + 16];

        toep_0_m1_m2[i] = vaddq_u16(toep_0 [i], vaddq_u16(toep_m1[i], toep_m2[i]));
        toep_p1_0_m1[i] = vaddq_u16(toep_p1[i], vaddq_u16(toep_0 [i], toep_m1[i]));
        toep_p2_p1_0[i] = vaddq_u16(toep_p2[i], vaddq_u16(toep_p1[i], toep_0 [i]));
    }

    for (uint16_t i=0; i<4; i++) {
        vec_0[i] = vec[i    ];
        vec_1[i] = vec[i + 4];
        vec_2[i] = vec[i + 8];

        vec_0_minus_1[i] = vsubq_u16(vec_0[i], vec_1[i]);
        vec_1_minus_2[i] = vsubq_u16(vec_1[i], vec_2[i]);
        vec_2_minus_0[i] = vsubq_u16(vec_2[i], vec_0[i]);
    }

    Toep_2x2x8(toep_0_m1_m2,   vec_2,          intermediate_0);
    Toep_2x2x8(toep_p1_0_m1,   vec_1,          intermediate_1);
    Toep_2x2x8(toep_p2_p1_0,   vec_0,          intermediate_2);
    Toep_2x2x8(toep_0,         vec_2_minus_0,  intermediate_3);
    Toep_2x2x8(toep_p1,        vec_0_minus_1,  intermediate_4);
    Toep_2x2x8(toep_m1,        vec_1_minus_2,  intermediate_5);

    // Recombination
    for (uint16_t i=0; i<4; i++){
        r[i    ] = vsubq_u16(intermediate_0[i], vsubq_u16(intermediate_3[i], intermediate_5[i])); 
        r[i + 4] = vsubq_u16(intermediate_1[i], vsubq_u16(intermediate_5[i], intermediate_4[i])); 
        r[i + 8] = vsubq_u16(intermediate_2[i], vsubq_u16(intermediate_4[i], intermediate_3[i])); 
    }
}

void Toep_2x2x8(uint16x8_t *toep, uint16x8_t *vec, uint16x8_t *r){
    // a is the anti-diagonal elements of a 32x32 toep, consists of 64 elements. (In fact 63 of 64 will be used)
    // b is the vector to be multiplied with, consists of 32 elements
    // r is the result vector

    // prepare the anti-diagonal elements of a 16x16 toep
    uint16x8_t toep_m1[ 4 ];
    uint16x8_t toep_0 [ 4 ];
    uint16x8_t toep_p1[ 4 ];

    uint16x8_t toep_0_m1[ 4 ];
    uint16x8_t toep_p1_0[ 4 ];

    uint16x8_t vec_0[ 2 ];
    uint16x8_t vec_1[ 2 ];
    uint16x8_t vec_1_minus_0[ 2 ];

    uint16x8_t intermediate_0[ 2 ];
    uint16x8_t intermediate_1[ 2 ];
    uint16x8_t intermediate_2[ 2 ];

    for (uint16_t i=0; i<4; i++){
        // i = 0, 1, ... 4*SIZE-1 = 31
        toep_p1[i] = toep[i    ];  // toep[0 - 31]
        toep_0 [i] = toep[i + 2];  // toep[16 - 47]
        toep_m1[i] = toep[i + 4];  // toep[32 - 63]

        toep_0_m1[i] = vaddq_u16(toep_0 [i], toep_m1[i]);
        toep_p1_0[i] = vaddq_u16(toep_p1[i], toep_0 [i]);
    }


    for (uint16_t i=0; i<2; i++){
        vec_0[i] = vec[    i];
        vec_1[i] = vec[2 + i];

        vec_1_minus_0[i] = vec_1[i] - vec_0[i];
        vec_1_minus_0[i] = vsubq_u16(vec_1[i], vec_0[i]);
    }




    Toep_2x8(toep_0_m1, vec_1,         intermediate_0);
    Toep_2x8(toep_0,    vec_1_minus_0, intermediate_1);
    Toep_2x8(toep_p1_0, vec_0,         intermediate_2);


    // Recombination
    for (uint16_t i=0; i<2; i++){
        r[    i] = vsubq_u16(intermediate_0[i], intermediate_1[i]);
        r[2 + i] = vaddq_u16(intermediate_1[i], intermediate_2[i]);
    }
}

void Toep_2x8(uint16x8_t *toep, uint16x8_t *vec, uint16x8_t *r){
    // a is the anti-diagonal elements of a 16x16 toep, consists of 64 elements. (In fact 31 of 32 will be used)
    // b is the vector to be multiplied with, consists of 16 elements
    // r is the result vector

    // prepare the anti-diagonal elements of a 8x8 toep
    uint16x8_t toep_m1[ 2 ];
    uint16x8_t toep_0 [ 2 ];
    uint16x8_t toep_p1[ 2 ];

    uint16x8_t toep_0_m1[ 2 ];
    uint16x8_t toep_p1_0[ 2 ];

    uint16x8_t vec_0;
    uint16x8_t vec_1;
    uint16x8_t vec_1_minus_0;

    uint16x8_t intermediate_0;
    uint16x8_t intermediate_1;
    uint16x8_t intermediate_2;

    for (uint16_t i=0; i<2; i++){
        // i = 0, 1, ... (2*SIZE)/2-1 = 31
        toep_p1[i] = toep[i    ];  // toep[0 - 31]
        toep_0 [i] = toep[i + 1];  // toep[16 - 47]
        toep_m1[i] = toep[i + 2];  // toep[32 - 63]

        toep_0_m1[i] = vaddq_u16(toep_0 [i], toep_m1[i]);
        toep_p1_0[i] = vaddq_u16(toep_p1[i], toep_0 [i]);
    }

    // for (uint16_t i=0; i<2*SIZE; i++){
    //     printf("%d ", toep_m1[i]);
    // }
    // printf("\n");

    vec_0 = vec[0];
    vec_1 = vec[1];
    vec_1_minus_0 = vsubq_u16(vec_1, vec_0);


    TMVP_8x8_on_8(toep_0_m1, &vec_1,          &intermediate_0);
    TMVP_8x8_on_8(toep_0,    &vec_1_minus_0,  &intermediate_1);
    TMVP_8x8_on_8(toep_p1_0, &vec_0,          &intermediate_2);

    // Recombination
    r[0] = vsubq_u16(intermediate_0, intermediate_1);
    r[1] = vaddq_u16(intermediate_1, intermediate_2);
}

void TMVP_8x8_on_8(uint16x8_t *toep, uint16x8_t *vec, uint16x8_t *r){
    *r = vdupq_n_u16(0);
    uint16_t scalar;
    uint16x8_t toep_0 = toep[0];
    uint16x8_t toep_1 = toep[1];
    uint16x8_t toep_v;

    scalar = (*vec)[0];
    toep_v = vextq_u16(toep_0, toep_1, 0);
    *r = vmlaq_n_u16(*r, toep_v, scalar);
    scalar = (*vec)[1];
    toep_v = vextq_u16(toep_0, toep_1, 1);
    *r = vmlaq_n_u16(*r, toep_v, scalar);
    scalar = (*vec)[2];
    toep_v = vextq_u16(toep_0, toep_1, 2);
    *r = vmlaq_n_u16(*r, toep_v, scalar);
    scalar = (*vec)[3];
    toep_v = vextq_u16(toep_0, toep_1, 3);
    *r = vmlaq_n_u16(*r, toep_v, scalar);
    scalar = (*vec)[4];
    toep_v = vextq_u16(toep_0, toep_1, 4);
    *r = vmlaq_n_u16(*r, toep_v, scalar);
    scalar = (*vec)[5];
    toep_v = vextq_u16(toep_0, toep_1, 5);
    *r = vmlaq_n_u16(*r, toep_v, scalar);
    scalar = (*vec)[6];
    toep_v = vextq_u16(toep_0, toep_1, 6);
    *r = vmlaq_n_u16(*r, toep_v, scalar);
    scalar = (*vec)[7];
    toep_v = vextq_u16(toep_0, toep_1, 7);
    *r = vmlaq_n_u16(*r, toep_v, scalar);

    // Reverse to get the correct result
    *r = vrev64q_u16(*r);
    *r = vextq_u16(*r, *r, 4);

    //for (int i=0; i<8; i++){printf("%5d %5d %5d %5d\n",toep[0][i], toep[1][i], (*vec)[i], (*r)[i]);}printf("\n");
}
