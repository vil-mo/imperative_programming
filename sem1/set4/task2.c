#include <stdio.h>

void reverse(char *start, int len) {
    for (int i=0; i<len/2; i++) {
        char symb = *(start+i);
        *(start+i) = *(start + len - i - 1);
        *(start + len - i - 1) = symb;
    }
}

int main() {
    int n;
    scanf("%d", &n);

    char s[101];
    for (int i=0; i<n; i++) {
        scanf("%s", s);

        int len = 0;
        while(s[len] != '\0') {
            len++;
        }
        reverse(s, len);
        printf("%s\n", s);   
    }

    return 0;
}