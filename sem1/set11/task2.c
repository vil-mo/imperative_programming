#include <stdio.h>
#include <stdlib.h>

typedef void (*callback)(void *ctx, int *value);

void arrayForeach(void *ctx, callback func, int *arr, int n) {
    for (int i = 0; i < n; i++) {
        func(ctx, &arr[i]);
        ;
    }
}

typedef struct Node {
    struct Node *next;
    int value;
} Node;

void listForeach(void *ctx, callback func, Node *list) {
    if (list == NULL) {
        return;
    }
       
    func(ctx, &(list->value));
    listForeach(ctx, func, list->next);
}

void sum(int *ctx, int *value) {
    if (*value % 2 == 0) {
        (*ctx) += *value;
    }
}

int main() {
    int n;
    scanf("%d", &n);

    int *arr = malloc(n * sizeof(int));
    Node list;

    Node *current_list = &list;
    for (int i = 0; i < n; i++) {
        int value;
        scanf("%d", &value);

        arr[i] = value;
        current_list->value = value;

        current_list->next = malloc(sizeof(Node));
        current_list = current_list->next;
    }
    current_list->next = NULL;

    int arraySum = 0;
    int listSum = 0;
    arrayForeach(&arraySum, (callback)sum, arr, n);
    listForeach(&listSum, (callback)sum, &list);

    printf("%d %d", arraySum, listSum);

    return 0;
}
