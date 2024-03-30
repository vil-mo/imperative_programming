#ifndef HASHMAP_2323984
#define HASHMAP_2323984

#include <inttypes.h>

// pointer to key or value (untyped)
typedef const void *cpvoid;

// returns 1 if and only if two keys pointed by [a] and [b] are equal
// returns 0 otherwise
typedef int (*EqualFunc)(void *context, cpvoid a, cpvoid b);

// returns 32-bit hash of a key pointed by [key]
typedef uint32_t (*HashFunc)(void *context, cpvoid key);



typedef struct Bucket {
    cpvoid key;
    cpvoid value;
} Bucket;

typedef struct {
    int cap;
    int len;
    Bucket *buf;
}BucketVec;

typedef struct {
    int cap;
    int load;
    EqualFunc eqf;
    HashFunc hashf;
    void *context;

    BucketVec *buf;
} HashMap;



// creates and returns new hash table with:
//  [ef] –- function which compares keys for equality
//  [hf] –- function which produces a hash for a key
//  [context] –- a pointer which is passed to HashFunc and EqualFunc
HashMap HM_Init(EqualFunc ef, HashFunc hf, void *context);

// frees memory of hash map [self] and resets it to empty state
// it is allowed to use any operations on the table afterwards
void HM_Clear(HashMap *self);

// returns value corresponding to the specified key [key] in hash map [self]
// if [key] is not present in the map, then returns NULL
cpvoid HM_Get(const HashMap *self, cpvoid key);

// sets value [value] for the key [key] in hash map [self]
// if [self] already has some value for [key], it is overwritten
void HM_Set(HashMap *self, cpvoid key, cpvoid value);

// removes key [key] from the table [self]
// returns the value corresponding to key [key] before removal
// if key [key] is not present, then nothing is done, and NULL is returned
cpvoid HM_Remove(HashMap *self, cpvoid key);


#endif // !HASHMAP_2323984
