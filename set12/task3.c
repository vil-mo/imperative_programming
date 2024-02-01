#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define RAW_TYPE BioAndMovie 







typedef struct ActorBio {
    char Name[33];
    int BirthEar;
    char Country[13];
} ActorBio;

typedef struct ActorInMovie {
    char ActorName[33];
    char MovieName[23];
} ActorInMovie;

typedef struct BioAndMovie {
    ActorBio bio;
    ActorInMovie movie;
} BioAndMovie;

char *scanString(char s[]) {
    int i = 0;

    scanf("\"%c", &s[i]);
    while (s[i] != '"') {
        i++;
        scanf("%c", &s[i]);
    }
    s[i] = '\0';

    return s;
}









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
    return self->buf.arr[index];
}

void vecFree(Vector *self) {
    rawFree(&self->buf); 

    self->len = 0;
}











int main(int argc, char *argv[]) {
    int n, m;
    scanf("%d\n", &n);

    ActorBio *bios = malloc(n * sizeof(ActorBio));

    for (int i = 0; i < n; i++) {
        scanString(bios[i].Name);
        scanf("%d ", &bios[i].BirthEar);
        scanString(bios[i].Country);
        scanf("\n");
    }

    scanf("%d\n", &m);
    ActorInMovie *movies = malloc(m * sizeof(ActorInMovie));

    Vector bnm;
    vecInit(&bnm);

    for (int i = 0; i < m; i++) {
        scanString(movies[i].ActorName);
        scanf(" ");
        scanString(movies[i].MovieName);
        scanf("\n");


        for (int j = 0; j < n; j++) {
            if (strcmp(bios[j].Name, movies[i].ActorName) == 0) {
                BioAndMovie bio_n_movie;
                bio_n_movie.bio = bios[j];
                bio_n_movie.movie = movies[i];

                vecPush(&bnm, bio_n_movie);
            }
        }
    }

    for (int i = 0; i < bnm.len; i++) {
        BioAndMovie b = vecGet(&bnm, i);
        printf("\"%s\" %d \"%s\" \"%s\" \"%s\"\n", 
            b.bio.Name, b.bio.BirthEar, b.bio.Country, 
            b.movie.ActorName, b.movie.MovieName);
    }

    free(bios);
    free(movies);
    vecFree(&bnm);

    return EXIT_SUCCESS;
}
