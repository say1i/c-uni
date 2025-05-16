#include <stdio.h>
#include <stdlib.h>
void multondigit(double x,double**matrix,double**result,int n)
{
	for(int i = 0; i < n;i++)
	{
		for(int j = 0; j < n;j++)
		{
			result[i][j]=x*matrix[i][j];
		}
	}
}
void multmatrix(double** matrix1, double** matrix2, double** result, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            double sum = 0;
            for (int k = 0; k < n; k++) {
                sum += matrix1[i][k] * matrix2[k][j];
            }
            result[i][j] = sum;
        }
    }
}
void summatrix(double**matrix1,double**matrix2,double**result,int n)
{
	for(int i = 0; i< n;i++)
	{
		for(int j = 0; j < n;j++)
		{
			result[i][j]=matrix1[i][j]+matrix2[i][j];
		}
	}
}
int main()
{
	int n;
	FILE* fin  = fopen("output.txt","r");
    fscanf(fin,"%d",&n);
    double** matrix1 = (double**)malloc(n*sizeof(double));
    for(int i = 0; i < n;i++)
    {
		matrix1[i]=(double*)malloc(n*sizeof(double));
		for(int j = 0;j<n;j++)
		{
			fscanf(fin,"%lf",&matrix1[i][j]);
		}
	}
	double** matrix2 = (double**)malloc(n*sizeof(double));
    for(int i = 0; i < n;i++)
    {
		matrix2[i]=(double*)malloc(n*sizeof(double));
		for(int j = 0;j<n;j++)
		{
			fscanf(fin,"%lf",&matrix2[i][j]);
		}
	}
	double** result = (double**)malloc(n*sizeof(double));
    for(int i = 0; i < n;i++)
    {
		result[i]=(double*)malloc(n*sizeof(double));
	}
	printf("sum\n");
	summatrix(matrix1,matrix2,result,n);
	for(int i = 0; i < n;i++)
    {
        for(int j = 0; j < n;j++)
        {
            printf("%lf ",result[j][i]);
        }
        printf("\n");
    }
    printf("multiply\n");
	multmatrix(matrix1,matrix2,result,n);
	for(int i = 0; i < n;i++)
    {
        for(int j = 0; j < n;j++)
        {
            printf("%lf ",result[j][i]);
        }
        printf("\n");
    }
    printf("multiply to digit\n");
	multondigit(3,matrix1,result,n);
	for(int i = 0; i < n;i++)
    {
        for(int j = 0; j < n;j++)
        {
            printf("%lf ",result[j][i]);
        }
        printf("\n");
    }
}
