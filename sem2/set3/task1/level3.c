#include "myblas.h"

//====== уровень 3 ======
// вычислить матрицу (alpha*A*B + beta*C) и записать её в C
// здесь A –- матрица размера m на k, B –- матрица размера k на n,
// C –- матрица размера m на n
void dgemm(int m, int n, int k, double alpha, const double *A, const double *B, double beta, double *C) {
    for (int mi = 0; mi < m; mi++) {
        for (int ni = 0; ni < n; ni++) {
            C[mi * n + ni] *= beta;

            for (int ki = 0; ki < k; ki++) {
                C[mi * n + ni] += alpha * A[mi * k + ki] * B[ki * n + ni];
            }
        }
    }
}
