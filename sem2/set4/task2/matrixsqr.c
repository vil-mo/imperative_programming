#include "cblas.h"

void MatrixSqr(int n, const double *A, double *R) {
    cblas_dgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans, n, n, n, 1, A, n, A, n, 1, R, n);

    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            double r = R[i*n+j];
            if (-0.00000000000000001 < r && r < 0.00000000000000001){
                R[i*n+j] = 0;
            }
        }
    }
}
