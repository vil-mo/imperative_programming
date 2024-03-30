#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#define min(a, b) (a) < (b) ? (a) : (b)
#define max(a, b) (a) > (b) ? (a) : (b)

void rawInitWithCapasity(RawVec *self, int withCap) {
    self->cap = withCap;
    self->arr = malloc(withCap * sizeof(RAW_TYPE));
}

void rawReserve(RawVec *self, int newCap) {
    if (newCap <= self->cap) {
        return;
    }

    self->cap = max(max(newCap, self->cap * 2), 4);

    self->arr = realloc(self->arr, sizeof(RAW_TYPE) * self->cap);
}

typedef struct Deque {
    int head;
    int len;
    int cap;
    RAW_TYPE *buf;
} Deque;

void dequeInitWithCapasity(Deque *self, int withCap) {
    self->head = 0;
    self->len = 0;
    self->cap = 0;
    self->buf = NULL;
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
        return (RAW_TYPE)NULL;
    }

    int ind_to_pop = (self->head + self->len - 1) % self->buf.cap;

    self->len--;
    return self->buf.arr[ind_to_pop];
}

RAW_TYPE dequePopFirst(Deque *self) {
    if (self->len == 0) {
        return (RAW_TYPE)NULL;
    }
    int ind_to_pop = self->head;

    self->len--;
    self->head = (self->head + 1) % self->buf.cap;
    return self->buf.arr[ind_to_pop];
}

RAW_TYPE dequeGet(Deque *self, int index) {
    if (index >= self->len) {
        return (RAW_TYPE)NULL;
    }

    return self->buf.arr[(self->head + index) % self->buf.cap];
}

RAW_TYPE dequeGetLast(Deque *self) {
    if (self->len == 0) {
        return (RAW_TYPE)NULL;
    }

    int ind_to_ret = (self->head + self->len - 1) % self->buf.cap;

    return self->buf.arr[ind_to_ret];
}

RAW_TYPE dequeGetFirst(Deque *self) {
    if (self->len == 0) {
        return (RAW_TYPE)NULL;
    }
    return self->buf.arr[self->head];
}

void dequeFree(Deque *self) {
    free(self->buf);
}







int main(int argc, char *argv[]) {
    int n, m;
    scanf("%d %d\n", &n, &m);

    Deque left, right;
    dequeInitWithCapasity(&left, 2 * n + 1);
    dequeInitWithCapasity(&right, 2 * n + 1);

    for (int i = 1; i <= n; i++) {
        dequePushLast(&left, i);
        dequePushLast(&right, -i);
    }

    for (int i = 0; i < m; i++) {
        char c;
        scanf("%c", &c);
        int command;
        if ('0' <= c && c <= '9') {
            command = c - '0';
        } else {
            command = c - 'A' + 10;
        }

        Deque *deckToOperate;

        if ((command & 0b1000) > 0) {
            deckToOperate = &right;
        } else {
            deckToOperate = &left;
        }

        int card;
        if ((command & 0b0100) > 0) {
            card = dequePopLast(deckToOperate);
        } else {
            card = dequePopFirst(deckToOperate);
        }

        if (card == 0) {
            continue;
        }

        if ((command & 0b0010) > 0) {
            deckToOperate = &right;
        } else {
            deckToOperate = &left;
        }

        if ((command & 0b0001) > 0) {
            dequePushLast(deckToOperate, card);
        } else {
            dequePushFirst(deckToOperate, card);
        }

        // printf("\n=========\n%d ", left.len);
        // for (int i = 0; i < left.len; i++) {
        //     printf("%d ", dequeGet(&left, i));
        // }
        // printf("\n%d ", right.len);
        // for (int i = 0; i < right.len; i++) {
        //     printf("%d ", dequeGet(&right, i));
        // }
    }

    printf("\n%d ", left.len);
    for (int i = 0; i < left.len; i++) {
        printf("%d ", dequeGet(&left, i));
    }
    printf("\n%d ", right.len);
    for (int i = 0; i < right.len; i++) {
        printf("%d ", dequeGet(&right, i));
    }

    dequeFree(&left);
    dequeFree(&right);

    return EXIT_SUCCESS;
}
