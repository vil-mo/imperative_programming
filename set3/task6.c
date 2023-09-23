#include <stdio.h>

void main() {
    int n;
    scanf("%d", &n);

    int val[100001];
    for (int i=0; i<100001; i++) {
        val[i] = 0;
    }

    for (int i=0; i<n; i++) {
        int num;
        scanf("%d", &num);

        val[num] = 1;
    }

    scanf("%d", &n);

    for (int i=0; i<n; i++) {
        int num;
        scanf("%d", &num);

        val[num] = 0;
    }

    int amount = 0;
    for (int i=0; i<100001; i++) {
        if (val[i] == 1) {
            amount++;
        }
    }
    printf("%d\n", amount);
    for (int i=0; i<100001; i++) {
        if (val[i] == 1) {
            printf("%d ", i);
        }
    }
}