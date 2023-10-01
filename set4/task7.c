#include <stdio.h>

int main() {

    int arr[127];
    for (int i = 32; i < 127; i++) {
        arr[i] = 0;
    }

    char symb;
    while (scanf("%c", &symb) == 1) {
        arr[symb]++;
    }

    for (int i = 32; i < 127; i++) {
        if (arr[i] > 0) {
            printf("%c ", (char)i);

            for (int j = 0; j < arr[i]; j++) {
                printf("#");
            }

            printf("\n");
        }
    }
    
    return 0;
}