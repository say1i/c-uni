#include <stdio.h>
#include <stdlib.h>
int main()
{
    int n;
    scanf("%d",&n);
    double* matrix = (double*)malloc(n*n*sizeof(double));
    for(int i = 0; i < n;i++)
    {
        for(int j = 0; j < n;j++)
        {
            if(i>n/2&&j<n/2)
            {
                matrix[i*n+j]=0;
            }
            else
            {
                matrix[i*n+j]=1/(1+i+j);
            }
        }
    }
    for(int i = 0; i < n;i++)
    {
        for(int j = 0; j < n;j++)
        {
            printf("%lf ",matrix[i*n+j]);
        }
        printf("\n");
    }
}
