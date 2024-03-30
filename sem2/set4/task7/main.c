#include "hashmap.h"
#include <assert.h>
#include <string.h>

#define INTOF(ptr) (*(int *)(ptr))

int IntModEqualFunc(void *context, cpvoid a, cpvoid b) { return (INTOF(a) - INTOF(b)) % INTOF(context) == 0; }

uint32_t IntModHashFunc(void *context, cpvoid key) {
    int t = INTOF(key) % INTOF(context);
    if (t < 0)
        t += INTOF(context);
    return t * 0xDEADBEEF;
}

int main() {
    int MOD = 1000;
    HashMap h = HM_Init(IntModEqualFunc, IntModHashFunc, &MOD);

    int data[] = {13, 174, 1013, -987, 0, 1};
    HM_Set(&h, &data[0], " hello ");
    HM_Set(&h, &data[1], " world ");
    assert(strcmp(HM_Get(&h, &data[2]), " hello ") == 0);

    const char *old = HM_Remove(&h, &data[3]);
    assert(old && strcmp(old, " hello ") == 0);
    assert(HM_Get(&h, &data[0]) == 0);

    old = HM_Remove(&h, &data[2]);
    assert(!old);

    HM_Set(&h, &data[4], " zero ");
    assert(strcmp(HM_Get(&h, &data[4]), " zero ") == 0);
    assert(strcmp(HM_Get(&h, &data[1]), " world ") == 0);

    HM_Set(&h, &data[5], " one ");
    assert(HM_Get(&h, &data[0]) == 0);

    HM_Clear(&h); // note: frees memory
    assert(HM_Get(&h, &data[5]) == 0);
    assert(HM_Remove(&h, &data[3]) == 0);

    HM_Set(&h, &data[1], " newtable ");
    HM_Set(&h, &data[1], " newtableX ");
    assert(strcmp(HM_Get(&h, &data[1]), " newtableX ") == 0);
}
