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









typedef struct Deque {
    int head;
    int len;
    RawVec buf;

    RAW_TYPE min;
    RAW_TYPE max;
} Deque;

void dequeInit(Deque *self) {
    self->head = 0;
    self->len = 0;

    rawInit(&self->buf);

    self->min = 0;
    self->max = 0;
}

void dequeGrowIfFull(Deque *self, int growAmount) {
    if (self->len + growAmount <= self->buf.cap) {
        return;
    }

    rawReserve(&self->buf, self->len + growAmount);

    int fromCopyIndex, toCopyIndex, copyAmount;
    if (self->head < self->len / 2) {
        fromCopyIndex = 0;
        copyAmount = self->head;
        toCopyIndex = self->len;
    } else {
        fromCopyIndex = self->head;
        copyAmount = self->len - self->head;
        toCopyIndex = self->buf.cap - copyAmount;
        
        self->head = toCopyIndex % self->buf.cap;
    }

    memcpy(&self->buf.arr[toCopyIndex], &self->buf.arr[fromCopyIndex], copyAmount * sizeof(RAW_TYPE));
}

void dequePushLast(Deque *self, RAW_TYPE value) {
    if (self->len == 0 || value > self->max) {
        self->max = value;
    }
    if (self->len == 0 || value < self->min) {
        self->min = value;
    }

    dequeGrowIfFull(self, 1);

    int ind_to_put = (self->head + self->len) % self->buf.cap;

    self->buf.arr[ind_to_put] = value;
    self->len++;
}

RAW_TYPE dequePopFirst(Deque *self) {
    if (self->len == 0) {
        return (RAW_TYPE) 0;
    }
    int ind_to_pop = self->head;

    self->len--;
    self->head = (self->head + 1) % self->buf.cap;
    return self->buf.arr[ind_to_pop];
}

void dequeFree(Deque *self) {
    rawFree(&self->buf);

    self->len = 0;
    self->head = 0;
    self->max = 0;
    self->min = 0;
}

RAW_TYPE dequeMax(Deque *self) {
    if (self->len == 0) {
        return (RAW_TYPE) 0;
    }
    return self->max;
}

RAW_TYPE dequeMin(Deque *self) {
    if (self->len == 0) {
        return (RAW_TYPE) 0;
    }
    return self->min;
}


int main(int argc, char *argv[])
{
    int n;
    scanf("%d", &n);

    Deque deque;
    dequeInit(&deque);

    for (int i = 0; i < n; i++) {
        char command[9];

        scanf("%s", command);

        if (strcmp(command, "enqueue") == 0) {
            int val;
            scanf("%d", &val);

            dequeEnqueue(&deque, val);
        } else if (strcmp(command, "dequeue") == 0) {
            printf("%d\n", dequeDequeue(&deque));
        } else if (strcmp(command, "max") == 0) {
            printf("%d\n", dequeMax(&deque));
        } else if (strcmp(command, "min") == 0) {
            printf("%d\n", dequeMin(&deque));
        }
    }

    dequeFree(&deque);

    return EXIT_SUCCESS;
}
