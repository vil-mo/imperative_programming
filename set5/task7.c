#include <stdio.h>
#include <math.h>

typedef struct {
    int len;
    int arr[10000];
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

void scanLongNum(LongNum *long_num) {
    char symb;
    scanf("%c", &symb);

    while (!('0' <= symb && symb <= '9')){
        scanf("%c", &symb);
    }

    long_num->len = 0;

    while ('0' <= symb && symb <= '9'){
        long_num->arr[long_num->len] = symb - '0';
        long_num->len++;

        scanf("%c", &symb);
    }

    for (int i = 0; i < long_num->len/2; i++) {
        int num = long_num->arr[i];
        long_num->arr[i] = long_num->arr[long_num->len - i - 1];
        long_num->arr[long_num->len - i -1] = num;
    }
}

void printLongNum(LongNum *num) {
    for (int i = num->len - 1; i >= 0; i--) {
        printf("%d", num->arr[i]);
    }
}

void addLongNums(LongNum *a, LongNum *b, LongNum *result) {
    int remember = 0;
    
    for (result->len = 0; result->len < a->len || result->len < b->len; (result->len)++) {
        int num = remember;
        if (result->len < a->len) {
            num += a->arr[result->len];
        }
        if (result->len < b->len) {
            num += b->arr[result->len];
        }
        remember = num / 10;
        result->arr[result->len] = num % 10;
    }


    while (remember > 0) {
        result->arr[result->len] = remember % 10;
        remember = remember / 10;
        result->len++;
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

void multiplyLongNums(LongNum *a, LongNum *b, LongNum *result) {
    if (a->len == 1 && a->arr[0] == 0) {
        *result = newLongNum(0);
        return;
    }

    LongNum res = newLongNum(0);

    for (int i = a->len - 1; i >= 0; i--) {
        LongNum c_res;
        multiplyLongNumAndInt(10, &res, &c_res);
        res = c_res;
        multiplyLongNumAndInt(a->arr[i], b, &c_res);
        
        addLongNums(&res, &c_res, result);
        res = *result;
    }

    normalizeLongNum(result);
}


int main() {
    LongNum a, b, res;

    scanLongNum(&a);
    scanLongNum(&b);

    multiplyLongNums(&a, &b, &res);

    printLongNum(&res);

    return 0;
}