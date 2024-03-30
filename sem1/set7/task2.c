#include <stdio.h>
#include <math.h>

//какой-нибудь целочисленный тип (желательно беззнаковый)
typedef unsigned int bitword ;
int bitword_size = sizeof(bitword) * 8;

int bitwordIdxToArrIdx(int idx) {
    return idx / (bitword_size);
}

bitword bitInArrElem(int idx) {
    return 1 << idx;
}

//инициализирует массив битов длины num, устанавливая все его биты в ноль
void bitsetZero ( bitword * arr , int num ) {
    int arrIdxNum = bitwordIdxToArrIdx(num);
    for (int i = 0; i <= arrIdxNum; i++) {
        arr[i] = 0;
    }
}

//возвращает значение idx-ого бита (0 или 1)
int bitsetGet ( const bitword * arr , int idx ) {
    if ((arr[bitwordIdxToArrIdx(idx)] & bitInArrElem(idx)) != 0) {
        return 1;
    }

    return 0;
}

//устанавливает значение idx-ого бита в newval (которое равно 0 или 1)
void bitsetSet ( bitword * arr , int idx , int newval ) {
    int arrIdx = bitwordIdxToArrIdx(idx);
    bitword bit = bitInArrElem(idx);
    
    //0101 1010 & 1111 0111
    arr[arrIdx] = arr[arrIdx] & (~bit);
    arr[arrIdx] += bit * newval;
}
//возвращает 1, если среди битов с номерами k
//для left <= k < right есть единичный, и 0 иначе
int bitsetAny ( const bitword * arr , int left , int right ) {
    int leftIdx = bitwordIdxToArrIdx(left);
    int rightIdx = bitwordIdxToArrIdx(right);
    

    


    if (leftIdx == rightIdx) {
        for (int currElem = left % bitword_size; currElem < right % bitword_size; currElem++) {
            int bit = bitInArrElem(currElem);

            if ((arr[leftIdx] & bit) != 0) {
                return 1;
            }
        }
        return 0;    
    }

    for (int currElem = left % bitword_size; currElem < bitword_size; currElem++) {
        int bit = bitInArrElem(currElem);

        if ((arr[leftIdx] & bit) != 0) {
            return 1;
        }
    }

    for (int currIdx = leftIdx + 1; currIdx < rightIdx; currIdx++) {
        if ((arr[currIdx]) != 0) {
            return 1;
        }
    }

    for (int currElem = 0; currElem < right % bitword_size; currElem++) {
        int bit = bitInArrElem(currElem);

        if ((arr[rightIdx] & bit) != 0) {
            return 1;
        }
    }


    return 0;
}


int main() {

    int n;
    scanf("%d", &n);

    bitword arr[bitwordIdxToArrIdx(20000000) + 1];


    for (int i = 0; i < n; i++) {
        int command;
        scanf("%d", &command);

        switch (command)
        {

        case 0: {
            int num;
            scanf("%d", &num);
            bitsetZero(arr, num);
        } break;

        case 1: {
            int idx;
            scanf("%d", &idx);
            printf("%d\n", bitsetGet(arr, idx));
        } break;

        case 2: {
            int idx, newval;
            scanf("%d %d", &idx, &newval);
            bitsetSet(arr, idx, newval);
        } break;

        case 3: {
            int left, right;
            scanf("%d %d", &left, &right);
            if (bitsetAny(arr, left, right)) {
                printf("some\n");
            } else {
                printf("none\n");
            }
        } break;
        
        default: break;
        }

    }
}