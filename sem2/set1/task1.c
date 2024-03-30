#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum Operation {
    ADD,
    SUB,
    MUL,
} Operation;

int main(int argc, char *argv[])
{
    if (argc == 1) {
        fprintf(stderr, "No parameters specified.");
        return 13;
    }
    
    int64_t m = -1;
    Operation operation = ADD;
    int64_t num1 = 10;
    int64_t num2 = 4;
    int64_t result;

    int i = 1;

    if (strcmp("-m", argv[i]) == 0) {
        i++;
        sscanf(argv[i], "%lld", &m);
        i++;
    }
    if (strcmp("add", argv[i]) == 0) {
        operation = ADD;
    } else if (strcmp("sub", argv[i]) == 0) {
        operation = SUB;
    } else {
        operation = MUL;
    }

    i++;
    sscanf(argv[i], "%lld", &num1);
    i++;
    sscanf(argv[i], "%lld", &num2);
    i++;
    
    if (i < argc) {
        sscanf(argv[i + 1], "%lld", &m);
    }


    switch (operation) {
        case ADD:
            result = num1 + num2;
            break;
        case SUB:
            result = num1 - num2;
            break;
        case MUL:
            result = num1 * num2;
            break;
    }

    if (m > 0) {
        result = result % m;
        if (result < 0) {
            result += m;
        }
    }

    printf("%lld", result);


    return EXIT_SUCCESS;
}
