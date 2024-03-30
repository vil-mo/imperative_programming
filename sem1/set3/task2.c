#include <stdio.h>
#include <math.h>

void main() {
    int n;
    scanf("%d", &n);

    int sum[100000];

    for (int i=1; i<=n; i++) {
        int num;
        scanf("%d", &num);
        sum[i-1] = 0;


        short flag = i == n;
        for (int j=1; j * j <= i; j++) {
            if (i % j == 0) {
                sum[j-1] += num;
                if (j * j != i) {
                    sum[i/j-1] += num;
                }
            }
        }
    }

    for (int i=0; i<n; i++) {
        printf("%d\n", sum[i]);
    }



}