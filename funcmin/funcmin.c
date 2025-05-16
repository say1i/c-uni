#include <stdio.h>
#include <math.h>
double func(double x)
{
    return (x+1)*(x+1);
}
double funcmin(double(*f)(double),double a,double b)
{

    double x1=3*a/4+b/4;
    double x2=(a+b)/2;
    double x3=a/4+3*b/4;
    double ab = fabs(a - b);
    while(ab>1e-15||ab>1e-15*fabs(a+b)/2)
    {
        double mas[5]={a,x1,x2,x3,b};
        double min = mas[0];
        int condition = 0;
        for(int i = 0;i < 5;i++)
        {
            if(f(mas[i])<f(min))
            {
                condition = i;
            }
        }
        if(condition==0||condition==1)
        {
            b=x2;
        }
        if(condition==2)
        {
            a=x1;
            b=x3;
        }
        if(condition==3||condition==4)
        {
            a=x2;
        }
        x1=3*a/4.0+b/4.0;
        x2=(a+b)/2.0;
        x3=a/4.0+3.0*b/4.0;
        ab=fabs(a-b);
    }
    return (a+b)/2.0;
}
int main()
{
    printf("%lf",funcmin(func,-1,1));
}
