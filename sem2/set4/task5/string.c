#include <stdlib.h>
#include <string.h>

typedef struct State {
    char *regs[256];
} State;

static inline int to_int(char *str) {
    int res = 0;
    for (int i = 0; str[i] != '\0'; i++) {
        res *= 10;
        res += str[i] - '0';
    }

    return res;
}

static inline void to_string(int n, char *str) {
    int cur_i = 0;
    int cur_n;
    if (n >= 100) {
        str[cur_i] = (cur_n / 100) + '0';
        cur_n %= 100;
        cur_i++;
    }
    if (n >= 10) {
        str[cur_i] = (cur_n / 100) + '0';
        cur_n %= 10;
        cur_i++;
    }

    str[cur_i] = cur_n + '0';
    cur_i++;
     
    str[cur_i] = '\0';
}

static inline int string_len(char *str) {
    if (str == NULL) {
        return 0;
    }

    int l = 0;
    while (str[l] != '\0') {
        l++;
    }
    l++;

    return l;
}

// loads string A from I-th register ([idx0] contains its index)
// loads string B from J-th register ([idx1] contains its index)
// then stores concatenation of A and B into I-th register
// BEWARE: [idx0] and [idx1] are allowed to be equal indices
void concat_2(State *state, char *idx0, char *idx1) {
    int a = to_int(idx0);
    int b = to_int(idx1);

    int a_len = string_len(state->regs[a]); 
    int b_len = string_len(state->regs[b]);

    state->regs[a] = realloc(state->regs[a], (a_len + b_len) * sizeof(char));

    strcpy(&state->regs[a][a_len], state->regs[b]);
}

// extracts sequence of tokens/words separated by underscore character from string [arg]
// puts K –- number of tokens into 0-th register
// puts the tokens into 1-th, 2-th, ..., K-th registers (in correct order)
void tokenize_1(State *state, char *arg) {
    int k = 1;

    int arg_i = 0;
    while (arg[arg_i] == '_') {
        arg_i++;
    }

    while (arg[arg_i] != '\0') {
        int curr_arg_i = arg_i;
        while (arg[arg_i] != '_' && arg[arg_i] != '\0') {
            arg_i++;
        }

        if (state->regs[k] != NULL) {
            free(state->regs[k]);
        }
        state->regs[k] = malloc((arg_i - curr_arg_i) * sizeof(char));
        memcpy(state->regs[k], &arg[curr_arg_i], (arg_i - curr_arg_i) * sizeof(char));

        k++;

        while (arg[arg_i] == '_') {
            arg_i++;
        }
    }

    if (state->regs[0] != NULL) {
        free(state->regs[0]);
    }

    state->regs[0] = malloc(4 * sizeof(char));

    to_string(k, state->regs[0]);
}
