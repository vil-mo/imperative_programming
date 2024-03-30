#include "modular.h"

int MOD;

int pnorm(int a) {
    int r = a % MOD;

    if (r < 0) {
        r += MOD;
    }
    
    return r;
}

int padd(int a, int b) {
    return (int)( ((long)a + (long)b) % MOD );
}

int psub(int a, int b) {
    return pnorm(a - b);
}

int pmul(int a, int b) {
    return (int)( ((long)a * (long)b) % (long)MOD);
}

int pdiv(int a, int b) {
    return pmul(a, pinv(b));
}

int ppow(int a, int b) {
    int r = 1;

    for (int i = 0; i < 32; i++) {
        if ((b >> i) & 1) {
            r= pmul(r, a);
        }
        a = pmul(a, a);
    }

    return r;
}

int pinv(int a) { 
    return ppow(a, MOD - 2);
}

