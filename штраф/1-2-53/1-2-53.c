#include <stdio.h>

int main()
{
    FILE *fin = fopen("input.txt", "r");
    int n;
    fscanf(fin, "%d", &n);
    double sec[n];
    for (int i = 0; i < n; i++) {
        fscanf(fin, "%lf", &sec[i]);
    }

    int local_min_first_index = 1;
    int local_min_last_index = 1;
    int local_max_first_index = 1;
    int local_max_last_index = 1;
    for (int i = 1; i < n - 1; i++) {
        if (sec[i - 1] < sec[i] && sec[i] > sec[i + 1])//local max
        {
            if(i>=local_max_last_index)local_max_last_index = i;
        }
        if (sec[i - 1] > sec[i] && sec[i] < sec[i + 1])//local min
        {
            if(i>=local_min_last_index)local_min_last_index = i;
        }
    }
    for (int i = 1; i < n - 1; i++) {
        if (sec[i - 1] < sec[i] && sec[i] > sec[i + 1])//local max
        {
            local_max_first_index = i;
            break;
        }
    }
    for (int i = 1; i < n - 1; i++) {
        if (sec[i - 1] < sec[i] && sec[i] > sec[i + 1])//local max
        {
            local_min_first_index = i;
            break;
        }
    }
    printf("local max biggest distance %d\n",local_max_last_index-local_max_first_index);
    printf("local min biggest distance %d\n",local_min_last_index-local_min_first_index);
    return 0;
}
