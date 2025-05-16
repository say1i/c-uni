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
{double f0(double x)
{
	return 1;

}
double pf0(double x)
{
	return x;
}
double f1(double x)
{
	return x;
}
double pf1(double x)
{
	return x*x/2;
}
double f2(double x)
{
	return x*x;
}
double pf2(double x)
{
	return x*x*x/3;
}
double f3(double x)
{
	return x*x*x;
}
double pf3(double x)
{
	return x*x*x*x/4;
}
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
	printf("sdrob: %lf | idrob: %lf | rdrob: %lf\n",sdrob,idrob,rdrob);
	printf("ssin: %lf | isin: %lf | rsin: %lf\n",ssin,isin,rsin);
	printf("spolynom: %lf | ipolynom: %lf | rpolynom: %lf\n",spolynom,ipolynom,rpolynom);
	{/*double s0 = f(f0,a,b,n);
	double s1 = f(f1,a,b,n);
	double s2 = f(f2,a,b,n);
	double s3 = f(f3,a,b,n);

	double i0 = pf0(b)-pf0(a);
	double i1 = pf1(b)-pf1(a);
	double i2 = pf2(b)-pf2(a);
	double i3 = pf3(b)-pf3(a);

	double r0 = fabs(s0-i0);
	double r1 = fabs(s1-i1);
	double r2 = fabs(s2-i2);
	double r3 = fabs(s3-i3);

	printf("s0: %lf | i0: %lf | r0: %lf\n",s0,i0,r0);
	printf("s1: %lf | i1: %lf | r1: %lf\n",s1,i1,r1);
	printf("s2: %lf | i2: %lf | r2: %lf\n",s2,i2,r2);
	printf("s3: %lf | i3: %lf | r3: %lf\n",s3,i3,r3);*/}
}

