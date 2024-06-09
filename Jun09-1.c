#include <stdio.h>
#include <arm_neon.h>

uint16_t TM[8] =   {1, 2, 3, 4, 5, 6, 7, 8};
uint16_t b[8] =     {2, 3, 4, 5, 6, 7, 8, 9};
//uint16_t b[8] =     {1, 0, 0, 0, 0, 0, 0, 0};

uint16_t result[8] = {0, 0, 0, 0, 0, 0, 0, 0};

int main() {
    
    uint16x8_t vector3 = vld1q_u16(result);
    u_int16_t scalar;
    uint16x8_t vector1;

    for (uint16_t i=0; i<8; i++){

        // Create a temporary array with TM repeated twice
        uint16_t temp_array[16];
        for (uint16_t i = 0; i < 8; i++) {
            temp_array[i] = TM[i];
            temp_array[i + 8] = TM[i];
        }
        // temp_array = TM || TM


        // Load vectors
        scalar = b[i];


        vector1 = vld1q_u16(&temp_array[7-i]);


        // Perform multiply-accumulate operation
        vector3 = vmlaq_n_u16(vector3, vector1, scalar);



    }





    // Store the result in an array
    uint16_t result_array[8];
    vst1q_u16(result_array, vector3);

    // Print each element of the result array
    for (int i = 0; i < 8; i++) {
        printf("%u ", result_array[i]);
    }

    printf("\n");
    return 0;
}
