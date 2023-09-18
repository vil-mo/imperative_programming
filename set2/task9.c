#include <stdio.h>
#include <stdbool.h>

void main() {

    bool is_in_multiline_comment = false;
    bool is_in_singleline_comment = false;
    bool last_symb_is_part_of_comment = false;
    char last_symb, symb;
    scanf("%c", &last_symb);

    while (true)
    {
        if (scanf("%c", &symb) != 1) {


            break;
        }

        if (is_in_multiline_comment) {
            if (last_symb == '*' && symb == '/') {
                is_in_multiline_comment = false;
            } else if(symb == '\n') {
                printf("\n");
            }
        } else if (is_in_singleline_comment) {
            if (symb == '\n') {
                printf("\n");
                is_in_singleline_comment = false;
            }
        } else if (last_symb_is_part_of_comment) {
            last_symb_is_part_of_comment = false;
        } else {
            if (last_symb == '/' && symb == '*') {
                is_in_multiline_comment = true;
                last_symb_is_part_of_comment = true;
                scanf("%c", &last_symb);
            } else if (last_symb == '/' && symb == '/') {
                is_in_singleline_comment = true;
                last_symb_is_part_of_comment = true;
            } else {
                printf("%c", last_symb);
            }
        }
        last_symb = symb;
    }

    if (last_symb == '\n' || !(is_in_multiline_comment || is_in_singleline_comment)) {
        printf("%c", last_symb);
    }
}