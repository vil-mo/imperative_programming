#include <stdio.h>

int main() {
    int n, m;
    scanf("%d %d", &n, &m);

    int is_function = 1;
    int is_everywhere_defined = 0;
    if (m == n) {
        is_everywhere_defined = 1;
    }
    int is_injective = 1;
    int is_surjective = 0;
    int is_bijective = 0;


    int f[300], values[300];
    for (int i=0; i < 300; i++) {
        f[i] = 0;
        values[i] = 0;
    }

    for (int i=0; i<m; i++) {
        int x, y;
        scanf("%d %d", &x, &y);

        if (f[x] > 0) {
            is_function = 0;
            break;
        }

        f[x] = y;

        if (values[y] > 0) {
            is_injective = 0;
        }
        values[y] = x;
    }

    if (is_injective && is_everywhere_defined) {
        is_surjective = 1;
        is_bijective = 1;
    }

    printf("%d ", is_function);
    if (is_function) {
        if (is_everywhere_defined) {
            printf("2 ");
        }
        if (is_injective) {
            printf("3 ");
        }
        if (is_surjective) {
            printf("4 ");
        }
        if (is_bijective) {
            printf("5");
        }
    }

    return 0;
}