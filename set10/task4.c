#include <stdio.h>
#include <stdlib.h>

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
    return (RAW_TYPE)NULL;
}

RAW_TYPE stackGet(Stack *self) {
    if (self->len > 0) {
        return self->buf.arr[self->len - 1];
    }
    return (RAW_TYPE)NULL;
}

void stackFree(Stack *self) {
    rawFree(&self->buf);

    self->len = 0;
}



#define THIS_CONST 1000000007

int main(int argc, char *argv[]) { 
    int n;
    scanf("%d\n", &n);

    Stack stack;
    stackInit(&stack);

    for (int i = 0; i < n; i++) {
        char symb;
        scanf("%c", &symb);
        switch (symb) {
            case '+': 
            {
                int a = stackPop(&stack);
                int b = stackPop(&stack);
                stackPush(&stack, (a + b)%THIS_CONST);
                if (i != n - 1) {
                    scanf(" ");
                }
                break;
            }
            case '-': 
            {
                int a = stackPop(&stack);
                int b = stackPop(&stack);
                stackPush(&stack, (b - a) % THIS_CONST);
                if (i != n - 1) {
                    scanf(" ");
                }
                break;
            }

            case '*': 
            {
                int a = stackPop(&stack);
                int b = stackPop(&stack);
                stackPush(&stack, (a * b) % THIS_CONST);
                if (i != n - 1) {
                    scanf(" ");
                }
                break;
            }


            default:
            {
                char word[15];
                int j = 0;
                while ('0' <= symb && symb <= '9') {
                    word[j] = symb;
                    j++;
                    if (scanf("%c", &symb) == 0) {
                        break;
                    }
                }
                word[j] = '\0';
            
                int value;
                sscanf(word, "%d", &value);
                stackPush(&stack, value);
                break;
            }
        }
    }

    printf("%d", stackPop(&stack));

    stackFree(&stack); 

    return EXIT_SUCCESS; 
}
