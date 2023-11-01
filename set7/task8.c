#include <stdio.h>
#include <malloc.h>

typedef struct MyDoubleHeapElem_s
{
    double val;
    struct MyDoubleHeapElem_s *next;
} MyDoubleHeapElem;

typedef struct MyDoubleHeap_s
{
    MyDoubleHeapElem *arr;
    MyDoubleHeapElem *freeHeap;
    MyDoubleHeapElem *allocatedHeap;
} MyDoubleHeap;

MyDoubleHeap initAllocator(int slotsCount)
{
    MyDoubleHeap heap;
    heap.arr = malloc(slotsCount * sizeof(MyDoubleHeapElem));

    for (int i = 0; i < slotsCount - 1; i++)
    {
        heap.arr[i].next = &heap.arr[i + 1];
    }
    heap.arr[slotsCount - 1].next = NULL;

    heap.freeHeap = &heap.arr[0];
    heap.allocatedHeap = NULL;

    return heap;
}

// запросить блок памяти под число типа double
double *allocDouble(MyDoubleHeap *heap)
{
    MyDoubleHeapElem *elem = heap->freeHeap;

    if (elem == NULL)
    {
        return NULL;
    }

    heap->freeHeap = heap->freeHeap->next;

    elem->next = heap->allocatedHeap;
    heap->allocatedHeap = elem;

    return &elem->val;
}

// освободить блок памяти, на который смотрит заданный указатель
void freeDouble(MyDoubleHeap *heap, double *ptr)
{
    MyDoubleHeapElem *elemPtr = heap->allocatedHeap;

    if (&elemPtr->val == ptr)
    {
        heap->allocatedHeap = elemPtr->next;
    }
    else
    {

        while (&elemPtr->next->val != ptr)
        {
            elemPtr = elemPtr->next;
        }
        MyDoubleHeapElem *el = elemPtr->next;
        elemPtr->next = elemPtr->next->next;
        elemPtr = el;
    }
    elemPtr->next = heap->freeHeap;
    heap->freeHeap = elemPtr;
}

double *idToHeap[301000];

int main()
{
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);


    int n, q;
    scanf("%d %d", &n, &q);

    MyDoubleHeap heap = initAllocator(n);

    for (int i = 0; i < q; i++)
    {
        int command;
        scanf("%d", &command);

        switch (command)
        {
        case 0:
        {
            double *val = allocDouble(&heap);
            if (val != NULL)
            {
                scanf("%lf", val);
                printf("%p\n", val);
            }
            else
            {
                double trash;
                scanf("%lf", &trash);
                printf("00000000\n");
            }
            idToHeap[i] = val;
        }
        break;

        case 1:
        {
            int indx;
            scanf("%d", &indx);

            freeDouble(&heap, idToHeap[indx]);
        }
        break;

        case 2:
        {
            int indx;
            scanf("%d", &indx);

            printf("%5lf\n", *idToHeap[indx]);
        }
        break;

        default:
            break;
        }
    }

    free(heap.arr);


    fclose(stdin);
    fclose(stdout);


    return 0;
}