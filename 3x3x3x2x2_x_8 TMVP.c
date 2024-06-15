#include <stdio.h>
#include <arm_neon.h>


// Define the size of the arrays
#define SIZE 8

uint16_t a[108*SIZE] = {187,42,21,59,174,9,98,3,93,153,20,52,15,117,186,148,155,26,134,164,200,100,173,175,162,79,80,85,99,135,60,150,99,55,18,38,193,151,43,15,86,98,88,79,147,95,112,21,68,188,154,3,137,77,146,11,13,91,110,134,45,74,52,33,14,11,15,95,193,138,160,143,4,125,129,127,55,75,33,109,118,108,92,173,98,120,132,91,177,34,186,82,75,101,51,126,19,60,53,194,79,49,141,140,15,178,9,192,83,6,139,189,120,58,187,56,121,189,177,127,96,197,80,87,182,104,52,183,61,82,92,106,35,114,167,85,180,26,65,88,53,172,99,114,78,179,154,120,127,171,76,198,187,139,75,137,197,179,84,104,31,56,85,152,193,53,119,159,4,78,26,121,16,137,25,26,68,67,121,200,81,32,156,11,34,92,83,136,0,45,9,134,60,158,44,171,90,155,172,55,62,139,185,191,0,41,36,161,74,162,62,159,7,196,93,178,190,170,57,135,63,162,115,162,108,168,13,1,159,190,2,111,62,127,122,190,12,185,165,23,154,23,109,35,30,101,37,134,40,93,58,23,61,28,73,162,78,165,151,193,73,95,70,162,105,7,35,65,131,90,187,55,0,26,105,15,6,159,108,89,126,50,190,65,109,26,157,135,118,180,145,14,94,2,153,26,7,88,81,97,22,63,56,49,115,36,6,96,148,117,140,73,52,170,100,151,155,113,71,115,136,196,157,42,57,53,143,95,94,51,23,96,145,5,112,186,70,188,58,168,16,135,171,169,58,130,92,29,131,110,15,159,182,140,27,177,81,37,70,141,37,123,95,52,111,39,35,184,60,164,23,114,96,123,73,10,130,57,94,150,122,183,80,16,68,61,135,85,119,86,187,109,154,1,173,48,85,85,181,2,73,32,32,137,91,72,31,100,14,185,58,113,84,170,11,80,75,128,16,172,20,146,78,92,165,69,105,160,54,195,58,156,30,133,89,62,56,87,60,80,67,195,30,180,186,42,119,147,144,116,158,174,132,55,115,147,129,96,26,157,172,97,100,63,39,160,45,144,49,86,12,45,116,171,174,93,163,22,89,89,113,66,23,127,111,97,79,84,75,147,178,44,42,194,30,27,43,62,98,52,95,117,122,133,14,198,110,179,68,10,44,157,91,181,66,110,77,37,175,185,148,96,53,149,75,175,27,100,101,26,25,38,131,22,34,196,15,154,109,102,126,143,61,132,86,60,168,147,78,126,16,67,58,40,8,132,98,125,155,34,160,118,127,76,194,86,198,180,145,17,75,152,21,76,106,40,186,56,28,46,198,189,84,175,46,161,41,3,192,4,155,15,5,13,22,2,131,9,1,59,36,12,33,88,75,100,16,120,45,135,5,154,44,43,174,164,17,46,100,92,155,6,162,38,139,195,195,196,118,110,184,21,199,75,59,14,122,68,78,184,187,18,141,173,15,120,180,27,107,196,131,161,76,25,120,92,161,168,109,48,179,106,137,199,92,61,38,59,60,181,180,200,171,162,32,171,166,48,100,70,46,50,53,177,36,53,184,150,137,161,132,91,32,45,47,6,27,74,179,114,200,39,158,139,53,121,59,184,27,109,36,132,94,22,136,160,130,18,10,87,96,28,117,108,41,164,166,181,177,173,189,62,118,70,97,52,92,60,10,153,37,15,158,66,34,145,56,21,38,116,104,101,47,183,153,14,92,32,86,147,150,10,134,67,18,198,179,149,188,196,100,107,170,196,36,173,40,51,43,163,90,161,106,22,84,108,22,19,164,96,69,112,50,72,1,191,178,90,115,196,186,150,66,153,154,142,7,169,198,72,31,127,52,180,113,170,188,27,185,123,161,151,150,89,91,138,84,94,172,3,197,49,95,66,107,14,36,164,71,52,76,155,104,158,118,14,85,88,45,100,160,167,40,76,192,54,150,167,27,144,80,167,195,62};
uint16_t b[108*SIZE] = {181,3,177,183,51,136,175,184,183,174,149,106,182,41,40,33,122,55,92,28,153,85,123,174,54,28,197,126,156,155,66,113,103,113,12,93,143,149,91,166,47,19,179,191,90,182,15,75,123,171,138,177,87,57,157,107,61,2,5,124,6,186,192,147,145,159,122,134,114,149,39,158,200,188,33,96,12,50,192,175,129,26,18,25,127,174,46,159,193,200,37,192,85,17,41,153,43,113,184,100,175,51,138,33,86,107,173,146,0,190,37,121,73,30,156,73,50,89,73,0,155,42,91,195,194,19,124,2,150,48,48,1,144,61,15,118,46,75,68,24,98,11,9,163,37,12,154,93,133,87,70,25,139,37,19,53,102,101,20,89,45,49,57,153,68,41,135,11,147,180,4,77,190,12,22,84,33,8,23,135,54,147,156,59,130,125,102,70,161,31,48,192,190,37,36,187,137,14,2,71,149,116,41,40,95,134,118,86,165,190,130,49,87,173,30,185,194,92,103,123,8,70,86,162,40,8,117,137,157,15,115,177,68,153,128,70,120,76,196,127,41,92,107,90,68,17,0,141,1,189,70,129,1,56,183,106,91,95,136,87,123,193,87,152,101,35,104,64,139,56,27,26,30,155,110,151,82,7,87,8,196,98,66,84,41,30,28,107,67,200,110,52,98,25,66,176,52,30,125,114,143,90,184,200,27,151,101,125,22,1,188,36,156,176,60,35,3,129,22,174,129,81,159,197,164,37,17,38,84,50,160,57,146,59,70,121,72,108,41,87,198,58,67,12,43,102,102,176,104,190,0,31,88,44,54,100,100,18,34,40,122,35,135,126,38,135,155,21,85,187,161,143,197,99,28,42,55,47,193,143,1,108,173,133,96,43,13,70,6,87,119,35,55,10,112,54,199,106,183,43,49,120,87,112,90,91,196,81,71,164,139,197,29,188,82,100,148,160,2,156,104,158,113,111,49,147,200,189,15,5,58,25,100,60,12,141,181,99,83,147,148,94,12,65,9,94,156,18,119,189,144,87,72,114,99,200,54,49,99,147,59,118,85,4,127,192,55,169,89,136,103,145,10,91,178,111,123,127,56,165,7,72,73,43,196,159,158,94,159,76,99,96,172,102,191,44,183,35,63,31,40,62,151,37,39,76,128,193,122,107,39,112,7,84,70,60,189,33,121,81,186,199,40,121,108,61,80,56,56,77,48,172,157,193,46,45,74,110,52,67,186,176,17,34,85,193,188,106,199,45,196,133,79,145,47,172,105,46,77,126,195,108,27,124,102,46,45,121,116,178,131,192,27,197,168,42,170,192,97,4,149,5,140,181,187,194,142,20,105,40,104,12,57,16,62,33,120,42,171,134,161,25,52,44,38,193,112,156,46,135,32,198,178,5,182,108,148,49,2,155,43,59,144,167,64,76,82,39,193,162,42,18,100,64,4,112,69,175,148,100,157,37,158,191,45,35,148,69,44,180,1,126,181,139,53,115,103,101,188,113,145,165,81,81,160,77,127,63,154,184,133,5,109,107,6,95,152,90,93,54,119,69,28,40,65,178,199,64,28,66,178,167,174,37,19,129,75,177,33,114,141,8,197,168,54,191,73,30,115,107,199,160,95,149,20,117,65,110,33,83,50,131,175,178,149,99,122,192,36,66,118,81,194,114,135,131,58,21,3,28,71,123,105,110,96,152,15,15,56,98,4,53,41,136,45,132,111,146,128,72,156,25,28,8,80,59,85,103,46,3,111,71,28,2,116,153,99,88,24,96,117,163,192,151,200,100,86,75,99,51,93,20,7,145,102,4,2,193,25,80,84,14,28,94,198,41,173,53,81,4,151,145,104,24,63,183,31,173,47,24,37,160,123,165,132,36,18,8,61,145,145,33,123,16,54,164,170,44,45,97,62,87,94,150,191,161,136,103,172,40,28,156,69,43,48,3,110,67,173,185,173,1,117,26};

uint16_t result[108*SIZE] = {0};

void Toep_3x3x3x2x2x8(uint16_t *toep, uint16_t *vec, uint16_t *r);
void Toep_3x3x2x2x8(uint16_t *toep, uint16_t *vec, uint16_t *r);
void Toep_3x2x2x8(uint16_t *toep, uint16_t *vec, uint16_t *r);
void Toep_2x2x8(uint16_t *toep, uint16_t *vec, uint16_t *r);
void Toep_2x8(uint16_t *toep, uint16_t *vec, uint16_t *r);
void TMVP_8x8_on_8( uint16_t *toep, uint16_t *vec, uint16_t *r);

int main() {
    // Convert coefficients of a into the anti-diagonal of 32x32 Toep matrix:
    uint16_t toep_a[216*SIZE];

    for (uint16_t i=0; i<108*SIZE; i++){
        toep_a[i           ] = a[108*SIZE - 1 - i];
        toep_a[i + 108*SIZE] = a[108*SIZE - 1 - i];
    }
    // toep_a = {a_n-1, ..., a_1, a_0, a_n-1, ..., a_1, a_0} the last a_0 is of no use.

    // Perform the main function

    Toep_3x3x3x2x2x8(toep_a, b, result);

    // Reduction
    for (uint16_t i=0; i<108*SIZE; i++){
        result[i] = result[i] % 4096;
    }

    // print the result
    printf("the result is:\n[");
    for (uint16_t i=0; i<108*SIZE; i++){
        printf("%d, ", result[i]);
    }
    printf("\b\b]");


    return 0;
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

        toep_0_m1_m2[i] = toep_0[i] + toep_m1[i] + toep_m2[i];
        toep_p1_0_m1[i] = toep_p1[i] + toep_0[i] + toep_m1[i];
        toep_p2_p1_0[i] = toep_p2[i] + toep_p1[i] + toep_0[i];

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
        r[i]        = intermdiate_0[i] - intermdiate_1[i];
        r[SIZE+i] = intermdiate_1[i] + intermdiate_2[i];
    }
}

void TMVP_8x8_on_8(uint16_t *toep, uint16_t *vec, uint16_t *r){
    // a is the anti-diagonal elements of a toep, consists of 15 elements.
    // b is the vector to be multiplied with
    // r is the result vector

    uint16x8_t result_vector = vdupq_n_u16(0);
    u_int16_t scalar;
    uint16x8_t toep_vector;



    for (uint16_t i=0; i<SIZE; i++){

        scalar = vec[i];
        // Load vectors
        toep_vector = vld1q_u16(&toep[i]);

        // Perform multiply-accumulate operation
        result_vector = vmlaq_n_u16(result_vector, toep_vector, scalar);

    }

    uint16_t r_temp[SIZE];
    vst1q_u16(r_temp, result_vector);

    // 我怎麼想也不知道 result_vector 要 倒序 才會是我們要的
    for (uint16_t i=0; i<SIZE; i++){
        r[i] = r_temp[(SIZE - 1) - i];
    }


}
