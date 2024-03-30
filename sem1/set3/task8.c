#include <stdio.h>

int char_to_int(char symb) {
    if ('0' <= symb && symb <= '9') {
        return symb - '0';
    } else {
        return symb - 'a' + 10;
    }
}

char int_to_char(int num) {
    if (num < 10) {
        return '0' + num;
    } else {
        return 'a' + num - 10;
    }
}

int main() {
    int p, q;
    scanf("%d %d ", &p, &q);

    int num = 0;
    char symbs[500];
    // for (int i=0; i<500; i++) {
    //     symbs[i] = '#';
    // }
    scanf("%s", symbs);

    for (int i=0; i<500; i++) {
        if (symbs[i] == 0) break;
        num *= p;
        num += char_to_int(symbs[i]);
    }
    
    int i = 0;

    if (num == 0) {
        printf("0");
        return 0;
    }

    while (num > 0) {
        symbs[i] = int_to_char(num % q);
        num /= q;
        i++;
    }
    for (int j = i-1; j >= 0; j--) {
        printf("%c", symbs[j]);
    }

    return 0;
}