#include <stdio.h>
#include <math.h>
double onedivsqrtn(int x)
{
    return 1/sqrt(x);
}
double lnkdivk(int x)
{
    return log(x)/x;
}
double onedivk(int x)
{
    return 1/x;
}
double onedivkvpow2(int x)
{
    1/(x*x);
}
double onedivkvfact(int x)
{
    return 1/fact(x);
}
int fact(int x)
{
    if (x == 1) return 1;
    return x * fact(x - 1);
}

int findn(double(*f)(int), double eps)
{
    int n = 1;
    while (1)
    {
        double psum = 0;
        double osum = 0;
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
        n++;
    }
    return n;
}
int main()
{
    double eps = 1e-16;
    printf("1/sqrt(x) :%d\n",findn(onedivsqrtn,eps));
    printf("log(x)/x :%d\n",findn(lnkdivk,eps));
    printf("1/x :%d\n",findn(onedivk,eps));
    printf("1/(x*x) :%d\n",findn(onedivkvpow2,eps));
    printf("1/fact(x) :%d\n",findn(onedivkvfact,eps));
}
