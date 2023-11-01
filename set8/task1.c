#include <stdio.h>
#include <math.h>

int main() {
    FILE * in = fopen("input.txt", "rb");
    FILE * out = fopen("output.txt", "wb");

    int arr[2];

    fread(arr, sizeof(int), 2, in);


    long long x = arr[0], y = arr[1];
    long long res = floor((x + y) / 2.0);


    fwrite(&res, sizeof(int), 1, out);

    fclose(in);
    fclose(out);

    return 0;
}