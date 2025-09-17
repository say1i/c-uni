#include <stdio.h>
#include <math.h>
int steps;
double qarant;
double sredn;

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
double f(double x)
{
    return sqrt(1+pow(x,5))+sqrt(1-pow(x,5));
}
double autostep(double epsilon,double a, double b,double(*f)(double))
{
    steps=0;
    qarant=0;
    sredn=0;
    double sum = 0;
    double i1;
    double i2;
    double delta;
    double chi;
    double h = 0.1;
    int sp = 15;//2^(5-1)-1
    while(a<b)
    {
        if(a+h>b)h=b-a;
        i1= kvadr_f(a,a+h,f);
        i2 = kvadr_f(a,a+h/2.0,f)+kvadr_f(a+h/2.0,a+h,f);
        delta = (i2-i1)/sp;
        if(fabs(delta)<=epsilon)
        {
            if(delta<0)qarant+=-delta;
            else qarant+=delta;
            sredn+=delta;
            sum+=i2;
            a+=h;
            steps++;
        }
        chi=pow(fabs(delta)/epsilon,1.0/5.0);//недопонял как это связано с новым шагом
        if(chi>10)chi=10;
        if(chi<0.1)chi=0.1;
        h = h * 0.95 / chi;
    }
    if(sredn<0)sredn*=-1;
    return sum;
}
double ftest(double x)
{
	return x*x;
}

int main()
{
    /*double a,b;

	scanf("%lf",&a);
	scanf("%lf",&b);
	double ssin7 = autostep(1e-7,a,b,sin);
    double sdrob7 = autostep(1e-7,a,b,drob);
    double spolynom7 = autostep(1e-7,a,b,polynom);

	double idrob7 = pdrob(b)-pdrob(a);
	double isin7 = -cos(b)+cos(a);
	double ipolynom7 = ppolynom(b)-ppolynom(a);

	double rdrob7 = fabs(sdrob7-idrob7);
	double rsin7 = fabs(ssin7-isin7);
	double rpolynom7 = fabs(spolynom7-ipolynom7);

	printf("e=10^-7\n");
	printf("my drob: %le | accurate drob: %le | drob error: %le | drob steps: %d | drob qarant: %le | drob sredn: %le\n",sdrob7,idrob7,rdrob7,steps,qarant,sredn);
    printf("my sin: %le | accurate sin: %le | sin error: %le | sin steps: %d | sin qarant: %le | sin sredn: %le\n",ssin7,isin7,rsin7,steps,qarant,sredn);
	printf("my polynom: %le | accurate polynom: %le | polynom error: %le | polynom steps: %d | polynom qarant: %le | polynom sredn: %le\n",spolynom7,ipolynom7,rpolynom7,steps,qarant,sredn);
	double ssin9 = autostep(1e-9,a,b,sin);
    double sdrob9 = autostep(1e-9,a,b,drob);
    double spolynom9 = autostep(1e-9,a,b,polynom);

	double idrob9 = pdrob(b)-pdrob(a);
	double isin9 = -cos(b)+cos(a);
	double ipolynom9 = ppolynom(b)-ppolynom(a);

	double rdrob9 = fabs(sdrob9-idrob9);
	double rsin9 = fabs(ssin9-isin9);
	double rpolynom9 = fabs(spolynom9-ipolynom9);

	printf("e=10^-9\n");
	printf("my drob: %le | accurate drob: %le | drob error: %le | drob steps: %d | drob qarant: %le | drob sredn: %le\n",sdrob9,idrob9,rdrob9,steps,qarant,sredn);
    printf("my sin: %le | accurate sin: %le | sin error: %le | sin steps: %d | sin qarant: %le | sin sredn: %le\n",ssin9,isin9,rsin9,steps,qarant,sredn);
	printf("my polynom: %le | accurate polynom: %le | polynom error: %le | polynom steps: %d | polynom qarant: %le | polynom sredn: %le\n",spolynom9,ipolynom9,rpolynom9,steps,qarant,sredn);

	double ssin11 = autostep(1e-11,a,b,sin);
    double sdrob11 = autostep(1e-11,a,b,drob);
    double spolynom11 = autostep(1e-11,a,b,polynom);

	double idrob11 = pdrob(b)-pdrob(a);
	double isin11 = -cos(b)+cos(a);
	double ipolynom11 = ppolynom(b)-ppolynom(a);

	double rdrob11 = fabs(sdrob11-idrob11);
	double rsin11 = fabs(ssin11-isin11);
	double rpolynom11 = fabs(spolynom11-ipolynom11);

	printf("e=10^-11\n");
	printf("my drob: %le | accurate drob: %le | drob error: %le | drob steps: %d | drob qarant: %le | drob sredn: %le\n",sdrob11,idrob11,rdrob11,steps,qarant,sredn);
    printf("my sin: %le | accurate sin: %le | sin error: %le | sin steps: %d | sin qarant: %le | sin sredn: %le\n",ssin11,isin11,rsin11,steps,qarant,sredn);
	printf("my polynom: %le | accurate polynom: %le | polynom error: %le | polynom steps: %d | polynom qarant: %le | polynom sredn: %le\n",spolynom11,ipolynom11,rpolynom11,steps,qarant,sredn);*/

	printf("%lf",autostep(1e-16,0,0.5,f));
}

