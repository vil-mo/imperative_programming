#include "primes.h"

#define PRIMES_COUNT 10000001

int Primes[PRIMES_COUNT]; // stores next prime
int primesInitialized = 0;

void InitializePrimes() {
    primesInitialized = 1;

    Primes[0] = 2;
    Primes[1] = 2;
    Primes[2] = 3;

    int last = 2;
    for (int j = 4; j < PRIMES_COUNT; j += 2) {
        Primes[j] = 1;
    }

    int x = 3;
    for (; x * x <= PRIMES_COUNT; x++) {
        if (Primes[x] == 0) {
            for (int j = x * x; j < PRIMES_COUNT; j += x) {
                Primes[j] = 1;
            }

            for (int j = last; j < x; j++) {
                Primes[j] = x;
            }
            last = x;
        }
    }

    for (; x < PRIMES_COUNT; x++) {
        if (Primes[x] == 0) {
            for (int j = last; j < x; j++) {
                Primes[j] = x;
            }
            last = x;
        }
    }

    for (int j = last; j < PRIMES_COUNT; j++) {
        Primes[j] = 10000019;
    }
}

int isPrime(int x) {
    if (!primesInitialized) {
        InitializePrimes();
    }

    return x > 1 && Primes[x - 1] == x;
}

int findNextPrime(int x) {
    return isPrime(x) ? x : Primes[x];
}

int getPrimesCount(int l, int r) {
    int count = 0;

    if (isPrime(l) && r > l ) {
        count++;
    }

    for (int x = Primes[l]; x < r; x = Primes[x]) {
        count++;
    }

    return count;
}
