#include <stdio.h>

typedef struct {
    int len;
    int arr[500];
} LongNum;

LongNum newLongNum() {
    LongNum num;
    num.len = 1;
    num.arr[0] = 1;
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

    if (remember > 0) {
        result->arr[result->len] = remember;
        result->len++;
    }
}

void printLongNum(LongNum num) {
    for (int i = num.len - 1; i >= 0; i--) {
        printf("%d", num.arr[i]);
    }
}


int main() {
    int n;
    scanf("%d", &n);

    LongNum a = newLongNum();
    LongNum b = newLongNum();
    LongNum res;

    for (int i=0; i<n-2; i++) {
        addLongNums(a, b, &res);
        a = b;
        b = res;
    }
    printLongNum(b);
    printf("\n");

    return 0;
}