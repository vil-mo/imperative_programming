#include <stdio.h>

int main() {
    int x, y, z;
    scanf("%d", &x);
    scanf("%d", &y);
    scanf("%d", &z);

    if (x <= 0) {
        printf("-1\n");
    } else if (y <= 0) {
        printf("-2\n");
    } else if (z <= 0) {
        printf("-3\n");
    } else {
        printf("%d\n", 2 * (x * y + x * z + y * z));
    }

    return 0;
}