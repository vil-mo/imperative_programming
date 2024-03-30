#include "hashmap.h"
#include <stdlib.h>

#define DEFAULT_CAP 43
#define LOAD_FACTOR 0.75

#define hash(self, val) self->hashf(self->context, val) % self->cap;
#define cmp(self, a, b) self->eqf(self->context, a, b)

#define max(a, b) (a) > (b) ? (a) : (b)

static void BV_reserve(BucketVec *self, int cap) {
    if (self->cap < cap) {
        self->cap = max(cap, self->cap * 1.5);
        self->buf = realloc(self->buf, self->cap * sizeof(Bucket));
    }
}

static void BV_push(BucketVec *self, Bucket item) {
    BV_reserve(self, self->len + 1);

    self->buf[self->len] = item;
    self->len += 1;
}



// creates and returns new hash table with:
//  [ef] –- function which compares keys for equality
//  [hf] –- function which produces a hash for a key
//  [size] –- prescribed size/capacity of the hash table (number of cells)
__attribute__((visibility("default"))) HashMap HM_Init(EqualFunc ef, HashFunc hf, void *context) {
    HashMap hm;

    hm.cap = 0;
    hm.load = 0;
    hm.eqf = ef;
    hm.hashf = hf;
    hm.context = context;

    hm.buf = NULL;
    
    return hm;
}


// frees memory of hash map [self] and resets it to empty state
// it is allowed to use any operations on the table afterwards
__attribute__((visibility("default"))) void HM_Clear(HashMap *self) {
    for (int i = 0; i < self->cap; i++) {
        if (self->buf[i].buf != NULL) {
            free(self->buf[i].buf);
        }
    }
    free(self->buf);

    self->load = 0;
    self->cap = 0;
    self->buf = NULL;
}

static inline void HM_Reallocate(HashMap *self, int new_cap) {
    int old_cap = self->cap;
    BucketVec *old_buf = self->buf;

    self->load = 0;
    self->cap = new_cap;
    self->buf = calloc(new_cap, sizeof(BucketVec));

    for (int i = 0; i < old_cap; i++) {
        if (old_buf[i].buf == NULL) {
            continue;
        }

        for (int j = 0; j < old_buf[i].len; j++) {
            Bucket cur_el = old_buf[i].buf[j];
            if (cur_el.value == NULL) {
                continue;
            }

            int h = hash(self, cur_el.key);
            BV_push(&self->buf[h], cur_el);
            self->load += 1;
        }
   }

    free(old_buf);
}

static void HM_CheckReservation(HashMap *self) {
    if (self->cap * LOAD_FACTOR <= self->load) {
        int new_cap = max(DEFAULT_CAP, self->cap * 2);

        HM_Reallocate(self, new_cap);
    }
}

// returns value corresponding to the specified key [key] in hash map [self]
// if [key] is not present in the map, then returns NULL
__attribute__((visibility("default"))) cpvoid HM_Get(const HashMap *self, cpvoid key) {
    if (self->cap == 0) {
        return NULL;
    }

    int h = hash(self, key);

    for (int i = 0; i < self->buf[h].len; i++) {
        if (cmp(self, self->buf[h].buf[i].key, key)) {
            return self->buf[h].buf[i].value;
        }
    }

    return NULL;
}

// sets value [value] for the key [key] in hash map [self]
// if [self] already has some value for [key], it is overwritten
__attribute__((visibility("default"))) void HM_Set(HashMap *self, cpvoid key, cpvoid value) {
    self->load += 1;
    HM_CheckReservation(self);

    int h = hash(self, key);

    for (int i = 0; i < self->buf[h].len; i++) {
        if (cmp(self, self->buf[h].buf[i].key, key)) {
            self->buf[h].buf[i].value = value;
            return;
        }
    }

    Bucket b;
    b.value = value;
    b.key = key;
    BV_push(&self->buf[h], b);
}

// removes key [key] from the table [self]
// returns the value corresponding to key [key] before removal
// if key [key] is not present, then nothing is done, and NULL is returned
__attribute__((visibility("default"))) cpvoid HM_Remove(HashMap *self, cpvoid key) {
    if (self->cap == 0) {
        return NULL;
    }

    int h = hash(self, key);
    for (int i = 0; i < self->buf[h].len; i++) {
        if (cmp(self, self->buf[h].buf[i].key, key)) {
            cpvoid temp = self->buf[h].buf[i].value;
            self->buf[h].buf[i].value = NULL;

            return temp;
        }
    }


    return NULL;
}

