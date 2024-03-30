#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

void Init(const int *, int);
int Query(int, int64_t);
void FreeA();

int main(int argc, char *argv[])
{
    FILE *in = fopen("input.txt", "r");
    FILE *out = fopen("output.txt", "w");

    int n, m;
    fscanf(in, "%d %d", &n, &m);

    int *arr = malloc(sizeof(int) * n);

    for (int i = 0; i < n; i++) {
        fscanf(in, "%d", &arr[i]);
    }

    Init(arr, n);

    for (int i = 0; i < m; i++) {
        int l;
        int64_t s;
        fscanf(in, "%d %lld", &l, &s);
        fprintf(out, "%d\n", Query(l, s));
    }

    free(arr);
    FreeA();

    fclose(in);
    fclose(out);

    return EXIT_SUCCESS;
}

