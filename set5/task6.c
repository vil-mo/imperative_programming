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

void addLongNums(LongNum a, LongNum b, LongNum *result) {
    
    int remember = 0;
    
    for (result->len = 0; result->len < a.len || result->len < b.len; (result->len)++) {
        int num = remember;
        if (result->len < a.len) {
            num += a.arr[result->len];
        }
        if (result->len < b.len) {
            num += b.arr[result->len];
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

void multiplyLongNumAndInt(int a, LongNum b, LongNum *result) {
    LongNum res = newLongNum(0);
    res.len = b.len;
    for (int i = 0; i < b.len; i++) {
        res.arr[i] = a * b.arr[i];
    }

    addLongNums(res, newLongNum(0), result);
}

void printLongNum(LongNum num) {
    for (int i = num.len - 1; i >= 0; i--) {
        printf("%d", num.arr[i]);
    }
}


int main() {
    int n;
    scanf("%d", &n);

    LongNum a = newLongNum(1);
    LongNum res;


    for (int i = 2; i <= n; i++) {
        multiplyLongNumAndInt(i, a, &res);
        a = res;
    }


    printLongNum(a);
    printf("\n");

    return 0;
}