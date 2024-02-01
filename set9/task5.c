#include <malloc.h>
#include <stdio.h>

void swap(int *arr, int a, int b) {
    int v = arr[a];
    arr[a] = arr[b];
    arr[b] = v;
}

void _quicksort(int *arr, int left, int right) {
    int mid = (left + right) / 2;

    int max = right - 1;
    if (arr[left] > arr[max]) {
        swap(arr, left, max);
    }
    if (arr[mid] > arr[max]) {
        swap(arr, mid, max);
    } else if (arr[mid] < arr[left]) {
        swap(arr, mid, left);
    }

    int curr = left;
    int pivot = arr[mid];

    for (int i = left; i < right; i++) {
        if (arr[i] > arr[max]) {
            swap(arr, i, max);
        } else if (arr[i] < arr[left]) {
            swap(arr, i, left);
        }
        if (arr[i] < pivot) {
            swap(arr, i, curr);

            curr++;
        }
    }

    if (arr[left] == arr[max]) {
        return;
    }
    right--;
    left++;

    if (curr == left && right - left > 2) {
        swap(arr, left, mid);

        _quicksort(arr, left + 1, right);
        return;
    }

    if (curr - left > 2) {
        _quicksort(arr, left, curr);
    } else if (curr - left == 2 && arr[left] > arr[left + 1]) {
        swap(arr, left, left + 1);
    }

    if (right - curr > 2) {
        _quicksort(arr, curr, right);
    } else if (right - curr == 2 && arr[curr] > arr[curr + 1]) {
        swap(arr, curr, curr + 1);
    }
}

void quicksort(int *arr, int len) {
    if (len > 1) {
        _quicksort(arr, 0, len);
    }
}

int main() {
    FILE *in = fopen("input.txt", "rb");
    FILE *out = fopen("output.txt", "wb");

    int n;
    fread(&n, sizeof(int), 1, in);
    // scanf("%d", &n);

    int *a = malloc(n * sizeof(int));
    fread(a, sizeof(int), n, in);

    // for (int i = 0; i < n; i++) {
    //     scanf("%d", &a[i]);
    // }

    quicksort(a, n);

    fwrite(a, sizeof(int), n, out);
    // for (int i = 0; i < n; i++) {
    //     printf("%d, ", a[i]);
    // }

    free(a);

    fclose(in);
    fclose(out);

    return 0;
}
