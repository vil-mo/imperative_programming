#include <stdio.h>

void printTime (int h, int m, int s) {
    printf("%02d:%02d:%02d\n", h, m, s);
}

int main() {
    int n;
    scanf("%d", &n);

    for (int i=0; i<n; i++) {
        int h, m, s;
        scanf("%d %d %d", &h, &m, &s);
        printTime(h, m, s);
    }

    return 0;
}