#include <stdio.h>
#include <arm_neon.h>

#define SIZE 24

uint16_t result[SIZE] = {0};

int main(){
    for (uint16_t i=0; i<SIZE; i++){
        printf("%d ", result[i]);
    }
}