#include <stdio.h>
#include <inttypes.h>

int main() {
    int n;
    scanf("%d", &n);

    int64_t arr[n];
    int count = 0;

    for (int i = 0; i < n; i++) {
        scanf("%llx", &arr[i]);

        for (int j = 0; j < i; j++) {
            if ((arr[i] & arr[j]) == 0) {
                count++;
            }
        }
    }

    printf("%d", count);

    return 0;
}