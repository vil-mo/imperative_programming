#include <stdio.h>
#include <malloc.h>

void _mergesort(int *a, int start, int end, int * sorted)
{
   int m = (end + start) / 2;

    if (end - start > 2)
    {
        _mergesort(a, start, m, sorted);
        _mergesort(a, m, end, sorted);
    }

    int x = start;
    int y = m;

    for (int i = start; i < end; i++)
    {
        if (y == end || (x != m && a[x] < a[y]))
        {
            sorted[i] = a[x];
            x++;
        }
        else
        {
            sorted[i] = a[y];
            y++;
        }
    }

    for (int i = start; i < end; i++)
    {
        a[i] = sorted[i];
    }

}

void mergesort(int *a, int n)
{
    int * sorted = malloc(n * sizeof(int));
    _mergesort(a, 0, n, sorted);
    free(sorted);
}

int main()
{
    FILE *in = fopen("input.txt", "rb");
    FILE *out = fopen("output.txt", "wb");

    int n;
    fread(&n, sizeof(int), 1, in);

    int *a = malloc(n * sizeof(int));
    fread(a, sizeof(int), n, in);

    mergesort(a, n);

    fwrite(a, sizeof(int), n, out);

    free(a);

    fclose(in);
    fclose(out);

    return 0;
}
