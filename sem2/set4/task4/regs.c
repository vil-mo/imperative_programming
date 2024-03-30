#include "stdio.h"
#include <stdlib.h>
#include <string.h>

typedef struct State {
    char *regs[256];
} State;

// prints ’ECHO: ’ and all passed strings separated by ’|’
void echo_0(State *state) {
    printf("ECHO: \n");
}
void echo_1(State *state, char *arg0) {
    printf("ECHO: %s\n", arg0);
}
void echo_2(State *state, char *arg0, char *arg1) {
    printf("ECHO: %s|%s\n", arg0, arg1);
}
void echo_3(State *state, char *arg0, char *arg1, char *arg2) {
    printf("ECHO: %s|%s|%s\n", arg0, arg1, arg2);
}

static inline int to_int(char *str) {
    int res = 0;
    for (int i = 0; str[i] != '\0'; i++) {
        res *= 10;
        res += str[i] - '0';
    }

    return res;
}

// prints contents of I-th register (it must not be NULL)
//[idx] contains decimal representation of I
void print_1(State *state, char *idx) {
    int i = to_int(idx);
    if (state->regs[i] != NULL) {
        printf("%s\n", state->regs[i]);
    }
}

// prints all non-NULL registers with their values (sorted by register number)
void printregs_0(State *state) {
    for (int i = 0; i < 256; i++) {
        if (state->regs[i] != NULL) {
            printf("%d = %s\n", i, state->regs[i]);
        }
    }
}

static inline int string_len(char *str) {
    int l = 0;
    while (str[l] != '\0') {
        l++;
    }
    l++;

    return l;
}

// saves a copy of string [what] into I-th register
//[idx] contains decimal representation of I
void store_2(State *state, char *idx, char *what) {
    int i = to_int(idx);

    if (state->regs[i] != NULL) {
        free(state->regs[i]);
    }

    state->regs[i] = malloc(string_len(what) * sizeof(char));

    strcpy(state->regs[i], what);
}

// copies contents of S-th register into D-th register (S-th register is not NULL)
//[dst] and [src] contain decimal representations of D and S respectively
// BEWARE: [dst] and [src] are allowed to be equal indices
void copy_2(State *state, char *dst, char *src) {
    int d = to_int(dst);
    int s = to_int(src);

    if (d != s) {
        if (state->regs[d] != NULL) {
            free(state->regs[d]);
        }

        state->regs[d] = malloc(string_len(state->regs[s]) * sizeof(char));

        strcpy(state->regs[d], state->regs[s]);
    }
}

// assigns NULL to I-th register
//[idx] contains decimal representation of I
void clear_1(State *state, char *idx) {
    int i = to_int(idx);

    if (state->regs[i] != NULL) {
        free(state->regs[i]);

        state->regs[i] = NULL;
    }
}
