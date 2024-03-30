#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define HASH_KEY int32_t

#define RAW_TYPE Bucket

typedef struct Bucket {
    bool hasVal;
    HASH_KEY key;
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

int hash(int32_t key, uint32_t mod) { 
    uint32_t h = 0;
    h += key;
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

typedef struct HashSet {
    RawVec buf;
    int len;
} HashSet;

void hashSetInit(HashSet *self) {
    rawInit(&self->buf);
    self->len = 0;
}

void hashSetInitWithCapasity(HashSet *self, int withCap) {
    rawInitWithCapasity(&self->buf, withCap);
    self->len = 0;

    for (int i = 0; i < self->buf.cap; i++) {
        self->buf.arr[i].hasVal = false;
    }
}

void hashSetFree(HashSet *self) { rawFree(&self->buf); }

Bucket *hashSetGetBucket(HashSet *self, HASH_KEY key) {
    int hashedKey = hash(key, self->buf.cap);

    Bucket *bucket = &self->buf.arr[hashedKey];
    while (bucket->hasVal && bucket->key != key) {
        hashedKey = (hashedKey + 1) % self->buf.cap;
        bucket = &self->buf.arr[hashedKey];
    }

    return bucket;
}

bool hashSetHas(HashSet *self, HASH_KEY key) {
    Bucket *bucket = hashSetGetBucket(self, key);

    return bucket->hasVal;
}

bool hashSetInsert(HashSet *self, HASH_KEY key) {
    Bucket *bucket = hashSetGetBucket(self, key);

    if (bucket->hasVal) {
        return true;
    }

    bucket->key = key;
    bucket->hasVal = true;
    self->len++;

    return false;
}

HASH_KEY *hashSetKeys(HashSet *self) {
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

//--------------
//
// main
//
//-------------

int main() {
    FILE *in = fopen("input.bin", "rb");
    FILE *out = fopen("output.bin", "wb");

    HashSet set;
    hashSetInitWithCapasity(&set, 2000000);

    int32_t n;
    fread(&n, 4, 1, in);

    int32_t *values = malloc(n * 4);
    int arr_i = 0;

    for (int i = 0; i < n; i++) {
        int32_t elem;
        fread(&elem, 4, 1, in);

        if (!hashSetInsert(&set, elem)) {
            values[arr_i] = elem;
            arr_i++;
        }
    }

    fwrite(&arr_i, 4, 1, out);
    fwrite(values, 4, set.len, out);

    free(values);
    hashSetFree(&set);

    fclose(in);
    fclose(out);

    return 0;
}
