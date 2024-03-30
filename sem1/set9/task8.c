#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    int n;
    scanf("%d", &n);

    int *a = malloc(n * sizeof(int));
    scanf("%d", a);

    int mid_i = 0;

    for (int i = 1; i < n; i++) {
        scanf("%d", &a[i]);
        if (a[i - 1] > a[i]) {
            mid_i = i;
        }

        if (a[i] > a[i - 1]) {
            a[i - 1] = a[i] - a[i - 1];
        } else {
            a[i - 1] = a[i - 1] - a[i];
        }
    }

    int q;
    scanf("%d", &q);

    for (int i = 0; i < q; i++) {
        int result = 0;
        int c;
        scanf("%d", &c);

        int dir;
        if (c < 0) {
            dir = 1;
            c = -c;
        } else {
            dir = -1;
            result = 1;
        }

        int i;
        for (i = mid_i; i < n - 1 && i >= 0; i += dir) {
            int val = a[i];
            if (val >= c) {
                if (val == c) {
                    result = 0;
                }
                break;
            }
        }
        result += i;

        printf("%d\n", result);
    }

    return EXIT_SUCCESS;
}
