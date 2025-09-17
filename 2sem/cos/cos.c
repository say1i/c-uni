#include <stdio.h>
#include <math.h>

double myCos(double x)
{
    if(x>M_PI)
    {
        while(x>M_PI)
        {
            x-=M_PI;
        }
    }
    if(x<1e-16||x==M_PI)return 1;
    if(x<0)
    {
        x-=M_PI;
    }
    double sum = 1.0;
    int i = 1;
    double h = 1;
    double eps = 1.e-16;
    do
    {
        h *= -x * x / ((2 * i - 1) * (2 * i));
        sum += h;
        i++;

    }
    while(fabs(h)>eps);
    return sum;
}
double absCosErr(double x)
{
    return fabs(cos(x)-myCos(x));
}
double relCosErr(double x)
{
    return fabs(absCosErr(x)/cos(x));
}
int main()
{
    double x = 1;
    FILE *fout = fopen("output.txt", "w");
    do
    {
        fprintf(fout, "x: %lg ", x);
        fprintf(fout, "cos(x): %lg ", cos(x));
        fprintf(fout, "abs err: %lg ", absCosErr(x));
        fprintf(fout, "rel err: %lg ", relCosErr(x));
        fprintf(fout,"\n");
        x++;
    }
    while(absCosErr(x)<1.e-13&&relCosErr(x)<1.e-13);
    fprintf(fout, "x: %lg ", x);
    fprintf(fout, "cos(x): %lg ", cos(x));
    fprintf(fout, "abs err: %lg ", absCosErr(x));
    fprintf(fout, "rel err: %lg ", relCosErr(x));
    fprintf(fout,"\n");
    return 0;
}
