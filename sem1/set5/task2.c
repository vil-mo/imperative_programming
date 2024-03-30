#include <stdio.h>
#include <math.h>

int max(int a, int b) {
    if (a > b) {
        return a;
    }

    return b;
}

int main() {
    int q;
    scanf("%d", &q);



    for (int curr_q = 0; curr_q < q; curr_q++) {
        int n, k;
        scanf("%d %d", &n, &k);

        double arr[n+1];
        arr[0] = 1;
        for (int i=1; i <= n; i++) {
            arr[i] = 0;
        }

        for (int i=1; i<=n; i++) {
            const int numb = max(1, k - n + i);
            for (int j = k; j >= numb; j--) {
                arr[j] = arr[j] + arr[j-1];
            }
        }

        printf("%0.10g\n", arr[k]);

    }



    return 0;
}