#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    FILE *in = fopen("input.txt", "r");
    FILE *out = fopen("output.txt","w");

    int64_t m;
    int t;
    fscanf(in, "%lld %d", &m, &t);

    int64_t *nums[2001];

    for (int i = 0; i < 2001; i++) {
        nums[i] = malloc(sizeof(int64_t) * (i + 1));
        nums[i][0] = 1;
        nums[i][i] = 1;

        for (int j = 1; j < i; j++) {
            nums[i][j] = ((nums[i-1][j-1] + nums[i-1][j]) % m);
        }
    }

    for (int i = 0; i < t; i++) {
        int n, k;
        fscanf(in, "%d %d", &n, &k);

        if (k < 0 || k > n) {
            fprintf(out, "0\n");
        } else {
            fprintf(out, "%lld\n", nums[n][k]);
        }
    }

    for (int i = 0; i < 2001; i++) {
        free(nums[i]);
    }

    fclose(in);
    fclose(out);

    return EXIT_SUCCESS;
}
