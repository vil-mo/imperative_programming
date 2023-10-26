#include <stdio.h>

int binarySearch(int *arr, int len, int num)
{
    int left = 0;
    int right = len;

    while (1)
    {
        int curr = (left + right) / 2;
        if (arr[curr] == num && arr[curr + 1] != num)
        {
            return curr;
        }

        if (curr == left)
        {
            return -1;
        }

        if (arr[curr] > num)
        {
            right = curr;
        }
        else
        {
            left = curr + 1;
        }
    }
}

int main()
{
    int n, q;
    scanf("%d", &n);

    int arr[n];
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &arr[i]);
    }

    scanf("%d", &q);

    int last_r = 0;

    for (int i = 0; i < q; i++)
    {
        int x;
        scanf("%d", &x);

        int y = x + last_r;

        int r = binarySearch(arr, n, y);

        printf("%d\n", r);

        last_r = r;
    }

    return 0;
}