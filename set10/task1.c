#include <stdio.h>
#include <stdlib.h>

int cmp(const int *a, const int *b) { return *a - *b; }

int main(int argc, char *argv[]) {
    int an, bn;

    scanf("%d", &an);
    int *a = malloc(sizeof(int) * an);
    for (int i = 0; i < an; i++) {
        scanf("%d", &a[i]);
    }

    scanf("%d", &bn);
    int *b = malloc(sizeof(int) * bn);
    for (int i = 0; i < bn; i++) {
        scanf("%d", &b[i]);
    }

    qsort(a, an, sizeof(int), (int (*)(const void *, const void *)) cmp);
    qsort(b, bn, sizeof(int), (int (*)(const void *, const void *)) cmp);
    
    int ans = 0;

    int bi = 0;
    for (int ai = 0; ai < an; ai++) {
        while (bi < bn && b[bi] < a[ai]) {
            bi++;
        }

        if ((bi >= bn || a[ai] != b[bi]) && a[ans - 1] != a[ai]) {
            a[ans] = a[ai];
            ans++;
        }
    }

    printf("%d\n", ans);
    for (int i = 0; i < ans; i++) {
        printf("%d ", a[i]);
    }


    free(a);
    free(b);

    return EXIT_SUCCESS;
}
