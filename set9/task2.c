#include <stdio.h>
#include <malloc.h>
#include <memory.h>

void swap(int *arr, int a, int b)
{
    int v = arr[a];
    arr[a] = arr[b];
    arr[b] = v;
}

int partition(int *arr, int n, int pivot)
{
    int *list = malloc(sizeof(int) * n);

    int left = 0, right = n - 1;
    int piv_i = 0;

    for (int i = 0; i < n; i++)
    {
        if (arr[i] < pivot)
        {
            list[left] = arr[i];
            left++;
        }
        else if (arr[i] > pivot)
        {
            list[right] = arr[i];
            right--;
        }
        else
        {
            arr[piv_i] = pivot;
            piv_i++;
        }
    }

    memcpy(list + left, arr, piv_i * sizeof(int));
    memcpy(arr, list, n * sizeof(int));

    free(list);

    return 1 + (left + right) / 2;
}

int main()
{
    FILE *in = fopen("input.txt", "rb");
    FILE *out = fopen("output.txt", "wb");

    int n, p;
    fread(&n, 4, 1, in);
    fread(&p, 4, 1, in);

    int *arr = malloc(n * 4);

    fread(arr, 4, n, in);

    int k = partition(arr, n, p);

    fwrite(&k, 4, 1, out);
    fwrite(arr, 4, n, out);

    free(arr);

    fclose(in);
    fclose(out);

    return 0;
}
