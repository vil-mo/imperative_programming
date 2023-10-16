#include <stdio.h>
#include <stdbool.h>
#include <malloc.h>

typedef struct Tokens_s {
    int num;
    char **arr;
} Tokens;

void tokensSplit(Tokens *tokens, const char *str, const char *delims) {
    bool is_inside_of_word = false;
    tokens->num = -1;
    int current_token_beggining_index = 0;

    for (int i = 0; 1; i++) {
        char symb = str[i];
        if (symb == '\0') {
            break;
        }
        
        bool is_symb_delim = false;

        for (int j = 0;; j++) {
            char delim = delims[j];
            if (delim == '\0') {
                break;
            }

            if (symb == delim) {
                is_symb_delim = true;
                break;
            }
        }

        if (is_symb_delim) {
            if (is_inside_of_word) {
                is_inside_of_word = false;

                if (tokens->arr != NULL) {
                    tokens->arr[tokens->num] = malloc((i - current_token_beggining_index + 1) * sizeof(char));
                    for (int j = current_token_beggining_index; j < i; j++) {
                        tokens->arr[tokens->num][j - current_token_beggining_index] = str[j];
                    }
                    tokens->arr[tokens->num][i - current_token_beggining_index] = '\0';
                }
            }
        } else {
            if (!is_inside_of_word) {
                is_inside_of_word = true;
                tokens->num++;
                current_token_beggining_index = i;
            }
        }
    }

    tokens->num++;

}

void tokensFree(Tokens *tokens) {
    if (tokens->arr == NULL) {
        return;
    }

    for (int i = 0; i < tokens->num; i++) {
        free(tokens->arr[i]);
    }

    free(tokens->arr);
    tokens->arr = NULL;
}


int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    char str[1000000];
    fscanf(stdin, "%s", str);
    char delims[5] = ".,;:\0";
    Tokens tokens;
    tokens.arr = NULL;

    tokensSplit(&tokens, str, delims);
    tokens.arr = malloc(tokens.num * sizeof(char*));
    tokensSplit(&tokens, str, delims);

    printf("%d\n", tokens.num);
    for (int i = 0; i < tokens.num; i++) {
        for (int j = 0; 1; j++) {
            if (tokens.arr[i][j] == '\0') {
                break;
            }
            printf("%c", tokens.arr[i][j]);
        }
        printf("\n");
    }

    tokensFree(&tokens);

    fclose(stdin);
    fclose(stdout);

    return 0;
}