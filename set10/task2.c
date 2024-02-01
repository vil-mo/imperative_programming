#include <stdio.h>
#include <stdlib.h>

#define RAW_TYPE char *

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













typedef struct Vector {
    int len;
    RawVec buf;   
} Vector;

void vecInit(Vector *self) {
    self->len = 0;
    rawInit(&self->buf);
}

void vecGrow(Vector *self, int additional) {
    rawReserve(&self->buf, self->len + additional);
    //
}

void vecPush(Vector *self, RAW_TYPE value) {
    vecGrow(self, 1);
    self->buf.arr[self->len] = value;
    self->len++;
}

RAW_TYPE vecPop(Vector *self) {
    self->len--;
    return self->buf.arr[self->len];
}

RAW_TYPE vecGet(Vector *self, int index) {
    if (index < self->len) {
        return self->buf.arr[index];
    }
    return NULL;
}

void vecFree(Vector *self) {
    rawFree(&self->buf); 

    self->len = 0;
}






int main() {
    Vector vects[1000001];

    for (int i = 0; i <= 1000000; i++) {
        vecInit(&vects[i]);
    }

    int n;
    scanf("%d", &n);
   
    for (int i = 0; i < n; i++) {
        int key;
        char *s = malloc(sizeof(char) * 7);

        scanf("%d %s", &key, s);

        vecPush(&vects[key], s);
    }

    for (int i = 0; i <= 1000000; i++) {
        for (int j = 0; j < vects[i].len; j++) {
            char *s = vecGet(&vects[i], j);
            printf("%d %s\n", i, s);

            free(s);
        }
        vecFree(&vects[i]);
    }

    return EXIT_SUCCESS;
}
