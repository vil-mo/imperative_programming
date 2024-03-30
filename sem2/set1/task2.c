#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int64_t mod_mul(int64_t a, int64_t b, int64_t m) {
    return (a * b) % m;
}

int mod_pow(int64_t x, int64_t a, int64_t m) {
    int64_t result = 1;

    for (int i = 0; i < 32; i++) {
        if ((a >> i) & 1) {
            result = mod_mul(result, x, m);
        }
        x = mod_mul(x, x, m);
    }

    return result;
}

int main(int argc, char *argv[])
{
    int t;
    int64_t m;
    scanf("%d %lld", &t, &m);

    for (int i = 0; i < t; i++) {
        int64_t k;
        scanf("%lld", &k);

        int64_t r = mod_pow(k, m - 2, m);

        if (mod_mul(k, r, m) == 1) {
            printf("%lld\n", r);
        } else {
            printf("-1\n");
        }
    }

    return EXIT_SUCCESS;
}
