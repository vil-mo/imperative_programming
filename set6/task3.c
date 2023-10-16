#include <stdio.h>
#include <malloc.h>

char *strCreate() {
    int len;
    fscanf(stdin, " %d ", &len);

    char* str = malloc(len * sizeof(char));

    for (int i = 0; i < len; i++) {
        fscanf(stdin, "%c", &str[i]);
    }

    return str;
}

void strRemove(char* str) {
    free(str);
}

void strPrint(char* str) {
    for (int i = 0; i < sizeof(str) / sizeof(char); i++) {
        if (str[i] == '\0') {
            break;
        }
        fprintf(stdout, "%c", str[i]);
    }
    fprintf(stdout, "\n");
}

void strPrintAmountOf(char* str, char symb) {
    int am = 0;
    for (int i = 0; i < sizeof(str) / sizeof(char); i++) {
        if (str[i] == symb) {
            am++;
        }
    }
    fprintf(stdout, "%d\n", am);
}


int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int n;
    fscanf(stdin, "%d", &n);

    char* arr[n];
    int current_index = 0;

    for (int i = 0; i < n; i++) {
        int command;
        fscanf(stdin, "%d", &command);

        switch (command) {
            case 0: {
                arr[current_index] = strCreate();
                current_index++;
                break;
            }
            case 1: {
                int ind;
                fscanf(stdin, " %d", &ind);
                strRemove(arr[ind]);
                arr[ind] = NULL;
                break;
            }
            case 2: {
                int ind;
                fscanf(stdin, " %d", &ind);
                strPrint(arr[ind]);
                break;
            }
            case 3: {
                int ind;
                char symb;
                fscanf(stdin, " %d %c", &ind, &symb);
                strPrintAmountOf(arr[ind], symb);
                break;
            }
            default:
                break;
        }
    }

    for (int i = 0; i < current_index; i++) {
        if (arr[i] != NULL) {
            free(arr[i]);
        }
    }


    fclose(stdin);
    fclose(stdout);

    return 0;
}