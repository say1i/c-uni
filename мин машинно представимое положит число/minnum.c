#include  <stdio.h>
void printBits(void *a)
{
    int i; unsigned long long x;
    x=*(unsigned long long *)a;
    for( i=63; i>=0; i--)
    {
        if((x & ((unsigned long long)1 << i)) != 0) printf("1");
        else printf("0");
        if( i==63 ) printf(" ");
        if( i==62 ) printf(" ");
        if( i==52 ) printf(" ");
    }
}

int main(void) {
    double a = 16.0;
    int i = 4;
    do
    {
        printf("%d: %le\n", i, a);
        printBits(&a); printf("\n");
        printBits(&b); printf("\n");
        a /= 2.0;
        i--;
    }
    while (a >0);
    printBits(&b); printf("\n");
    //минимум такой чтоб мантиса не нулевая


    return 0;
}
