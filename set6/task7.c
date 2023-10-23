#include <stdio.h>
#include <malloc.h>

typedef struct Node_s {
    struct Node_s *prev, *next;
    void *value;
} Node;

typedef Node List;

void initList(List *list) {
    list->prev = list;
    list->next = list;
}

Node *addAfter(Node *node, void *ptr) {
    Node *new_node = malloc(sizeof(Node));
    new_node->prev = node;
    new_node->next = node->next;

    new_node->prev->next = new_node;
    new_node->next->prev = new_node;

    new_node->value = ptr;

    return new_node;
}

Node *addBefore(Node *node, void *ptr) {
    Node *new_node = malloc(sizeof(Node));
    new_node->prev = node->prev;
    new_node->next = node;

    new_node->prev->next = new_node;
    new_node->next->prev = new_node;

    new_node->value = ptr;

    return new_node;
}

void *erace(Node *node) {
    node->prev->next = node->next;
    node->next->prev = node->prev;

    void *val = node->value;
    free(node);
    return val;
}


int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);


    int t;
    scanf("%d", &t);

    Node* arr[100000];


    for (int t_ind = 0; t_ind < t; t_ind++) {
        int q;
        scanf("%d", &q);

        List list;
        initList(&list);

        arr[0] = &list;
        int arr_i = 1;

        for (int i = 0; i < q; i++) {
            int command, index;
            scanf("%d %d", &command, &index);
            index++;

            switch (command) {
                case 0: {
                    free(erace(arr[index]));

                    break;
                }
                case 1: {
                    int *val = malloc(sizeof(int));
                    scanf(" %d", val);

                    arr[arr_i] = addAfter(arr[index], val);
                    arr_i++;

                    break;
                }
                case -1: {
                    int *val = malloc(sizeof(int));
                    scanf(" %d", val);

                    arr[arr_i] = addBefore(arr[index], val);
                    arr_i++;

                    break;
                }

                default: break;
            }
        }

        Node* next;
        for (Node* x = list.next; x != &list; x = next) {
            next = x->next;
            int* val = erace(x);
            printf("%d\n", *val);
            free(val);
        }
        
        printf("===\n");
    }

    
    fclose(stdin);
    fclose(stdout);

    return 0;
}