#include <stdio.h>
#include <string.h>

typedef struct Node_s {
    char val[8];
    int next;
} Node;

int main() {
    int t;
    scanf("%d", &t);

    for (int t_ind = 0; t_ind < t; t_ind++) {
        int n, first, q;
        scanf("%d %d %d", &n, &first, &q);

        Node arr[10000];

        for (int i = 0; i < n; i++) {
            int next_ind;

            scanf("%s %d", &arr[i].val, &arr[i].next);
        }

        for (int i = 0; i < q; i++) {
            int command, index;
            scanf("%d %d", &command, &index);

            if (command == 0) {
                scanf(" %s", &arr[n].val);
                
                if (index == -1) {
                    arr[n].next = first;
                    first = n;
                } else {
                    arr[n].next = arr[index].next;
                    arr[index].next = n;
                }


                printf("%d\n", n);
                n++;

            } else {
                if (index == -1) {
                    first = arr[first].next;
                } else {
                    printf("%s\n", arr[arr[index].next].val);
                    arr[index].next = arr[arr[index].next].next;                    
                }
            }
        }

        printf("===\n");
        for (int i = first; i > -1; i = arr[i].next) {
            printf("%s\n", arr[i].val);
        }
        printf("===\n");
    }


    return 0;
}