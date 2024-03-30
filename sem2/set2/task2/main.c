# include "modular.h"
# include <assert.h>
#include <stdio.h>

int main () {
    MOD = 13;

    int x, y, z;

    assert( pnorm(-1) == 12);

    assert ( pnorm(45) == 6);

    x = pmul(padd(7, psub(2, 3)), 5);
    assert ( x == 4);

    y = pdiv (7, x);
    assert(pmul (x, y) == 7);

    assert(padd(10, 10) == 7);
    assert(psub(1, 10) == 4);

    assert(pdiv(7, 1) == 7);

    assert(pdiv(7, 3) == 11);


    MOD = 2;
    assert ( pnorm (5) == 1);

    MOD = 999999733;
    assert( pmul(999999732, 999999732) == 1);

    assert(pdiv(999999732, 999999731) == 499999867);


    return 0;
}
