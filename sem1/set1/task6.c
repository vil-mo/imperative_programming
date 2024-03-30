#include <stdio.h>

int main() {
    int n;
    scanf("%d", &n);

    int min_val = 99999999999999999;
    int min_ind = -1;
    int max_val = -99999999999999999;
    int max_ind = -1;

    for (int i=0; i<n; i++) {
        int a;
        scanf("%d", &a);

        if (a < min_val) {
            min_val = a;
            min_ind = i + 1;
        }
        if (a > max_val) {
            max_val = a;
            max_ind = i + 1;
        }
    }

    printf("%d %d %d %d\n", min_val, min_ind, max_val, max_ind);


    return 0;
}
