#include "integerset.h"
#include <stdint.h>
#include <stdlib.h>

uint32_t hash(int num, int cap) {
    const uint32_t A = 2654435769U; // округлённое до целого phi * 2^32
    uint32_t x = (A * num);         // умножаем по модулю 2^32 (за счёт переполнения)
    return x % cap;                 // берём старшие s битов --- получаем номер ячейки
}

IntegerSet *CreateSet(int *buf, int len) {
    IntegerSet *set_ptr = calloc(sizeof(IntegerSet) + len * 2 * sizeof(int), 1);
    set_ptr->cap = len * 2;
    set_ptr->max_i_diff = 0;
    set_ptr->zero_in = 0;

    int *set = (int *)&set_ptr[1];

    for (int i = 0; i < len; i++) {
        if (0 == buf[i]) {
            if (set_ptr->zero_in) {
                free(set_ptr);
                return NULL;
            }

            set_ptr->zero_in = 1;
            continue;
        }

        uint32_t i_inSet = hash(buf[i], set_ptr->cap);

        int i_diff = 0;
        while (set[i_inSet] != 0) {
            if (set[i_inSet] == buf[i]) {
                free(set_ptr);
                return NULL;
            }
            i_inSet++;
            i_inSet %= set_ptr->cap;

            i_diff++;
        }

        if (i_diff > set_ptr->max_i_diff) {
            set_ptr->max_i_diff = i_diff;
        }

        set[i_inSet] = buf[i];
    }

    return set_ptr;
}

int IsInSet(IntegerSet *set_ptr, int val) {
    if (set_ptr == NULL || set_ptr->cap == 0) {
        return 0;
    }
    if (val == 0) {
        return set_ptr->zero_in;
    }

    int *set = (int *)&set_ptr[1];

    uint32_t i_inSet = hash(val, set_ptr->cap);

    for (int i = 0; set[i_inSet] != val && i < set_ptr->max_i_diff; i++) {
        i_inSet++;
        i_inSet %= set_ptr->cap;
    }

    return set[i_inSet] == val;
}
