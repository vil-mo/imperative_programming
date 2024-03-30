#include <stdio.h>
#include <stdlib.h>

int gcd(int a, int b) { return b == 0 ? a : gcd(b, a % b); }

int main(int argc, char *argv[])
{
    int n;
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        int a, b;
        scanf("%d %d", &a, &b);

        int min = a < b ? a : b;
        
        printf("%d\n", gcd(a, b));
    }

    return EXIT_SUCCESS;
}
