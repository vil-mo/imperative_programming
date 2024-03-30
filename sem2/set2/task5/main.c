#include <stdlib.h>
#include <stdio.h>

typedef struct Factors {
    int k;
    int primes[32];
    int powers[32]; 
} Factors;
void Factorize(int, Factors *);

int main(int argc, char *argv[])
{
    FILE *in = fopen("input.txt", "r");
    FILE *out = fopen("output.txt", "w");

    int m;
    fscanf(in, "%d", &m);

    for (int i = 0; i < m; i++) {
        int x;
        fscanf(in, "%d", &x);

        Factors f;

        Factorize(x, &f);

        if (x == 1) {
            fprintf(out, "1 = 1");
        } else {
            fprintf(out, "%d = %d^%d", x, f.primes[0], f.powers[0]);
        }
        for (int i = 1; i < f.k; i++) {
            fprintf(out, " * %d^%d", f.primes[i], f.powers[i]);
        }
        fprintf(out, "\n");
    }

    fclose(in);
    fclose(out);

    return EXIT_SUCCESS;
}
