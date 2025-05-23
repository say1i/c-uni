#include <stdio.h>
#include <math.h>
int steps;
double qarant;
double sredn;
double f(double x)
{
    return sqrt(1+pow(x,5))+sqrt(1-pow(x,5));
}
double kvadr_f(double a,double b,double(*f)(double))
{
	return ((b-a)/8)*(f(a)+3*f((2*a+b)/3)+3*f((a+b*2)/3)+f(b));
}
int sign(double x)
{
    if(x>0)return 1;
    else if(x<0)return -1;
    return 0;
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

double chord_method(double a,double b, double (*f)(double),double eps,double alpha)
{
    double x = 0.0;
    double fa,fb,fc,c[2];
    int i =0,sfa,sfb,sfc;
    c[0]=a;c[1]=b;fa=autostep(eps,0,a,f)-alpha;fb=autostep(eps,0,b,f)-alpha;
    if(fabs(fa)<eps){x=a;return x;}
    if(fabs(fb)<eps){x=b;return x;}
    sfa = sign(fa);sfb=sign(fb);
    if(sfa*sfb==1){printf("метод не применим");return -1;}

    for(int k=1;fabs(c[1]-c[0])>eps;k++)
    {
        i=!i;
        c[i]=(a*fb-b*fa)/(fb-fa);
        fc = autostep(eps,0,c[i],f)-alpha;sfc = sign(fc);
        if(fabs(fc)<eps){x=c[i];return k+1;}
        if(sfa*sfc==1){a=c[i];fa=fc;}
        else{b=c[i];fb=fc;}
    }
    x=c[i];
    return x;
}

double itog(double epsilon,double alpha,double a,double b,double(*f)(double))
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
    double fx=0.0,fxplush=0.0;
    while(a<b)
    {
        if(a+h>b)h=b-a;
        i1= kvadr_f(a,a+h,f);
        i2 = kvadr_f(a,a+h/2.0,f)+kvadr_f(a+h/2.0,a+h,f);
        delta = (i2-i1)/sp;
        fx = sum;
        if(fabs(delta)<=epsilon)
        {
            if(delta<0)qarant+=-delta;
            else qarant+=delta;
            sredn+=delta;
            a+=h;
            sum+=i2;
            fxplush=sum;
            if(fabs(fx)<=alpha)
            {
                return a;
            }
            if(fxplush>alpha)
            {
                break;
            }
            steps++;
        }
        chi=pow(fabs(delta)/epsilon,1.0/5.0);
        if(chi>10)chi=10;
        if(chi<0.1)chi=0.1;
        h = h * 0.95 / chi;
    }

    printf("%lf\n",a);
    printf("%lf\n",a+h);

    return chord_method(a,a+h,f,epsilon,alpha);
}
int main()
{
    printf("%lf",itog(1e-16,1.970191,0,1,f));
}
