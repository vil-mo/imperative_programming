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
} Deque;


void dequeInit(Deque *self) {
    self->head = 0;
    self->len = 0;

    rawInit(&self->buf);
}

void dequeInitWithCapasity(Deque *self, int withCap) {
    self->head = 0;
    self->len = 0;

    rawInitWithCapasity(&self->buf, withCap);
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
    dequeGrowIfFull(self, 1);

    int ind_to_put = (self->head + self->len) % self->buf.cap;

    self->buf.arr[ind_to_put] = value;
    self->len++;
}

void dequePushFirst(Deque *self, RAW_TYPE value) {
    dequeGrowIfFull(self, 1);

    self->head = (self->head + self->buf.cap - 1) % self->buf.cap;
    self->buf.arr[self->head] = value;
    self->len++;
}

RAW_TYPE dequePopLast(Deque *self) {
    if (self->len == 0) {
        return (RAW_TYPE) 0;
    }

    int ind_to_pop = (self->head + self->len - 1) % self->buf.cap;

    self->len--;
    return self->buf.arr[ind_to_pop];
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

RAW_TYPE dequeGet(Deque *self, int index) {
    if (index >= self->len) {
        return (RAW_TYPE) 0;
    }

    return self->buf.arr[(self->head + index) % self->buf.cap];
}

RAW_TYPE dequeGetLast(Deque *self) {
    if (self->len == 0) {
        return (RAW_TYPE) 0;
    }

    int ind_to_ret = (self->head + self->len - 1) % self->buf.cap;

    return self->buf.arr[ind_to_ret];
}

RAW_TYPE dequeGetFirst(Deque *self) {
    if (self->len == 0) {
        return (RAW_TYPE) 0;
    }
    return self->buf.arr[self->head];
}

void dequeFree(Deque *self) {
    rawFree(&self->buf);

    self->head = 0;
    self->len = 0;
}




int main(int argc, char *argv[])
{
    int n, m;
    scanf("%d %d", &n, &m);

    Deque messages;
    dequeInit(&messages);


    for (int i = 0; i < n; i++) {
        int mtime;
        scanf("%d", &mtime);

        dequePushLast(&messages, mtime);

        while (mtime - dequeGetFirst(&messages) > m) {
            dequePopFirst(&messages);
        }

        printf("%d\n", messages.len);
    }


    dequeFree(&messages);

    return EXIT_SUCCESS;
}
