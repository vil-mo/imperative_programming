#include <stdio.h>
#include <stdint.h>

void bitwiseXOR(double *result, double *x_doub, uint64_t *y_long) {
    uint64_t x = *((uint64_t *) x_doub);
    uint64_t y = *y_long;

    uint64_t z = x ^ y;
    
    *result = *((double *) &z);
}


int main() {
    int n;
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        int p, q;
        uint64_t m;

        scanf("%d/%d xor %llx", &p, &q, &m);

        double x = (double)p / q;

        double result;
        bitwiseXOR(&result, &x, &m);

        printf("%0.15g\n", result);
    }

    

    return 0;
}