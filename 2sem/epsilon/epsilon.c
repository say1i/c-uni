#include  <stdio.h>
void printBits(void *a)
{
    int i; unsigned long long x;
    x=*(unsigned long long *)a;
    for( i=63; i>=0; i--) {
        if((x & ((unsigned long long)1 << i)) != 0) printf("1");
        else printf("0");
        if( i==63 ) printf(" ");
        if( i==62 ) printf(" ");
        if( i==52 ) printf(" ");
    }
}

int main(void) {
    double x = 1.0, b;
    int i = 0;


    do {
        printf("%d: %le\n", i, x);  // Вывод x
        printBits(&x); printf("\n"); // Вывод битов x
        b = 1.0 + x;
        printBits(&b); printf("\n"); // Вывод битов 1 + x
        x /= 2.0; // Делим x на 2
        i--; // Уменьшаем счётчик
    }
    while (1.0 + x > 1.0);
    b = 1.0 + x;
    printBits(&b); printf("\n");

    return 0;
}
