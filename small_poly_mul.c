#include <stdio.h>
#include "small_poly_mul.h"

int main(){
    uint16_t a[8] = {1805, 4031, 1542,  395,  146, 3928,  152,  987};
    uint16_t b[8] = {2971,  238, 3063, 1069, 2193,  610,  756, 1881};
    uint16_t c[8] = { 672, 1294, 3201, 2860, 1192, 1772,  304, 1043};
    uint16_t aa[15];
    for(int i=0; i<15; i++){aa[i] = a[(15 - i) % 8];}
    printf("Computing the polynomial multiplication of A and B in Z_4096[x]/(x^8-1)\n");
    printf("a(x) = %dx^7 + %dx^6 + %dx^5 + %dx^4 + %dx^3 + %dx^2 + %dx + %d\n",
          a[7], a[6], a[5], a[4], a[3], a[2], a[1], a[0]);
    printf("b(x) = %dx^7 + %dx^6 + %dx^5 + %dx^4 + %dx^3 + %dx^2 + %dx + %d\n",
          b[7], b[6], b[5], b[4], b[3], b[2], b[1], b[0]);
    uint16_t r[8];
    toep_poly_mul_8(r, aa, b);
    printf("Computed result:\n");
    printf("r(x) = %dx^7 + %dx^6 + %dx^5 + %dx^4 + %dx^3 + %dx^2 + %dx + %d\n",
          r[7], r[6], r[5], r[4], r[3], r[2], r[1], r[0]);
    printf("Correct result (computed in SageMath):\n");
    printf("c(x) = %dx^7 + %dx^6 + %dx^5 + %dx^4 + %dx^3 + %dx^2 + %dx + %d\n",
          c[7], c[6], c[5], c[4], c[3], c[2], c[1], c[0]);
  return 0;
}
