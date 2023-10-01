#include <stdio.h>
#include <stdbool.h>
#include <malloc.h>

bool symb_is_splitter(char symb, char* splitters, int splitters_amount) {
    for (int j=0; j<splitters_amount; j++) {
        if (splitters[j] == symb) {
            return true;
        }
    }

    return false;
}

int* split(char* s, char* splitters, int splitters_amount, int* len) {
    *len = 0;
    
    char symb = *s;
    int i = 0;
    bool outside_of_word = true;

    while (symb != '\0') {
        bool current_symb_is_splitter = symb_is_splitter(symb, splitters, splitters_amount);

        if (current_symb_is_splitter) {    
            outside_of_word = true;
        } else if (outside_of_word) {
            outside_of_word = false;
            (*len)++;
        }

        i++;
        symb = *(s + i);
    }


    symb = *s;
    i = 0;
    outside_of_word = true;
    int j = -1;
    int* arr = malloc(*len * 3 * sizeof(int));

    while (symb != '\0') {
        bool current_symb_is_splitter = symb_is_splitter(symb, splitters, splitters_amount); 
        
        if (current_symb_is_splitter) {
            outside_of_word = true;
        } else {
            if (outside_of_word) {
                outside_of_word = false;
                j++;
                *(arr + j * 3) = i;
                *(arr + j * 3 + 1) = 0;
                *(arr + j * 3 + 2) = 0; 
            }

            arr[j * 3 + 1]++;
            if ('A' <= symb && symb <= 'Z') {
                (*(arr + j * 3 + 2))++;
            }
        }
        i++;
        symb = *(s + i);
    }

    return arr;
}

int main() {

    char s[1000000];
    gets(s);

    char splitters[4] = ".,;:";
    int len;
    int* splitted_info = split(s, splitters, 4, &len);

    for (int i=0; i<len; i++) {
        printf("%d/%d ", splitted_info[i * 3 + 2], splitted_info[i * 3 + 1]);
        for (int j=0; j < splitted_info[i * 3 + 1]; j++) {
            printf("%c", s[splitted_info[i * 3] + j]);
        }
        printf("\n");
    }

    return 0;
}