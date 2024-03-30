#include "hashmap.h"
#include <stdlib.h>

// creates and returns new hash table with:
//  [ef] –- function which compares keys for equality
//  [hf] –- function which produces a hash for a key
//  [size] –- prescribed size/capacity of the hash table (number of cells)

__attribute__((visibility("default"))) HashMap HM_Init(EqualFunc ef, HashFunc hf, int size) {
    HashMap hm;

    hm.cap = size;
    hm.eqf = ef;
    hm.hashf = hf;

    hm.buf = calloc(size, sizeof(Bucket));
    
    return hm;
}


// frees memory of hash map [self]
// note: called exactly once for every hash map created by HM_Init
__attribute__((visibility("default"))) void HM_Destroy(HashMap *self) {
    free(self->buf);
}

// returns value corresponding to the specified key [key] in hash map [self]
// if [key] is not present in the map, then returns NULL
__attribute__((visibility("default"))) cpvoid HM_Get(const HashMap *self, cpvoid key) {
    uint32_t hash = self->hashf(key) % self->cap;

    if (self->buf[hash].key == NULL) {
        return NULL;
    }

    while (!self->eqf(key, self->buf[hash].key)) {
        hash = (hash + 1) % self->cap;

        if (self->buf[hash].key == NULL) {
            return NULL;
        }
    }

    return self->buf[hash].value;
}

// sets value [value] for the key [key] in hash map [self]
// if [self] already has some value for [key], it is overwritten
__attribute__((visibility("default"))) void HM_Set(HashMap *self, cpvoid key, cpvoid value) {
    uint32_t hash = self->hashf(key) % self->cap;

    while (self->buf[hash].key != NULL && !self->eqf(key, self->buf[hash].key)) {
        hash = (hash + 1) % self->cap;
    }

    self->buf[hash].key = key;
    self->buf[hash].value = value;
}
