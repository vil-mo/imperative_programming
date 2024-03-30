#include <stdint.h>

extern int R;
int64_t Sum(int, int);


// находит самый длинный отрезок с началом в l и суммой не более sum
// возвращает правый край искомого отрезка
int Query(int l, int64_t sum) {
    int min = l + 1, max = R + 1;

    while (min < max) {
        int i = (min + max) / 2;

        if (Sum(l, i) <= sum) {
            min = i + 1;
        } else {
            max = i;
        }
    }

    return min - 1;
}

