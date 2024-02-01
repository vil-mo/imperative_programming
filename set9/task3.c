#include <inttypes.h>
#include <malloc.h>
#include <stdio.h>
#include <stdlib.h>

int64_t cmp(int64_t *a, int64_t *b) { return *a - *b; }

int main() {
    uint32_t n;
    scanf("%u", &n);

    int64_t *arr = malloc(n * sizeof(int64_t));

    int64_t s = 0;

    for (int i = 0; i < n; i++) {
        scanf("%lld", &arr[i]);
    }

    qsort(arr, n, sizeof(int64_t), cmp);

    n--;

    for (int i = 0; i < n; i++) {
        s += arr[i] * (n - i);
    }

    printf("%lld", s);

    free(arr);

    return 0;
}
