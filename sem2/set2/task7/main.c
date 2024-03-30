#include <stdlib.h>
#include "primes.h"
#include <assert.h>


int main(int argc, char *argv[])
{
    assert(!isPrime(0));
    assert(!isPrime(1));
    assert(isPrime(2));
    assert(isPrime(3));
    assert(isPrime(7));
    assert(!isPrime(15));
    assert(!isPrime(10000000));


    assert(!isPrime(18));
    assert(isPrime(19));
    assert(!isPrime(20));


    assert(findNextPrime(0) == 2);
    assert(findNextPrime(1) == 2);
    assert(findNextPrime(2) == 2);
    assert(findNextPrime(7) == 7);
    assert(findNextPrime(15) == 17);
    assert(findNextPrime(10000000) == 10000019);

    assert(findNextPrime(18) == 19);
    assert(findNextPrime(19) == 19);
    assert(findNextPrime(20) == 23);

    assert(getPrimesCount(0, 10000000) == 664579);
    assert(getPrimesCount(9999990, 10000000) == 1);

    assert(getPrimesCount(0, 10) == 4);
    assert(getPrimesCount(2, 10) == 4);
    assert(getPrimesCount(2, 7) == 3);
    assert(getPrimesCount(0, 7) == 3);

    assert(getPrimesCount(18, 30) == 3);
    assert(getPrimesCount(19, 30) == 3);
    assert(getPrimesCount(20, 30) == 2);

    assert(getPrimesCount(10, 18) == 3);
    assert(getPrimesCount(10, 19) == 3);
    assert(getPrimesCount(10, 20) == 4);

    assert(getPrimesCount(0, 0) == 0);
    assert(getPrimesCount(100, 100) == 0);
    assert(getPrimesCount(17, 17) == 0);
    assert(getPrimesCount(10000000, 10000000) == 0);

    return EXIT_SUCCESS;
}
