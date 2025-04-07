#include <stdio.h>
#include <math.h>
double kvadr_f(double a,double b,double(*f)(double))
{
	return ((b-a)/8)*(f(a)+3*f((2*a+b)/3)+3*f((a+b*2)/3)+f(b));
}
double f0(double x)
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
double f4(double x)
{
	return x*x*x*x;
}
double pf4(double x)
{
	return x*x*x*x*x/5;
}
int main()
{
	double a,b;
	scanf("%lf",&a);
	scanf("%lf",&b);
	double s0=kvadr_f(a,b,f0);
	double s1=kvadr_f(a,b,f1);
	double s2=kvadr_f(a,b,f2);
	double s3=kvadr_f(a,b,f3);
	double s4=kvadr_f(a,b,f4);
	double i0 = pf0(b)-pf0(a);
	double i1 = pf1(b)-pf1(a);
	double i2 = pf2(b)-pf2(a);
	double i3 = pf3(b)-pf3(a);
	double i4 = pf4(b)-pf4(a);
	double r0 = fabs(s0-i0);
	double r1 = fabs(s1-i1);
	double r2 = fabs(s2-i2);
	double r3 = fabs(s3-i3);
	double r4 = fabs(s4-i4);
	printf("s0: %lf | i0: %lf | r0: %lf\n",s0,i0,r0);
	printf("s1: %lf | i1: %lf | r1: %lf\n",s1,i1,r1);
	printf("s2: %lf | i2: %lf | r2: %lf\n",s2,i2,r2);
	printf("s3: %lf | i3: %lf | r3: %lf\n",s3,i3,r3);
	printf("/////////////////////////////\n");
	printf("s4: %lf | i4: %lf | r4: %lf\n",s4,i4,r4);
}

