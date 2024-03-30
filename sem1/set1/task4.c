#include <stdio.h>

int main() {
    int n;
    scanf("%d", &n);

    if (n == 1) {
        printf("NO\n");
        return 0;
    }

    for (int i=2; i<n; i++) {
        if (n % i == 0) {
            printf("NO\n");
            return 0;
        }
    }

    printf("YES\n");

    return 0;
}