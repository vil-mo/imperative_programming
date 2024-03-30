#include <stdio.h>
#include <stdlib.h>

#define Scalar double

int main(int argc, char *argv[])
{
    int n;
    scanf("%d\n", &n);

    Scalar **equations = malloc(sizeof(Scalar *) * n);

    for (int i = 0; i < n; i++) {
        equations[i] = malloc(sizeof(Scalar) * (n + 1));

        for (int j = 0; j < n + 1; j++) {
            scanf("%lf", &equations[i][j]);
        }
    }


    for (int var_to_zero = 0; var_to_zero < n - 1; var_to_zero++) {
        for (int curr = var_to_zero + 1; curr < n; curr++) {
            
            if (equations[var_to_zero][var_to_zero] == 0) {
                Scalar *temp = equations[var_to_zero];
                equations[var_to_zero] = equations[curr];
                equations[curr] = temp;
                continue;
            }

            if (equations[curr][var_to_zero] == 0) {
                continue;
            }

            Scalar k_curr = equations[var_to_zero][var_to_zero] / equations[curr][var_to_zero];;
            for (int curr_var = var_to_zero; curr_var < n + 1; curr_var++) {
                equations[curr][curr_var] *= k_curr;
                equations[curr][curr_var] -= equations[var_to_zero][curr_var];
            }
        }
    }
    
    // for (int e = 0; e < n; e++) {
    //     for (int i = 0; i < n + 1; i++) {
    //         printf("%lf    ", equations[e][i]);
    //     }
    //     printf("\n");
    // }
    
    for (int eq = n - 1; eq >= 0; eq--) {
        for (int v = eq + 1; v < n; v++) {
            equations[eq][n] -= equations[eq][v] * equations[v][n];
        }
        equations[eq][n] /= equations[eq][eq];
    }

    for (int e = 0; e < n; e++) {
        printf("%0.15lf\n", equations[e][n]);
        free(equations[e]);
    }

    free(equations);

    return EXIT_SUCCESS;
}
