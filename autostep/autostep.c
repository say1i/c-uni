#include <stdio.h>
#include <math.h>
int steps = 0;
double qarant = 0;
double sredn = 0;

double kvadr_f(double a,double b,double(*f)(double))
{
	return ((b-a)/8)*(f(a)+3*f((2*a+b)/3)+3*f((a+b*2)/3)+f(b));
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
double autostep(double epsilon,double a, double b,double(*f)(double))
{
    int i = 1;
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
        delta = (fabs(i2-i1))/sp;
        if(delta<epsilon)
        {
            sum+=i2;
            a+=h;
            i++;
        }
        chi=pow(delta/epsilon,1/5);//недопонял как это связано с новым шагом
        if(chi>10)chi=10;
        if(chi<10)chi=0.1;
        h=(h*0.95)/chi;
    }

}
int main()
{

}
