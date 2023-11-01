#include <stdio.h>

int convert(int num) {
    int b0, b1, b2, b3;

    b0 = (num & 0x000000ff) << 24u;
    b1 = (num & 0x0000ff00) << 8u;
    b2 = (num & 0x00ff0000) >> 8u;
    b3 = (num & 0xff000000) >> 24u;

    return b3 | b2 | b1 | b0;
}

int main() {
    FILE * in = fopen("input.txt", "rb");
    FILE * out = fopen("output.txt", "wb");

    int n;
    fread(&n, sizeof(int), 1, in);

    int shouldConvert = 0;

    if (n > 10000) {
        shouldConvert = 1;
        n = convert(n);
    }

    int s = 0;


    for (int i = 0; i < n; i++) {
        int num;
        fread(&num, sizeof(int), 1, in);

        if (shouldConvert) {
            num = convert(num);
        }

        s += num;
    }

    if (shouldConvert) {
        s = convert(s);
    }

    fwrite(&s, sizeof(int), 1, out);

    fclose(in);
    fclose(out);

    return 0;
}