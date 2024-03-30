#include <stdio.h>
#include <math.h>



int main() {
    int n;
    scanf("%d", &n);

    long long answer = n;

    double sqr = sqrt(n);
    double cb = cbrt(n);


    for (int i = 2; i <= sqr; i++) {
        answer -= i-1;

        answer += floor(n / (i));
    }

    for (int i = 2; i <= cb; i++) {
        for (int j = 2; j <= cb; j++) {
            answer -= i+j-3;

            answer += floor(n / (i));
        }
    }

    printf("%d\n", answer);

    return 0;
}

