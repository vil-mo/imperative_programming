#include <stdio.h>
#include <malloc.h>

void swap(int *a, int *b)
{
    int v = *a;
    *a = *b;
    *b = v;
}

void _quicksort(int *arr, int low, int high)
{
    if (low >= high)
    {
        return;
    }
    int left = 0, right = n - 1;
    int left_pivot_i = 0, right_pivot_i = n - 1;
    while (left < right)
    {
        while (left < right && a[left] <= pivot)
        {
            while (left < right && a[left] == pivot)
            {
                swap(a, left_pivot_i, left);
                left_pivot_i++;
                left++;
            }
            if (left < right && a[left] < pivot)
            {
                left++;
            }
        }

        while (left < right && a[right] >= pivot)
        {
            while (left < right && a[right] == pivot)
            {
                swap(a, right_pivot_i, right);
                right_pivot_i--;
                right--;
            }
            if (left < right && a[right] > pivot)
            {
                right--;
            }
        }

        if (left < right)
        {
            swap(a, left, right);
        }
    }

    if (left >= 0)
    {
        swap(&arr[high], &arr[secondPivot]);
        _quicksort(arr, low, secondPivot - 1);
        _quicksort(arr, secondPivot + 1, high);
    }
    else
    {
        _quicksort(arr, low, high - 1);
    }
}

void quicksort(int *arr, int len)
{
    _quicksort(arr, 0, len - 1);
}

int main()
{
    FILE *in = fopen("input.txt", "rb");
    FILE *out = fopen("output.txt", "wb");

    int n;
    fread(&n, sizeof(int), 1, in);

    int *a = malloc(n * sizeof(int));
    fread(a, sizeof(int), n, in);

    quicksort(a, n);

    fwrite(a, sizeof(int), n, out);

    free(a);

    fclose(in);
    fclose(out);

    return 0;
}
