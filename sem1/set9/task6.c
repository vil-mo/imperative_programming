#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct Node_s {
    uint8_t key[4];
    uint32_t val;
} Node;

void sort_digit(Node *input, Node *output, uint32_t len, uint32_t digits_am[256], uint32_t digit) {
    for (int i = 0; i < 256; i++) {
        digits_am[i] = 0;
    }

    for (int i = 0; i < len; i++) {
        digits_am[input[i].key[digit]]++;
    }

    digits_am[0]--;
    for (int i = 1; i < 256; i++) {
        digits_am[i] += digits_am[i - 1];
    }

    for (int i = 0; i < len; i++) {
        Node node = input[i];
        output[digits_am[node.key[digit]]] = node;
        digits_am[node.key[digit]]++;
    }
}

void radix_sort(Node *arr, uint32_t len) {
    Node *arr2 = malloc(sizeof(Node) * len);
    uint32_t digits_am[256];

    sort_digit(arr, arr2, len, digits_am, 0);
    sort_digit(arr2, arr, len, digits_am, 1);
    sort_digit(arr, arr2, len, digits_am, 2);
    sort_digit(arr2, arr, len, digits_am, 3);

    free(arr2);
}

int main() {
    FILE *in = fopen("input.txt", "rb");
    FILE *out = fopen("output.txt", "wb");

    uint32_t n;
    fread(&n, sizeof(uint32_t), 1, in);

    Node *arr = malloc(n * sizeof(Node));

    for (int i = 0; i < n; i++) {
        fread(&arr[i].key, sizeof(uint8_t), 4, in);
        fread(&arr[i].val, sizeof(uint32_t), 1, in);
    }

    radix_sort(arr, n);

    for (int i = 0; i < n; i++) {
        fwrite(&arr[i].key, sizeof(uint8_t), 4, out);
        fwrite(&arr[i].val, sizeof(uint32_t), 1, out);
    }

    free(arr);
    fclose(in);
    fclose(out);

    return 0;
}
