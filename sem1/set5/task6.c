#include <stdio.h>

typedef struct {
    int len;
    int arr[3000];
} LongNum;

LongNum newLongNum(int from) {
    LongNum num;
    num.len = 0;
    if (from == 0) {
        num.arr[0] = 0;
        num.len = 1;
    }
    while (from > 0) {
        num.arr[num.len] = from % 10;
        num.len++;
        from /= 10;
    }
    return num;
}


void printLongNum(LongNum *num) {
    for (int i = num->len - 1; i >= 0; i--) {
        printf("%d", num->arr[i]);
    }
}

void normalizeLongNum(LongNum *long_num) {
    int remember = 0;

    for (int i = 0; i < long_num->len; i++) {
        remember += long_num->arr[i];
        long_num->arr[i] = remember % 10;
        remember /= 10;
    }

    while (remember > 0) {
        long_num->arr[long_num->len] = remember % 10;
        remember = remember / 10;
        long_num->len++;
    }
}

void multiplyLongNumAndInt(int a, LongNum *b, LongNum *result) {
    *result = newLongNum(0);
    result->len = b->len;
    for (int i = 0; i < b->len; i++) {
        result->arr[i] = a * b->arr[i];
    }

    normalizeLongNum(result);
}






int main() {
    int n;
    scanf("%d", &n);

    LongNum a = newLongNum(1);
    LongNum res;


    for (int i = 2; i <= n; i++) {
        multiplyLongNumAndInt(i, &a, &res);
        a = res;
    }


    printLongNum(&a);
    printf("\n");

    return 0;
}