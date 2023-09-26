#include <stdio.h>

int calcLetters (char* iStr, int* oLowerCnt, int* oUpperCnt, int* oDigitsCnt) {
    *oLowerCnt = 0;
    *oUpperCnt = 0;
    *oDigitsCnt = 0;

    int i = 0;
    char symb = *(iStr + i);
    while (symb != '\0') {
        if ('a' <= symb && symb <= 'z') {
            (*oLowerCnt)++;
        } else if ('A' <= symb && symb <= 'Z') {
            (*oUpperCnt)++;
        } else if ('0' <= symb && symb <= '9') {
            (*oDigitsCnt)++;
        }

        i++;
        symb = *(iStr + i);
    }

    return i;
}

void main() {
    char str[101];

    int i = 1;
    while (gets(str) != NULL) {
        int lowerCnt, upperCnt, digitsCnt;
        
        int len = calcLetters(str, &lowerCnt, &upperCnt, &digitsCnt);

        printf("Line %d has %d chars: %d are letters (%d lower, %d upper), %d are digits.\n", i, len, lowerCnt+upperCnt, lowerCnt, upperCnt, digitsCnt);

        i++;
    }
}