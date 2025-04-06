#include <stdio.h>

double kvadr_f(double a,double b,double (*f)(double))
{
    return ((b-a)/3)*f((a+b)/2-(sqrt(2)/4)*(b-a))+f((a+b)/2)+f((a+b)/2+(sqrt(2)/4)*(b-a));
}
double f0(double x)
{
    return 10;
}
double f1(double x)
{
    return x;
}
double f2(double x)
{
    return x*x;
}
double f3(double x)
{
    return x*x*x;
}
double f4(double x)
{
    return x*x*x*x;
}
double f5(double x)
{
    return x*x*x*x*x;
}
int main()
{

}
