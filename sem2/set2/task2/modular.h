#pragma once
// Current mod of the program. All the functions in this file use it to calculate return values.
//
// Should be prime number and less or equal to 10^9.
extern int MOD;

// Reurns number modulo.
// `a mod MOD`
int pnorm(int a); 

// Modulo addition.
// `(a + b) mod MOD`
int padd(int a, int b);

// Modulo substraction.
// `(a - b) mod MOD`
int psub(int a, int b);

// Modulo multiplication.
// `(a * b) mod MOD`
int pmul(int a, int b);

// Modulo division.
// `(a * b^-1) mod MOD`
int pdiv(int a, int b);

// Modulo power.
// `(a ^ b) mod MOD`
int ppow(int a, int b);

// Modulo inverse
// `a^-1 mod MOD`
int pinv(int a);
