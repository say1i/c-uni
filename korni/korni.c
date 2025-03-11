#include <stdio.h>
#include <math.h>
int nf;
int sign(double x)
{
    if(x>0)return 1;
    else if(x<0)return -1;
    return 0;
}
double f1(double x)
{
    nf++;
    return pow(x-1,6)-1;
}
double df1(double x)
{
    nf++;
    return 6*pow(x-1,5);
}
double f3(double x)
{
    nf++;
    return cos(x)-x;
}
double df3(double x)
{
    nf++;
    return -sin(x)-1;
}
double f5(double x)
{
    nf++;
    return exp(x*x+7*x-30)-1;
}
double df5(double x)
{
    nf++;
    return (2*x+7)*exp(x*x+7*x-30);
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
int nyuton_method(double *x,double (*f)(double),double (*df)(double),double eps,double xn)
{
    int k;
    double xnplus1;
    for(k=1;k<20;k++)
    {
        xnplus1=xn-f(xn)/df(xn);
        if(fabs(xnplus1-xn)<eps){*x=xn;return k+1;}
        if(fabs(f(xn))<eps){*x=xn;return k+1;}
        xn = xnplus1;
    }
    return k;
}
int main()
{
    FILE *fout = fopen("output.txt","w");
    double x,y,z;
    nf=0;
    fprintf(fout,"chord method:\n");
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
    fprintf(fout, "abs err: %lg ", y-0.5177573636824583);
    fprintf(fout, "rel err: %lg \n", (y-0.5177573636824583)/0.5177573636824583);
    nf=0;
    int res13 = chord_method(&z,0,1,f13,1.e-15);
    fprintf(fout, "13)x: %lg ", z);
    fprintf(fout, "iteration: %d ", res13);
    fprintf(fout, "call: %lg ", nf);
    fprintf(fout, "abs err: %lg ", z-0);
    fprintf(fout, "rel err: я не знаю\n");
    /////////////////////////////////////////////
    double a,b,c;
    nf=0;
    fprintf(fout,"nyuton method:\n");
    int res1 = nyuton_method(&a,f1,df1,1.e-15,3.0);
    fprintf(fout, "1)x: %lg ", a);
    fprintf(fout, "iteration: %d ", res1);
    fprintf(fout, "call: %lg ", nf);
    fprintf(fout, "abs err: %lg ", a-0.3459548158482420);
    fprintf(fout, "rel err: %lg \n", (a-0.3459548158482420)/0.3459548158482420);
    nf=0;
    int res3 = nyuton_method(&b,f3,df3,1.e-15,2.0);;
    fprintf(fout, "5)x: %lg ", b);
    fprintf(fout, "iteration: %d ", res3);
    fprintf(fout, "call: %lg ", nf);
    fprintf(fout, "abs err: %lg ", b-0.5177573636824583);
    fprintf(fout, "rel err: %lg \n", (b-0.5177573636824583)/0.5177573636824583);
    nf=0;
    int res5 = nyuton_method(&c,f5,df5,1.e-15,2.0);;
    fprintf(fout, "5)x: %lg ", c);
    fprintf(fout, "iteration: %d ", res5);
    fprintf(fout, "call: %lg ", nf);
    fprintf(fout, "abs err: %lg ", c-0);
    fprintf(fout, "rel err: я не знаю");
}
