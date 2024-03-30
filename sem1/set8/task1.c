#include <stdio.h>
#include <math.h>

int main() {
    FILE * in = fopen("input.txt", "rb");
    FILE * out = fopen("output.txt", "wb");

    int arr[2];

    fread(arr, sizeof(int), 2, in);


    long long x = arr[0], y = arr[1];

    long long res;
    res = 0xff00ffffffffffff;
    int val = fwrite(&res, sizeof(int), 1, out);


    printf("%d", val);

    fclose(in);
    fclose(out);

    return 0;
}