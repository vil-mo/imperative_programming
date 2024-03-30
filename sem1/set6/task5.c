#include <stdio.h>
#include <malloc.h>

typedef struct Node_s {
    char val[8];
    struct Node_s *next;
} Node;


int main() {
    int n;
    scanf("%d", &n);

    Node* arr[1000001];
    Node* last[1000001];
    for (int i = 0; i < 1000001; i++) {
        arr[i] = NULL;
        last[i] = NULL;
    }


    Node nodes[n];

    for (int i = 0; i < n; i++) {
        int index;
        scanf("%d %s", &index, &nodes[i].val);
        nodes[i].next = NULL;


        if (arr[index] == NULL) {
            arr[index] = &nodes[i];
            last[index] = &nodes[i];
        } else {
            last[index]->next = &nodes[i];
            last[index] = &nodes[i];
        }

    }


    for (int i = 0; i < 1000001; i++) {
        for (Node *node = arr[i]; node != NULL; node = node->next) {
            printf("%d %s\n", i, node->val);
        }
    }

    return 0;
}