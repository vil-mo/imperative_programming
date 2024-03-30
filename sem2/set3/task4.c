#include <stdio.h>
#include <math.h>

typedef struct {
    double c0;
    double c1;
    double c2;
    double c3;
} CubicEq;

typedef struct {
    CubicEq x;
    CubicEq y;
    CubicEq z;

    double l;
    double r;
} Span;


double derivative(CubicEq *eq, double x) {
    return eq->c1 + 2 * eq->c2 * x + 3 * eq->c3 * x * x;
}

double f(Span *span, double x) {
    x -= span->l;

    double xs = derivative(&span->x, x);
    double ys = derivative(&span->y, x);
    double zs = derivative(&span->z, x);

    return sqrt(xs * xs + ys * ys + zs * zs);
}

double simpson(Span *span, double a, double b) {
    return ((b - a) / 6.0) * (f(span, a) + 4.0 * f(span, (a + b) / 2.0) + f(span, b));
}

double calculate(Span *span) {
    const int steps = 100;

    double increment = (span->r - span->l) / steps;

    double res = 0;

    for (double current = span->l + increment; current < span->r + increment / 2; current += increment) {
        res += simpson(span, current - increment, current);
    }
    return res;
}

int main() {
    int n;
    scanf("%d", &n);

    double sum = 0;

    for (int i = 0; i < n; i++) {
        Span currentSpan;

        scanf("%lf %lf", &currentSpan.l, &currentSpan.r);
        scanf("%lf %lf %lf %lf", &currentSpan.x.c0, &currentSpan.x.c1, &currentSpan.x.c2, &currentSpan.x.c3);
        scanf("%lf %lf %lf %lf", &currentSpan.y.c0, &currentSpan.y.c1, &currentSpan.y.c2, &currentSpan.y.c3);
        scanf("%lf %lf %lf %lf", &currentSpan.z.c0, &currentSpan.z.c1, &currentSpan.z.c2, &currentSpan.z.c3);

        sum += calculate(&currentSpan);
    }

    printf("%.15lf", sum);

    return 0;
}
