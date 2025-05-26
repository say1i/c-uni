#include <stdio.h>
#include <math.h>
int steps;
double qarant;
double sredn;
double f(double x)
{
    return 3 * x * sin(x*x*x) + 3 * x;
}
double ftest(double x)
{
	return x*x;
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

double chord_method(double a,double b, double (*func)(double),double eps,double alpha,double help)
{
    double x = 0.0;
    double fa,fb,fc,c[2];
    int i =0,sfa,sfb,sfc;
    c[0]=a;c[1]=b;
    fa = help + kvadr_f(a, c[0], func) - alpha;
    fb = help + kvadr_f(a, c[1], func) - alpha;
    sfa = sign(fa);sfb=sign(fb);
    if(sfa*sfb==1){printf("метод не применим");return -1;}
printf("a %0.20f\n",a);
printf("b %0.20f\n",b);
    for(int k=1;fabs(c[1]-c[0])>eps;k++)
    {
        i=!i;
        c[i] = (c[0] * fb - c[1] * fa) / (fb - fa);
        fc = help + kvadr_f(a,c[i],func)-alpha;
        sfc = sign(fc);
        printf("%0.20f\n",c[i]);
        if(fabs(fc)<eps){x=c[i];return x;}
        if(sfa*sfc==1){a=c[i];fa=fc;}
        else{b=c[i];fb=fc;}
    }
    x=c[i];
    return x;
}

double itog(double epsilon, double alpha, double a, double b, double(*func)(double))
{
    steps = 0;
    qarant = 0;
    sredn = 0;
    double sum = 0;
    double i1;
    double i2;
    double delta;
    double chi;
    double h = 0.1;
    int sp = 15;

    while (a < b) {
        if (a + h > b) h = b - a;

        i1 = kvadr_f(a, a + h, func);
        i2 = kvadr_f(a, a + h / 2.0, func) + kvadr_f(a + h / 2.0, a + h, func);
        delta = (i2 - i1) / sp;
        printf("%lf\n",a);
        if (fabs(delta) <= epsilon) {
            if (delta < 0) qarant += -delta;
            else qarant += delta;
            sredn += delta;

            steps++;
            sum += i2;
            if (fabs(sum - alpha) <= epsilon)
            {
                printf("\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\ \n");
                return a+h;
            }
            if (sum >= alpha)
            {
                printf("%lf\n",sum);
                printf("\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\ \n");
                return chord_method(a, a + h, func, epsilon, alpha,sum-i2);
            }
            printf("a+h=%lf sum=%.15lf\n", a+h, sum);
            a += h;
        }

        chi = pow(fabs(delta) / epsilon, 1.0 / 5.0);
        if (chi > 10) chi = 10;
        if (chi < 0.1) chi = 0.1;
        h = h * 0.95 / chi;
    }
    return b;
}

int main()
{
    printf("x=%lf",itog(1e-16,0.999989,0,6,f));

}
