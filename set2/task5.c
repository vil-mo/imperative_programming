#include <stdio.h>
#include <stdbool.h>

void main() {
    char symbol;
    scanf("%c", &symbol);
    
    bool word_considered = false;
    int word_amonut = 0;

    while (symbol != '\n')
    {
        if (symbol == '.') {
            word_considered = false;
        } else if (! word_considered) {
            word_amonut++;
            word_considered = true;
        }

        scanf("%c", &symbol);
    }

    printf("%d\n", word_amonut);
    

}