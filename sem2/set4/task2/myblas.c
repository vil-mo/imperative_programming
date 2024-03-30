#include "cblas.h"

void cblas_dgemm(
    OPENBLAS_CONST enum CBLAS_ORDER Order, 
    OPENBLAS_CONST enum CBLAS_TRANSPOSE TransA, 
    OPENBLAS_CONST enum CBLAS_TRANSPOSE TransB, 
    OPENBLAS_CONST blasint M, 
    OPENBLAS_CONST blasint N, 
    OPENBLAS_CONST blasint K, 
    OPENBLAS_CONST double alpha, 
    OPENBLAS_CONST double *A, 
    OPENBLAS_CONST blasint lda, 
    OPENBLAS_CONST double *B, 
    OPENBLAS_CONST blasint ldb, 
    OPENBLAS_CONST double beta, 
    double *C, 
    OPENBLAS_CONST blasint ldc
) {
    for (int mi = 0; mi < M; mi++) {
        for (int ni = 0; ni < N; ni++) {
            C[mi * N + ni] *= beta;

            for (int ki = 0; ki < K; ki++) {
                C[mi * K + ni] += alpha * A[mi * K + ki] * B[ki * K + ni];
            }
        }
    }
}
