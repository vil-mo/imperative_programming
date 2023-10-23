#include <stdio.h>
#include <string.h>

typedef struct Node_s {
    int val;
    int next;
    int prev;
} Node;

int main() {
    int t;
    scanf("%d", &t);

    Node arr[1000000];
    
    for (int t_ind = 0; t_ind < t; t_ind++) {
        int n, first, last, q;
        scanf("%d %d %d %d", &n, &first, &last, &q);
        n++;

        arr[0].next = first + 1;
        arr[0].prev = last + 1;

        for (int i = 1; i < n; i++) {
            scanf("%d %d %d", &arr[i].val, &arr[i].next, &arr[i].prev);
            arr[i].next++;
            arr[i].prev++;
        }

        for (int i = 0; i < q; i++) {
            int command, index;
            scanf("%d %d", &command, &index);
            index++;

            switch (command) {
                case 0: {

                    printf("%d\n", arr[index].val);
                    int next = arr[index].next;
                    int prev = arr[index].prev;
                    arr[next].prev = prev;
                    arr[prev].next = next;
                    
                    break;
                }
                case 1: {
                    scanf(" %d", &arr[n].val);

                    arr[n].next = arr[index].next;
                    arr[n].prev = index;
                    arr[arr[index].next].prev = n;    
                    arr[index].next = n;

                    printf("%d\n", n - 1);
                    n++;

                    break;
                }
                case -1: {
                    scanf(" %d", &arr[n].val);

                    arr[n].next = index;
                    arr[n].prev = arr[index].prev;
                    arr[arr[index].prev].next = n;
                    arr[index].prev = n;
                    
                    printf("%d\n", n - 1);
                    n++;

                    break;
                }

                default: break;
            }
        }

        printf("===\n");
        for (int i = arr[0].next; i != 0; i = arr[i].next) {
            printf("%d\n", arr[i].val);
        }
        printf("===\n");
    }


    return 0;
}