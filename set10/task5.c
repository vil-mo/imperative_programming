#include <stdio.h>

#define PRESISION 0.000000000001

double sin_tailor(double x, double result, double last_elem, int n) {
    double next_elem = -1 * last_elem * x * x / (n * (n + 1));

    double new_result = result + next_elem;

    double diff = new_result - result;
    if (-PRESISION < diff && diff < PRESISION) {
        return new_result;
    }

    return sin_tailor(x, new_result, next_elem, n + 2);
}

double mysin(double x) {
    return sin_tailor(x, x, x, 2);
}

int main(int argc, char *argv[])
{
    int n;
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        double x;
        scanf("%lf", &x); 

        printf("%0.15lf\n", mysin(x));
    }


    return 0;
}
