#include <stdio.h>
#include <math.h>

double myExp(double x)
{
    if(x==0)return 1;
    int xPos = 1;
    if(x<0)
    {
        x*=-1;
        xPos=0;
    }
    double sum = 1.0;//сумма начинается с 1 тк 1^0/0!=1
    double h = x;//то куда записываются временные значения изначально юудет x^1/1!=x
    double eps = 1.e-16;
    int i = 2;
    do
    {
        sum+=h;
        h*=x;//типо возводим в степень
        h/=i;//типо делим на факториал
        i++;//для нашего типо факториала
    }
    while(fabs(h)>eps);
    if(xPos==0)
    {
        return 1/sum;
    }
    return sum;
}
double wrongExp(double x)
{
    double sum=1.0, h, eps=1.e-16; int i=2;
    h=x;
    do
    {
        sum+=h;
        h*=x/i;
        i++;
    }
    while( fabs(h)>eps );
    return sum;
}
double absExpErr(double x)
{
    return fabs(exp(x)-myExp(x));
}
double relExpErr(double x)
{
    return fabs(absExpErr(x)/exp(x));
}
int main()
{
    double x[8] = {1, 10, 40, 50, -1, -10, -40, -50};
    FILE *fout = fopen("output.txt", "w");
    for (int i = 0; i < 8; i++)
    {
        fprintf(fout, "x: %lg ", x[i]);
        fprintf(fout, "exp(x): %lg ", exp(x[i]));
        fprintf(fout, "abs err: %lg ", absExpErr(x[i]));
        fprintf(fout, "rel err: %lg ", relExpErr(x[i]));
        fprintf(fout,"\n");
    }
fprintf(fout,".......................\n");
    for (int i = 0; i < 8; i++)
    {
        fprintf(fout, "x: %lg ", x[i]);
        fprintf(fout, "exp(x): %lg ", exp(x[i]));
        fprintf(fout, "abs err: %lg ", exp(x[i])-wrongExp(x[i]));
        fprintf(fout, "rel err: %lg ", exp((x[i])-wrongExp(x[i]))/exp(x[i]));
        fprintf(fout,"\n");
    }
    return 0;
}

