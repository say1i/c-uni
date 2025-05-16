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
double pdrob(double x)
{
    return log(x);
}
double polynom(double x)
{
    return 10/(1+25*x*x);
}
double ppolynom(double x)
{
    return 2*atan(5*x);
}

double f(double(*f)(double),double a,double b,double n)
{
	double s = 0;
	double h = (b-a)/(n-1);
	double temp_x1 = a;
	for(int i = 0;i<n-1;i++)
    {
        s+=kvadr_f(temp_x1,temp_x1+h,f);
        temp_x1+=h;
    }
    return s;
}
int main()
{
    double a,b,n;
	scanf("%lf",&a);
	scanf("%lf",&b);
	scanf("%lf",&n);
	double ssin = f(sin,a,b,n);
    double sdrob = f(drob,a,b,n);
    double spolynom = f(polynom,a,b,n);

	double idrob = pdrob(b)-pdrob(a);
	double isin = -cos(b)+cos(a);
	double ipolynom = ppolynom(b)-ppolynom(a);

	double rdrob = fabs(sdrob-idrob);
	double rsin = fabs(ssin-isin);
	double rpolynom = fabs(spolynom-ipolynom);
	printf("my drob: %lf | accurate drob: %lf | drob error: %lf\n",sdrob,idrob,rdrob);
	printf("my sin: %lf | accurate sin: %lf | sin error: %lf\n",ssin,isin,rsin);
	printf("my polynom: %lf | accurate polynom: %lf | polynom error: %lf\n",spolynom,ipolynom,rpolynom);

}

