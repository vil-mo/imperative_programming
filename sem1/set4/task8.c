#include <stdio.h>

int amount_of_digits(int num) {
    int amount = 1;

    while (num >= 10) {
        num /= 10;
        amount++;
    }
    
    return amount;
}

int id_digits = 1, fragments_digits = 1, lenght_digits = 1;

void printSpaces(int amount) {
    for (int i = 0; i < amount; i++) {
        printf(" ");
    }
}

void printMinuses(int amount) {
    for (int i = 0; i < amount; i++) {
        printf("-");
    }
}

void printTableThing() {
    printf("+-");
    printMinuses(id_digits);
    printf("-+-");
    printMinuses(fragments_digits);
    printf("-+-");
    printMinuses(lenght_digits);
    printf("-+\n");
}

int main() {
    int n;
    scanf("%d", &n);

    int fragments[1001];
    int lenght[1001];
    for (int i = 0; i < 1001; i++) {
        fragments[i] = 0;
        lenght[i] = 0;
    }


    for (int i = 0; i < n; i++) {
        int id, len;

        scanf("%d %d", &id, &len);

        fragments[id]++;
        lenght[id] += len;

        if (amount_of_digits(id) > id_digits) {
            id_digits = amount_of_digits(id);
        }
        if (amount_of_digits(fragments[id]) > fragments_digits) {
            fragments_digits = amount_of_digits(fragments[id]);
        }
        if (amount_of_digits(lenght[id]) > lenght_digits) {
            lenght_digits = amount_of_digits(lenght[id]);
        }
    }

    printTableThing();
    for (int i = 0; i < 1001; i++) {
        if (fragments[i] > 0) {
            printf("| ");
            printSpaces(id_digits - amount_of_digits(i));
            printf("%d | ", i);
            printSpaces(fragments_digits - amount_of_digits(fragments[i]));
            printf("%d | ", fragments[i]);
            printSpaces(lenght_digits - amount_of_digits(lenght[i]));
            printf("%d |\n", lenght[i]);
            printTableThing();
        }
    }


    return 0;
}