#include <stdio.h>

typedef struct Node_s
{
    char val[8];
    int key;
} Node;

void swap(Node *a, Node *b)
{
    Node v = *a;
    *a = *b;
    *b = v;
}

void _quicksort(Node *arr, int low, int high)
{
    if (low >= high) {
        return;
    }

    int secondpoint = -1;
    for (int m = low; m < high; m = secondpoint + 1)
    {
        int currSecondpoint = secondpoint;
        int flag = 1;
        for (int i = m; i < high; i++)
        {
            if (arr[i].key > arr[high].key)
            {
                secondpoint = i;
                for (int j = i + 1; j < high; j++)
                {
                    if (arr[j].key < arr[high].key)
                    {
                        swap(&arr[j], &arr[secondpoint]);
                        flag = 0;
                        break;
                    }
                }
                break;
            }
        }
        if (flag)
        {
            break;
        }
    }

    if (secondpoint >= 0)
    {
        swap(&arr[high], &arr[secondpoint]);
        _quicksort(arr, low, secondpoint - 1);
        _quicksort(arr, secondpoint + 1, high);   
    } else {
        _quicksort(arr, low, high - 1);
    }

}

void quicksort(Node *arr, int len)
{
    _quicksort(arr, 0, len - 1);
}

int main()
{
    int n;
    scanf("%d", &n);

    Node arr[n];

    for (int i = 0; i < n; i++)
    {
        scanf("%d %s", &arr[i].key, &arr[i].val);
    }

    quicksort(arr, n);

    for (int i = 0; i < n; i++)
    {
        printf("%d %s\n", arr[i].key, arr[i].val);
    }

    return 0;
}