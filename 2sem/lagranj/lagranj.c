#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double lagrange(double* x, double* fx, int n, double point) {
    double result = 0;
    for (int i = 0; i < n; i++) {
        double term = fx[i];
        for (int j = 0; j < n; j++) {
            if (j != i)
                term *= (point - x[j]) / (x[i] - x[j]);
        }
        result += term;
    }
    return result;
}

int main() {
    const int M = 100000;
    double max_error;
    double true_val, interp_val;

    for (int n = 2; n <= 20; n++) {
        double* x = (double*)malloc(n * sizeof(double));
        double* fx = (double*)malloc(n * sizeof(double));
        for (int i = 0; i < n; i++) {
            x[i] = (double)i / (n - 1);
            fx[i] = sin(x[i]);
        }
        max_error = 0.0;
        for (int j = 0; j <= M; j++) {
            double xi = (double)j / M;
            true_val = sin(xi);
            interp_val = lagrange(x, fx, n, xi);
            double err = fabs(true_val - interp_val);
            if (err > max_error)
                max_error = err;
        }

        printf("n %d | err %le\n", n, max_error);
    }

    return 0;
}

