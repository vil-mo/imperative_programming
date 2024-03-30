#ifndef INTEGERSET_3214341
#define INTEGERSET_3214341

typedef struct {
    int cap;
    int max_i_diff;
    int zero_in;
} IntegerSet;


IntegerSet *CreateSet(int *, int);

int IsInSet(IntegerSet *, int);

#endif