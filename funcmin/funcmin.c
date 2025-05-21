#include <stdio.h>
#include <math.h>
double func(double x)
{
    return (x+1)*(x+1);
}
double funcmin(double(*f)(double), double a, double b)
{
    double x1 = (3*a + b) / 4.0;
    double x2 = (a + b) / 2.0;
    double x3 = (a + 3*b) / 4.0;
    double f1 = f(x1);
    double f2 = f(x2);
    double f3 = f(x3);

    double ab = fabs(a - b);

    while (ab>1e-15||ab>1e-15*fabs(a+b)/2)
    {
        if (f1 < f2 && f1 < f3)
        {
            b = x2;
            x2 = x1;
            x1 = (3*a + b) / 4.0;
            x3 = (a + 3*b) / 4.0;
            f2 = f1;
            f1 = f(x1);
            f3 = f(x3);
        }
        else if (f3 < f2 && f3 < f1)
        {
            a=x2;
            x2=x3;
            x1 = (3*a + b) / 4.0;
            x3 = (a + 3*b) / 4.0;
            f2=f3;
            f1 = f(x1);
            f3 = f(x3);
        }
        else
        {
            a = x1;
            b = x3;
            x1 = (3*a + b) / 4.0;
            x2 = (a + b) / 2.0;
            x3 = (a + 3*b) / 4.0;
            f1 = f(x1);
            f2 = f(x2);
            f3 = f(x3);
        }
        ab = fabs(a - b);
    }

    return (a + b) / 2.0;
}
int main()
{
    printf("%lf",funcmin(func,-1,1));
}
