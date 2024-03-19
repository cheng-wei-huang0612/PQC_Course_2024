#include <stdio.h>
#include <math.h>
#include <stdlib.h>

// 簡單的加法函數，用於對數字進行加法操作
int add(int x, int y) {
    return x + y;
}

// 簡單的減法函數，用於對數字進行減法操作
int subtract(int x, int y) {
    return x - y;
}

// Karatsuba乘法
int karatsuba(int x, int y) {
    // 基礎情況
    if (x < 10 || y < 10) return x * y;

    // 計算大小
    int n = fmax(log10(x) + 1, log10(y) + 1);
    int half = n / 2;

    // 拆分數字
    int high1 = x / (int)pow(10, half);
    int low1 = x % (int)pow(10, half);
    int high2 = y / (int)pow(10, half);
    int low2 = y % (int)pow(10, half);

    // 遞歸步驟
    int z0 = karatsuba(low1, low2);
    int z1 = karatsuba(add(low1, high1), add(low2, high2));
    int z2 = karatsuba(high1, high2);

    // 最終結果
    return z2 * pow(10, 2 * half) + (z1 - z2 - z0) * pow(10, half) + z0;
}

int main() {
    int x = 23422;
    int y = 56782;

    printf("Karatsuba multiplication of %d and %d is %d\n", x, y, karatsuba(x, y));
    return 0;
}

