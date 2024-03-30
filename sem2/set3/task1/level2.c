#include "myblas.h"

//====== уровень 2 ======
// вычислить вектор (alpha*A*X + beta*Y) длины m, и записать его в Y
// здесь A –- матрица размера m на n, X –- вектор длины n, а Y –- вектор длины m
void dgemv(int m, int n, double alpha, const double *A, const double *X, double beta, double *Y) {
    for (int y = 0; y < m; y++) {
        Y[y] *= beta;

        for (int x = 0; x < n; x++) {
            Y[y] += alpha * A[y * n + x] * X[x];
        }
    }
}

// вычислить матрицу (alpha*X*Yt + A) и записать её в A
// здесь Yt –- это транспонированный вектор Y, то есть записанный как вектор-строка
//  A –- матрица размера m на n, X –- вектор длины m, а Y –- вектор длины n
void dger(int m, int n, double alpha, const double *X, const double *Y, double *A) {
    for (int x = 0; x < m; x++) {
        for (int y = 0; y < n; y++) {
            A[x * n + y] += alpha * X[x] * Y[y];
        }
    }
}
