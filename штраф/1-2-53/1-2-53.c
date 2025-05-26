#include <stdio.h>

int main()
{
    FILE *fin = fopen("input.txt", "r");
    int n;
    fscanf(fin, "%d", &n);
    double prev, curr, next;

    fscanf(fin,"%lf", &prev);
    fscanf(fin,"%lf", &curr);
    int firstpos = -1;
    int lastpos = -1;
    int cond = 0;
    for(int i = 1; i < n-1;i++)
    {
        fscanf(fin,"%lf", &next);
        if(cond==0)
        {
            if (curr < prev && curr < next)
            {
                firstpos = i;
                cond = 1;
            }
        }
        if (curr < prev && curr < next)
        {
            lastpos = i;
        }
        prev = curr;
        curr = next;
    }
    if(lastpos==-1||firstpos==-1)
    {
        printf("no local\n");
        return 0;
    }
    if(lastpos==firstpos)
    {
        printf("one local\n");
        return 0;
    }
    printf("local min biggest distance %d\n",lastpos-firstpos);
    return 0;
}
