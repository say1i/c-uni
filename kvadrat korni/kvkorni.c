#include <stdio.h>
#include <math.h>
int sign(double x) {
    if (x > 0) return 1;
    if (x < 0) return -1;
    return 0;
}
 int kvadr(double b, double c, double *x1, double *x2)
 {
    double d;
    d=b*b-4*c;
    if(d<0) return 0;

    *x1=(-b+sign(b)*sqrt(d))/2.0;
    *x2 = c / (*x1);

    return 1;
 }
  int wrongKvadr(double b, double c, double *x1, double *x2)
 {
    double d;
    d=b*b-4*c;
    if(d<0) return 0;

    *x1=(-b+sqrt(d))/2;
    *x2=(-b-sqrt(d))/2;

    return 1;
 }
int main() {
    double x1, x2,iks1,iks2,c,q,b;

    scanf("%lg", &x1);
    scanf("%lg", &x2);

    b=-( x1+ x2);
    c=x1*x2;

    kvadr(b,c,&iks1,&iks2);
    double abs1=fabs(x1-iks1);
    double abs2=fabs(x2-iks2);

    double rel1=fabs(x1/iks1-1);
    double rel2=fabs(x2/iks2-1);
    printf("x1 tochnoe=%lg\nx2 tochnoe=%lg\n", x1, x2);

    printf("x1=%lg\nx2=%lg\n", x1, x2);

    printf("abs err1=%lg\nabs err2=%lg\n", abs1, abs2);
    printf("rel err1=%lg\nrel err2=%lg\n", rel1, rel2);
}
