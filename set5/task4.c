#include <stdio.h>
#include <stdbool.h>

int main() {
    int n, q;
    scanf("%d %d", &n, &q);

    int is_number_prime[n];
    is_number_prime[0] = 0;
    is_number_prime[1] = 0;
    
    for (int i = 2; i < n; i++) {
        is_number_prime[i] = 1;

        for (int j = 2; j <= i/2; j++){
            if (i % j == 0) {
                is_number_prime[i] = 0;
            }
        }
    }

    for (int i = 0; i < q; i++) {
        int num;
        scanf("%d", &num);

        if (is_number_prime[num]) {
            printf("%d prime\n", num);
        } else {
            printf("%d not\n", num);
        }
    }

    return 0;
}