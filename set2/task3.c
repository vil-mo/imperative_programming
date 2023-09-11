#include <stdio.h>

int main() {
    double negative = 0;
    double zero = 0;
    double positive = 0;

    int n;
    scanf("%d", &n);

    for (int i=0; i<n; i++) {
        int num;
        scanf("%d", &num);
        if (num > 0) {
            positive++;
        } else if (num < 0) {
            negative++;
        } else {
            zero++;
        }
    }    

    double s = negative + zero + positive;
    negative /= s;
    zero /= s;
    positive /= s;

    printf ("%0.5lf %0.5lf %0.5lf\n", negative, zero, positive);

    return 0;
}