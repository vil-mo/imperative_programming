#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int main(int _argc, char *_argv[])
{
    FILE *in = fopen("input.txt", "r");
    FILE *out = fopen("output.txt", "w");

    int argc = 0;
    char argv[100][100];
    int curr_argi = 0;

    char symb;
    fscanf(in, "%c", &symb);

    bool devide_with_spaces = true;

    while (symb != '\0' && !feof(in)) {
        if (symb == '"') {
            devide_with_spaces = !devide_with_spaces;
        } else if (symb == ' ' && devide_with_spaces) {
            if (curr_argi != 0) {
                argv[argc][curr_argi] = '\0';
                argc++;
                curr_argi = 0;
            }
        } else if (
                symb == ' ' ||
                ('a' <= symb && symb <= 'z') ||
                ('A' <= symb && symb <= 'Z') ||
                ('0' <= symb && symb <= '9')
            ) {
            argv[argc][curr_argi] = symb;
            curr_argi++;
        }

        fscanf(in, "%c", &symb); 
    }

    if (curr_argi != 0) {
        argc++;
    }

    for (int i = 0; i < argc; i++) {
        fprintf(out, "[%s]\n", argv[i]);
    }


    fclose(in);
    fclose(out);

    return EXIT_SUCCESS;
}
