#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define RAW_TYPE int

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












typedef struct Stack {
    RawVec buf;
    int len;
} Stack;

void stackInit(Stack *self) {
    self->len = 0;
    rawInit(&self->buf);
}

void stackGrow(Stack *self, int additional) {
    rawReserve(&self->buf, self->len + additional);
    //
}

void stackPush(Stack *self, RAW_TYPE value) {
    stackGrow(self, 1);
    self->buf.arr[self->len] = value;
    self->len++;
}

RAW_TYPE stackPop(Stack *self) {
    if (self->len > 0) {
        self->len--;
        return self->buf.arr[self->len];
    }
    return (RAW_TYPE) 0;
}

RAW_TYPE stackGet(Stack *self) {
    if (self->len > 0) {
        return self->buf.arr[self->len - 1];
    }
    return (RAW_TYPE) 0;
}

void stackFree(Stack *self) {
    rawFree(&self->buf);

    self->len = 0;
}









typedef struct MinMaxStack {
    Stack values;
    Stack min;
    Stack max;
} MinMaxStack;

void minMaxStackInit(MinMaxStack *self) {
    stackInit(&self->values);
    stackInit(&self->min);
    stackInit(&self->max);
}

void minMaxStackPush(MinMaxStack *self, RAW_TYPE value) {
    int len = self->values.len;
    if (len == 0 || value >= stackGet(&self->max)) {
        stackPush(&self->max, value);
        
    }
    if (len == 0 || value <= stackGet(&self->min)) {
        stackPush(&self->min, value);
    }

    stackPush(&self->values, value);
}

RAW_TYPE minMaxStackPop(MinMaxStack *self) {
    RAW_TYPE val = stackGet(&self->values);
    if (val == stackGet(&self->max)) {
        stackPop(&self->max);
    }
    if (val == stackGet(&self->min)) {
        stackPop(&self->min);
    }

    return stackPop(&self->values);
}

RAW_TYPE minMaxStackGet(MinMaxStack *self) {
    return stackGet(&self->values);
}

void minMaxStackFree(MinMaxStack *self) {
    stackFree(&self->values);
    stackFree(&self->min);
    stackFree(&self->max);
}

RAW_TYPE minMaxStackMin(MinMaxStack *self) {
    return stackGet(&self->min);
}

RAW_TYPE minMaxStackMax(MinMaxStack *self) {
    return stackGet(&self->max);
}




int main(int argc, char *argv[])
{
    int n;
    scanf("%d", &n);

    MinMaxStack stack;
    minMaxStackInit(&stack);

    for (int i = 0; i < n; i++) {
        char command[6];

        scanf("%s", command);

        if (strcmp(command, "push") == 0) {
            int val;
            scanf("%d", &val);

            minMaxStackPush(&stack, val);
        } else if (strcmp(command, "pop") == 0) {
            printf("%d\n", minMaxStackPop(&stack));
        } else if (strcmp(command, "max") == 0) {
            printf("%d\n", minMaxStackMax(&stack));
        } else if (strcmp(command, "min") == 0) {
            printf("%d\n", minMaxStackMin(&stack));
        }
    }

    minMaxStackFree(&stack);

    return EXIT_SUCCESS;
}
