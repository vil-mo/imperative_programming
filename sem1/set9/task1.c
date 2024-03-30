#include <stdio.h>
#include <malloc.h>

// merges sorted arrays a[0..ak-1] and b[0..bk-1] into
// one sorted array res[0..rk-1], returning rk from function
int merge(const int *a, int ak, const int *b, int bk, int *res)
{
    int ai = 0, bi = 0;
    int k = ak + bk;

    for (int i = 0; i < k; i++)
    {
        if ((bi == bk) || (ai != ak && a[ai] < b[bi]))
        {
            res[i] = a[ai];
            ai++;
        }
        else
        {
            res[i] = b[bi];
            bi++;
        }
    }
}

int main()
{
    FILE *in = fopen("input.txt", "rb");
    FILE *out = fopen("output.txt", "wb");

    int ak, bk;
    fread(&ak, 4, 1, in);
    fread(&bk, 4, 1, in);

    int *a = malloc(ak * 4);
    int *b = malloc(bk * 4);
    int *res = malloc((ak + bk) * 4);

    fread(a, 4, ak, in);
    fread(b, 4, bk, in);

    merge(a, ak, b, bk, res);

    fwrite(res, 4, ak + bk, out);


    free(a);
    free(b);
    free(res);

    fclose(in);
    fclose(out);

    return 0;
}