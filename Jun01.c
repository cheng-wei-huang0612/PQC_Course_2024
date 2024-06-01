#include<stdio.h>
#include<math.h>

int main() {
    u_int16_t A[4] = {2,2,3,4}; //1 + 2x + 3x^2 + 4x^3
    u_int16_t B[4] = {5,6,7,1};

    const int n = 4;
    const int omega[4] = {1, 4, 16, 13}; //store the omegas, 4^0, 4^1, 4^2, 4^3, respectively. omega^ij = omega[i*j]
    u_int16_t inverse_omega[4] = {1, 13, 16, 4}; // omega^{-i*j} = inverse_omega[i*j]

    
    u_int16_t C[4]; //expected: 6, 10, 2, 2 (i.e., 6 + 10x + 2x^2 + 2x^3 )

// Multiplication started:

//NTT forward

    u_int16_t NTT_A[4];
    u_int16_t NTT_B[4];
    u_int16_t NTT_C[4];

    NTT_A[0] = omega[(0 * 0)%4 ]*A[0] + omega[(0 * 1) % 4]*A[1] + omega[(0 * 2) % 4]*A[2] + omega[(0 * 3) % 4]*A[3];
    NTT_A[1] = omega[(1 * 0)%4 ]*A[0] + omega[(1 * 1) % 4]*A[1] + omega[(1 * 2) % 4]*A[2] + omega[(1 * 3) % 4]*A[3];
    NTT_A[2] = omega[(2 * 0)%4 ]*A[0] + omega[(2 * 1) % 4]*A[1] + omega[(2 * 2) % 4]*A[2] + omega[(2 * 3) % 4]*A[3];
    NTT_A[3] = omega[(3 * 0)%4 ]*A[0] + omega[(3 * 1) % 4]*A[1] + omega[(3 * 2) % 4]*A[2] + omega[(3 * 3) % 4]*A[3];

        //Reduction
    NTT_A[0] = NTT_A[0]%17;
    NTT_A[1] = NTT_A[1]%17;
    NTT_A[2] = NTT_A[2]%17;
    NTT_A[3] = NTT_A[3]%17;

    printf("NTT_A is [%d, %d, %d, %d]", NTT_A[0], NTT_A[1], NTT_A[2], NTT_A[3]);

    NTT_B[0] = omega[(0 * 0)%4 ]*B[0] + omega[(0 * 1) % 4]*B[1] + omega[(0 * 2) % 4]*B[2] + omega[(0 * 3) % 4]*B[3];
    NTT_B[1] = omega[(1 * 0)%4 ]*B[0] + omega[(1 * 1) % 4]*B[1] + omega[(1 * 2) % 4]*B[2] + omega[(1 * 3) % 4]*B[3];
    NTT_B[2] = omega[(2 * 0)%4 ]*B[0] + omega[(2 * 1) % 4]*B[1] + omega[(2 * 2) % 4]*B[2] + omega[(2 * 3) % 4]*B[3];
    NTT_B[3] = omega[(3 * 0)%4 ]*B[0] + omega[(3 * 1) % 4]*B[1] + omega[(3 * 2) % 4]*B[2] + omega[(3 * 3) % 4]*B[3];

        //Reduction
    NTT_B[0] = NTT_B[0]%17;
    NTT_B[1] = NTT_B[1]%17;
    NTT_B[2] = NTT_B[2]%17;
    NTT_B[3] = NTT_B[3]%17;

    printf("NTT_B is [%d, %d, %d, %d]", NTT_B[0], NTT_B[1], NTT_B[2], NTT_B[3]);


    //component-wise multiplication

    NTT_C[0] = NTT_A[0]*NTT_B[0];
    NTT_C[1] = NTT_A[1]*NTT_B[1];
    NTT_C[2] = NTT_A[2]*NTT_B[2];
    NTT_C[3] = NTT_A[3]*NTT_B[3];
    
            //Reduction
    NTT_C[0] = NTT_C[0]%17;
    NTT_C[1] = NTT_C[1]%17;
    NTT_C[2] = NTT_C[2]%17;
    NTT_C[3] = NTT_C[3]%17;

    printf("NTT_C is [%d, %d, %d, %d]", NTT_C[0], NTT_C[1], NTT_C[2], NTT_C[3]);

//Backward NTT:


    // series 
    C[0] = inverse_omega[(0 * 0)%4 ]*NTT_C[0] + inverse_omega[(0 * 1) % 4]*NTT_C[1] + inverse_omega[(0 * 2) % 4]*NTT_C[2] + inverse_omega[(0 * 3) % 4]*NTT_C[3];
    C[1] = inverse_omega[(1 * 0)%4 ]*NTT_C[0] + inverse_omega[(1 * 1) % 4]*NTT_C[1] + inverse_omega[(1 * 2) % 4]*NTT_C[2] + inverse_omega[(1 * 3) % 4]*NTT_C[3];
    C[2] = inverse_omega[(2 * 0)%4 ]*NTT_C[0] + inverse_omega[(2 * 1) % 4]*NTT_C[1] + inverse_omega[(2 * 2) % 4]*NTT_C[2] + inverse_omega[(2 * 3) % 4]*NTT_C[3];
    C[3] = inverse_omega[(3 * 0)%4 ]*NTT_C[0] + inverse_omega[(3 * 1) % 4]*NTT_C[1] + inverse_omega[(3 * 2) % 4]*NTT_C[2] + inverse_omega[(3 * 3) % 4]*NTT_C[3];




    // divided by n
    C[0] = (C[0] * 13) % 17;
    C[1] = (C[1] * 13) % 17;
    C[2] = (C[2] * 13) % 17;
    C[3] = (C[3] * 13) % 17;

    printf("C is [%d, %d, %d, %d]", C[0], C[1], C[2], C[3]);



    





    return 0;
}