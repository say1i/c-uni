#include <stdio.h>
#include <math.h>
double kvadr_f(double a,double b,double(*f)(double))
{
	return ((b-a)/8)*(f(a)+3*f((2*a+b)/3)+3*f((a+b*2)/3)+f(b));
}
double drob(double x)
{
    return 1/x;
}
double polynom(double x)
{
    return 10/(1+25*x*x);
}
int main()
{
    double a,b,n;
	scanf("%lf",&a);
	scanf("%lf",&b);
	scanf("%lf",&n);
	double ssin = 0;
	double h = (b-a)/(n-1);
	double temp_x1 = a;
	for(double i = 0;i<=n;i+=h)
    {
        ssin+=kvadr_f(temp_x1,temp_x1+h,sin);
        temp_x1+=h;
    }
    double sdrob = 0;
	double temp_x2 = a;
	for(double i = 0;i<=n;i+=h)
    {
        sdrob+=kvadr_f(temp_x2,temp_x2+h,drob);
        temp_x2+=h;
    }
    double spolynom = 0;
	double temp_x3 = a;
	for(double i = 0;i<=n;i+=h)
    {
        spolynom +=kvadr_f(temp_x3,temp_x3+h,polynom);
        temp_x3+=h;
    }
    printf("sin %lf\n1/x %lf\n10/(1+25*x*x) %lf",ssin,sdrob,spolynom);
}
