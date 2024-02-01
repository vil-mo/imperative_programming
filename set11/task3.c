#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define HASH_KEY uint64_t
#define HASH_VAL uint32_t 

#define RAW_TYPE Bucket

typedef struct Bucket {
    bool hasVal;
    HASH_KEY key;
    HASH_VAL value;
} Bucket;

//--------------------
//
// RawVec
//
// -------------------

int min(int a, int b) {
    if (a < b) {
        return a;
    }
    return b;
}
int max(int a, int b) {
    if (a > b) {
        return a;
    }
    return b;
}

typedef struct RawVec {
    int cap;
    RAW_TYPE *arr;
} RawVec;

void rawInit(RawVec *self) {
    self->cap = 0;
    self->arr = NULL;
}

void rawFree(RawVec *self) {
    if (self->arr != NULL) {
        free(self->arr);
    }

    rawInit(self);
}

void rawResize(RawVec *self, int newCap) {
    if (self->arr == NULL) {
        self->arr = malloc(sizeof(RAW_TYPE) * newCap);
    } else {
        self->arr = realloc(self->arr, sizeof(RAW_TYPE) * newCap);
    }

    self->cap = newCap;
}

void rawInitWithCapasity(RawVec *self, int withCap) {
    self->cap = withCap;
    self->arr = malloc(withCap * sizeof(RAW_TYPE));
}

void rawReserve(RawVec *self, int newCap) {
    if (newCap <= self->cap) {
        return;
    }

    if (self->cap == 0) {
        newCap = max(newCap, 4);
    } else {
        newCap = max(newCap, self->cap * 2);
    }
    rawResize(self, newCap);
}

//-------------
//
// hash
//
//-------------

int hash(int64_t key, uint32_t mod) { 
    uint32_t h = 0;
    h += key;
    h += key >> 32;
    h += h << 10;
    h ^= h >> 6;
    h += h << 3;
    h ^= h >> 11;
    h += h << 15;
    return h % mod;
}

//---------------
//
// HashMap
//
//---------------

typedef struct HashMap {
    RawVec buf;
    int len;
} HashMap;

void hashMapInit(HashMap *self) {
    rawInit(&self->buf);
    self->len = 0;
}

void hashMapInitWithCapasity(HashMap *self, int withCap) {
    rawInitWithCapasity(&self->buf, withCap);
    self->len = 0;

    for (int i = 0; i < self->buf.cap; i++) {
        self->buf.arr[i].hasVal = false;
    }
}

void hashMapFree(HashMap *self) { rawFree(&self->buf); }

Bucket *hashMapGetBucket(HashMap *self, HASH_KEY key) {
    int hashedKey = hash(key, self->buf.cap);

    Bucket *bucket = &self->buf.arr[hashedKey];
    while (bucket->hasVal && bucket->key != key) {
        hashedKey = (hashedKey + 1) % self->buf.cap;
        bucket = &self->buf.arr[hashedKey];
    }

    return bucket;
}

bool hashMapGet(HashMap *self, HASH_KEY key, HASH_VAL *out) {
    Bucket *bucket = hashMapGetBucket(self, key);

    (*out) = bucket->value;

    return bucket->hasVal;
}

bool hashMapHas(HashMap *self, HASH_KEY key) {
    Bucket *bucket = hashMapGetBucket(self, key);

    return bucket->hasVal;
}

bool hashMapAdd(HashMap *self, HASH_KEY key, HASH_VAL value) {
    Bucket *bucket = hashMapGetBucket(self, key);

    if (bucket->hasVal) {
        return true;
    }

    bucket->value = value;
    bucket->key = key;
    bucket->hasVal = true;
    self->len++;

    return false;
}

bool hashMapInsert(HashMap *self, HASH_KEY key, HASH_VAL value) {
    Bucket *bucket = hashMapGetBucket(self, key);

    bucket->value = value;

    if (bucket->hasVal) {
        return true;
    }

    bucket->key = key;
    bucket->hasVal = true;
    self->len++;

    return false;
}

HASH_KEY *hashMapKeys(HashMap *self) {
    HASH_KEY *arr = malloc(self->len * sizeof(HASH_KEY));
    int arr_i = 0;

    for (int i = 0; i < self->buf.cap; i++) {
        if (self->buf.arr[i].hasVal) {
            arr[arr_i] = self->buf.arr[i].key;
            arr_i++;
            if (arr_i == self->len) {
                return arr;
            }
        }
    }

    return arr;
}

HASH_VAL *hashMapValues(HashMap *self) {
    HASH_VAL *arr = malloc(self->len * sizeof(HASH_VAL));
    int arr_i = 0;

    for (int i = 0; i < self->buf.cap; i++) {
        if (self->buf.arr[i].hasVal) {
            arr[arr_i] = self->buf.arr[i].value;
            arr_i++;
            if (arr_i == self->len) {
                return arr;
            }
        }
    }

    return arr;
}



//--------------
// 
// state
// 
//--------------

uint64_t nextState(uint64_t s, uint64_t a, uint64_t b, uint64_t c, uint64_t m) {
    return (s * s * a + s * b + c) % m;
}


//--------------
//
// main
//
//-------------

int main(int argc, char *argv[])
{
    uint64_t m, a, b, c;
    scanf("%llu\n%llu %llu %llu", &m, &a, &b, &c);
    
    uint64_t state = 1;
    int32_t step = 0;

    HashMap map;
    hashMapInitWithCapasity(&map, 4000000);

    while (!hashMapAdd(&map, state, step)) {
        state = nextState(state, a, b, c, m);
        step++;
    }

    uint32_t val;
    hashMapGet(&map, state, &val);
    printf("%u %u", val, step);

    hashMapFree(&map);

    return EXIT_SUCCESS;
}
