#include <stdio.h>
#include <math.h>
#include <stdlib.h>


int main() {
    int a, b;
    scanf("%d", &a);
    scanf("%d", &b);

    double devided = (double)a / b;

    int floored = floor(devided);
    int ceiled = ceil(devided);
    int to_zero;
    if (devided > 0) {
        to_zero = floor(devided);
    } else {
        to_zero = ceil(devided);
    }

    int remainder = abs(a) % b;
    if (!((remainder - a) % b == 0)) {
        remainder = b - remainder;
    }

    printf("%d %d %d %d\n", floored, ceiled, to_zero, remainder);

    return 0;
}