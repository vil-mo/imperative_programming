#include <stdio.h>
#include <stdlib.h>

#define dx 0.000000001

double Function(double x);

int main(int argc, char *argv[])
{
    FILE *in = fopen("input.txt", "r");
    FILE *out = fopen("output.txt", "w");

    int m;
    fscanf(in, "%d", &m);

    for (int i = 0; i < m; i++) {
        double x;
        fscanf(in, "%lf", &x);

        double y = Function(x);

        double x0;
        if (x > 0.5) {
            x0 = x - dx;
        } else {
            x0 = x + dx;
        }

        double y0 = Function(x0);

        double dy;
        if (x > 0.5) {
            dy = y - y0;
        } else {
            dy = y0 - y;
        }

        double proizv = dy / dx;

        fprintf(out, "%lf\n", proizv);
    }

    fclose(in);
    fclose(out);

    return EXIT_SUCCESS;
}
