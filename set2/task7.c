#include <stdio.h>
#include <math.h>

void main() {
    int l, an, k;
    scanf("%d %d %d", &l, &an, &k);

    int s = 0;

    int diff = an - l;
    
    for (int a1=l; a1 < an; a1++) {
        for (int d=1; d <= diff; d++) {

            double n = (double)(an - a1)/d + 1;

            if (floor(n) == k) {
                s++;
            }
        }
    }

    printf("%d\n", s);

}