#include <stdio.h>
#include <math.h>
int nf;
int sign(double x)
{
    if(x>0)return 1;
    else if(x<0)return -1;
    return 0;
}

double f9(double x)
{
    nf++;
    return x*x+pow(x-1,5);
}
double f10(double x)
{
    nf++;
    return cos(x)-x*exp(x);
}
double f13(double x)
{
    nf++;
    return x*x*x*x+sin(x);
}
int chord_method(double *x,double a,double b, double (*f)(double),double eps)
{
    double fa,fb,fc,c[2];
    int i =0,sfa,sfb,sfc,k;
    c[0]=a;c[1]=b;fa=f(a);fb=f(b);
    if(fabs(fa)<eps){*x=a;return 1;}
    if(fabs(fb)<eps){*x=b;return 1;}
    sfa = sign(fa);sfb=sign(fb);
    if(sfa*sfb==1)return 0;

    for(k=1;fabs(c[1]-c[0])>eps;k++)
    {
        i=!i;
        c[i]=(a*fb-b*fa)/(fb-fa);
        fc = f(c[i]);sfc = sign(c[i]);
        if(fabs(fc)<eps){*x=c[i];return k+1;}
        if(sfa*sfc==1){a=c[i];fa=fc;}
        else{b=c[i];fb=fc;}
    }
    *x=c[i];
    return k;
}
int nyuton_method(double *x,double a,double b, double (*f)(double),double (*d1f)(double),double (*d2f)(double),double (*od1f)(double),double eps)
{
    int k;
    double xn;double xnplus1;double hn;
    xn=(a+b)/2;
    double fa;double fb;double d1fxn;double d2fxn;double fxn;
    fa = f(a);fb=f(b);d1fxn=d1f(xn);d2fxn=d2f(xn);fxn=f(xn);
    if(fa*fb>=0)return -1;
    if(d1fxn==0||d2fxn==0)return -2;
    if(fxn*d2fxn<=0)return -3;
    for(k=0;fabs(xnplus1-xn)<eps;k++)
    {
        if(xnplus1<xn)b=xn;
        else a=xnplus1;
        xn=(a+b)/2;
        hn=-1*od1f(xn)*f(xn);
        xnplus1=xn+hn;
    }
    *x = xn;
    return k;
}
int main()
{
    FILE *fout = fopen("output.txt","w");
    double x,y,z;
    nf=0;
    int res9 = chord_method(&x,0,2,f9,1.e-15);
    fprintf(fout, "9)x: %lg ", x);
    fprintf(fout, "iteration: %d ", res9);
    fprintf(fout, "call: %lg ", nf);
    fprintf(fout, "abs err: %lg ", x-0.3459548158482420);
    fprintf(fout, "rel err: %lg \n", (x-0.3459548158482420)/0.3459548158482420);
    nf=0;
    int res10 = chord_method(&y,0,2,f10,1.e-15);
    fprintf(fout, "10)x: %lg ", y);
    fprintf(fout, "iteration: %d ", res10);
    fprintf(fout, "call: %lg ", nf);
    fprintf(fout, "abs err: %lg ", x-0.5177573636824583);
    fprintf(fout, "rel err: %lg \n", (x-0.5177573636824583)/0.5177573636824583);
    nf=0;
    int res13 = chord_method(&z,0,1,f13,1.e-15);
    fprintf(fout, "13)x: %lg ", y);
    fprintf(fout, "iteration: %d ", res13);
    fprintf(fout, "call: %lg ", nf);
    fprintf(fout, "abs err: %lg ", x-0);
    fprintf(fout, "rel err: я не знаю");
}
