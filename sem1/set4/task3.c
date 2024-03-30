#include <stdio.h>
#include <string.h>

char* pref_end = 0;

char* concat(char *pref, char *suff) {
    
    int len_suff = 0;
    while(*(suff + len_suff) != '\0') {
        len_suff++;
    }

    for (int i=0; i<=len_suff; i++) {
        *(pref_end + i) = *(suff + i);
    }

    return pref_end + len_suff;
}

int main() {
    int n;
    scanf("%d", &n);

    char s[n*100+1];
    scanf("%s", s);
    
    {
        int len_pref = 0;
        while(s[len_pref] != '\0') {
            len_pref++;
        }
        pref_end = s + len_pref;
    }

    for (int i=1; i<n; i++) {
        char curr_s[101];
        scanf("%s", curr_s);
        pref_end = concat(s, curr_s);
    }
    puts(s);

    return 0;
}