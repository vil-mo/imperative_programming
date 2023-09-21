#include <stdio.h>

void main() {
    int n;
    scanf("%d", &n);
    
    int arr[100];

    int amount[100];

    for (int j=0; j<n; j++) {
        scanf("%d", &arr[j]);
        amount[j] = 0;

        for (int i=0; i<j; i++) {
            if (arr[i] > arr[j]) {
                amount[i]++;
            }
        }
    }

    for (int i=0; i<n; i++) {
        printf("%d ", amount[i]);
    }


}