#include <stdio.h>

int main() {
    int n;
    scanf("%d", &n);

    int s = 0;
    for (int i=0; i<n; i++) {
        int a;
        scanf("%d", &a);
        if (a % 2 == 0) {
            s += a;
        }
    }

    printf("%d\n", s);

    return 0;
}