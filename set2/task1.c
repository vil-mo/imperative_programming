#include <stdio.h>
#include <stdbool.h>

int main() {
    int n;
    scanf("%d", &n);

    int primes[n];
    int primes_amount = 0;


    for (int i=2; i<=n; i++) {
        bool is_prime = true;

        for (int j=0; j< primes_amount; j++){
            if (i % primes[j] == 0) {
                is_prime = false;
                break;
            }
        }

        if (is_prime) {
            printf("%d\n", i);
            primes[primes_amount] = i;
            primes_amount++;
        }
    }


    return 0;
}