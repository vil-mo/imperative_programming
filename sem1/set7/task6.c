#include <stdio.h>

typedef struct Node_s {
    struct Node_s *next;
    int value;
} Node;

int main() {
    int n, k;
    scanf("%d %d", &n, &k);

    Node arr[n];
    for (int i = 0; i < n; i++) {
        arr[i].value = i + 1;
        arr[i].next = &arr[(i + 1) % n];
    }

    Node * currNode = &arr[n - 1];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < k - 1; j++) {
            currNode = currNode->next;
        }
        printf("%d\n", currNode->next->value);
        currNode->next = currNode->next->next;
    }

    return 0;
}