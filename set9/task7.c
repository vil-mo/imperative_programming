#include "malloc.h"
#include "stdio.h"
#include <stdlib.h>

int cmp(const int *a, const int *b) { return *a - *b; }

int main() {
    int n;
    scanf("%d", &n);

    int *a = malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }

    qsort(a, n, sizeof(int), (int (*)(const void *, const void *))cmp);

    int s = 0;
    for (int i = 0; i < n - 1; i++) {
        if (a[i] != a[i + 1]) {
            a[s] = a[i];
            s++;
        }
    }

    a[s] = a[n - 1];
    s++;

    printf("%d\n", s);
    for (int i = 0; i < s; i++) {
        printf("%d\n", a[i]);
    }

    free(a);
}
