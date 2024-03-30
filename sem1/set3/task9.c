#include <stdio.h>


int main() {
    int n;
    scanf("%d\n", &n);

    char arr[n], output_arr[n];
    for (int i=0; i<n; i++) {
        if (i == n-1) {
            scanf("%c", &arr[i]);
        } else {
            scanf("%c ", &arr[i]);
        }

        output_arr[i] = arr[i];
    }

    for (int j=1; j<n; j++) {
        int out_of_cycle = 0;

        for (int i=n-j-1; i>=0; i--) {
            if (arr[n-j] > arr[i]) {

                output_arr[i] = arr[n-j];
                
                for (int k=1; k<n-i; k++) {
                    if (k == j) {
                        output_arr[i+k] = arr[i];
                    } else {
                        output_arr[i+k] = arr[n-k];
                    }
                }

                out_of_cycle = 1;

                break;
            }
        }

        if (out_of_cycle) {
            break;
        }
    }

    for (int i=0; i<n; i++) {
        printf("%c ", output_arr[i]);
    }

    return 0;
}