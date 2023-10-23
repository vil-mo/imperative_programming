#include <stdio.h>
#include <stdlib.h>

typedef struct Node_s {
    char val[8];
    int key;
} Node;

int nodeCmpFn(const Node *arg1, const Node *arg2) {
    return arg1->key - arg2->key;
}


int main() {
    int n;
    scanf("%d", &n);

    Node arr[n];

    for (int i = 0; i < n; i++) {
        scanf("%d %s", &arr[i].key, &arr[i].val);
    }

    qsort(arr, n, sizeof(Node), &nodeCmpFn);

    for (int i = 0; i < n; i++) {
        printf("%d %s\n", arr[i].key, arr[i].val);    
    }

    return 0;
}