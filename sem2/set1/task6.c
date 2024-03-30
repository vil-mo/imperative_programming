#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

const int64_t mod = 1000000007;


int64_t mod_mul(int64_t a, int64_t b) {
    return (a * b) % mod;
}

int64_t mod_pow(int64_t x, int64_t a) {
    int64_t result = 1;

    for (int i = 0; i < 32; i++) {
        if ((a >> i) & 1) {
            result = mod_mul(result, x);
        }
        x = mod_mul(x, x);
    }

    return result;
}

int64_t rev(int64_t n) {
    return mod_pow(n, mod - 2); 
}
int64_t _facts[1000001];

int64_t fact(int64_t n) {
    return _facts[n];
}

int64_t calculate(int64_t n, int64_t k) {
    return mod_mul(mod_mul(fact(n), rev(fact(k))), rev(fact(n - k)));
}


int main(int argc, char *argv[])
{
    _facts[0] = 1;
    _facts[1] = 1;
    int64_t result = 1;
    for (int64_t i = 2; i < 1000001; i++) {
        result = mod_mul(result, i);
        _facts[i] = result;
    }


    FILE *in = fopen("input.txt", "r");
    FILE *out = fopen("output.txt","w");

    int t;
    fscanf(in, "%d", &t);

    for (int i = 0; i < t; i++) {
        int64_t n, k;
        fscanf(in, "%lld %lld", &n, &k);

        fprintf(out, "%lld\n", calculate(n, k));
    }

    fclose(in);
    fclose(out);

    return EXIT_SUCCESS;
}
