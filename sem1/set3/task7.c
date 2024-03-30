#include <stdio.h>
#include <stdlib.h>

int comp (const int *i, const int *j) {
    return *i - *j;
}


int main() {
    int n;
    scanf("%d", &n);
    int arr[n];
    for (int i=0; i<n; i++) {
        scanf("%d", &arr[i]);
    }

    qsort(arr, n, sizeof(int), (int(*) (const void *, const void *)) comp);

    for(int i=0; i<n; i++) {
        printf("%d ", arr[i]);
    }


    return 0;
}