#include <stdio.h>



typedef struct Node_s {
    float val;
    int next;
} Node;

int main() {
    int n, f;
    scanf("%d %d", &n, &f);

    Node arr[n];

    for (int i = 0; i < n; i++) {
        float val;
        int next_ind;

        scanf("%f %d", &arr[i].val, &arr[i].next);
    }

    
    for (int i = f; i > -1; i = arr[i].next) {
        
        printf("%0.3lf\n", arr[i].val);
    }

    return 0;
}