#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

const int64_t SOL_MOD = 1000000007;

int min(int a, int b) {
    return a < b ? a : b;
}

int max(int a, int b) {
    return a > b ? a : b;
}

int64_t mod_mul(int64_t a, int64_t b, int64_t m) {
    return (a * b) % m;
}

int64_t mod_add(int64_t a, int64_t b, int64_t m) {
    return (a + b) % m;
}

int64_t mod_sub(int64_t a, int64_t b, int64_t m) {
    int64_t r = (a - b) % m;
    if (r < 0) {
        r += m;
    }

    return r;
}

int64_t mod_pow(int64_t x, int64_t a, int64_t m) {
    int64_t result = 1;

    for (int i = 0; i < 32; i++) {
        if ((a >> i) & 1) {
            result = mod_mul(result, x, m);
        }
        x = mod_mul(x, x, m);
    }

    return result;
}

int64_t rev(int64_t n, int64_t m) {
    return mod_pow(n, m - 2, m); 
}


int main(int argc, char *argv[])
{
    int n, k;
    int64_t m;
    scanf("%d %d %lld\n", &n, &k, &m);

    int64_t **equations = malloc(sizeof(int64_t) * k);

    for (int i = 0; i < k; i++) {
        equations[i] = malloc(sizeof(int64_t) * (n + 1));

        for (int j = 0; j < n + 1; j++) {
            scanf("%lld", &equations[i][j]);
        }
    }

    for (int v = 0; v < min(n, k) - 1; v++) {
        for (int eq = v + 1; eq < k; eq++) {
            if (equations[v][v] == 0) {
                int64_t *temp = equations[eq];
                equations[eq] = equations[v];
                equations[v] = temp;
                continue;
            }

            if (equations[eq][v] == 0) {
                continue;
            }

            int64_t revv = rev(equations[eq][v], m);
            int64_t coef = mod_mul(equations[v][v], revv, m);

            for (int curr_v = v; curr_v < n + 1; curr_v++) {
                equations[eq][curr_v] = mod_mul(coef, equations[eq][curr_v], m);
                equations[eq][curr_v] = mod_sub(equations[eq][curr_v], equations[v][curr_v], m);
            }
        }
    }
    
    int64_t solutions = 1;
    int more_than_one_solution = 0;
    int solved_am = 0;

    for (int eq = min(k, n) - 1; eq >= 0; eq--) {
        int64_t coef_count = 0;
        for (int v = eq; v < n - solved_am; v++) {
            if (equations[eq][eq] != 0) {
                coef_count++;
            }
        }

        solutions = mod_mul(solutions, mod_pow(m, max(coef_count - 1, 0), SOL_MOD), SOL_MOD);
        if (solutions > 1) {
            more_than_one_solution = 1;
        }

        if (!more_than_one_solution) {
            int64_t debug;

            for (int v = n - solved_am; v < n; v++) {
                equations[eq][v] = mod_mul(equations[eq][v], equations[v][n], m);
                equations[eq][n] = mod_sub(equations[eq][n], equations[eq][v], m);
            }
            equations[eq][n] = mod_mul(equations[eq][n], rev(equations[eq][eq], m), m);
        }

        solved_am += coef_count;
    }

    for (int eq = n; eq < k; eq++) {
        if (equations[eq][n - 1] * equations[n - 1][n] != equations[eq][n]) {
            solutions = 0;
        }

        free(equations[eq]);
    }

    if (k > n) {
        k = n;
    }


    printf("%lld\n", solutions);
    for (int eq = 0; eq < k; eq++) {
        if (!more_than_one_solution && solutions == 1) {
            printf("%lld\n", equations[eq][n]);
        }
        free(equations[eq]);
    }

    free(equations);

    return EXIT_SUCCESS;
}
