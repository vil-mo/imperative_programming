#include <stdio.h>
#include <stdlib.h>

int cmprfn(const int *a, const int *b)
{
    return *a - *b;
}

int main()
{
    int num[10] = {1, 9, 3, 10, 4, 4, 3, 3, 8, 3};

    printf("Original array:");

    for (int i = 0; i < 10; i++)
        printf(" %d", num[i]);
    printf("\n");

    int a = -10;

    qsort(num, 10, sizeof(int), &a);
    
    printf("Sorted array: ");
    for (int i = 0; i < 10; i++)
        printf("%d ", num[i]);

    return 0;
}
