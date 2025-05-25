#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double lagranj(double*xmas,double*fxmas,int n,double x)
{
    double*Fxmas=(double*)malloc(sizeof(double)*n);
    double mult;
    for(int i = 0;i<n;i++)
    {
        mult = 1;
        for(int j = 0; j < n;j++)
        {
            if(i==j)continue;
            mult *= (x - xmas[j]) / (xmas[i] - xmas[j]);
        }
        Fxmas[i] = mult;
    }
    double sum = 0;
    for(int i = 0; i < n;i++)
    {
        sum+=fxmas[i]*Fxmas[i];
    }
    return sum;
}
int main()
{
    int n = 2;
    double *xmas = (double *)malloc(sizeof(double) * n);
    double *fxmas = (double *)malloc(sizeof(double) * n);

    xmas[0] = 0;
    xmas[1] = 1;
    for(int i = 1; i < n-1;i++)
    {
        xmas[i]=i/100000;
    }
    for (int i = 0; i < n; i++)
    {
        fxmas[i] = sin(xmas[i]);
    }

    double max_error = 0;
    for (int j = 0; j <= n; j++) {
        double interp = lagranj(xmas, fxmas, n, xmas[j]);
        double error = fabs(interp - fxmas[j]);
        if (error > max_error)
            max_error = error;
    }

    printf("ln(x) = %le\nn = %d\nerror = %le\nnorma = %le\n", lagranj(xmas, fxmas, n, 0.5), n, fabs(sin(0.5) - lagranj(xmas, fxmas, n, 0.5)), max_error);

    return 0;
}
