#include <stdio.h>
#include <math.h>

int fact(int x);

double onedivsqrtn(int x)
{
    return 1.0 / sqrt(x);
}

double lnkdivk(int x)
{
    return log(x) / x;
}

double onedivk(int x)
{
    return 1.0 / x;
}

double onedivkvpow2(int x)
{
    return 1.0 / (x * x);
}

double onedivkvfact(int x)
{
    double temp = 1;
    for(int i = 1;i<=x;i++)
    {
        temp=temp/i;
    }
    return temp;
}

int findn(double(*f)(int), double eps,double* strsum,double* revsum)
{
    int n = 1;
    double psum;
    double osum;
    double last_psum = 0;
    double last_osum = 0;
    while (1)
    {
        psum = 0;
        osum = 0;
        for (int i = 1; i <= n; i++)
        {
            psum += f(i);
        }
        for (int i = n; i >= 1; i--)
        {
            osum += f(i);
        }
        if (fabs(psum - osum) > eps)
            break;
        last_psum = psum;
        last_osum = osum;
        n++;
    }
    *strsum=last_psum;
    *revsum=last_osum;
    return n;
}
int kfindn(double(*f)(int), double eps,double* strsum,double* revsum)
{
    int n = 1;
    double psum = 0.0;
    double osum = 0.0;
    *strsum = 0.0;
    *revsum = 0.0;

    while (1)
    {
        psum = 0;
        osum = 0;
        for (int i = 1; i <= n; i++)
        {
            psum += f(i)*pow(-1,i);
        }
        for (int i = n; i >= 1; i--)
        {
            osum += f(i)*pow(-1,i);
        }
        if (fabs(psum - osum) > eps)
            break;
        n++;
    }
    *strsum=psum;
    *revsum=osum;
    return n;
}
int main()
{
    double eps = 1e-16;
    double psum, osum;
    int n;

    n = findn(onedivsqrtn, eps, &psum, &osum);
    printf("1/sqrt(x) n = %d | str sum = %lg | rev sum = %lg\n", n, psum, osum);

    n = kfindn(onedivsqrtn, eps, &psum, &osum);
    printf("1/sqrt(x) n = %d | str sum = %lg | rev sum = %lg for (-1)^k\n", n, psum, osum);

    n = findn(lnkdivk, eps, &psum, &osum);
    printf("log(x)/x n = %d | str sum = %lg | rev sum = %lg\n", n, psum, osum);

    n = kfindn(lnkdivk, eps, &psum, &osum);
    printf("log(x)/x n = %d | str sum = %lg | rev sum = %lg for (-1)^k\n", n, psum, osum);

    n = findn(onedivk, eps, &psum, &osum);
    printf("1/x n = %d | str sum = %lg | rev sum = %lg\n", n, psum, osum);

    n = kfindn(onedivk, eps, &psum, &osum);
    printf("1/x n = %d | str sum = %lg | rev sum = %lg for (-1)^k\n", n, psum, osum);

    n = findn(onedivkvpow2, eps, &psum, &osum);
    printf("1/(x*x) n = %d | str sum = %lg | rev sum = %lg\n", n, psum, osum);

    n = kfindn(onedivkvpow2, eps, &psum, &osum);
    printf("1/(x*x) n = %d | str sum = %lg | rev sum = %lg for (-1)^k\n", n, psum, osum);

    n = findn(onedivkvfact, eps, &psum, &osum);
    printf("1/fact(x) n = %d | str sum = %lg | rev sum = %lg\n", n, psum, osum);

    n = kfindn(onedivkvfact, eps, &psum, &osum);
    printf("1/fact(x) n = %d | str sum = %lg | rev sum = %lg for (-1)^k\n", n, psum, osum);

    return 0;
}
