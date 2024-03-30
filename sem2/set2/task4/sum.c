#include <stdint.h>
#include <stdlib.h>

int64_t *A;

// Длина массива
int R = 0;

// выполнить подготовку массива: запускается один раз перед запусками Sum
// здесь arr[0..n) –- это массив A из входного файла
void Init(const int *arr, int n) {
    R = n;
    A = malloc(sizeof(int64_t) * (n + 1));

    int64_t s = 0;

    A[0] = 0;

    for (int i = 0; i < n; i++) {
        s += arr[i];
        A[i + 1] = s;
    }
}
// найти сумму элементов A на отрезке [l..r)
// использует данные, посчитанные функцией Init
int64_t Sum(int l, int r) {
    return A[r] - A[l];
}

void FreeA() {
    free(A);
}
