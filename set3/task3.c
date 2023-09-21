#include <stdio.h>

void main() {
    int n;
    scanf("%d", &n);

    int arr[10001];
    for (int i=0; i<10001; i++) {
        arr[i] = 0;
    }

    int max_num = 1;

    for (int i = 0; i<n; i++) {
        int num;
        scanf("%d", &num);

        arr[num]++;

        if (num > max_num) {
            max_num = num;
        }
    }

    for (int i = 0; i <= max_num; i++) {
        if (arr[i] > 0) {
            printf("%d: %d\n", i, arr[i]);
        }
    }

    
}