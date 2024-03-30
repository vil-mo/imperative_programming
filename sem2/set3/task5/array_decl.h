#define CONCAT2_EXPAND(A, B) A ## B
#define CONCAT2(A, B) CONCAT2_EXPAND(A, B)
#define NAME_FUNCTION(FN) CONCAT2(NAME, FN)


typedef struct {
    int n;     // number of elements in array
    int cap;
    TYPE *arr; // points to the array of elements
} NAME;

//initializes members of [vec] structure for empty array
void NAME_FUNCTION(_init) (NAME *vec);

// makes array [vec] empty and frees its array buffer [vec->arr]
// note: this function can be called many times
void NAME_FUNCTION(_destroy)(NAME *vec);

// adds element [value] to the end of array [vec]
// returns index of the added element
int NAME_FUNCTION(_push)(NAME *vec, TYPE value);

// removes the last element from array [vec]
// returns removed element
TYPE NAME_FUNCTION(_pop)(NAME *vec);

// ensures that array [vec] has enough storage for [capacity] elements
// note: address of elements surely won’t change before [vec->n] exceeds capacity
void NAME_FUNCTION(_reserve)(NAME *vec, int capacity);

// changes number of elements in array [vec] to [newCnt]
// if the number increases, new elements get value [fill]
// if the number decreases, some elements at the end are removed
void NAME_FUNCTION(_resize)(NAME *vec, int newCnt, TYPE fill);

// inserts elements [arr[0]], [arr[1]], [arr[2]], ..., [arr[num-1]]
// in-between elements [vec->arr[where-1]] and [vec->arr[where]]
// note: the whole array [arr] cannot be part of array [vec]
//[where] may vary from 0 to [vec->n], [num] can also be zero
void NAME_FUNCTION(_insert)(NAME *vec, int where, TYPE *arr, int num);

// removes elements [vec->arr[k]] for k = [where], [where+1], ..., [where+num-1]
// all the elements starting from [where+num]-th are shifted left by [num] positions
void NAME_FUNCTION(_erase)(NAME *vec, int where, int num);
